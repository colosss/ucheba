(defun minus_nums(nums)
    (if (null nums)
        0
        (-1 (car nums)) (minus_nums (cdr nums))
    )
)


(defun remove_at (list n)
    (if (null list)
        nil)
    (if (= n 0) (cdr list)
        (cons (car list) (remove_at (cdr list) (- n 1))))
    )

(defun remove_by_in(list nums)
    (if(null nums)
        list
        (remove_by_in
        (remove_at list (car nums)) (cdr nums))
        
    )