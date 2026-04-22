(defun plus_1(num names_list)
    (cond
        ((null names_list) num)
        (t (plus_1 (+ num 1) (cdr names_list)))
    )
)

(defun find_r(list)
    (cond
        ((null list) nil)
        (t (cons
            (list(caar list)
                (plus_1 0 (caddr(car list)))
                (caddr(car list)))
            (find_r (cdr list)))
        )
    )
)
(defun find_min(list min)
    (cond
        ((null list) min)
        ((< (cadar list) min)
            (find_min (cdr list) (cadar list))
        )
        (t (find_min (cdr list) min))
    )
)

(defun r(list)
    (cond
        ((null list) nil)
        (t (find_min (find_r list) (cadar (find_r list))))
    )
)

(setq graph_1 '((a 0 (b))
                (b 0 (a c d))
                (c 0 (b d))
                (d 0 (b c))))

; Треугольник - каждый узел связан с двумя другими, минимум = 2
(setq graph_2 '((a 0 (b c))
                (b 0 (a c))
                (c 0 (a b))))

; Звезда -  центр связан со всеми, листья только с центром, минимум = 1
(setq graph_3 '((a 0 (b c d e))
                (b 0 (a))
              (c 0 (a))
                (d 0 (a))
                (e 0 (a))))

; Цепочка - крайние узлы имеют степень 1, минимум = 1
(setq graph_4 '((a 0 (b))
                (b 0 (a c))
                (c 0 (b d))
                (d 0 (c e))
                (e 0 (d))))

; Полный граф K4 - каждый связан с каждым, минимум = 3
(setq graph_5 '((a 0 (b c d))
                (b 0 (a c d))
                (c 0 (a b d))
                (d 0 (a b c))))

(print (r graph_1))
(print (r graph_2))
(print (r graph_3))
(print (r graph_4))
(print (r graph_5))
