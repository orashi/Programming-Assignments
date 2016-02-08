#lang planet neil/sicp
(define (repeat f n)
  (define (iter x n)
    (if (> n 0)(f (iter x (- n 1)))
        x))
  (lambda(x) (iter x n)))

(define (smooth f)
  (define dx 0.001)
  (lambda(x) (/ (+ (f (- x dx))
                   (f x)
                   (f (+ x dx)))
                3)))
(define result
  (repeat (smooth (f)) n))
    
