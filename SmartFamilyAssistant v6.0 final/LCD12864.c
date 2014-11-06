#include "Option.h"
#include<intrins.h>

//*************************************************
//函数名：LCD_Busy(void)      函数功能：12864判断是否忙碌                 
//存在变量：
//创建者&时间：
//*************************************************
void LCD_Busy(void)
{
	DataPort=0xff;
	RS=0;
	RW=1;
	E=1;
	while(Busy==1);
	E=0;
}

void LCD_Write_Com(unsigned char com) 
{  
	LCD_Busy();
	RS=0;
	RW=0;
	DataPort=com;
	E=1;
	nop();
	E=0; 
}
/*------------------------------------------------
写入数据函数
------------------------------------------------*/
void LCD_Write_Data(unsigned char Data) 
{ 
	LCD_Busy();
	RS=1;
	RW=0;
	DataPort=Data;
	E=1;
	nop();
	E=0; 
}

/*------------------------------------------------
清屏函数
------------------------------------------------*/
void LCD_Clear(void) 
{ 
	
	LCD_Row_Clear(0);
	LCD_Row_Clear(1);
	LCD_Row_Clear(2);
	LCD_Row_Clear(3);
}
/*------------------------------------------------
写入字符串函数			  LCD_Write_String(第y行,字符串)
------------------------------------------------*/
void LCD_Write_String(unsigned int y,unsigned char *s) //change version: char --> int
{     
	unsigned char i;
	switch(y)
	{
		case 0:y=0x80;break;
		case 1:y=0x90;break;
		case 2:y=0x88;break;
		case 3:y=0x98;break;
	}
	LCD_Write_Com(0x30);
	LCD_Write_Com(y);
	for(i=0;i<16;i++)
	{
		LCD_Write_Data(*s);
		s++;
	}
}
/*------------------------------------------------
写入字符函数		LCD_Write_Char(第x个,第y行,字符)
------------------------------------------------*/
void LCD_Write_Char(unsigned int x,unsigned int y,unsigned char Data)  //change version: char --> int
{     
	switch(y)
	{
		case 0:y=0x80;break;
		case 1:y=0x90;break;
		case 2:y=0x88;break;
		case 3:y=0x98;break;
	}
	LCD_Write_Com(0x30);
	LCD_Write_Com(y+x);       
	LCD_Write_Data( Data);  
}
/*------------------------------------------------
初始化函数
------------------------------------------------*/
void LCD_Init(void) 
{
	RST=1;
	PSB=1;
	LCD_Write_Com(0x30);  /*30---基本指令动作*/   
	LCD_Write_Com(0x01);  /*清屏，地址指针指向00H*/
	LCD_Write_Com(0x06);  /*光标的移动方向*/
	LCD_Write_Com(0x0c);  /*开显示，关游标*/
}

/*------------------------------------------------
清屏行函数
------------------------------------------------*/
void LCD_Row_Clear(unsigned int row) 
{
	//                    1234567890123456
	LCD_Write_String(row,"                ");
}

