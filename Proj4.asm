FIVE	.INT #5



		JMP MAIN
MAIN	MOV R4, FP
		LDR R1, FIVE
		MOV FP, SP
		ADI SP, #-4
		STR R4, SP ; SAVE PFP
		ADI SP, #-4
		STR R1, SP
		MOV R1, PC
		ADI R1, #36
		STR R1, FP
		JMP ADDTWO
		LDR R3, SP
		TRP #1
		TRP #0


;void flush() function
flush	MOV R4, FP

;place functions below our jump main otherwise we run into errors(fix them later)
;function that can be used as reference 
ADDTWO	MOV R4, FP
		ADI R4, #-8
		LDR R1, R4
		ADI R1, #2
		MOV SP, FP
		ADI R4, #4
		LDR R0, R4
		MOV FP, R0
		MOV R4, SP
		LDR R5, R4
		STR R1, SP
		JMR R5