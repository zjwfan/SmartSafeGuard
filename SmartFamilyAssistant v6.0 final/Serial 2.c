#include<Option.h>


#define FOSC_serial_2   11059200L        //系统频率
#define BAUD_serial_2 115200//9600//115200             //串口波特率

#define NONE_PARITY     0       //无校验
#define ODD_PARITY      1       //奇校验
#define EVEN_PARITY     2       //偶校验
#define MARK_PARITY     3       //标记校验
#define SPACE_PARITY    4       //空白校验

#define PARITYBIT EVEN_PARITY   //定义校验位

//sfr AUXR  = 0x8e;               //辅助寄存器
//sfr S2CON = 0x9a;               //UART2 控制寄存器
//sfr S2BUF = 0x9b;               //UART2 数据寄存器
//sfr T2H   = 0xd6;               //定时器2高8位
//sfr T2L   = 0xd7;               //定时器2低8位
//sfr IE2   = 0xaf;               //中断控制寄存器2

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3

//sfr P_SW2   = 0xBA;             //外设功能切换寄存器2
#define S2_S0 0x01              //P_SW2.0

#define buf_max_Uart2 72//缓存长度72
//
unsigned char k_Uart2=0;//,i;
unsigned char rec_buf_Uart2[buf_max_Uart2];//接收缓存

bit busy_serial_2;

void init_serial_2(void);
void SendData_serial_2(BYTE dat);
void SendString_serial_2(char *s);
void send_pc_visit(void);
void send_pc_enter(void);

void init_serial_2()
{
    P_SW2 &= ~S2_S0;            //S2_S0=0 (P1.0/RxD2, P1.1/TxD2)
 // P_SW2 |= S2_S0;             //S2_S0=1 (P4.6/RxD2_2, P4.7/TxD2_2)

#if (PARITYBIT == NONE_PARITY)
    S2CON = 0x50;               //8位可变波特率
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S2CON = 0xda;               //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
    S2CON = 0xd2;               //9位可变波特率,校验位初始为0
#endif

    T2L = (65536 - (FOSC_serial_2/4/BAUD_serial_2));   //设置波特率重装值
    T2H = (65536 - (FOSC_serial_2/4/BAUD_serial_2))>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
//  IE2 = 0x01;                 //使能串口2中断
    IE2 = 0x00;
    EA = 1;



	//SendString_serial_2("1234567890!\r\n");
    //SendString_serial_2("STC15F2K60S2\r\nUart2 Test !\r\n");
   	//SendData_serial_2('a');
//	while(1);
}

/*----------------------------
UART2 中断服务程序
-----------------------------*/
void Uart2() interrupt 8 using 1
{
//    if (S2CON & S2RI)
//    {
//        
//       // P0 = S2BUF;             //P0显示串口数据
//        //P2 = (S2CON & S2RB8);   //P2.2显示校验位
//    }
//    if (S2CON & S2TI)
//    {
//        S2CON &= ~S2TI;         //清除S2TI位
//        busy_serial_2 = 0;               //清忙标志
//    }

 	ES=0;	 //关串口中断
	S2CON &= ~S2RI;         //清除S2RI位
	rec_buf_Uart2[k_Uart2]=S2BUF;
	if(k_Uart2<buf_max_Uart2)
		k_Uart2++;
	else
		k_Uart2=0;
	ES=1;	 //开串口中断
//		    if(strstr(rec_buf_Uart2,"O")!=NULL)
//	    Uart1Sends("OK");
}

/*----------------------------
发送串口数据
----------------------------*/
void SendData_serial_2(BYTE dat)
{
	Delay(3);
//    while (busy_serial_2);               //等待前面的数据发送完成
    ACC = dat;                  //获取校验位P (PSW.0)
    if (P)                      //根据P来设置校验位
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON &= ~S2TB8;        //设置校验位为0
#elif (PARITYBIT == EVEN_PARITY)
        S2CON |= S2TB8;         //设置校验位为1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON |= S2TB8;         //设置校验位为1
#elif (PARITYBIT == EVEN_PARITY)
        S2CON &= ~S2TB8;        //设置校验位为0
#endif
    }

	ES=0;//关串行口中断	
    busy_serial_2 = 1;
    S2BUF = ACC;                //写数据到UART2数据寄存器
	while(S2CON & S2TI==0);	//查询发送是否结束
		S2CON &= ~S2TI;         //清除S2TI位
	ES=1;//开串行口中断		
}

/*----------------------------
发送字符串
----------------------------*/
void SendString_serial_2(char *s)
{
    while (*s)                  //检测字符串结束标志
    {
        SendData_serial_2(*s++);         //发送当前字符
    }								  	
}

/*---------------
//发送到pc	
//日访问数（错误+成功）//02 06 00 01 05 01
---------------*/
void send_pc_visit(void)
{
	unsigned char Str[22];	
	int str_i=0;

    //IE2 = 0x00;
	
	{//发送到pc	
     //日访问数（错误）//02 06 00 01 05 01  
		Str[0]=0x02;
		Str[1]=0x06;
		Str[2]=0x00;
		Str[3]=0x01;	
		Str[4]=0x05;	
		Str[5]=0x01;	
	}		
	for(str_i=0;str_i<=5;str_i++)
	SendData_serial_2(Str[str_i]);
	//SendString_serial_2(Str);

    //IE2 = 0x01;                 //使能串口2中断
}


/*---------------
//发送到pc	
//日进入数（成功）//02 06 00 01 06 01
---------------*/
void send_pc_enter(void)
{
	unsigned char Str2[22];	
	int str_i2=0;

    //IE2 = 0x00;
	
	{//发送到pc	
     //日访问数（错误+成功）//02 06 00 01 06 01  
		Str2[0]=0x02;
		Str2[1]=0x06;
		Str2[2]=0x00;
		Str2[3]=0x01;	
		Str2[4]=0x06;	
		Str2[5]=0x01;	
	}		
	for(str_i2=0;str_i2<=5;str_i2++)
	SendData_serial_2(Str2[str_i2]);
	//SendString_serial_2(Str);

    //IE2 = 0x01;                 //使能串口2中断
}