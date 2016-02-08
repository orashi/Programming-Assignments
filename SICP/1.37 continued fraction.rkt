#lang planet neil/sicp
(define (cont-frac1 n d k)
  (let((en (n k))
       (de (d k)))
    (if (> k 1)(/ en
                  (+ de
                     (cont-frac1 n d (- k 1))))
        (/ en
           de))))
    
(define (cont-frac2 n d k)
  (let((en (n k))
       (de (d k)))
    (define (iter k result)
      (if (> k 0)(iter(- k 1)
                      (/ en
                         (+ de
                            result)))
          result))
    (iter (- k 1) (/ en de))))



(cont-frac1 (lambda(i) 1.0)
           (lambda(i) 1.0)
           11)

(cont-frac2 (lambda(i) 1.0)
           (lambda(i) 1.0)
           11)
           