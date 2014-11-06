/*******************************************************************************
**		Fliename:WisdomWellServerDlg.cpp
**      Description:应用程序主窗口、串口数据接收、系统状态显示
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "WisdomWellServerDlg.h"
#include "MSComm.h"
#include "DataDispatch.h"
#include "LoginDlg.h"
#include "ModifyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWisdomWellServerDlg dialog

CWisdomWellServerDlg::CWisdomWellServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWisdomWellServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWisdomWellServerDlg)
	m_strAvgYield = _T("");
	m_strCarDirect = _T("停止");
	m_strCarStatus = _T("载矿");//_T("");//m_strCarStatus = _T("载矿");
	m_strDailyYield = _T("");
	m_strEmpAbsence = _T("");
	m_empCurrent = _T("");
	m_strEmpLeave = _T("");
	m_strEmpShouldBe = _T("");
	m_strEmpTotal = _T("");
	m_strNowCarWeight = _T(" ");//_T("");//m_strNowCarWeight = _T("1000kg");
	m_strNowTime = _T("");
	m_strNowWorkStatus = _T("运行中");
	m_strRealConcentration = _T(" ");
	m_strRealHumidity = _T(" ");
	m_strRealTemperature = _T(" ");
	m_NowCarSpeedV = _T(" ");
	m_pCross = _T("");
	m_CrossingStatus = _T("空闲中");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iBuffLen = 1024;
    m_pCross_num=0;
	m_empCurrent_num=0;
	//m_pCross_num_up=0; 
	//m_pCross_num_down=0;
	//memcpy(m_btBuffer,0,sizeof(m_btBuffer));
	m_pCurr = 0;
	CConfigMgr conf;
//	m_mdlCar = new CModel("Car");
	m_nTimeDiff = atoi(conf.GetConfigItem(CString("TimeDiff"))) * 60;
}

void CWisdomWellServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWisdomWellServerDlg)
	DDX_Control(pDX, IDC_POSITIONGROUP, m_ctrlPositionRect);
	DDX_Control(pDX, IDC_DEVICESTATUSGROUP, m_ctrlPosition);
	DDX_Text(pDX, IDC_AVGYIELD, m_strAvgYield);
	DDX_Text(pDX, IDC_CARDIRECT, m_strCarDirect);
	DDX_Text(pDX, IDC_CARSTATUS, m_strCarStatus);
	DDX_Text(pDX, IDC_DAILYYIELD, m_strDailyYield);
	DDX_Text(pDX, IDC_EMPABSENCE, m_strEmpAbsence);
	DDX_Text(pDX, IDC_EMPCURRENT, m_empCurrent);
	DDX_Text(pDX, IDC_EMPLEAVE, m_strEmpLeave);
	DDX_Text(pDX, IDC_EMPSHOULDBE, m_strEmpShouldBe);
	DDX_Text(pDX, IDC_EMPTOTAL, m_strEmpTotal);
	DDX_Text(pDX, IDC_NOWCARWEIGHT, m_strNowCarWeight);
	DDX_Text(pDX, IDC_NOWTIME, m_strNowTime);
	DDX_Text(pDX, IDC_NOWWORKSTATUS, m_strNowWorkStatus);
	DDX_Text(pDX, IDC_REALCONCENTRATION, m_strRealConcentration);
	DDX_Text(pDX, IDC_REALHUMIDITY, m_strRealHumidity);
	DDX_Text(pDX, IDC_REALTEMPERATURE, m_strRealTemperature);
	DDX_Control(pDX, IDC_MSCOMM, m_Series);
	DDX_Text(pDX, IDC_NOWCARSPEED, m_NowCarSpeedV);
	DDX_Text(pDX, IDC_EMPCROSS, m_pCross);
	DDX_Text(pDX, IDC_CrossingStatus, m_CrossingStatus);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWisdomWellServerDlg, CDialog)
	//{{AFX_MSG_MAP(CWisdomWellServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_MGR_EMPLOYEE, OnMgrEmployee)
	ON_COMMAND(IDM_MODIFY_PASSWD, OnModifyPasswd)
	ON_COMMAND(IDM_PARAM_SETTING, OnParamSetting)
	ON_COMMAND(IDM_SAMPLING_RECORD, OnSamplingRecord)
	ON_COMMAND(IDM_SYS_LOG, OnSysLog)
	ON_COMMAND(IDM_CARRECORD, OnCarrecord)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_TEST_COMM, OnBtnTestComm)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CAR_RUN_AWAY, OnCarRunAway)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWisdomWellServerDlg message handlers
//开始事件映射


BOOL CWisdomWellServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//this->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1),FALSE);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	m_menuMain.LoadMenu(IDR_MAINMENU);
	SetMenu(&m_menuMain);
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1), TRUE);			// Set big icon
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1), FALSE);		// Set small icon

	//CClientDC dc(GetDlgItem(IDC_POSITIONGROUP));
	//CRect rect(0,0,100,100);
	//m_ctrlPositionRect.GetWindowRect(&rect);
	//ScreenToClient(&rect);

	//CBrush *brush = CBrush::FromHandle((HBRUSH)::GetStockObject(BLACK_BRUSH));
	//dc.FillRect(&rect,brush);
	// TODO: Add extra initialization here
	SetTimer(1,1000,NULL);
	//m_Series.SetCommPort(2);//weiyuan-chang 7.21!!!
	m_Series.SetInBufferSize(1024);
	m_Series.SetOutBufferSize(1024);
	CConfigMgr theConfig("WisdomWellServer.conf");  //打开配置文件
	if(m_Series.GetPortOpen())
	{
		m_Series.SetPortOpen(FALSE);
	}
	//CString portStr = theConfig.GetConfigItem(CString("comport"));  //获取串口号
	m_Series.SetCommPort(9);//weiyuan-chang 7.21!!!纬园串口设置
	
	
	//int port = atoi(portStr);
	//m_Series.SetCommPort(port);
	if(!m_Series.GetPortOpen())
	{
		m_Series.SetPortOpen(TRUE);
	}
	
	CString bitFreq = theConfig.GetConfigItem(CString("bitfreq")); //获取串口配置
	
	m_Series.SetSettings(bitFreq);
	m_Series.SetInputMode(1);      //表示以二进制方式检取数据
	m_Series.SetRThreshold(1);  	 //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
	m_Series.SetInputLen(0);       //一次读取缓冲区全部数据
	m_Series.GetInput();           //先预读缓冲区以清除残留数据
	
//	m_Series.SetInBufferCount(0);
//	m_Series.SetInBufferSize(1024);
//	m_Series.SetOutBufferCount(1);
//	m_Series.SetOutBufferSize(1024);

   // m_Series.SetOutput(COleVariant(CString("Welcome You1 !\n")));//------------ 
	//m_Series.SetInputLen(0);
	//	m_ctrComm.SetInBufferSize(1024);//设置输入缓冲区的大小，Bytes
    //	m_ctrComm.SetOutBufferSize(512);//设置输出缓冲区的大小，Bytes
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWisdomWellServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWisdomWellServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	
	DrawPosition();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWisdomWellServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWisdomWellServerDlg::OnMgrEmployee() 
{
	// TODO: Add your command handler code here
	CEmployeeDlg dlg;
	dlg.DoModal();
}

void CWisdomWellServerDlg::OnModifyPasswd() 
{
	// TODO: Add your command handler code here
	CLoginDlg ldlg;
	if(IDOK == ldlg.DoModal())
	{
		CModifyDlg dlg;
		dlg.DoModal();
	}
}

void CWisdomWellServerDlg::OnParamSetting() 
{
	// TODO: Add your command handler code here
	CLoginDlg ldlg;
	if(IDOK == ldlg.DoModal())
	{
		CSettingDlg dlg;
		dlg.DoModal();
	}
}

void CWisdomWellServerDlg::OnSamplingRecord() 
{
	// TODO: Add your command handler code here
	CSamplingDlg dlg;
	dlg.DoModal();
}

void CWisdomWellServerDlg::OnSysLog() 
{
	// TODO: Add your command handler code here
	CSysLogDlg dlg;
	dlg.DoModal();
}
int CWisdomWellServerDlg::m_arrKeyPos[13][4] = {
	300,39,310,49,
	260,39,270,49,
	240,50,250,60,
	220,61,230,71,
	200,72,210,82,
	180,83,190,93,
	160,94,170,104,
	140,105,150,115,
	120,116,130,126,
	100,127,110,137,
	80,138,90,148,								
	60,140,70,150,
    20,140,30,150
	/*
		20,140,30,150,
	60,140,70,150,
	80,138,90,148,
	100,127,110,137,
	120,116,130,126,
	140,105,150,115,
	160,94,170,104,
	180,83,190,93,
	200,72,210,82,
	220,61,230,71,
	240,50,250,60,
	260,39,270,49,
	300,39,310,49
	  */
	
};
void CWisdomWellServerDlg::OnCarrecord() 
{
	// TODO: Add your command handler code here
	CCarRecordDlg dlg;
	dlg.DoModal();
}

void CWisdomWellServerDlg::DrawPosition()
{
	
	CClientDC dc(this);
	CRect rect;
	m_ctrlPositionRect.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.top += 15;

	//HBRUSH bsh = (HBRUSH)GetClassLong(this->m_hWnd,GCL_HBRBACKGROUND);
	CBrush *pBrush = new CBrush(RGB(0xf5,0xf5,0xf5));
	//SetClassLong(this->m_hWnd,GCL_HBRBACKGROUND,(LONG)GetStockObject(BLACK_BRUSH));
/*	
	CPen pen(PS_SOLID , 5, RGB(0,0,0));
	CPen *pOldPen = dc.SelectObject(&pen);
	dc.FillRect(&rect,pBrush);
	dc.MoveTo(rect.left + 20,rect.top + 150);
	dc.LineTo(rect.left + 80,rect.top + 150);
	dc.LineTo(rect.left + 260,rect.top + 50);
	dc.LineTo(rect.left + 340,rect.top + 50);
	CPen dotPen(PS_SOLID ,1,RGB(200,0,0));
	dc.SelectObject(&dotPen);
	CBrush brush(RGB(200,0,0));
	dc.SelectObject(&brush);
	int i = 0;
	for(i = 0;i < 13;i ++)
	{
		if(i == m_currPosIndex)
		{
			CRect rctPos(rect.left + m_arrKeyPos[i][0],rect.top + m_arrKeyPos[i][1],
					 rect.left + m_arrKeyPos[i][2],rect.top + m_arrKeyPos[i][3]);
			dc.Ellipse(&rctPos);
		}
	}
*/

	delete pBrush;

}

void CWisdomWellServerDlg::OnTimer(UINT nIDEvent) 
{
//	m_Series.SetOutput(COleVariant(CString("Welcome You2 !\n")));  
	// TODO: Add your message handler code here and/or call default
	CTime tm = CTime::GetCurrentTime();
	m_strNowTime = tm.Format("%Y-%m-%d %H:%M:%S");

    ///////////////人员显示，因为不知为什么无法在那个函数中运用显示，所以暂时放置这里/////////////
    char strpCross[20];//02 06 00 01 05 01 
    char strempCurrent[20];
//    this->m_pCross_num=this->m_pCross_num_up+this->m_pCross_num_down;
	gcvt((float)this->m_pCross_num,4,strpCross);//m_pCross_num
	this->m_pCross = strpCross;
	this->m_pCross += "次";

	gcvt((float)this->m_empCurrent_num,4,strempCurrent);//m_pCross_num    m_pCross_num=0; m_empCurrent_num=0;	
    this->m_empCurrent = strempCurrent;
    this->m_empCurrent+= "次";
    


	if((this->m_pCross_num==0)&&strcmp(this->m_strCarDirect,"停止")==0)
	this->m_CrossingStatus="空闲中";

    if(strcmp(this->m_strCarDirect,"上行")==0)
    this->m_CrossingStatus="矿车上行中";

	if(strcmp(this->m_strCarDirect,"下行")==0)
    this->m_CrossingStatus="矿车下行中";

	/////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////
	CRect rect;
	m_ctrlPositionRect.GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(rect);
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}

void CWisdomWellServerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(IDOK == MessageBox("你确定要退出吗？","退出",MB_OKCANCEL))
	{
		CDialog::OnClose();
	}

}

BEGIN_EVENTSINK_MAP(CWisdomWellServerDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CWisdomWellServerDlg)
	ON_EVENT(CWisdomWellServerDlg, IDC_MSCOMM, 1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/** 串口有数据时触发 （串口事件）

*/
void CWisdomWellServerDlg::OnOnCommMscomm() 
{
//	MessageBox("aaaaaaaaaaaaaaa");
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	//int len;
	CString str;
	short eventFlag;
	TCHAR bufftemp;
	eventFlag = m_Series.GetCommEvent();
	CString sstr = "";

	switch (eventFlag)
	{
	case EV_RXFLAG: //事件值为2表示接收缓冲区内有字符
	                ////////以下你可以根据自己的通信协议加入处理代码weiyuan-change2014年7月22日15:35:56
	//	m_bShow = FALSE;
		variant_inp = m_Series.GetInput(); //读缓冲区
		safearray_inp = variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
		len = safearray_inp.GetOneDimSize(); //得到有效数据长度
		
		for(k = 0; k < len; k++)
		{
			safearray_inp.GetElement(&k, &bufftemp);//转换为BYTE型数组
		//	m_AImageData.push_back(bufftemp);
		//	sstr += bufftemp;
			if(m_pCurr == 0 && ((int)bufftemp > 0x04 && (int)bufftemp != 0xFF))
			{
				m_pCurr = 0;
				m_iBuffLen = 1024;
				//m_Series.SetOutput(COleVariant(CString((int)bufftemp))); 
				continue;
			}

			
			if(m_pCurr == 1)
			{
				//如果是紧急帧，长度为2
				if((BYTE)bufftemp == 0xFF) //FF 02 
				{
					m_iBuffLen = 2;
					//bufftemp = 0x02;
				    //break;
				}
				else
					m_iBuffLen = (int)bufftemp;
			}
			//为了防止程序被不正确的帧意外终止 将 == 改为  >=
			if(m_pCurr >= m_iBuffLen - 1)
			{
				m_btBuffer[m_pCurr] = bufftemp;
				CDataDispatch dd(m_btBuffer,m_iBuffLen,this);//!!!!
				dd.DispatchFrame();
				/*char s[1024] = {0};

				for(int j = 0;j < m_iBuffLen; j ++)
				{
					sprintf(s,"%s 0x%X ",s,m_btBuffer[j]);
				}*/
				m_pCurr = 0;
				m_iBuffLen = 1024;
				//Sleep(1000);
				
			}
			//else if(m_pCurr > m_iBuffLen - 1)
			//{
			//	m_pCurr = 0;
			//	m_iBuffLen = 1024;
			//}
			else
			{
				m_btBuffer[m_pCurr] = bufftemp;
				m_pCurr ++;
			}
		}
		
		//MessageBox(sstr);
		//	m_uiBytesRecved += len;
		//	if (m_dataprotocolstyle==1)
		//	{
			//	if (m_uiBytesRecved >= m_iRow*m_iColumn+m_iRow*2)
			//	{
			//		m_bShow = TRUE;
			//		Invalidate(TRUE);
		//		}          
		//	}
		//	if (m_dataprotocolstyle==0)
		//	{  
		//		if (m_uiBytesRecved >= m_iRow*m_iColumn)
		//		{
		//			m_bShow = TRUE;
		//			Invalidate(TRUE);
		//		}
		//	}
		break;
	case EV_CTS:
		break;
	default:
		break;
	}
    
}
/** 设置温度、湿度、可燃性气体浓度
	@param t:温度
	@param w:湿度
	@param g:可燃性气体浓度   02 08 00 01 10 FF FF FF    ->255 255 255 ------ok--weiyuan2014年7月22日20:38:21
//02 0B 00 08 10 00 06 01 34 01 00
    uartbuf[0] = UDCODE_TYPE_DATA;
    uartbuf[1] = 0x0b;
    uartbuf[2] = 0x00;
    uartbuf[3] = UDCODE_ZIGBEE_PC | UDCODE_ZIGBEE_WELL_TOP;
    uartbuf[4] = UDCODE_SOURCE_TWG;
    
	uartbuf[5] = Mk;
    uartbuf[6] = TmpH;
    uartbuf[7] = TmpL;
    
	uartbuf[8] = DHTOne;
    uartbuf[9] = DHTTwo;
    
	uartbuf[10] = MQResult;
    sendlength = 11;
*/
void CWisdomWellServerDlg::SetTWG(int t,int t1,int t2,int w,int w1,float g)//8650110-10
{

	char strT[20],strT1[20],strT2[20];
	char strW[20],strW1[20];
	char strG[20];
	//char* gas_dis="安全";
	
     //if(1)//(t==0)
	 //{
	 /// this->m_strRealTemperature = '+';//strT;//+ -
	 //}
	 //else
     // this->m_strRealTemperature = '-';//strT;//+ -
	 //gcvt((double)t,4,strT);
	 
	//this->m_strRealTemperature += "25";

	 if(t1>10&&t1<99)
	{
	 itoa( t1, strT1, 10 );
     this->m_strRealTemperature = '+';
	 this->m_strRealTemperature += strT1;
	 
	 //else
     //this->m_strRealTemperature = "+10";

	 itoa( t2, strT2, 10 );
	 
	 this->m_strRealTemperature += ".";
	 this->m_strRealTemperature += strT2;
	 this->m_strRealTemperature += "℃";
     }

	 itoa( w*10+w1, strW, 10 );
	 itoa( w1, strW1, 10 );
	 /*
	 itoa( w, strW, 10 );
	 itoa( w1, strW1, 10 );
     */
	 //gcvt((double)w,4,strW);
	 this->m_strRealHumidity = strW;
	 this->m_strRealHumidity += ".";
	 this->m_strRealHumidity += strW1;
	 this->m_strRealHumidity += "%";

	

	//gcvt((double)g,4,strG);
	//this->m_strRealConcentration = strG;
	//this->m_strRealConcentration += "%";
      if(g==0)
	 {
	  this->m_strRealConcentration = "安全";//strT;//+ -
	  //gas_dis="安全";
	 }
	 else
	 {
      this->m_strRealConcentration = "超标";//strT;//+ -
	  //gas_dis="超标";//
	  g=50;
	 }
	CUTime tNow;

	if(1)//tNow.GetUnixTime() - m_nPrevTime > m_nTimeDiff)
	{
		CModel m("sampling");
		char data[255] = {0};

		//sprintf(data,"null,%d,%f,%f,%f",tNow.GetUnixTime(),t1,w,g);
		sprintf(data,"null,%d,%d,%d,%d",tNow.GetUnixTime(),t1,w*10+w1,(int)g);
		m.Insert(data);
	}


	m_nPrevTime = tNow.GetUnixTime();
	//AfxMessageBox("aaaaaaaa");
	UpdateData(FALSE);
	//UpdateData();

/*

	char strT[20];
	char strW[20];
	char strG[20];
	

	 gcvt((double)t,4,strT);
	 this->m_strRealTemperature = strT;
	 this->m_strRealTemperature += "℃";

	

	gcvt((double)w,4,strW);
	this->m_strRealHumidity = strW;
	this->m_strRealHumidity += "%";

	

	gcvt((double)g,4,strG);
	this->m_strRealConcentration = strG;
	this->m_strRealConcentration += "%";
    
	CUTime tNow;

	if(1)//tNow.GetUnixTime() - m_nPrevTime > m_nTimeDiff)
	{
		CModel m("sampling");
		char data[255] = {0};

		sprintf(data,"null,%d,%f,%f,%f",tNow.GetUnixTime(),t,w,g);
		m.Insert(data);
	}


	m_nPrevTime = tNow.GetUnixTime();
	//AfxMessageBox("aaaaaaaa");
	UpdateData(FALSE);
	//UpdateData();
*/
}

/** 设置温度
	@param t:温度
    02 06 00 00 01 FF     ->255  ------ok--weiyuan2014年7月22日20:38:21
*/
void CWisdomWellServerDlg::SetT(float t)//8650110-1
{
	CUTime tNow;


	char strT[20];

	

	 gcvt((double)t,4,strT);
	 this->m_strRealTemperature = strT;
	 this->m_strRealTemperature += "℃";



	m_nPrevTime = tNow.GetUnixTime();
	//AfxMessageBox("aaaaaaaa");
	UpdateData(FALSE);
	//UpdateData();
}

/** 设置湿度
	@param w:湿度
	02 06 00 00 02 FF     ->255  ------ok--weiyuan2014年7月22日20:38:21
*/
void CWisdomWellServerDlg::SetW(float w)//8650110-2
{
	char strW[20];
	gcvt((double)w,4,strW);
	this->m_strRealHumidity = strW;
	this->m_strRealHumidity += "%";
}

/** 设置气体浓度
	@param g:气体浓度
	02 06 00 00 03 FF     ->255  ------ok--weiyuan2014年7月22日20:38:21
*/
void CWisdomWellServerDlg::SetG(float g)//8650110-3
{
	char strG[20];	
	gcvt((double)g,4,strG);
	this->m_strRealConcentration = strG;
	this->m_strRealConcentration += "%";
}

/** 设置矿载
	@param weight:矿载
	02 06 00 00 04 FF     ->255  ------ok--weiyuan2014年7月22日20:38:21
*/
void CWisdomWellServerDlg::SetWeight(float weight)//8650110-4
{
	if(weight<20)
    weight=0;
	char strWeight[20];
	gcvt((double)weight,4,strWeight);
	this->m_strNowCarWeight = strWeight;
	this->m_strNowCarWeight += "g";
	CModel mdlCar("car");
	char data[50] = {0};
	CUTime tNow;
	//sprintf(data,"%d,%s,%s",tNow.GetUnixTime(),strWeight,strWeight);
	//mdlCar.Insert(data);


  //  m_mdlCar->Insert(data);
	//m_strDailyYield  m_strAvgYield
}

void CWisdomWellServerDlg::OnBtnTestComm() 
{
	// TODO: Add your control notification handler code here
/*	CUTime t(1403487223);
	int ts = t.GetUnixTime();
	CUTime t2(t.m_year,t.m_mon,t.m_day,t.m_h,t.m_m,t.m_s);
	int t2s = t2.GetUnixTime(); 
	*/
	long *s;
	long num = 100110;
	s = &num;
	BYTE b[1024];
	b[0] = 0x02;
	b[1] = sizeof(s) + 5;
	b[2] = 0xff;
	b[3] = 0xff;
	b[4] = 0x05;
	memcpy(&b[5],(void *)&num,sizeof(long));
	CDataDispatch d(b,sizeof(long) + 5,this);
	d.DispatchFrame();
}
/**** 设置车的状态   8650110-7
	@param pos:位置
	@param dir:方向
	@param v:速度
	@param w:是否跑车     02 09 00 01 07 3B 03 32 30 

  	int position;	//矿车位置： //1-11红外编号--》31--1      --》3B--11
	char velocity;	//矿车速度            FF--》255           00--》0
	int direction;	//0停止 1向上 2向下  --》30-0 --》31--1 --》32--2
	int HarvMon_warn;	//0正常 1跑车    --》30-0 --》31--1
*/

void CWisdomWellServerDlg::SetCarStatus(int pos, float v,int dir ,int w)
{
  if(m_pCross_num==0)
  {
	char strV[20];
	                                         //UpdateData(FALSE);//UpdateData(TRUE);
	gcvt((double)v,4,strV);
	this->m_NowCarSpeedV = strV;
	this->m_NowCarSpeedV += "M/S";           //m_NowCarSpeedV
    
	pos-=48;//换算 0-》30-》48
	dir-=48;
	w-=48;
                                              //dir=0;//this->m_strCarDirect = dir == 0 ? "下行" : "上行";//0-下行
	if(dir==0)
    this->m_strCarDirect ="停止";
	else if(dir==1)
    this->m_strCarDirect ="上行";
	else if(dir==2)
    this->m_strCarDirect ="下行";


	                                                                                                     //pos=11;
	this->m_currPosIndex = pos > 0 && pos < 12 ? pos : m_currPosIndex;                                   //1-11 
	
	                                                                                                      //w=0;
	if(w == 1)
	{
		PostMessage(UM_CAR_RUN_AWAY,(WPARAM)pos,0); //跑车，向系统发送跑车消息
	}
  }                                            //UpdateData(FALSE);
}

/** 处理跑车消息   8650110-f
	@param wParam:发生跑车的位置
	@param lParam:附加参数,未用    FF 02  --待OK!!!
*/

void CWisdomWellServerDlg::OnCarRunAway(WPARAM wParam,LPARAM lParam)
{
	CModel m("log");

	CUTime uTime;
	char data[1024];
	sprintf(data,"null,'矿车发生跑车','关闭安全门，停止卷扬机，报警',%d,%d",wParam,uTime.GetUnixTime());
	m.Insert(data);
	//	MessageBox("啊，跑车了");
	
}
/** 井上RFID触发   8650110-5
	@param rfidNum:射频卡ID号    02 06 00 01 05 01     ->255 255 255 ------?ok
*/
void CWisdomWellServerDlg::TopRfidTrigger(long rfidNum)
{
  if(strcmp(this->m_strCarDirect,"停止")==0)//由于老师说现场操作只用一张RFID,为了防止发送多了数据帧
  {
	CModel m("record");

	char data[255];
	CUTime now;
	//sprintf(data,"null,'%ld',%d,0",(int)2,now.GetUnixTime());//weiyuan1
	sprintf(data,"null,'%ld',%d,0",(int)1,now.GetUnixTime());//weiyuan1

    m_empCurrent_num=1;//m_empCurrent_num++;
	//m_pCross_num++;
	//m_pCross_num++;
	//sprintf(data,"null,'%ld',%d,1",rfidNum,now.GetUnixTime());//haihua
	//MessageBox(data);
	if(m.Insert(data))
	{


		//m_empCurrent_num
		//打卡记录插入成功，身分验证通过
     // if(m_pCross_num_down<=0)//准备下井//m_pCross_num_up m_pCross_num_down
	//	{
		// m_pCross_num++;
		 //m_empCurrent_num++;//02 08 00 01 10 FF FF FF 
	//	}


		//    m_pCross_num=0;
	    //m_empCurrent_num=0;
		//
	}
	else
	{
		//打卡记录插入失败，身份验证失败
	}
  }
}
/** 井下RFID触发  8650110-6
	@param rfidNum:射频卡ID号  02 06 00 01 06 01    ->255 255 255 ------?ok
*/
void CWisdomWellServerDlg::BottomRfidTrigger(long rfidNum)
{
   if(strcmp(this->m_strCarDirect,"停止")==0)
   {
	//if(m_empCurrent_num>0)
	{
	CModel m("record");
	char data[255];
	CUTime now;
	
	//sprintf(data,"null,'%ld',%d,1",(int)2,now.GetUnixTime());
    sprintf(data,"null,'%ld',%d,0",(int)1,now.GetUnixTime());//weiyuan1
	m_pCross_num=1;//m_pCross_num++;
	//sprintf(data,"null,'%ld',%d,0",rfidNum,now.GetUnixTime());//haihua
	//MessageBox(data);
	if(m.Insert(data))
	{
		//m_pCross_num++;
		//打卡记录插入成功，身分验证通过
		/*
		if(m_pCross_num>0)//有人下井//m_pCross_num_up m_pCross_num_down
		{
		 m_pCross_num_up--;
		 m_empCurrent_num++;//02 08 00 01 10 FF FF FF 
		}

		else//if(m_empCurrent_num>0&&m_pCross_num_up<=0)//准备上井//m_pCross_num_up m_pCross_num_down
		{
		 m_pCross_num_down++;
		 m_empCurrent_num--;//02 08 00 01 10 FF FF FF 
		}

		*/
		 //    m_pCross_num=0;
	    //m_empCurrent_num=0;
	}
	else
	{
		//打卡记录插入失败，身分验证不通过
	}
	}
   }
}
/** 向串口发送一个帧
	@param:bts 发送的内容
	@param:len 帧的长度    
*/
void CWisdomWellServerDlg::SendFrame(BYTE *bts, int len)
{
	CByteArray btArr;
	for(int i = 0;i < len;i ++)
	{
		btArr.Add(bts[i]);
	}
	
	this->m_Series.SetOutput(COleVariant(btArr));
}

void CWisdomWellServerDlg::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

HBRUSH CWisdomWellServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
		 if (pWnd-> GetDlgCtrlID() == IDC_STATIC_1 || pWnd-> GetDlgCtrlID() == IDC_STATIC_2 || pWnd-> GetDlgCtrlID() == IDC_STATIC
			 || pWnd-> GetDlgCtrlID() == IDC_NOWWORKSTATUS || pWnd-> GetDlgCtrlID() == IDC_STATIC_3)
	 {
	  pDC->SetBkMode(TRANSPARENT);   //设置背景透明
	  //pDC->SetTextColor(RGB(255,255,255));
	  return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	 }

	// TODO: Return a different brush if the default is not desired
	return hbr;
}
