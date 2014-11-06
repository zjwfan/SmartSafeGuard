#include "Option.h"

extern unsigned char RandPswd[7] ; //一次密码
extern int randseed;	   //Timer0的计数数值
	   /*
void Delay(unsigned int time)
{
	unsigned int j;
	for(;time>0;time--)
		for(j=0;j<510;j++);
//		for(j=0;j<110;j++);
}
*/
void Delay(unsigned int time)
{
//	unsigned int j;
//	for(;time>0;time--)
//		for(j=0;j<510;j++);
//		for(j=0;j<110;j++);
	int d;
	for(;time>1;time--)
		for(d=0;d<1000;d++)
		;
}
/*
void delay_moto(int time)
{ 
  int i,j;
  
  for(j=0; j <= time; j++)
  	for(i =0 ; i <= 120; i++);
//   for(i =0 ; i <= 120; i++);
}
 */

void delay_moto(int x)		//@11.0592MHz   x ms
{
	unsigned char i, j;
	while(x--)
	{
	  _nop_();
	  _nop_();
	  _nop_();
	  i = 20;	 //原：11 	卡顿  1.7        ||	 12			 ||	20 			 ||		||		||
	  j = 190;	 //原：190	  卡顿			 ||	 变化不大	 ||	 效果变化不大||		||		||
	  do
	  {
		while (--j);
	  } 
	  while (--i);
    }
}

//蜂鸣器（响应时长）
void Beep(unsigned int time)
{
	BeepON;
	BeepON;
	Delay(time);
	BeepOFF;
	BeepOFF;
}


//延时函数大概是1s钟，不过延时大的话不准...
void DelaySec(int sec)
{
	unsigned int i , j= 0;
	
	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}

/*------------------------------------------------
uS延时函数，含有输入参数 unsigned char t，无返回值
unsigned char 是定义无符号字符变量，其值的范围是
0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
	while(--t);
}

/*------------------------------------------------
mS延时函数，含有输入参数 unsigned char t，无返回值
unsigned char 是定义无符号字符变量，其值的范围是
0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
	
	while(t--)
	{
		//大致延时1mS
		DelayUs2x(245);
		DelayUs2x(245);
	}
}
/******************************以下为硬件相关***********************/

void Go()
{	 //A
    PH1 = 0;  //PH1为0 则A线圈为反向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2为1 则B线圈为正向电流
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 1;  //PH1为1 则A线圈为正向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 1;  //PH1为1 则A线圈为正向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2为0 则B线圈为反向电流
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 0;
	I01 = 0;
	I11 = 0;
	

	PH2 = 0;  
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);
	
	
}

//步进电机
void Forward() //正转
{	 //A
    PH1 = 0;  //PH1为0 则A线圈为反向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2为1 则B线圈为正向电流
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 1;  //PH1为1 则A线圈为正向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 1;  //PH1为1 则A线圈为正向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2为0 则B线圈为反向电流
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 0;
	I01 = 0;
	I11 = 0;
	

	PH2 = 0;  
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);	
}

void Reverse() //反转
{	// 反转：A/B/  AB/  AB   A/B
     //A
    PH1 = 0;  //PH1为0 则A线圈为反向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2为0 则B线圈为反向电流
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 1;  //PH1为1 则A线圈为正向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2为0 则B线圈为反向电流
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 0;  //PH1为0 则A线圈为反向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2为1 则B线圈为正向电流
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 0;   //PH1为0 则A线圈为反向电流
	I01 = 0;
	I11 = 0;
	

	PH2 = 1;  //PH2为0 则B线圈为正向电流
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);	
}		  \

void Reverse2() //反转
{	// 反转：A/B/  AB/  AB   A/B
     //A
    PH1 = 1;  //PH1为0 则A线圈为反向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2为0 则B线圈为反向电流
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 0;  //PH1为1 则A线圈为正向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2为0 则B线圈为反向电流
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 0;  //PH1为0 则A线圈为反向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2为1 则B线圈为正向电流
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 1;   //PH1为0 则A线圈为反向电流
	I01 = 0;
	I11 = 0;
	

	PH2 = 1;  //PH2为0 则B线圈为正向电流
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);	
}

			void Reverse3() //反转
{	// 反转：A/B/  AB/  AB   A/B
     //A
    PH1 = 0;  //PH1为0 则A线圈为反向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2为0 则B线圈为反向电流
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 1;  //PH1为1 则A线圈为正向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2为0 则B线圈为反向电流
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 1;  //PH1为0 则A线圈为反向电流
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2为1 则B线圈为正向电流
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 0;   //PH1为0 则A线圈为反向电流
	I01 = 0;
	I11 = 0;
	

	PH2 = 1;  //PH2为0 则B线圈为正向电流
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);	
}

void MakeArandStr()
{
	unsigned int r,t,u,p=0;//全局变量
	unsigned char l;
	//t=r;
	t=randseed;
	for(;;)
	{
		r+=29;
		t++;t%=10;//j只在0到9
		switch(t)
		{
		case 1:r*=2;break;
		case 2:r+=8;break;
		case 3:r*=1;break;
		case 4:r+=3;break;
		case 5:r*=6;break;
		case 6:r+=4;break;
		case 7:r*=3;break;
		case 8:r+=5;break;
		case 9:r*=7;break;
		case 0:r+=3;break;
		}
		u = r%10;//随机数只在1到10之间出现
		switch(u)
		{
		case 1:l='1';break;
		case 2:l='2';break;
		case 3:l='3';break;
		case 4:l='4';break;
		case 5:l='5';break;
		case 6:l='6';break;
		case 7:l='7';break;
		case 8:l='8';break;
		case 9:l='9';break;
		case 0:l='0';break;
		}
		
		RandPswd[p]=l;
		p++;	
		if(p==6)
		{
		  RandPswd[p]='\0'; 
		  p=0;
		  break;
		}	
	}

}

void OpenDoor()
{
	int r=60;	 //old：r=60  n=60
	int n=60;

	while(r--)
	{
		Reverse3();
	}

	Delay(5000);
/*
	if(RED == 0)
	{
//		Delay(100);	
		do
		{
			;
		}
		while(RED == 1)
	
	}
*/
	while(n--)
	{
		if(RED == 0)
		{
		 	Delay(3000);
		}
		Forward();
	}
	
	
	//此处添加红外传感器确认
	

/*
	while(1)
	{
//		Reverse();
		Go();
	}
*/
}
/*
char * ShiftUnicode(unsigned char i)
{
	char UnicodeStr[5];
	switch(i)
	{
		case '0':strcpy(UnicodeStr,"0030");break;
		case '1':strcpy(UnicodeStr,"0031");break;
		case '2':strcpy(UnicodeStr,"0032");break;
		case '3':strcpy(UnicodeStr,"0033");break;
		case '4':strcpy(UnicodeStr,"0034");break;
		case '5':strcpy(UnicodeStr,"0035");break;
		case '6':strcpy(UnicodeStr,"0036");break;
		case '7':strcpy(UnicodeStr,"0037");break;
		case '8':strcpy(UnicodeStr,"0038");break;
		case '9':strcpy(UnicodeStr,"0039");break;
		default:strcpy(UnicodeStr,"0038");	
	}
	return UnicodeStr;
}
*/
/******************************以上为硬件相关***********************/