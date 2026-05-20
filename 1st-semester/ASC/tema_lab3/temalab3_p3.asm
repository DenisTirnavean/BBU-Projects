bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;Interpretare fara semn
;12.(a*b+2)/(a+7-c)+d+x; a,c-byte; b-word; d-doubleword; x-qword
segment data use32 class=data
   a db 12
   b dw 13
   c db 14
   d dd 15
   x dq 16

; our code starts here
segment code use32 class=code
    start:
        mov ah,0
        mov al,[a]
        mul word [b]; DX:AX=a*b
        add ax,2
        adc dx,0; DX:AX=a*b+2
        mov bl,[a]
        add bl,7
        sub bl,[c] ; BL=a+7-c
        mov bh,0 ; BX=a+7-c
        div bx ; AX=DX:AX/BX
               ; AX=(a*b+2)/(a+7-c)
               ;DX=restul immpartirii (a*b+2)/(a+7-c)
        mov bx,dx; salvam restul impartirii in BX
        mov dx,0
        push dx
        push ax
        pop eax; EAX=(a*b+2)/(a+7-c)
        add eax,[d]; EAX=(a*b+2)/(a+7-c)+d
        mov edx,0
        add eax, dword [x]
        adc edx, dword [x+4] ; EDX:EAX=(a*b+2)/(a+7-c)+d+x
                             ; BX=restul impartirii (a*b+2)/(a+7-c)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
