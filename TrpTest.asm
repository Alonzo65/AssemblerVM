;name letters 
;
TEST    .INT
TEN     .INT #10
;TRP #2
 ;       TRP #1
  ;      TRP #3
   ;     TRP #4
    ;    TRP #3
     ;   TRP #0
; HAS TO CHECK IF THERE IS ALREADY SOMETHING IN THE BUFFER FOR TRP4 AND USE THAT VALUE NEXT INSTEAD OF ASKING FOR A VALUE
        JMP MAIN
MAIN    LDR R0, TEN
        LDR R1, TEN
        MUL R0, R1
        STR R0, TEST
        LDR R3, TEST
        TRP #1
        MUL R0, R1
        STR R0, TEST
        LDR R3, TEST
        TRP #1
        TRP #0