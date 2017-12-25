    B main

gap   DEFB "  ", 0
board	DEFW 	3, 1, 4, 7, 5, 1, 7, 6, 6, 0, 2, 5, 0, 4, 2, 3
    ALIGN

main
    ADR R0, board
    BL printBoard
    SWI 2

; printBoard -- print the board
; Input: R0 <-- Address of board
printBoard
    MOV R1, R0    ; R1 = copy of input
    MOV R0, #" "
    ADR R0, gap
    SWI 3
    MOVS R2, #0

colLabels
    ADD
    ADDS R2, R2, #1
    SWI 4

colLabelsCond
    BLT colLabels
    ; Insert your implementation here


        MOV PC,R14
