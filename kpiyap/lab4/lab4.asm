.model small
.stack 256
.data

handle dw 0
pixels equ 2200
words equ 4000
screen db 4000 dup (00)
map db 2200 dup(0)
screen_start dw 0
path db "gf.txt", 0
str_game_over db "GAME OVER"

input db (?)

p_x dw 40
p_y dw 11
p_pos dw (?)
p_direction db 0
p_directions db 'A', 'V', '<', '>'
p_bullet_pos dw (?)
p_bullet_dir db (?)
p_bullet_exist db 0

p_base_blocks dw 0

b_length equ 160
w_length equ 80

c_orange equ 4eh
c_green equ 2h
c_black equ 0
c_player equ 3h
c_p_bullet equ 4
c_p_base equ 74h

s_empty equ 'e'
s_wall equ 61
s_tree equ 176
s_player db 41h
s_p_bullet equ 7
s_p_base equ 157

.code

render proc 
	call redraw_player
	call redraw_p_bullet
	mov cx, words
	mov di, word ptr screen_start
	mov si, offset screen
	cld
	rep movsb
	ret
render endp

check_upTile proc 
	push di
	mov di, p_pos
	sub di, b_length
	cmp screen[di], s_empty
	je check_upTile_end
	stc
	check_upTile_end:
	pop di
	ret
check_upTile endp

check_downTile proc 
	push di
	mov di, p_pos
	add di, b_length
	cmp screen[di], s_empty
	je check_downTile_end
	stc
	check_downTile_end:
	pop di
	ret
check_downTile endp

check_leftTile proc 
	push di
	mov di, p_pos
	sub di, 2
	cmp screen[di], s_empty
	je check_leftTile_end
	stc
	check_leftTile_end:
	pop di
	ret
check_leftTile endp

check_rightTile proc 
	push di
	mov di, p_pos
	add di, 2
	cmp screen[di], s_empty
	je check_rightTile_end
	stc
	check_rightTile_end:
	pop di
	ret
check_rightTile endp

check_bullet_tile proc 
	push di
	push ax
	mov di, bx
	cmp screen[di], s_tree
	jne cbt_notTree

	mov p_bullet_exist, 0
	mov screen[di], s_empty
	mov screen[di+1], c_black
	jmp cbt_end

	cbt_notTree:
	cmp screen[di], s_empty
	jne cbt_notEmpty

	mov p_bullet_exist, 1
	mov p_bullet_pos, di
	jmp cbt_end

	cbt_notEmpty:
	mov p_bullet_exist, 0
	mov di, p_bullet_pos
	mov screen[di], s_empty
	mov screen[di+1], c_black

	cbt_end:
	pop ax
	pop di
	ret
check_bullet_tile endp

check_bullet_spawn_pos proc 
	push bx
	push ax
	push di

	mov bl, p_direction
	mov ax, p_pos
	call get_pos_by_dir

	mov di, ax
	cmp screen[di], s_empty
	jne not_empty_sp

	mov ax, p_pos
	mov p_bullet_pos, ax
	mov bl, p_direction
	mov p_bullet_dir, bl
	mov p_bullet_exist, 1
	jmp check_bullet_sp_end

	not_empty_sp:
	cmp screen[di], s_tree
	jne check_bullet_sp_end

	mov screen[di], s_empty
	mov screen[di+1], c_black
	mov p_bullet_exist, 0
	jmp check_bullet_sp_end
	check_bullet_sp_end:
	pop di
	pop ax
	pop bx
	ret
check_bullet_spawn_pos endp

get_pos_by_dir proc ;bx - direction, ax - position
	cmp bl, 0
	jne dir_not_0
	sub ax, b_length
	jmp get_tile_by_dir_end
	
	dir_not_0:
	cmp bl, 1
	jne dir_not_1
	add ax, b_length
	jmp get_tile_by_dir_end

	dir_not_1:
	cmp bl, 2
	jne dir_not_2
	sub ax, 2
	jmp get_tile_by_dir_end

	dir_not_2:
	cmp bl, 3
	jne get_tile_by_dir_end
	add ax, 2
	jmp get_tile_by_dir_end

	get_tile_by_dir_end:
	ret
get_pos_by_dir endp

update proc 
	push bx
	push ax
	push di
	push cx
	mov ah, 01h
	int 16h
	
	jnz no_input
	jmp update_continue
	no_input:
	call get_key
	
	clc;
	cmp input, 32
	jne not_keySpace
	cmp p_bullet_exist, 1
	jne space_input
	jmp update_continue
	space_input:

	call check_bullet_spawn_pos
	jmp update_continue

	not_keySpace:
	cmp input, 'w'
	jne not_keyW
	mov p_direction, 0
	call check_upTile
	jc update_continue
	dec p_y
	jmp update_continue

	not_keyW:
	cmp input, 's'
	jne not_keyS
	mov p_direction, 1
	call check_downTile
	jc update_continue
	inc p_y
	jmp update_continue

	not_keyS:
	cmp input, 'a'
	jne not_keyA
	mov p_direction, 2
	call check_leftTile
	jc update_continue
	dec p_x
	jmp update_continue

	not_keyA:
	cmp input, 'd'
	jne update_continue
	mov p_direction, 3
	call check_rightTile
	jc update_continue
	inc p_x
	jmp update_continue

	update_continue:
	clc
	call update_player_symbol
	call update_p_bullet
	cmp p_base_blocks, 0
	jnz update_end
	jmp game_over
	update_end:
	pop cx
	pop di
	pop ax
	pop bx
	cmp p_base_blocks, 0
	jne update_ret
	jmp game_over
	update_ret:
	ret
update endp

update_player_symbol proc
	push ax
	push di
	push cx 
	xor cx, cx
	mov di, offset p_directions
	mov cl, p_direction
	update_symbol_loop:
	inc di
	loop update_symbol_loop
	mov ah, [di]
	mov s_player, ah
	pop cx
	pop di
	pop ax
	ret
update_player_symbol endp

update_p_bullet proc 
	push di
	push bx
	push ax

	cmp p_bullet_exist, 1
	jne update_p_b_end

	mov ax, p_bullet_pos
	mov bl, p_bullet_dir
	call get_pos_by_dir
	call erase_p_bullet
	mov p_bullet_pos, ax

	update_p_b_end:
	pop ax
	pop bx
	pop di
	ret
update_p_bullet endp

get_key proc 
	mov ax, 0
	int 16h
	cmp al, 0
	je get_extended
	mov input, al
	jmp get_key_end
	get_extended:
	mov input, ah
	get_key_end:
	ret
get_key endp

redraw_player proc 
	push ax
	push bx
	push di

	mov ax, p_pos
	call calculatePPos
	mov bx, p_pos
	push bx
	push ax
	mov ah, s_empty
	mov al, c_black
	pop di
	mov screen[di], ah
	mov screen[di+1], al
	pop di
	mov ah, s_player
	mov al, c_player
	mov screen[di], ah
	mov screen[di+1], al

	pop di
	pop bx
	pop ax
	ret
redraw_player endp

redraw_p_bullet proc 
	push di
	push bx
	push ax

	cmp p_bullet_exist, 1
	jne redraw_p_b_end

	mov di, p_bullet_pos
	cmp screen[di], s_empty
	jne rpb_not_empty
	mov screen[di], s_p_bullet
	mov screen[di+1], c_p_bullet
	jmp redraw_p_b_end

	rpb_not_empty:
	cmp screen[di], s_tree
	je rpb_erase_tile
	cmp screen[di], s_p_base
	je rpb_destroy_base_block
	jmp rpb_destroy_bullet

	rpb_destroy_base_block:
	dec p_base_blocks
	jmp rpb_erase_tile
	rpb_erase_tile:
	call erase_di_tile
	jmp rpb_destroy_bullet

	rpb_destroy_bullet:
	mov p_bullet_exist, 0
	redraw_p_b_end:
	pop ax
	pop bx
	pop di
	ret
redraw_p_bullet endp 

draw_p_bullet proc 
	push di
	mov di, p_bullet_pos
	mov screen[di], s_p_bullet
	mov screen[di+1], c_p_bullet
	pop di
	ret
draw_p_bullet endp

erase_p_bullet proc
	push di
	mov di, p_bullet_pos
	mov screen[di], s_empty
	mov screen[di+1], c_black
	pop di
	ret
erase_p_bullet endp

erase_di_tile proc
	mov screen[di], s_empty
	mov screen[di+1], c_black
	ret
erase_di_tile endp


read_map proc 
	push dx
	push ax
	push bx
	push cx


	mov ax, 3D00h
	lea dx, path
	int 21h
	jc file_read_err	
                
    mov handle, ax
	mov bx, handle
    mov ah, 3fh   
    lea dx, map
    mov cx, pixels       	
    int 21h

    mov handle, ax

    file_read_end:
	mov ah,3eh
    int 21h

    pop cx
    pop bx
	pop ax
	pop dx
	ret
	file_read_err:
	jmp exit
read_map endp

convert_map proc 
	push cx
	push di
	push si
	push ax
	mov cx, pixels
	xor di, di
	add di, b_length
	add di, b_length
	add di, b_length
	xor si, si
	convert_loop:
		cmp map[si], 31
		ja convert_continue
		inc si
		jmp convert_loop

		convert_continue:
		cmp map[si], 'w'
		jne not_wall
		mov ah, s_wall
		mov al, c_orange
		jmp convert_map_symbol

		not_wall:
		cmp map[si], 't'
		jne not_tree
		mov ah, s_tree
		mov al, c_green
		jmp convert_map_symbol

		not_tree:
		cmp map[si], 'b'
		jne not_p_base
		mov ah, s_p_base
		mov al, c_p_base
		inc p_base_blocks
		jmp convert_map_symbol

		not_p_base:
		convert_loop_inner_end:
		mov ah, 'e'
		mov al, c_black

		convert_map_symbol:
		mov screen[di], ah
		mov screen[di+1], al
		convert_loop_end:
		inc si
		add di, 2
		loop convert_loop
	pop ax
	pop si
	pop di
	pop cx
	ret
convert_map endp

close_file proc 
	mov ah,3eh
    int 21h
	ret
close_file endp

calculatePPos proc 
	push ax
	push bx
	mov ax, p_x
	push ax
	mov ax, p_y
	mov bx, w_length
	mul bx
	pop bx
	add ax, bx
	mov bx, 2
	mul bx
	mov p_pos, ax
	pop bx
	pop ax
	ret
calculatePPos endp

wait_tick proc 	
	push ax
	push cx
	push dx
	push bx
	xor ax, ax
	int 1ah
	mov bx, dx
	wait_tick_loop:
		xor ax, ax
		int 1ah
		cmp dx, bx
	je wait_tick_loop
	pop bx
	pop dx
	pop cx
	pop ax
	ret
wait_tick endp

game_over:
	mov ax, 0003h
	int 10h
	push 0B800h
	pop es
	; mov ah, 02h
	; mov bh, 00h
	; mov dh, 12
	; mov dl, 34
	; int 10h
	game_over_outp:
	mov cx, words
	mov di, offset screen_start
	; black_screen_loop:
	; 	mov [di], s_wall
	; 	mov [di+1], c_green
	; 	add di, 2
	; loop black_screen_loop	
	mov ax, @data
	mov es, ax
	mov bp, offset str_game_over
	mov ah, 13h	
	mov al, 00h
	mov cx, 9
	mov bl, c_green
	mov dh, 11
	mov dl, 34
	int 10h
	wait_loop:
		mov ah, 01h
		int 16h
		jz wait_loop
		call get_key
		cmp input, 'r'
		je start
		cmp input, 'e'
		je exit
	jmp wait_loop
	

start:

	mov ax, @data
	mov ds, ax

	mov p_x, 40
	mov p_y, 19

	mov ax, 0003h
	int 10h
	push 0B800h
	pop es

	call read_map
	call convert_map

	render_loop:
		
		call update
		call render
		call wait_tick

	jmp render_loop


exit:
	mov ah, 4ch
	int 21h
end start