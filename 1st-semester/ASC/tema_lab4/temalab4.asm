bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;24.
;Se da dublucuvantul M. Sa se obtina dublucuvantul MNew astfel:
;bitii 0-3 a lui MNew sunt identici cu bitii 5-8 a lui M
;bitii 4-7 a lui MNew au valoarea 1
;bitii 27-31 a lui MNew au valoarea 0
;bitii 8-26 din MNew sunt identici cu bitii 8-26 a lui M.
segment data use32 class=data
    M dd 12348A9Fh
    MNew resd 1 ; rezervam un doubleword pentru rezultat
    ; REZULTATUL FINAL A LUI MNEW AR TREBUI SA FIE:
                        ;
segment code use32 class=code
    start:
    ;bitii 0-3 a lui MNew sunt identici cu bitii 5-8 a lui M
        mov ebx,0
        mov eax,[M]
        and eax,111100000b
        shr eax,5
        or ebx,eax
    ;bitii 4-7 a lui MNew au valoarea 1
        or ebx,11110000b
    ;bitii 27-31 a lui MNew au valoarea 0 :(
    ;in teorie ar fi deja zerorizati de la prima comanda
        and ebx,0000_0111_1111_1111_1111_1111_1111_1111b
    ;bitii 8-26 din MNew sunt identici cu bitii 8-26 a lui M.
        mov eax,[M]
        and eax,0000_0111_1111_1111_1111_1111_0000_0000b ; sau: and EAX,7FFFF00h
        or ebx,eax
        mov [MNew],ebx
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
