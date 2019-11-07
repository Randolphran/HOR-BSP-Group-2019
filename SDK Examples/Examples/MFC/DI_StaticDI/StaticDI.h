// DI_Instant.h : main header file for the INSTANT DI application
//

#if !defined(AFX_INSTANTDI_H__73467A83_B314_4EDE_9BCA_80F003100ADB__INCLUDED_)
#define AFX_INSTANTDI_H__73467A83_B314_4EDE_9BCA_80F003100ADB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStaticDIApp:
// See StaticDI.cpp for the implementation of this class
//

class CStaticDIApp : public CWinApp
{
public:
	CStaticDIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStaticDIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTANTDI_H__73467A83_B314_4EDE_9BCA_80F003100ADB__INCLUDED_)
