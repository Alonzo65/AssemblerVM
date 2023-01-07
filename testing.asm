
DAGS	.BYT	'D'
		.BYT 	'A'
		.BYT 	'G'
		.BYT 	'S'
GADS		.BYT 	'G'
		.BYT 	'A'
		.BYT 	'D'
		.BYT 	'S'
i 			.INT    #356
SIZE		.INT 	#4
rel			.BYT 
HYPHEN 		.BYT 	'-'
EQUALS 		.BYT 	'='
SPACE 		.BYT 	' '
GREATERTHAN 	.BYT 	'>'
LESSTHAN 		.BYT 	'<'
ENDLINE 		.BYT 	'\n'

;.BYT LETTERS TO PRINT
		JMP MAIN
MAIN	LDR R3, i
		TRP #1
		TRP #3
		ADI R3, #-3
		BRZ R3, END
		TRP #3
		TRP #4
		TRP #3
END		TRP #0