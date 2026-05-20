%elimina_impare(L: list, Rez: list) (i,o) determinist
elimina_impare([],[]).
elimina_impare([H|T], Rez):-
    1 is H mod 2,
    elimina_impare(T,Rez).
elimina_impare([H|T], [H| Rez]):-
    0 is H mod 2,
    elimina_impare(T,Rez).


%facem merge sort :(


%split(L: list,L1: list,L2: list) (i,o,o) determinist
split([],[],[]):-!.
split([H],[H],[]):-!.
split([X,Y|T], [X|T1], [Y|T2]):-
    split(T,T1,T2).

%merge(L1: list, L2: list, Rez: list) (i,i,o) determinist
merge([],[],[]):-!.
merge(L,[],L):-!.
merge([],L,L):-!.
merge([H1|T1],[H2|T2],[H1|Rez]):-
    H1=<H2,
    !,
    merge(T1,[H2|T2],Rez).
merge([H1|T1],[H2|T2],[H2|Rez]):-
    H1> H2,
    !,
    merge([H1|T1],T2,Rez).


%merge_sort(L:list, Rez: list) (i,o) determinist
merge_sort([],[]):-!.
merge_sort([H],[H]):-!.
merge_sort(L,Rez):-
    split(L,A,B), %ii bun
    merge_sort(A,RA),
    merge_sort(B,RB),
    merge(RA,RB,Rez). %ii bun


%rezolvare(L:list, Rez:list) (i,o) determinist
rezolvare(L,Rez):-
    elimina_impare(L,R1),
    merge_sort(R1,Rez).
