bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    ;Adunari si scaderi ex4
    ;a,b,c,d word
    ;(b+b)-c-(a+d)
    ; exemplu (100+100) - 270 - (10+11) = 200-270-21=-91
    a dw 10
    b dw 100
    c dw 270
    d dw 11
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax,[b] ;AX=b= 100
        add ax,[b] ;AX=AX+b=b+b = 200
        mov bx,[a] ;BX=a = 10
        add bx,[d] ;BX=BX+d=a+d =21
        sub ax,[c] ;AX=AX-c=(b+b)-c = -70
        sub ax,bx ;AX=AX-BX=(b+b)-c+(a+d) = -70-21=-91
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
