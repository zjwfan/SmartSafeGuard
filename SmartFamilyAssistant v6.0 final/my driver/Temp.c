 
 /*************************此部分为18B20的驱动程序*************************************/
#include<Option.h>



sbit DQ_18B20=P2^0;//P4^2;  //ds18b20 端口
	

void Delay1(unsigned int x);
unsigned char ReadTemperature(void);
void Init_DS18B20(void);
unsigned char ReadOneChar(void);
void WriteOneChar(unsigned char dat);
void delay_18B20(unsigned int i);
/************************************************************************/



void Delay1(unsigned int x)		//@11.0592MHz   x ms
{
	unsigned char i, j;
	while(x--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} 
		while (--i);
	}
}

void delay_18B20(unsigned int i)//延时函数
{
	while(i--);
}
/***************************************************************************************/
//18b20初始化函数
void Init_DS18B20(void)
{
	unsigned char x=0;
	DQ_18B20 = 1;    //DQ_18B20复位
	delay_18B20(80);  //稍做延时
	DQ_18B20 = 0;    //单片机将DQ_18B20拉低
	delay_18B20(800); //精确延时 大于 480us
	DQ_18B20 = 1;    //拉高总线
	delay_18B20(100);
	x=DQ_18B20;      //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
	delay_18B20(50);
}

//读一个字节
unsigned char ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ_18B20 = 0; // 给脉冲信号
		dat>>=1;
		DQ_18B20 = 1; // 给脉冲信号
		if(DQ_18B20)
		dat|=0x80;
		delay_18B20(50);
	}
	return(dat);
}

//写一个字节
void WriteOneChar(unsigned char dat)
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DQ_18B20 = 0;
		DQ_18B20 = dat&0x01;
		delay_18B20(50);
		DQ_18B20 = 1;
		dat>>=1;
	}
	delay_18B20(50);
}

//读取温度
unsigned char ReadTemperature(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned char t=0;
	//float tt=0;
	Init_DS18B20();
	WriteOneChar(0xCC); // 跳过读序号列号的操作
	WriteOneChar(0x44); // 启动温度转换
	delay_18B20(2000);
	Init_DS18B20();
	WriteOneChar(0xCC); //跳过读序号列号的操作 
	WriteOneChar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a=ReadOneChar();
	b=ReadOneChar();
	
	b<<=4;
	b+=(a&0xf0)>>4;
	t=b;
	//tt=t*0.0625;
	//t= tt*10+0.5; //放大10倍输出并四舍五入
	return(t);
}
