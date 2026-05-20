bits 32 
global start        
extern exit             
import exit msvcrt.dll    

;   4.Se da un sir de octeti s. Sa se construiasca sirul de octeti d, care contine pe fiecare pozitie numarul de biti 1 ai octetului de pe pozitia corespunzatoare din s.
;exemplu:

;       s:  5,   25,   55,   127
;in binary: 101, 11001,10111,1111111

;rezultat:     
;       d: 2, 3, 5, 7
segment data use32 class=data
        s db 5,25,55,127
        ls equ $-s
        d times ls db 0

segment code use32 class=code
    start:
        ; ...
        mov ecx,ls
        jecxz final
        mov esi,s
        mov edi,d
        cld
    repeta:
        lodsb ; AL=<DS:ESI> deci element din s, plus incrementeaza esi
        push ecx ; punem continutul lui ecx pe stiva pentru a salva contorul pentru ciclarea repeta
        mov ecx,8
        mov ah,0 ;AH este unde numaram bitii 1 din AL
        loop_interior:
            test al,1
            je nu_e_unu; ZF=0 deci AL and 1 da rezultatul 0=>ultimul bit din AL nu e 1
            add ah,1
            nu_e_unu:
            shr al,1; Shift la dreapta cu o pozitie=>trecem la urmatorul bit
            loop loop_interior
        mov al,ah
        pop ecx ; recuperam valoarea lui ecx de pe stiva
        stosb ; <DS:EDI>=AL plus incrementeaza edi
        loop repeta
    final:
        push    dword 0 
        call    [exit]     
