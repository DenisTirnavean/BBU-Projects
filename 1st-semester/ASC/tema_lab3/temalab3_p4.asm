bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;Interpretare cu semn
;12.(a*b+2)/(a+7-c)+d+x; a,c-byte; b-word; d-doubleword; x-qword
segment data use32 class=data
   a db 12
   b dw 13
   c db 15
   d dd 14
   x dq 16

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,[a]
        cbw; AX=a
        imul word [b]; DX:AX=AX*b= a*b
        clc
        add ax,2
        adc dx,0; DX:AX=a*b+2
        mov cx,ax ;eliberam temporar registrul ax pentru a putea converti un byte->word
        mov al,[a]
        add al,7
        sub al,[c];AL=a+7-c
        cbw ; AX=a+7-c
        mov bx,ax ;BX=a+7-c
        mov ax,cx ; DX:AX=a*b+2
        idiv bx ;AX=DX:AX/BX= [(a*b+2)/(a+7-c)], DX=(restul)(a*b+2)/(a+7-c)
        mov cx,dx;salvam restul impartirii in CX
        cwd  ;DX:AX=(a*b+2)/(a+7-c)
        push dx
        push ax
        pop eax ; EAX=(a*b+2)/(a+7-c)
        add eax,[d]; EAX=(a*b+2)/(a+7-c)+d
        cdq; EDX:EAX=(a*b+2)/(a+7-c)+d
        clc
        add eax, dword [x]
        adc edx, dword [x+4]; EDX:EAX=(a*b+2)/(a+7-c)+d+x, restul impartirii salvat in CX
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
