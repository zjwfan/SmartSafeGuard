/*******************************************************************************
**		Fliename:DataDispatch.h
**      Description:数据帧处理、转换、分发
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#if !defined(AFX_DATADISPATCH_H__CD5ED693_2F46_4457_AFD4_D64EE117A17C__INCLUDED_)
#define AFX_DATADISPATCH_H__CD5ED693_2F46_4457_AFD4_D64EE117A17C__INCLUDED_
#include "WisdomWellServerDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		UDCODE_TYPE_CTRL		0x01	//控制码
#define		UDCODE_TYPE_DATA		0x02    //数据码
#define		UDCODE_TYPE_RET			0x03	//反馈码
#define		UDCODE_TYPE_ROUTE		0x04	//路由码
#define		UDCODE_TYPE_EMER		0xFF	//紧急码

#define		UDCODE_SOURCE_TWG		0x10     //温湿度、可燃气体浓度数据
#define		UDCODE_SOURCE_TEM		0x01	 //温度
#define		UDCODE_SOURCE_SIM		0x02	 //湿度
#define		UDCODE_SOURCE_AIR		0x03     //可燃气体浓度
#define		UDCODE_SOURCE_PRE		0x04     //压力（矿车重量）
#define		UDCODE_SOURCE_RFID_TOP	0x05     //井上RFID数据
#define		UDCODE_SOURCE_RFID_BOT	0x06	 //进下RFID数据
#define		UDCODE_SOURCE_CAR_STAT	0x07	 //矿车状态数据

#define		UDCODE_DEST_TIME		0x81	 //时间数据
#define		UDCODE_DEST_PASSWORD	0x82	 //请求开门密码
#define		UDCODE_DEST_YIELD_DAILY	0x83	 //请求当日采矿量
#define		UDCODE_DEST_PHONENUM	0x84	 //请求发送短信的号码
#define		UDCODE_DEST_VMECHINE	0x85	 //请求卷扬机转速



#define		UDCODE_ZIGBEE_PC			0x0001	//PC端ZigBee地址
#define		UDCODE_ZIGBEE_A				0x0002	//ZigBee-A端：（位于斜井监控终端1）
#define		UDCODE_ZIGBEE_B				0x0004	//ZigBee-B端：（位于斜井监控终端2）
#define		UDCODE_ZIGBEE_WELL_TOP		0x0008	//ZigBee井上网关端：（位于井上出口处）（即系统的信息处理中心）
#define		UDCODE_ZIGBEE_WELL_BOTTOM	0x0010	//ZigBee-井下网关端：（位于井下出口处）
#define		UDCODE_ZIGBEE_BROADCAST		0x0000	//Zigbee广播

#define		UDCODE_TARGET_PEDESTRAINDOOR_TOP		0x01	//井上人行门
#define		UDCODE_TARGET_PEDESTRAINDOOR_BOTTOM		0x03	//井下人行门
#define		UDCODE_TARGET_SAFEDOOR_1				0x05	//安全门1
#define		UDCODE_TARGET_SAFEDOOR_2				0x06	//安全门2
#define		UDCODE_TARGET_CARDOOR_TOP				0x02	//井上车行门
#define		UDCODE_TARGET_CARDOOR_BOTTOM			0x04	//井下车行门
#define		UDCODE_TARGET_MECHINE					0x07	//卷扬机

#define		UDCODE_ACTION_START			0x03	//启动
#define		UDCODE_ACTION_STOP			0x04	//停止
#define		UDCODE_ACTION_OPEN			0x01	//打开
#define		UDCODE_ACTION_CLOSE			0x02	//关闭

typedef struct _TWGStruct//weiyuan-change2014年7月22日14:42:07
{
	char t; //温度//float
	char w; //湿度
	char g; //可燃气体浓度
}   TWGSTRUCT,*PTWGSTRUCT;

typedef struct _CarStatus
{
	int position;	//矿车位置： 井上0 井通道一1 井通道二2 井下3
	char velocity;	//矿车速度
	int direction;	//0停止 1向上 2向下
	int HarvMon_warn;	//0正常 1跑车
}CARSTATUS,*PCARSTATUS;	//状态



typedef unsigned short ZIGBEEADDR;

class CDataDispatch  
{
public:
	static CDataDispatch* CreateDataFrame(unsigned short toAddr,BYTE type,BYTE *content,int contentlen);
	void SendFrame();
	static CDataDispatch* CreateControlFrame(unsigned short toAddr,BYTE target,BYTE action);
	void DispatchFrame();
	CDataDispatch();
	CDataDispatch(BYTE* bytes,int len,CWisdomWellServerDlg * dialog);
	virtual ~CDataDispatch();

private:
	void ResponseVMechine();
	void ResponsePhoneNum();
	void ResponseYieldDaily();
	void ResponsePassword();
	void ResponseTime();
	long CodeToRFID(BYTE *bts);
	CARSTATUS CodeToCarStatus(BYTE *bts);
	CWisdomWellServerDlg * m_dlgMain;
	TWGSTRUCT CodeToTWGStruct(BYTE *bts);
	CString CodeToCString(BYTE * bts,int len);
	float CodeToFloat(BYTE* bts);
	void DispatchData();
	BYTE m_btSource;
	ZIGBEEADDR m_addrTo;
	ZIGBEEADDR m_addrFrom;
	BYTE m_btType;
	BYTE m_btContent[1024];
	int m_iLength;
};

#endif // !defined(AFX_DATADISPATCH_H__CD5ED693_2F46_4457_AFD4_D64EE117A17C__INCLUDED_)
