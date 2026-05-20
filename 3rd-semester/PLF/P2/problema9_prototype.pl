%Problema 9
%a) eliminare secvente de elemente consecutive
%
%stergSecv(L:list,Prec: element, R: list), (i,i,o)


stergSecv([],_,[]).
stergSecv([H|T],Prec,R):-
    H is Prec+1,!,
    stergSecv(T,H,R).
stergSecv([H|T],_,[H|R]):-
    sterg(T,R).

%sterg(L:list, R: list), (i,o).
sterg([],[]).
sterg([H],[H]).
sterg([E1,E2|T],[E1|Rez]):-
    E1 =\= E2-1,!,
    sterg([E2|T],Rez).
sterg([H|T],R):-
    stergSecv(T,H,R).
