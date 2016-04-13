SECTION .data
	msg	db "Hi World",10 
	len	equ $-msg
SECTION .text
	global _start
_start:
		mov edx,len 
		mov ecx,msg 
		mov ebx,1 
		mov eax,4    ;sys write
		int 0x80     ;interrupt used to invoke system call
		mov ebx,0    
		mov eax,1    ;sys exit
		int 0x80
