#include<Option.h>


sbit DOUT_MQ2=P2^1;//P5^5; 

//void Mq2Init(void);
unsigned char Mq2Read(void);
void delay_MQ2(void);
/****************************************************************
*�������� ����ʱ����										
*��ڲ��� ����												
*�� �� ֵ ����							
*˵    �� ��				
****************************************************************/
void delay_MQ2(void)
{
    char m,n,s;
    for(m=20;m>0;m--)
    for(n=20;n>0;n--)
    for(s=248;s>0;s--);
}

/****************************************************************
*�������� ����ʼ������Ũ�ȶ�ȡ�˿�										
*��ڲ��� ����												
*�� �� ֵ ����							
*˵    �� ��					
****************************************************************/
//void Mq2Init(void)
//{
//  P0SEL &= ~0x01;//��P00Ϊ��ͨIO�ڣ�
//  P0DIR &= ~0x01;//��P00Ϊ���� 
//  P0INP &= ~0x01;//����P00Ϊ����������ģʽ
//  P2INP |= 0x10;//����P01Ϊ����
//}

/****************************************************************
*�������� ����ȡ����Ũ�ȣ�������Ƿ񳬱�										
*��ڲ��� ����												
*�� �� ֵ ����							
*˵    �� ��					
****************************************************************/
unsigned char Mq2Read(void)
{
   int result;
   
   if(DOUT_MQ2==0)        //��Ũ�ȸ����趨ֵʱ ��ִ����������
   {
      delay_MQ2();        //��ʱ������
      if(DOUT_MQ2==0)     //ȷ�� Ũ�ȸ����趨ֵʱ ��ִ����������
      {
       result = 1;
      }
   }
   else
   {
     result = 0;
   }
   return result;
}