	;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	;�ֽڵ�ַ����
	;0C\0D\0E\4λ�ֱ��Ӧ������3λ�ɸ�λ����λ
	;10H,11H,12H��Ӧ��ѹ��3����ֵ
	;13H,14H,15H,16H,17H��Ӧ���ʵ�5����ֵ
	;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	P1ASF	EQU	9DH	;P1�����üĴ���
	ADC_CONTOR	EQU	BCH	;ADC���ƼĴ���
	ADC_RES	EQU	BDH	;ADC�����8λ
	ADC_RESL	EQU	BEH	;ADC��8Ϊ���
	AUXR1	EQU	A2H	;���üĴ���
	IJISHU	EQU	30H	;�����Ƚϴ�������
	UJISHU	EQU	31H	;��ѹ�Ƚϴ�������
	IL	EQU	32H	;������λ
	IH	EQU	33H	;������λ
	UL	EQU	34H	;��ѹ��λ
	UH	EQU	35H	;��ѹ��λ
	RS	BIT	P2.5	;����RSΪP2.5
	RW	BIT	P2.6	;����RWΪP2.6
	E	BIT	P2.7	;����EΪP2.7
	ORG	0000H
	LJMP	START
	ORG	002BH
START:	MOV	P1ASF,#00000011B	;����P1.0��P1.1��ΪAD������˿�
	MOV	AUXR1,#04H	;����AD�����ʽ
	MOV	SP,#5FH	;����ջ��
	MOV	IJISHU,#00H
	MOV	UJISHU,#00H
	;��������������������������������������������������
LCD:	MOV	P0,#38H	;���ù���
	LCALL	XML
	MOV	P0,#38H	;���ù���
	LCALL	XML
	MOV	P0,#01H	;�����Ļ
	LCALL	XML
	MOV	P0,#0CH	;������ʾ����,����
	LCALL	XML
	MOV	P0,#1CH	;����
	LCALL	XML
	;������������������������������������������������������
	;������
	;--------------------------------------------------------------------------------------------------
MAIN:	MOV	ADC_CONTOR,#11001001B	;����P1.1��ADת��,����
	LCALL	AD	;����AD�ӳ���
	MOV	A,ADC_RES
	CJNE	A,IH,MAINI
	MOV	A,ADC_RESL
	CJNE	A,IL,MAINI
	MOV	IJISHU,#00H
	SJMP	MAINI1
MAINI:	INC	IJISHU
	MOV	A,#20
	CJNE	A,IJISHU,MAINI1
	MOV	IJISHU,#00H
	MOV	IH,ADC_RES	;�����������
	MOV	IL,ADC_RESL
MAINI1:	MOV	0AH,IH
	MOV	0BH,IL
	LCALL	2TO10
	MOV	0CH,18H
	MOV	0DH,19H
	MOV	0EH,1AH
	MOV	A,0AH
	RRC	A
	MOV	0AH,A
	MOV	A,0BH
	RRC	A
	MOV	0BH,A
	MOV	A,0AH
	RRC	A
	MOV	A,0BH
	RRC	A
	MOV	09H,A	;09H����8λ��������
	MOV	ADC_CONTOR,#11001000B	;����P1.0��ADת��	��ѹ
	LCALL	AD	;����AD�ӳ���
	MOV	A,ADC_RES
	CJNE	A,UH,MAINU
	MOV	A,ADC_RESL
	CJNE	A,UL,MAINU
	MOV	UJISHU,#00H
	SJMP	MAINU1
MAINU:	INC	UJISHU
	MOV	A,#20
	CJNE	A,UJISHU,MAINU1
	MOV	UJISHU,#00H
	MOV	UH,ADC_RES	;�����ѹ����
	MOV	UL,ADC_RESL
MAINU1:	MOV	0AH,UH
	MOV	0BH,UL
	LCALL	2TO10
	MOV	10H,18H
	MOV	11H,19H
	MOV	12H,1AH
	MOV	A,0AH
	RRC	A
	MOV	0AH,A
	MOV	A,0BH
	RRC	A
	MOV	0BH,A
	MOV	A,0AH
	RRC	A
	MOV	A,0BH
	RRC	A
	MOV	08H,A	;08H����8λ��ѹ����
	MOV	B,09H
	MUL	AB
	MOV	R2,B
	MOV	R3,A
	MOV	R4,#61H	;/25000
	MOV	R5,#A8H
	LCALL	DIVD
	MOV	A,R7
	ADD	A,#30H
	MOV	13H,A
	MOV	R4,#09H
	MOV	R5,#C4H	;/2500
	LCALL	DIVD
	MOV	A,R7
	ADD	A,#30H
	MOV	14H,A
	MOV	R4,#00H
	MOV	R5,#250	;/250
	LCALL	DIVD
	MOV	A,R7
	ADD	A,#30H
	MOV	15H,A
	MOV	R4,#00H
	MOV	R5,#25	;/25
	LCALL	DIVD
	MOV	A,R7
	ADD	A,#30H
	MOV	16H,A
	MOV	A,R3
	CLR	C
	RLC	A
	CLR	C
	RLC	A
	MOV	R3,A
	MOV	R5,#10
	LCALL	DIVD
	MOV	A,R7
	ADD	A,#30H
	MOV	17H,A
	LCALL	XIANSHI
	LJMP	MAIN
	;����������������������������������������������������������������������������������������������������������������������
	;ADת���ӳ���
	;����������������������������������������������������������������������������������������������������������������������
AD:	MOV	A,ADC_CONTOR
	JNB	E4H,AD
	CLR	E4H
	MOV	ADC_CONTOR,A
	;����������������������������������������������������������������������������������������������������������������������
	;��-ʮ����ת���ӳ���,ͬʱ�ӱ��������1602��0-9��ģ��ַ��ת��	������18H	19H	1AH
	;����������������������������������������������������������������������������������������������������������������������
2TO10:	MOV	R2,0AH
	MOV	R3,0BH
	MOV	R4,#0
	MOV	R5,#2
	LCALL	DIVD
	MOV	A,R6
	MOV	R2,A
	MOV	A,R7
	MOV	R3,A
	MOV	R4,#00H
	MOV	R5,#100
	LCALL	DIVD
	MOV	18H,R7
	MOV	A,#30H
	ADD	A,18H
	MOV	18H,A
	MOV	R5,#10
	LCALL	DIVD
	MOV	19H,R7
	MOV	A,#30H
	ADD	A,19H
	MOV	19H,A
	MOV	1AH,R3
	MOV	A,#30H
	ADD	A,1AH
	MOV	1AH,A
	RET
	;������������������������������������������������������������������������������������������������������
	;˫�ֽڳ��������ӳ���
	;�������:	��������R2��R3��������R4��R5��,����R6��R7�С�R1���ڼ���λ����
	;������Ϣ:	������R2��R3��,˫�ֽ�����R4��R5��,OV=1	ʱ�����
	;Ӱ����Դ:	PSW��A��R1��R7
	;����������������������������������������������������������������������������������������������������������������
DIVD:	PUSH	A
	PUSH	PSW
	MOV	R1,#00H	;����������
	MOV	R6,#00H
	MOV	R7,#00H
	LCALL	SUBBD	;�жϹ�������
	JC	DIVDE
DIVD1:	MOV	A,R4
	JB	ACC.7,DIVD3	;�ж����λ�ǲ���1
	CLR	C	;��������һλ
	MOV	A,R5	
	RLC	A
	MOV	R5,A
	MOV	A,R4
	RLC	A
	MOV	R4,A
	INC	R1	;���Ƽ���������
	LCALL	SUBBD	;�Ƚ����ƺ󹻲�����
	JNC	DIVD1	;����ת��,����������
	LCALL	DIVDR	;��������һλ
	DEC	R1	;������,����Ҫ-1
DIVD3:	CLR	C
	MOV	A,R3	;��ʼ����
	SUBB	A,R5
	MOV	R3,A
	MOV	A,R2
	SUBB	A,R4
	MOV	R2,A
	INC	R7
DIVD4:	CJNE	R1,#00H,DIVD5	;�ж��ǲ��ǵ����һλ��
	SJMP	DIVDE
DIVD5:	LCALL	DIVDR	;��������һλ
	MOV	A,R7
	CLR	C
	RLC	A
	MOV	R7,A
	MOV	A,R6
	RLC	A
	MOV	R6,A
	DEC	R1	;λ�ü�����-1
	LCALL	SUBBD	;�ȽϹ�������
	JC	DIVD4
	SJMP	DIVD3
SUBBD:	CLR	C	;�жϹ��������ӳ���
	MOV	A,R3
	SUBB	A,R5
	MOV	A,R2
	SUBB	A,R4
	RET
DIVDR:	CLR	C
	MOV	A,R4
	RRC	A
	MOV	R4,A
	MOV	A,R5
	RRC	A
	MOV	R5,A
	RET
DIVDE:	SETB	OV
	POP	PSW
	POP	A
	RET
	;��������������������������������������������������������������������������������������������������������������������
	;��ʾ����
	;��������������������������������������������������������������������������������������������������������������������
XIANSHI:	MOV	P0,#80H	
	LCALL	XML
	MOV	P0,#55H	;��ѹ���֣�10H,11H,12HΪ��ѹ����λ��ֵ��
	LCALL	XSJ
	MOV	P0,#3DH
	LCALL	XSJ
	MOV	A,#30H
	CJNE	A,10H,DYXY
	MOV	P0,#20H
	SJMP	DYXY1
DYXY:	MOV	P0,10H	;��ѹ���λ��ʾ0ʱ����
DYXY1:	LCALL	XSJ
	MOV	P0,11H
	LCALL	XSJ
	MOV	P0,#2EH
	LCALL	XSJ
	MOV	P0,12H
	LCALL	XSJ
	MOV	P0,#76H
	LCALL	XSJ
	MOV	P0,#20H	;�������֣�0CH,0DH,0EH��Ӧ������3����ֵ��
	LCALL	XSJ
	MOV	P0,#49H
	LCALL	XSJ
	MOV	P0,#3DH
	LCALL	XSJ
	MOV	P0,0CH
	LCALL	XSJ
	MOV	P0,#2EH
	LCALL	XSJ
	MOV	P0,0DH
	LCALL	XSJ
	MOV	P0,0EH
	LCALL	XSJ
	MOV	P0,#41H
	LCALL	XSJ
	MOV	P0,#C0H	;���ʲ��֣�13H,14H,15H,16H,17H��Ӧ���ʵ�5����ֵ��
	LCALL	XML
	MOV	P0,#50H
	LCALL	XSJ
	MOV	P0,#3DH
	LCALL	XSJ
	MOV	P0,13H
	LCALL	XSJ
	MOV	P0,14H
	LCALL	XSJ
	MOV	P0,15H
	LCALL	XSJ
	MOV	P0,#2EH
	LCALL	XSJ
	MOV	P0,16H
	LCALL	XSJ
	MOV	P0,17H
	LCALL	XSJ
	MOV	P0,#57H
	LCALL	XSJ
	RET
	;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	;д�����ӳ���
	;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XML:	CLR	RS
	CLR	RW
	SETB	E
	NOP
	NOP
	CLR	E
	LCALL	WEAT	
	RET
	;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	;д�����ӳ���
	;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XSJ:	SETB	RS
	CLR	RW
	SETB	E
	NOP
	NOP
	CLR	E
	LCALL	WEAT	
	RET
	;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	;�ȴ��ӳ���
	;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
WEAT:	SETB	RW
	CLR	RS
	SETB	E
	MOV	P0,#FFH
WEAT1:	JB	P0.7,WEAT1
	CLR	E
	RET
	END

