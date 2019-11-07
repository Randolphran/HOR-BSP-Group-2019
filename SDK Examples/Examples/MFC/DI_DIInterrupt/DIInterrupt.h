// DIInterrupt.h : main header file for the DI INTERRUPT application
//

#if !defined(AFX_DIINTERRUPT_H__8F0D4D69_579C_44B0_AA2A_D2BE5DCC6EFA__INCLUDED_)
#define AFX_DIINTERRUPT_H__8F0D4D69_579C_44B0_AA2A_D2BE5DCC6EFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDIInterruptApp:
// See DI Interrupt.cpp for the implementation of this class
//

class CDIInterruptApp : public CWinApp
{
public:
	CDIInterruptApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIInterruptApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDIInterruptApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIINTERRUPT_H__8F0D4D69_579C_44B0_AA2A_D2BE5DCC6EFA__INCLUDED_)
