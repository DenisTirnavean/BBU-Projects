%a) Sa se scrie un predicat care intoarce intersectia a doua multimi


%apare(E: integer - ce caut, L: list - unde caut) (i,i)
%folosim apare pentru a determina daca un element apare intr-o lista
apare(E, [E|_]):-!.
apare(E, [_|T]):- apare(E, T).

%intersectie(L: list - prima multime,
%            M: list - a doua multime,
%            R: list - unde se afla solutia)
%(i,i,o) deterministic

intersectie([], _, []).
intersectie([H|T], L2, [H|R]) :-apare(H, L2),!,intersectie(T, L2, R).
%taietura ca sa oprim backtracking din a lua-o pe ulei
intersectie([_|T], L2, R) :-intersectie(T, L2, R).

%cazuri de testare:
%intersectie([1,2,3,4],[1,2,3,4],[1,2,3,4]).
%intersectie([1,2,3],[2,3,4,5],[2,3]).
%intersectie([1,2,3,4,5],[2,3],[2,3]).
%intersectie([],[1,2,3],[]).
%intersectie([1,2,3,4],[],[]).
%intersectie([],[],[]).
%intersectie([1,2,3],[4,5,6],[]).



% b) Sa se construiasca lista formata din elementele (m,...,n), adica
%multimea formata din numerele intregi din intervalul [m,n]
% interval(M:integer - capatul stang al intervalului,
%          N:integer - capatul drept al intervalului,
%          L:list  - unde se returneaza solutia)
% (i,i,o) deterministic
interval(N,N,[N]):-!.
%interval(M,N,[]):-M>N,!.
interval(M,N,[M|Rest]):-
    M<N,
    M1 is M+1,
    interval(M1,N,Rest).


%cazuri de testare
%interval(1,5,[1,2,3,4,5]).
%interval(1,1,[1]).
%interval(2,1,[]).
%interval(-2,2,[-2,-1,0,1,2]).
