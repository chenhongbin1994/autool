#pragma debug scope 1 1
#line 11 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
__acsr EQU [023H]
__adcr EQU [022H]
__adrh EQU [021H]
__adrl EQU [020H]
__pwm0 EQU [01fH]
__intc1 EQU [01eH]
__scomc EQU [01cH]
__ctrl1 EQU [01bH]
__ctrl0 EQU [01aH]
__pcpu EQU [019H]
__pcc EQU [018H]
__pc EQU [017H]
__pbpu EQU [016H]
__pbc EQU [015H]
__pb EQU [014H]
__pawk EQU [013H]
__papu EQU [012H]
__pac EQU [011H]
__pa EQU [010H]
__tmr1c EQU [0fH]
__tmr1 EQU [0eH]
__tmr0c EQU [0dH]
__tmr0 EQU [0cH]
__intc0 EQU [0bH]
__status EQU [0aH]
__wdts EQU [09H]
__tblh EQU [08H]
__tblp EQU [07H]
__pcl EQU [06H]
__acc EQU [05H]
__mp1 EQU [03H]
__mp0 EQU [01H]
__iar1 EQU [02H]
__iar0 EQU [00H]
@SendBit_1621 .SECTION 'CODE'
PUBLIC _SendBit_1621
_SendBit_1621 PROC
#pragma debug scope 2 1
#line 10 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC SendBit_16210
LOCAL SendBit_16210 DB ? ; data
#pragma debug variable 8 2 SendBit_16210 data
#line 10 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC SendBit_16211
LOCAL SendBit_16211 DB ? ; cnt
#pragma debug variable 8 2 SendBit_16211 cnt
#pragma debug scope 2 1 ; 13 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 13 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR CR1
#line 13 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
JMP L5
L2:
#pragma debug scope 3 2 ; 15 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 15 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SZ SendBit_16210.7
JMP L6
#line 15 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [017H].3
#line 15 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
JMP L7
L6:
#line 16 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SET [017H].3
L7:
#line 17 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [017H].5
#line 18 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
NOP
#line 19 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
NOP
#line 20 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SET [017H].5
#line 21 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [0AH].0
RLC SendBit_16210
L3:
#line 13 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#pragma debug scope 2 1 ; 13 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
INC CR1
L5:
#line 13 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,CR1
SUB A,SendBit_16211
SNZ [0ah].0
JMP L2
L1:
RET
#line 12 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
LOCAL CR1 DB ? ; i
#pragma debug variable 8 2 CR1 i
_SendBit_1621 ENDP
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
@SendDataBit_1621 .SECTION 'CODE'
PUBLIC _SendDataBit_1621
_SendDataBit_1621 PROC
#pragma debug scope 4 1
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC SendDataBit_16210
LOCAL SendDataBit_16210 DB ? ; data
#pragma debug variable 8 4 SendDataBit_16210 data
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC SendDataBit_16211
LOCAL SendDataBit_16211 DB ? ; cnt
#pragma debug variable 8 4 SendDataBit_16211 cnt
#pragma debug scope 4 1 ; 28 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 28 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR CR2
#line 28 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
JMP L12
L9:
#pragma debug scope 5 4 ; 30 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 30 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SZ SendDataBit_16210.0
JMP L13
#line 30 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [017H].3
#line 30 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
JMP L14
L13:
#line 31 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SET [017H].3
L14:
#line 32 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [017H].5
#line 33 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
NOP
#line 34 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
NOP
#line 35 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SET [017H].5
#line 36 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [0AH].0
RRC SendDataBit_16210
L10:
#line 28 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#pragma debug scope 4 1 ; 28 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
INC CR2
L12:
#line 28 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,CR2
SUB A,SendDataBit_16211
SNZ [0ah].0
JMP L9
L8:
RET
#line 27 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
LOCAL CR2 DB ? ; i
#pragma debug variable 8 4 CR2 i
_SendDataBit_1621 ENDP
#line 41 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
@SendCmd .SECTION 'CODE'
PUBLIC _SendCmd
_SendCmd PROC
#pragma debug scope 6 1
#line 40 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC SendCmd0
LOCAL SendCmd0 DB ? ; command
#pragma debug variable 8 6 SendCmd0 command
#pragma debug scope 6 1 ; 42 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 42 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [017H].4
#line 43 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,080h
MOV SendBit_16210,A
MOV A,04h
MOV SendBit_16211,A
CALL _SendBit_1621
#line 44 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,SendCmd0
MOV SendBit_16210,A
MOV A,08h
MOV SendBit_16211,A
CALL _SendBit_1621
#line 45 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SET [017H].4
L15:
RET
_SendCmd ENDP
#line 49 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
@Write_1621 .SECTION 'CODE'
PUBLIC _Write_1621
_Write_1621 PROC
#pragma debug scope 7 1
#line 48 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC Write_16210
LOCAL Write_16210 DB ? ; addr
#pragma debug variable 8 7 Write_16210 addr
#line 48 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC Write_16211
LOCAL Write_16211 DB ? ; data
#pragma debug variable 8 7 Write_16211 data
#pragma debug scope 7 1 ; 50 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 50 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [0AH].0
RLC Write_16210
CLR [0AH].0
RLC Write_16210
#line 52 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [017H].4
#line 53 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,0a0h
MOV SendBit_16210,A
MOV A,03h
MOV SendBit_16211,A
CALL _SendBit_1621
#line 54 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,Write_16210
MOV SendBit_16210,A
MOV A,06h
MOV SendBit_16211,A
CALL _SendBit_1621
#line 55 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,Write_16211
MOV SendDataBit_16210,A
MOV A,04h
MOV SendDataBit_16211,A
CALL _SendDataBit_1621
#line 56 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SET [017H].4
L16:
RET
_Write_1621 ENDP
#line 60 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
@WriteAll_1621 .SECTION 'CODE'
PUBLIC _WriteAll_1621
_WriteAll_1621 PROC
#pragma debug scope 8 1
#line 59 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC WriteAll_16210
LOCAL WriteAll_16210 DB ? ; addr
#pragma debug variable 8 8 WriteAll_16210 addr
#line 59 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC WriteAll_16211
LOCAL WriteAll_16211 DB ? ; p
#pragma debug variable 19 8 WriteAll_16211 p
#line 59 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
PUBLIC WriteAll_16212
LOCAL WriteAll_16212 DB ? ; cnt
#pragma debug variable 8 8 WriteAll_16212 cnt
#pragma debug scope 8 1 ; 62 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 62 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [0AH].0
RLC WriteAll_16210
CLR [0AH].0
RLC WriteAll_16210
#line 64 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR [017H].4
#line 65 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,0a0h
MOV SendBit_16210,A
MOV A,03h
MOV SendBit_16211,A
CALL _SendBit_1621
#line 66 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,WriteAll_16210
MOV SendBit_16210,A
MOV A,06h
MOV SendBit_16211,A
CALL _SendBit_1621
#line 67 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR CR3
#line 67 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
JMP L21
L18:
#pragma debug scope 9 8 ; 69 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 69 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,WriteAll_16211
MOV [01H],A
MOV A,[00H]
MOV b0_5,A
MOV A,b0_5
MOV SendDataBit_16210,A
MOV A,08h
MOV SendDataBit_16211,A
CALL _SendDataBit_1621
L19:
#line 67 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#pragma debug scope 8 1 ; 67 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
INC CR3
INC WriteAll_16211
L21:
#line 67 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,CR3
SUB A,WriteAll_16212
SNZ [0ah].0
JMP L18
#line 71 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
SET [017H].4
L17:
RET
LOCAL b0_5 DB ?
#line 61 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
LOCAL CR3 DB ? ; i
#pragma debug variable 8 8 CR3 i
_WriteAll_1621 ENDP
#line 75 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
@init_1621 .SECTION 'CODE'
PUBLIC _init_1621
_init_1621 PROC
#pragma debug scope 10 1 ; 78 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 78 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,052h
MOV SendCmd0,A
CALL _SendCmd
#line 79 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,02h
MOV SendCmd0,A
CALL _SendCmd
#line 80 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,06h
MOV SendCmd0,A
CALL _SendCmd
#line 82 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR CR4
#line 82 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
JMP L26
L23:
#pragma debug scope 11 10 ; 84 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 84 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,CR4
MOV Write_16210,A
MOV A,00h
MOV Write_16211,A
CALL _Write_1621
L24:
#line 82 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#pragma debug scope 10 1 ; 82 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
INC CR4
L26:
#line 82 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,CR4
SUB A,020h
SNZ [0ah].0
JMP L23
L22:
RET
#line 76 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
LOCAL CR4 DB ? ; seg
#pragma debug variable 8 10 CR4 seg
_init_1621 ENDP
#line 89 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
@clr_1621 .SECTION 'CODE'
PUBLIC _clr_1621
_clr_1621 PROC
#pragma debug scope 12 1 ; 91 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 91 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
CLR CR5
#line 91 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
JMP L31
L28:
#pragma debug scope 13 12 ; 93 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#line 93 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,CR5
MOV Write_16210,A
MOV A,055h
MOV Write_16211,A
CALL _Write_1621
L29:
#line 91 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
#pragma debug scope 12 1 ; 91 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
INC CR5
L31:
#line 91 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
MOV A,CR5
SUB A,020h
SNZ [0ah].0
JMP L28
L27:
RET
#line 90 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\ht1621.c"
LOCAL CR5 DB ? ; seg
#pragma debug variable 8 12 CR5 seg
_clr_1621 ENDP
