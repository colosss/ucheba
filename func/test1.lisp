(defun contains (n nums)
    (if (null nums)
        nil
        (if (= n (car nums))
            t
            (contains n (cdr nums))
        )
    )
)

(defun minus_nums (n)
    (if (null n)
        nil
        (cons (- (car n) 1) (minus_nums (cdr n)))
    )
)

(defun remove_by_in (list n)
    (if (null list)
        nil
        (if (contains 1 n)
            (remove_by_in (cdr list) (minus_nums n))
            (cons (car list) (remove_by_in (cdr list) (minus_nums n)))
        )
    )
)