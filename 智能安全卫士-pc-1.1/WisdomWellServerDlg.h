/*******************************************************************************
**		Fliename:WisdomWellServerDlg.h
**      Description:应用程序主窗口、串口数据接收、系统状态显示
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_WISDOMWELLSERVERDLG_H__D3354C59_76AE_409B_AA15_BF433846BF11__INCLUDED_)
#define AFX_WISDOMWELLSERVERDLG_H__D3354C59_76AE_409B_AA15_BF433846BF11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "Db.h"
#include "Model.h"
#include "CarRecordDlg.h"
#include "EmployeeDlg.h"
#include "SamplingDlg.h"
#include "SettingDlg.h"
#include "SysLogDlg.h"
#include "UTime.h"
/////////////////////////////////////////////////////////////////////////////
// CWisdomWellServerDlg dialog

#define UM_CAR_RUN_AWAY		WM_USER + 1
#include "ConfigMgr.h"	// Added by ClassView
class CWisdomWellServerDlg : public CDialog
{
// Construction
public:
	CConfigMgr m_confMgr;
	void SendFrame(BYTE *bts,int len);
	void TopRfidTrigger(long rfidNum);
	void BottomRfidTrigger(long rfidNum);
	void SetTWG(int t,int t1,int t2,int w,int w1,float g);
	//void SetTWG(float t,float w,float g);			//设置温度、湿度、可燃气体浓度
	void SetT(float t);			//设置温度、湿度、可燃气体浓度
	void SetW(float w);			//设置温度、湿度、可燃气体浓度
	void SetG(float g);			//设置温度、湿度、可燃气体浓度
	void SetCarStatus(int pos,float v,int dir,int w);  //设置小车状态信息
	void SetWeight(float weight);//设置矿载
	void DrawPosition();
	CWisdomWellServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWisdomWellServerDlg)
	enum { IDD = IDD_WISDOMWELLSERVER_DIALOG };
	CButton	m_ctrlPositionRect;
	CButton	m_ctrlPosition;
	CString	m_strAvgYield;
	CString	m_strCarDirect;
	CString	m_strCarStatus;
	CString	m_strDailyYield;
	CString	m_strEmpAbsence;
	CString	m_empCurrent;
	CString	m_strEmpLeave;
	CString	m_strEmpShouldBe;
	CString	m_strEmpTotal;
	CString	m_strNowCarWeight;
	CString	m_strNowTime;
	CString	m_strNowWorkStatus;
	CString	m_strRealConcentration;
	CString	m_strRealHumidity;
	CString	m_strRealTemperature;
	CMSComm	m_Series;
	CString	m_NowCarSpeedV;
	CString	m_pCross;
	CString	m_CrossingStatus;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWisdomWellServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWisdomWellServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMgrEmployee();
	afx_msg void OnModifyPasswd();
	afx_msg void OnParamSetting();
	afx_msg void OnSamplingRecord();
	afx_msg void OnSysLog();
	afx_msg void OnCarrecord();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnOnCommMscomm();
	afx_msg void OnBtnTestComm();
	afx_msg void OnAbout();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnCarRunAway(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	
private:
//	int m_pCross_num_down;
//	int m_pCross_num_up;
	int m_empCurrent_num;
	int m_pCross_num;
	int m_nTimeDiff;
	int m_nPrevTime;
	//CModel m_mdlCar("car");
	BYTE m_btBuffer[1024]; //串口接收数据队列
	int m_iBuffLen;
    int m_pCurr;
	UINT m_currPosIndex;
	static int m_arrKeyPos[13][4];
	CMenu m_menuMain;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WISDOMWELLSERVERDLG_H__D3354C59_76AE_409B_AA15_BF433846BF11__INCLUDED_)
