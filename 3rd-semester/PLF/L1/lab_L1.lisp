;Laborator P1
; Cerinta 4
;a) Definiti o functie care intoarce suma a doi vectori. 


(defun sum_vect(v1 v2)
	(cond
		((null v1) v2)
		((null v2) v1)
		(t(cons (+(car v1)(car v2)) (sum_vect (cdr v1)(cdr v2))))
	)
)
;-------------------------------------------------------------------------------
;b)Definiti o functie care obtine dintr-o lista data lista tuturor atomilor 
;care apar, pe orice nivel, dar in aceeasi ordine. De exemplu: 
;(((A B) C) (D E)) --> (A B C D E) 


(defun multime_atom(l)
	(cond
		((null l) nil)
		((atom (car l)) (cons (car l) (multime_atom (cdr l)))) 
		((listp (car l)) (append (multime_atom (car l)) (multime_atom (cdr l))))
	)
)
;---------------------------------------------------------------------------------
;c)Sa se scrie o functie care plecand de la o lista data ca argument, 
;inverseaza numai secventele continue de atomi. Exemplu: 
;(a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g)) 

(defun take_atoms (l)
  (cond
    ((null l) nil)
    ((atom (car l)) (cons (car l) (take_atoms (cdr l))))
    (t nil)
  )
)

(defun drop_atoms (l)
  (cond
    ((null l) nil)
    ((atom (car l)) (drop_atoms (cdr l)))
    (t l)
  )
)

(defun rev_seq (l)
  (cond
    ((null l) nil)
    (t (append (rev_seq (cdr l)) (list (car l))))
  )
)

(defun proc_atoms (seq rest)
  (append (rev_seq seq) (inverseaza rest))
)

(defun inverseaza (l)
  (cond
    ((null l) nil)

    ((atom (car l))
      (proc_atoms (take_atoms l) (drop_atoms l))
	)
    (t (cons (inverseaza (car l))
             (inverseaza (cdr l))))
  )
)


;-----------------------------------------------------------------------------------
;d)Sa se construiasca o functie care intoarce maximul atomilor numerici 
;dintr-o lista, de la nivelul superficial. 

;gaseste primul element numeric la nivel superficial
(defun find_first_num(l)
	(cond
		((null l)nil)
		((numberp (car l)) (car l))
		(t(find_first_num (cdr l)))
	)
) 


(defun maxim_superficial(l maxi)
	(cond
		((null l) maxi)
		((and (numberp (car l))(> (car l) maxi))
			(maxim_superficial (cdr l) (car l))
		)
		(t(maxim_superficial (cdr l) maxi))
	)
)


(defun maxi_main(l)
	(maxim_superficial l (find_first_num l))
)
