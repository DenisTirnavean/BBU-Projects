
bits 32

global _intercal

segment data public data use32

segment code public code use32
_intercal:;intercal(sir,sir2,sir_intercalat)
	push ebp
	mov ebp, esp
	mov esi,0
	mov edi,0
	mov eax, [ebp+8]
	mov ebx, [ebp+12]
	mov edx, [ebp+16]
	intercal_modular:
		mov cl, [eax+esi] ;incarcam in cl caracterul curent din sirul din eax(sir1)
		cmp cl, 0 ; verificam daca am ajuns la finalul sirului
		je final
		mov [edx+edi], cl ;punem in sirul destinatie caracterul din cl(pozitie impara/index par)
		inc edi
		mov cl, [ebx+esi] ;incarcam in cl caracterul curent din sirul din ebx(sir2)
		mov [edx+edi],cl; punem in sirul destinatie caracterul din cl(pozitie para/index impar)
		inc edi
		inc esi
		jmp intercal_modular
	final:
		mov byte [edx+edi],0 ;punem finalul de sir
		mov esp,ebp
		pop ebp
		ret 