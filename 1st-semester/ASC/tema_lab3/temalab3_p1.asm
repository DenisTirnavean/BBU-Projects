bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

                          
;a - byte, b - word, c - double word, d - qword - Interpretare fara semn
;12.(a+b+d)-(a-c+d)+(b-c)
segment data use32 class=data
    ; ...
    a db 12
    b dw 257
    c dd 25
    d dq 18
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov eax,0 ;pregatim eax pentru adunarea cu d
        mov al,[a]
        add ax,[b]; AX=a+b
        mov edx,0; EDX:EAX= a+b
        clc
        add eax, dword [d]
        adc edx, dword [d+4]; EDX:EAX=a+b+d
        mov ebx,0
        mov bx,[b]; EBX=b
        sub ebx,[c] ; EBX=b-c
        add eax,ebx ; EDX:EAX=(a+b+d)+(b-c)
        mov ebx,0
        mov bl,[a]; EBX=a
        sub ebx,[c]; EBX=a-c
        mov ecx,0; ECX:EBX=a-c
        clc
        add ebx, dword [d]
        adc ecx, dword [d+4]; ECX:EBX=(a-c+d)
        clc
        sub eax,ebx
        sbb edx,ecx ; EDX:EAX= (a+b+d)+(b-c)-(a-c+d)=(a+b+d)-(a-c+d)+(b-c)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
