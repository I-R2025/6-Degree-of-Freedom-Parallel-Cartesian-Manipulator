
// 6DOFPCMView.h : interface of the C6DOFPCMView class
//

#pragma once
#include "gdipbutton.h"
#include "CGdiPlusBitmap.h"
#include "MemDC.h"
#include "afxwin.h"
#include "afxtempl.h"
#include "afxbutton.h"
#include "LA01Dlg.h"
#include "EET02Dlg.h"
#include "EET03Dlg.h"
#include "ScheduleDlg.h"
#include "afxcmn.h"
#include "LoginDlg.h"

class C6DOFPCMView : public CFormView
{
protected: // create from serialization only
	C6DOFPCMView();
	DECLARE_DYNCREATE(C6DOFPCMView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_6DOFPCM_FORM };
#endif

// Attributes
public:
	C6DOFPCMDoc* GetDocument() const;

// Operations
public:
	static C6DOFPCMView* GetView();
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~C6DOFPCMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CLoginDlg* m_signindlg;
	CScheduleDlg m_scheduledlg;
	CLA01Dlg	m_la01dlg;
	CEET02Dlg	m_eet02dlg;
	CEET03Dlg	m_eet03dlg;
	void ShowWindowNumber(int number);
	CRect m_rSettingsRect;
	CTabCtrl m_cTab;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	

	afx_msg void OnBnClickedConnect();

	CDC* dc ;
	
	void RA_DispMsg(CString msg);                         //*****************************************Message Area************************************************
	BOOL Initialize_LEDs_Status();						  //*****************************************Initialize LEDs Status**************************************
														  //*****************************************Connection**************************************************

	BOOL RA01_Connectall();
	BOOL RA01_Disconnectall();
	BOOL Connect_PM();
	BOOL Connect_LA();
	BOOL Connect_EET();

	BOOL Hold_Brakes();
	BOOL DisConnect_EET();
	BOOL DisConnect_LA();
	BOOL DisConnect_PM();

	BOOL Check_FaultState_Controllers();

	BOOL Inputs_Configuration();
	BOOL Release_Brakes();

	BOOL PM_LimitSwitches_Status();
	BOOL PM_HomeSwitches_Status();

	BOOL LA_LimitSwitches_Status();
	BOOL Brakes_Status();

	BOOL Display_Motion_Status();                        //******************************************Display Motion Status****************************************
			
	

	BOOL Update_PM_Position();

	BOOL Update_LA1_Position();
	BOOL Update_LA2_Position();
	BOOL Update_LA3_Position();
	
	BOOL Update_ETC2_Position();
	BOOL Update_ETC3_Position();
	BOOL Update_CTC_Position();
	BOOL Update_All_Positions();
														 
														 //Variables


	HANDLE cfont;
	CString Title;
	HICON m_hIcon;
	HBITMAP m_hBitmap;
	
	//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	

	CBrush BrGreen = RGB(0, 213, 53);
	CBrush BrYellow = RGB(250, 200, 0);
	CBrush BrRed = RGB(255, 4, 4);
	CBrush BrLRed = RGB(255, 204, 204);
	CBrush BrBlue = RGB(0, 0, 155);
	CBrush BrLBlue = RGB(198, 198, 255);

	CRgn LED_NS;
	CRgn LED_EW;
	CRgn LED_ELAC1;
	CRgn LED_ELAC2;
	CRgn LED_ELAC3;
	CRgn LED_ETC2;
	CRgn LED_CTC;
	CRgn LED_ETC3;

	CRgn LED_CMTR;
	CRgn LED_CNSA;
	CRgn LED_CEWA;
	CRgn LED_CLA1;
	CRgn LED_CLA2;
	CRgn LED_CLA3;
	CRgn LED_CE2T;
	CRgn LED_CL3C;
	CRgn LED_CE3T;

	CRgn LED_BNL;
	CRgn LED_BEL;

	CRgn LED_XURL1;
	CRgn LED_XURL2;
	CRgn LED_XURL3;
	CRgn LED_XPGL1;
	CRgn LED_XPGL2;
	CRgn LED_XPGL3;

	CRgn LED_XN;
	CRgn LED_XS;
	CRgn LED_XE;
	CRgn LED_XW;
	CRgn LED_NHP;
	CRgn LED_EHP;

	

	
	afx_msg void OnBnClickedDisconnect2();
	CString m_cstrMsgArea;
	afx_msg void OnBnClickedHome();
	long m_pPositionIsNS;
	long m_pPositionIsEW;
	long m_pPositionIsELAC1;
	long m_pPositionIsELAC2;
	long m_pPositionIsELAC3;
	long m_pPositionIsETC2;
	long m_pPositionIsCTC;
	long m_pPositionIsETC3;
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

//	CGdipButton m_connect;
//	CGdipButton m_disconnect;
//	CGdipButton m_home;
//	CGdipButton m_park;
//	CGdipButton m_BELRel;
//	CGdipButton m_BELhold;
//	CGdipButton m_BNLRel;
//	CGdipButton m_BNLHold;
//	CGdipButton m_resetmaster;
//	CGdipButton m_resetNS;
//	CGdipButton m_resetEW;
//	CGdipButton m_resetElac1;
//	CGdipButton m_resetELAC2;
//	CGdipButton m_resetElac3;
//	CGdipButton m_resetETC2;
//	CGdipButton m_resetCTC;
//	CGdipButton m_resetETC3;
//	CGdipButton m_LoadSchedule;
//	CGdipButton m_close;

	BOOL RA01_Home();
	BOOL Home_NS_and_EW();
	BOOL Adjust_PM();
	BOOL PM_Park();
	BOOL PM_Ready2Move(void);
	BOOL RaHomeelac1();
	BOOL RaHomeelac2();
	BOOL RaHomeelac3();
	BOOL testETC2(void);
	BOOL testETC3(void);
	BOOL testCTC(void);
	BOOL RaHomectc();
	BOOL Home_LAs();
	BOOL test_EET();
	BOOL test_synchronize_motion();
	BOOL Check_MovementState_Controllers();

	afx_msg void OnBnClickedPark();
	afx_msg void OnBnClickedResetMaster();
	afx_msg void OnBnClickedResetNs();
	afx_msg void OnBnClickedResetEw();
	afx_msg void OnBnClickedResetElac1();
	afx_msg void OnBnClickedResetMaster2();
	afx_msg void OnBnClickedResetElac3();
	afx_msg void OnBnClickedResetEtc2();
	afx_msg void OnBnClickedResetCtc();
	afx_msg void OnBnClickedResetEtc3();
	afx_msg void OnBnClickedClose();
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
//	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL PM_Ready2Home(void);
	
	CString m_username_received;
	CString m_usertype_received;

//	CGdipButton m_signout;
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSignout();
	afx_msg void OnBnClickedSignin();
	CListBox m_ListBox;
	int Count = 0;
	bool ScheduleloadedFlag = FALSE;
	afx_msg void OnBnClickedremove();
	afx_msg void OnLbnSelchangeList1();

	void Receive_ListBox();
	int NumFAs = 0;
	void DisplayName();

	//CToolTipCtrl m_ToolTip;
//	CGdipButton m_signin;
//	CSliderCtrl m_elac1sc;
	
	bool Movectc2tosafelimit();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedHoldBnl();
	CEdit ns;
	CEdit ew;
	CEdit elac1;
	CEdit elac2;
	CEdit elac3;
	CEdit etc2;
	CEdit ctc;
	CEdit etc3;

	CString NSpos;
	CString EWpos;
	CString ELAC1pos;
	CString ELAC2pos;
	CString ELAC3pos;
	CString ETC2pos;
	CString CTCpos;
	CString ETC3pos;
	CString ETC2turns;
	CString ETC3turns;
	CGdipButton m_connect;
	CGdipButton m_disconnect;
	CGdipButton m_home;
	CGdipButton m_park;
	CGdipButton m_BNLHold;
	CGdipButton m_BNLRel;
	CGdipButton m_BELhold;
	CGdipButton m_BELRel;
	CGdipButton m_resetmaster;
	CGdipButton m_resetNS;
	CGdipButton m_resetEW;
	CGdipButton m_resetElac1;
	CGdipButton m_resetELAC2;
	CGdipButton m_resetElac3;
	CGdipButton m_resetETC2;
	CGdipButton m_resetCTC;
	CGdipButton m_resetETC3;
	CGdipButton m_LoadSchedule;
	CGdipButton m_close;
	CGdipButton m_signout;
	CEdit m_etc2not;
	CEdit m_etc3not;
};

#ifndef _DEBUG  // debug version in 6DOFPCMView.cpp
inline C6DOFPCMDoc* C6DOFPCMView::GetDocument() const
   { return reinterpret_cast<C6DOFPCMDoc*>(m_pDocument); }
#endif

