.model small
.stack 256
.data
     string DB 200, 200 dup ('$')  
     input_invitation DB "Input string for sort", 10,13,"$" 
     result_string DB 10,13,"Sorted string:", 10, 13, "$"   
	len DB '?'

.code   
JMP start  
    
	print_str MACRO out_str
		MOV AH, 09h
		MOV DX, OFFSET out_str
		INT 21h
	ENDM
	
	shift PROC
		PUSH SI
		PUSH DI
		PUSH CX
		MOV CL, len
		
		MOV SI, 2
		CLD        
		LEA DI, string+2
		MOV AL, 20h
		REPE SCASB 
		DEC DI
		MOV CL, len
		SUB CX, DI  
		add cx, 2
		LEA SI, string+DI
		LEA DI, string+2
		REP MOVSB
		POP CX
		POP DI
		POP SI
		ret
	shift ENDP
	
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
     
start:
     MOV AX, @data
     MOV DS, AX 
     MOV ES, AX     
         
	print_str input_invitation
	
     MOV AH, 0ah
     LEA DX,string
     INT 21h  
                         
     LEA SI,string   
     MOV DI, OFFSET string+2
	 XOR CX, CX
     MOV CL, string+1
	 INC CL
	 MOV len, CL
	 mov di, cx
	 add di, 2
	 mov [string+di], '$'
     PUSH CX
words_cycle_preparations:            
     POP CX               ;renewing cx = len(string)
     PUSH CX      
     LEA SI,string+2  
     MOV DI, OFFSET string+2
     MOV AL, ' '
     XOR BX,BX
     PUSH SI
words_cycle:   
     MOV SI, DI
     REPNE SCASB 
     DEC DI              ;move position from space to words border
     PUSH DI 
     SUB DI, SI          ;counting current word len
     MOV DX, DI
         
     POP DI                         
     CMP DX, BX          ;compare len of previous word and current                      
         
     JL short swap_condition   ;if previous word bigger then current
     MOV BX, SI          ;saving len of current word
     POP SI
     MOV SI, BX
     MOV BX, DX
     PUSH SI             ;saving left border of current word     
     INC DI   
     JCXZ short complete       ;when cx == 0 -> jump to end
     INC CX              ;loop will decrement cx, but cx also decremets by repne
LOOP words_cycle

swap_condition:          ;swap short and long words, that are right next to each other
     DEC DI              ;change position from space to symbol
     CALL reverse        ;reverse of right words
     SUB SI, 2           ;move position from left border of right word
                         ;to right border of left word(jump over space)
     MOV AX, SI
     POP SI              ;pop left border of left word(pushed in words loop)
     PUSH DI             
     MOV DI, AX
     CALL reverse        ;reverse of left words
     POP DI
     CALL reverse        ;reverse of both words
     JMP short words_cycle_preparations

complete:   
	CALL shift
    print_str result_string
    print_str string+2
     MOV AH, 4ch
     INT 21h

     END start