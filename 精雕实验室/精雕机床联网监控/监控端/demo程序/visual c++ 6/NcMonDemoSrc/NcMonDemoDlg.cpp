// NcMonDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NcMonDemo.h"
#include "NcMonDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CPropertyPage
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

CAboutDlg::CAboutDlg() : CPropertyPage(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNcMonDemoDlg dialog

CNcMonDemoDlg::CNcMonDemoDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CNcMonDemoDlg::IDD)
{
	//{{AFX_DATA_INIT(CNcMonDemoDlg)
	m_csIPAddress;// = _T("192.168.200.211");
	m_csMachDir = _T("F:\\En3D_Dat\\Usr\\Rcv\\");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nTimerIDEvent = 0;
	m_bIsSendingFile = FALSE;
}

void CNcMonDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNcMonDemoDlg)
	DDX_Text(pDX, IDC_EDIT_IPADDRSS, m_csIPAddress);
	DDX_Text(pDX, IDC_EDIT_MACH_DIR, m_csMachDir);
	DDX_Control(pDX, IDC_PROGRESS_SENDFILE, m_ProgCtrl);
	DDX_Control(pDX, IDC_LIST_FILE, m_ListBoxFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNcMonDemoDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CNcMonDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, OnButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_BROWSEFILE, OnButtonBrowseFile)
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE,   OnButtonSendFile)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH,   OnButtonRefreshFileList)
	ON_BN_CLICKED(IDC_BUTTON_DEL,   OnButtonDelFile)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, OnButtonDownloadFile)
	ON_BN_CLICKED(IDC_BUTTON_RENAME, OnButtonRenameFile)
	ON_BN_CLICKED(IDC_BUTTON_MACHTIME_RECORD, OnButtonGetWorkpieceMachTimeRecord)
	ON_BN_CLICKED(IDC_BUTTON_BROWSENC, OnButtonBrowseNcFile)
	ON_BN_CLICKED(IDC_BUTTON_SENDNC, OnButtonSendNcFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNcMonDemoDlg message handlers

BOOL CNcMonDemoDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	static int nIDEvt = 1;
	m_nTimerIDEvent = SetTimer(nIDEvt, 1200, NULL);
	nIDEvt++;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNcMonDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CPropertyPage::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNcMonDemoDlg::OnPaint() 
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
		CPropertyPage::OnPaint();
	}
}

HCURSOR CNcMonDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNcMonDemoDlg::OnButtonConnect() 
{
	if(m_JDMachMon.IsConncect())
		OnButtonDisconnect();
	UpdateData();
	if(!m_JDMachMon.ConnectJDMach(m_csIPAddress))
	{
		AfxMessageBox("连接失败");
		return;
	}
	
	AfxMessageBox("连接成功");

	OnButtonRefreshFileList();
}

void CNcMonDemoDlg::ErrHandle()
{
	//{ 当连接不正常，无法获得机床位置时，关闭计时器
	KillTimer(m_nTimerIDEvent);
	m_nTimerIDEvent = 0;

	CString csIPAddr;
	CWnd * pWnd = GetDlgItem(IDC_EDIT_IPADDRSS);
	if(pWnd != NULL)
		pWnd->GetWindowText(csIPAddr);
	AfxMessageBox(csIPAddr + ":通讯连接中断");
}

void CNcMonDemoDlg::OnTimer(UINT nIDEvent) 
{
	CPropertyPage::OnTimer(nIDEvent);

	double dMachCoord[3], dAbsCoord[3], dRelCoord[3];
	if(m_JDMachMon.GetMachPos(dMachCoord, dAbsCoord, dRelCoord))
	{//获取POS
		char csCoord[512];
		CWnd * pWnd = GetDlgItem(IDC_EDIT_MACH_COORD);
		if(pWnd != NULL ) 
		{		
			sprintf(csCoord,"%.4f %.4f %.4f", dMachCoord[0], dMachCoord[1], dMachCoord[2]);
			pWnd->SetWindowText(csCoord);
		}
		
		pWnd = GetDlgItem(IDC_EDIT_ABS_COORD);
		if(pWnd != NULL ) 
		{		
			sprintf(csCoord,"%.4f %.4f %.4f", dAbsCoord[0], dAbsCoord[1], dAbsCoord[2]);
			pWnd->SetWindowText(csCoord);
		}
		
		pWnd = GetDlgItem(IDC_EDIT_REL_COORD);
		if(pWnd != NULL ) 
		{		
			sprintf(csCoord,"%.4f %.4f %.4f", dRelCoord[0], dRelCoord[1], dRelCoord[2]);
			pWnd->SetWindowText(csCoord);
		}
	}

	int nAlmInfo = 0;
	if(m_JDMachMon.GetMachAlmInfo(nAlmInfo))
	{//获取报警信息
		enum NcAlmInfo 
		{ 
			NCALM_NO,         //无报警
			NCALM_EMG,        //急停
			NCALM_ERR,        //报警
			NCALM_UPS,        //外部电源已掉电
			NCALM_PROMPT      //提示
		};

		char csAlmInfo[64];
		csAlmInfo[0] = '\0';
		if(nAlmInfo == NCALM_NO)			strcpy(csAlmInfo, "无报警");
		else if(nAlmInfo == NCALM_EMG)		strcpy(csAlmInfo, "急停");
		else if(nAlmInfo == NCALM_ERR)		strcpy(csAlmInfo, "报警");
		else if(nAlmInfo == NCALM_UPS)		strcpy(csAlmInfo, "外部电源已掉电");
		else if(nAlmInfo == NCALM_PROMPT)	strcpy(csAlmInfo, "提示");

		CWnd * pWnd = GetDlgItem(IDC_EDIT_ALMINFO);
		if(pWnd != NULL ) 
			pWnd->SetWindowText(csAlmInfo);
	}

	int nProgState = 0;
	if(m_JDMachMon.GetProgState(nProgState))
	{//获取程控状态
		enum NcProgState
		{
			NCPROG_STOP,      //停止态
			NCPROG_RUN,       //执行态
			NCPROG_PAUSE,     //暂停态
			NCPROG_RESET,     //复位态
		};
		
		char csProgState[64];
		csProgState[0] = '\0';
		if(nProgState == NCPROG_STOP)			strcpy(csProgState, "停止态");
		else if(nProgState == NCPROG_RUN)		strcpy(csProgState, "执行态");
		else if(nProgState == NCPROG_PAUSE)		strcpy(csProgState, "暂停态");
		else if(nProgState == NCPROG_RESET)		strcpy(csProgState, "复位态");
		
		CWnd * pWnd = GetDlgItem(IDC_EDIT_PROG_STATE);
		if(pWnd != NULL ) 
			pWnd->SetWindowText(csProgState);
	}

	float Feedrate, MachTime;
	int  nCurrWCoord, SpindleSpeed, ToolNo, CurrO, CurrMainO ;
	if(m_JDMachMon.GetBasicModalInfo(nCurrWCoord, Feedrate, SpindleSpeed, ToolNo, MachTime,CurrO, CurrMainO))
	{//获取基本模态信息
		CWnd * pWnd = GetDlgItem(IDC_EDIT_CURR_WCOORD);
		if(pWnd != NULL ) 
		{		
			CString csCurrWCoord;
			csCurrWCoord.Format("G%d", nCurrWCoord);
			pWnd->SetWindowText(csCurrWCoord);
		}

		CString csCurrItem;
		pWnd = GetDlgItem(IDC_EDIT_CURR_F);
		csCurrItem.Format("%.2f", Feedrate);
		if(pWnd != NULL ) 	pWnd->SetWindowText(csCurrItem);

		pWnd = GetDlgItem(IDC_EDIT_CURR_S);
		csCurrItem.Format("%d", SpindleSpeed);
		if(pWnd != NULL ) 	pWnd->SetWindowText(csCurrItem);

		pWnd = GetDlgItem(IDC_EDIT_CURR_T);
		csCurrItem.Format("%d", ToolNo);
		if(pWnd != NULL ) 	pWnd->SetWindowText(csCurrItem);

		pWnd = GetDlgItem(IDC_EDIT_MACHTIME);
		csCurrItem.Format("%.2f", MachTime);
		if(pWnd != NULL ) 	pWnd->SetWindowText(csCurrItem);

		pWnd = GetDlgItem(IDC_EDIT_CURR_O);
		csCurrItem.Format("%d", CurrO);
		if(pWnd != NULL ) 	pWnd->SetWindowText(csCurrItem);

		pWnd = GetDlgItem(IDC_EDIT_CURR_MAINO);
		csCurrItem.Format("%d", CurrMainO);
		if(pWnd != NULL ) 	pWnd->SetWindowText(csCurrItem);
	}

	//get last err code
	UINT nLastErr = m_JDMachMon.GetLastErr();
	CString csCurrItem;
	csCurrItem.Format("%d", nLastErr);
	CWnd * pWnd = GetDlgItem(IDC_EDIT_GETLASTERR);
	if(pWnd != NULL) pWnd->SetWindowText(csCurrItem);

	if(m_bIsSendingFile && !m_JDMachMon.IsSendingFile())
		OnButtonRefreshFileList();
	m_bIsSendingFile = m_JDMachMon.IsSendingFile();
}

void CNcMonDemoDlg::OnButtonDisconnect() 
{
	if(m_JDMachMon.DisConnectJDMach())
	{		
	}
}

void CNcMonDemoDlg::OnButtonBrowseFile() 
{
	CString file;
	CString ext;
	CString str;
	
	str = "JDPaint加工文件(*.eng)|*.eng|GCode加工文件(*.nc)|*.nc|En3D8加工文件(*.en8)|*.en8|En3D8任务文件(*.tsk)|*.tsk||\n";
	CFileDialog dlgFile(TRUE, NULL, NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	
	
	if(dlgFile.DoModal() == IDOK)
	{
		CWnd * pWnd = GetDlgItem(IDC_EDIT_FILEPATH);
		if(pWnd != NULL)
			pWnd->SetWindowText(dlgFile.GetPathName());
	}
	
}

void SetProgPos(void *pProgCtrl, int ProgPos)
{
	CProgressCtrl * p = (CProgressCtrl*)pProgCtrl;
	if(p != NULL && p->GetSafeHwnd())
		p->SetPos(ProgPos);
}

void CNcMonDemoDlg::OnButtonSendFile()
{
	if(m_JDMachMon.IsSendingFile())
	{
		AfxMessageBox("正在发送文件，请稍后再发送");
		return;
	}
	CWnd * pWnd = GetDlgItem(IDC_BUTTON_SENDFILE);
	if(pWnd != NULL)
		pWnd->EnableWindow(FALSE);

	pWnd = GetDlgItem(IDC_EDIT_FILEPATH);
	CButton * pChkBtn = (CButton *)GetDlgItem(IDC_CHECK_ADDTASK);
	if(pWnd != NULL && pChkBtn != NULL)
	{
		CString csFileName;
		pWnd->GetWindowText(csFileName);

		int nStrLen = csFileName.GetLength();
		if(nStrLen > 400)
		{
			AfxMessageBox("路径超长");
			goto SendEndLine;
		}
		else if(nStrLen < 1)
		{
			AfxMessageBox("文件名为空");
			goto SendEndLine;
		}

		CFile cfile;
		if(cfile.Open(csFileName, CFile::modeRead))
		{
			m_ProgCtrl.SetRange(0, cfile.GetLength()/1024/1024);
			cfile.Close();
		}

		//test
		m_JDMachMon.SendFile(csFileName, pChkBtn->GetCheck(), &m_ProgCtrl, SetProgPos);
		//OnButtonRefreshFileList();
	}

SendEndLine:
	pWnd = GetDlgItem(IDC_BUTTON_SENDFILE);
	if(pWnd != NULL)
		pWnd->EnableWindow(TRUE);
}

void CNcMonDemoDlg::OnButtonRefreshFileList()
{
	UpdateData();

	int nCurSel = m_ListBoxFile.GetCurSel();
	CString csCusSel;
	if(nCurSel >= 0 && nCurSel < m_ListBoxFile.GetCount())
		m_ListBoxFile.GetText(nCurSel, csCusSel);
	int nOldScrolPos = m_ListBoxFile.GetScrollPos(SB_VERT);

	m_ListBoxFile.ResetContent();
	if(m_JDMachMon.IsConncect())
	{
		if(!m_JDMachMon.IsSendingFile())
			m_JDMachMon.SetMachRcvFolder(m_csMachDir);

		char csFileList[102400];
		memset(csFileList, 0, sizeof(csFileList));

		m_JDMachMon.GetMachFileList(m_csMachDir, 102400, csFileList );
		const char * p = csFileList;
		while(p && *p != '\0')
		{
			int nstrlen = strlen(p);
			m_ListBoxFile.AddString(p);
			p += nstrlen + 1;
		}
	}

	m_ListBoxFile.SetScrollPos(SB_VERT, nOldScrolPos);
	if(csCusSel.GetLength() > 0)
		m_ListBoxFile.SelectString(0, csCusSel);
}

void CNcMonDemoDlg::OnButtonDelFile()
{
	UpdateData();
	if(m_JDMachMon.IsConncect())
	{		
		int nCurrSel = m_ListBoxFile.GetCurSel();
		if(nCurrSel >=0 && nCurrSel < m_ListBoxFile.GetCount())
		{
			CString csCurrSelFile;
			m_ListBoxFile.GetText(nCurrSel, csCurrSelFile);

			if(AfxMessageBox("确定删除选中的文件或文件夹?", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				m_JDMachMon.DelMachFile(m_csMachDir, csCurrSelFile);

				OnButtonRefreshFileList();
			}
		}
	}
}

void CNcMonDemoDlg::OnButtonDownloadFile()
{
	UpdateData();
	if(m_JDMachMon.IsConncect())
	{		
		int nCurrSel = m_ListBoxFile.GetCurSel();
		if(nCurrSel >=0 && nCurrSel < m_ListBoxFile.GetCount())
		{
			CString csCurrSelFile;
			m_ListBoxFile.GetText(nCurrSel, csCurrSelFile);
			
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char cext[_MAX_EXT];
			_splitpath(csCurrSelFile, drive,dir,fname,cext);
			
			if(strlen(cext) > 0)
			{//存在后缀名,为文件，下载之
				
				CString csFileName = fname;
				csFileName += cext;
				CFileDialog fdlg(FALSE, NULL, csFileName);
				if(fdlg.DoModal() == IDOK)
				{
					m_JDMachMon.ReceiveFile( m_csMachDir + "\\" + csCurrSelFile, fdlg.GetPathName(), NULL, NULL);
				}
			}
			else
			{//为目录
				AfxMessageBox("不能下载文件夹");
			}
		}
	}
}


void CNcMonDemoDlg::OnButtonRenameFile()
{
	UpdateData();
	if(m_JDMachMon.IsConncect())
	{		
		int nCurrSel = m_ListBoxFile.GetCurSel();
		
		if(nCurrSel >=0 && nCurrSel < m_ListBoxFile.GetCount() )
		{
			CString csCurrSelFile;
			m_ListBoxFile.GetText(nCurrSel, csCurrSelFile);
			
			CRenameFileDlg RenameFileDlg;
			RenameFileDlg.csFileName = csCurrSelFile;
			if(RenameFileDlg.DoModal() == IDOK)
			{				
				char drive[_MAX_DRIVE];
				char dir[_MAX_DIR];
				char fname[_MAX_FNAME];
				char cext[_MAX_EXT];
				_splitpath(csCurrSelFile, drive,dir,fname,cext);
				
				m_JDMachMon.RenameMachFile( m_csMachDir + "\\" + csCurrSelFile, RenameFileDlg.csFileName);

				OnButtonRefreshFileList();
			}
		}
	}
}

void CNcMonDemoDlg::OnButtonGetWorkpieceMachTimeRecord()
{
	if(m_JDMachMon.IsConncect())
	{	
		int    aProgNo[1024];
		float  aMachTime[1024];
		int nWorkpieceCount = 0;
		m_JDMachMon.GetWorkpieceMachTimeRecord(1024, nWorkpieceCount, aProgNo, aMachTime);
		CString strResult, strCurrLine;
		for(int i = 0; i < nWorkpieceCount; i++)
		{
			strCurrLine.Format("程序号:%d  加工时间(分):%.2f\r\n", aProgNo[i], aMachTime[i]);
			strResult += strCurrLine;
		}
		if(strResult.GetLength() > 0)
			MessageBox(strResult, "工件加工时间履历表" ,MB_OK);
		else
			MessageBox("工件加工记录为空", "工件加工时间履历表" ,MB_OK);
	}
}

BOOL CNcMonDemoDlg::DestroyWindow() 
{
	OnButtonDisconnect();
	
	return CPropertyPage::DestroyWindow();
}

void CNcMonDemoDlg::OnButtonBrowseNcFile()
{
	CString file;
	CString ext;
	CString str;
	
	str = "GCode加工文件(*.nc)|*.nc||\n";
	CFileDialog dlgFile(TRUE, NULL, NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	
	
	if(dlgFile.DoModal() == IDOK)
	{
		CWnd * pWnd = GetDlgItem(IDC_EDIT_NCFILEPATH);
		if(pWnd != NULL)
			pWnd->SetWindowText(dlgFile.GetPathName());
	}
}

void CNcMonDemoDlg::OnButtonSendNcFile()
{
	if(m_JDMachMon.IsSendingFile())
	{
		AfxMessageBox("正在发送文件，请稍后再发送");
		return;
	}
	CWnd * pWnd = GetDlgItem(IDC_BUTTON_SENDNC);
	if(pWnd != NULL)
		pWnd->EnableWindow(FALSE);
	
	pWnd = GetDlgItem(IDC_EDIT_NCFILEPATH);
	CButton * pChkBtn = (CButton *)GetDlgItem(IDC_CHECK_NCADDTASK);
	CButton * pChkBtn1 = (CButton *)GetDlgItem(IDC_CHECK_NCASMAIN);
	if(pWnd != NULL && pChkBtn != NULL && pChkBtn1 != NULL)
	{
		CString csFileName;
		pWnd->GetWindowText(csFileName);
		
		int nStrLen = csFileName.GetLength();
		if(nStrLen > 400)
		{
			AfxMessageBox("路径超长");
			goto SendNcEndLine;
		}
		else if(nStrLen < 1)
		{
			AfxMessageBox("文件名为空");
			goto SendNcEndLine;
		}
		
		CFile cfile;
		if(cfile.Open(csFileName, CFile::modeRead))
		{
			m_ProgCtrl.SetRange(0, cfile.GetLength()/1024/1024);
			cfile.Close();
		}

		m_JDMachMon.SendNcFile(csFileName, pChkBtn->GetCheck(), pChkBtn1->GetCheck(), NULL, NULL);
	}
	
SendNcEndLine:
	pWnd = GetDlgItem(IDC_BUTTON_SENDNC);
	if(pWnd != NULL)
		pWnd->EnableWindow(TRUE);
}