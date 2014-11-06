 /*************************此部分为湿度传感器的驱动程序*************************************/
#include<Option.h>

sbit DHT_IN_DQ=P2^2;//P5^4;//湿度传感器 端口
 

#define UINT8 unsigned char       
#define UINT16 unsigned short      





#define DHT_CL_DQ  DHT_IN_DQ=0
#define DHT_SET_DQ DHT_IN_DQ=1

void Read8Bit(void);
void DHT11Read(UINT8 *OneNum, UINT8 *TwoNum);



UINT8  OverTimeCnt = 0;
UINT8  tmpBit,tmp8BitValue;

void Delay_nus(UINT16 s) 
{
  while (s--);

}

void Read8Bit(void)
{
	UINT8 i;
	
	for(i=0;i<8;i++)
	{
		OverTimeCnt = 2;
		while((DHT_IN_DQ == 0)&&OverTimeCnt++);
		//while(IN_DQ == 0);
		Delay_nus(19);//12
		if(DHT_IN_DQ == 1)
		tmpBit = 1;
		else
		tmpBit = 0;
		OverTimeCnt = 2;
		while((DHT_IN_DQ == 1)&&OverTimeCnt++);
		//while(IN_DQ == 1);
		//超时则跳出for循环		  
		if(OverTimeCnt==1)
		break;
		
		tmp8BitValue<<=1;
		tmp8BitValue|=tmpBit;        //0
		
	}

}

void DHT11Read(UINT8 *OneNum, UINT8 *TwoNum)
{
	//UINT8 tmp;
	
	
	DHT_CL_DQ; 
	Delay_nus(20000);//主机拉低至少18ms  
	DHT_SET_DQ;
	Delay_nus(20);//总线由上拉电阻拉高 主机延时20us-40us
	
	if(DHT_IN_DQ == 0)
	{
		OverTimeCnt = 2;
		while((DHT_IN_DQ == 0)&&OverTimeCnt++);
		//判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
		//OverTimeCnt = 2;
		//while((IN_DQ == 1)&&OverTimeCnt++);
		while(DHT_IN_DQ == 1);
		//数据接收状态	
		Read8Bit();
		//SensorValueBuf[0] = tmp8BitValue;
		*OneNum = tmp8BitValue;
		
		Read8Bit();
		//SensorValueBuf[1] = tmp8BitValue;
		*TwoNum = tmp8BitValue;		
	}

}