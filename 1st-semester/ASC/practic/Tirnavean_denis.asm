bits 32
global start        

extern exit,fopen,fclose,printf,fread, scanf ,fscanf
import exit msvcrt.dll 
import fopen msvcrt.dll 
import fclose msvcrt.dll 
import printf msvcrt.dll 
import fread msvcrt.dll 
import scanf msvcrt.dll 
import fscanf msvcrt.dll 
   
segment data use32 class=data
    nume_fisier times 51    db 0
    mod_acces db 'r',0
    format_citire db '%s',0
    format_afisare db 'Numar consoane in baza 16: %x',0
    descriptor dd 0
    mesajul db 'nu s-a reusit deschiderea fisierului'
    buffer dd 0
    count dd 100
    sir_curent times 101 db 0
segment code use32 class=code
    start:
        ;citire nume fisier
        push dword nume_fisier
        push dword format_citire
        call [scanf]
        add esp,4*2
        ;deschidere fisier
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        mov [descriptor],eax
        cmp eax,0
        je mesaj
        
        push dword [descriptor]
        call [fclose]
        add esp,4
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        xor ebx,ebx
        citire:
            push dword sir_curent
            push dword format_citire
            push dword [descriptor]
            call [fscanf]
            add esp,4*3
            cmp eax,0
            jng afara
            
            mov esi,sir_curent
            numara:
                lodsb; in al caracterul curent
                ;vf ca este litera
                cmp al,0
                je afara_numara
                cmp al,'A'
                jb e_vocala
                cmp al,'z'
                ja e_vocala
                cmp al,'a'
                jb verific_interval
                jmp dupa
                verific_interval
                    cmp al,'Z'
                    ja e_vocala
                dupa:
                ;verifica daca e vocala, in caz ca este nu inc ebx
                cmp al,'a'
                je e_vocala
                cmp al,'A'
                je e_vocala
                cmp al,'e'
                je e_vocala
                cmp al,'E'
                je e_vocala
                cmp al,'i'
                je e_vocala
                cmp al,'I'
                je e_vocala
                cmp al,'o'
                je e_vocala
                cmp al,'O'
                je e_vocala
                cmp al,'U'
                je e_vocala
                cmp al,'u'
                je e_vocala
                
                
                inc ebx
                e_vocala:
                jmp numara
            afara_numara:
            jmp citire
        afara:
        
        push ebx
        push dword format_afisare
        call [printf]
        add esp,4*2
        
        jmp peste
        mesaj:
        push dword mesajul
        call [printf]
        add esp,4
        peste:
        push    dword 0     
        call    [exit]   
