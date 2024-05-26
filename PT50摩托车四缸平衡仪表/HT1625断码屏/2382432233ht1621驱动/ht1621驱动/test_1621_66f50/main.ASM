#pragma debug scope 1 1
#line 13 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
__scomc EQU [05eH]
__tm3ah EQU [05dH]
__tm3al EQU [05cH]
__tm3dh EQU [05bH]
__tm3dl EQU [05aH]
__tm3c1 EQU [059H]
__tm3c0 EQU [058H]
__tm2rp EQU [057H]
__tm2ah EQU [056H]
__tm2al EQU [055H]
__tm2dh EQU [054H]
__tm2dl EQU [053H]
__tm2c1 EQU [052H]
__tm2c0 EQU [051H]
__tm1bh EQU [050H]
__tm1bl EQU [04fH]
__tm1ah EQU [04eH]
__tm1al EQU [04dH]
__tm1dh EQU [04cH]
__tm1dl EQU [04bH]
__tm1c2 EQU [04aH]
__tm1c1 EQU [049H]
__tm1c0 EQU [048H]
__prm2 EQU [047H]
__prm1 EQU [046H]
__prm0 EQU [045H]
__tmpc1 EQU [044H]
__tmpc0 EQU [043H]
__eed EQU [042H]
__eea EQU [041H]
__tm0ah EQU [03fH]
__tm0al EQU [03eH]
__tm0dh EQU [03dH]
__tm0dl EQU [03cH]
__tm0c1 EQU [03bH]
__tm0c0 EQU [03aH]
__simc2 EQU [039H]
__sima EQU [039H]
__simd EQU [038H]
__simc1 EQU [037H]
__simc0 EQU [036H]
__cp1c EQU [035H]
__cp0c EQU [034H]
__acerl EQU [032H]
__adcr1 EQU [031H]
__adcr0 EQU [030H]
__adrh EQU [02fH]
__adrl EQU [02eH]
__pfc EQU [02aH]
__pf EQU [029H]
__pfpu EQU [028H]
__pec EQU [027H]
__pe EQU [026H]
__pepu EQU [025H]
__pdc EQU [024H]
__pd EQU [023H]
__pdpu EQU [022H]
__pcc EQU [021H]
__pc EQU [020H]
__pcpu EQU [01fH]
__pbc EQU [01eH]
__pb EQU [01dH]
__pbpu EQU [01cH]
__pac EQU [01bH]
__pa EQU [01aH]
__papu EQU [019H]
__pawu EQU [018H]
__mfi3 EQU [017H]
__mfi2 EQU [016H]
__mfi1 EQU [015H]
__mfi0 EQU [014H]
__intc2 EQU [012H]
__intc1 EQU [011H]
__intc0 EQU [010H]
__tbc EQU [0fH]
__wdtc EQU [0eH]
__integ EQU [0dH]
__lvdc EQU [0cH]
__smod EQU [0bH]
__status EQU [0aH]
__tbhp EQU [09H]
__tblh EQU [08H]
__tblp EQU [07H]
__pcl EQU [06H]
__acc EQU [05H]
__bp EQU [04H]
__mp1 EQU [03H]
__iar1 EQU [02H]
__mp0 EQU [01H]
__iar0 EQU [00H]
@sys_init .SECTION 'CODE'
PUBLIC _sys_init
_sys_init PROC
#pragma debug scope 2 1 ; 14 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 14 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __papu
#line 15 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pac
#line 16 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pa
#line 18 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pbpu
#line 19 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pbc
#line 20 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pb
#line 22 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pcpu
#line 23 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pcc
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __pc
#line 29 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		a,80h
#line 30 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		__mp0,a
#line 31 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		a,128
#line 32 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
clr		__iar0
#line 33 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
inc		__mp0
#line 34 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
sdz		__acc
#line 35 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
jmp		$-3
#line 36 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"

#line 37 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		a,01
#line 38 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		__bp,a
#line 39 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		a,80h
#line 40 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		__mp0,a
#line 41 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		a,128
#line 42 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
clr		__iar0
#line 43 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
inc		__mp0
#line 44 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
sdz		__acc
#line 45 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
jmp		$-3
#line 46 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"

#line 47 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		a,02
#line 48 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		__bp,a
#line 49 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		a,80h
#line 50 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		__mp0,a
#line 51 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
mov		a,128
#line 52 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
clr		__iar0
#line 53 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
inc		__mp0
#line 54 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
sdz		__acc
#line 55 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
jmp		$-3
#line 56 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
clr		__bp
#line 60 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,08h
MOV __cp0c,A
#line 61 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,08h
MOV __cp1c,A
#line 63 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,030h
MOV __tm0c0,A
#line 64 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,0c1h
MOV __tm0c1,A
#line 65 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,0c1h
MOV __tm0al,A
#line 66 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,03h
MOV __tm0ah,A
#line 69 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET [03AH].3
#line 70 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET [011H].1
#line 71 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET [014H].1
#line 72 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET [010H].0
#line 74 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR __acerl
L1:
RET
_sys_init ENDP
#line 80 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
@MAIN .SECTION 'CODE'
_main PROC
begin:
#pragma debug scope 3 1 ; 81 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 81 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CALL _sys_init
#line 83 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CALL _init_1621
#line 83 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
JMP L4
L3:
#pragma debug scope 4 3 ; 87 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 87 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR WDT
#line 90 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SNZ _flg_100ms
JMP L6
#pragma debug scope 5 4 ; 92 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 92 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR _flg_100ms
#line 94 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CALL _clr_1621
L6:
L4:
#line 85 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#pragma debug scope 3 1 ; 85 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
JMP L3
L2:
#line 99 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
JMP $
_main ENDP
#line 104 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
@@tm0_isr .SECTION AT 014H 'CODE'
JMP _tm0_isr
@tm0_isr .SECTION 'CODE'
_tm0_isr PROC
MOV V5A,A
MOV A,[0AH]
MOV V5S,A
MOV A,[03H]
MOV V5MP1,A
MOV A,[04H]
MOV V5BP,A
#pragma debug scope 6 1 ; 105 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 105 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
CLR [014H].5
#line 107 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,BANK _tmr_cnt1
MOV [04H],A
MOV A,OFFSET _tmr_cnt1
MOV [03H],A
INCA [02H]
MOV b0_3,A
MOV A,BANK _tmr_cnt1
MOV [04H],A
MOV A,OFFSET _tmr_cnt1
MOV [03H],A
MOV A,b0_3
MOV [02H],A
MOV A,b0_3
SUB A,019h
SNZ [0ah].0
JMP L9
#pragma debug scope 7 6 ; 109 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
#line 109 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
MOV A,BANK _tmr_cnt1
MOV [04H],A
MOV A,OFFSET _tmr_cnt1
MOV [03H],A
CLR [02H]
#line 110 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
SET _flg_100ms
L9:
L8:
MOV A,V5MP1
MOV [03H],A
MOV A,V5BP
MOV [04H],A
MOV A,V5S
MOV [0AH],A
MOV A,V5A
RETI
_tm0_isr ENDP
RAMBANK 0 @tm0_isr
@tm0_isr .SECTION 'DATA'
b0_3 DB ?
#line 6 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
PUBLIC _tmr_cnt1
@tmr_cnt1 .SECTION 'DATA'
_tmr_cnt1 DB ? ; tmr_cnt1
#pragma debug variable 8 1 _tmr_cnt1 tmr_cnt1
EXTERN _clr_1621:NEAR
EXTERN _init_1621:NEAR
#line 9 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
RAMBANK 0 BITDATASEC
BITDATASEC .SECTION 'DATA'
PUBLIC _flg_100ms
_flg_100ms DBIT ; flg_100ms
#pragma debug variable 2 1 _flg_100ms flg_100ms
#line 79 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
STARTSEC .SECTION  COM_L 'CODE'
STARTUP:
STARTSEC .SECTION  COM_E 'CODE'
RET
EXTERN V5A:BYTE
EXTERN V5S:BYTE
EXTERN V5MP1:BYTE
EXTERN V5BP:BYTE
#line 79 "C:\Users\Eason\Desktop\test_1621_46r065 - 副本 (2)\main.c"
@CODE .SECTION AT 0 'CODE'
CALL STARTUP
JMP begin
@DUMMY PROC
CALL _main
@DUMMY ENDP
