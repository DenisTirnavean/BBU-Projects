%Dandu-se o valoare N, sa se genereze permutarile de N elemente cu
% proprietatea ca oricare ar fi 2<=i<=n exista un 1<=j<=i astfel incat
% |v(i)-v(j)|=1


% strategie cu candidat si conditie


%candidat(N:integer, E: integer)
%(i,o) nedeterminist
candidat(N,N).
candidat(N,I):-
    N>1,
    N1 is N-1,
    candidat(N1,I).

%apare(E:element, L:list)
%(i,i)
apare(H,[H|_]).
apare(E,[_|T]):-
    apare(E,T).

%conditie(E:element, L:list)
%(i,i)
conditie(E,[H|_]):-
    H =:= E+1,!.
conditie(E,[H|_]):-
    H =:= E-1,!.
conditie(E,[_|T]):-
    conditie(E,T).

%adauga_final(E:element, L:list, LRez: list)
%(i,i,o) determinist%
adauga_final(E,[],[E]).
adauga_final(E,[H|T],[H|Rez]):-
    adauga_final(E,T,Rez).

%permutari(N:integer, L:list)
%(i,o) nedeterminist
permutari(N,L):-
    candidat(N,I),
    permutari_aux(N,L,1,[I]).

permutari_list(N,L):-
    findall(Rez,permutari(N,Rez),L).

%permutari_aux(N:integer, L:List, Lg: integer, Col:list)
%(i,o,i,i) nedeterminist
permutari_aux(N,Col,N,Col).
permutari_aux(N,L,Lg,[H|T]):-
     Lg < N,
     candidat(N,I),
     conditie(I,[H|T]),
     \+apare(I,[H|T]),
     Lg1 is Lg+1,
     adauga_final(I,[H|T],Rez),
     permutari_aux(N,L,Lg1,Rez).


%cazuri de testare:
% 1.caz N=0  permutari_list(0,L). => L=[]

% 2. caz N=1 permutari_list(1,L). =>L=[[1]] (lista tuturor permutarilor
% lui 1, luate ca lista, o permutare posibila, lista in lista


%3. caz normal N=3 permutari_list(3,L) =>
%L = [[3,2,1],[2,3,1],[2,1,3],[1,2,3]]


% 4. caz numere negative N=-3. permutari_list(-3,L) => L=[]

