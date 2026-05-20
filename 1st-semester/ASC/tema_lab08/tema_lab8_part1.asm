bits 32 
global start        

extern exit, printf            
import exit msvcrt.dll
import printf msvcrt.dll 
;LAB 8, Apeluri de fucntii sistem 
;ex4
;Se dau doua numere naturale a si b (a, b: word, definite in segmentul de date). Sa se calculeze produsul lor si sa se afiseze in urmatorul format: "<a> * <b> = <result>"
;Exemplu: "2 * 4 = 8"
;Valorile vor fi afisate in format decimal (baza 10) cu semn.
segment data use32 class=data
    a dw -2
    b dw 4
    format db '%d * %d = %d',0

segment code use32 class=code
    start:
        mov ax,[a]
        mov bx,[b]
        imul bx ; dx:ax=a*b
        push dx
        push ax
        pop eax ; eax=a*b
        ;printf('%d * %d = %d', a,b,rezultat)
        push eax ; punem rezultatul pe stiva
        mov ax,[b]
        cwde
        push eax; punem pe stiva word-ul b sub forma de dword
        mov ax,[a]
        cwde
        push eax;punem pe stiva word-ul a sub forma de dword
        push dword format
        call [printf]
        add esp,4*4
        push dword 0
        call [exit]