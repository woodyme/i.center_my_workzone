// NcMonDemoDlg.h : header file
//

#if !defined(AFX_NCMONDEMODLG_H__B598A27C_06E9_426E_8809_011869E9C4C2__INCLUDED_)
#define AFX_NCMONDEMODLG_H__B598A27C_06E9_426E_8809_011869E9C4C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNcMonDemoDlg dialog
#include "JDMachMon.h"

#define MAX_MACH_MON_COUNT 8

class CRenameFileDlg : public CDialog
{
public:
	CRenameFileDlg(CWnd* pParent = NULL): CDialog(CRenameFileDlg::IDD, pParent) {}
	CString csFileName;
	enum { IDD = IDD_DIALOG_RENAME };
	void DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_EDIT1, csFileName);
	}
};

class CNcMonDemoDlg : public CPropertyPage
{
// Construction
public:
	CNcMonDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNcMonDemoDlg)
	enum { IDD = IDD_NCMONDEMO_PAGE_DIALOG };
	CString	        m_csIPAddress;
	CProgressCtrl	m_ProgCtrl;
	CString	        m_csMachDir;
	CListBox        m_ListBoxFile;
	//}}AFX_DATA
	UINT	   m_nTimerIDEvent;
	CJDMachMon m_JDMachMon;
	CString    m_csFileName;
	BOOL       m_bIsSendingFile;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNcMonDemoDlg)
	protected:
	virtual BOOL DestroyWindow();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void ErrHandle();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNcMonDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonDisconnect();
	afx_msg void OnButtonBrowseFile();
	afx_msg void OnButtonSendFile();
	afx_msg void OnButtonRefreshFileList();
	afx_msg void OnButtonDelFile();
	afx_msg void OnButtonDownloadFile();
	afx_msg void OnButtonRenameFile();
	afx_msg void OnButtonGetWorkpieceMachTimeRecord();
	afx_msg void OnButtonBrowseNcFile();
	afx_msg void OnButtonSendNcFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NCMONDEMODLG_H__B598A27C_06E9_426E_8809_011869E9C4C2__INCLUDED_)
