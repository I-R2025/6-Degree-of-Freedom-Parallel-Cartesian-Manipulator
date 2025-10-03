// RegistrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "6DOFPCM.h"
#include "RegistrationDlg.h"
#include "afxdialogex.h"
#include "6DOFPCMView.h"

// CRegistrationDlg dialog

IMPLEMENT_DYNAMIC(CRegistrationDlg, CDialog)

CRegistrationDlg::CRegistrationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_REGISTRATION_DLG, pParent)
	, m_register_username(_T(""))
	, m_Authorized_Usr_Psswrd(_T(""))
	, m_register_password(_T(""))
	, m_confirm_password(_T(""))
	, m_user_type(_T(""))
{

}

CRegistrationDlg::~CRegistrationDlg()
{
}

void CRegistrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT8, m_register_username);
	DDX_Text(pDX, IDC_EDIT1, m_Authorized_Usr_Psswrd);
	DDX_Text(pDX, IDC_EDIT9, m_register_password);
	DDX_Text(pDX, IDC_EDIT10, m_confirm_password);
	DDX_CBString(pDX, IDC_COMBO2, m_user_type);
}


BEGIN_MESSAGE_MAP(CRegistrationDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegistrationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegistrationDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CRegistrationDlg message handlers


void CRegistrationDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}

	C6DOFPCMView *pView;
	pView = pView->GetView();
	if (!pView)
	{
		AfxMessageBox("ERROR: Unable to get View pointer");
		return;
	}


	UpdateData(TRUE);

	if (m_Authorized_Usr_Psswrd == "RA-Manager")
	{
		if (m_register_password == m_confirm_password)
		{
			WriteData();

			full_message = m_register_username + _T("\t") + _T("get registered");
			pDoc->RA_LogEvents(m_register_username + _T("\t") + _T("get registered"));
			CString tempmsg = m_register_username; tempmsg += _T(" "); tempmsg += _T("get registerd");
			pView->MessageBox(tempmsg);

			CDialog::OnOK();
		}
		else
		{
			AfxMessageBox("ERROR: Password dont match", (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
			pView->RA_DispMsg("ERROR: Password dont match"); return;
		}
	}
	else
		AfxMessageBox("ERROR: Not Authrized to use this program", (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
	pView->RA_DispMsg("ERROR: Not Authrized to use this program"); return;
}

void CRegistrationDlg::WriteData()
{
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}

	C6DOFPCMView *pView;
	pView = pView->GetView();
	if (!pView)
	{
		AfxMessageBox("ERROR: Unable to get View pointer");
		return;
	}


	char path[MAX_PATH];
	size_t path_len;

	if (0 != getenv_s(&path_len, path, MAX_PATH, _T("SDILOGIN_PATH")) || path_len == 0)
	{
		::AfxMessageBox("EEROR: Cannot find SDILOGIN Enviorment Variable");
		return;
	}

	CStdioFile fileSrc;
	if (m_user_type == "Manager")
	{

		CString full_path = CString(path) + CString(_T("\\Manager.dat.txt"));

		//if (!fileSrc.Open((LPCTSTR)_T("C:/Users/Roboram/Documents/Visual Studio 2015/Projects/RA01/RA01-Project-16102018/RA01-Project-16102018/SDILogin/Manager.dat.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
		if (!fileSrc.Open(LPCTSTR(full_path), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
		{
			//ofstream::app;
			AfxMessageBox("ERROR: Unable to open Manager.dat.txt File", (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
			pView->RA_DispMsg("ERROR: Unable to open Manager.dat.txt File"); return;
		}
		else
		{
			UpdateData(TRUE);
			fileSrc.SeekToEnd();
			fileSrc.WriteString(_T("\n"));
			fileSrc.WriteString(m_register_username);
			fileSrc.WriteString(_T("\n"));
			fileSrc.WriteString(m_confirm_password);
			fileSrc.WriteString(_T("\n"));
			fileSrc.Flush();
			fileSrc.Close();
		}


	}

	if (m_user_type == "Operator")
	{
		CString full_path = CString(path) + CString(_T("\\Operator.dat.txt"));
		//if (!fileSrc.Open((LPCTSTR)_T("C:/Users/Roboram/Documents/Visual Studio 2015/Projects/RA01/RA01-Project-16102018/RA01-Project-16102018/SDILogin/Manager.dat.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
		if (!fileSrc.Open(LPCTSTR(full_path), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
		{
			//ofstream::app;
			AfxMessageBox("ERROR: Unable to open Operator.dat.txt File", (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
			pView->RA_DispMsg("ERROR: Unable to open Operator.dat.txt File"); return;
		}
		else
		{
			UpdateData(TRUE);
			fileSrc.SeekToEnd();
			fileSrc.WriteString(_T("\n"));
			fileSrc.WriteString(m_register_username);
			fileSrc.WriteString(_T("\n"));
			fileSrc.WriteString(m_confirm_password);
			fileSrc.WriteString(_T("\n"));
			fileSrc.Flush();
			fileSrc.Close();
		}

	}

}


void CRegistrationDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	CDialog::OnCancel();

}
