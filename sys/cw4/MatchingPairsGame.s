  B main

seed    DEFW    0x1234567
dMul    DEFW 65539
sGap    DEFB "  ", 0
sNewl   DEFB "\n", 0
  ALIGN
board	  DEFW 	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
  ALIGN
sBoardPrompt DEFW "Enter square to reveal: ", 0


main
  MOV R13, #0x100000     ; Setup stack (see Lecture 21)
  ADR R0, board
  BL printMaskedBoard
  ; Your main game loop should go here

  SWI 2

; cls -- Clears the Screen
; Input : None
; Ouptut: None
cls
  MOV R0, #10
  MOV R1, #100

_clsLoop
  SWI 3
  SUBS R1, R1, #1
  BNE _clsLoop

  MOV PC,R14

; boardSquareInput -- read the square to reveael from the Keyboard
; Input:  R0 <- address of prompt for user
; Output: R0 <- Array index of entered square
boardSquareInput


  MOV PC,R14

; generateBoard
; Input R0 -- array to generate board in
generateBoard
  MOV R6, #0

generateBoardWhile
  PUSH {R14}
  BL randu

  MOV R3, #4
  MOV R0, R0 ASR #8
  AND R1, R0, #0xf

  MUL R1, R1, R3
  LDR R3, [R5, R1]
  CMP R3, #0xFFFFFFFF
  BNE generateBoardWhile

  MOV R0, R6 ASR #1
  STR R0, [R5, R1]

  ADD R6, R6, #1
  CMP R6, #16
  BNE generateBoardWhile

  POP {PC}

; randu -- Generates a random number
; Input: None
; Ouptut: R0 -> Random number
randu
  LDR R1, dMul	    ; Get 65539 in R1
  LDR R2, seed     ; If no starting seed in seed

  MUL R0, R1, R2
  AND R0, R0, #0x7FFFFFFF
  MOV R2, R0
  STR R2, seed
  MOV PC, R14

; printMaskedBoard -- print the board with only the squares in R1 and R2 visible
; Input: R0 <-- Address of board
;        R1 <-- Number of Cell to reveal
;        R2 <-- Number of Cell to reveal
printMaskedBoard
  MOV R3, R0      ; R3 = copy of input
  MOV R4, #48      ; R13 = column counter / offset from origin of array

printMaskedBoardColumns  ; Print first line of board
  ADR R0, sGap
  SWI 3
  CMP R4, #48    ; Print space if first item
  MOVEQ R0, #32
  MOVNE R0, R4
  SWI 0
  ADR R0, sGap
  SWI 3
  ADD R4, R4, #1

  CMP R4, #52    ; Jump back and print
  BLE printMaskedBoardColumns

  MOVS R4, #0    ; Reset loop counter before next loop

printMaskedBoardRowStart  ; Print row label
  ADRL R0, sNewl
  SWI 3
  SWI 3
  MOV R0, #65
  ADD R0, R0, R4 ASR #4
  SWI 0
  ADRL R0, sGap
  SWI 3
  SWI 3

printMaskedBoardRowInner  ; Print row elements
  SWI 3

  MOV R0, #4
  MUL R0, R1, R0  ; Multiply each hidden index to compare with offset
  CMP R4, R0

  MOVNE R0, #4
  MULNE R0, R2, R0
  CMPNE R4, R0

  MOV NE R0, #'*'     ; Print asterisk no match
  SWINE 0
  BNE printMaskedBoardIf

  LDR R0, [R3, R4] ; Otherwise load index

  CMP R0, #-1      ; Compare with -1

  ADDNE R0, R0, #65
  SWINE 0

  MOVEQ R0, #' '
  SWIEQ 0

printMaskedBoardIf
  ADRL R0, sGap
  SWI 3

  ADD R4, R4, #4

  CMP R4, #64
  MOVEQ PC, R14

  TST R4, #15
  BNE printMaskedBoardRowInner
  BEQ printMaskedBoardRowStart  ; Print next row
