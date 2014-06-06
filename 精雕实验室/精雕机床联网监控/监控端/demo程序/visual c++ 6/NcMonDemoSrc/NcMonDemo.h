// NcMonDemo.h : main header file for the NCMONDEMO application
//

#if !defined(AFX_NCMONDEMO_H__52CD1CAA_23A8_4299_B791_45767D233B87__INCLUDED_)
#define AFX_NCMONDEMO_H__52CD1CAA_23A8_4299_B791_45767D233B87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNcMonDemoApp:
// See NcMonDemo.cpp for the implementation of this class
//

class CNcMonDemoApp : public CWinApp
{
public:
	CNcMonDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNcMonDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNcMonDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NCMONDEMO_H__52CD1CAA_23A8_4299_B791_45767D233B87__INCLUDED_)
