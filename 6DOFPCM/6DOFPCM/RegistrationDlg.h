#pragma once
#include "6DOFPCMDoc.h"
#include "GdipButton.h"

// CRegistrationDlg dialog

class CRegistrationDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegistrationDlg)

public:
	CRegistrationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRegistrationDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTRATION_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_register_username;
	CString m_Authorized_Usr_Psswrd;
	CString m_register_password;
	CString m_confirm_password;
	CString m_user_type;
	CString full_message;
	afx_msg void OnBnClickedButton1();
	void WriteData();
	afx_msg void OnBnClickedButton2();
};
