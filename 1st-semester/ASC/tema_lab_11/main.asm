
;Problema 12
;Se dau doua siruri de caractere de lungimi egale. Se cere sa se calculeze si sa se afiseze rezultatele intercalarii ;literelor, pentru cele doua intercalari posibile (literele din primul sir pe pozitii pare, respectiv literele din primul sir 
;pe pozitii impare)

bits 32 
global start        
extern exit, printf,intercal
import exit msvcrt.dll   
import printf msvcrt.dll   
segment data use32 class=data
    sir1 db "00000000"
    len equ $-sir1
    sir2 db "xxxxxxxx"
    len_final equ len*2
    sir3 times len_final db 0
    sir4 times len_final db 0
    new_line db 10,13,0
segment code use32 class=code
    start:
        xor eax,eax
        mov eax,len
        ;intercal(lungime_sir, sir2, sir1, sir_rezultat)
        ;prima intercalare
        push dword sir3
        push dword sir1
        push dword sir2
        push eax
        call intercal;stiva se elibereaza in cadrul functiei
        ;afisare rezultat
        push dword sir3
        call [printf]
        add esp,4
        push dword new_line
        call [printf]
        add esp,4
        
        xor eax,eax
        mov eax,len
        ;intercal(lungime, sir1,sir2, sir_rezultat)
        ;a doua intercalare
        push dword sir3
        push dword sir2
        push dword sir1
        push eax
        call intercal;stiva se elibereaza in cadrul functiei
        ;afisare rezultat
        push dword sir3
        call [printf]
        add esp,4
        push dword new_line
        call [printf]
        add esp,4
        push    dword 0    
        call    [exit]  
