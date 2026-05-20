bits 32
global intercal
    
segment code use32 class=code
    intercal:
        ;intercaleaza doua siruri de caractere: caracterele sirului sir1 pe pozitii impare, caracterele sirului sir2 pe pozitii pare
        ;parametrii se transmit pe stiva in urmatoarea ordine: adr_sir_rezultat, adr_sir2, adr_sir1, lungimea sirurilor 
        ;stiva se elibereaza in timpul executiei functiei
        
        ; |------------------------------------------------|
        ; |            adresa de revenire                  |  Esp
        ; |------------------------------------------------|
        ; |           lungimea unui sir                    |  Esp+4
        ; |------------------------------------------------|
        ; |               adresa sir1                      |  Esp+8
        ; |------------------------------------------------|
        ; |               adresa sir2                      |  Esp+12
        ; |------------------------------------------------|
        ; |           rezultatul intercalarii              |  Esp+16
        ; |------------------------------------------------|
        mov ecx,[esp+4] ; lungimea sirurilor sir1 si sir2
        jecxz final
        mov esi,[esp+8] ; sirul 1
        mov edi, [esp+16] ; sirul 2
        mov ebx, [esp+12] ; unde tinem sirul rezultat
        cld
        intercalare:
            movsb ; incarcam in <DS:EDI> caracterul(octetul) de la adresa <ES:ESI>
            xchg esi,ebx ; interschimbam sir1 cu sir2 ca sa putem folosi movbs si pentru al doilea sir
            movsb
            xchg esi,ebx ; refacem interschimbare
            loop intercalare
        mov byte [edi],0;final de sir
        
        ;in varful stivei se afla adresa de revenire, salvam in eax adresa de revenire, eliberam stiva de parametrii apelului
        ;si punem adresa de revenire inapoi in varful stivei
        pop eax
        add esp, 4*5
        push eax
    final:
        ret
