#include <Option.h>

extern char EnviInfo[6];
extern char Message[250];
extern unsigned char PassWord[7];

extern unsigned char RandPswd[7]; //一次密码
extern  void DHT11Read(unsigned char *OneNum, unsigned char *TwoNum);
extern unsigned char Mq2Read(void);
extern unsigned char ReadTemperature(void);
#define buf_max 372//缓存长度372
extern  int flag[];

unsigned char rec_buf[buf_max];//接收缓存
unsigned int k=0;

/*----------------------------
    UART1初始化
-----------------------------*/
void InitUART(void)
{
    SCON = 0x50;                //8位可变波特率	
	AUXR1= AUXR1 & 0x3F; 
//    AUXR = 0x40;                //定时器1为1T模式
	AUXR |= 0x40;                //定时器1为1T模式
    TMOD = 0x20;                //定时器1为模式2(8位自动重载)

    TL1 = 0xDC;   //设置波特率重装值
    TH1 = 0xDC;
    TR1 = 1;                    //定时器1开始工作
    ES = 1;                     //使能串口中断
    EA = 1;
	
}

/*----------------------------
UART 中断服务程序
-----------------------------*/
void Uart() interrupt 4 using 1
{

 	ES=0;	 //关串口中断
	RI=0;   
	rec_buf[k]=SBUF;
	if(k<buf_max)
		k++;
	else
		k=0;
	ES=1;	 //开串口中断
}

/*----------------------------
发送串口数据
----------------------------*/
void Uart1Send(unsigned char dat)
{

	ES=0;//关串行口中断	
    SBUF = dat;                 //写数据到UART数据寄存器
	while(TI==0);	//查询发送是否结束
		TI=0;	//清除发送一标志位
	ES=1;//开串行口中断	
}

/*----------------------------
发送字符串
----------------------------*/
void Uart1Sends(unsigned char *at)
{
    uchar cnt=0;								  
	ES=0;//关串行口中断									
	while(*(at+cnt))	//判断一串数据是否结束			
	{
		SBUF=*(at+cnt);	//发送数据
		while(TI==0);	//查询发送是否结束
		TI=0;	//清除发送一标志位
		cnt++;	//准备发送一个数据
	}
	ES=1;//开串行口中断	
}


//发短信模块
void SendMessage(char *number,char *text)
{
	char Message[100]="";	
    Uart1Sends("AT+CMGF=1\r\n");
	DelaySec(1);//延时3秒
	Uart1Sends("AT+CSMP=17,167,2,25\r\n");
	DelaySec(1);//延时3秒
	Uart1Sends("AT+CSCS=\"UCS2\"\r\n");
	DelaySec(1);//延时3秒
	strcpy(Message,"AT+CMGS=\"");//输入手机号码
	strcat(Message,number);
	strcat(Message,"\"\r\n");
	Uart1Sends(Message);
	DelaySec(1);//延时3秒
	Uart1Sends(text);//输入短信内容
	Uart1Send(0x1a);

}

//打电话函数
void CallPhone(char *number)
{
	char Message[20]="";
	strcpy(Message,"ATD");
	strcat(Message,number);//输入手机号码
	strcat(Message,";\r\n");//
	Uart1Sends(Message);//打电话指令综合
	//LCD_Init();//LCD清屏
	LCD_Clear();
	//                  1234567890123456
	LCD_Write_String(1,"拨号中...       ");//LCD 显示正在拨号
	//LCD_Write_String(2,"按 #  可挂断电话");//按 # 挂电话
	DelaySec(1);//延时1秒
}


//GSM_control 短信控制////////////////////////////////////////////////////////////




   /*****************判断缓存中是否含有指定的字符串函数******************/
/*函数原型:bit hand(unsigned char *a)
/*函数功能:判断缓存中是否含有指定的字符串
/*输入参数:unsigned char *a 指定的字符串
/*输出参数:bit 1---含有    0---不含有
/*调用模块:无
/**********************************************************************/
bit hand(uchar *a)
{ 
    if(strstr(rec_buf,a)!=NULL)	  //!=是不等于
       return 1;
    else
       return 0;
}

/**************************清除缓存数据函数****************************/
/*函数原型:void clr_buf(void)
/*函数功能:清除缓存数据
/*输入参数:无
/*输出参数:无
/*调用模块:无
/**********************************************************************/
void clr_buf(void)
{
    for(k=0;k<=buf_max;k++)
	{
   	    rec_buf[k]='0';
	}	
	 	k=0;
}

/****************************清除短信函数*****************************/
/*函数原型:void clr_ms(void)
/*函数功能:清除短信
/*输入参数:无
/*输出参数:无
/*调用模块:无
/**********************************************************************/
void clr_ms(void)
  {
     //Uart1Sends("AT+CMGDA=6\r\n");

	 Uart1Sends("AT+CMGD=1\r\n");

  }

void GSM_control(void)
{
	int j;
	unsigned char *pos;	    	

	Uart1Sends("AT+CMGR=1\r\n");//发送读指令
	delay_GSM(100);//Delay(50000);//
	Uart1Sends("AT+CMGR=1\r\n");//发送读指令
	
	
	if(strstr(rec_buf,"8BBE7F6E5BC67801FF1A" )!=NULL && flag[1]!=1)//设置密码：
	{
		

		flag[1] = 1;              
	 	pos = strstr(rec_buf,"8BBE7F6E5BC67801FF1A");
		if(pos-rec_buf < 309)
		{
		
			

			PassWord[0] = rec_buf[pos-rec_buf+20+3];
			PassWord[1] = rec_buf[pos-rec_buf+20+7];
			PassWord[2] = rec_buf[pos-rec_buf+20+11];
			PassWord[3] = rec_buf[pos-rec_buf+20+15];
			PassWord[4] = rec_buf[pos-rec_buf+20+19];
			PassWord[5] = rec_buf[pos-rec_buf+20+23];
			for(j=0;j<6;j++)
			{
			 	if(PassWord[j]<='9' && PassWord[j]>='0')
				{
				;
				}
				else
				{
					PassWord[j]='0';
				}

			}
			LCD_Write_String(2,"已更改短信密码");
//			LCD_Write_String(3,PassWord);

//			SendString_serial_2(PassWord);
//			strcpy(Message,"66F465395BC678016210529FFF0C65B05BC678014E3AFF1A");	
//			pos = pos+20;		
//			strcat(Message,pos);
//			CloseTimer0();		
//			SendMessage("00310033003100370037003700350035003100330034",Message);				
//			InitTimer();//计时器0初始化Timer0
	
			Delay(50);
			clr_ms();//删除短信
			Delay(50);
//			InitGSM();//初始化GSM控制
			LCD_Row_Clear(2);
//			Delay(10000);
		}

		//初始化GSM控制
		Uart1Sends("AT\r\n");
		 Delay(1000);
		 //while(!hand("OK"));
		 clr_buf();	
		 Uart1Sends("AT+CMGF=1\r\n");//文本方式
		 Delay(1000);
		 //while(!hand("OK"));
	
		 clr_buf();
		 Uart1Sends("AT+CNMI=2,1\r\n");
		 Delay(1000);
		 //while(!hand("OK")); 
		 clr_buf(); 
	
		clr_ms();//删除短信	
		Delay(1000);
		//while(!hand("OK")); 
		clr_buf();
		Delay(50);
	}


	if(strstr(rec_buf,"751F6210968F673A7801")!=NULL && flag[2]!=1)//生成随机码
	{
		
		flag[2] = 1;
		MakeArandStr();		//生成随机码到RandPswd[]
		strcpy(Message,"968F673A78014E3AFF1A");
		for(j=0;j<6;j++)
		{
			switch(RandPswd[j])
			{
			case '0':strcat(Message,"0030");break;
			case '1':strcat(Message,"0031");break;
			case '2':strcat(Message,"0032");break;
			case '3':strcat(Message,"0033");break;
			case '4':strcat(Message,"0034");break;
			case '5':strcat(Message,"0035");break;
			case '6':strcat(Message,"0036");break;
			case '7':strcat(Message,"0037");break;
			case '8':strcat(Message,"0038");break;
			case '9':strcat(Message,"0039");break;
			default:strcat(Message,"0030");break;
				
			}

		}
		
		CloseTimer0();		
		SendMessage("00310038003200370030003700320030003300350033",Message);	//		SendMessage("00310033003100370037003700350035003100330034",Message);				
		InitTimer();//计时器0初始化Timer0

		strcpy(Message,"968F673A78014E3AFF1A");
		Delay(50);
		clr_ms();//删除短信
		Delay(50);
		
		//初始化GSM控制
		//初始化GSM控制
		Uart1Sends("AT\r\n");
		 Delay(1000);
		 //while(!hand("OK"));
		 clr_buf();	
		 Uart1Sends("AT+CMGF=1\r\n");//文本方式
		 Delay(1000);
		 //while(!hand("OK"));
	
		 clr_buf();
		 Uart1Sends("AT+CNMI=2,1\r\n");
		 Delay(1000);
		 //while(!hand("OK")); 
		 clr_buf(); 
	
		clr_ms();//删除短信	
		Delay(1000);
		//while(!hand("OK")); 
		clr_buf();
		Delay(50);
	}


	if(strstr(rec_buf,"5BB65EAD73AF5883")!=NULL && flag[3]!=1)//查看家庭环境
	{		

		flag[3]=1;
			
		strcpy(Message,"76EE524D76845BB65EAD73AF588360C551B54E3AFF1A");
		for(j=0;j<4;j++)
		{
			
			if(j==0)
			{
				strcat(Message,"007C007C6E295EA6003A");
			}
			if(j==2)
			{
				strcat(Message,"007C007C6E7F5EA6003A");
			}
		 	switch(EnviInfo[j])
			{
			case '0':strcat(Message,"0030");break;
			case '1':strcat(Message,"0031");break;
			case '2':strcat(Message,"0032");break;
			case '3':strcat(Message,"0033");break;
			case '4':strcat(Message,"0034");break;
			case '5':strcat(Message,"0035");break;
			case '6':strcat(Message,"0036");break;
			case '7':strcat(Message,"0037");break;
			case '8':strcat(Message,"0038");break;
			case '9':strcat(Message,"0039");break;
			default:strcat(Message,"0030");break;
				
			}
		}
//----g
		strcat(Message,"007C007C537196696C144F5368C06D4B003A");
//		MQ=Mq2Read();
		if(EnviInfo[4]=='0')
		{
		  strcat(Message,"5B895168007C007C");
		}
		else
		{
		  strcat(Message,"5F025E38007C007C");
		  
		}
		
		CloseTimer0();		
		SendMessage("00310038003200370030003700320030003300350033",Message);
						
		InitTimer();//计时器0初始化Timer0

		strcpy(Message,"76EE524D76845BB65EAD73AF588360C551B54E3AFF1A");
		Delay(50);	
		clr_ms();//删除短信
		Delay(50);
		
		//初始化GSM控制
		//初始化GSM控制
		Uart1Sends("AT\r\n");
		 Delay(1000);
		 //while(!hand("OK"));
		 clr_buf();	
		 Uart1Sends("AT+CMGF=1\r\n");//文本方式
		 Delay(1000);
		 //while(!hand("OK"));
	
		 clr_buf();
		 Uart1Sends("AT+CNMI=2,1\r\n");
		 Delay(1000);
		 //while(!hand("OK")); 
		 clr_buf(); 
	
		clr_ms();//删除短信	
		Delay(1000);
		//while(!hand("OK")); 
		clr_buf();

		Delay(50);
	}
	
	
	clr_buf();     
	
}

void InitGSM(void)
{

    CloseTimer0();

	 clr_buf();

     Uart1Sends("AT\r\n");

	 while(!hand("OK"));

	 clr_buf();
	 //clr_ms();//删除短信	
	 Uart1Sends("AT+CMGF=1\r\n");//文本方式
	 while(!hand("OK"));

	 clr_buf();
	 Uart1Sends("AT+CNMI=2,1\r\n");
	 while(!hand("OK")); 
	 clr_buf(); 

	clr_ms();//删除短信	
	while(!hand("OK")); 
	clr_buf();
	InitTimer();//计时器0初始化Timer0
}

 void delay_GSM(uint z)		  //1ms延时
{
     uint x,y;
	 for(x=z;x>0;x--)
	    for(y=110;y>0;y--);
}

