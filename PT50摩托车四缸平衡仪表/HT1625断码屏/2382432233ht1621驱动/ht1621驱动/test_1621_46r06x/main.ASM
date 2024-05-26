#pragma debug scope 1 1
#line 10 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
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
@sys_init .SECTION 'CODE'
PUBLIC _sys_init
_sys_init PROC
#pragma debug scope 2 1 ; 11 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 11 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pac
#line 12 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pa
#line 14 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pcc
#line 15 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pc
#line 18 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,087h
MOV __tmr0c,A
#line 19 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,063h
MOV __tmr0,A
#line 21 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET [0BH].2
#line 22 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET [0BH].0
#line 23 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET [0DH].4
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,07h
MOV __wdts,A
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR WDT
L1:
RET
_sys_init ENDP
#line 32 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
@MAIN .SECTION 'CODE'
_main PROC
begin:
#pragma debug scope 3 1 ; 33 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 33 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CALL _sys_init
#line 35 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CALL _init_1621
#line 35 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
JMP L4
L3:
#pragma debug scope 4 3 ; 39 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 39 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR WDT
#line 42 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SNZ _flg_100ms
JMP L6
#pragma debug scope 5 4 ; 44 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 44 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR _flg_100ms
#line 46 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CALL _clr_1621
L6:
L4:
#line 37 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#pragma debug scope 3 1 ; 37 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
JMP L3
L2:
#line 51 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
JMP $
_main ENDP
#line 56 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
@@tm0_isr .SECTION AT 08H 'CODE'
JMP _tm0_isr
@tm0_isr .SECTION 'CODE'
_tm0_isr PROC
MOV V2A,A
MOV A,[0AH]
MOV V2S,A
#pragma debug scope 6 1 ; 58 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 58 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
INCA _tmr_cnt1
MOV b0_3,A
MOV A,b0_3
MOV _tmr_cnt1,A
MOV A,b0_3
SUB A,019h
SNZ [0ah].0
JMP L9
#pragma debug scope 7 6 ; 60 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 60 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR _tmr_cnt1
#line 61 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET _flg_100ms
L9:
L8:
MOV A,V2S
MOV [0AH],A
MOV A,V2A
RETI
_tm0_isr ENDP
@tm0_isr .SECTION 'DATA'
b0_3 DB ?
PUBLIC _tmr_cnt1
@tmr_cnt1 .SECTION 'DATA'
#line 6 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
_tmr_cnt1 DB ? ; tmr_cnt1
#pragma debug variable 8 1 _tmr_cnt1 tmr_cnt1
EXTERN _clr_1621:NEAR
EXTERN _init_1621:NEAR
BITDATASEC .SECTION 'DATA'
PUBLIC _flg_100ms
#line 7 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
_flg_100ms DBIT ; flg_100ms
#pragma debug variable 2 1 _flg_100ms flg_100ms
#line 31 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
STARTSEC .SECTION  COM_L 'CODE'
STARTUP:
STARTSEC .SECTION  COM_E 'CODE'
RET
EXTERN V2A:BYTE
EXTERN V2S:BYTE
#line 31 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
@CODE .SECTION AT 0 'CODE'
CALL STARTUP
JMP begin
@DUMMY PROC
CALL _main
@DUMMY ENDP
