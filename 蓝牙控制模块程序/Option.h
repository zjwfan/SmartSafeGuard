#ifndef _OPTION_H_
#define _OPTION_H_

#include <reg52.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

unsigned char KeyScan();

void LCD_Write_Com(unsigned char com);
void LCD_Write_Data(unsigned char Data);
void LCD_Clear(void);
void LCD_Write_String(unsigned int x,unsigned int y,unsigned char *s);
void LCD_Write_Char(unsigned int x,unsigned int y,unsigned char Data);
void LCD_Init(void);
void LCD_Row_Clear(unsigned int row);
void LCD_Cursor(unsigned int flag);

void DelayUs2x(unsigned char t);
void DelayMs(unsigned char t);
void Delay(unsigned int time);
void Beep(unsigned int time);
void DelaySec(int sec);
void Relay();
void Moto();

void SerialInti();
void Serial_interrupt();
void Uart1Send(unsigned char c);
void Uart1Sends(unsigned char *str);
void SendMessage(char *number,char *text);
void TakePhone(char *number);

void EntranceGuardInit();
void Correct();
void Error(unsigned int ErrNum);
void SendMessage_Const(unsigned int flag);

/******************************以下为硬件相关***********************/

#define DataPort P0//LCD1602的数据口

#define CursorON LCD_Write_Com(0x0f);  //LCD1602光标开
#define CursorOFF LCD_Write_Com(0x0c);	//LCD1602光标关

#define BeepON beep=0;
#define BeepOFF beep=1;

#define RelayOpen R=0;
#define RelayClose R=1;



sbit R = P2^0;
sbit RS = P2^4;
sbit RW = P2^5;
sbit EN = P2^6;
sbit beep = P2^3;

sbit A0 = P1^0;	//按键判断
sbit A1 = P1^1;
sbit A2 = P1^2;
sbit A3 = P1^3;

/******************************以上为硬件相关***********************/
 
#endif