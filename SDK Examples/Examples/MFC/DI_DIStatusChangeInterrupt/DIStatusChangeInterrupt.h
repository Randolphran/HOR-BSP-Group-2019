// DI Status Change.h : main header file for the DI STATUS CHANGE application
//

#if !defined(AFX_DISTATUSCHANGE_H__FC908D6E_9D2B_4767_9D62_8D485ABE0EF7__INCLUDED_)
#define AFX_DISTATUSCHANGE_H__FC908D6E_9D2B_4767_9D62_8D485ABE0EF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStatusChangeApp:
// See DIStatusChangeInterrupt.cpp for the implementation of this class
//

class CDIStatusChangeInterruptApp : public CWinApp
{
public:
	CDIStatusChangeInterruptApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DIStatusChangeInterrupt)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(DIStatusChangeInterrupt)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISTATUSCHANGE_H__FC908D6E_9D2B_4767_9D62_8D485ABE0EF7__INCLUDED_)
