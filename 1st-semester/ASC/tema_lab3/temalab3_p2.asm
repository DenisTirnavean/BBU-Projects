bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;a - byte, b - word, c - double word, d - qword - Interpretare cu semn
;12.(a-b-c)+(d-b-c)-(a-d)
segment data use32 class=data
    a db 12
    b dw 13
    c dd 14
    d dq 15

; our code starts here
segment code use32 class=code
    start:
       
        mov ebx, dword [d]
        mov ecx, dword [d+4]
        mov ax, [b]
        cwd ; DX:AX=b
        push dx
        push ax
        pop eax; EAX=b
        cdq ; EDX:EAX=b
        clc ;clear carry
        sub ebx,eax
        sbb ecx,edx; ECX:EBX=d-b
        mov eax,[c]
        cdq ; EDX:EAX=c
        clc
        sub ebx,eax
        sbb ecx,edx; ECX:EBX=d-b-c
        mov al,[a]
        cbw; AX=a
        sub ax,[b]
        cwd; DX:AX=a-b
        push dx
        push ax
        pop eax
        sub eax,[c];EAX=a-b-c
        cdq ;EDX:EAX=a-b-c
        clc
        add ebx,eax
        adc ecx,edx ; ECX:EBX=(a-b-c)+(d-b-c)
        mov al,[a]
        cbw
        cwd
        push dx
        push ax
        pop eax
        cdq
        clc
        sub eax, dword [d]
        sbb edx, dword [d+4];EDX:EAX=a-d
        clc
        sub ebx,eax
        sbb ecx,edx; EBX:ECX=(a-b-c)+(d-b-c)-(a-d)
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
