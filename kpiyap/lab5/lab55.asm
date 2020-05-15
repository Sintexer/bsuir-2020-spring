.model small
.stack 256
.data 
cmd_line db 127 dup (0)
path db 127 dup(0)
string db 127 dup (0)
string_len dw 0
change db 127 dup (0)
change_len dw 0
argc db 0
path_temp db 13 dup(0)
handle dw 0
handle_temp dw 0
buffer db 200 dup (?)
buffer_len dw 200
buf_len equ 200

input_error_str db "ERROR: first substring is too short", 10, 13, "$"
file_open_error_str db "ERROR: Can't open input file", 10, 13, "$"
temp_file_error_str db "ERROR: Can't open temp file", 10, 13, "$"
file_close_error_str db "ERROR: Can't close input file", 10, 13, "$"
temp_file_close_error_str db "ERROR: Can't close temp file", 10, 13, "$"
temp_file_delete_error_str db "ERROR: Can't delete temp file", 10, 13, "$"
not_enough_cmdl_len_str db "ERROR: Not enough command line arguments.", 10, 13, "$"
too_many_args_str db "ERROR: Provided to many arguments", 10, 13, "$"
cmd_line_example_str db "Example: lab55.exe [inputfile.txt] [", 22h, "first_substr", 22h, "] [", 22h, "second_substr", 22h,"]", 10, 13, "$"


.code
jmp start

print_str MACRO out_str   				;Prints str to screen
        push ax
        push dx   
        push di
        xor di, di
		MOV AH, 09h
		MOV DX, OFFSET out_str
		INT 21h 
		pop di   
		pop dx
		pop ax
ENDM 

strlen macro stroke						;finds amount of characters before 0, returns length in cx
	push di 
	push cx
	mov al, 0
	mov di, offset stroke
	mov cx, 70h
	repne scasb
	inc cx
	mov ax, 70h
	sub ax, cx
	pop cx
	pop di 
endm strlen

move_fptr macro pcx, pdx, pal, psi 		;pcx*65536+pdx - offset, pal - from where to start (0 - begin,1 - current, 2 - end), psi - what file
	push ax 
	push dx 
	push cx
	push si
	mov cx, pcx 
	mov dx, pdx
	mov al, pal
	mov si, psi
	call shift_fptr
	pop si
	pop cx 
	pop dx 
	pop ax
endm move_fptr

shift_fptr proc 						;cx, dx, al, si - [0-handle, 1-handle_temp]
	push bx 
	mov ah, 42h
	cmp si, 0
	jne sfptr_temp
	mov bx, handle
	jmp sftpr_call

	sfptr_temp:
		mov bx, handle_temp
	sftpr_call:
		int 21h
		pop bx
	ret
shift_fptr endp

write_change proc 						;Writes change str to temp file
	push ax 
	push bx
	push dx
	push cx
	mov ah, 40h
	mov bx, handle_temp
	lea dx, change 
	mov cx, change_len
	int 21h
	pop cx 
	pop dx
	pop bx
	pop ax
	ret 
write_change endp

write_file macro fhandle, str 			;cx - str_len
	push ax 
	push bx
	push dx
	push cx
	mov ah, 40h
	mov bx, fhandle
	lea dx, str 
	int 21h
	pop cx 
	pop dx
	pop bx
	pop ax
endm write_file

read_buffer_from macro psi 				;psi - what file (0 - handle, 1 - handle_temp)
	push si
	mov si, psi
	call read_buffer
	pop si
endm read_buffer_from 

read_buffer proc 						;si - handle or handle_temp
	push bx
	push cx 
	push ax 
	push dx
	mov dx, offset buffer
	mov cx, buf_len
	mov ah, 3fh

	cmp si, 0
	jne rb_temp_file
	mov bx, handle
	jmp rb_callint

	rb_temp_file:
		mov bx, handle_temp
		jmp rb_callint
	rb_callint:
		int 21h
		mov buffer_len, ax
	pop dx 
	pop ax 
	pop cx 
	pop bx
	ret
read_buffer endp

open_file proc 							;Opens input file
	push ax
	push dx 
	mov ah, 3dh	
	mov al, 2
	mov dx, offset path
	int 21h
	jnc file_good_e
	print_str file_open_error_str
	jmp file_err
	file_good_e:
	mov handle, ax 
	pop dx 
	pop ax
	ret
open_file endp

open_file_temp proc 					;Creates and opens temp file
	push ax
	push dx 
	push cx 
	mov ah, 5ah	
	mov cx, 0
	mov dx, offset path_temp
	int 21h
	jnc file_good_t
	print_str temp_file_error_str
	jmp temp_file_err
	file_good_t:
	mov handle_temp, ax 
	pop cx
	pop dx 
	pop ax
	ret
open_file_temp endp

close_file proc 						;Closes input file
	push ax
	mov bx, handle
	mov ah, 3eh
	int 21h
	jnc cf_end
	print_str file_close_error_str 		;If error occured
	jmp bend
	cf_end:
	pop ax
	ret
close_file endp

close_temp_file proc 					;Closes temp file
	push ax
	mov bx, handle_temp
	mov ah, 3eh
	int 21h
	jnc ctf_end
	print_str temp_file_close_error_str ;If error occured
	jmp bend
	ctf_end:
	pop ax
	ret
close_temp_file endp

delete_temp_file proc 					;Deletes temp file 
	push ax
	mov ah, 41h
	mov dx, offset path_temp
	int 21h
	jnc dtf_end
	print_str temp_file_delete_error_str 	;If error occured
	jmp bend
	dtf_end:
	pop ax
	ret
delete_temp_file endp

write_eof proc 							;Writes eof to input file to cut down excess bytes
	push ax 
	push bx 
	push cx
	mov ah, 40h
	mov bx, handle
	mov cx, 0
	int 21h
	pop cx 
	pop bx 
	pop ax
	ret 
write_eof endp

parse_cmd proc 							;Reads input file path from cmd, and then call proc, that reads substrs
	mov ax, @data
    mov es,ax
    
    xor cx,cx
    
    mov cl, ds:[80h] 
	cmp cl, 7
	ja cmdl_parse_continue
	mov ds, ax
	print_str not_enough_cmdl_len_str 	;If commandline_args str is too short
	print_str cmd_line_example_str
	jmp bend
	cmdl_parse_continue:
	mov di, offset cmd_line
	mov si, 82h  
	rep movsb  							;Read all cmd to cmd_line str

	mov ds, ax  
	mov di, offset cmd_line 
	mov si, offset path
	find_param:
		mov al, ' '
		cmp [di], al 					;Skip spaces before path
		jne before_read_param
		inc di
		jmp find_param 					;When character is not space
	before_read_param:
		inc argc
	read_param:
		cmp [di], byte ptr 0dh 			;Exit if end of cmd
		je params_end
		cmp [di], byte ptr ' ' 			;If space, then read substrs
		je param_readen

		mov al, [di]					;copy another symbol to path str
		mov [si], al
		inc di
		inc si
		jmp read_param

	param_readen:   					;when path readen
		inc di   
	    mov si, offset string 
	    call read_cmdstr
	    inc di 
	    mov si, offset change
	    call read_cmdstr
	    inc di 
	    cmp [di], byte ptr 0dh
	    jne pcmd_too_many_args 
	    jmp params_end

	    pcmd_too_many_args:
		print_str too_many_args_str
		print_str cmd_line_example_str
		jmp bend
	params_error:
	params_end:
	ret
parse_cmd endp

read_cmdstr proc
	rcmdstr_find_param:
		
		cmp [di], byte ptr 0dh 
		jne rcmdstr_continue
		jmp bend
		rcmdstr_continue:
		mov al, ' '
		cmp [di], al
		

		jne rcmdstr_before_read_param
		inc di
		jmp rcmdstr_find_param
	rcmdstr_before_read_param:
		inc argc
		cmp [di], byte ptr '"'
		je rcmdstr_before_read_str
		print_str cmd_line_example_str
		jmp bend 
	rcmdstr_before_read_str:
	    inc di
	rcmdstr_read_str:
		cmp [di], byte ptr 0dh
		je rcmdstr_param_error
		cmp [di], byte ptr '"'
		je rcmdstr_end

		mov al, [di]
		mov [si], al
		inc di
		inc si
		jmp rcmdstr_read_str

	rcmdstr_param_error:
		print_str cmd_line_example_str
		jmp bend
	rcmdstr_end:
	ret
read_cmdstr endp


start:
	
	call parse_cmd
	cmp argc, 3
	je before_strlen
	print_str not_enough_cmdl_len_str
	print_str cmd_line_example_str
	jmp bend
	before_strlen:
	strlen string 
	cmp ax, 0
	jne find_len_continue
	print_str input_error_str
	jmp bend
	find_len_continue:
	mov string_len, ax
	strlen change 
	mov change_len, ax

	call open_file
	call open_file_temp
	next_buffer:
		read_buffer_from 0
		mov cx, buffer_len
		cmp cx, string_len
		jge before_scasb

		write_file handle_temp, buffer
		jmp copy_temp_file

	before_scasb:
		mov di, offset buffer

	continue_scasb:
		mov al, string[0]
		repne scasb
		cmp cx, 0
		jne after_scasb

		mov cx, buffer_len
		write_file handle_temp, buffer
		jmp next_buffer

	after_scasb:	
		inc cx
		mov bx, cx 
		neg bx
		move_fptr 0ffffh, bx, 1, 0
		neg cx
		add cx, buffer_len
		write_file handle_temp, buffer
		read_buffer_from 0

		mov si, offset string
		mov di, offset buffer
		mov cx, string_len
		inc cx
		repe cmpsb
		cmp cx, 0
		je found_str

		mov bx, string_len
		sub bx, cx 
		mov cx, bx
		write_file handle_temp, buffer
		mov bx, buffer_len
		sub bx, cx 
		neg bx
		move_fptr 0ffffh, bx, 1, 0
		jmp next_buffer

	found_str:
		call write_change
		mov bx, buffer_len
		sub bx, string_len
		neg bx
		move_fptr 0ffffh, bx, 1, 0
		jmp next_buffer

	copy_temp_file:
		move_fptr 0, 0, 0, 0
		move_fptr 0, 0, 0, 1
		copy_next_buf:
			read_buffer_from 1

			cmp buffer_len, 0
			call write_eof
			je close_files
			
			mov cx, buffer_len
			write_file handle, buffer
			jmp copy_next_buf

	close_files:
		call close_temp_file
		call delete_temp_file
	temp_file_err:
		call close_file
	file_err:
	bend:
		mov ah, 4ch
		int 21h
end start