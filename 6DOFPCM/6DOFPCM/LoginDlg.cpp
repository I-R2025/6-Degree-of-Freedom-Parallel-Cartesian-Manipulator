// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "6DOFPCM.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "6DOFPCMView.h"
#include "RegistrationDlg.h"

// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGIN_DLG, pParent)
	, m_usertype(_T(""))
	, m_username(_T(""))
	, m_password(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_usertype);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT7, m_password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoginDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CLoginDlg message handlers


void CLoginDlg::OnBnClickedButton1()
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


	char path[MAX_PATH];
	size_t path_len;

	if (0 != getenv_s(&path_len, path, MAX_PATH, _T("SDILOGIN_PATH")) || path_len == 0)
	{
		::AfxMessageBox("ERROR: Cannot find SDILOGIN Enviorment Variable");
		return;
	}


	UpdateData(TRUE);

	CStdioFile fileSrc;
	CString strline;
	CString strReadString;

	if (m_usertype == "Manager")
	{
		CString full_path = CString(path) + CString(_T("\\Manager.dat.txt"));

		if (fileSrc.Open(LPCTSTR(full_path), CFile::modeRead))
		{
			fileSrc.SeekToBegin();
			while ((fileSrc.ReadString(strline)))
			{
				strReadString += strline;
				if (m_username == strline)
				{
					pDoc->m_login_name = _T("TRUE");

					strReadString += strline;
					fileSrc.ReadString(strline);
					if (m_password == strline)
					{
						pDoc->m_login_passowrd = _T("TRUE");
					}
				}

			}
			fileSrc.Close();
		}
		else
		{
			AfxMessageBox(_T("ERROR: Unable to open Manager.dat.txt File"), (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
			pView->RA_DispMsg("ERROR: Unable to open Manager.dat.txt File"); return;
		}

		if (pDoc->m_login_name == _T("0"))
		{
			AfxMessageBox(_T("ERROR: The Name entered is incorrect"), (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK); BringWindowToTop();
			pView->RA_DispMsg(("ERROR: The Name entered is incorrect")); return;
		}
		else if (pDoc->m_login_passowrd == ("0"))
		{
			AfxMessageBox(_T("ERROR: The Password entered is incorrect"), (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
			pView->RA_DispMsg(_T("ERROR: The Password entered is incorrect")); return;
		}
		else
		{
			pDoc->m_usertype_received = m_usertype;
			pDoc->m_username_received = m_username;
			pDoc->m_password_received = m_password;

			pDoc->RA_LogEvents(_T("INFO: ") + m_usertype + _T("\t") + m_username + _T("\tLog In"));
			CString tempmsg = _T("INFO: ") + m_usertype; tempmsg += _T(" "); tempmsg += m_username; tempmsg += _T(" "); tempmsg += _T("Sign In");
			pView->RA_DispMsg(tempmsg);
			pView->m_usertype_received = m_usertype;
			pView->m_username_received = m_username;
			

			pDoc->m_login_first = 1;
			pDoc->m_login_name = _T("0");
			pDoc->m_login_passowrd = _T("0");

			pView->m_ListBox.ResetContent();
			pView->DisplayName();
			CDialog::OnOK();
		}

	}

	if (m_usertype == "Operator")
	{
		CString full_path = CString(path) + CString(_T("\\Operator.dat.txt"));
		if (fileSrc.Open(LPCTSTR(full_path), CFile::modeRead))
		{
			fileSrc.SeekToBegin();
			while ((fileSrc.ReadString(strline)))
			{
				strReadString += strline;
				if (m_username == strline)
				{
					pDoc->m_login_name = _T("TRUE");

					strReadString += strline;
					fileSrc.ReadString(strline);
					if (m_password == strline)
					{
						pDoc->m_login_passowrd = _T("TRUE");
					}
				}

			}
			fileSrc.Close();

		}
		else
		{
			AfxMessageBox("ERROR: Unable to open Operator.dat.txt File", (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
			//	pView->RA_DispMsg("ERROR: Unable to open Operator.dat.txt File"); return;
		}

		if (pDoc->m_login_name == _T("0"))
		{
			AfxMessageBox("ERROR: The Name you entered is incorrect", (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
			//	pView->RA_DispMsg(_T("ERROR: The Name you entered is incorrect")); return;
		}
		else if (pDoc->m_login_passowrd == _T("0"))
		{
			AfxMessageBox("ERROR: The Password you entered is incorrect", (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
			//	pView->RA_DispMsg(_T("ERROR: The Password you entered is incorrect")); return;
		}
		else
		{
			pDoc->m_usertype_received = m_usertype;
			pDoc->m_username_received = m_username;
			pDoc->m_password_received = m_password;

			pDoc->RA_LogEvents(_T("INFO: ") + m_usertype + _T("\t") + m_username + _T("\tLog In"));
			CString tempmsg = _T("INFO: ") + m_usertype; tempmsg += _T(" "); tempmsg += m_username; tempmsg += _T(" "); tempmsg += _T("Sign In");
			pView->RA_DispMsg(tempmsg);
			pView->m_usertype_received = m_usertype;
			pView->m_username_received = m_username;
			

			pDoc->m_login_first = 1;
			pDoc->m_login_name = _T("0");
			pDoc->m_login_passowrd = _T("0");

			pView->m_ListBox.ResetContent();
			pView->Receive_ListBox();
			pView->DisplayName();

			CDialog::OnOK();
		}

	}
	
}


void CLoginDlg::OnBnClickedButton2() // Sign Out Button
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


	pDoc->RA_LogEvents(_T("INFO:  ") + m_usertype + _T("\t") + m_username + _T("\t") + _T("Sign Out"));
	CString tempmsg = _T("INFO:  ") + m_usertype; tempmsg += _T(" "); tempmsg += m_username; tempmsg += _T(" "); tempmsg += _T("Sign Out");
	pView->RA_DispMsg(tempmsg);

	pDoc->m_usertype_received = _T(" ");
	pDoc->m_username_received = _T(" ");

	pView->m_usertype_received = _T(" ");
	pView->m_username_received = _T(" ");
	pView->GetDocument()->UpdateAllViews(NULL);

	pDoc->m_login_first = 0;
}


void CLoginDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CRegistrationDlg dlg;
	dlg.DoModal();
}
