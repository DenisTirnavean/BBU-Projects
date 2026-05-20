;lab L3, prob 9

;functii map, sa fac substituierea unui element cu elementele din alta lista


(defun subs(l el oth)
	(cond
		((and (atom l) (equal l el)) oth)
		((atom l) l)
		(t (mapcar 
				#'(lambda(x)
						(subs x el oth)
				)
			l
			)
		)
	)
)


; lst - lista neliniara
; e - elementul de substituit
; l - lista prin care substituim elementul e
(defun substituie (lst e l)
  (apply #'append
         (mapcar
			#'(lambda (x)
					(cond
							((and (atom x) (equal x e)) l)
							((atom x) (list x))
							(t (list (substituie x e l)))
					)
				)
          lst
		 )
	)
)
