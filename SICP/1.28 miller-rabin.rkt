#lang planet neil/sicp
(define (square x)
  (* x x))
(define (expmod base exp m)
  (define (judge x)
  (if(and (not (= x 1))
       (not (= x (- m 1)))
       (= (remainder (square x) m) 1))
     0
     x))
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square(judge (expmod base (/ exp 2) m))) m))
        (else
         (remainder (* base (expmod base (- exp 1) m))
                    m))))
(define (fixed-fermat-test n)
  (define(try-it a)(= (expmod a (- n 1) n) 1))
  (try-it (+ 1(random(- n 1)))))
(define(miller-rabin x times)
  (cond((= times 0)true)
       ((fixed-fermat-test x)(miller-rabin x (- times 1)))
       (else false)))

(miller-rabin 997 50)
(miller-rabin 1105 50)

