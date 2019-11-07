// Instant Do.h : main header file for the INSTANT DO application
//

#if !defined(AFX_INSTANTDO_H__79720EAF_3D82_42AE_AB47_DBCC15583424__INCLUDED_)
#define AFX_INSTANTDO_H__79720EAF_3D82_42AE_AB47_DBCC15583424__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStaticDOApp:
// See Static Do.cpp for the implementation of this class
//

class CStaticDOApp : public CWinApp
{
public:
	CStaticDOApp();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticDOApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	
	// Implementation
	
	//{{AFX_MSG(CStaticDOApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTANTDO_H__79720EAF_3D82_42AE_AB47_DBCC15583424__INCLUDED_)
