#pragma once
#include "6DOFPCMDoc.h"
#include "GdipButton.h"


// CEET02Dlg dialog

class CEET02Dlg : public CDialog
{
	DECLARE_DYNAMIC(CEET02Dlg)

public:
	CEET02Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEET02Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EET02_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString M_SelectedSpeed_PM;
//	CGdipButton m_move;
//	CGdipButton m_step1;
//	CGdipButton m_step2;
//	CGdipButton m_step3;
//	CGdipButton m_step4;
//	CGdipButton m_updateFL;
//	CGdipButton m_resetFL;
//	CGdipButton m_st_se;
//	CGdipButton m_st_be;
//	CGdipButton m_st_sw;
//	CGdipButton m_st_bw;
//	CGdipButton m_st_ss;
//	CGdipButton m_st_bs;
//	CGdipButton m_st_sn;
//	CGdipButton m_st_bn;
//	CGdipButton m_st_su;
//	CGdipButton m_st_sd;
//	CGdipButton m_st_bu;
//	CGdipButton m_st_bd;
//	CGdipButton m_ft_movePM;
//	CGdipButton m_ft_moveelac2;
	CString m_Select_LA02_Speed;
	CString m_cstrFLUpdPw;
	CString m_Select_PM_Mode;
	CString m_Select_PM_Direction;
	CString m_Direction;
	afx_msg void OnBnClickedMovePm();
	afx_msg void Move_EET02_to_Selected_PM_Location();
	BOOL Select_PM_Speed();

	DWORD ProfileVelocityNS;
	DWORD ProfileAccelerationNS;
	DWORD ProfileDeccelerationNS;

	DWORD ProfileVelocityEW;
	DWORD ProfileAccelerationEW;
	DWORD ProfileDeccelerationEW;
	afx_msg void OnBnClickedMovela2tosafelimit();
	afx_msg void OnBnClickedRotatenut();

	BOOL LA02_Speed();
	DWORD ProfileVelocityLA02;
	DWORD ProfileAccelerationLA02;
	DWORD ProfileDeccelerationLA02;
	LONG ptargetpositionETC2;
	afx_msg void OnBnClickedRotateEtc2();
	afx_msg void OnBnClickedHomeElac2();
	afx_msg void OnBnClickedUpdateLocationFile();
	afx_msg void OnBnClickedResetLocationFile();
	void PM_WriteLocations2File();
	afx_msg void OnBnClickedButton6();

	unsigned int NS_FINE_INC;
	unsigned int EW_FINE_INC;
	unsigned int NS_COARSE_INC;
	unsigned int EW_COARSE_INC;
	unsigned int LA2_COARSE_INC;
	unsigned int LA2_FINE_INC;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton149();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton151();
	afx_msg void OnBnClickedButton150();
	afx_msg void OnBnClickedButton157();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedMovePmft();
	long m_PM_Value;
	afx_msg void OnBnClickedMoveElac2ft();
	int m_Value;
	CString m_select_tool;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_PM_Selected_Location;
	afx_msg void OnBnClickedNext();
//	CGdipButton m_next;
	void SelectedPosition();
	virtual void PostNcDestroy();

	LONG NStargetPos = 0;
	LONG EWtargetPos = 0;
	CGdipButton m_move;
	CGdipButton m_updateFL;
	CGdipButton m_resetFL;
	CGdipButton m_ft_movePM;
	CGdipButton m_ft_moveelac2;
	CGdipButton m_step1;
	CGdipButton m_step2;
	CGdipButton m_step3;
	CGdipButton m_next;
};
