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

    ;Adunari scaderi, ex4
    ;a,b,c,d byte
    ;(a-b)+(c-b-d)+d
    ;exemple pentru testare: a=10, b=5, c=24, d= 50 => (10-5)+(24-5-50)+50=5-31+50=24
    ;a=25 b=18 c=60 d=50 => (25-18)+(60-18-50)+50= 7-8+50=49
    ;a=255 b=255 c=255 d=255 => (255-255) + (255-255-255) +255= -255+255=0
    a db 10
    b db 5
    c db 24
    d db 50
; our code starts here
segment code use32 class=code
    start:
       
        mov al,[a] ;AL=a= 10
        sub al,[b] ;AL= AL-b= a-b = 10-5=5
        mov bl,[c] ;BL=c = 24
        sub bl,[b] ;BL= BL-b= c-b = 24-5= 19
        sub bl,[d] ;BL= BL-d= c-b-d = 19-50= -31
        add al,bl ; AL=AL+BL = (a-b)+(c-b-d) = 5+ -31=-26
        add al,[d] ; AL=AL+d= (a-b)+(c-b-d)+d = -26+50=24
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
