   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.9.2 - 29 Jun 2010
   3                     ; Generator V4.3.5 - 02 Jul 2010
2878                     ; 52 void delay_ms(u16 ms)
2878                     ; 53 {
2880                     	switch	.text
2881  0000               _delay_ms:
2883  0000 89            	pushw	x
2884  0001 88            	push	a
2885       00000001      OFST:	set	1
2888  0002 201b          	jra	L5302
2889  0004               L3302:
2890                     ; 57 				for(i=0;i<250;i++)
2892  0004 0f01          	clr	(OFST+0,sp)
2893  0006               L1402:
2896  0006 0c01          	inc	(OFST+0,sp)
2899  0008 7b01          	ld	a,(OFST+0,sp)
2900  000a a1fa          	cp	a,#250
2901  000c 25f8          	jrult	L1402
2902                     ; 59 				for(i=0;i<75;i++)
2904  000e 0f01          	clr	(OFST+0,sp)
2905  0010               L7402:
2908  0010 0c01          	inc	(OFST+0,sp)
2911  0012 7b01          	ld	a,(OFST+0,sp)
2912  0014 a14b          	cp	a,#75
2913  0016 25f8          	jrult	L7402
2914                     ; 61 				ms--;
2916  0018 1e02          	ldw	x,(OFST+1,sp)
2917  001a 1d0001        	subw	x,#1
2918  001d 1f02          	ldw	(OFST+1,sp),x
2919  001f               L5302:
2920                     ; 55 			while(ms!=0)
2922  001f 1e02          	ldw	x,(OFST+1,sp)
2923  0021 26e1          	jrne	L3302
2924                     ; 63 }
2927  0023 5b03          	addw	sp,#3
2928  0025 81            	ret
2971                     ; 65 void delay_us(u16 us)
2971                     ; 66 {
2972                     	switch	.text
2973  0026               _delay_us:
2975  0026 89            	pushw	x
2976  0027 88            	push	a
2977       00000001      OFST:	set	1
2980  0028 201b          	jra	L1012
2981  002a               L7702:
2982                     ; 70 				for(i=0;i<25;i++)
2984  002a 0f01          	clr	(OFST+0,sp)
2985  002c               L5012:
2988  002c 0c01          	inc	(OFST+0,sp)
2991  002e 7b01          	ld	a,(OFST+0,sp)
2992  0030 a119          	cp	a,#25
2993  0032 25f8          	jrult	L5012
2994                     ; 72 				for(i=0;i<7;i++)
2996  0034 0f01          	clr	(OFST+0,sp)
2997  0036               L3112:
3000  0036 0c01          	inc	(OFST+0,sp)
3003  0038 7b01          	ld	a,(OFST+0,sp)
3004  003a a107          	cp	a,#7
3005  003c 25f8          	jrult	L3112
3006                     ; 74 				us--;
3008  003e 1e02          	ldw	x,(OFST+1,sp)
3009  0040 1d0001        	subw	x,#1
3010  0043 1f02          	ldw	(OFST+1,sp),x
3011  0045               L1012:
3012                     ; 68 			while(us!=0)
3014  0045 1e02          	ldw	x,(OFST+1,sp)
3015  0047 26e1          	jrne	L7702
3016                     ; 76 }
3019  0049 5b03          	addw	sp,#3
3020  004b 81            	ret
3066                     ; 18 void I2C_Init(void)
3066                     ; 19 {
3067                     	switch	.text
3068  004c               _I2C_Init:
3072                     ; 20 		I2C_FREQR=0x0f;    //设置频率寄存器
3074  004c 350f5212      	mov	_I2C_FREQR,#15
3075                     ; 21 		I2C_CCRH=0x00;     //设置始终寄存器高位
3077  0050 725f521c      	clr	_I2C_CCRH
3078                     ; 22 		I2C_CCRL=0x50;     //设置始终寄存器低位
3080  0054 3550521b      	mov	_I2C_CCRL,#80
3081                     ; 23 		I2C_TRISER=0x11;   //设置最大SCL上升时间
3083  0058 3511521d      	mov	_I2C_TRISER,#17
3084                     ; 24 		I2C_CR1|=0x01;     //使能I2C模块
3086  005c 72105210      	bset	_I2C_CR1,#0
3087                     ; 25 		I2C_Ack();         //设置匹配应答
3089  0060 72145211      	bset	_I2C_CR2,#2
3090                     ; 26 		I2C_CR2|=0x08;     //设置接收应答
3093  0064 72165211      	bset	_I2C_CR2,#3
3094                     ; 27 }
3097  0068 81            	ret
3123                     ; 30 void I2C_Start(void)
3123                     ; 31 {
3124                     	switch	.text
3125  0069               _I2C_Start:
3129  0069               L1512:
3130                     ; 32 	I2C_busy();
3132  0069 c65219        	ld	a,_I2C_SR3
3133  006c a402          	and	a,#2
3134  006e a101          	cp	a,#1
3135  0070 27f7          	jreq	L1512
3136                     ; 33 	I2C_start();
3139  0072 72105211      	bset	_I2C_CR2,#0
3142  0076               L7512:
3143                     ; 34 	while(I2C_SBask==0);
3145  0076 c65217        	ld	a,_I2C_SR1
3146  0079 a501          	bcp	a,#1
3147  007b 27f9          	jreq	L7512
3148                     ; 35 }
3151  007d 81            	ret
3188                     ; 37 void I2C_SendDAdr(u8 Add)
3188                     ; 38 {
3189                     	switch	.text
3190  007e               _I2C_SendDAdr:
3194                     ; 39 	I2C_writebyte(Add);	
3196  007e c75216        	ld	_I2C_DR,a
3199  0081               L3022:
3200                     ; 40 	while(I2C_addrask==0);
3202  0081 c65217        	ld	a,_I2C_SR1
3203  0084 a502          	bcp	a,#2
3204  0086 27f9          	jreq	L3022
3206  0088               L1122:
3207                     ; 41 	I2C_busy();
3209  0088 c65219        	ld	a,_I2C_SR3
3210  008b a402          	and	a,#2
3211  008d a101          	cp	a,#1
3212  008f 27f7          	jreq	L1122
3213                     ; 42 }
3217  0091 81            	ret
3254                     ; 45 void I2C_SendDat(u8 data)
3254                     ; 46 {
3255                     	switch	.text
3256  0092               _I2C_SendDat:
3260                     ; 47 	I2C_writebyte(data);
3262  0092 c75216        	ld	_I2C_DR,a
3265  0095               L5322:
3266                     ; 48 	I2C_busy();
3268  0095 c65219        	ld	a,_I2C_SR3
3269  0098 a402          	and	a,#2
3270  009a a101          	cp	a,#1
3271  009c 27f7          	jreq	L5322
3274  009e               L3422:
3275                     ; 49 	while(I2C_TxEask==0);
3277  009e c65217        	ld	a,_I2C_SR1
3278  00a1 a580          	bcp	a,#128
3279  00a3 27f9          	jreq	L3422
3280                     ; 50 }
3283  00a5 81            	ret
3319                     ; 52 u8 I2C_RcvDat(void)
3319                     ; 53 {
3320                     	switch	.text
3321  00a6               _I2C_RcvDat:
3323  00a6 88            	push	a
3324       00000001      OFST:	set	1
3327  00a7               L1722:
3328                     ; 55 	while(I2C_RxNeask==0);
3330  00a7 c65217        	ld	a,_I2C_SR1
3331  00aa a540          	bcp	a,#64
3332  00ac 27f9          	jreq	L1722
3333  00ae               L7422:
3334                     ; 56 	abc:
3334                     ; 57 	if(I2C_BTF==0x04)
3336  00ae c65217        	ld	a,_I2C_SR1
3337  00b1 a404          	and	a,#4
3338  00b3 a104          	cp	a,#4
3339  00b5 26f7          	jrne	L7422
3340                     ; 58 	{i=I2C_DR;}
3342  00b7 c65216        	ld	a,_I2C_DR
3343  00ba 6b01          	ld	(OFST+0,sp),a
3345                     ; 60 	if(I2C_BTF==0){}
3347  00bc c65217        	ld	a,_I2C_SR1
3348  00bf a504          	bcp	a,#4
3349  00c1 26eb          	jrne	L7422
3351                     ; 62 	return i;
3353  00c3 7b01          	ld	a,(OFST+0,sp)
3356  00c5 5b01          	addw	sp,#1
3357  00c7 81            	ret
3398                     ; 23 void AT24CXX_Init(void)
3398                     ; 24 {
3399                     	switch	.text
3400  00c8               _AT24CXX_Init:
3404                     ; 25 	I2C_Init();
3406  00c8 ad82          	call	_I2C_Init
3408                     ; 26 }
3411  00ca 81            	ret
3458                     ; 28 void AT24CXX_WriteAByte(u8 wordAdr,u8 dat)
3458                     ; 29 {
3459                     	switch	.text
3460  00cb               _AT24CXX_WriteAByte:
3462  00cb 89            	pushw	x
3463       00000000      OFST:	set	0
3466                     ; 30 	I2C_Start();
3468  00cc ad9b          	call	_I2C_Start
3470                     ; 31 	I2C_SendDAdr(WD_DADR);
3472  00ce a6a0          	ld	a,#160
3473  00d0 adac          	call	_I2C_SendDAdr
3475                     ; 32 	I2C_SendDat(wordAdr);
3477  00d2 7b01          	ld	a,(OFST+1,sp)
3478  00d4 adbc          	call	_I2C_SendDat
3480                     ; 33 	I2C_SendDat(dat);
3482  00d6 7b02          	ld	a,(OFST+2,sp)
3483  00d8 adb8          	call	_I2C_SendDat
3485                     ; 34 	I2C_stop();
3487  00da 72125211      	bset	_I2C_CR2,#1
3488                     ; 35 }
3492  00de 85            	popw	x
3493  00df 81            	ret
3541                     ; 37 u8 AT24CXX_ReadAByte(u8 wordAdr)
3541                     ; 38 {
3542                     	switch	.text
3543  00e0               _AT24CXX_ReadAByte:
3545  00e0 88            	push	a
3546  00e1 88            	push	a
3547       00000001      OFST:	set	1
3550                     ; 40 	I2C_Start();
3552  00e2 ad85          	call	_I2C_Start
3554                     ; 41 	I2C_SendDAdr(WD_DADR);
3556  00e4 a6a0          	ld	a,#160
3557  00e6 ad96          	call	_I2C_SendDAdr
3559                     ; 42 	I2C_SendDat(wordAdr);
3561  00e8 7b02          	ld	a,(OFST+1,sp)
3562  00ea ada6          	call	_I2C_SendDat
3564                     ; 43 	I2C_Start();
3566  00ec cd0069        	call	_I2C_Start
3568                     ; 44 	I2C_NAck();
3570  00ef 72155211      	bres	_I2C_CR2,#2
3571                     ; 45 	I2C_SendDAdr(RD_DADR);
3574  00f3 a6a1          	ld	a,#161
3575  00f5 ad87          	call	_I2C_SendDAdr
3577                     ; 46 	dat=I2C_RcvDat();
3579  00f7 adad          	call	_I2C_RcvDat
3581  00f9 6b01          	ld	(OFST+0,sp),a
3582                     ; 47 	I2C_stop();
3584  00fb 72125211      	bset	_I2C_CR2,#1
3585                     ; 48 	I2C_Ack();
3588  00ff 72145211      	bset	_I2C_CR2,#2
3589                     ; 49 	return dat;
3592  0103 7b01          	ld	a,(OFST+0,sp)
3595  0105 85            	popw	x
3596  0106 81            	ret
3638                     ; 17 void SPI_Init(void)
3638                     ; 18 {
3639                     	switch	.text
3640  0107               _SPI_Init:
3644                     ; 19 	SPI_CR1|=0x38;   //波特率
3646  0107 c65200        	ld	a,_SPI_CR1
3647  010a aa38          	or	a,#56
3648  010c c75200        	ld	_SPI_CR1,a
3649                     ; 24 	SPI_CR2|=0x03;   //配置NSS脚为1
3651  010f c65201        	ld	a,_SPI_CR2
3652  0112 aa03          	or	a,#3
3653  0114 c75201        	ld	_SPI_CR2,a
3654                     ; 25 	SPI_CR1|=0x04;   //配置为主设备
3656  0117 72145200      	bset	_SPI_CR1,#2
3657                     ; 26 	SPI_CR1|=0x40;   //开启SPI
3659  011b 721c5200      	bset	_SPI_CR1,#6
3660                     ; 27 }
3663  011f 81            	ret
3699                     ; 29 void SPI_sendchar(u8 data)
3699                     ; 30 {	
3700                     	switch	.text
3701  0120               _SPI_sendchar:
3705                     ; 31 	SPI_DR=data;
3707  0120 c75204        	ld	_SPI_DR,a
3709  0123               L7242:
3710                     ; 32 	while(!(SPI_SR & 0x02));
3712  0123 c65203        	ld	a,_SPI_SR
3713  0126 a502          	bcp	a,#2
3714  0128 27f9          	jreq	L7242
3715                     ; 33 }
3718  012a 81            	ret
3754                     ; 35 u8 SPI_rechar(void)
3754                     ; 36 {	
3755                     	switch	.text
3756  012b               _SPI_rechar:
3758  012b 88            	push	a
3759       00000001      OFST:	set	1
3762                     ; 38 	data=SPI_DR;
3764  012c c65204        	ld	a,_SPI_DR
3765  012f 6b01          	ld	(OFST+0,sp),a
3767  0131               L5542:
3768                     ; 39 	while(!(SPI_SR & 0x01));
3770  0131 c65203        	ld	a,_SPI_SR
3771  0134 a501          	bcp	a,#1
3772  0136 27f9          	jreq	L5542
3773                     ; 40 	return data;
3775  0138 7b01          	ld	a,(OFST+0,sp)
3778  013a 5b01          	addw	sp,#1
3779  013c 81            	ret
3838                     ; 21 void st7920LcdInit(void)
3838                     ; 22 {
3839                     	switch	.text
3840  013d               _st7920LcdInit:
3842  013d 88            	push	a
3843       00000001      OFST:	set	1
3846                     ; 24 	SPI_Init();
3848  013e adc7          	call	_SPI_Init
3850                     ; 25 	delay_ms(100);
3852  0140 ae0064        	ldw	x,#100
3853  0143 cd0000        	call	_delay_ms
3855                     ; 26 	PE_DDR|=0x20;
3857  0146 721a5016      	bset	_PE_DDR,#5
3858                     ; 27 	PE_CR1|=0x20;
3860  014a 721a5017      	bset	_PE_CR1,#5
3861                     ; 28 	PE_CR2|=0x20;
3863  014e 721a5018      	bset	_PE_CR2,#5
3864                     ; 29 	sendCodeST7920(0x0c);//整体显示
3866  0152 a60c          	ld	a,#12
3867  0154 ad1c          	call	_sendCodeST7920
3869                     ; 30 	sendCodeST7920(0x01);//清屏
3871  0156 a601          	ld	a,#1
3872  0158 ad18          	call	_sendCodeST7920
3874                     ; 31 	sendCodeST7920(0x02);
3876  015a a602          	ld	a,#2
3877  015c ad14          	call	_sendCodeST7920
3879                     ; 32 	for(i=0;i<64;i++)
3881  015e 0f01          	clr	(OFST+0,sp)
3882  0160               L5052:
3883                     ; 33 		lcd_buffer[i]=' ';
3885  0160 7b01          	ld	a,(OFST+0,sp)
3886  0162 5f            	clrw	x
3887  0163 97            	ld	xl,a
3888  0164 a620          	ld	a,#32
3889  0166 e700          	ld	(_lcd_buffer,x),a
3890                     ; 32 	for(i=0;i<64;i++)
3892  0168 0c01          	inc	(OFST+0,sp)
3895  016a 7b01          	ld	a,(OFST+0,sp)
3896  016c a140          	cp	a,#64
3897  016e 25f0          	jrult	L5052
3898                     ; 35 }
3901  0170 84            	pop	a
3902  0171 81            	ret
3939                     ; 37 void sendCodeST7920(u8 Lcd_cmd)
3939                     ; 38 {
3940                     	switch	.text
3941  0172               _sendCodeST7920:
3943  0172 88            	push	a
3944       00000000      OFST:	set	0
3947                     ; 39 	E_CLK
3949  0173 721b5014      	bres	_PE_ODR,#5
3950                     ; 40 	LCD_DELAY()
3953  0177 9d            nop
3958  0178 9d            nop
3963  0179 9d            nop
3968  017a 9d            nop
3973  017b 9d            nop
3975                     ; 41 	E_SET
3977  017c 721a5014      	bset	_PE_ODR,#5
3978                     ; 42 	SPI_sendchar(0xF8);
3980  0180 a6f8          	ld	a,#248
3981  0182 ad9c          	call	_SPI_sendchar
3983                     ; 43 	SPI_sendchar(Lcd_cmd & 0xF0);
3985  0184 7b01          	ld	a,(OFST+1,sp)
3986  0186 a4f0          	and	a,#240
3987  0188 ad96          	call	_SPI_sendchar
3989                     ; 44 	SPI_sendchar(Lcd_cmd << 4);
3991  018a 7b01          	ld	a,(OFST+1,sp)
3992  018c 97            	ld	xl,a
3993  018d a610          	ld	a,#16
3994  018f 42            	mul	x,a
3995  0190 9f            	ld	a,xl
3996  0191 ad8d          	call	_SPI_sendchar
3998                     ; 45 	LCD_DELAY()
4001  0193 9d            nop
4006  0194 9d            nop
4011  0195 9d            nop
4016  0196 9d            nop
4021  0197 9d            nop
4023                     ; 46 	E_CLK
4025  0198 721b5014      	bres	_PE_ODR,#5
4026                     ; 47 	LCD_DELAY()
4029  019c 9d            nop
4034  019d 9d            nop
4039  019e 9d            nop
4044  019f 9d            nop
4049  01a0 9d            nop
4051                     ; 48 }
4054  01a1 84            	pop	a
4055  01a2 81            	ret
4092                     ; 50 void sendDataST7920(u8 Lcd_data)
4092                     ; 51 {
4093                     	switch	.text
4094  01a3               _sendDataST7920:
4096  01a3 88            	push	a
4097       00000000      OFST:	set	0
4100                     ; 52 	E_CLK
4102  01a4 721b5014      	bres	_PE_ODR,#5
4103                     ; 53 	LCD_DELAY()
4106  01a8 9d            nop
4111  01a9 9d            nop
4116  01aa 9d            nop
4121  01ab 9d            nop
4126  01ac 9d            nop
4128                     ; 54 	E_SET
4130  01ad 721a5014      	bset	_PE_ODR,#5
4131                     ; 55 	SPI_sendchar(0xFA);
4133  01b1 a6fa          	ld	a,#250
4134  01b3 cd0120        	call	_SPI_sendchar
4136                     ; 56 	SPI_sendchar(Lcd_data & 0xF0);
4138  01b6 7b01          	ld	a,(OFST+1,sp)
4139  01b8 a4f0          	and	a,#240
4140  01ba cd0120        	call	_SPI_sendchar
4142                     ; 57 	SPI_sendchar(Lcd_data << 4);
4144  01bd 7b01          	ld	a,(OFST+1,sp)
4145  01bf 97            	ld	xl,a
4146  01c0 a610          	ld	a,#16
4147  01c2 42            	mul	x,a
4148  01c3 9f            	ld	a,xl
4149  01c4 cd0120        	call	_SPI_sendchar
4151                     ; 58 	LCD_DELAY()
4154  01c7 9d            nop
4159  01c8 9d            nop
4164  01c9 9d            nop
4169  01ca 9d            nop
4174  01cb 9d            nop
4176                     ; 59 	E_CLK
4178  01cc 721b5014      	bres	_PE_ODR,#5
4179                     ; 60 	LCD_DELAY()
4182  01d0 9d            nop
4187  01d1 9d            nop
4192  01d2 9d            nop
4197  01d3 9d            nop
4202  01d4 9d            nop
4204                     ; 61 }
4207  01d5 84            	pop	a
4208  01d6 81            	ret
4254                     ; 63 void refreshLCD(const u8 *lcd_stack)
4254                     ; 64 {
4255                     	switch	.text
4256  01d7               _refreshLCD:
4258  01d7 89            	pushw	x
4259  01d8 88            	push	a
4260       00000001      OFST:	set	1
4263                     ; 66 	sendCodeST7920(0x02);	//地址归位
4265  01d9 a602          	ld	a,#2
4266  01db ad95          	call	_sendCodeST7920
4268                     ; 67 	for(addr=0;addr<16;addr++)
4270  01dd 0f01          	clr	(OFST+0,sp)
4271  01df               L1752:
4272                     ; 69 		sendDataST7920(*(lcd_stack + addr));
4274  01df 7b02          	ld	a,(OFST+1,sp)
4275  01e1 97            	ld	xl,a
4276  01e2 7b03          	ld	a,(OFST+2,sp)
4277  01e4 1b01          	add	a,(OFST+0,sp)
4278  01e6 2401          	jrnc	L64
4279  01e8 5c            	incw	x
4280  01e9               L64:
4281  01e9 02            	rlwa	x,a
4282  01ea f6            	ld	a,(x)
4283  01eb adb6          	call	_sendDataST7920
4285                     ; 67 	for(addr=0;addr<16;addr++)
4287  01ed 0c01          	inc	(OFST+0,sp)
4290  01ef 7b01          	ld	a,(OFST+0,sp)
4291  01f1 a110          	cp	a,#16
4292  01f3 25ea          	jrult	L1752
4293                     ; 71 	for(addr=32;addr<48;addr++)
4295  01f5 a620          	ld	a,#32
4296  01f7 6b01          	ld	(OFST+0,sp),a
4297  01f9               L7752:
4298                     ; 73 		sendDataST7920(*(lcd_stack + addr));
4300  01f9 7b02          	ld	a,(OFST+1,sp)
4301  01fb 97            	ld	xl,a
4302  01fc 7b03          	ld	a,(OFST+2,sp)
4303  01fe 1b01          	add	a,(OFST+0,sp)
4304  0200 2401          	jrnc	L05
4305  0202 5c            	incw	x
4306  0203               L05:
4307  0203 02            	rlwa	x,a
4308  0204 f6            	ld	a,(x)
4309  0205 ad9c          	call	_sendDataST7920
4311                     ; 71 	for(addr=32;addr<48;addr++)
4313  0207 0c01          	inc	(OFST+0,sp)
4316  0209 7b01          	ld	a,(OFST+0,sp)
4317  020b a130          	cp	a,#48
4318  020d 25ea          	jrult	L7752
4319                     ; 75 	for(addr=16;addr<32;addr++)
4321  020f a610          	ld	a,#16
4322  0211 6b01          	ld	(OFST+0,sp),a
4323  0213               L5062:
4324                     ; 77 		sendDataST7920(*(lcd_stack + addr));
4326  0213 7b02          	ld	a,(OFST+1,sp)
4327  0215 97            	ld	xl,a
4328  0216 7b03          	ld	a,(OFST+2,sp)
4329  0218 1b01          	add	a,(OFST+0,sp)
4330  021a 2401          	jrnc	L25
4331  021c 5c            	incw	x
4332  021d               L25:
4333  021d 02            	rlwa	x,a
4334  021e f6            	ld	a,(x)
4335  021f ad82          	call	_sendDataST7920
4337                     ; 75 	for(addr=16;addr<32;addr++)
4339  0221 0c01          	inc	(OFST+0,sp)
4342  0223 7b01          	ld	a,(OFST+0,sp)
4343  0225 a120          	cp	a,#32
4344  0227 25ea          	jrult	L5062
4345                     ; 80 	for(addr=48;addr<64;addr++)
4347  0229 a630          	ld	a,#48
4348  022b 6b01          	ld	(OFST+0,sp),a
4349  022d               L3162:
4350                     ; 82 		sendDataST7920(*(lcd_stack + addr));
4352  022d 7b02          	ld	a,(OFST+1,sp)
4353  022f 97            	ld	xl,a
4354  0230 7b03          	ld	a,(OFST+2,sp)
4355  0232 1b01          	add	a,(OFST+0,sp)
4356  0234 2401          	jrnc	L45
4357  0236 5c            	incw	x
4358  0237               L45:
4359  0237 02            	rlwa	x,a
4360  0238 f6            	ld	a,(x)
4361  0239 cd01a3        	call	_sendDataST7920
4363                     ; 80 	for(addr=48;addr<64;addr++)
4365  023c 0c01          	inc	(OFST+0,sp)
4368  023e 7b01          	ld	a,(OFST+0,sp)
4369  0240 a140          	cp	a,#64
4370  0242 25e9          	jrult	L3162
4371                     ; 84 }
4374  0244 5b03          	addw	sp,#3
4375  0246 81            	ret
4428                     ; 86 void decToAscii(u8* str,u16 dec,u8 width)
4428                     ; 87 {
4429                     	switch	.text
4430  0247               _decToAscii:
4432  0247 89            	pushw	x
4433       00000000      OFST:	set	0
4436  0248 ace702e7      	jpf	L5662
4437  024c               L3662:
4438                     ; 90 		switch(width)
4440  024c 7b07          	ld	a,(OFST+7,sp)
4442                     ; 121 			default: *str = '0';
4443  024e 4a            	dec	a
4444  024f 2603cc02d7    	jreq	L1362
4445  0254 4a            	dec	a
4446  0255 2764          	jreq	L7262
4447  0257 4a            	dec	a
4448  0258 2745          	jreq	L5262
4449  025a 4a            	dec	a
4450  025b 2726          	jreq	L3262
4451  025d 4a            	dec	a
4452  025e 2707          	jreq	L1262
4453  0260               L3362:
4456  0260 1e01          	ldw	x,(OFST+1,sp)
4457  0262 a630          	ld	a,#48
4458  0264 f7            	ld	(x),a
4459  0265 2077          	jra	L3762
4460  0267               L1262:
4461                     ; 94 				*str = (dec / 10000 + '0');
4463  0267 1e05          	ldw	x,(OFST+5,sp)
4464  0269 90ae2710      	ldw	y,#10000
4465  026d 65            	divw	x,y
4466  026e 1c0030        	addw	x,#48
4467  0271 1601          	ldw	y,(OFST+1,sp)
4468  0273 01            	rrwa	x,a
4469  0274 90f7          	ld	(y),a
4470  0276 02            	rlwa	x,a
4471                     ; 95 				dec %= 10000;
4473  0277 1e05          	ldw	x,(OFST+5,sp)
4474  0279 90ae2710      	ldw	y,#10000
4475  027d 65            	divw	x,y
4476  027e 51            	exgw	x,y
4477  027f 1f05          	ldw	(OFST+5,sp),x
4478                     ; 96 				break;
4480  0281 205b          	jra	L3762
4481  0283               L3262:
4482                     ; 100 				*str = (dec / 1000 + '0');
4484  0283 1e05          	ldw	x,(OFST+5,sp)
4485  0285 90ae03e8      	ldw	y,#1000
4486  0289 65            	divw	x,y
4487  028a 1c0030        	addw	x,#48
4488  028d 1601          	ldw	y,(OFST+1,sp)
4489  028f 01            	rrwa	x,a
4490  0290 90f7          	ld	(y),a
4491  0292 02            	rlwa	x,a
4492                     ; 101 				dec %= 1000;
4494  0293 1e05          	ldw	x,(OFST+5,sp)
4495  0295 90ae03e8      	ldw	y,#1000
4496  0299 65            	divw	x,y
4497  029a 51            	exgw	x,y
4498  029b 1f05          	ldw	(OFST+5,sp),x
4499                     ; 102 				break;
4501  029d 203f          	jra	L3762
4502  029f               L5262:
4503                     ; 106 				*str = (dec/100+'0');
4505  029f 1e05          	ldw	x,(OFST+5,sp)
4506  02a1 90ae0064      	ldw	y,#100
4507  02a5 65            	divw	x,y
4508  02a6 1c0030        	addw	x,#48
4509  02a9 1601          	ldw	y,(OFST+1,sp)
4510  02ab 01            	rrwa	x,a
4511  02ac 90f7          	ld	(y),a
4512  02ae 02            	rlwa	x,a
4513                     ; 107 				dec %= 100;
4515  02af 1e05          	ldw	x,(OFST+5,sp)
4516  02b1 90ae0064      	ldw	y,#100
4517  02b5 65            	divw	x,y
4518  02b6 51            	exgw	x,y
4519  02b7 1f05          	ldw	(OFST+5,sp),x
4520                     ; 108 				break;
4522  02b9 2023          	jra	L3762
4523  02bb               L7262:
4524                     ; 112 				*str = (dec/10+'0');
4526  02bb 1e05          	ldw	x,(OFST+5,sp)
4527  02bd 90ae000a      	ldw	y,#10
4528  02c1 65            	divw	x,y
4529  02c2 1c0030        	addw	x,#48
4530  02c5 1601          	ldw	y,(OFST+1,sp)
4531  02c7 01            	rrwa	x,a
4532  02c8 90f7          	ld	(y),a
4533  02ca 02            	rlwa	x,a
4534                     ; 113 				dec %= 10;
4536  02cb 1e05          	ldw	x,(OFST+5,sp)
4537  02cd 90ae000a      	ldw	y,#10
4538  02d1 65            	divw	x,y
4539  02d2 51            	exgw	x,y
4540  02d3 1f05          	ldw	(OFST+5,sp),x
4541                     ; 114 				break;
4543  02d5 2007          	jra	L3762
4544  02d7               L1362:
4545                     ; 118 				*str = (dec+'0');
4547  02d7 7b06          	ld	a,(OFST+6,sp)
4548  02d9 ab30          	add	a,#48
4549  02db 1e01          	ldw	x,(OFST+1,sp)
4550  02dd f7            	ld	(x),a
4551                     ; 119 				break;
4553  02de               L3762:
4554                     ; 123 		width--;
4556  02de 0a07          	dec	(OFST+7,sp)
4557                     ; 124 		str++;
4559  02e0 1e01          	ldw	x,(OFST+1,sp)
4560  02e2 1c0001        	addw	x,#1
4561  02e5 1f01          	ldw	(OFST+1,sp),x
4562  02e7               L5662:
4563                     ; 88 	while(width)
4565  02e7 0d07          	tnz	(OFST+7,sp)
4566  02e9 2703          	jreq	L26
4567  02eb cc024c        	jp	L3662
4568  02ee               L26:
4569                     ; 126 }
4572  02ee 85            	popw	x
4573  02ef 81            	ret
4635                     ; 128 void hexToAscii(u8* str,u16 hex,u8 width)
4635                     ; 129 {
4636                     	switch	.text
4637  02f0               _hexToAscii:
4639  02f0 89            	pushw	x
4640  02f1 89            	pushw	x
4641       00000002      OFST:	set	2
4644  02f2 acac03ac      	jpf	L3472
4645  02f6               L1472:
4646                     ; 133 		switch(width)
4648  02f6 7b09          	ld	a,(OFST+7,sp)
4650                     ; 163 			default: *str = '0';
4651  02f8 4a            	dec	a
4652  02f9 2603          	jrne	L07
4653  02fb cc0380        	jp	L3072
4654  02fe               L07:
4655  02fe 4a            	dec	a
4656  02ff 2758          	jreq	L1072
4657  0301 4a            	dec	a
4658  0302 2730          	jreq	L7762
4659  0304 4a            	dec	a
4660  0305 2709          	jreq	L5762
4661  0307               L5072:
4664  0307 1e03          	ldw	x,(OFST+1,sp)
4665  0309 a630          	ld	a,#48
4666  030b f7            	ld	(x),a
4667  030c aca303a3      	jpf	L1572
4668  0310               L5762:
4669                     ; 137 				tmp = (hex >> 12);
4671  0310 1e07          	ldw	x,(OFST+5,sp)
4672  0312 01            	rrwa	x,a
4673  0313 4f            	clr	a
4674  0314 41            	exg	a,xl
4675  0315 4e            	swap	a
4676  0316 a40f          	and	a,#15
4677  0318 02            	rlwa	x,a
4678  0319 1f01          	ldw	(OFST-1,sp),x
4679                     ; 138 				if(tmp > 9) *str = tmp + ('A' - 10);
4681  031b 1e01          	ldw	x,(OFST-1,sp)
4682  031d a3000a        	cpw	x,#10
4683  0320 2509          	jrult	L3572
4686  0322 7b02          	ld	a,(OFST+0,sp)
4687  0324 ab37          	add	a,#55
4688  0326 1e03          	ldw	x,(OFST+1,sp)
4689  0328 f7            	ld	(x),a
4691  0329 2078          	jra	L1572
4692  032b               L3572:
4693                     ; 139 				else *str = tmp + '0';
4695  032b 7b02          	ld	a,(OFST+0,sp)
4696  032d ab30          	add	a,#48
4697  032f 1e03          	ldw	x,(OFST+1,sp)
4698  0331 f7            	ld	(x),a
4699  0332 206f          	jra	L1572
4700  0334               L7762:
4701                     ; 144 				tmp = (hex >> 8) & 0x000F;
4703  0334 1e07          	ldw	x,(OFST+5,sp)
4704  0336 4f            	clr	a
4705  0337 01            	rrwa	x,a
4706  0338 01            	rrwa	x,a
4707  0339 a40f          	and	a,#15
4708  033b 5f            	clrw	x
4709  033c 02            	rlwa	x,a
4710  033d 1f01          	ldw	(OFST-1,sp),x
4711  033f 01            	rrwa	x,a
4712                     ; 145 				if(tmp > 9) *str = tmp + ('A' - 10);
4714  0340 1e01          	ldw	x,(OFST-1,sp)
4715  0342 a3000a        	cpw	x,#10
4716  0345 2509          	jrult	L7572
4719  0347 7b02          	ld	a,(OFST+0,sp)
4720  0349 ab37          	add	a,#55
4721  034b 1e03          	ldw	x,(OFST+1,sp)
4722  034d f7            	ld	(x),a
4724  034e 2053          	jra	L1572
4725  0350               L7572:
4726                     ; 146 				else *str = tmp + '0';
4728  0350 7b02          	ld	a,(OFST+0,sp)
4729  0352 ab30          	add	a,#48
4730  0354 1e03          	ldw	x,(OFST+1,sp)
4731  0356 f7            	ld	(x),a
4732  0357 204a          	jra	L1572
4733  0359               L1072:
4734                     ; 151 				tmp = (hex >> 4) & 0x000F;
4736  0359 1e07          	ldw	x,(OFST+5,sp)
4737  035b 54            	srlw	x
4738  035c 54            	srlw	x
4739  035d 54            	srlw	x
4740  035e 54            	srlw	x
4741  035f 01            	rrwa	x,a
4742  0360 a40f          	and	a,#15
4743  0362 5f            	clrw	x
4744  0363 5f            	clrw	x
4745  0364 97            	ld	xl,a
4746  0365 1f01          	ldw	(OFST-1,sp),x
4747                     ; 152 				if(tmp > 9) *str = tmp + ('A' - 10);
4749  0367 1e01          	ldw	x,(OFST-1,sp)
4750  0369 a3000a        	cpw	x,#10
4751  036c 2509          	jrult	L3672
4754  036e 7b02          	ld	a,(OFST+0,sp)
4755  0370 ab37          	add	a,#55
4756  0372 1e03          	ldw	x,(OFST+1,sp)
4757  0374 f7            	ld	(x),a
4759  0375 202c          	jra	L1572
4760  0377               L3672:
4761                     ; 153 				else *str = tmp + '0';
4763  0377 7b02          	ld	a,(OFST+0,sp)
4764  0379 ab30          	add	a,#48
4765  037b 1e03          	ldw	x,(OFST+1,sp)
4766  037d f7            	ld	(x),a
4767  037e 2023          	jra	L1572
4768  0380               L3072:
4769                     ; 158 				tmp = hex & 0x000F;
4771  0380 7b07          	ld	a,(OFST+5,sp)
4772  0382 97            	ld	xl,a
4773  0383 7b08          	ld	a,(OFST+6,sp)
4774  0385 a40f          	and	a,#15
4775  0387 5f            	clrw	x
4776  0388 02            	rlwa	x,a
4777  0389 1f01          	ldw	(OFST-1,sp),x
4778  038b 01            	rrwa	x,a
4779                     ; 159 				if(tmp > 9) *str = tmp + ('A' - 10);
4781  038c 1e01          	ldw	x,(OFST-1,sp)
4782  038e a3000a        	cpw	x,#10
4783  0391 2509          	jrult	L7672
4786  0393 7b02          	ld	a,(OFST+0,sp)
4787  0395 ab37          	add	a,#55
4788  0397 1e03          	ldw	x,(OFST+1,sp)
4789  0399 f7            	ld	(x),a
4791  039a 2007          	jra	L1572
4792  039c               L7672:
4793                     ; 160 				else *str = tmp + '0';
4795  039c 7b02          	ld	a,(OFST+0,sp)
4796  039e ab30          	add	a,#48
4797  03a0 1e03          	ldw	x,(OFST+1,sp)
4798  03a2 f7            	ld	(x),a
4799  03a3               L1572:
4800                     ; 165 		width--;
4802  03a3 0a09          	dec	(OFST+7,sp)
4803                     ; 166 		str++;
4805  03a5 1e03          	ldw	x,(OFST+1,sp)
4806  03a7 1c0001        	addw	x,#1
4807  03aa 1f03          	ldw	(OFST+1,sp),x
4808  03ac               L3472:
4809                     ; 131 	while(width)
4811  03ac 0d09          	tnz	(OFST+7,sp)
4812  03ae 2703          	jreq	L27
4813  03b0 cc02f6        	jp	L1472
4814  03b3               L27:
4815                     ; 168 }
4818  03b3 5b04          	addw	sp,#4
4819  03b5 81            	ret
4912                     ; 170 void showLine(const u8 x,const u8 y,u8* lcd_stack,char * str,...)
4912                     ; 171 {
4913                     	switch	.text
4914  03b6               _showLine:
4916  03b6 89            	pushw	x
4917  03b7 5204          	subw	sp,#4
4918       00000004      OFST:	set	4
4921                     ; 172 	u8 coordinate = 16 * y + x;
4923  03b9 9f            	ld	a,xl
4924  03ba 97            	ld	xl,a
4925  03bb a610          	ld	a,#16
4926  03bd 42            	mul	x,a
4927  03be 9f            	ld	a,xl
4928  03bf 1b05          	add	a,(OFST+1,sp)
4929  03c1 6b04          	ld	(OFST+0,sp),a
4930                     ; 175 	va_start(marker,str); // Initialize variable arguments.  
4932  03c3 96            	ldw	x,sp
4933  03c4 1c000d        	addw	x,#OFST+9
4934  03c7 1f02          	ldw	(OFST-2,sp),x
4935                     ; 176 	for(i=0;i<64;i++)
4937  03c9 0f01          	clr	(OFST-3,sp)
4938  03cb               L1403:
4941  03cb 0c01          	inc	(OFST-3,sp)
4944  03cd 7b01          	ld	a,(OFST-3,sp)
4945  03cf a140          	cp	a,#64
4946  03d1 25f8          	jrult	L1403
4948  03d3 ace104e1      	jpf	L1503
4949  03d7               L7403:
4950                     ; 182 		if(coordinate > 64) break;	//防止堆栈溢出
4952  03d7 7b04          	ld	a,(OFST+0,sp)
4953  03d9 a141          	cp	a,#65
4954  03db 2503          	jrult	L5503
4956  03dd               L3503:
4957                     ; 217 	va_end( marker ); // Reset variable arguments. 
4959                     ; 218 } 
4962  03dd 5b06          	addw	sp,#6
4963  03df 81            	ret
4964  03e0               L5503:
4965                     ; 184 		if(*str == '\\')
4967  03e0 1e0b          	ldw	x,(OFST+7,sp)
4968  03e2 f6            	ld	a,(x)
4969  03e3 a15c          	cp	a,#92
4970  03e5 261b          	jrne	L7503
4971                     ; 186 			str++;
4973  03e7 1e0b          	ldw	x,(OFST+7,sp)
4974  03e9 1c0001        	addw	x,#1
4975  03ec 1f0b          	ldw	(OFST+7,sp),x
4976                     ; 187 			lcd_stack[coordinate] = *str;
4978  03ee 7b09          	ld	a,(OFST+5,sp)
4979  03f0 97            	ld	xl,a
4980  03f1 7b0a          	ld	a,(OFST+6,sp)
4981  03f3 1b04          	add	a,(OFST+0,sp)
4982  03f5 2401          	jrnc	L67
4983  03f7 5c            	incw	x
4984  03f8               L67:
4985  03f8 02            	rlwa	x,a
4986  03f9 160b          	ldw	y,(OFST+7,sp)
4987  03fb 90f6          	ld	a,(y)
4988  03fd f7            	ld	(x),a
4990  03fe acd804d8      	jpf	L1603
4991  0402               L7503:
4992                     ; 189 		else if(*str == '%')
4994  0402 1e0b          	ldw	x,(OFST+7,sp)
4995  0404 f6            	ld	a,(x)
4996  0405 a125          	cp	a,#37
4997  0407 2703          	jreq	L011
4998  0409 cc04c8        	jp	L3603
4999  040c               L011:
5000                     ; 191 			str++;
5002  040c 1e0b          	ldw	x,(OFST+7,sp)
5003  040e 1c0001        	addw	x,#1
5004  0411 1f0b          	ldw	(OFST+7,sp),x
5005                     ; 192 			if (*str == 'd' || *str == 'D')
5007  0413 1e0b          	ldw	x,(OFST+7,sp)
5008  0415 f6            	ld	a,(x)
5009  0416 a164          	cp	a,#100
5010  0418 2707          	jreq	L7603
5012  041a 1e0b          	ldw	x,(OFST+7,sp)
5013  041c f6            	ld	a,(x)
5014  041d a144          	cp	a,#68
5015  041f 2637          	jrne	L5603
5016  0421               L7603:
5017                     ; 194 				str++;
5019  0421 1e0b          	ldw	x,(OFST+7,sp)
5020  0423 1c0001        	addw	x,#1
5021  0426 1f0b          	ldw	(OFST+7,sp),x
5022                     ; 195 				decToAscii(&lcd_stack[coordinate],va_arg(marker,u16),(*str-'0'));
5024  0428 1e0b          	ldw	x,(OFST+7,sp)
5025  042a f6            	ld	a,(x)
5026  042b a030          	sub	a,#48
5027  042d 88            	push	a
5028  042e 1e03          	ldw	x,(OFST-1,sp)
5029  0430 1c0002        	addw	x,#2
5030  0433 1f03          	ldw	(OFST-1,sp),x
5031  0435 1e03          	ldw	x,(OFST-1,sp)
5032  0437 5a            	decw	x
5033  0438 5a            	decw	x
5034  0439 fe            	ldw	x,(x)
5035  043a 89            	pushw	x
5036  043b 7b0c          	ld	a,(OFST+8,sp)
5037  043d 97            	ld	xl,a
5038  043e 7b0d          	ld	a,(OFST+9,sp)
5039  0440 1b07          	add	a,(OFST+3,sp)
5040  0442 2401          	jrnc	L001
5041  0444 5c            	incw	x
5042  0445               L001:
5043  0445 02            	rlwa	x,a
5044  0446 cd0247        	call	_decToAscii
5046  0449 5b03          	addw	sp,#3
5047                     ; 196 				coordinate += (*str-'0'-1);
5049  044b 1e0b          	ldw	x,(OFST+7,sp)
5050  044d f6            	ld	a,(x)
5051  044e a031          	sub	a,#49
5052  0450 1b04          	add	a,(OFST+0,sp)
5053  0452 6b04          	ld	(OFST+0,sp),a
5055  0454 acd804d8      	jpf	L1603
5056  0458               L5603:
5057                     ; 198 			else if(*str == 'c' || *str == 'C')
5059  0458 1e0b          	ldw	x,(OFST+7,sp)
5060  045a f6            	ld	a,(x)
5061  045b a163          	cp	a,#99
5062  045d 2707          	jreq	L5703
5064  045f 1e0b          	ldw	x,(OFST+7,sp)
5065  0461 f6            	ld	a,(x)
5066  0462 a143          	cp	a,#67
5067  0464 261f          	jrne	L3703
5068  0466               L5703:
5069                     ; 200 				lcd_stack[coordinate] = va_arg(marker,u16);
5071  0466 7b09          	ld	a,(OFST+5,sp)
5072  0468 97            	ld	xl,a
5073  0469 7b0a          	ld	a,(OFST+6,sp)
5074  046b 1b04          	add	a,(OFST+0,sp)
5075  046d 2401          	jrnc	L201
5076  046f 5c            	incw	x
5077  0470               L201:
5078  0470 02            	rlwa	x,a
5079  0471 1602          	ldw	y,(OFST-2,sp)
5080  0473 72a90002      	addw	y,#2
5081  0477 1702          	ldw	(OFST-2,sp),y
5082  0479 1602          	ldw	y,(OFST-2,sp)
5083  047b 905a          	decw	y
5084  047d 905a          	decw	y
5085  047f 90e601        	ld	a,(1,y)
5086  0482 f7            	ld	(x),a
5088  0483 2053          	jra	L1603
5089  0485               L3703:
5090                     ; 202 			else if(*str == 'x' || *str == 'X')
5092  0485 1e0b          	ldw	x,(OFST+7,sp)
5093  0487 f6            	ld	a,(x)
5094  0488 a178          	cp	a,#120
5095  048a 2707          	jreq	L3013
5097  048c 1e0b          	ldw	x,(OFST+7,sp)
5098  048e f6            	ld	a,(x)
5099  048f a158          	cp	a,#88
5100  0491 2645          	jrne	L1603
5101  0493               L3013:
5102                     ; 204 				str++;
5104  0493 1e0b          	ldw	x,(OFST+7,sp)
5105  0495 1c0001        	addw	x,#1
5106  0498 1f0b          	ldw	(OFST+7,sp),x
5107                     ; 205 				hexToAscii(&lcd_stack[coordinate],va_arg(marker,u16),(*str - '0'));
5109  049a 1e0b          	ldw	x,(OFST+7,sp)
5110  049c f6            	ld	a,(x)
5111  049d a030          	sub	a,#48
5112  049f 88            	push	a
5113  04a0 1e03          	ldw	x,(OFST-1,sp)
5114  04a2 1c0002        	addw	x,#2
5115  04a5 1f03          	ldw	(OFST-1,sp),x
5116  04a7 1e03          	ldw	x,(OFST-1,sp)
5117  04a9 5a            	decw	x
5118  04aa 5a            	decw	x
5119  04ab fe            	ldw	x,(x)
5120  04ac 89            	pushw	x
5121  04ad 7b0c          	ld	a,(OFST+8,sp)
5122  04af 97            	ld	xl,a
5123  04b0 7b0d          	ld	a,(OFST+9,sp)
5124  04b2 1b07          	add	a,(OFST+3,sp)
5125  04b4 2401          	jrnc	L401
5126  04b6 5c            	incw	x
5127  04b7               L401:
5128  04b7 02            	rlwa	x,a
5129  04b8 cd02f0        	call	_hexToAscii
5131  04bb 5b03          	addw	sp,#3
5132                     ; 206 				coordinate += (*str - '0' - 1);
5134  04bd 1e0b          	ldw	x,(OFST+7,sp)
5135  04bf f6            	ld	a,(x)
5136  04c0 a031          	sub	a,#49
5137  04c2 1b04          	add	a,(OFST+0,sp)
5138  04c4 6b04          	ld	(OFST+0,sp),a
5139  04c6 2010          	jra	L1603
5140  04c8               L3603:
5141                     ; 212 			lcd_stack[coordinate] = *str;
5143  04c8 7b09          	ld	a,(OFST+5,sp)
5144  04ca 97            	ld	xl,a
5145  04cb 7b0a          	ld	a,(OFST+6,sp)
5146  04cd 1b04          	add	a,(OFST+0,sp)
5147  04cf 2401          	jrnc	L601
5148  04d1 5c            	incw	x
5149  04d2               L601:
5150  04d2 02            	rlwa	x,a
5151  04d3 160b          	ldw	y,(OFST+7,sp)
5152  04d5 90f6          	ld	a,(y)
5153  04d7 f7            	ld	(x),a
5154  04d8               L1603:
5155                     ; 214 		str++;
5157  04d8 1e0b          	ldw	x,(OFST+7,sp)
5158  04da 1c0001        	addw	x,#1
5159  04dd 1f0b          	ldw	(OFST+7,sp),x
5160                     ; 215 		coordinate++;
5162  04df 0c04          	inc	(OFST+0,sp)
5163  04e1               L1503:
5164                     ; 180 	while(*str != '\0')
5166  04e1 1e0b          	ldw	x,(OFST+7,sp)
5167  04e3 7d            	tnz	(x)
5168  04e4 2703          	jreq	L211
5169  04e6 cc03d7        	jp	L7403
5170  04e9               L211:
5171  04e9 acdd03dd      	jpf	L3503
5259                     ; 21 main()
5259                     ; 22 {
5260                     	switch	.text
5261  04ed               _main:
5263  04ed 88            	push	a
5264       00000001      OFST:	set	1
5267                     ; 24 	AT24CXX_Init();
5269  04ee cd00c8        	call	_AT24CXX_Init
5271                     ; 25 	st7920LcdInit();
5273  04f1 cd013d        	call	_st7920LcdInit
5275                     ; 27 	showLine(0,0,lcd_buffer,"AT24Cxx Example");
5277  04f4 ae001f        	ldw	x,#L7413
5278  04f7 89            	pushw	x
5279  04f8 ae0000        	ldw	x,#_lcd_buffer
5280  04fb 89            	pushw	x
5281  04fc 5f            	clrw	x
5282  04fd cd03b6        	call	_showLine
5284  0500 5b04          	addw	sp,#4
5285                     ; 28 	showLine(0,1,lcd_buffer,"Program and");
5287  0502 ae0013        	ldw	x,#L1513
5288  0505 89            	pushw	x
5289  0506 ae0000        	ldw	x,#_lcd_buffer
5290  0509 89            	pushw	x
5291  050a ae0001        	ldw	x,#1
5292  050d cd03b6        	call	_showLine
5294  0510 5b04          	addw	sp,#4
5295                     ; 29 	showLine(0,2,lcd_buffer,"Verify");
5297  0512 ae000c        	ldw	x,#L3513
5298  0515 89            	pushw	x
5299  0516 ae0000        	ldw	x,#_lcd_buffer
5300  0519 89            	pushw	x
5301  051a ae0002        	ldw	x,#2
5302  051d cd03b6        	call	_showLine
5304  0520 5b04          	addw	sp,#4
5305                     ; 30 	showLine(0,3,lcd_buffer,"Results:");
5307  0522 ae0003        	ldw	x,#L5513
5308  0525 89            	pushw	x
5309  0526 ae0000        	ldw	x,#_lcd_buffer
5310  0529 89            	pushw	x
5311  052a ae0003        	ldw	x,#3
5312  052d cd03b6        	call	_showLine
5314  0530 5b04          	addw	sp,#4
5315                     ; 31 	refreshLCD(lcd_buffer);
5317  0532 ae0000        	ldw	x,#_lcd_buffer
5318  0535 cd01d7        	call	_refreshLCD
5320                     ; 33 	AT24CXX_WriteAByte(0x01,'P');
5322  0538 ae0150        	ldw	x,#336
5323  053b cd00cb        	call	_AT24CXX_WriteAByte
5325                     ; 34 	delay_ms(10);
5327  053e ae000a        	ldw	x,#10
5328  0541 cd0000        	call	_delay_ms
5330                     ; 35 	tmp=AT24CXX_ReadAByte(0x01);
5332  0544 a601          	ld	a,#1
5333  0546 cd00e0        	call	_AT24CXX_ReadAByte
5335  0549 6b01          	ld	(OFST+0,sp),a
5336                     ; 37 	showLine(9,3,lcd_buffer,"%c",tmp);
5338  054b 7b01          	ld	a,(OFST+0,sp)
5339  054d 88            	push	a
5340  054e ae0000        	ldw	x,#L7513
5341  0551 89            	pushw	x
5342  0552 ae0000        	ldw	x,#_lcd_buffer
5343  0555 89            	pushw	x
5344  0556 ae0903        	ldw	x,#2307
5345  0559 cd03b6        	call	_showLine
5347  055c 5b05          	addw	sp,#5
5348                     ; 38 	refreshLCD(lcd_buffer); 
5350  055e ae0000        	ldw	x,#_lcd_buffer
5351  0561 cd01d7        	call	_refreshLCD
5353  0564               L1613:
5354                     ; 39 	while (1);
5356  0564 20fe          	jra	L1613
5369                     	xdef	_main
5370                     	xdef	_SPI_rechar
5371                     	xdef	_SPI_sendchar
5372                     	xdef	_SPI_Init
5373                     	switch	.ubsct
5374  0000               _lcd_buffer:
5375  0000 000000000000  	ds.b	64
5376                     	xdef	_lcd_buffer
5377                     	xdef	_showLine
5378                     	xdef	_hexToAscii
5379                     	xdef	_decToAscii
5380                     	xdef	_refreshLCD
5381                     	xdef	_st7920LcdInit
5382                     	xdef	_sendDataST7920
5383                     	xdef	_sendCodeST7920
5384                     	xdef	_AT24CXX_ReadAByte
5385                     	xdef	_AT24CXX_WriteAByte
5386                     	xdef	_AT24CXX_Init
5387                     	xdef	_I2C_RcvDat
5388                     	xdef	_I2C_SendDat
5389                     	xdef	_I2C_SendDAdr
5390                     	xdef	_I2C_Start
5391                     	xdef	_I2C_Init
5392                     	xdef	_delay_us
5393                     	xdef	_delay_ms
5394                     .const:	section	.text
5395  0000               L7513:
5396  0000 256300        	dc.b	"%c",0
5397  0003               L5513:
5398  0003 526573756c74  	dc.b	"Results:",0
5399  000c               L3513:
5400  000c 566572696679  	dc.b	"Verify",0
5401  0013               L1513:
5402  0013 50726f677261  	dc.b	"Program and",0
5403  001f               L7413:
5404  001f 415432344378  	dc.b	"AT24Cxx Example",0
5424                     	end
