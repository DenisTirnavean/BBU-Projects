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
    ;a,b,c,d-byte ; e,f,g,h-word
    ;(a-c)*3+b*b
    ; exemplu (38-13)*3+78*78=25*3+6084=6159
    a db 38
    b db 78
    c db 13
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov bl,[a] ;BL=a =38
        sub bl,[c] ;BL=BL-c= a-c =38-13=25
        mov al,bl ;AL=BL= a-c =25
        mov ah,3; AH=3
        mul ah ;AX=AL*AH= (a-c)*3 = 25*3=75
        mov bx,ax ;BX=AX= (a-c)*3 =75
        mov al,[b] ;AL=b= 78
        mul byte [b] ;AX=AL*b=b*b = 78*78=6084
        add ax,bx ;AX=AX+BX=b*b+(a-c)*3= (a-c)*3+b*b = 6084+75=6159
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
