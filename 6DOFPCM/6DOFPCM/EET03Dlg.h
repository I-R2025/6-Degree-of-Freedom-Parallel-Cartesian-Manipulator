#pragma once
#include "6DOFPCMDoc.h"
#include "GdipButton.h"

// CEET03Dlg dialog

class CEET03Dlg : public CDialog
{
	DECLARE_DYNAMIC(CEET03Dlg)

public:
	CEET03Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEET03Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EET03_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CString m_SelectedSpeed_PM;
//	CGdipButton m_move;
//	CGdipButton m_step1;
//	CGdipButton m_step2;
//	CGdipButton m_step3;
//	CGdipButton m_step3;
//	CGdipButton m_step4;
//	CGdipButton m_step5;
//	CGdipButton m_step6;
//	CGdipButton m_step11;
//	CGdipButton m_step12;
//	CGdipButton m_step14;
//	CGdipButton m_step15;
//	CGdipButton m_updateFL;
//	CGdipButton m_resetFL;
//	CGdipButton m_st_ss;
//	CGdipButton m_st_bs;
//	CGdipButton m_st_sn;
//	CGdipButton m_st_bn;
//	CGdipButton m_st_se;
//	CGdipButton m_st_sw;
//	CGdipButton m_st_be;
//	CGdipButton m_st_bw;
//	CGdipButton m_st_bu;
//	CGdipButton m_st_su;
//	CGdipButton m_st_sd;
//	CGdipButton m_st_bd;
//	CGdipButton m_ft_movePM;
//	CGdipButton m_ft_moveSM;
//	CGdipButton m_ft_move_tool;
	CString m_cstrFLUpdPw;
	long m_PM_Value;
	CString m_Select_PM_Mode;
//	CString m_Select_PM_Direction;
	CString m_SelectedSpeed_PM;
	CString m_Select_PM_direction;
	float m_Number_of_Rev;
	CString m_Select_Direction_ETC3;
	CString m_select_tool;
	long m_Enter_Value_CTC;
	CString m_Select_Direction_CTC;
//	CGdipButton m_next;
	afx_msg void OnBnClickedMovePm();
	afx_msg void Move_EET02_to_Selected_PM_Location();

	BOOL Select_PM_Speed();

	DWORD ProfileVelocityNS;
	DWORD ProfileAccelerationNS;
	DWORD ProfileDeccelerationNS;

	DWORD ProfileVelocityEW;
	DWORD ProfileAccelerationEW;
	DWORD ProfileDeccelerationEW;

	unsigned int NS_FINE_INC;
	unsigned int EW_FINE_INC;
	unsigned int NS_COARSE_INC;
	unsigned int EW_COARSE_INC;
	unsigned int LA3_COARSE_INC;
	unsigned int LA3_FINE_INC;
	afx_msg void OnBnClickedMovela2tosafelimit();
	afx_msg void OnBnClickedMovela2tosafelimit2();
	afx_msg void OnBnClickedMovela2tosafelimit5();
	afx_msg void OnBnClickedMovela2tosafelimit3();

	LONG ptargetpositionETC3;
	LONG ptargetpositionELAC3;

	
	afx_msg void OnBnClickedMovela2tosafelimit6();
	
	afx_msg void OnBnClickedMovela2tosafelimit8();
	afx_msg void OnBnClickedMovela2tosafelimit9();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton149();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton151();
	afx_msg void OnBnClickedButton150();
	afx_msg void OnBnClickedButton157();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedMovePmft();
	afx_msg void OnBnClickedMoveElac2ft2();
	afx_msg void OnBnClickedMoveElac2ft();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_PM_Selected_Location;
	afx_msg void OnBnClickedUpdateLocationFile();
	afx_msg void OnBnClickedResetLocationFile();
	void PM_WriteLocations2File();
	void SelectedPosition();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedNext();
	CGdipButton m_move;
	CGdipButton m_updateFL;
	CGdipButton m_resetFL;
	CGdipButton m_ft_movePM;
	CGdipButton m_ft_moveSM;
	CGdipButton m_ft_move_tool;
	CGdipButton m_step1;
	CGdipButton m_step2;
	CGdipButton m_step3;
	CGdipButton m_step4;
	CGdipButton m_step5;
};
