bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;8.Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate literele mari din sirul S
;exemplu: S: 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
;         D: 'A', 'B', 'M'
segment data use32 class=data
    S db 'aAbB2%JxM'
    len equ $-S
    D times len db 0

; our code starts here
segment code use32 class=code
    start:
        mov ecx,len
        mov esi,0
        mov edi,0
        jecxz sfarsit
    repeta:
        mov al,[S+esi]
        cmp al,'A' ;comaparam codul ascii al elementului din sir cu codul  ascii a lui 'A'
        jb nu_este_litera_mare ; daca cod_ascii[al]<'A' nu este litera mare
        cmp al,'Z' ; stim ca ascii[al]>='A', trebuie sa verificam ca acest caracter are codul ascii mai mic egal 'Z'
        ja nu_este_litera_mare ; daca cod_ascii[al]>'Z' nu este litera mare
        ;pe linia asta ajungem daca avem o litera mare
        mov [D+edi],al
        inc edi
        ;nu avem nevoie de un salt peste eticheta de nu_este_litera_mare pt ca oricum incrementam esi o data/loop ca este sau nu caracterul litera mare
    nu_este_litera_mare: ; daca nu e litera mare trecem direct la next element
        inc ESI
        loop repeta
    sfarsit:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
