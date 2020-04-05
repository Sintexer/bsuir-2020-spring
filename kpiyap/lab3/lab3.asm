.model small
.stack 256
.data     
        
length dw ?  
l_bound dw ?
r_bound dw ?
size equ 30 
arr dw 30 dup(?)
 
temp db 7, 7 dup ('$')                         
sSizeInvite db "Input number amount", 10, 13, '$'
sNumInvite db "Input number (word size)", 10, 13, '$'  
sLBoundInvite db "Input left bound", 10, 13, '$'
sRBoundInvite db "Input right bound", 10, 13, '$'                                    

sRBoundErr db "Right bound must be bigger or equal to left bound", 10, 13, '$'
sErr db "Error input", 10, 13, '$'  
sNumber db "Number ", '$' 
sDash db " - $"
sTime db " time$"      
sSchar db "s$"
sDelim db 10,13,'$'

.code  


reverse PROC        ;si - begin, di - end of substring
          PUSH SI
          PUSH DI
          PUSH AX
          PUSH BX

          CLD    
          cycle:
               MOV AL, [SI]   ;swapping symbols
               MOV BL, [DI]
               MOV [SI], BL
               MOV [DI], AL 

               DEC DI    ;moving borders towards each other
               INC SI
               CMP SI, DI 
          JL cycle       ;if borders met -> ret  

          POP BX
          POP AX
          POP DI
          POP SI
          RET
     reverse ENDP          

make_str_from_integer proc 
    push di 
    push dx
    push cx     
    push si   
    push ax
    mov si, offset temp 
    mov cx, 10      
    cmp ax, 0     
    jge make_str_loop 
    neg ax
    make_str_loop:
    xor dx, dx
    div cx
    xchg ax, dx
    add al, '0'
    mov [si], al
    xchg ax, dx      
    inc si
    or ax, ax
    jne make_str_loop
    dec si  
    pop ax
    cmp ax, 0      
    jge end_makestr 
    clc
    inc si
    mov [si], '-'
    end_makestr:        
    push si
    pop di            
    
    mov si, offset temp
    call reverse
    inc di
    mov [di], '$'
    pop si
    pop cx
    pop dx  
    pop di
    ret      
endp      
  

print_integer macro integer
    push ax
    mov ax, integer    
    call make_str_from_integer
    print_str temp
    pop ax
endm

print_str MACRO out_str   
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

print_symbol MACRO out_symbol
    push ax
    push dx
    mov dx, out_symbol
    mov ah, 02h
    int 21h
    pop dx
    pop ax
endM
     
get_num MACRO num
    push ax  
    push dx 
    push cx  
    push si 
    push di
    lea dx, temp
    mov ah, 0ah
    int 21h      
    print_str sDelim
    mov si, offset temp+2  
    xor cx, cx
    mov cl, [temp+1]
    call convert   
    mov num, ax 
    pop di 
    pop si
    pop cx     
    pop dx
    pop ax
ENDM             

convert PROC 
    push bx    
    push si      
    jcxz error
    xor ax, ax 
    mov bx, 10
	xor dx, dx
	mov dl, [si]
    cmp dl, '-'
    jne conv_loop
    inc si
    dec cx
    conv_loop:
    mul bx 
    mov bx, ax  
    xor ax, ax
    cmp dx, 0
    jnz error
    mov al, [si]
    cmp al, '0'
    jb error
    cmp al, '9'
    ja error
    sub al, '0'
    add ax, bx
    mov bx, 10
    cmp ax, 8000h
    ja error
    inc si
    loop conv_loop
    pop si
    push si
	xor dx, dx
	mov dx, [si]
    cmp dl, '-'
    jne check_overflow
    neg ax
    jmp clear_cf
    check_overflow:
    or ax, ax
    js error 
    clear_cf:
    clc
    jmp conv_end  
    error:
    stc  
    MOV AH, 09h
		MOV DX, OFFSET sErr
		INT 21h
    
    conv_end:
    pop si
    pop bx    
ret   
convert ENDP

start:
mov ax, @data
mov ds, ax     
                   
size_input:     
print_str sSizeInvite 
get_num length          
jc size_input 

cmp length, 1  
jb error_size_input 
push ax
mov ax, size
cmp length, ax
pop ax
ja error_size_input
jmp array_input
error_size_input:
print_str sErr
jmp size_input

array_input:  
mov cx, length    
push cx
mov di, offset arr
array_input_loop: 
clc       
print_str sNumInvite  
get_num length
jc array_input_loop  
push ax
mov ax, length
mov [di],ax
pop ax
add di, 2
loop array_input_loop 
                      
l_bound_input:     
print_str sLBoundInvite 
get_num l_bound          
jc l_bound_input 
  
push ax
mov ax, l_bound          
jmp r_bound_input
r_bound_print_error:
print_str sRBoundErr
r_bound_input:     
print_str sRBoundInvite 
get_num r_bound          
jc r_bound_input
cmp r_bound, ax
jl r_bound_print_error               
pop ax     
             
pop cx
mov length, cx
mov ax, l_bound 
array_loop_preparations:      
mov di, offset arr 
mov cx, length 
xor bx, bx
array_loop:
cmp ax, [di]
jne continue_array_loop
inc bx
continue_array_loop:
add di, 2
loop array_loop   
print_str sNumber
print_integer ax
print_str sDash        
print_integer bx
print_str sTime
cmp bx, 1   
je continue_print
print_str sSchar
continue_print:  
print_str sDelim
inc ax
cmp ax, r_bound
jg  ender
jmp array_loop_preparations
ender: 

mov ah, 4ch
int 21h
end start