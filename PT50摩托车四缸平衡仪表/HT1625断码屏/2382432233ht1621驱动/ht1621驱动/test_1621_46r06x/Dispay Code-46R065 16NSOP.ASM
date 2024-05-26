#pragma debug scope 1 1
#line 29 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_dspT .SECTION INPAGE PRIVATE 'CODE'
PUBLIC l_dspT
l_dspT:
ADDM A,[06h]
_dspT:
RET A,250
RET A,10
RET A,188
RET A,158
RET A,78
RET A,214
RET A,246
RET A,138
RET A,254
RET A,222
#line 30 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_dspA:
RET A,95
RET A,80
RET A,61
RET A,121
RET A,114
RET A,107
RET A,111
RET A,81
RET A,127
RET A,123
#line 59 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
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
@delay1 .SECTION 'CODE'
PUBLIC _delay1
_delay1 PROC
#pragma debug scope 2 1
#line 58 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC delay10
LOCAL delay10 DB ? ; i
#pragma debug variable 8 2 delay10 i
L2:
L3:
#pragma debug scope 2 1 ; 60 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 60 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,delay10
MOV b0_1,A
DEC delay10
SZ b0_1
JMP L2
L1:
RET
LOCAL b0_1 DB ?
_delay1 ENDP
#line 70 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@@ext_int .SECTION AT 04H 'CODE'
RETI
#line 71 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@@ad_int .SECTION AT 010H 'CODE'
RETI
#line 72 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@@tmr1_int .SECTION AT 0cH 'CODE'
RETI
#line 73 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@@base0_int .SECTION AT 014H 'CODE'
RETI
#line 75 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@@tmr0_int .SECTION AT 08H 'CODE'
JMP _tmr0_int
@tmr0_int .SECTION 'CODE'
_tmr0_int PROC
MOV V2A,A
MOV A,[0AH]
MOV V2S,A
#pragma debug scope 7 1 ; 76 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 76 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _cnt500ms
#line 77 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_cnt500ms
SUB A,07dh
SNZ [0ah].0
JMP L10
#pragma debug scope 8 7 ; 79 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 79 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _cnt500ms
#line 80 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _f_500ms
#line 81 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ _f_flash
JMP L32_0
SET _f_flash
JMP L32_1
L32_0:
CLR _f_flash
L32_1:
#line 82 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_min_16u[1]
SUB A,02h
SNZ [0ah].0
JMP L33
SNZ [0ah].2
JMP L12
MOV A,_min_16u
SUB A,0d0h
SZ [0ah].0
JMP L12
L33:
#pragma debug scope 9 8 ; 84 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 84 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _min_16u
SZ [0AH].2
INC _min_16u[1]
#line 85 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 8 7 ; 85 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L13
L12:
#pragma debug scope 10 8 ; 88 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 88 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _min_16u
CLR _min_16u[1]
#line 89 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_hour_32u[3]
SUB A,00h
SNZ [0ah].0
JMP L34
SNZ [0ah].2
JMP L14
MOV A,_hour_32u[2]
SUB A,0fh
SNZ [0ah].0
JMP L34
SNZ [0ah].2
JMP L14
MOV A,_hour_32u[1]
SUB A,042h
SNZ [0ah].0
JMP L34
SNZ [0Ah].2
JMP L14
MOV A,_hour_32u
SUB A,03fh
SZ [0ah].0
JMP L14
L34:
#pragma debug scope 11 10 ; 91 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 91 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _hour_32u
SZ [0AH].2
INC _hour_32u[1]
SZ [0AH].2
INC _hour_32u[2]
SZ [0AH].2
INC _hour_32u[3]
#line 92 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 10 8 ; 92 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L15
L14:
#pragma debug scope 12 10 ; 95 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 95 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _hour_32u
CLR _hour_32u[1]
CLR _hour_32u[2]
CLR _hour_32u[3]
#line 96 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _min_16u
CLR _min_16u[1]
L15:
L13:
L10:
#line 100 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 7 1 ; 100 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ _f_adflag
JMP L35_0
SET _f_adflag
JMP L35_1
L35_0:
CLR _f_adflag
L35_1:
#line 101 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ _f_adflag
JMP L16
#pragma debug scope 13 7 ; 103 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 103 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
MOV __acsr,A
#line 103 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,010h
MOV __adcr,A
#line 103 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [022H].7
#line 103 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [022H].7
#line 103 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [022H].7
L18:
L19:
#line 104 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [022H].6
JMP L18
#line 105 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,__adrh
MOV b0_6,A
CLR b0_6[1]
SWAP b0_6[1]
MOV A,0F0H
ANDM A,b0_6[1]
SWAPA b0_6
AND A,0FH
ORM A,b0_6[1]
SWAP b0_6
MOV A,0F0H
ANDM A,b0_6
SWAPA __adrl
AND A,0FH
MOV b1_6,A
CLR b1_6[1]
MOV A,b1_6
ADD A,b0_6
MOV b0_6,A
MOV A,b1_6[1]
ADC A,b0_6[1]
MOV b0_6[1],A
CLR b0_6[2]
CLR b0_6[3]
MOV A,b0_6
ADDM A,_adsumv_32u
MOV A,b0_6[1]
ADCM A,_adsumv_32u[1]
MOV A,b0_6[2]
ADCM A,_adsumv_32u[2]
MOV A,b0_6[3]
ADCM A,_adsumv_32u[3]
#line 106 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _adnumv
#line 107 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,__adrh
SUB A,03ch
SZ [0ah].0
JMP L21
#pragma debug scope 14 13 ; 109 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 109 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,03ch
SUB A,_cnt5s
SZ [0ah].0
JMP L23
#pragma debug scope 15 14 ; 111 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 111 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _f_poweroff
#line 112 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 14 13 ; 112 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L24
L23:
#pragma debug scope 16 14 ; 115 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 115 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_poweroff
#line 116 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_save
L24:
L21:
#line 119 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 13 7 ; 119 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR __adcr
#line 120 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_adnumv
XOR A,015h
SNZ [0ah].2
JMP L17
#pragma debug scope 17 13 ; 122 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 122 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_adsumv_32u
MOV _adaverv_32u,A
MOV A,_adsumv_32u[1]
MOV _adaverv_32u[1],A
MOV A,_adsumv_32u[2]
MOV _adaverv_32u[2],A
MOV A,_adsumv_32u[3]
MOV _adaverv_32u[3],A
#line 123 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _adsumv_32u
CLR _adsumv_32u[1]
CLR _adsumv_32u[2]
CLR _adsumv_32u[3]
#line 124 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _adnumv
#line 126 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 7 1 ; 126 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L17
L16:
#pragma debug scope 18 7 ; 129 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 129 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
MOV __acsr,A
#line 129 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,011h
MOV __adcr,A
#line 129 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [022H].7
#line 129 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [022H].7
#line 129 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [022H].7
L27:
L28:
#line 130 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [022H].6
JMP L27
#line 131 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,__adrh
MOV b0_6,A
CLR b0_6[1]
SWAP b0_6[1]
MOV A,0F0H
ANDM A,b0_6[1]
SWAPA b0_6
AND A,0FH
ORM A,b0_6[1]
SWAP b0_6
MOV A,0F0H
ANDM A,b0_6
SWAPA __adrl
AND A,0FH
MOV b1_6,A
CLR b1_6[1]
MOV A,b1_6
ADD A,b0_6
MOV b0_6,A
MOV A,b1_6[1]
ADC A,b0_6[1]
MOV b0_6[1],A
MOV A,b0_6
ADDM A,_adsumi_16u
MOV A,b0_6[1]
ADCM A,_adsumi_16u[1]
#line 132 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _adnumi
#line 133 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR __adcr
#line 134 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_adnumi
XOR A,08h
SNZ [0ah].2
JMP L30
#pragma debug scope 19 18 ; 136 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 136 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [0AH].0
RRC _adsumi_16u[1]
RRC _adsumi_16u
CLR [0AH].0
RRC _adsumi_16u[1]
RRC _adsumi_16u
CLR [0AH].0
RRC _adsumi_16u[1]
RRC _adsumi_16u
#line 137 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_adsumi_16u
MOV _adaveri_16u,A
MOV A,_adsumi_16u[1]
MOV _adaveri_16u[1],A
#line 138 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _adsumi_16u
CLR _adsumi_16u[1]
#line 139 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _adnumi
L30:
L17:
L9:
MOV A,V2S
MOV [0AH],A
MOV A,V2A
RETI
_tmr0_int ENDP
@tmr0_int .SECTION 'DATA'
b0_6 DB 4 DUP(?)
b1_6 DB 2 DUP(?)
#line 144 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@init .SECTION 'CODE'
PUBLIC _init
_init PROC
#pragma debug scope 20 1 ; 145 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 145 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR __ctrl0
#line 146 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0f5h
MOV __ctrl1,A
#line 147 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0e7h
MOV __pa,A
#line 148 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0e7h
MOV __pac,A
#line 149 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04h
MOV __papu,A
#line 150 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,03fh
MOV __pbpu,A
#line 151 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01fh
MOV __pbc,A
#line 152 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,03fh
MOV __pb,A
#line 153 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0feh
MOV __pcpu,A
#line 154 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0c0h
MOV __pcc,A
#line 155 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0ch
MOV __pc,A
#line 156 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04h
MOV __intc0,A
#line 157 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR __intc1
#line 158 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,086h
MOV __tmr0c,A
#line 159 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,06h
MOV __tmr0,A
#line 160 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,090h
MOV __tmr1c,A
#line 161 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,06h
MOV __tmr1,A
#line 162 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,07h
MOV __wdts,A
L36:
RET
_init ENDP
#line 169 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@ram_clr .SECTION 'CODE'
PUBLIC _ram_clr
_ram_clr PROC
#pragma debug scope 21 1 ; 170 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 170 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,040h
MOV __mp0,A
#line 170 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L41
L38:
#pragma debug scope 22 21 ; 172 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 172 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR __iar0
L39:
#line 170 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 21 1 ; 170 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC __mp0
L41:
#line 170 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,09fh
SUB A,__mp0
SZ [0AH].0
JMP L38
L37:
RET
_ram_clr ENDP
#line 176 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@MAIN .SECTION 'CODE'
_main PROC
begin:
#pragma debug scope 23 1 ; 177 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 177 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _init
#line 178 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _ram_clr
#line 179 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04h
MOV sendcmd0,A
CALL _sendcmd
#line 180 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,052h
MOV sendcmd0,A
CALL _sendcmd
#line 181 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,02h
MOV sendcmd0,A
CALL _sendcmd
#line 183 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _j
#line 183 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L46
L43:
#pragma debug scope 24 23 ; 185 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 185 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [0AH].0
RLCA _j
MOV b0_9,A
CLR [0AH].0
RLC b0_9
MOV A,b0_9
MOV write_16210,A
MOV A,00h
MOV write_16211,A
CALL _write_1621
#line 186 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 187 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,018H
CALL __DELAYX0
L44:
#line 183 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 183 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _j
L46:
#line 183 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01fh
SUB A,_j
SZ [0ah].0
JMP L43
#line 190 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 191 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,05h
MOV IICReadByteAt0,A
MOV A,OFFSET _k
MOV IICReadByteAt1,A
CALL _IICReadByteAt
#line 192 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 193 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_k
MOV _min_16u,A
CLR _min_16u[1]
#line 194 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_min_16u
MOV _min_16u[1],A
CLR _min_16u
#line 195 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0f9H
CALL __DELAYX0
#line 196 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 197 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04h
MOV IICReadByteAt0,A
MOV A,OFFSET _k
MOV IICReadByteAt1,A
CALL _IICReadByteAt
#line 198 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 199 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_k
ADDM A,_min_16u
CLR [05H]
ADCM A,_min_16u[1]
#line 200 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0f9H
CALL __DELAYX0
#line 201 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 203 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _j
#line 203 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L50
L47:
#pragma debug scope 25 23 ; 205 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 205 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_j
MOV IICReadByteAt0,A
MOV A,OFFSET _k
MOV IICReadByteAt1,A
CALL _IICReadByteAt
#line 206 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 207 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0f9H
CALL __DELAYX0
#line 208 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 209 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_k
MOV b0_9,A
CLR b0_9[1]
CLR b0_9[2]
CLR b0_9[3]
SWAPA _j
RR [05H]
AND A,0F8H
MOV b1_9,A
MOV A,b1_9
MOV RH,A
MOV A,b0_9
MOV b0_9,A
MOV A,b0_9[1]
MOV b0_9[1],A
MOV A,b0_9[2]
MOV b0_9[2],A
MOV A,b0_9[3]
MOV b0_9[3],A
SZA RH
JMP sha243
JMP shb243
sha243:
CLR [0AH].0
RLC b0_9
RLC b0_9[1]
RLC b0_9[2]
RLC b0_9[3]
SDZ RH
JMP sha243
shb243:
MOV A,b0_9
ADDM A,_hour_32u
MOV A,b0_9[1]
ADCM A,_hour_32u[1]
MOV A,b0_9[2]
ADCM A,_hour_32u[2]
MOV A,b0_9[3]
ADCM A,_hour_32u[3]
L48:
#line 203 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 203 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _j
L50:
#line 203 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_j
SUB A,04h
SNZ [0ah].0
JMP L47
#line 212 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,00h
SUB A,_hour_32u[3]
SNZ [0ah].0
JMP L244
SNZ [0ah].2
JMP L51
MOV A,0fh
SUB A,_hour_32u[2]
SNZ [0Ah].0
JMP L244
SNZ [0Ah].2
JMP L51
MOV A,042h
SUB A,_hour_32u[1]
SNZ [0Ah].0
JMP L244
SNZ [0Ah].2
JMP L51
MOV A,03fh
SUB A,_hour_32u
SZ [0ah].0
JMP L51
L244:
#pragma debug scope 26 23 ; 214 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 214 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _hour_32u
CLR _hour_32u[1]
CLR _hour_32u[2]
CLR _hour_32u[3]
#line 215 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _min_16u
CLR _min_16u[1]
L51:
#line 217 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 217 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_poweroff
#line 218 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [0DH].4
#line 219 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [0BH].0
#line 220 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,06h
MOV sendcmd0,A
CALL _sendcmd
#line 221 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _cnt5s
#line 222 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _j
#line 222 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L56
L53:
#pragma debug scope 27 23 ; 224 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 224 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04H
MOV RH,A
MOV A,0deH
CALL __DELAYY3
#line 225 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
L54:
#line 222 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 222 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _j
L56:
#line 222 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_j
SUB A,064h
SNZ [0ah].0
JMP L53
#line 227 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _f_saodiche
#line 228 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [017H].6
JMP L57
#pragma debug scope 28 23 ; 230 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 230 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04H
MOV RH,A
MOV A,0deH
CALL __DELAYY3
#line 231 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 232 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04H
MOV RH,A
MOV A,0deH
CALL __DELAYY3
#line 233 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 234 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [017H].6
JMP L59
#pragma debug scope 29 28 ; 236 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 236 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_saodiche
L59:
L57:
#line 239 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 239 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _f_telephone
#line 240 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [017H].7
JMP L61
#pragma debug scope 30 23 ; 242 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 242 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04H
MOV RH,A
MOV A,0deH
CALL __DELAYY3
#line 243 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 244 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04H
MOV RH,A
MOV A,0deH
CALL __DELAYY3
#line 245 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 246 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [017H].7
JMP L63
#pragma debug scope 31 30 ; 248 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 248 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_telephone
L63:
L61:
#line 252 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 252 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,00h
SUB A,_adaverv_32u[3]
SNZ [0ah].0
JMP L245
SNZ [0ah].2
JMP L65
MOV A,00h
SUB A,_adaverv_32u[2]
SNZ [0Ah].0
JMP L245
SNZ [0Ah].2
JMP L65
MOV A,0c0h
SUB A,_adaverv_32u[1]
SNZ [0Ah].0
JMP L245
SNZ [0Ah].2
JMP L65
MOV A,00h
SUB A,_adaverv_32u
SZ [0ah].0
JMP L65
L245:
#pragma debug scope 32 23 ; 254 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 254 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0e4h
MOV _step1_16u,A
MOV A,02h
MOV _step1_16u[1],A
#line 255 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0d0h
MOV _step2_16u,A
MOV A,02h
MOV _step2_16u[1],A
#line 256 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0a8h
MOV _step3_16u,A
MOV A,02h
MOV _step3_16u[1],A
#line 257 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 257 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L68
L65:
#pragma debug scope 33 23 ; 260 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 260 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0e0h
MOV _step1_16u,A
MOV A,01h
MOV _step1_16u[1],A
#line 261 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0cch
MOV _step2_16u,A
MOV A,01h
MOV _step2_16u[1],A
#line 262 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0a4h
MOV _step3_16u,A
MOV A,01h
MOV _step3_16u[1],A
#line 263 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 263 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L68
L67:
#pragma debug scope 34 23 ; 266 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 266 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 268 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_poweroff
JMP L70
#pragma debug scope 35 34 ; 270 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 270 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ _f_save
JMP L72
#pragma debug scope 36 35 ; 272 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 272 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _f_save
#line 273 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _j
#line 273 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L77
L74:
#pragma debug scope 37 36 ; 275 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 275 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SWAPA _j
RR [05H]
AND A,0F8H
MOV b0_9,A
MOV A,b0_9
MOV RH,A
MOV A,_hour_32u
MOV b0_9,A
MOV A,_hour_32u[1]
MOV b0_9[1],A
MOV A,_hour_32u[2]
MOV b0_9[2],A
MOV A,_hour_32u[3]
MOV b0_9[3],A
SZA RH
JMP sha246
JMP shb246
sha246:
CLR [0AH].0
RRC b0_9[3]
RRC b0_9[2]
RRC b0_9[1]
RRC b0_9
SDZ RH
JMP sha246
shb246:
MOV A,b0_9
MOV _k,A
#line 276 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 277 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_j
MOV IICWriteByteAt0,A
MOV A,_k
MOV IICWriteByteAt1,A
CALL _IICWriteByteAt
#line 278 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01H
MOV RH,A
MOV A,0f2H
CALL __DELAYY1
#line 279 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
L75:
#line 273 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 36 35 ; 273 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _j
L77:
#line 273 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_j
SUB A,04h
SNZ [0ah].0
JMP L74
#line 281 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_min_16u
MOV _k,A
#line 282 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 283 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04h
MOV IICWriteByteAt0,A
MOV A,_k
MOV IICWriteByteAt1,A
CALL _IICWriteByteAt
#line 284 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01H
MOV RH,A
MOV A,0f2H
CALL __DELAYY1
#line 285 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 286 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_min_16u[1]
MOV b0_9,A
CLR b0_9[1]
MOV A,b0_9
MOV _k,A
#line 287 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 288 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,05h
MOV IICWriteByteAt0,A
MOV A,_k
MOV IICWriteByteAt1,A
CALL _IICWriteByteAt
#line 289 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01H
MOV RH,A
MOV A,0f2H
CALL __DELAYY1
#line 290 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
L72:
L70:
#line 295 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 34 23 ; 295 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 296 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_500ms
JMP L78
#pragma debug scope 38 34 ; 298 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 298 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 299 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_500ms
#line 300 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_cnt5s
SUB A,064h
SZ [0ah].0
JMP L80
#pragma debug scope 39 38 ; 302 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 302 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _cnt5s
L80:
#line 307 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 307 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,__pb
AND A,01fh
XOR A,01fh
SNZ [0AH].2
JMP L82
#pragma debug scope 40 38 ; 309 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 309 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt.2
#line 310 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0f0h
ANDM A,_lcdt[1]
#line 311 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[2].2
#line 312 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 312 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L83
L82:
#pragma debug scope 41 38 ; 315 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 315 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [014H].0
JMP L86
#pragma debug scope 42 41 ; 317 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 317 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,03h
ORM A,_lcdt[1]
#line 318 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 318 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L87
L86:
#pragma debug scope 43 41 ; 321 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 321 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0fch
ANDM A,_lcdt[1]
L87:
#line 323 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 323 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [014H].3
JMP L90
#pragma debug scope 44 41 ; 325 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 325 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[1].3
#line 326 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 326 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L91
L90:
#pragma debug scope 45 41 ; 329 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 329 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[1].3
L91:
#line 331 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 331 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [014H].4
JMP L94
#pragma debug scope 46 41 ; 333 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 333 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[1].2
#line 334 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 334 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L95
L94:
#pragma debug scope 47 41 ; 337 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 337 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[1].2
L95:
#line 339 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 339 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [014H].2
JMP L98
#pragma debug scope 48 41 ; 341 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 341 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt.2
#line 342 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 342 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L99
L98:
#pragma debug scope 49 41 ; 345 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 345 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt.2
L99:
#line 347 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 347 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [014H].1
JMP L100
#pragma debug scope 50 41 ; 349 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 349 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[2].2
#line 350 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 41 38 ; 350 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L101
L100:
#pragma debug scope 51 41 ; 353 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 353 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[2].2
L101:
L83:
#line 359 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 359 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_hour_32u
MOV T2,A
MOV A,_hour_32u[1]
MOV RH,A
MOV A,_hour_32u[2]
MOV RM,A
MOV A,_hour_32u[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,01h
MOV T5,A
MOV A,086h
MOV T4,A
MOV A,0a0h
MOV T3,A
CALL DIVUL4
MOV A,RU
MOV b0_9[3],A
MOV A,RM
MOV b0_9[2],A
MOV A,RH
MOV b0_9[1],A
MOV A,T2
MOV b0_9,A
MOV A,b0_9
MOV _lcdtemp,A
#line 360 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,09h
SUB A,_lcdtemp
SZ [0ah].0
JMP L104
#pragma debug scope 52 38 ; 362 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 362 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,09h
MOV _lcdtemp,A
L104:
#line 364 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 364 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd,A
#line 365 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 366 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_hour_32u
MOV T2,A
MOV A,_hour_32u[1]
MOV RH,A
MOV A,_hour_32u[2]
MOV RM,A
MOV A,_hour_32u[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,027h
MOV T4,A
MOV A,010h
MOV T3,A
CALL DIVUL4
MOV A,RU
MOV b0_9[3],A
MOV A,RM
MOV b0_9[2],A
MOV A,RH
MOV b0_9[1],A
MOV A,T2
MOV b0_9,A
MOV A,b0_9
MOV T2,A
MOV A,b0_9[1]
MOV RH,A
MOV A,b0_9[2]
MOV RM,A
MOV A,b0_9[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,00h
MOV T4,A
MOV A,0ah
MOV T3,A
CALL DIVUL4
MOV A,T10
MOV b0_9[3],A
MOV A,T9
MOV b0_9[2],A
MOV A,T8
MOV b0_9[1],A
MOV A,T7
MOV b0_9,A
MOV A,b0_9
MOV _lcdtemp,A
#line 367 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd[1],A
#line 368 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 369 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_hour_32u
MOV T2,A
MOV A,_hour_32u[1]
MOV RH,A
MOV A,_hour_32u[2]
MOV RM,A
MOV A,_hour_32u[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,03h
MOV T4,A
MOV A,0e8h
MOV T3,A
CALL DIVUL4
MOV A,RU
MOV b0_9[3],A
MOV A,RM
MOV b0_9[2],A
MOV A,RH
MOV b0_9[1],A
MOV A,T2
MOV b0_9,A
MOV A,b0_9
MOV T2,A
MOV A,b0_9[1]
MOV RH,A
MOV A,b0_9[2]
MOV RM,A
MOV A,b0_9[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,00h
MOV T4,A
MOV A,0ah
MOV T3,A
CALL DIVUL4
MOV A,T10
MOV b0_9[3],A
MOV A,T9
MOV b0_9[2],A
MOV A,T8
MOV b0_9[1],A
MOV A,T7
MOV b0_9,A
MOV A,b0_9
MOV _lcdtemp,A
#line 370 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd[2],A
#line 371 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 372 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_hour_32u
MOV T2,A
MOV A,_hour_32u[1]
MOV RH,A
MOV A,_hour_32u[2]
MOV RM,A
MOV A,_hour_32u[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,00h
MOV T4,A
MOV A,064h
MOV T3,A
CALL DIVUL4
MOV A,RU
MOV b0_9[3],A
MOV A,RM
MOV b0_9[2],A
MOV A,RH
MOV b0_9[1],A
MOV A,T2
MOV b0_9,A
MOV A,b0_9
MOV T2,A
MOV A,b0_9[1]
MOV RH,A
MOV A,b0_9[2]
MOV RM,A
MOV A,b0_9[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,00h
MOV T4,A
MOV A,0ah
MOV T3,A
CALL DIVUL4
MOV A,T10
MOV b0_9[3],A
MOV A,T9
MOV b0_9[2],A
MOV A,T8
MOV b0_9[1],A
MOV A,T7
MOV b0_9,A
MOV A,b0_9
MOV _lcdtemp,A
#line 373 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd[3],A
#line 374 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 375 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_hour_32u
MOV T2,A
MOV A,_hour_32u[1]
MOV RH,A
MOV A,_hour_32u[2]
MOV RM,A
MOV A,_hour_32u[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,00h
MOV T4,A
MOV A,0ah
MOV T3,A
CALL DIVUL4
MOV A,RU
MOV b0_9[3],A
MOV A,RM
MOV b0_9[2],A
MOV A,RH
MOV b0_9[1],A
MOV A,T2
MOV b0_9,A
MOV A,b0_9
MOV T2,A
MOV A,b0_9[1]
MOV RH,A
MOV A,b0_9[2]
MOV RM,A
MOV A,b0_9[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,00h
MOV T4,A
MOV A,0ah
MOV T3,A
CALL DIVUL4
MOV A,T10
MOV b0_9[3],A
MOV A,T9
MOV b0_9[2],A
MOV A,T8
MOV b0_9[1],A
MOV A,T7
MOV b0_9,A
MOV A,b0_9
MOV _lcdtemp,A
#line 376 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd[4],A
#line 377 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 378 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_hour_32u
MOV T2,A
MOV A,_hour_32u[1]
MOV RH,A
MOV A,_hour_32u[2]
MOV RM,A
MOV A,_hour_32u[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,00h
MOV T4,A
MOV A,0ah
MOV T3,A
CALL DIVUL4
MOV A,T10
MOV b0_9[3],A
MOV A,T9
MOV b0_9[2],A
MOV A,T8
MOV b0_9[1],A
MOV A,T7
MOV b0_9,A
MOV A,b0_9
MOV _lcdtemp,A
#line 379 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd[5],A
#line 380 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 382 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[4].0
#line 383 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[5].0
#line 388 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04h
ADD A,_adaveri_16u
MOV b0_9,A
MOV A,00h
ADC A,_adaveri_16u[1]
MOV b0_9[1],A
MOV A,_adibak_16u[1]
SUB A,b0_9[1]
SNZ [0ah].0
JMP L247
SNZ [0ah].2
JMP L115
MOV A,_adibak_16u
SUB A,b0_9
SNZ [0ah].0
JMP L247
SNZ [0ah].2
JMP L115
L247:
MOV A,04h
ADD A,_adibak_16u
MOV b0_9,A
MOV A,00h
ADC A,_adibak_16u[1]
MOV b0_9[1],A
MOV A,b0_9[1]
SUB A,_adaveri_16u[1]
SNZ [0ah].0
JMP L248
SNZ [0ah].2
JMP L113
MOV A,b0_9
SUB A,_adaveri_16u
SZ [0ah].0
JMP L113
L248:
L115:
#pragma debug scope 53 38 ; 390 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 390 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_adaveri_16u
MOV _adibak_16u,A
MOV A,_adaveri_16u[1]
MOV _adibak_16u[1],A
L113:
#line 392 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 392 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_adibak_16u
MOV b0_9,A
MOV A,_adibak_16u[1]
MOV b0_9[1],A
CLR b0_9[2]
CLR b0_9[3]
MOV A,b0_9
MOV T2,A
MOV A,b0_9[1]
MOV RH,A
MOV A,b0_9[2]
MOV RM,A
MOV A,b0_9[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,02h
MOV T4,A
MOV A,071h
MOV T3,A
CALL MULL4
MOV A,T10
MOV b0_9[3],A
MOV A,T9
MOV b0_9[2],A
MOV A,T8
MOV b0_9[1],A
MOV A,T7
MOV b0_9,A
MOV A,b0_9
MOV T2,A
MOV A,b0_9[1]
MOV RH,A
MOV A,b0_9[2]
MOV RM,A
MOV A,b0_9[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,010h
MOV T4,A
MOV A,080h
MOV T3,A
CALL DIVUL4
MOV A,RU
MOV b0_9[3],A
MOV A,RM
MOV b0_9[2],A
MOV A,RH
MOV b0_9[1],A
MOV A,T2
MOV b0_9,A
MOV A,b0_9
MOV _current_16u,A
MOV A,b0_9[1]
MOV _current_16u[1],A
#line 393 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_current_16u[1]
SUB A,00h
SNZ [0ah].0
JMP L249
SNZ [0ah].2
JMP L116
MOV A,_current_16u
SUB A,02h
SZ [0ah].0
JMP L116
L249:
#pragma debug scope 54 38 ; 395 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 395 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _current_16u
CLR _current_16u[1]
L116:
#line 397 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 397 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
SUB A,_current_16u[1]
SNZ [0ah].0
JMP L250
SNZ [0ah].2
JMP L118
MOV A,0f4h
SUB A,_current_16u
SZ [0ah].0
JMP L118
L250:
#pragma debug scope 55 38 ; 399 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 399 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0f4h
MOV _current_16u,A
MOV A,01h
MOV _current_16u[1],A
L118:
#line 401 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 401 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,064h
MOV T2,A
MOV A,00h
MOV RH,A
MOV A,_current_16u[1]
MOV T6,A
MOV A,_current_16u
CALL DIVUL
MOV b0_9,A
MOV A,T6
MOV b0_9[1],A
MOV A,b0_9
MOV _lcdtemp,A
#line 402 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,10
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd[8],A
#line 403 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0ah
MOV T2,A
MOV A,00h
MOV RH,A
MOV A,_current_16u[1]
MOV T6,A
MOV A,_current_16u
CALL DIVUL
MOV b0_9,A
MOV A,T6
MOV b0_9[1],A
MOV A,0ah
MOV T2,A
MOV A,00h
MOV RH,A
MOV A,b0_9[1]
MOV T6,A
MOV A,b0_9
CALL DIVUL
MOV A,T5
MOV b0_9,A
MOV A,T4
MOV b0_9[1],A
MOV A,b0_9
MOV _lcdtemp,A
#line 404 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,10
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd[7],A
#line 405 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0ah
MOV T2,A
MOV A,00h
MOV RH,A
MOV A,_current_16u[1]
MOV T6,A
MOV A,_current_16u
CALL DIVUL
MOV A,T5
MOV b0_9,A
MOV A,T4
MOV b0_9[1],A
MOV A,b0_9
MOV _lcdtemp,A
#line 406 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,10
ADD A,_lcdtemp
CALL l_dspT
MOV _lcd[6],A
#line 407 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[6].7
#line 408 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[2].1
#line 412 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_adaverv_32u
MOV T2,A
MOV A,_adaverv_32u[1]
MOV RH,A
MOV A,_adaverv_32u[2]
MOV RM,A
MOV A,_adaverv_32u[3]
MOV RU,A
MOV A,00h
MOV T6,A
MOV A,00h
MOV T5,A
MOV A,00h
MOV T4,A
MOV A,032h
MOV T3,A
CALL MULL4
MOV A,T10
MOV b0_9[3],A
MOV A,T9
MOV b0_9[2],A
MOV A,T8
MOV b0_9[1],A
MOV A,T7
MOV b0_9,A
CLR [0Ah].0
RRC b0_9[3]
RRC b0_9[2]
RRC b0_9[1]
RRC b0_9
MOV A,0ch
DEC [05h]
sha252:
CLR [0Ah].0
RRC b0_9[3]
RRC b0_9[2]
RRC b0_9[1]
RRC b0_9
SDZ [05h]
JMP sha252
MOV A,b0_9
MOV _voltage_16u,A
MOV A,b0_9[1]
MOV _voltage_16u[1],A
#line 413 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,05h
ADD A,_voltage_16u
MOV b0_9,A
MOV A,00h
ADC A,_voltage_16u[1]
MOV b0_9[1],A
MOV A,_voltagebak_16u[1]
SUB A,b0_9[1]
SNZ [0ah].0
JMP L253
SNZ [0ah].2
JMP L127
MOV A,_voltagebak_16u
SUB A,b0_9
SNZ [0ah].0
JMP L253
SNZ [0ah].2
JMP L127
L253:
MOV A,05h
ADD A,_voltagebak_16u
MOV b0_9,A
MOV A,00h
ADC A,_voltagebak_16u[1]
MOV b0_9[1],A
MOV A,b0_9[1]
SUB A,_voltage_16u[1]
SNZ [0ah].0
JMP L254
SNZ [0ah].2
JMP L125
MOV A,b0_9
SUB A,_voltage_16u
SZ [0ah].0
JMP L125
L254:
L127:
#pragma debug scope 56 38 ; 415 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 415 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_voltage_16u
MOV _voltagebak_16u,A
MOV A,_voltage_16u[1]
MOV _voltagebak_16u[1],A
L125:
#line 417 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 417 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd.0
#line 418 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt.0
#line 419 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_step1_16u[1]
SUB A,_voltagebak_16u[1]
SNZ [0ah].0
JMP L255
SNZ [0ah].2
JMP L128
MOV A,_step1_16u
SUB A,_voltagebak_16u
SNZ [0ah].0
JMP L255
SNZ [0ah].2
JMP L128
L255:
#pragma debug scope 57 38 ; 421 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 421 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_vlow
#line 422 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt.1
#line 423 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[1].0
#line 424 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[2].0
#line 425 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[3].0
#line 426 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 426 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L129
L128:
#line 427 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_step2_16u[1]
SUB A,_voltagebak_16u[1]
SNZ [0ah].0
JMP L256
SNZ [0ah].2
JMP L133
MOV A,_step2_16u
SUB A,_voltagebak_16u
SNZ [0ah].0
JMP L256
SNZ [0ah].2
JMP L133
L256:
#pragma debug scope 58 38 ; 429 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 429 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_vlow
#line 430 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt.1
#line 431 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[1].0
#line 432 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[2].0
#line 433 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 433 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L134
L133:
#line 434 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_step3_16u[1]
SUB A,_voltagebak_16u[1]
SNZ [0ah].0
JMP L257
SNZ [0ah].2
JMP L137
MOV A,_step3_16u
SUB A,_voltagebak_16u
SNZ [0ah].0
JMP L257
SNZ [0ah].2
JMP L137
L257:
#pragma debug scope 59 38 ; 436 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 436 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _f_vlow
#line 437 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt.1
#line 438 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[1].0
#line 439 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 439 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L138
L137:
#pragma debug scope 60 38 ; 442 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 442 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _f_vlow
#line 443 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _lcdt.1
JMP L140
#pragma debug scope 61 60 ; 445 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 445 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt.1
#line 446 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 60 38 ; 446 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L141
L140:
#pragma debug scope 62 60 ; 449 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 449 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt.1
L141:
L138:
L134:
L129:
#line 452 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 452 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_flash
JMP L142
SNZ _f_vlow
JMP L142
#pragma debug scope 63 38 ; 454 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 454 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].1
#line 455 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 455 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L143
L142:
#pragma debug scope 64 38 ; 458 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 458 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].1
L143:
#line 463 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 463 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC _mode
#line 464 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0fh
SUB A,_mode
SZ [0ah].0
JMP L144
#pragma debug scope 65 38 ; 466 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 466 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _mode
L144:
#line 468 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 468 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,_mode
MOV b0_9,A
SZ b0_9
JMP L258
JMP L148
L258:
MOV A,b0_9
XOR A,01h
SZ [0ah].2
JMP L155
MOV A,b0_9
XOR A,02h
SZ [0ah].2
JMP L165
MOV A,b0_9
XOR A,03h
SZ [0ah].2
JMP L175
MOV A,b0_9
XOR A,04h
SZ [0ah].2
JMP L185
MOV A,b0_9
XOR A,05h
SZ [0ah].2
JMP L195
#line 468 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L146
L148:
#pragma debug scope 66 38 ; 471 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 471 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[3].0
#line 472 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[3].2
#line 473 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].1
#line 474 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[3].3
#line 475 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcd[8].7
#line 476 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].2
#line 477 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L147
L155:
#line 479 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_saodiche
JMP L156
#pragma debug scope 67 66 ; 481 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 481 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].0
#line 482 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].1
#line 483 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcd[8].7
#line 484 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 484 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L157
L156:
#pragma debug scope 68 66 ; 487 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 487 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].1
L157:
#line 489 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 489 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[3].2
#line 490 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].2
#line 491 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[3].3
#line 492 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L147
L165:
#line 494 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_saodiche
JMP L166
#pragma debug scope 69 66 ; 496 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 496 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].0
#line 497 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].1
#line 498 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcd[8].7
#line 499 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 499 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L167
L166:
#pragma debug scope 70 66 ; 502 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 502 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].1
L167:
#line 505 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 505 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].2
#line 506 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].2
#line 507 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[3].3
#line 508 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L147
L175:
#line 510 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_saodiche
JMP L176
#pragma debug scope 71 66 ; 512 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 512 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].0
#line 513 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcd[8].7
#line 514 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].2
#line 515 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 515 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L177
L176:
#pragma debug scope 72 66 ; 518 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 518 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].2
L177:
#line 520 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 520 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[3].3
#line 521 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].1
#line 522 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].2
#line 523 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L147
L185:
#line 525 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_saodiche
JMP L186
#pragma debug scope 73 66 ; 527 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 527 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].0
#line 528 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcd[8].7
#line 529 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].2
#line 530 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 530 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L187
L186:
#pragma debug scope 74 66 ; 533 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 533 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].2
L187:
#line 535 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 535 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].1
#line 536 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].2
#line 537 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].3
#line 538 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L147
L195:
#line 540 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_saodiche
JMP L196
#pragma debug scope 75 66 ; 542 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 542 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].0
#line 543 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[8].7
#line 544 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].2
#line 545 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 545 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L197
L196:
#pragma debug scope 76 66 ; 548 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 548 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].2
L197:
#line 550 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 550 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].2
#line 551 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].1
#line 552 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].3
#line 553 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L147
L146:
#line 555 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_saodiche
JMP L205
#pragma debug scope 77 66 ; 557 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 557 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].0
#line 558 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcd[8].7
L205:
#line 560 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 66 38 ; 560 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].1
#line 561 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].2
#line 562 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].2
#line 563 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].3
L147:
#line 566 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 566 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ _f_telephone
JMP L213
#pragma debug scope 78 38 ; 568 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 568 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt.3
#line 569 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].0
#line 570 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].3
#line 571 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].1
#line 572 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[2].3
#line 573 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 573 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L214
L213:
#pragma debug scope 79 38 ; 576 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 576 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt.3
#line 577 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[4].0
#line 578 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[4].3
#line 579 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET _lcdt[3].1
#line 580 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR _lcdt[2].3
L214:
#line 583 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 38 34 ; 583 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,020h
MOV write_16210,A
SWAPA _lcd
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 584 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01ch
MOV write_16210,A
MOV A,_lcd
MOV write_16211,A
CALL _write_1621
#line 585 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,018h
MOV write_16210,A
SWAPA _lcd[1]
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 586 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,014h
MOV write_16210,A
MOV A,_lcd[1]
MOV write_16211,A
CALL _write_1621
#line 587 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,010h
MOV write_16210,A
SWAPA _lcd[2]
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 588 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0ch
MOV write_16210,A
MOV A,_lcd[2]
MOV write_16211,A
CALL _write_1621
#line 589 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,08h
MOV write_16210,A
SWAPA _lcd[3]
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 590 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04h
MOV write_16210,A
MOV A,_lcd[3]
MOV write_16211,A
CALL _write_1621
#line 591 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,00h
MOV write_16210,A
SWAPA _lcd[4]
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 592 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,058h
MOV write_16210,A
MOV A,_lcd[4]
MOV write_16211,A
CALL _write_1621
#line 593 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,054h
MOV write_16210,A
SWAPA _lcd[5]
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 594 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,050h
MOV write_16210,A
MOV A,_lcd[5]
MOV write_16211,A
CALL _write_1621
#line 595 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 597 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,044h
MOV write_16210,A
SWAPA _lcd[6]
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 598 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,040h
MOV write_16210,A
MOV A,_lcd[6]
MOV write_16211,A
CALL _write_1621
#line 599 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,03ch
MOV write_16210,A
SWAPA _lcd[7]
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 600 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,038h
MOV write_16210,A
MOV A,_lcd[7]
MOV write_16211,A
CALL _write_1621
#line 601 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,028h
MOV write_16210,A
SWAPA _lcd[8]
AND A,0FH
MOV b0_9,A
MOV A,b0_9
MOV write_16211,A
CALL _write_1621
#line 602 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,02ch
MOV write_16210,A
MOV A,_lcd[8]
MOV write_16211,A
CALL _write_1621
#line 603 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
#line 605 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,024h
MOV write_16210,A
MOV A,_lcdt
MOV write_16211,A
CALL _write_1621
#line 606 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,04ch
MOV write_16210,A
MOV A,_lcdt[1]
MOV write_16211,A
CALL _write_1621
#line 607 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,048h
MOV write_16210,A
MOV A,_lcdt[2]
MOV write_16211,A
CALL _write_1621
#line 608 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,030h
MOV write_16210,A
MOV A,_lcdt[3]
MOV write_16211,A
CALL _write_1621
#line 609 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,034h
MOV write_16210,A
MOV A,_lcdt[4]
MOV write_16211,A
CALL _write_1621
#line 610 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR WDT
L78:
L68:
#line 264 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 23 1 ; 264 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L67
L42:
#line 613 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP $
LOCAL b0_9 DB 4 DUP(?)
LOCAL b1_9 DB ?
_main ENDP
#line 619 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@sendaddr_1621 .SECTION 'CODE'
PUBLIC _sendaddr_1621
_sendaddr_1621 PROC
#pragma debug scope 80 1
#line 618 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC sendaddr_16210
LOCAL sendaddr_16210 DB ? ; data
#pragma debug variable 8 80 sendaddr_16210 data
#line 618 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC sendaddr_16211
LOCAL sendaddr_16211 DB ? ; cnt
#pragma debug variable 8 80 sendaddr_16211 cnt
#pragma debug scope 80 1 ; 621 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 621 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR CR3
#line 621 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L263
L260:
#pragma debug scope 81 80 ; 623 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 623 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ sendaddr_16210.7
JMP L264
#line 624 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].3
#line 624 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L265
L264:
#line 626 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].3
L265:
#line 627 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].5
#line 628 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
NOP
#line 629 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].5
#line 630 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [0AH].0
RLC sendaddr_16210
L261:
#line 621 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 80 1 ; 621 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC CR3
L263:
#line 621 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR3
SUB A,sendaddr_16211
SNZ [0ah].0
JMP L260
L259:
RET
#line 620 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
LOCAL CR3 DB ? ; i
#pragma debug variable 8 80 CR3 i
_sendaddr_1621 ENDP
#line 635 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@senddata_1621 .SECTION 'CODE'
PUBLIC _senddata_1621
_senddata_1621 PROC
#pragma debug scope 82 1
#line 634 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC senddata_16210
LOCAL senddata_16210 DB ? ; data
#pragma debug variable 8 82 senddata_16210 data
#line 634 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC senddata_16211
LOCAL senddata_16211 DB ? ; cnt
#pragma debug variable 8 82 senddata_16211 cnt
#pragma debug scope 82 1 ; 637 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 637 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR CR4
#line 637 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L270
L267:
#pragma debug scope 83 82 ; 639 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 639 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ senddata_16210.0
JMP L271
#line 640 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].3
#line 640 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L272
L271:
#line 642 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].3
L272:
#line 643 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].5
#line 644 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
NOP
#line 645 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].5
#line 646 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [0AH].0
RRC senddata_16210
L268:
#line 637 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 82 1 ; 637 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC CR4
L270:
#line 637 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR4
SUB A,senddata_16211
SNZ [0ah].0
JMP L267
L266:
RET
#line 636 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
LOCAL CR4 DB ? ; i
#pragma debug variable 8 82 CR4 i
_senddata_1621 ENDP
#line 651 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@sendcmd .SECTION 'CODE'
PUBLIC _sendcmd
_sendcmd PROC
#pragma debug scope 84 1
#line 650 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC sendcmd0
LOCAL sendcmd0 DB ? ; command
#pragma debug variable 8 84 sendcmd0 command
#pragma debug scope 84 1 ; 652 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 652 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].4
#line 653 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,080h
MOV sendaddr_16210,A
MOV A,04h
MOV sendaddr_16211,A
CALL _sendaddr_1621
#line 654 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,sendcmd0
MOV sendaddr_16210,A
MOV A,08h
MOV sendaddr_16211,A
CALL _sendaddr_1621
#line 655 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].4
L273:
RET
_sendcmd ENDP
#line 659 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@write_1621 .SECTION 'CODE'
PUBLIC _write_1621
_write_1621 PROC
#pragma debug scope 85 1
#line 658 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC write_16210
LOCAL write_16210 DB ? ; addr
#pragma debug variable 8 85 write_16210 addr
#line 658 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC write_16211
LOCAL write_16211 DB ? ; data
#pragma debug variable 8 85 write_16211 data
#pragma debug scope 85 1 ; 660 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 660 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].4
#line 661 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0a0h
MOV sendaddr_16210,A
MOV A,03h
MOV sendaddr_16211,A
CALL _sendaddr_1621
#line 662 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,write_16210
MOV sendaddr_16210,A
MOV A,06h
MOV sendaddr_16211,A
CALL _sendaddr_1621
#line 663 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,write_16211
MOV senddata_16210,A
MOV A,04h
MOV senddata_16211,A
CALL _senddata_1621
#line 664 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].4
L274:
RET
_write_1621 ENDP
#line 668 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@writeall_1621 .SECTION 'CODE'
PUBLIC _writeall_1621
_writeall_1621 PROC
#pragma debug scope 86 1
#line 667 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC writeall_16210
LOCAL writeall_16210 DB ? ; addr
#pragma debug variable 8 86 writeall_16210 addr
#line 667 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC writeall_16211
LOCAL writeall_16211 DB ? ; p
#pragma debug variable 19 86 writeall_16211 p
#line 667 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC writeall_16212
LOCAL writeall_16212 DB ? ; cnt
#pragma debug variable 8 86 writeall_16212 cnt
#pragma debug scope 86 1 ; 670 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 670 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].4
#line 671 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0a0h
MOV sendaddr_16210,A
MOV A,03h
MOV sendaddr_16211,A
CALL _sendaddr_1621
#line 672 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,writeall_16210
MOV sendaddr_16210,A
MOV A,06h
MOV sendaddr_16211,A
CALL _sendaddr_1621
#line 673 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR CR5
#line 673 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L279
L276:
#pragma debug scope 87 86 ; 675 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 675 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,writeall_16211
MOV [01H],A
MOV A,[00H]
MOV b0_14,A
MOV A,b0_14
MOV senddata_16210,A
MOV A,08h
MOV senddata_16211,A
CALL _senddata_1621
L277:
#line 673 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 86 1 ; 673 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC CR5
INC writeall_16211
L279:
#line 673 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR5
SUB A,writeall_16212
SNZ [0ah].0
JMP L276
#line 677 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].4
L275:
RET
LOCAL b0_14 DB ?
#line 669 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
LOCAL CR5 DB ? ; i
#pragma debug variable 8 86 CR5 i
_writeall_1621 ENDP
#line 687 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICStart .SECTION 'CODE'
PUBLIC _IICStart
_IICStart PROC
#pragma debug scope 88 1 ; 688 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 688 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 689 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 690 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].2
#line 691 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 692 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [014H].5
#line 693 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 694 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].2
#line 695 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 696 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 697 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
L280:
RET
_IICStart ENDP
#line 706 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICStop .SECTION 'CODE'
PUBLIC _IICStop
_IICStop PROC
#pragma debug scope 89 1 ; 707 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 707 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 708 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 709 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].2
#line 710 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 711 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [014H].5
#line 712 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 713 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].2
#line 714 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
L281:
RET
_IICStop ENDP
#line 723 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICTxAct .SECTION 'CODE'
PUBLIC _IICTxAct
_IICTxAct PROC
#pragma debug scope 90 1 ; 724 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 724 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 725 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 726 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].2
#line 727 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 728 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [014H].5
#line 729 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 730 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 731 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 732 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].2
#line 733 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
L282:
RET
_IICTxAct ENDP
#line 742 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICTxNoAct .SECTION 'CODE'
PUBLIC _IICTxNoAct
_IICTxNoAct PROC
#pragma debug scope 91 1 ; 743 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 743 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 744 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 745 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].2
#line 746 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 747 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [014H].5
#line 748 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
L283:
RET
_IICTxNoAct ENDP
#line 757 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICCRCAct .SECTION 'CODE'
PUBLIC _IICCRCAct
_IICCRCAct PROC
#pragma debug scope 92 1 ; 758 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 758 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR CR6
#line 759 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [018H].2
#line 760 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 761 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 762 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [014H].5
#line 763 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 763 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L286
L285:
#pragma debug scope 93 92 ; 766 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 766 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC CR6
#line 767 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR6
XOR A,0ffh
SNZ [0AH].2
JMP L288
#line 767 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L287
L288:
L286:
#line 764 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 92 1 ; 764 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SZ [017H].2
JMP L285
L287:
#line 769 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 770 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [018H].2
#line 771 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 772 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR6
SUB A,0ffh
SZ [0AH].0
JMP L290
#line 773 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,00h
#line 773 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L284
L290:
#line 775 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
L284:
RET
#line 758 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
LOCAL CR6 DB ? ; Temp
#pragma debug variable 8 92 CR6 Temp
_IICCRCAct ENDP
#line 784 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICWriteByte .SECTION 'CODE'
PUBLIC _IICWriteByte
_IICWriteByte PROC
#pragma debug scope 94 1
#line 783 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC IICWriteByte0
LOCAL IICWriteByte0 DB ? ; Data
#pragma debug variable 8 94 IICWriteByte0 Data
#pragma debug scope 94 1 ; 786 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 786 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR CR7
#line 786 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L296
L293:
#pragma debug scope 95 94 ; 788 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 788 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ IICWriteByte0.7
JMP L297
#line 789 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [017H].2
#line 789 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L298
L297:
#line 791 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [017H].2
L298:
#line 792 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 793 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [014H].5
#line 794 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 795 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 796 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 797 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [0AH].0
RLC IICWriteByte0
L294:
#line 786 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 94 1 ; 786 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC CR7
L296:
#line 786 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR7
SUB A,08h
SNZ [0ah].0
JMP L293
L292:
RET
#line 785 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
LOCAL CR7 DB ? ; Temp
#pragma debug variable 8 94 CR7 Temp
_IICWriteByte ENDP
#line 807 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICReadByte .SECTION 'CODE'
PUBLIC _IICReadByte
_IICReadByte PROC
#pragma debug scope 96 1 ; 808 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 808 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR CR8
#line 809 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR CR9
#line 809 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L303
L300:
#pragma debug scope 97 96 ; 811 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 811 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [018H].2
#line 812 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 813 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [0AH].0
RLC CR8
#line 814 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SNZ [017H].2
JMP L304
#line 815 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC CR8
L304:
#line 816 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
SET [014H].5
#line 817 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 818 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [014H].5
#line 819 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
L301:
#line 809 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#pragma debug scope 96 1 ; 809 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
INC CR9
L303:
#line 809 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR9
SUB A,08h
SNZ [0ah].0
JMP L300
#line 821 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR [018H].2
#line 822 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,023h
MOV delay10,A
CALL _delay1
#line 823 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR8
L299:
RET
#line 808 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
LOCAL CR8 DB ? ; Data
#pragma debug variable 8 96 CR8 Data
#line 808 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
LOCAL CR9 DB ? ; Temp
#pragma debug variable 8 96 CR9 Temp
_IICReadByte ENDP
#line 833 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICWriteByteAt .SECTION 'CODE'
PUBLIC _IICWriteByteAt
_IICWriteByteAt PROC
#pragma debug scope 98 1
#line 832 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC IICWriteByteAt0
LOCAL IICWriteByteAt0 DB ? ; Address
#pragma debug variable 8 98 IICWriteByteAt0 Address
#line 832 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC IICWriteByteAt1
LOCAL IICWriteByteAt1 DB ? ; Data
#pragma debug variable 8 98 IICWriteByteAt1 Data
#pragma debug scope 98 1 ; 835 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 835 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CLR CR10
#line 836 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICStart
#line 837 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0a0h
MOV IICWriteByte0,A
CALL _IICWriteByte
#line 838 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICCRCAct
MOV b0_22,A
MOV A,b0_22
XOR A,01h
SNZ [0ah].2
JMP L307
#line 839 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
#line 839 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L306
L307:
#line 840 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,IICWriteByteAt0
MOV IICWriteByte0,A
CALL _IICWriteByte
#line 841 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICCRCAct
MOV b0_22,A
MOV A,b0_22
XOR A,01h
SNZ [0ah].2
JMP L309
#line 842 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
#line 842 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L306
L309:
#line 844 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,IICWriteByteAt1
MOV IICWriteByte0,A
CALL _IICWriteByte
#line 845 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICCRCAct
MOV b0_22,A
MOV A,b0_22
XOR A,01h
SNZ [0ah].2
JMP L311
#line 846 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
MOV CR10,A
L311:
#line 847 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICStop
#line 848 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,CR10
L306:
RET
LOCAL b0_22 DB ?
#line 834 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
LOCAL CR10 DB ? ; i1
#pragma debug variable 8 98 CR10 i1
_IICWriteByteAt ENDP
#line 858 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@IICReadByteAt .SECTION 'CODE'
PUBLIC _IICReadByteAt
_IICReadByteAt PROC
#pragma debug scope 99 1
#line 857 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC IICReadByteAt0
LOCAL IICReadByteAt0 DB ? ; Address
#pragma debug variable 8 99 IICReadByteAt0 Address
#line 857 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
PUBLIC IICReadByteAt1
LOCAL IICReadByteAt1 DB ? ; Data
#pragma debug variable 19 99 IICReadByteAt1 Data
#pragma debug scope 99 1 ; 860 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
#line 860 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICStart
#line 861 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0a0h
MOV IICWriteByte0,A
CALL _IICWriteByte
#line 862 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICCRCAct
MOV b0_23,A
MOV A,b0_23
XOR A,01h
SNZ [0ah].2
JMP L314
#line 863 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
#line 863 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L313
L314:
#line 864 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,IICReadByteAt0
MOV IICWriteByte0,A
CALL _IICWriteByte
#line 865 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICCRCAct
MOV b0_23,A
MOV A,b0_23
XOR A,01h
SNZ [0ah].2
JMP L316
#line 866 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
#line 866 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L313
L316:
#line 867 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICStart
#line 868 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,0a1h
MOV IICWriteByte0,A
CALL _IICWriteByte
#line 869 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICCRCAct
MOV b0_23,A
MOV A,b0_23
XOR A,01h
SNZ [0ah].2
JMP L318
#line 870 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,01h
#line 870 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
JMP L313
L318:
#line 872 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICReadByte
MOV b0_23,A
MOV A,IICReadByteAt1
MOV [01H],A
MOV A,b0_23
MOV [00H],A
#line 873 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICTxNoAct
#line 874 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
CALL _IICStop
#line 875 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
MOV A,00h
L313:
RET
LOCAL b0_23 DB ?
_IICReadByteAt ENDP
PUBLIC _adaverv_32u
@adaverv_32u .SECTION 'DATA'
#line 28 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_adaverv_32u DB 4 DUP (?) ; adaverv_32u
#pragma debug variable 14 1 _adaverv_32u adaverv_32u
PUBLIC _adsumv_32u
@adsumv_32u .SECTION 'DATA'
#line 28 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_adsumv_32u DB 4 DUP (?) ; adsumv_32u
#pragma debug variable 14 1 _adsumv_32u adsumv_32u
PUBLIC _hour_32u
@hour_32u .SECTION 'DATA'
#line 28 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_hour_32u DB 4 DUP (?) ; hour_32u
#pragma debug variable 14 1 _hour_32u hour_32u
PUBLIC _lcdt
@lcdt .SECTION 'DATA'
#line 27 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_lcdt DB 5 DUP (?) ; lcdt
#pragma debug array 42 8 5 1 _lcdt lcdt
PUBLIC _lcd
@lcd .SECTION 'DATA'
#line 27 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_lcd DB 9 DUP (?) ; lcd
#pragma debug array 43 8 9 1 _lcd lcd
PUBLIC _step3_16u
@step3_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_step3_16u DB 2 DUP (?) ; step3_16u
#pragma debug variable 12 1 _step3_16u step3_16u
PUBLIC _step2_16u
@step2_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_step2_16u DB 2 DUP (?) ; step2_16u
#pragma debug variable 12 1 _step2_16u step2_16u
PUBLIC _step1_16u
@step1_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_step1_16u DB 2 DUP (?) ; step1_16u
#pragma debug variable 12 1 _step1_16u step1_16u
PUBLIC _voltagebak_16u
@voltagebak_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_voltagebak_16u DB 2 DUP (?) ; voltagebak_16u
#pragma debug variable 12 1 _voltagebak_16u voltagebak_16u
PUBLIC _voltage_16u
@voltage_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_voltage_16u DB 2 DUP (?) ; voltage_16u
#pragma debug variable 12 1 _voltage_16u voltage_16u
PUBLIC _adibak_16u
@adibak_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_adibak_16u DB 2 DUP (?) ; adibak_16u
#pragma debug variable 12 1 _adibak_16u adibak_16u
PUBLIC _current_16u
@current_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_current_16u DB 2 DUP (?) ; current_16u
#pragma debug variable 12 1 _current_16u current_16u
PUBLIC _min_16u
@min_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_min_16u DB 2 DUP (?) ; min_16u
#pragma debug variable 12 1 _min_16u min_16u
PUBLIC _adaveri_16u
@adaveri_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_adaveri_16u DB 2 DUP (?) ; adaveri_16u
#pragma debug variable 12 1 _adaveri_16u adaveri_16u
PUBLIC _adsumi_16u
@adsumi_16u .SECTION 'DATA'
#line 26 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_adsumi_16u DB 2 DUP (?) ; adsumi_16u
#pragma debug variable 12 1 _adsumi_16u adsumi_16u
PUBLIC _cnt5s
@cnt5s .SECTION 'DATA'
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_cnt5s DB ? ; cnt5s
#pragma debug variable 8 1 _cnt5s cnt5s
PUBLIC _mode
@mode .SECTION 'DATA'
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_mode DB ? ; mode
#pragma debug variable 8 1 _mode mode
PUBLIC _lcdtemp
@lcdtemp .SECTION 'DATA'
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_lcdtemp DB ? ; lcdtemp
#pragma debug variable 8 1 _lcdtemp lcdtemp
PUBLIC _adnumi
@adnumi .SECTION 'DATA'
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_adnumi DB ? ; adnumi
#pragma debug variable 8 1 _adnumi adnumi
PUBLIC _adnumv
@adnumv .SECTION 'DATA'
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_adnumv DB ? ; adnumv
#pragma debug variable 8 1 _adnumv adnumv
PUBLIC _cnt500ms
@cnt500ms .SECTION 'DATA'
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_cnt500ms DB ? ; cnt500ms
#pragma debug variable 8 1 _cnt500ms cnt500ms
PUBLIC _k
@k .SECTION 'DATA'
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_k DB ? ; k
#pragma debug variable 8 1 _k k
PUBLIC _j
@j .SECTION 'DATA'
#line 25 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_j DB ? ; j
#pragma debug variable 8 1 _j j
BITDATASEC .SECTION 'DATA'
PUBLIC _f_vlow
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_f_vlow DBIT ; f_vlow
#pragma debug variable 2 1 _f_vlow f_vlow
PUBLIC _f_telephone
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_f_telephone DBIT ; f_telephone
#pragma debug variable 2 1 _f_telephone f_telephone
PUBLIC _f_saodiche
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_f_saodiche DBIT ; f_saodiche
#pragma debug variable 2 1 _f_saodiche f_saodiche
PUBLIC _f_save
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_f_save DBIT ; f_save
#pragma debug variable 2 1 _f_save f_save
PUBLIC _f_poweroff
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_f_poweroff DBIT ; f_poweroff
#pragma debug variable 2 1 _f_poweroff f_poweroff
PUBLIC _f_adflag
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_f_adflag DBIT ; f_adflag
#pragma debug variable 2 1 _f_adflag f_adflag
PUBLIC _f_flash
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_f_flash DBIT ; f_flash
#pragma debug variable 2 1 _f_flash f_flash
PUBLIC _f_500ms
#line 24 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
_f_500ms DBIT ; f_500ms
#pragma debug variable 2 1 _f_500ms f_500ms
#line 175 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
STARTSEC .SECTION  COM_L 'CODE'
STARTUP:
STARTSEC .SECTION  COM_E 'CODE'
RET
EXTERN RH:BYTE
EXTERN RM:BYTE
EXTERN RU:BYTE
EXTERN T2:BYTE
EXTERN T3:BYTE
EXTERN T4:BYTE
EXTERN T5:BYTE
EXTERN T6:BYTE
EXTERN T7:BYTE
EXTERN T8:BYTE
EXTERN T9:BYTE
EXTERN T10:BYTE
EXTERN T11:BYTE
EXTERN T12:BYTE
EXTERN T13:BYTE
EXTERN V2A:BYTE
EXTERN V2S:BYTE
EXTERN MULL4:NEAR
EXTERN DIVUL:NEAR
EXTERN DIVUL4:NEAR
EXTERN __DELAYX0:NEAR
EXTERN __DELAYX1:NEAR
EXTERN __DELAYX2:NEAR
EXTERN __DELAYX3:NEAR
EXTERN __DELAYX4:NEAR
EXTERN __DELAYX5:NEAR
EXTERN __DELAYX6:NEAR
EXTERN __DELAYY0:NEAR
EXTERN __DELAYY1:NEAR
EXTERN __DELAYY2:NEAR
EXTERN __DELAYY3:NEAR
EXTERN __DELAYY4:NEAR
EXTERN __DELAYY5:NEAR
#line 175 "C:\Users\Eason\Desktop\test_1621_46r065\Dispay Code-46R065 16NSOP.c"
@CODE .SECTION AT 0 'CODE'
CALL STARTUP
JMP begin
@DUMMY PROC
CALL _main
@DUMMY ENDP
