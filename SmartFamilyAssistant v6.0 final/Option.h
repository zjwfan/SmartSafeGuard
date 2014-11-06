#ifndef _OPTION_H_
#define _OPTION_H_

//#define DEBUG	 //7

#include "STC15F2K.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <intrins.H>

#define uchar unsigned char 
#define uint unsigned int
typedef unsigned char BYTE;
typedef unsigned int WORD;

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

unsigned char KeyScan();

//LCD相关函数声明
void LCD_Write_Com(unsigned char com);
void LCD_Write_Data(unsigned char Data);
void LCD_Clear(void);
void LCD_Write_String(unsigned int y,unsigned char *s);
void LCD_Write_Char(unsigned int x,unsigned int y,unsigned char Data);
void LCD_Init(void);
void LCD_Row_Clear(unsigned int row);
void LCD_Busy(void);

void OpenDoor();
void DelayUs2x(unsigned char t);
void DelayMs(unsigned char t);
void Delay(unsigned int time);
void Beep(unsigned int time);
void DelaySec(int sec);
void Reverse();
void Forward();
void Go();
void MakeArandStr();
void delay_moto(int time);
//char * ShiftUnicode(unsigned int i);

void InitUART(void);
void Uart1Send(unsigned char dat);
void Uart1Sends(unsigned char *s);

void InitGSM(void);
void delay_GSM(uint z);
void GSM_control(void);
void SerialInti();
void Serial_interrupt();
void Uart1Send(unsigned char c);
//void Uart1Sends(unsigned char *str);
void SendMessage(char *number,char *text);
void CallPhone(char *number);
void GSM_control(void);


void EntranceGuardInit();
void Correct();
void Error(unsigned int ErrNum);
void SendMessage_Const(unsigned int flag);

void show_environment_data(void);


void CloseTimer0(void);
void InitTimer(void);
void init_serial_2(void);
void SendData_serial_2(BYTE dat);
void SendString_serial_2(char *s);
void send_pc_visit(void);
void send_pc_enter(void);
/******************************以下为硬件相关***********************/


#define CursorON LCD_Write_Com(0x0f);  //LCD1602光标开
#define CursorOFF LCD_Write_Com(0x0c);	//LCD1602光标关

#define BeepON beep=0;
#define BeepOFF beep=1;
#define BEEPT 500


#define nop(); {_nop_();_nop_();_nop_();_nop_();};
#define DataPort P0                          //定义P0口为LCD通讯端口
sbit RS=P2^7;								 //数据/命令端
sbit RW=P4^5;								 //读/写选择端
sbit E=P2^6;
sbit RST=P2^4;
sbit PSB=P2^5;								 //I/O口更改，原：sbit PSB=P2^2;	2014-9-2 16:18:50
sbit Busy=DataPort^7;

sbit beep = P2^3;		  //
sbit RED = P4^4;

sbit A0 = P5^5;//P3^6;//P1^0;	//按键判断
sbit A1 = P5^4;//P3^7;//P1^1;
sbit A2 = P1^2;
sbit A3 = P1^3;

#define speed 2				//源代码：2	//1：完全被卡	2：一个卡一个不卡	 3:可动易卡	  4:0.5个卡 1.5个不卡

 //Motor
sbit PH1 = P3^2;	  //定义管脚
sbit PH2 = P3^3;
sbit I01 = P3^4;
sbit I11 = P3^5;
sbit I02 = P3^6;
sbit I12 = P3^7;
/******************************以上为硬件相关***********************/
 
#endif