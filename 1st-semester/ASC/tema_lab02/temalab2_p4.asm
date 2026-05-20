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
    ;Inmultiri impartiri ex4
    ;a,b,c- byte d- word
    ; -a*a+2*(b-1)-d
    ;exemplu -12*12+2*(18-1)-270=-144+14-270=-380
    a db 12
    b db 18
    d dw 270
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,[a] ; AL=a = 12
        mul byte [a] ;AX=AL*a= a*a = 12*12=144
        neg ax ;AX=0-AX=-AX=-a*a = -144
        mov bx,ax ;BX=AX=-a*a = -144
        mov al,[b] ;AL=b = 18
        sub al,1 ; AL=AL-1=b-1 = 18-1=17
        mov ah,2 ;AH=2
        mul ah; AX=AH*AL= 2*(b-1) = 2*17=34
        sub ax,[d] ;AX=AX-d=2*(b-1)-d = 34-270=-236
        add bx,ax ;BX=BX+AX= -a*a+2*(b-1)-d = -144 + -236 = -380
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
