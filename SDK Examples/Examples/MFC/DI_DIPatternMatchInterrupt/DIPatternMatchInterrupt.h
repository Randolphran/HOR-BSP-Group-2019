// DI Pattern Match.h : main header file for the DI PATTERN MATCH application
//

#if !defined(AFX_DIPATTERNMATCH_H__BAC5F5B6_67B0_4F1E_930C_8290842487E5__INCLUDED_)
#define AFX_DIPATTERNMATCH_H__BAC5F5B6_67B0_4F1E_930C_8290842487E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDIPatternMatchInterruptApp:
// See DIPatternMatchInterrupt.cpp for the implementation of this class
//

class CDIPatternMatchInterruptApp : public CWinApp
{
public:
	CDIPatternMatchInterruptApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIPatternMatchInterruptApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDIPatternMatchInterruptApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIPATTERNMATCH_H__BAC5F5B6_67B0_4F1E_930C_8290842487E5__INCLUDED_)
