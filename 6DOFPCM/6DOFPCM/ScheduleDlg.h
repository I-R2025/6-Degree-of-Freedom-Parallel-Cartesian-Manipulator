#pragma once
#include "6DOFPCMDoc.h"
#include "GdipButton.h"
#include "afxbutton.h"

// CScheduleDlg dialog

class CScheduleDlg : public CDialog
{
	DECLARE_DYNAMIC(CScheduleDlg)

public:
	CScheduleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScheduleDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Schedule_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton4();
	CString Assembly;
	
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton64();
	afx_msg void OnBnClickedButton75();
	afx_msg void OnBnClickedButton63();
	afx_msg void OnBnClickedButton76();
	afx_msg void OnBnClickedButton79();
	afx_msg void OnBnClickedButton91();
	afx_msg void OnBnClickedButton90();
	afx_msg void OnBnClickedButton139();
	afx_msg void OnBnClickedButton138();
	afx_msg void OnBnClickedButton148();
	afx_msg void OnBnClickedButton147();
	afx_msg void OnBnClickedButton146();
	afx_msg void OnBnClickedButton156();
	afx_msg void OnBnClickedButton155();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton38();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton48();
	afx_msg void OnBnClickedButton43();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	CMFCButton m_20_K;
	CMFCButton m_17_L;
	CMFCButton m_21_L;
	CMFCButton m_18_M;
	CMFCButton m_20_M;
	CMFCButton m_12_R;
	CMFCButton m_14_R;
	CMFCButton m_11_S;
	CMFCButton m_13_S;
	CMFCButton m_15_S;
	CMFCButton m_12_T;
	CMFCButton m_14_T;
	CMFCButton m_C_T;
	CMFCButton m_21_G;
	CMFCButton m_19_G;
	CMFCButton m_23_G;
	CMFCButton m_20_H;
	CMFCButton m_22_H;
	CMFCButton m_22_F;
	CMFCButton m_20_F;
	virtual BOOL OnInitDialog();
	CMFCButton m_18_K;
	afx_msg void OnBnClickedButton158();

	
	

	virtual void PostNcDestroy();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton34();
};
