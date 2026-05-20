bits 32 
global start        


extern exit,printf,fopen,fscanf,fclose, fprintf       
import printf msvcrt.dll   
import exit msvcrt.dll   
import fopen msvcrt.dll   
import fscanf msvcrt.dll   
import fclose msvcrt.dll   
import fprintf msvcrt.dll   
;LAB 8, Operatii cu fisiere text
;ex27.
;Se da un fisier text. Fisierul contine numere (in baza 10) separate prin spatii. Sa se citeasca continutul acestui fisier, sa se determine minimul numerelor citite si sa se scrie rezultatul la sfarsitul fisierului
segment data use32 class=data
    nume_fisier db 'alin.txt',0
    mod_acces db 'a+',0
    descriptor dd 0
    formatc db '%d',0
    formatm db ' %d',0
    message db "nu s-a deschis fisierul",0
    n dd 0
segment code use32 class=code
    start:
        ;fopen(file_name,mode)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        mov [descriptor],EAX ;vf daca s-a deschis fisierul
        cmp eax,0
        je mesaj
        mov ebx,0FFFFFFFh; punem o valoare mare in ebx urmand sa tinem in ebx minimul curent
        
    repeta:
        ;fscanf(descriptor,formatc,&n)
        push dword n
        push dword formatc
        push dword [descriptor]
        call [fscanf]
        add esp,4*3
        cmp eax,0
        jnge gata
        cmp ebx,[n]
        jle nu_minim ; jump if below or equal deci vf daca minimul curent din ebx <= numarul curent [d]
        ;daca nu s-a sarit atunci in [d] avem un numar mai mic decat minimul si il stocam in ebx
        mov ebx,[n]
    nu_minim:
        jmp repeta
        ;fprint(descriptor,format,valoare)
    gata:
    ;aici am terminat citirea numerelor din fisier si punem la final minimul obtinut
        push ebx
        push dword formatm
        push dword [descriptor]
        call [fprintf]
        add esp,4*3
    ;inchiderea fisierului
        push dword [descriptor]
        call [fclose]
        jmp peste
    mesaj:
        push dword message
        call [printf]
        add esp,4
    peste:
        push    dword 0      
        call    [exit]       
