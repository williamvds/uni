B main

array	DEFW	4, 2, 47, 23, 18, 10, 22, 6, 37, 28


message	DEFB	"Sorted list is \0"
msg4	DEFB	"\n\0"
ALIGN

main	MOV R13, #0x100000

LDR R0, array     ; R0 <- origin of array
MOV R1, #10       ; R1 <- 10 = #elements
BL insertionSort
; output message

ADR R0, message
SWI 3
MOV R3,#10
ADR R5, array
print	LDR R0, [R5], #4
SWI 4
MOV R0, #','
SWI 0
SUBS R3,R3,#1
BNE print

ADR r0, msg4
SWI 3

SWI 2

; insertionSort -- Sort array of integers
; Input: R0 <- Array of integers
;        R1 <- Number of elements

insertionSort
  STMFD R13!, { R4, R5, R6, R7, R14 } ; push things
  MOV R4,#0   ; R4 = Index being compared?
  B oLoopCond

oLoop
  MOV R5,R4 ; R5 = copy of index
  B iLoopCond

  iLoop
    STR R6, [R0, R5 LSL #4]
    STR R7, [R0, R3 LSL #4]

  iLoopCond
    CMP R5,#0
    BLEQ endILoop  ; If first element skip
    SUB R3,R5,#1 ; R3 should be R5?
    ; array[j-1] -> R6
    LDR R6, [R0, R3 LSL #2]
    LDR R7, [R0, R5 LSL #2]
    CMP R6, R7
    BGT iLoop

  endILoop
    ADD R4, R4, #1

oLoopCond
  CMP R4, R1  ; Check if index == #elements
  ; BUG
  ; LEQ should be used because index starts at 0, so R1 is index +1
  BLEQ	oLoop ; Possibly should be BLE because index starts at 0?
  LDMFD R13!, { R5, R6, R7,  PC }
