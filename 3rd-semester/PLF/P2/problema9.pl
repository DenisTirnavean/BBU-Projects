%Problema 9
%a) eliminare secvente de elemente consecutive
%
%elimSecv(L:list, F: bool, R: list), (i,i,o)
elimSecv([],_,[]).
elimSecv([H],0,[H]).
elimSecv([_],1,[]).
elimSecv([H1,H2|T],0,[H1|R]):-
    H2 =\= H1+1,
    elimSecv([H2|T],0,R).
elimSecv([H1,H2|T],_,R):-
    H2 =:=H1+1,
    elimSecv([H2|T],1,R).
elimSecv([H1,H2|T],1,R):-
    H2 =\= H1+1,
    elimSecv([H2|T],0,R).

%elimSecvMain(L: list, R: list), (i,o) determinist
elimSecvMain(L,R):-elimSecv(L,0,R),!.

%cazuri de testare:
%elimSecvMain([1,2,3,5,55,55,56,3,2,1,1,2,2,2,12,13],L).
%L=[5,55,3,2,1,2,2]
%elimSecvMain([1,3,5,7,9,11],L).
%L=[1,3,5,7,9,11]
%elimSecvMain([1,2,3,4,5,6,7,8,9,10],L).
%L=[]
%elimSecvMain([],L).
%L=[]








%b) liste eterogene, stergerea din subliste a secventelor consecutive
%
%elimEterogen(L:list,R: list) (i,o) determinist
elim([],[]).
elim([H|T],[HR|TR]):-
    is_list(H),
    !,
    elimSecvMain(H,HR),
    elim(T,TR).
elim([H|T],[H|R]):-
    elim(T,R).


%cazuri de testare:
%elim([1,[2,3,5],9,[1,2,4,3,4,5,7,9],11,[5,8,2],7],L).
%L=[1,[5],9,[4,7,9],11,[5,8,2],7]
%elim([1,4,7,9,122],L).
%L=[1,4,7,9,122]
%elim([[1,3],[4,6],[7,9],[11,13]],L).
%L=[[1,3],[4,6],[7,9],[11,13]]
%elim([[1,2,3],[3,4,5],[8,9,10]],L).
%L=[[],[],[]]
%elim([[1,2,4],[2,3,5,7,8],[1,2,3,4,9]],L).
%L=[[4],[5],[4]]
%elim([[],1,2,332,[1,2,3,22],[3,5,7],[1,2,3,66,89],[],1000],L).
%L=[[],1,2,332,[22],[3,5,7],[66,89],[],1000]
