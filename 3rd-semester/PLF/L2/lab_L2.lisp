;problema 09
;Sa se converteasca un arbore de tipul (1) la un arbore de tipul (2)


(defun nrChildren (arb)
	(cond
		((null arb) 0)
		((and (null (cadr arb)) (null (caddr arb))) 0)
		((or  (null (cadr arb)) (null (caddr arb))) 1)
		(t 2)
	)
) 

(defun convert(Arb)
	(cond
		((null Arb) nil)
		(t (Append 
				(List (Car Arb) (nrChildren Arb))
				(convert (cadr Arb))
				(convert (caddr Arb))
			)
		)
	)
)

(defun convert2(Arb)
	(cond
		((null Arb) nil)
		((oddp (car arb))
			(Append 
				(List (* 2 (Car Arb)) (nrChildren Arb))
				(convert2 (cadr Arb))
				(convert2 (caddr Arb))
			)
		)
		(t (Append 
				(List (Car Arb) (nrChildren Arb))
				(convert2 (cadr Arb))
				(convert2 (caddr Arb))
			)
		)
	)
)



; (defun nrChildren(Arb)
	; (cond
		; ((null Arb) 0)
		; ((OR (null (Cdr Arb)) (AND (null(cadr Arb)) (null(caddr Arb)))) 0)
		; ((And (listp Arb) (atom (car Arb)) (not(null (cadr Arb))) (null (caddr Arb))) 1)
		; ((And (listp Arb) (atom (car Arb)) (null (cadr Arb)) (not(null (caddr Arb)))) 1)
		; ((And (listp Arb) (atom (car Arb)) (not(null (cadr Arb))) (not(null (caddr Arb))) 2))
	; )
; )
	
; (defun convert (arb)
	; (cond
		; ((null arb) nil)
		; (t (append 
				; (list (car arb) (nrChildren arb))
				; (convert (cadr arb)) 
				; (convert (caddr arb))
			; )
		; )
	; )
; )