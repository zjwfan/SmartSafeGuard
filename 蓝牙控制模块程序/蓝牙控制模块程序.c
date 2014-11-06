/************************************************************
程序说明：
本程序运行后如果蓝牙模块找到蓝牙连接信号课实现蓝牙控制家电等功能


*************************************************************/
#include <REG51.H>
#include <string.H>
#define uchar unsigned char
#define uint unsigned int
//以下是板子上LED的配置，把Px_x改成自己对应的脚。
//以下是你的51单片机的晶振大小
int flag;//标志位 为1表示密码正确，为0错误！
int If_num = 0;//if检测的次数

#define num 3
//Motor
unsigned char code FFW[3]={0xf1,0xf3,0xf2}; //1
unsigned char code FFZ[3]={0xf8,0xfc,0xf4}; //2

sbit BUZZ=P0^6;//蜂鸣器
sbit Accept = P0^7;

sbit LED=P0^0;//LED灯泡
sbit XSQ=P0^1; //显示器
sbit WHQ=P0^2; //雾化器
sbit BFQ=P0^3; //播放器

sbit KZ1=P1^0;//无线控制
sbit KZ2=P1^1; 
sbit KZ3=P2^2; 
sbit KZ4=P3^3; 


#define FOSC_110592M
//#define FOSC_12M

//以下是GSM模块返回数据
uchar rec_data[50];
uchar rec_num;
unsigned int  K;
//注意，无论接收到信号还是发送完信号，都会进中断服务程序的
/*初始化程序（必须使用，否则无法收发），次程序将会使用定时器1*/
void SerialInti()//初始化程序（必须使用，否则无法收发）
{
	TMOD=0x20;//定时器1操作模式2:8位自动重载定时器

#ifdef FOSC_12M		   //在这里根据晶振大小设置不同的数值初始化串口
	TH1=0xf3;//装入初值，波特率2400
	TL1=0xf3;	
#else 	
	TH1=0xfd;//装入初值，波特率9600
	TL1=0xfd;
#endif //end of SOC_12M
	
	TR1=1;//打开定时器
	SM0=0;//设置串行通讯工作模式，（10为一部发送，波特率可变，由定时器1的溢出率控制）
	SM1=1;//(同上)在此模式下，定时器溢出一次就发送一个位的数据
	REN=1;//串行接收允许位（要先设置sm0sm1再开串行允许）
	EA=1;//开总中断
	ES=1;//开串行口中断	
}

/*串行通讯中断，收发完成将进入该中断*///如：+CMTI:"SM",2
void Serial_interrupt() interrupt 4 
{

	uchar temp;
	temp=SBUF;
	rec_data[rec_num++]=temp;
	if(rec_num>=50)
		rec_num=0;
	else
		;
	RI=0;//接收中断信号清零，表示将继续接收

}

//串行口连续发送char型数组，遇到终止号/0将停止
void Uart1Sends(uchar *str)
{
	while(*str!='\0')
	{
		SBUF=*str;
		while(!TI);//等待发送完成信号（TI=1）出现
		TI=0;
		str++;
	}
}
void Uart1BYTE(uchar temp)
{
		SBUF=temp;
		while(!TI);//等待发送完成信号（TI=1）出现
		TI=0;

}

uchar hand(uchar *ptr)
{
	if(strstr(rec_data,ptr)!=NULL)
		return 1;
	else
		return 0;
}

void clear_rec_data()
{
	uchar i;
	for(i=0;i<strlen(rec_data);i++)
	{
		rec_data[i]='0';
	
	}
	rec_num=0;


}
//延时函数大概是1s钟，不过延时大的话不准...
void DelaySec(int sec)
{
	uint i , j= 0;

	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}

/*******************延时函数****************************/
void delay(int time)
{ 
  int i,j;
  
  for(j=0; j <= time; j++)
   for(i =0 ; i <= 120; i++); //for(i =0 ; i <= 120; i++);
}

void Moto_delay(unsigned int t)//步进电机延时程序
{                           
   unsigned int k;
   while(t--)
   {
     for(k=0; k<80; k++)
     { }
   }
}
/**********************************************************************
*																	  *
*                       步进电机驱动								  *
*																	  *
***********************************************************************/
void Moto() //步进电机转动
 { 
   unsigned char motoi;
   unsigned int  motoj;
  	for (motoj=0; motoj<12*num; motoj++)         //转1*n圈 
    { 

      for (motoi=0; motoi<3; motoi++)       //一个周期转30度
        {
          if(K==1) 
		  {
		  P2 = FFW[motoi]&0x1f;  //取数据
		  Moto_delay(30);                   //调节转速
		  }
		  if(K==2)
		  {
		  P2 = FFZ[motoi]&0x1f;
          Moto_delay(30);                   //调节转速
		  }
        }
     } 
 }

void main()
{   uchar i = 0;
	SerialInti();
	LED=1;//关灯
	XSQ=1;//关闭显示器
	BFQ=0;//播放器不播放
	Accept=0;
	flag = 0;//没有输入密码	
  TMOD = 0x21;//两个定时\计数器都打开
  EA=1;//打开总中断
  //ET0=1;ET1=1;//定时器 //	影响整体	//计数器	 
  TR0=1;TR1=1;
  EX0=1;//开启外部中断0
  EX1=1;//开启外部中断1
  //TH0=0xd0;TL0=0xf0;//高低八位  //对中断有影响
  //TH1=0xE7;TL1=0xE7;
  while(1)
  {//(while(1))
  while(0==Accept);//等待蓝牙与手机的连接信号
  If_num++;
  delay(100);
  if(If_num%2!=0) 
  {//(if)
  Uart1Sends("Please enter the password:\r\n"); //请输入密码
  clear_rec_data();
  If_num++;
  }
	while(1)
	{	 if(0==Accept)
	     break;
	    delay(50);
		 if(1==KZ2)
         {
         BUZZ=0;
		 delay(300);//延时?秒
		 BUZZ=1;
		 delay(300);//延时?秒
         }
		 if(1==KZ1)
         {
         LED=!LED;
		 delay(200);//延时?秒
         }
		while(hand("abc")) //正确密码abc
		{clear_rec_data();
		 BUZZ=0;
		 delay(300);//延时?秒
		 BUZZ=1;
		 Uart1Sends("Please enter the command:\r\n"); //请输入指令
		 flag=1;//密码正确标志
		 break;
		}
		if(1==flag)
		break;
	}
	while(1)
 { 
    if(0==Accept)//||0==If_num%2)
	{
	clear_rec_data();
	break;
	}
	while(hand("opend")) 
	{
		clear_rec_data();
		LED=0;//开灯
		Uart1Sends("Light is open!\r\n");//灯已开启！
		break;
	}
	//clear_rec_data();//删除存储的GSM模块返回的数据，以便于以后继续判断
	while(hand("openx")) //检测SIM模块是否收到SIM卡READY
	{
		clear_rec_data();
		XSQ=1;//开显示器
		Uart1Sends("The display has been opened!\r\n");//显示器已开启！
		break;	
	}
	while(hand("closed")) 
	{
		clear_rec_data();
		LED=1;//关灯
		Uart1Sends("Light has been shut down!\r\n");//灯已关闭！
		break;
	}
	//clear_rec_data();//删除存储的GSM模块返回的数据，以便于以后继续判断
	while(hand("closex")) //检测SIM模块是否收到SIM卡READY
	{
		clear_rec_data();
		XSQ=0; //关显示器
		Uart1Sends("The display has been shut down!\r\n");//显示器已关闭！
		break;	
	}

	while(hand("closec")) //检测此条指令GSM模块是否执行
	{
		clear_rec_data();
	    //窗户已关闭！
		Uart1Sends("The window is closeing!\r\n");//窗户已关闭！
		  K=1;
		  Moto();//正转
		  break;
	}
	while(hand("openc")) //检测SIM模块是否收到SIM卡
	{
		clear_rec_data();
		 //窗户已开启！
		Uart1Sends("The window is opening!\r\n");//窗户已开启！
		K=2;
	    Moto();//反转										   
		break;
    }

	while(hand("closew")) //关闭雾化器
	{
		clear_rec_data();
	    WHQ=0;//关雾化器
		delay(100);
		WHQ=1;
		Uart1Sends("Atomizer has been shut down!\r\n");//雾化器已关闭！
		break;
	}
	//clear_rec_data();
	while(hand("openw")) //打开雾化器
	{
		clear_rec_data();
		WHQ=0; //开雾化器
		delay(100);
		WHQ=1;
		Uart1Sends("Atomizer has been opened!\r\n");//雾化器已开启！
		break;	
	}
		if(0==Accept)//||0==If_num%2)
		{
		clear_rec_data();
		break;
		}
 }
	   if(0==Accept)//||0==If_num%2)
		{
		clear_rec_data();
		break;
		}
   }//(while(1))
}

void External_one(void) interrupt 0	//外部中断 0
{	
    EA=0;//关中断
    if(0==INT0)//如果检测到障碍物
	{
	  BFQ=1;//给语音播放高电平
	  delay(1);	//短暂延时	 
	}
	if(1==INT0)//如果没有检测到障碍物
	{
	  BFQ=0;//给语音播放低电平
	  delay(1);	//短暂延时
	}
	EA=1;//开中断
}
//
void Time_one(void) interrupt 1	//时间中断 0
{
   
}

void External_two(void) interrupt 2	//外部中断 1
{
EA=0;//关中断
    //Uart1Sends("Enter INT1!\r\n");//
    if(0==INT1)//如果检测到障碍物
	{
	  BUZZ=0;
	  delay(100);
	  BUZZ=1;
	  delay(100);
	}
	EA=1;//开中断  
}

void Time_two(void) interrupt 3	//时间中断 2  //interrupt 4 是串口中断
{
  
}