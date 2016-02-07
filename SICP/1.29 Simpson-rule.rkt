#lang planet neil/sicp
(define (sum term a next b)
  (define(iter a result)
    (if (> a b)
        result
        (iter (next a)(+ result (term a)))))
  (iter a 0))
(define (Simpson-rule f a b n)
  (define h (/(- b a)
              n))
  (define (yn k)(f(+ a
                   (* k h))))
  (define (next a)
    (+ a 2))
  (* (/ h 3)
     (+ (yn 0)
        (* 4 (yn 1))
        (yn n)
        (sum (lambda(x)(+(* 2 (yn x))
                         (* 4 (yn (+ 1 x)))))
             2
             next
             (- n 2)))))
(Simpson-rule (lambda(x)(* x x x)) 0 1 100.0)
(Simpson-rule (lambda(x)(* x x x)) 0 1 1000.0)
             

             
