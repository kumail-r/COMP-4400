; by Kumail Raza
; 105225432


; lst is used to define the input web link graph
(define lst '((a b c) (b c d) (c b a) (d)))
; (define lst '((a b) (b c) (c b)))

; get all unique values in seperate list
(define (uniquely list)
  (let looking ((rslt '()) (list list))
    (if (null? list)
        rslt
        (let ((next (car list))
              (rest (cdr list)))
          (if (list? next)
              (looking rslt (append next rest))
              (looking (if (memq next rslt)
                           rslt
                           (cons next rslt))
                       rest))))))

; remove duplicates
(define (dedupe e)(if (null? e) '()(cons (car e) (dedupe (filter (lambda (x) (not (equal? x (car e)))) (cdr e))))))

; check if list contains value x
(define (contains list x)
	(cond [(null? list) #f]
		[(equal? (car list) x) #t]
		[else (contains (cdr list) x)]))

; "elements" contains all the letters used (with no duplicates)
(define elements (dedupe (uniquely lst)))
; (display elements)


; get go through sublist and find if it has a match
(define (get-sublist listy element)
    (if (not (null? listy))
        (begin
            (get-sublist (cdr listy) element)
            (if (contains (cdr (car listy)) element)
                (begin
                    (display (car (car listy)))
                    (display " ")
                )
                (display "")
            )
        )
        (display "")
    )
)

; go through each unique character to create its list
(define (iterate-uniques uniques)
    (if (not (null? uniques))
        (begin
            (display "[ ")
            (display (car uniques))
            (display " ")
            (get-sublist lst (car uniques))
            (display "], ")
            (iterate-uniques (cdr uniques))
        )
        (display "")
    )
)

; begin calling functions!
(iterate-uniques elements)


