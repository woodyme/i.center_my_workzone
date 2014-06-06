// NcMonDemo.cpp : Defines the class behaviors for the application.
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
// CNcMonDemoApp

BEGIN_MESSAGE_MAP(CNcMonDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CNcMonDemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNcMonDemoApp construction

CNcMonDemoApp::CNcMonDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNcMonDemoApp object

CNcMonDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNcMonDemoApp initialization

BOOL CNcMonDemoApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CPropertySheet dlg;
	CNcMonDemoDlg AllPage[MAX_MACH_MON_COUNT];
	CString strItem;
	for(int i = 0; i < MAX_MACH_MON_COUNT; i++)
	{
		dlg.AddPage(&AllPage[i]);

		/*CTabCtrl* pTab = dlg.GetTabControl();
		ASSERT (pTab);		
		TC_ITEM ti;
		ti.mask = TCIF_TEXT;
		strcpy(ti.pszText , strItem);
		VERIFY (pTab->SetItem (i, &ti));*/
	}



	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
