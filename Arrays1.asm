;test asm file for my newly implmented opcodes
;calculating mod: first divide the number then use that answer and times it by what you divided the number by, from there take that result
;and subtract it from the number that was divided-> the result from that should be the remainder(i.e. what was left over Mod)
SIZE	.INT	#10
ARR		.INT 	#10
		.INT 	#2
		.INT 	#3
		.INT 	#4
		.INT 	#15
		.INT 	#-6
		.INT 	#7
		.INT 	#8
		.INT 	#9
		.INT 	#10
i 		.INT 	#0
sum		.INT 	#0
temp	.INT
result	.INT
ONE		.INT 	#1
TWO 	.INT 	#2
I 		.BYT 	'i'
s 		.BYT 	's'
SPACE 	.BYT 	' '
e 		.BYT 	'e'
v 		.BYT 	'v'
n 		.BYT 	'n'
S 		.BYT 	'S'
u 		.BYT 	'u'
m 		.BYT 	'm'
o 		.BYT 	'o'
d 		.BYT 	'd'
ENDLINE 	.BYT 	'\n'
;.BYT LETTERS TO PRINT
	JMP MAIN
MAIN	LDR R0, i
		MOV R1, R0	
 		LDR R2, SIZE
		LDA R10, ARR
		LDR R4, sum
		LDR R5, result
WHILE 	CMP R1, R2	;MAKE SURE TO ADD TO I AND ARR THEN MOV IT BACK TO R1 
		BRZ R1, END
		LDR R6, R10
		ADD R4, R6
		MOV R7, R6
		LDR R8, TWO
		DIV R7, R8
		MUL R8, R7
		MOV R7, R6
		SUB R7, R8
		MOV R5, R7
IF		BNZ R5, ELSE
		MOV R3, R6
		TRP #1
		LDB   R3, SPACE
        TRP   #3
		LDB   R3, I
        TRP   #3
		LDB   R3, s
        TRP   #3
		LDB   R3, SPACE
        TRP   #3
		LDB   R3, e
        TRP   #3
		LDB   R3, v
        TRP   #3
		LDB   R3, e
        TRP   #3
		LDB   R3, n
        TRP   #3
		LDB   R3, ENDLINE
        TRP   #3
		JMP INCREMENT
ELSE			MOV R3, R6
		TRP #1
		LDB   R3, SPACE
        TRP   #3
		LDB   R3, I
        TRP   #3
		LDB   R3, s
        TRP   #3
		LDB   R3, SPACE
        TRP   #3
		LDB   R3, o
        TRP   #3
		LDB   R3, d
        TRP   #3
        TRP   #3
		LDB   R3, ENDLINE
        TRP   #3
INCREMENT	ADI R0, #1
		ADI R10, #4
		MOV R1, R0
		JMP WHILE
END		LDB   R3, S
        TRP   #3
		LDB   R3, u
        TRP   #3
		LDB   R3, m
        TRP   #3
		LDB   R3, SPACE
        TRP   #3
		LDB   R3, I
        TRP   #3
		LDB   R3, s
        TRP   #3
		LDB   R3, SPACE
        TRP   #3
		MOV   R3, R4
        TRP   #1
		LDB   R3, ENDLINE
        TRP   #3
		TRP   #0
