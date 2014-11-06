#include<Option.h>

//version 5.9 beta 	 (以委员提供加PC端程序的beta版本)
//notice:
//		
//		beep 待添加

unsigned char PassWord[7] = "111111"; //主人密码
unsigned char RandPswd[7] = "888888"; //一次密码
unsigned char Input[7] = "000000"; //键盘输入数据
char EnviInfo[6]="00000";
//static unsigned int  ErrNum=0;
int flag[10]={0};
              //    12345678901234567890123456789012345678901234567890123456789012345678901234567890
char Message[250];	//存储短信内容

//可以借用flag的不同的值在一个变量内部实现多个模态
//   flag：	    	0			 	1	     	   2				3				4				5	  				6				7	8	9	    
//  对应模态：气体危险报警	设置密码标记      生成随机码标记	查看家庭环境	气体安全一次通知	主人访问次一次		错误访问次一次



void main()
{
	unsigned int i=0;
	unsigned int  ErrNum=0;
	
	EntranceGuardInit();//门禁系统初始化
//	LCD_Init();//LCD初始化
			
	while(1)
	{
		Beep(500);
		LCD_Clear();
		//CursorON;
		//                  1234567890123456
		LCD_Write_String(0,"—智能安全卫士—");
		LCD_Write_String(1,"请输入密码:     ");
		LCD_Write_String(3,"        按* 通话");
		LCD_Write_Char(0,2,' ');
//		while(1)
//		{
		 Beep(500);
//		}//debug
		for(i=0;i<6;i++)
		{	
		    CursorON;
			
			Input[i] = KeyScan();
			LCD_Write_Char(i,2,Input[i]);
			Delay(500);
			LCD_Write_Char(i,2,'*');
			if(i>0)
			{
			LCD_Row_Clear(3);
			LCD_Write_String(3,"        按# 重输");
			}

			//客人给主人拨号 1827072 
			if('*'==Input[i] && i==0)//客人按“*”号键 给主人拨打电话
		    {
			    LCD_Row_Clear(1);
				LCD_Row_Clear(2);
				LCD_Row_Clear(3);
				CursorOFF;
				//                  1234567890123456
				LCD_Write_String(1,"拨打主人电话中..");
				CloseTimer0();
				
				CallPhone("18270720353");//("13177755134");//主人电话号码
				
				InitTimer();//计时器0初始化Timer0
				//i=0;
				LCD_Write_String(3,"    按# 挂断电话");
				while('#'!=Input[i] )
				{
				 Input[i] = KeyScan();
				}

			    LCD_Row_Clear(1);
				LCD_Row_Clear(2);
				LCD_Row_Clear(3);
				CursorOFF;
				//                  1234567890123456
				LCD_Write_String(1,"挂断电话...     ");
				Uart1Sends("ATH\r\n");//挂电话
				DelaySec(2);//延时2秒

				Delay(1000);
				LCD_Clear();
				
				//                  1234567890123456
				LCD_Write_String(0,"—智能安全卫士—");
				LCD_Write_String(1,"请输入密码:     ");
				LCD_Write_String(3,"        按* 通话");
				LCD_Write_Char(0,2,' ');
				i=-1;
			  
	        }  
			
			//客人按“#”号键 重新输入密码 
			if('#'==Input[i] && i>0)
		    {
			    LCD_Row_Clear(1);
				LCD_Row_Clear(2);
				LCD_Row_Clear(3);
				LCD_Write_String(1,"            重输");
				CursorOFF;
				Delay(1000);
				LCD_Write_String(1,"请输入密码:     ");
				LCD_Write_String(3,"        按* 通话");
				i=-1;
				LCD_Write_Char(0,2,' ');
	        }    

							 
		}

		
		CursorOFF;

		if(0==strcmp(Input,RandPswd) && i>=5)
		{//随机码正确
			
			strcpy(RandPswd,"******");		  //一次有效码用后失效
//			LCD_Init();//LCD初始化
			Correct();
			ErrNum=0;
			continue;	
		}
		else
	   	{

	   		if(0!=strcmp(Input,PassWord) && i>=5)
				{//密码错误
					ErrNum++;
					Error(ErrNum);
					if(ErrNum>=3)	ErrNum=0;
				}
				else
				{
				   Correct();
				   ErrNum=0;
				}
		}
		LCD_Row_Clear(2);
	}
}

//门禁系统运行前的初始化相关硬件工作
void EntranceGuardInit()  
{	
	LCD_Init();//LCD初始化
	BeepOFF;

	init_serial_2();

	InitUART();//串口1初始化
				
	InitTimer();//计时器0初始化Timer0
			
	InitGSM();//初始化GSM控制
		
}

//密码正确的话
void Correct()
{

	
	//LCD_Init();//LCD初始化
	LCD_Row_Clear(1);
	LCD_Row_Clear(2);
	LCD_Row_Clear(3);
	
	//Moto();
	
	//                  1234567890123456
	LCD_Write_String(1,"欢迎  请进   ^_^");
	OpenDoor();

//显示家居环境数据
   show_environment_data();

	Delay(1000);
//	ErrNum=0;
	if(flag[5]==0)
	{
	flag[5]=1;
	send_pc_enter(); //发送到pc	   Debug:2014年9月19日20:39:16
    //日进入数（成功）//02 06 00 01 06 01
	}
}

//密码错误的话
void Error(unsigned int ErrNum)
{
	unsigned int i=0;
	Beep(BEEPT);
	//LCD_Clear();
	LCD_Init();//LCD初始化
	

	if(ErrNum>=3)//3
	{
		 
		
		//                  1234567890123456
		LCD_Write_String(0,"错误  次    锁死");
		LCD_Write_Char(2,0,'3'); 		 
		//                  1234567890123456
		LCD_Write_String(2,"自动联系主人... ");
					 //18270721101
		MakeArandStr();		//生成随机码到RandPswd[]
		strcpy(Message,"8B66544AFF1A5BC678018F93516595198BEF8D858FC74E096B21FF01002089E395015BC678014E3A");
		for(i=0;i<6;i++)
		{
			switch(RandPswd[i])
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
			//strcat(Message,ShiftUnicode(RandPswd[i]));
		}
		// '\0'
		CloseTimer0();
				
		SendMessage("00310038003200370030003700320030003300350033",Message);		
		 //18270721101

		InitTimer();//计时器0初始化Timer0
//		strcpy(Message,"8B66544AFF1A5BC678018F93516595198BEF8D858FC74E096B21FF01002089E395015BC678014E3A");
		Delay(50);

		//LCD_Clear();
    	LCD_Init();//LCD初始化	
		
		CursorON;

		LCD_Write_String(0,"—错误    锁死—");
		//                  1234567890123456
		LCD_Write_String(1,"输入解锁密码解锁");
		//                  1234567890123456
		//LCD_Write_String(2,RandPswd);	//Test
		CloseTimer0();
				
		
		while(1)
		{
			LCD_Write_Char(0,2,' ');
//			beep=1;
			for(i=0;i<6;i++)
			{	
				Input[i] = KeyScan();
				LCD_Write_Char(i,2,Input[i]);
				Delay(400);
				LCD_Write_Char(i,2,'*');
								
//				SendString_serial_2(Str);	 
			}
			
			if(0==strcmp(Input,RandPswd) && i>=5)
			{//密码正确
				//                    1234567890123456
				strcpy(RandPswd,"******");		  //一次有效码用后失效
				CursorOFF;
				LCD_Clear();
				LCD_Row_Clear(1);
				LCD_Row_Clear(2);
//				OpenDoor();//Moto();
				//                  1234567890123456
				LCD_Write_String(1,"解锁码无误......");
				//                  1234567890123456
				LCD_Write_String(2,"锁定已解除      ");
				Delay(5000);
				break;
			}
			else
			{
				;
			}
			LCD_Row_Clear(2);
		}
		//ErrNum=0;	局部变量清零无效
		InitTimer();//计时器0初始化Timer0
	}
	
	else
	{

				

	    //LCD_Clear();
		//LCD_Init();//LCD初始化
		LCD_Row_Clear(1);
		LCD_Row_Clear(2);

		Beep(BEEPT);
		//                  1234567890123456
		LCD_Write_String(1,"密码错误:     次");
		LCD_Write_Char(6,1,(unsigned char)('0'+ErrNum));
		//                  1234567890123456
		LCD_Write_String(2,"超  次将会锁定  ");	 //请输入密码:   过三
		LCD_Write_Char(1,2,'3'); 

		Delay(5000);	
		Delay(50);

		LCD_Row_Clear(1);
		LCD_Row_Clear(2);
	}
	
//		 Debug:2014年9月19日20:39:16
		if(ErrNum==1&&flag[6]==0)//1
	{	  flag[6]=1;
		  send_pc_visit(); //发送到pc	
         //日访问数（错误）//02 06 00 01 05 01
    }				

}
