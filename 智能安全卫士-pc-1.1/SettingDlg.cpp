/*******************************************************************************
**		Fliename:SettingDlg.h
**      Description:
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/
#include "stdafx.h"
#include "WisdomWellServer.h"
#include "SettingDlg.h"
#include "ConfigMgr.h"
#include "UTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	CUTime tNow;

	//{{AFX_DATA_INIT(CSettingDlg)
	m_strMaxGas = m_confMgr.GetConfigItem("MaxGas");
	m_strMaxTemp = m_confMgr.GetConfigItem("MaxTemp");;
	m_strPassword = m_confMgr.GetConfigItem("Password");;
	m_strPhoneNum = m_confMgr.GetConfigItem("PhoneNum");;
	m_nRealTimeHour = tNow.m_h;
	m_nRealTimeMin = tNow.m_m;
	m_nRealTimeSec = tNow.m_s;
	m_nSafeWeight = atoi(m_confMgr.GetConfigItem("SafeWeight"));
	m_nTimeAftOffHour = atoi(m_confMgr.GetConfigItem("TimeAftOffHour"));
	m_nTimeAftOffMin = atoi(m_confMgr.GetConfigItem("TimeAftOffMin"));
	m_nTimeAftOnHour = atoi(m_confMgr.GetConfigItem("TimeAftOnHour"));
	m_nTimeAftOnMin = atoi(m_confMgr.GetConfigItem("TimeAftOnMin"));
	m_nTimeDiff = atoi(m_confMgr.GetConfigItem("TimeDiff"));
	m_nTimeMorOffHour = atoi(m_confMgr.GetConfigItem("TimeMorOffHour"));
	m_nTimeMorOffMin = atoi(m_confMgr.GetConfigItem("TimeMorOffMin"));
	m_nTimeMorOnHour = atoi(m_confMgr.GetConfigItem("TimeMorOnHour"));
	m_nTimeMorOnMin = atoi(m_confMgr.GetConfigItem("TimeMorOnMin"));
	m_nVMechine = atoi(m_confMgr.GetConfigItem("VMechine"));
	m_strCurrDate = tNow.GetTime();
	//}}AFX_DATA_INIT

	//SetTimer(1,1000,NULL);
	
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Text(pDX, IDC_MAXGAS, m_strMaxGas);
	DDX_Text(pDX, IDC_MAXTEMP, m_strMaxTemp);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_PHONENUM, m_strPhoneNum);
	DDX_Text(pDX, IDC_REALTIME_HOUR, m_nRealTimeHour);
	DDX_Text(pDX, IDC_REALTIME_MIN, m_nRealTimeMin);
	DDX_Text(pDX, IDC_REALTIME_SEC, m_nRealTimeSec);
	DDX_Text(pDX, IDC_SAFEWEIGHT, m_nSafeWeight);
	DDX_Text(pDX, IDC_TIMEAFTOFFHOUR, m_nTimeAftOffHour);
	DDX_Text(pDX, IDC_TIMEAFTOFFMIN, m_nTimeAftOffMin);
	DDX_Text(pDX, IDC_TIMEAFTONHOUR, m_nTimeAftOnHour);
	DDX_Text(pDX, IDC_TIMEAFTONMIN, m_nTimeAftOnMin);
	DDX_Text(pDX, IDC_TIMEDIFF, m_nTimeDiff);
	DDX_Text(pDX, IDC_TIMEMOROFFHOUR, m_nTimeMorOffHour);
	DDX_Text(pDX, IDC_TIMEMOROFFMIN, m_nTimeMorOffMin);
	DDX_Text(pDX, IDC_TIMEMORONHOUR, m_nTimeMorOnHour);
	DDX_Text(pDX, IDC_TIMEMORONMIN, m_nTimeMorOnMin);
	DDX_Text(pDX, IDC_VMECHINE, m_nVMechine);
	DDX_DateTimeCtrl(pDX, IDC_CURRDATE, m_strCurrDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_WM_TIMER()
	ON_NOTIFY(DTN_CLOSEUP, IDC_CURRDATE, OnCloseupCurrdate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_CURRDATE, OnDatetimechangeCurrdate)
	ON_EN_CHANGE(IDC_REALTIME_HOUR, OnChangeRealtimeHour)
	ON_EN_CHANGE(IDC_REALTIME_MIN, OnChangeRealtimeMin)
	ON_EN_CHANGE(IDC_REALTIME_SEC, OnChangeRealtimeSec)
	ON_EN_SETFOCUS(IDC_REALTIME_SEC, OnSetfocusRealtimeSec)
	ON_EN_KILLFOCUS(IDC_REALTIME_SEC, OnKillfocusRealtimeSec)
	ON_EN_SETFOCUS(IDC_REALTIME_MIN, OnSetfocusRealtimeMin)
	ON_EN_KILLFOCUS(IDC_REALTIME_MIN, OnKillfocusRealtimeMin)
	ON_EN_SETFOCUS(IDC_REALTIME_HOUR, OnSetfocusRealtimeHour)
	ON_EN_KILLFOCUS(IDC_REALTIME_HOUR, OnKillfocusRealtimeHour)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

CString CSettingDlg::IntToString(int i)
{
	char ch[20];
	itoa(i,ch,10);
	return CString(ch);
}

CSettingDlg::~CSettingDlg()
{


}

void CSettingDlg::OnBtnOk() 
{
	UpdateData();
	// TODO: Add your control notification handler code here
	m_confMgr.SetConfigItem("MaxGas",CString(m_strMaxGas));
	m_confMgr.SetConfigItem("MaxTemp",CString(m_strMaxTemp));
	m_confMgr.SetConfigItem("Password",CString(m_strPassword));
	m_confMgr.SetConfigItem("PhoneNum",CString(m_strPhoneNum));

	m_confMgr.SetConfigItem("TimeMorOnHour",IntToString(m_nTimeMorOnHour));
	m_confMgr.SetConfigItem("TimeMorOnMin",IntToString(m_nTimeMorOnMin));
	m_confMgr.SetConfigItem("TimeMorOffHour",IntToString(m_nTimeMorOffHour));
	m_confMgr.SetConfigItem("TimeMorOffMin",IntToString(m_nTimeMorOffMin));

	m_confMgr.SetConfigItem("TimeAftOnHour",IntToString(m_nTimeAftOnHour));
	m_confMgr.SetConfigItem("TimeAftOnMin",IntToString(m_nTimeAftOnMin));
	m_confMgr.SetConfigItem("TimeAftOffHour",IntToString(m_nTimeAftOffHour));
	m_confMgr.SetConfigItem("TimeAftOffMin",IntToString(m_nTimeAftOffMin));

	m_confMgr.SetConfigItem("SafeWeight",IntToString(m_nSafeWeight));
	m_confMgr.SetConfigItem("TimeDiff",IntToString(m_nTimeDiff));
	m_confMgr.SetConfigItem("VMechine",IntToString(m_nVMechine));
	m_confMgr.SaveConfig();
	CDialog::OnOK();
}

void CSettingDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CSettingDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CUTime tNow;
	
	m_nRealTimeHour = tNow.m_h;
	m_nRealTimeMin = tNow.m_m;
	m_nRealTimeSec = tNow.m_s;
	SetDlgItemText(IDC_REALTIME_HOUR,IntToString(m_nRealTimeHour));
	SetDlgItemText(IDC_REALTIME_MIN,IntToString(m_nRealTimeMin));
	SetDlgItemText(IDC_REALTIME_SEC,IntToString(m_nRealTimeSec));
	//UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}

BOOL CSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg::OnCloseupCurrdate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CSettingDlg::OnDatetimechangeCurrdate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetRealTime();
	*pResult = 0;
}

void CSettingDlg::SetRealTime()
{
	UpdateData();
	KillTimer(1);
	SYSTEMTIME setTime;
	CTime t;
	((CDateTimeCtrl *)GetDlgItem(IDC_CURRDATE))->GetTime(t);
	//memcpy((void *)&setTime,0,sizeof(SYSTEMTIME));
	setTime.wYear = t.GetYear();
	setTime.wMonth =t.GetMonth();
	setTime.wDay = t.GetDay();
	setTime.wHour = ((WORD)m_nRealTimeHour + 24 - 8) % 24;
	setTime.wMinute = (WORD)m_nRealTimeMin;
	setTime.wSecond =(WORD)m_nRealTimeSec;
	setTime.wMilliseconds = 0;
	SetSystemTime(&setTime);
	SetTimer(1,1000,NULL);
}

void CSettingDlg::OnChangeRealtimeHour() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	//SetRealTime();
	// TODO: Add your control notification handler code here
	
}

void CSettingDlg::OnChangeRealtimeMin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	//SetRealTime();
	// TODO: Add your control notification handler code here
	
}

void CSettingDlg::OnChangeRealtimeSec() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// SetRealTime();
	// TODO: Add your control notification handler code here
	
}

void CSettingDlg::OnSetfocusRealtimeSec() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
}

void CSettingDlg::OnKillfocusRealtimeSec() 
{
	// TODO: Add your control notification handler code here
	SetRealTime();
	SetTimer(1,1000,NULL);
}

void CSettingDlg::OnSetfocusRealtimeMin() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);

}

void CSettingDlg::OnKillfocusRealtimeMin() 
{
	// TODO: Add your control notification handler code here
	SetRealTime();
	SetTimer(1,1000,NULL);

}

void CSettingDlg::OnSetfocusRealtimeHour() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
}

void CSettingDlg::OnKillfocusRealtimeHour() 
{
	// TODO: Add your control notification handler code here
	SetRealTime();
	SetTimer(1,1000,NULL);
}
