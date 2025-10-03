#pragma once
#include "6DOFPCMDoc.h"
#include "GdipButton.h"
// CLA01Dlg dialog

class CLA01Dlg : public CDialog
{
	DECLARE_DYNAMIC(CLA01Dlg)

public:
	CLA01Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLA01Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LA01_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	
	afx_msg void OnBnClickedMovePm();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();

	afx_msg void PM_Move_to_Selected_Location();
	BOOL PM_Speed();
//	CString m_SelectedSpeed;
	DWORD ProfileVelocityNS = 0;
	DWORD ProfileAccelerationNS = 0;
	DWORD ProfileDeccelerationNS = 0;;
	DWORD ProfileVelocityEW = 0;
	DWORD ProfileAccelerationEW = 0;
	DWORD ProfileDeccelerationEW = 0;
	
	
	bool Get_Pointers();

	BOOL LA01_Speed();
	DWORD ProfileVelocityLA01;
	DWORD ProfileAccelerationLA01;
	DWORD ProfileDeccelerationLA01;
	afx_msg void OnBnClickedstep1();

	CString m_SelectedSpeed_LA01;
	afx_msg void OnBnClickedstep3();
	afx_msg void OnBnClickedstep4();
	afx_msg void OnBnClickedstep2();
	afx_msg void OnBnClickedUpdateLocations();
	CString m_cstrFLUpdPw;
	void PM_WriteLocations2File();
	afx_msg void OnBnClickedResetLocationsFile();
	afx_msg void OnBnClickedButton6();

	unsigned int NS_FINE_INC;
	unsigned int EW_FINE_INC;
	unsigned int NS_COARSE_INC;
	unsigned int EW_COARSE_INC;
	unsigned int LA1_COARSE_INC;
	unsigned int LA1_FINE_INC;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton149();
	afx_msg void OnBnClickedButton11();
	CString m_SelectedMode;
	CString m_SelectedDirection;
	long m_Value;
	long m_ValueLA1;
	
	CString m_SelectDirectionLA1;
	afx_msg void OnBnClickedButton151();
	afx_msg void OnBnClickedButton150();
	afx_msg void OnBnClickedButton157();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedMoveElac2();
	afx_msg void OnBnClickedMoveElac1();
//	CGdipButton m_movePM;
//	CGdipButton m_step1;
//	CGdipButton m_step2;
//	CGdipButton m_step3;
//	CGdipButton m_step4;
//	CGdipButton m_updateFL;
//	CGdipButton m_resetFL;
//	CGdipButton m_st_ss;
//	CGdipButton m_st_bs;
//	CGdipButton m_st_sn;
//	CGdipButton m_st_bn;
//	CGdipButton m_st_sw;
//	CGdipButton m_st_bw;
//	CGdipButton m_st_se;
//	CGdipButton m_st_be;
//	CGdipButton m_st_su;
//	CGdipButton m_st_bu;
//	CGdipButton m_st_sd;
//	CGdipButton m_st_bd;
//	CGdipButton m_ft_movePM;
//	CGdipButton m_ft_movela1;
//	CGdipButton m_Next;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_PM_Selected_Location;
	afx_msg void OnBnClickedNext();
	CString m_SelectedSpeed;
	
	virtual void PostNcDestroy();
	afx_msg void OnPaint();
	short m_conectCurrent;
	CGdipButton m_movePM;
	CGdipButton m_updateFL;
	CGdipButton m_resetFL;
	CGdipButton m_ft_movePM;
	CGdipButton m_ft_movela1;
	CGdipButton m_step1;
	CGdipButton m_step2;
	CGdipButton m_step3;
	CGdipButton m_Next;
};
