
;arbore in reprezentare 1 :) si asteptam arbore v2



;returneaza calea de la radacina la un nod mentionat, sau nil daca nu exista nodul n in arbore
; arb - arbore binar reprezentat sub forma (rad (list_subarb_st) (list_subarb_dr))
; n - nodul la care vrem sa-i afisam calea
; col - lista colectoare care va contine calea de la radacina arb la n
(defun cale_aux(arb n col)
	(cond
		((null arb)nil)
		((equal (car arb) n) (append col (list( car arb))))
		(t (append (cale_aux (cadr arb) n (append col (list (car arb)))) (cale_aux (caddr arb) n (append col (list (car arb))))))
	)
)


;returneaza calea de la radacina arb la nodul n, sau nil daca nu exista nodul n in arbore
; arb - arbore binar reprezentat sub forma (rad (list_subarb_st) (list_subarb_dr))
; n - nodul cautat
(defun cale(arb n)
	(cale_aux arb n '())
)

