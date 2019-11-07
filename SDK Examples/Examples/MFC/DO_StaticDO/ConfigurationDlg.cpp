// ConfigureForm.cpp : 
//
#include "stdafx.h"
#include "StaticDO.h"
#include "ConfigurationDlg.h"
#include <tchar.h>

#ifndef UNICODE
TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out)
{
   WideCharToMultiByte (CP_OEMCP,NULL,in,-1,out,MAX_DEVICE_DESC_LEN,NULL,FALSE);
   return out;
}
#else
TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out)
{
   wcscpy_s(out, wcslen(in) + 1, in);
	return out;
}
#endif

#ifndef UNICODE
WCHAR const * TCHAR_TO_WCHAR(TCHAR const * in,  WCHAR* out)
{
   MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)in, -1, out, MAX_DEVICE_DESC_LEN);
   return out;
}
#else
WCHAR const * TCHAR_TO_WCHAR(TCHAR const * in,  WCHAR* out)
{
	wcscpy_s(out, wcslen(in) + 1, in);
	return out;
}
#endif


// CConfigureForm dialog

IMPLEMENT_DYNAMIC(CConfigurationDlg, CDialog)

CConfigurationDlg::CConfigurationDlg(CWnd* pParent /*=NULL*/)
: CDialog(CConfigurationDlg::IDD, pParent)
{}

CConfigurationDlg::~CConfigurationDlg()
{}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Device, m_comboBox_Device);
}

BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
//{{AFX_MSG_MAP(CConfigureForm)
ON_BN_CLICKED(IDOK, OnOk)
ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
ON_WM_CLOSE()
ON_EN_CHANGE(IDC_EDIT_PROFILE, OnShowProfilePath)
ON_BN_CLICKED(IDBROWSE, OnBnClickedBrowse)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

DevConfParam CConfigurationDlg::GetParameter()
{
   DevConfParam param;
   param.deviceNumber = (int)m_comboBox_Device.GetItemData(m_comboBox_Device.GetCurSel());
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);
   return param;
}

BOOL CConfigurationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// create available device list.
   InstantDoCtrl * instantDoCtrl = InstantDoCtrl::Create();
   Array<DeviceTreeNode>* sptedDevices = instantDoCtrl->getSupportedDevices();

   if (sptedDevices->getCount() == 0)
   {
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
      AfxMessageBox(_T("No device to support the currently demonstrated function!"));
      return FALSE;
   }else{
      int deviceCount = 0;
      for (int i = 0; i < sptedDevices->getCount(); ++i)
      {
         DeviceTreeNode const & node = sptedDevices->getItem(i);
         TRACE("%d, %s\n", node.DeviceNumber, node.Description);

         DeviceInformation devInfo(node.DeviceNumber);
         ErrorCode errorCode = instantDoCtrl->setSelectedDevice(devInfo);

         GetDlgItem(IDOK)->EnableWindow(TRUE);
         if (errorCode != 0){
            CString str;
            str.Format(_T("Error: the error code is 0x%x, The %s is busy or not exit in computer now.\n\
  Select other device please!"),errorCode,node.Description);
            AfxMessageBox(str);
            GetDlgItem(IDOK)->EnableWindow(FALSE);
            return FALSE;}
         TCHAR des[MAX_DEVICE_DESC_LEN];
         m_comboBox_Device.AddString(WCHAR_TO_TCHAR(node.Description,des));
         m_comboBox_Device.SetItemData(deviceCount++,node.DeviceNumber);
      }
      sptedDevices->Dispose();
   }
   instantDoCtrl->Dispose();
   m_comboBox_Device.SetCurSel(0);
	return TRUE;
}

// CConfigureForm 

void CConfigurationDlg::OnOk()
{
   this->GetParent()->ShowWindow(SW_SHOW);
   this->GetParent()->EnableWindow(TRUE);
   this->ShowWindow(SW_HIDE);

   ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,0,0);
   CDialog::OnOK();
}

//This function is used to handle the errorCode information
void CConfigurationDlg::CheckError(ErrorCode errorCode)
{
   if (errorCode !=  Success)
   {
      CString str;
      str.Format(_T("Some errors happened, the error code is:0x%x"), errorCode);
      AfxMessageBox(str);
   }
}

void CConfigurationDlg::OnBnClickedCancel()
{
   // TODO: Add your control notification handler code here
   CString windowText;
   this->GetParent()->GetWindowText(windowText);
   if (!windowText.Compare(_T("StaticDO")))
   {
      ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,1,0);
      this->CloseWindow();
   } 
   OnCancel();
}

void CConfigurationDlg::OnClose()
{
   // TODO: Add your message handler code here and/or call default
   if ( m_comboBox_Device.GetCount() <= 0)
   {
      PostQuitMessage(0);
   }
   CDialog::OnClose();
}
void CConfigurationDlg::OnShowProfilePath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CConfigurationDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("xml"), _T(""), OFN_OVERWRITEPROMPT, _T("Licence File(*.xml)|*.xml|"));
	dlg.m_ofn.lpstrInitialDir = _T("../../profile/");  
	if(dlg.DoModal() == IDOK)
	{
		m_profilePath = dlg.GetPathName();
		GetDlgItem(IDC_EDIT_PROFILE)->SetWindowText(m_profilePath);
	} 
}
