;name letters 
A   .BYT   'A'
L   .BYT   'L'
O   .BYT   'O'
N   .BYT   'N'
Z   .BYT   'Z'
M   .BYT   'M'
R   .BYT   'R'
Q   .BYT   'Q'
U   .BYT   'U'
E   .BYT   'E'

H   .BYT   'H'
e   .BYT   'e'
l   .BYT   'l'
o   .BYT   'o'
I   .BYT   'I'

c   .BYT   'c'
a   .BYT   'a'
n   .BYT   'n'
p   .BYT   'p'
r   .BYT   'r'
i   .BYT   'i'
n   .BYT   'n'
t   .BYT   't'
G   .BYT   'G'
d   .BYT   'd'
y   .BYT   'y'
b   .BYT   'b'

;substr ', ' if nothing then empty
; IF STRING GREATER THAN ONE DONT THROW ERROR BECAUSE IT MIGHT BE /n
;SPECIAL CHARACTERS MAKE SURE MY ASSEMBLER CAN PICK UP .BYT CHAR ;
SEMICOLON   .BYT  ';'
SPACE     .BYT  ' '
NEWLINE   .BYT  '\n'  ;have to support \n and other special characters 
PLUSOPER  .BYT   '+'
MULTOPER  .BYT   '*'
MINUSOPER .BYT   '-'
DIVOPER   .BYT   '/'
EQUAL     .BYT   '='
ONE     .INT   #1
TWO     .INT   #2
THREE   .INT   #3
FIVE    .INT   #5
        JMP   MAIN
;PRINT HELLO AND NAME
MAIN    LDB   R3, H
        TRP   #3
        LDB   R3, e
        TRP   #3
        LDB   R3, l
        TRP   #3
        TRP   #3
        LDB   R3, o
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, A
        TRP   #3
        LDB   R3, L
        TRP   #3
        LDB   R3, O
        TRP   #3
        LDB   R3, N
        TRP   #3
        LDB   R3, Z
        TRP   #3
        LDB   R3, O
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, M
        TRP   #3
        LDB   R3, A
        TRP   #3
        LDB   R3, R
        TRP   #3
        LDB   R3, Q
        TRP   #3
        LDB   R3, U
        TRP   #3
        LDB   R3, E
        TRP   #3
        LDB   R3, Z
        TRP   #3
        LDB   R3, NEWLINE
        TRP   #3

;ADD ONE AND THREE
        LDR   R1, ONE
        LDR   R2, THREE
        ADD   R1, R2

;PRINT D[] AND RES
        LDR   R3, ONE
        TRP   #1
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, PLUSOPER
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDR   R3, THREE
        TRP   #1
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, EQUAL
        TRP   #3
        MOV   R3, R1
        TRP   #1
        LDB   R3, NEWLINE
        TRP   #3



;MULTIPLY TWO AND THREE
        LDR   R1, TWO
        LDR   R2, THREE
        MUL  R1, R2

;PRINT E[] AND RES
        LDR   R3, TWO
        TRP   #1
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, PLUSOPER
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDR   R3, THREE
        TRP   #1
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, EQUAL
        TRP   #3
        MOV   R3, R1
        TRP   #1
        LDB   R3, NEWLINE
        TRP   #3



;SUBTRACT ONE AND FIVE
        LDR   R1, ONE
        LDR   R2, FIVE
        SUB  R1, R2

;PRINT F[] AND RES
        LDR   R3, ONE
        TRP   #1
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, MINUSOPER
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDR   R3, FIVE
        TRP   #1
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, EQUAL
        TRP   #3
        MOV   R3, R1
        TRP   #1
        LDB   R3, NEWLINE
        TRP   #3

;DIVIDE FIVE BY TWO
        LDR   R1, FIVE
        LDR   R2, TWO
        DIV  R1, R2

;PRINT G[] AND RES
        LDR   R3, FIVE
        TRP   #1
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, PLUSOPER
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDR   R3, TWO
        TRP   #1
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, EQUAL
        TRP   #3
        MOV   R3, R1
        TRP   #1
        LDB   R3, NEWLINE
        TRP   #3

;PRINT C[]
        LDB   R3, I
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, c
        TRP   #3
        LDB   R3, a
        TRP   #3
        LDB   R3, n
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, p
        TRP   #3
        LDB   R3, r
        TRP   #3
        LDB   R3, i
        TRP   #3
        LDB   R3, n
        TRP   #3
        LDB   R3, t
        TRP   #3
        LDB   R3, SPACE
        TRP   #3
        LDB   R3, SEMICOLON
        TRP   #3
        LDB   R3, NEWLINE
        TRP   #3

;PRINT H[]
        LDB   R3, G
        TRP   #3
        LDB   R3, o
        TRP   #3
        TRP   #3
        LDB   R3, d
        TRP   #3
        LDB   R3, b
        TRP   #3
        LDB   R3, y
        TRP   #3
        LDB   R3, e
        TRP   #3
        LDB   R3, NEWLINE
        TRP   #3

;EXIT PROGRAM
        TRP   #0
