.model tiny
.code 
org 100h 

start:     

mov dx, offset str1
mov ah, 09h
int 21h        

mov dx, offset str2  
int 21h       

mov dx, offset str3      
int 21h  
    
ret
str1 db 13,"Hello world!$"
str2 db 10,13,"Hello ASM$"
str3 db 10,13,"Lab1$"  
end start





