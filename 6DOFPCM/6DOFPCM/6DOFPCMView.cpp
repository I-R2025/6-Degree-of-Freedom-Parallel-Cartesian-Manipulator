
// 6DOFPCMView.cpp : implementation of the C6DOFPCMView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "6DOFPCM.h"
#endif

#include "6DOFPCMDoc.h"
#include "6DOFPCMView.h"

#include <Windows.h>
#include "EposPCmd_Comm.h"
#include "EposPCmd_Drive.h"
#include "EposPCmd_Plc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C6DOFPCMView

IMPLEMENT_DYNCREATE(C6DOFPCMView, CFormView)

BEGIN_MESSAGE_MAP(C6DOFPCMView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_Connect, &C6DOFPCMView::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_Disconnect2, &C6DOFPCMView::OnBnClickedDisconnect2)
	ON_BN_CLICKED(IDC_Home, &C6DOFPCMView::OnBnClickedHome)
//	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Park, &C6DOFPCMView::OnBnClickedPark)
	ON_BN_CLICKED(IDC_Reset_Master, &C6DOFPCMView::OnBnClickedResetMaster)
	ON_BN_CLICKED(IDC_Reset_NS, &C6DOFPCMView::OnBnClickedResetNs)
	ON_BN_CLICKED(IDC_Reset_EW, &C6DOFPCMView::OnBnClickedResetEw)
	ON_BN_CLICKED(IDC_Reset_ELAC1, &C6DOFPCMView::OnBnClickedResetElac1)
	ON_BN_CLICKED(IDC_Reset_Master2, &C6DOFPCMView::OnBnClickedResetMaster2)
	ON_BN_CLICKED(IDC_Reset_ELAC3, &C6DOFPCMView::OnBnClickedResetElac3)
	ON_BN_CLICKED(IDC_Reset_ETC2, &C6DOFPCMView::OnBnClickedResetEtc2)
	ON_BN_CLICKED(IDC_Reset_CTC, &C6DOFPCMView::OnBnClickedResetCtc)
	ON_BN_CLICKED(IDC_Reset_ETC3, &C6DOFPCMView::OnBnClickedResetEtc3)
	ON_BN_CLICKED(IDC_CLOSE, &C6DOFPCMView::OnBnClickedClose)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &C6DOFPCMView::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_Load, &C6DOFPCMView::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_SignOut, &C6DOFPCMView::OnBnClickedSignout)
	ON_BN_CLICKED(IDC_SignIn, &C6DOFPCMView::OnBnClickedSignin)
	ON_BN_CLICKED(IDC_remove, &C6DOFPCMView::OnBnClickedremove)
	ON_LBN_SELCHANGE(IDC_LIST1, &C6DOFPCMView::OnLbnSelchangeList1)

	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Hold_BNL, &C6DOFPCMView::OnBnClickedHoldBnl)
END_MESSAGE_MAP()

// C6DOFPCMView construction/destruction

C6DOFPCMView::C6DOFPCMView()
	: CFormView(IDD_6DOFPCM_FORM)
	, m_cstrMsgArea(_T(""))
	, m_pPositionIsNS(0)
	, m_pPositionIsEW(0)
	, m_pPositionIsELAC1(0)
	, m_pPositionIsELAC2(0)
	, m_pPositionIsELAC3(0)
	, m_pPositionIsETC2(0)
	, m_pPositionIsCTC(0)
	, m_pPositionIsETC3(0)
{
	// TODO: add construction code here
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

C6DOFPCMView::~C6DOFPCMView()
{
	
}

void C6DOFPCMView::ShowWindowNumber(int number)
{
	// This example uses 1 windows
	int windowCount = 4;

	// Validate the parameter
	if ((number >= 0) && (number < windowCount))
	{
		// Create and assign pointers to each window
		CDialog *m_dPointer[4];

		m_dPointer[0] = &m_scheduledlg;
		m_dPointer[1] = &m_la01dlg; 
		m_dPointer[2] = &m_eet02dlg; 
		m_dPointer[3] = &m_eet03dlg;

		// Hide every window except for the chosen one
		for (int count = 0; count < windowCount; count++)
		{
			if (count != number)
			{
				m_dPointer[count]->ShowWindow(SW_HIDE);
			}
			else if (count == number)
			{
				// Show the chosen window and set it's location
				
				m_dPointer[count]->SetWindowPos(&wndTop, m_rSettingsRect.left,m_rSettingsRect.top, m_rSettingsRect.right,m_rSettingsRect.bottom, SWP_SHOWWINDOW);
				m_cTab.SetCurSel(count); m_dPointer[count]->ShowWindow(SW_SHOW); 
//				m_dPointer[count]->OnInitDialog(); 
//				m_dPointer[2]->OnInitDialog();
//				m_dPointer[3]->OnInitDialog();
			}
		}
	}

	DeleteObject(m_scheduledlg);
	DeleteObject(m_la01dlg);
	DeleteObject(m_eet02dlg);
	DeleteObject(m_eet03dlg);
}

void C6DOFPCMView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	C6DOFPCMView::OnShowWindow(bShow, nStatus);

	// When the dialog is shown, display the first window
	if (bShow)
	{
		ShowWindowNumber(bShow);
	}
}




void C6DOFPCMView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_cstrMsgArea);
	DDX_Text(pDX, IDC_EDIT1_positionNS, m_pPositionIsNS);
	DDX_Text(pDX, IDC_EDIT1_positionEW, m_pPositionIsEW);
	DDX_Text(pDX, IDC_EDIT1_positionElac1, m_pPositionIsELAC1);
	DDX_Text(pDX, IDC_EDIT1_positionElac2, m_pPositionIsELAC2);
	DDX_Text(pDX, IDC_EDIT1_positionElac3, m_pPositionIsELAC3);
	DDX_Text(pDX, IDC_EDIT1_positionETC2, m_pPositionIsETC2);
	DDX_Text(pDX, IDC_EDIT1_positionCTC, m_pPositionIsCTC);
	DDX_Text(pDX, IDC_EDIT1_positionETC3, m_pPositionIsETC3);
	//  DDX_Control(pDX, IDC_Connect, m_connect);
	//  DDX_Control(pDX, IDC_Disconnect2, m_disconnect);
	//  DDX_Control(pDX, IDC_Home, m_home);
	//  DDX_Control(pDX, IDC_Park, m_park);
	//  DDX_Control(pDX, IDC_Release_BEL, m_BELRel);
	//  DDX_Control(pDX, IDC_Hold_BEL, m_BELhold);
	//  DDX_Control(pDX, IDC_Release_BNL, m_BNLRel);
	//  DDX_Control(pDX, IDC_Hold_BNL, m_BNLHold);
	//  DDX_Control(pDX, IDC_Reset_Master, m_resetmaster);
	//  DDX_Control(pDX, IDC_Reset_NS, m_resetNS);
	//  DDX_Control(pDX, IDC_Reset_EW, m_resetEW);
	//  DDX_Control(pDX, IDC_Reset_ELAC1, m_resetElac1);
	//  DDX_Control(pDX, IDC_Reset_Master2, m_resetELAC2);
	//  DDX_Control(pDX, IDC_Reset_ELAC3, m_resetElac3);
	//  DDX_Control(pDX, IDC_Reset_ETC2, m_resetETC2);
	//  DDX_Control(pDX, IDC_Reset_CTC, m_resetCTC);
	//  DDX_Control(pDX, IDC_Reset_ETC3, m_resetETC3);
	//  DDX_Control(pDX, IDC_Load, m_LoadSchedule);
	//  DDX_Control(pDX, IDC_CLOSE, m_close);
	DDX_Control(pDX, IDC_TAB1, m_cTab);
	//  DDX_Control(pDX, IDC_SignOut, m_signout);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	//  DDX_Control(pDX, IDC_SignIn, m_signin);
	//  DDX_Control(pDX, IDC_SLIDERla1, m_elac1sc);
	DDX_Control(pDX, IDC_EDIT1, ns);
	DDX_Control(pDX, IDC_EDIT3, ew);
	DDX_Control(pDX, IDC_EDIT4, elac1);
	DDX_Control(pDX, IDC_EDIT5, elac2);
	DDX_Control(pDX, IDC_EDIT6, elac3);
	DDX_Control(pDX, IDC_EDIT7, etc2);
	DDX_Control(pDX, IDC_EDIT8, ctc);
	DDX_Control(pDX, IDC_EDIT10, etc3);
	DDX_Control(pDX, IDC_Connect, m_connect);
	DDX_Control(pDX, IDC_Disconnect2, m_disconnect);
	DDX_Control(pDX, IDC_Home, m_home);
	DDX_Control(pDX, IDC_Park, m_park);
	DDX_Control(pDX, IDC_Hold_BNL, m_BNLHold);
	DDX_Control(pDX, IDC_Release_BNL, m_BNLRel);
	DDX_Control(pDX, IDC_Hold_BEL, m_BELhold);
	DDX_Control(pDX, IDC_Release_BEL, m_BELRel);
	DDX_Control(pDX, IDC_Reset_Master, m_resetmaster);
	DDX_Control(pDX, IDC_Reset_NS, m_resetNS);
	DDX_Control(pDX, IDC_Reset_EW, m_resetEW);
	DDX_Control(pDX, IDC_Reset_ELAC1, m_resetElac1);
	DDX_Control(pDX, IDC_Reset_Master2, m_resetELAC2);
	DDX_Control(pDX, IDC_Reset_ELAC3, m_resetElac3);
	DDX_Control(pDX, IDC_Reset_ETC2, m_resetETC2);
	DDX_Control(pDX, IDC_Reset_CTC, m_resetCTC);
	DDX_Control(pDX, IDC_Reset_ETC3, m_resetETC3);
	DDX_Control(pDX, IDC_Load, m_LoadSchedule);
	DDX_Control(pDX, IDC_CLOSE, m_close);
	DDX_Control(pDX, IDC_SignOut, m_signout);
	DDX_Control(pDX, IDC_EDIT11, m_etc2not);
	DDX_Control(pDX, IDC_EDIT12, m_etc3not);
}

C6DOFPCMView * C6DOFPCMView::GetView()
{
	CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	CView* pView = pFrame->GetActiveView();
	if (!pView)
		return NULL;
	if (!pView->IsKindOf(RUNTIME_CLASS(C6DOFPCMView)))
		return NULL;
	return (C6DOFPCMView*)pView;
}

BOOL C6DOFPCMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void C6DOFPCMView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	ShowWindow(SW_MAXIMIZE);

	

	CRect tabRect;

	m_cTab.GetWindowRect(tabRect);

	// Set the size and location of the child windows based on the tab control
	m_rSettingsRect.left = 545;
	m_rSettingsRect.top = 145;
	m_rSettingsRect.right = 1080;
	m_rSettingsRect.bottom = 625; // tabRect.Height();

	if (this == nullptr)
	{
		RA_DispMsg(_T("ERROR: NULL pointer exception")); return;
	}

	m_scheduledlg.Create(IDD_Schedule_DLG, this);
	m_la01dlg.Create(IDD_LA01_DLG, this);
	m_eet02dlg.Create(IDD_EET02_DLG, this);
	m_eet03dlg.Create(IDD_EET03_DLG, this);
	ShowWindowNumber(0);

	// Set the titles for each tab
	TCITEM tabItem;
	tabItem.mask = TCIF_TEXT;

	tabItem.pszText = _T("Schedule");
	m_cTab.InsertItem(0, &tabItem);

	tabItem.pszText = _T("EET01");
	m_cTab.InsertItem(1, &tabItem);

	tabItem.pszText = _T("EET02");
	m_cTab.InsertItem(2, &tabItem);

	tabItem.pszText = _T("EET03");
	m_cTab.InsertItem(3, &tabItem);

	CLoginDlg SignIndlg; // Creating Login Modal Dialog
	SignIndlg.DoModal();

	
}

void C6DOFPCMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void C6DOFPCMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// C6DOFPCMView diagnostics

#ifdef _DEBUG
void C6DOFPCMView::AssertValid() const
{
	CFormView::AssertValid();
}

void C6DOFPCMView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

C6DOFPCMDoc* C6DOFPCMView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C6DOFPCMDoc)));
	return (C6DOFPCMDoc*)m_pDocument;
}
#endif //_DEBUG


// C6DOFPCMView message handlers


void C6DOFPCMView::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here

/*	try
	{
		int a, b,c; a = 10; b = 0;
		c = a / b; 
	}
	catch(CException& e)
	{
		AfxMessageBox(_T("Exception caught")); return;
	}*/
	C6DOFPCMDoc* pDoc = GetDocument(); // take doc pointer first
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	if (!pDoc)
	{
		MessageBeep(MB_ICONERROR);
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return;
	}

	if (pDoc->m_login_first == 1)
	{
		if (pDoc->m_usertype_received == "Operator")
		{
			Initialize_LEDs_Status();
			if (!RA01_Connectall())
			{
				MessageBeep(MB_ICONERROR);
				pDoc->RA_LogEvents(_T("ERROR: Connection not successful"));
				RA_DispMsg(_T("ERROR: Connection not successful")); return;
			}
			 
	//		Display_Motion_Status()
			if (!Initialize_LEDs_Status())
			{

			}
			else
			{
				pDoc->RA_LogEvents(_T("INFO: Connection Successful, RA01 ready to Home"));
				RA_DispMsg(_T("INFO: Connection Successful, RA01 ready to Home"));
			}
		}
		else
			AfxMessageBox("INFO: Only Operator can peform this operation", MB_TOPMOST);
	}
	else
		AfxMessageBox("INFO: Please Login your account first ", MB_TOPMOST);
	DeleteObject(pDoc);
}

void C6DOFPCMView::RA_DispMsg(CString msg)
{
	CStdioFile LogFile;
	CTime m_Time;
	time_t osBinaryTime;			// C run-time time (defined in <time.h>)
	m_Time = time(&osBinaryTime);	// Get the current time from the operating system.
	int YEAR = m_Time.GetYear();
	int MONTH = m_Time.GetMonth();
	int DAY = m_Time.GetDay();
	int HOUR = m_Time.GetHour();
	int MINT = m_Time.GetMinute();
	int SEC = m_Time.GetSecond();
	CString TimeStamp;
	
	if (msg.Find("ERROR") == 0)
	{
		MessageBeep(MB_ICONERROR); //m_cstrMsgArea = m_cstrMsgArea.Mid(0,4096);
	}

	if (m_cstrMsgArea.GetLength() > 10240)
		m_cstrMsgArea = m_cstrMsgArea.Mid(0, 4096);
	TimeStamp.Format(_T("%04d-%02d-%02d\t%02d:%02d"), YEAR, MONTH, DAY, HOUR, MINT);
	msg.Format(_T("%s\t%s"), TimeStamp, msg);
	
	m_cstrMsgArea = msg + "\r\n" + m_cstrMsgArea;
	UpdateData(FALSE);
}

BOOL C6DOFPCMView::Initialize_LEDs_Status()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		
		AfxMessageBox(_T("ERROR: Unable to get document pointer"));
		return FALSE;
	}

	//if(dc==NULL)
	//{
	dc = GetDC(); 
	dc->GetSafeHdc();
		
		CRect RECT; CWnd* pWnd;

		// Controllers current LEDs

		
			pWnd = GetDlgItem(IDC_STATIC_Master);pWnd->GetWindowRect(&RECT);ScreenToClient(&RECT);
			LED_CMTR.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top); 
		
		
			pWnd = GetDlgItem(IDC_STATIC_NS); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CNSA.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_EW); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CEWA.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_Elac1); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CLA1.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_Elac2); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CLA2.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_Elac3); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CLA3.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_ETC2); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CE2T.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_CTC); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CL3C.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_ETC3); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CE3T.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC__motion_NS); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_NS.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_motion_EW); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_EW.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_motion_Elac1); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_ELAC1.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_motion_Elac2); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_ELAC2.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_motion_Elac3); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_ELAC3.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_motion_ETC2); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_ETC2.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
		
			pWnd = GetDlgItem(IDC_STATIC_motion_CTC); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_CTC.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_STATIC_motion_ETC3); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_ETC3.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		

		
			pWnd = GetDlgItem(IDC_BNL); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_BNL.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_BEL); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_BEL.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XURL1); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XURL1.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XURL2); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XURL2.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XURL3); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XURL3.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XPGL1); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XPGL1.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XPGL2); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XPGL2.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XPGL3); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XPGL3.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XN); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XN.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XS); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XS.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XE); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XE.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_XW); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_XW.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_NHP); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_NHP.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
			pWnd = GetDlgItem(IDC_EHP); pWnd->GetWindowRect(&RECT); ScreenToClient(&RECT);
			LED_EHP.CreateRoundRectRgn(RECT.left, RECT.top, RECT.right, RECT.bottom, RECT.right - RECT.left, RECT.bottom - RECT.top);
		
		// Controllers Status
	//}

	dc->FillRgn(&LED_CMTR, pDoc->bMC ? &BrYellow : &BrGreen); 
	dc->FillRgn(&LED_CNSA, pDoc->bNSC ? &BrYellow : &BrGreen); 
	dc->FillRgn(&LED_CEWA, pDoc->bEWC ? &BrYellow : &BrGreen); 
	dc->FillRgn(&LED_CLA1, pDoc->bELAC1 ? &BrYellow : &BrGreen); 
	dc->FillRgn(&LED_CLA2, pDoc->bELAC2 ? &BrYellow : &BrGreen); 
	dc->FillRgn(&LED_CLA3, pDoc->bELAC3 ? &BrYellow : &BrGreen); 
	dc->FillRgn(&LED_CE2T, pDoc->bETC2 ? &BrYellow : &BrGreen); 
	dc->FillRgn(&LED_CL3C, pDoc->bCTC ? &BrYellow : &BrGreen); 
	dc->FillRgn(&LED_CE3T, pDoc->bETC3 ? &BrYellow : &BrGreen); 

	// Motion Status

	dc->FillRgn(&LED_NS, pDoc->bMovingFlagNS ? &BrRed : &BrGreen); 
	dc->FillRgn(&LED_EW, pDoc->bMovingFlagEW ? &BrRed : &BrGreen); 
	dc->FillRgn(&LED_ELAC1, pDoc->bMovingFlagELAC1 ? &BrRed : &BrGreen); 
	dc->FillRgn(&LED_ELAC2, pDoc->bMovingFlagELAC2 ? &BrRed : &BrGreen);
	dc->FillRgn(&LED_ELAC3, pDoc->bMovingFlagELAC3 ? &BrRed : &BrGreen); 
	dc->FillRgn(&LED_ETC2, pDoc->bMovingFlagETC2 ? &BrRed : &BrGreen); 
	dc->FillRgn(&LED_CTC, pDoc->bMovingFlagCTC ? &BrRed : &BrGreen); 
	dc->FillRgn(&LED_ETC3, pDoc->bMovingFlagETC3 ? &BrRed : &BrGreen); 

	// Brakes Status

	dc->FillRgn(&LED_BNL, pDoc->bBNL ? &BrRed : &BrGreen); 
	dc->FillRgn(&LED_BEL, pDoc->bBEL ? &BrRed : &BrGreen); 

	// LA Home & Limit Switches Status

	dc->FillRgn(&LED_XURL1, pDoc->bHELAC1 ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_XURL2, pDoc->bHELAC2 ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_XURL3, pDoc->bHELAC3 ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_XPGL1, pDoc->bHELAC1 ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_XPGL2, pDoc->bHELAC2 ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_XPGL3, pDoc->bHELAC3 ? &BrGreen : &BrYellow); 

	// PM Limit Switches Status

	dc->FillRgn(&LED_XN, pDoc->bXNL ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_XS, pDoc->bXSL ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_XW, pDoc->bXWL ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_XE, pDoc->bXEL ? &BrGreen : &BrYellow); 

	// PM Home Switches Status

	dc->FillRgn(&LED_NHP, pDoc->bHNSL ? &BrGreen : &BrYellow); 
	dc->FillRgn(&LED_EHP, pDoc->bHEWL ? &BrGreen : &BrYellow); 

	UpdateData(FALSE);
	UpdateWindow();

	//delete dadc;
	ReleaseDC(dc);
//	DeleteObject(pDoc);
//	DeleteObject(LED_CMTR); DeleteObject(LED_CNSA); DeleteObject(LED_CEWA); DeleteObject(LED_CLA1); DeleteObject(LED_CLA2); DeleteObject(LED_CLA3); DeleteObject(LED_CE2T); DeleteObject(LED_CL3C); DeleteObject(LED_CE3T);
//	DeleteObject(LED_NS); DeleteObject(LED_EW); DeleteObject(LED_ELAC1); DeleteObject(LED_ELAC2); DeleteObject(LED_ELAC3); DeleteObject(LED_ETC2); DeleteObject(LED_CTC); DeleteObject(LED_ETC3);
//	DeleteObject(LED_BNL); DeleteObject(LED_BEL);
//	DeleteObject(LED_XURL1); DeleteObject(LED_XURL2); DeleteObject(LED_XURL3); DeleteObject(LED_XPGL1); DeleteObject(LED_XPGL2); DeleteObject(LED_XPGL3);
//	DeleteObject(LED_XN); DeleteObject(LED_XS); DeleteObject(LED_XW); DeleteObject(LED_XE);
//	DeleteObject(LED_NHP); DeleteObject(LED_EHP);
	return TRUE;
}

BOOL C6DOFPCMView::RA01_Connectall()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{

		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}


	if (pDoc->PDisconnect == 0)
	{
		if (!Connect_PM())
		{
			pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": PM Connection failed");
			pDoc->RA_LogEvents(pDoc->errormsg);
			RA_DispMsg(pDoc->errormsg); return FALSE;
		}

		pDoc->RA_LogEvents(_T("INFO: PM Connected"));

		if (!Connect_LA())
		{
			pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": LA Connection failed");
			pDoc->RA_LogEvents(pDoc->errormsg);
			RA_DispMsg(pDoc->errormsg); return FALSE;

		}

		pDoc->RA_LogEvents(_T("INFO: LA Connected"));

		if (!Connect_EET())
		{
			pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": EET Connection failed");
			pDoc->RA_LogEvents(pDoc->errormsg);
			RA_DispMsg(pDoc->errormsg); return FALSE;

		}

	}

	pDoc->RA_LogEvents(_T("INFO: EET Connected"));

	if (!Check_FaultState_Controllers())
	{
	pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Controller is in Fault State");
	pDoc->RA_LogEvents(pDoc->errormsg);
	RA_DispMsg(pDoc->errormsg); return FALSE;

	}

	//Modified on 27-01-2017 to include controllers 8 & 9
	//Sending NMT(Network Management Services) to the Gateway

	if (!VCM_SendNMTService(pDoc->hGatewayHandleInt, NCS_START_REMOTE_NODE, &(pDoc->dwErrorCode)))
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": NMT Service failed");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg); return FALSE;

	}

	pDoc->RA_LogEvents(_T("INFO: Host Connected to all the controllers"));
	RA_DispMsg(_T("INFO: Host Connected to all the controllers"));

	if (!Inputs_Configuration())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Input Configuration failed");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg); return FALSE;

	}

	pDoc->RA_LogEvents(_T("INFO: Input Configuration Successful"));
	//Getting IO Status

	if (!PM_LimitSwitches_Status())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to check Limit Switches Status");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg); return FALSE;

	}

	if (!PM_HomeSwitches_Status())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to check Home Switches Status");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg); return FALSE;

	}

	if (!LA_LimitSwitches_Status())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to check LA Limit Switches Status");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg); return FALSE;

	}


	if (!Release_Brakes())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to release Brakes");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg); return FALSE;

	}

	if (!Brakes_Status())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to check Brakes Status");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg); return FALSE;

	}

	pDoc->bConfigFlag = TRUE;

	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::RA01_Disconnectall()
{
	// TODO: Add your command handler code here

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	pDoc->targetposition = -200000;

	if (!Movectc2tosafelimit())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to move CTC to safe limit"));
		RA_DispMsg(_T("ERROR: Unable to move CTC to safe limit"));
		return FALSE;
	}

	if (!Hold_Brakes())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to Hold Brakes");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!Brakes_Status())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to check Brakes Status");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	//Getting IO Status

	if (!PM_LimitSwitches_Status())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to check Limit Switches Status");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!PM_HomeSwitches_Status())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to check Home Switches Status");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!LA_LimitSwitches_Status())
	{
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to check LA Limit Switches Status");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	

	/*
	if (!DisConnect_EET())
	{
	pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to Disconnect EET's");
	pDoc->RA_LogEvents(pDoc->errormsg);
	RA_DispMsg(pDoc->errormsg);
	return FALSE;
	}


	if(!DisConnect_LA())
	{
	pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to Disconnect LA");
	RA_DispMsg(_T("ERROR: Unable to Disconnect LA"));
	return FALSE;
	}

	pDoc->RA_LogEvents("INFO: LA Disconnected");
	RA_DispMsg("INFO: LA Disconnected");

	if(!DisConnect_PM())
	{
	pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to Disconnect PM");
	RA_DispMsg(_T("ERROR: Unable to Disconnect PM"));
	return FALSE;
	}
	*/
	pDoc->RA_LogEvents("INFO: PM Disconnected");
	RA_DispMsg("INFO: PM Disconnected");

	pDoc->RA_LogEvents(_T("INFO: Host DisConnected to all the controllers"));
	RA_DispMsg(_T("INFO: Host DisConnected to all the controllers"));

	pDoc->bMC = TRUE; 
	pDoc->bNSC = TRUE; 
	pDoc->bEWC = TRUE; 
	pDoc->bELAC1 = TRUE; 
	pDoc->bELAC2 = TRUE; 
	pDoc->bELAC3 = TRUE; 
	pDoc->bETC2 = TRUE; 
	pDoc->bCTC = TRUE; 
	pDoc->bETC3 = TRUE; 


	pDoc->bCommFlag = TRUE;

	pDoc->RA_LogEvents(_T("INFO: Successfully Closed all communications: Now Exit -> "));
	RA_DispMsg(_T("INFO: Successfully Closed all communications: Now Exit -> "));
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Connect_PM()
{
	//Opening Communication with master controller through RS232

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	// Open Communication

	pDoc->hCommHandle = VCM_OpenCommunication("MAXON SERIAL V2", "RS232", "COM1", &(pDoc->dwErrorCode));
	if (pDoc->hCommHandle == NULL)
	{
		pDoc->errorcode = 1006;
		pDoc->RA_LogEvents(_T("ERROR: Unable to establish RS232 communication")); return FALSE;
	}
	//Setting Protocol Stack settings 

	if (!VCM_SetProtocolStackSettings(pDoc->hCommHandle, pDoc->dwBaudRate, pDoc->dwTimeOut, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 1007;
		pDoc->RA_LogEvents(_T("ERROR: Master controller protocol stack settings failed")); return FALSE;
	}

	/*BYTE pData;
	BYTE Communication;
	DWORD pNbOFBytesRead;
	VCM_GetObject(pDoc->hCommHandle, 0x1000, 0x00, &pData, 4, &pNbOFBytesRead, &(pDoc->dwErrorCode));
	Communication = pData;*/

	//Opening Gateways for All nodes [2-9]

	pDoc->hGatewayHandleInt = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleInt == NULL)
	{
		pDoc->errorcode = 1008;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open Master controller gateway")); return FALSE;
	}

	pDoc->hGatewayHandleExt2 = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleExt2 == NULL)
	{
		pDoc->errorcode = 1009;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open NS axis gateway")); return FALSE;
	}

	pDoc->hGatewayHandleExt3 = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleExt3 == NULL)
	{
		pDoc->errorcode = 2001;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open EW axis gateway")); return FALSE;
	}

	// Gateway Settings

	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleInt, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDInt, &(pDoc->dwErrorCode)))
	{

		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for Master controller failed")); return FALSE;
	}

	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleExt2, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDExt, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 1010;
		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for NS axis failed")); return FALSE;
	}

	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleExt3, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDExt, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 2002;
		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for EW axis failed")); return FALSE;
	}

	// Open Drive

	pDoc->hDriveHandleInt = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleInt, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleInt == NULL)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for Master controller")); return FALSE;;
	}

	pDoc->hDriveHandleExt2 = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleExt2, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleExt2 == NULL)
	{
		pDoc->errorcode = 1011;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for NS controller")); return FALSE;
	}
	pDoc->hDriveHandleExt3 = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleExt3, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleExt3 == NULL)
	{
		pDoc->errorcode = 2003;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for EW controller")); return FALSE;
	}


	if (!VCM_SetDriveSettings(pDoc->hDriveHandleInt, pDoc->byteEpos2NodeIDInt, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for Master controller failed")); return FALSE;
	}

	if (!VCM_SetDriveSettings(pDoc->hDriveHandleExt2, pDoc->byteEpos2NodeIDExt2, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 1012;
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for NS controller failed")); return FALSE;
	}

	if (!VCM_SetDriveSettings(pDoc->hDriveHandleExt3, pDoc->byteEpos2NodeIDExt3, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 2004;
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for EW controller failed")); return FALSE;
	}

	// Reset Drive

	if (!VCM_ResetDevice(pDoc->hDriveHandleInt, &(pDoc->dwErrorCode)))
	{
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset Master controller")); return FALSE;
	}

	if (!VCM_ResetDevice(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
	{
	pDoc->errorcode = 1013;
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset NS controller")); return FALSE;
	}

	if (!VCM_ResetDevice(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
	{
	pDoc->errorcode = 2005;
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset EW controller")); return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Connect_LA()
{
	// TODO: Add your command handler code here

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("ERROR: Unable to get document pointer ") + pDoc->errorcode;
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	// Open Gateway

	pDoc->hGatewayHandleExt4 = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleExt4 == NULL)
	{
		pDoc->errorcode = 3001;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open ELAC1 controller gateway")); return FALSE;
	}

	pDoc->hGatewayHandleExt5 = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleExt5 == NULL)
	{
		pDoc->errorcode = 4001;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open ELAC2 controller gateway")); return FALSE;
	}

	pDoc->hGatewayHandleExt6 = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleExt6 == NULL)
	{
		pDoc->errorcode = 5001;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open ELAC3 controller gateway")); return FALSE;
	}

	// Gateway Settings

	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleExt4, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDExt, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 3002;
		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for ELAC1 controller failed")); return FALSE;
	}

	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleExt5, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDExt, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 4002;
		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for ELAC2 controller failed")); return FALSE;
	}

	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleExt6, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDExt, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 5002;
		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for ELAC3 controller failed")); return FALSE;
	}

	// Open Drive

	pDoc->hDriveHandleExt4 = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleExt4, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleExt4 == NULL)
	{
		pDoc->errorcode = 3003;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for ELAC1 controller")); return FALSE;
	}

	pDoc->hDriveHandleExt5 = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleExt5, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleExt5 == NULL)
	{
		pDoc->errorcode = 4003;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for ELAC2 controller")); return FALSE;
	}

	pDoc->hDriveHandleExt6 = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleExt6, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleExt6 == NULL)
	{
		pDoc->errorcode = 5003;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for ELAC3 controller")); return FALSE;
	}

	// Drive Settings

	if (!VCM_SetDriveSettings(pDoc->hDriveHandleExt4, pDoc->byteEpos2NodeIDExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 3004;
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for ELAC1 controller failed")); return FALSE;
	}
	if (!VCM_SetDriveSettings(pDoc->hDriveHandleExt5, pDoc->byteEpos2NodeIDExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 4004;
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for ELAC2 controller failed")); return FALSE;
	}
	if (!VCM_SetDriveSettings(pDoc->hDriveHandleExt6, pDoc->byteEpos2NodeIDExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 5004;
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for ELAC3 controller failed")); return FALSE;
	}

	// Reset Device

		if (!VCM_ResetDevice(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
	pDoc->errorcode = 3005;
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset ELAC1 controller")); return FALSE;
	}

	if (!VCM_ResetDevice(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
	pDoc->errorcode = 4005;
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset ELAC2 controller")); return FALSE;
	}
	if (!VCM_ResetDevice(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
	pDoc->errorcode = 5005;
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset ELAC3 controller")); return FALSE;
	}

	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Connect_EET()
{
	// TODO: Add your command handler code here

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox(_T("ERROR: Unable to get document pointer"));
		return FALSE;
	}

	//Open Gateway

	pDoc->hGatewayHandleExt7 = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleExt7 == NULL)
	{
		pDoc->errorcode = 6001;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open ETC2 controller gateway")); return FALSE;
	}
	pDoc->hGatewayHandleExt8 = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleExt8 == NULL)
	{
		pDoc->errorcode = 7001;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open CTC controller gateway")); return FALSE;
	}
	pDoc->hGatewayHandleExt9 = VCM_OpenGateway("CANopen", "EPOS2 P", pDoc->hCommHandle, &(pDoc->dwErrorCode));
	if (pDoc->hGatewayHandleExt9 == NULL)
	{
		pDoc->errorcode = 8001;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open ETC3 controller gateway")); return FALSE;
	}
	//Modified on 27-01-2017 to include controllers 8 & 9
	//Setting Gateway Settings for all nodes [2-9]

	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleExt7, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDExt, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 6002;
		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for ETC2 controller failed")); return FALSE;
	}
	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleExt8, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDExt, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 7002;
		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for CTC controller failed")); return FALSE;
	}
	if (!VCM_SetGatewaySettings(pDoc->hGatewayHandleExt9, pDoc->byteEpos2PNodeID, pDoc->byteRemoteNetworkIDExt, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 8002;
		pDoc->RA_LogEvents(_T("ERROR: Gateway settings for ETC3 controller failed")); return FALSE;
	}
	//Modified on 27-01-2017 to include controllers 8 & 9
	//Opening Drives for all Nodes[2-9]


	pDoc->hDriveHandleExt7 = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleExt7, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleExt7 == NULL)
	{
		pDoc->errorcode = 6003;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for ETC2 controller")); return FALSE;
	}
	pDoc->hDriveHandleExt8 = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleExt8, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleExt8 == NULL)
	{
		pDoc->errorcode = 7003;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for CTC controller")); return FALSE;
	}
	pDoc->hDriveHandleExt9 = VCM_OpenDrive("EPOS2", pDoc->hGatewayHandleExt9, &(pDoc->dwErrorCode));
	if (pDoc->hDriveHandleExt9 == NULL)
	{
		pDoc->errorcode = 8003;
		pDoc->RA_LogEvents(_T("ERROR: Unable to open drive for ETC3 controller")); return FALSE;
	}
	//Modified on 27-01-2017 to include controllers 8 & 9

	//Setting Drive Settings for all Drives [2-9]


	if (!VCM_SetDriveSettings(pDoc->hDriveHandleExt7, pDoc->byteEpos2NodeIDExt7, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 6004;
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for ETC2 controller failed")); return FALSE;
	}
	if (!VCM_SetDriveSettings(pDoc->hDriveHandleExt8, pDoc->byteEpos2NodeIDExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 7004;
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for CTC controller failed")); return FALSE;
	}
	if (!VCM_SetDriveSettings(pDoc->hDriveHandleExt9, pDoc->byteEpos2NodeIDExt9, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 8004;
		pDoc->RA_LogEvents(_T("ERROR: Drive settings for ETC3 controller failed")); return FALSE;
	}
	//Modified on 27-01-2017 to include controllers 8 & 9
	//Reset All Devices [2-9]

		if (!VCM_ResetDevice(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
	{
	pDoc->errorcode = 6005;
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset ETC2 controller")); return FALSE;
	}
	if (!VCM_ResetDevice(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
	pDoc->errorcode = 7005;
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset CTC controller")); return FALSE;
	}
	if (!VCM_ResetDevice(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
	{
	pDoc->errorcode = 8005;
	pDoc->RA_LogEvents(_T("ERROR: Unable to reset ETC3 controller")); return FALSE;
	}
	//Modified on 27-01-2017 to include controllers 8 & 9



	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Hold_Brakes()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!VCM_DigitalOutputConfiguration(pDoc->hDriveHandleExt2, 4, DOC_GENERAL_PURPOSE_D, TRUE, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 1036;
		pDoc->RA_LogEvents(_T("ERROR: Unable to apply NS brake")); return FALSE;
	}
	if (!VCM_DigitalOutputConfiguration(pDoc->hDriveHandleExt3, 4, DOC_GENERAL_PURPOSE_D, TRUE, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 2031;
		pDoc->RA_LogEvents(_T("ERROR: Unable to apply EW brake")); return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::DisConnect_EET()
{
	// Disable States
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 6017;
		pDoc->RA_LogEvents(_T("ERROR: Setting disable state of ETC2 controller failed")); return FALSE;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 8020;
		pDoc->RA_LogEvents(_T("ERROR: Setting disable state of CTC controller failed")); return FALSE;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 7019;
		pDoc->RA_LogEvents(_T("ERROR: Setting disable state of ETC3 controller failed")); return FALSE;
	}

	// Closing Drives

	if (!VCM_CloseDrive(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close ETC2 drive")); return FALSE;
	}

	if (!VCM_CloseDrive(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close CTC drive")); return FALSE;
	}

	if (!VCM_CloseDrive(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close ETC3 drive")); return FALSE;
	}

	// Closing Gateway's

	if (!VCM_CloseGateway(pDoc->hGatewayHandleExt7, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close ETC2 Gateway")); return FALSE;
	}

	if (!VCM_CloseGateway(pDoc->hGatewayHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close CTC Gateway")); return FALSE;
	}

	if (!VCM_CloseGateway(pDoc->hGatewayHandleExt9, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close ETC3 Gateway")); return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::DisConnect_LA()
{
	// Disable States

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting disable state of LA1 controller failed")); return FALSE;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting disable state of LA2 controller failed")); return FALSE;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting disable state of LA3 controller failed")); return FALSE;
	}

	// Closing Drives

	if (!VCM_CloseDrive(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close LA1 drive")); return FALSE;
	}

	if (!VCM_CloseDrive(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close LA2 drive")); return FALSE;
	}

	if (!VCM_CloseDrive(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close LA3 drive")); return FALSE;
	}

	// Closing Gateway's

	if (!VCM_CloseGateway(pDoc->hGatewayHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close LA1 Gateway")); return FALSE;
	}

	if (!VCM_CloseGateway(pDoc->hGatewayHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close LA2 Gateway")); return FALSE;
	}

	if (!VCM_CloseGateway(pDoc->hGatewayHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close LA3 Gateway")); return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::DisConnect_PM()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	// Disable States

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting disable state of NS controller failed")); return FALSE;
	}
	if (!VCM_SetDisableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting disable state of EW controller failed")); return FALSE;
	}

	//Close Drives

	if (!VCM_CloseDrive(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close NS drive")); return FALSE;
	}
	if (!VCM_CloseDrive(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close EW drive")); return FALSE;
	}

	// Close Gateway's

	if (!VCM_CloseGateway(pDoc->hGatewayHandleExt2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close NS Gateway")); return FALSE;
	}

	if (!VCM_CloseGateway(pDoc->hGatewayHandleExt3, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close EW Gateway")); return FALSE;
	}

	// Close All Communication

	if (!VCM_CloseAllCommunication(&(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to close all communication")); return FALSE;
	}

	// 1000000;			     
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Check_FaultState_Controllers()
{
	// Clear Fault of PM

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("ERROR: Unable to get document pointer ") + pDoc->errorcode;
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleInt, &(pDoc->bMC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of Master controller")); return FALSE;
	}

	if (pDoc->bMC)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleInt, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of Master controller")); return FALSE;
		}
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt2, &(pDoc->bNSC), &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 1014;
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of NS controller")); return FALSE;
	}

	if (pDoc->bNSC)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of NS controller")); return FALSE;
		}
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt3, &(pDoc->bEWC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of EW controller")); return FALSE;
	}

	if (pDoc->bEWC)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of EW controller")); return FALSE;
		}
	}

	// Clear the Fault of LA's

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt4, &(pDoc->bELAC1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC1 controller")); return FALSE;
	}

	if (pDoc->bELAC1)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of ELAC1 controller")); return FALSE;
		}
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt5, &(pDoc->bELAC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC2 controller")); return FALSE;
	}

	if (pDoc->bELAC2)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of ELAC2 controller")); return FALSE;
		}
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller")); return FALSE;
	}

	if (pDoc->bELAC3)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of ELAC3 controller")); return FALSE;
		}
	}

	// Clear fault of EET's

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt7, &(pDoc->bETC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC2 controller")); return FALSE;
	}

	if (pDoc->bETC2)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of ETC2 controller")); return FALSE;
		}
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt8, &(pDoc->bCTC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of CTC controller")); return FALSE;
	}

	if (pDoc->bCTC)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of CTC controller")); return FALSE;
		}
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller")); return FALSE;
	}

	if (pDoc->bETC3)
	{
		if (!VCM_ClearFault(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to clear fault of ETC3 controller")); return FALSE;
		}
	}


	DeleteObject(pDoc);
	return TRUE;;
}

BOOL C6DOFPCMView::Inputs_Configuration()
{
	//Configuring Digital Inputs and Outputs for all Drives [2-9]

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox(_T("ERROR: Unable to get document pointer"));
		return FALSE;
	}

	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt2, 4, DIC_HOME_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure NS home switch")); return FALSE;
	}
	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt2, 5, DIC_POSITIVE_LIMIT_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure Extreme North Limit Switch")); return FALSE;
	}
	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt2, 6, DIC_NEGATIVE_LIMIT_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure Extreme South Limit Switch")); return FALSE;
	}

	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt3, 4, DIC_HOME_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure EW home switch")); return FALSE;
	}
	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt3, 5, DIC_POSITIVE_LIMIT_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure Extreme East Limit Switch")); return FALSE;
	}
	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt3, 6, DIC_NEGATIVE_LIMIT_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure Extreme West Limit Switch")); return FALSE;
	}

	//Home Switch Configurations for  ELAC1->ELAC3

	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt4, 4, DIC_HOME_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure ELAC1 home switch")); return FALSE;
	}
	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt5, 4, DIC_HOME_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure ELAC2 home switch")); return FALSE;
	}
	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt6, 4, DIC_HOME_SWITCH, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to configure ELAC3 home switch")); return FALSE;
	}

	// Master Encode Channels configuration for master encoder mode
	/*
	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt6, 2, DIC_GENERAL_PURPOSE_A, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
	pDoc->RA_LogEvents(_T("ERROR: Unable to configure Master Channel B on Slave Digital Input 2")); return FALSE;
	}

	if (!VCM_DigitalInputConfiguration(pDoc->hDriveHandleExt6, 3, DIC_GENERAL_PURPOSE_B, TRUE, 0, 1, &(pDoc->dwErrorCode)))
	{
	pDoc->RA_LogEvents(_T("ERROR: Unable to configure Master Channel A on Slave Digital Input 3")); return FALSE;
	}

	*/
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Release_Brakes()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox(_T("ERROR: Unable to get document pointer"));
		return FALSE;
	}

	if (!VCM_DigitalOutputConfiguration(pDoc->hDriveHandleExt2, 4, DOC_GENERAL_PURPOSE_D, FALSE, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to release NS brake")); return FALSE;
	}
	if (!VCM_DigitalOutputConfiguration(pDoc->hDriveHandleExt3, 4, DOC_GENERAL_PURPOSE_D, FALSE, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to release EW brake")); return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::PM_LimitSwitches_Status()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt2, &(pDoc->wDigInStateNS), &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 1038;
		pDoc->RA_LogEvents(_T("ERROR: Unable to get NS digital Inputs")); return FALSE;
	}
	if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt3, &(pDoc->wDigInStateEW), &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 2033;
		pDoc->RA_LogEvents(_T("ERROR: Unable to get EW digital Inputs")); return FALSE;
	}

	// PM Extreme Limit Switxhes Status

	if (pDoc->wDigInStateNS & 0x0002)  pDoc->bXNL = TRUE;	else	pDoc->bXNL = FALSE;
	if (pDoc->wDigInStateNS & 0x0001)  pDoc->bXSL = TRUE;	else	pDoc->bXSL = FALSE;
	if (pDoc->wDigInStateEW & 0x0002)  pDoc->bXWL = TRUE;	else	pDoc->bXWL = FALSE;
	if (pDoc->wDigInStateEW & 0x0001)  pDoc->bXEL = TRUE;	else	pDoc->bXEL = FALSE;
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::PM_HomeSwitches_Status()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	// PM Home Switxhes Status

	if (pDoc->wDigInStateNS & 0x0004)  pDoc->bHNSL = TRUE;	else	pDoc->bHNSL = FALSE;
	if (pDoc->wDigInStateEW & 0x0004)  pDoc->bHEWL = TRUE;	else	pDoc->bHEWL = FALSE;
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::LA_LimitSwitches_Status() // LA_Home Switches Status
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt4, &(pDoc->wDigInStateELAC1), &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 3029;
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ELAC1 digital Input state")); return FALSE;
	}
	if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt5, &(pDoc->wDigInStateELAC2), &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 4029;
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ELAC2 digital Input state")); return FALSE;
	}
	if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt6, &(pDoc->wDigInStateELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 5031;
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ELAC3 digital Input state")); return FALSE;
	}

	// LA's Extreme Limit Switches Status

	if (pDoc->wDigInStateELAC1 & 0x0004)  pDoc->bHELAC1 = TRUE;	else	pDoc->bHELAC1 = FALSE;
	if (pDoc->wDigInStateELAC2 & 0x0004)  pDoc->bHELAC2 = TRUE;	else	pDoc->bHELAC2 = FALSE;
	if (pDoc->wDigInStateELAC3 & 0x0004)  pDoc->bHELAC3 = TRUE;	else	pDoc->bHELAC3 = FALSE;
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Brakes_Status()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	if (!VCM_GetAllDigitalOutputs(pDoc->hDriveHandleExt2, &(pDoc->wDigOutStateNS), &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 1037;
		pDoc->RA_LogEvents(_T("ERROR: Unable to get NS digital output state")); return FALSE;
	}
	if (!VCM_GetAllDigitalOutputs(pDoc->hDriveHandleExt3, &(pDoc->wDigOutStateEW), &(pDoc->dwErrorCode)))
	{
		pDoc->errorcode = 2032;
		pDoc->RA_LogEvents(_T("ERROR: Unable to get EW digital output state")); return FALSE;
	}

	// Brakes Status

	if (pDoc->wDigOutStateNS & 0x1000) pDoc->bBNL = TRUE;		else	pDoc->bBNL = FALSE;
	if (pDoc->wDigOutStateEW & 0x1000) pDoc->bBEL = TRUE;		else	pDoc->bBEL = FALSE;
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Display_Motion_Status()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}


	dc = GetDC(); 
	dc->GetSafeHdc();
	UpdateData(TRUE);

	// Controllers Status

	/*	if (pDoc->bMC) dadc->FillRgn(&LED_CMTR, &BrYellow); else dadc->FillRgn(&LED_CMTR, &BrGreen);
	if (pDoc->bNSC) dadc->FillRgn(&LED_CNSA, &BrYellow); else dadc->FillRgn(&LED_CNSA, &BrGreen);
	if (pDoc->bEWC) dadc->FillRgn(&LED_CEWA, &BrYellow); else dadc->FillRgn(&LED_CEWA, &BrGreen);
	if (pDoc->bELAC1) dadc->FillRgn(&LED_CLA1, &BrYellow); else dadc->FillRgn(&LED_CLA1, &BrGreen);
	if (pDoc->bELAC2) dadc->FillRgn(&LED_CLA2, &BrYellow); else dadc->FillRgn(&LED_CLA2, &BrGreen);
	if (pDoc->bELAC3) dadc->FillRgn(&LED_CLA3, &BrYellow); else dadc->FillRgn(&LED_CLA3, &BrGreen);
	if (pDoc->bETC2) dadc->FillRgn(&LED_CE2T, &BrYellow); else dadc->FillRgn(&LED_CE2T, &BrGreen);
	if (pDoc->bCTC) dadc->FillRgn(&LED_CL3C, &BrYellow); else dadc->FillRgn(&LED_CL3C, &BrGreen);
	if (pDoc->bETC3) dadc->FillRgn(&LED_CE3T, &BrYellow); else dadc->FillRgn(&LED_CE3T, &BrGreen);*/



	//******************** commented on 13-8-21 **********************************************************

	if (dc != nullptr)
	{
		dc->FillRgn(&LED_CMTR, pDoc->bMC ? &BrYellow : &BrGreen);
		dc->FillRgn(&LED_CNSA, pDoc->bNSC ? &BrYellow : &BrGreen);
		dc->FillRgn(&LED_CEWA, pDoc->bEWC ? &BrYellow : &BrGreen);
		dc->FillRgn(&LED_CLA1, pDoc->bELAC1 ? &BrYellow : &BrGreen);
		dc->FillRgn(&LED_CLA2, pDoc->bELAC2 ? &BrYellow : &BrGreen);
		dc->FillRgn(&LED_CLA3, pDoc->bELAC3 ? &BrYellow : &BrGreen);
		dc->FillRgn(&LED_CE2T, pDoc->bETC2 ? &BrYellow : &BrGreen);
		dc->FillRgn(&LED_CL3C, pDoc->bCTC ? &BrYellow : &BrGreen);
		dc->FillRgn(&LED_CE3T, pDoc->bETC3 ? &BrYellow : &BrGreen);

		// Motion Status

		dc->FillRgn(&LED_NS, pDoc->bMovingFlagNS ? &BrGreen : &BrBlue);
		dc->FillRgn(&LED_EW, pDoc->bMovingFlagEW ? &BrGreen : &BrBlue);
		dc->FillRgn(&LED_ELAC1, pDoc->bMovingFlagELAC1 ? &BrGreen : &BrBlue);
		dc->FillRgn(&LED_ELAC2, pDoc->bMovingFlagELAC2 ? &BrGreen : &BrBlue);
		dc->FillRgn(&LED_ELAC3, pDoc->bMovingFlagELAC3 ? &BrGreen : &BrBlue);
		dc->FillRgn(&LED_ETC2, pDoc->bMovingFlagETC2 ? &BrGreen : &BrBlue);
		dc->FillRgn(&LED_CTC, pDoc->bMovingFlagCTC ? &BrGreen : &BrBlue);
		dc->FillRgn(&LED_ETC3, pDoc->bMovingFlagETC3 ? &BrGreen : &BrBlue);
		// Brakes Status

		dc->FillRgn(&LED_BNL, pDoc->bBNL ? &BrRed : &BrGreen);
		dc->FillRgn(&LED_BEL, pDoc->bBEL ? &BrRed : &BrGreen);

		// LA Home & Limit Switches Status

		dc->FillRgn(&LED_XURL1, pDoc->bHELAC1 ? &BrGreen : &BrYellow);
		dc->FillRgn(&LED_XURL2, pDoc->bHELAC2 ? &BrGreen : &BrYellow);
		dc->FillRgn(&LED_XURL3, pDoc->bHELAC3 ? &BrGreen : &BrYellow);
		dc->FillRgn(&LED_XPGL1, &BrYellow);
		dc->FillRgn(&LED_XPGL2, &BrYellow);
		dc->FillRgn(&LED_XPGL3, &BrYellow);

		// PM Limit Switches Status

		dc->FillRgn(&LED_XN, pDoc->bXNL ? &BrGreen : &BrYellow);
		dc->FillRgn(&LED_XS, pDoc->bXSL ? &BrGreen : &BrYellow);
		dc->FillRgn(&LED_XW, pDoc->bXWL ? &BrGreen : &BrYellow);
		dc->FillRgn(&LED_XE, pDoc->bXEL ? &BrGreen : &BrYellow);

		// PM Home Switches Status

		dc->FillRgn(&LED_NHP, pDoc->bHNSL ? &BrGreen : &BrYellow);
		dc->FillRgn(&LED_EHP, pDoc->bHEWL ? &BrGreen : &BrYellow);
	}


	//if (pDoc->bHomeandTestFlag == FALSE)
	//	{


	NSpos.Format(_T("%10d"), pDoc->pPositionIsNS);
	ns.SetWindowText(NSpos); UpdateWindow();
	EWpos.Format(_T("%10d"), pDoc->pPositionIsEW);
	ew.SetWindowText(EWpos); UpdateWindow();
	ELAC1pos.Format(_T("%10d"), pDoc->pPositionIsLA1);
	elac1.SetWindowText(ELAC1pos); UpdateWindow();
	ELAC2pos.Format(_T("%10d"), pDoc->pPositionIsLA2);
	elac2.SetWindowText(ELAC2pos); UpdateWindow();
	ELAC3pos.Format(_T("%10d"), pDoc->pPositionIsLA3);
	elac3.SetWindowText(ELAC3pos); UpdateWindow();
	ETC2pos.Format(_T("%10d"), pDoc->pPositionIsETC2);
	etc2.SetWindowText(ETC2pos); UpdateWindow();
	CTCpos.Format(_T("%10d"), pDoc->pPositionIsCTC);
	ctc.SetWindowText(CTCpos); UpdateWindow();
	ETC3pos.Format(_T("%10d"), pDoc->pPositionIsETC3);
	etc3.SetWindowText(ETC3pos); UpdateWindow();
	ETC2turns.Format(_T("%03f"), pDoc->notetc2);
	m_etc2not.SetWindowText(ETC2turns); UpdateWindow();
	ETC3turns.Format(_T("%03f"), pDoc->notetc3);
	m_etc3not.SetWindowText(ETC3turns); UpdateWindow();
	m_pPositionIsNS = pDoc->pPositionIsNS; 
	m_pPositionIsEW = pDoc->pPositionIsEW; 
	m_pPositionIsELAC1 = pDoc->pPositionIsLA1; 
	m_pPositionIsELAC2 = pDoc->pPositionIsLA2; 
	m_pPositionIsELAC3 = pDoc->pPositionIsLA3; 
	m_pPositionIsETC2 = pDoc->pPositionIsETC2;
	m_pPositionIsCTC = pDoc->pPositionIsCTC; 
	m_pPositionIsETC3 = pDoc->pPositionIsETC3;

	Sleep(500);

	//UpdateData(FALSE); UpdateWindow();
	/*	}
	else
	{
	m_pPositionIsNS = (702820 - pDoc->pPositionIsNS) /1229.502;
	m_pPositionIsEW = (-12000 - pDoc->pPositionIsEW) / 1990.278;
	m_pPositionIsELAC1 = pDoc->pPositionIsLA1 / 24500;
	m_pPositionIsELAC2 = pDoc->pPositionIsLA2 / 24500;
	m_pPositionIsELAC3 = pDoc->pPositionIsLA3 / 24500;
	m_pPositionIsETC2 = pDoc->pPositionIsETC2 / 1102500;
	m_pPositionIsCTC = pDoc->pPositionIsCTC / 179114;
	m_pPositionIsETC3 = pDoc->pPositionIsETC3 / 179667;

	Sleep(200);

	UpdateData(FALSE);
	}*/

	//******************** commented on 13-8-21 **********************************************************
	if (dc != nullptr)
	{
		dc->FillRgn(&LED_NS, pDoc->bMovingFlagNS ? &BrGreen : &BrLBlue);
		dc->FillRgn(&LED_EW, pDoc->bMovingFlagEW ? &BrGreen : &BrLBlue);
		dc->FillRgn(&LED_ELAC1, pDoc->bMovingFlagELAC1 ? &BrGreen : &BrLBlue);
		dc->FillRgn(&LED_ELAC2, pDoc->bMovingFlagELAC2 ? &BrGreen : &BrLBlue);
		dc->FillRgn(&LED_ELAC3, pDoc->bMovingFlagELAC3 ? &BrGreen : &BrLBlue);
		dc->FillRgn(&LED_ETC2, pDoc->bMovingFlagETC2 ? &BrGreen : &BrLBlue);
		dc->FillRgn(&LED_CTC, pDoc->bMovingFlagCTC ? &BrGreen : &BrLBlue);
		dc->FillRgn(&LED_ETC3, pDoc->bMovingFlagETC3 ? &BrGreen : &BrLBlue);
	}

	/*	if (pDoc->bMC == TRUE)
		{
			dc->FillRgn(&LED_NS, pDoc->bMovingFlagNS ? &BrRed : &BrRed);
			dc->FillRgn(&LED_EW, pDoc->bMovingFlagEW ? &BrRed : &BrRed);
			dc->FillRgn(&LED_ELAC1, pDoc->bMovingFlagELAC1 ? &BrRed : &BrRed);
			dc->FillRgn(&LED_ELAC2, pDoc->bMovingFlagELAC2 ? &BrRed : &BrRed);
			dc->FillRgn(&LED_ELAC3, pDoc->bMovingFlagELAC3 ? &BrRed : &BrRed);
			dc->FillRgn(&LED_ETC2, pDoc->bMovingFlagETC2 ? &BrRed : &BrRed);
			dc->FillRgn(&LED_CTC, pDoc->bMovingFlagCTC ? &BrRed : &BrRed);
			dc->FillRgn(&LED_ETC3, pDoc->bMovingFlagETC3 ? &BrRed : &BrRed);
		}*/

		/*if (pDoc->bNSC == TRUE) dc->FillRgn(&LED_NS, pDoc->bMovingFlagNS ? &BrRed : &BrRed);
		if (pDoc->bEWC == TRUE) dc->FillRgn(&LED_EW, pDoc->bMovingFlagEW ? &BrRed : &BrRed);
		if (pDoc->bELAC1 == TRUE) dc->FillRgn(&LED_ELAC1, pDoc->bMovingFlagELAC1 ? &BrRed : &BrRed);
		if (pDoc->bELAC2 == TRUE) dc->FillRgn(&LED_ELAC2, pDoc->bMovingFlagELAC2 ? &BrRed : &BrRed);
		if (pDoc->bELAC3 == TRUE) dc->FillRgn(&LED_ELAC3, pDoc->bMovingFlagELAC3 ? &BrRed : &BrRed);
		if (pDoc->bETC2 == TRUE) dc->FillRgn(&LED_ETC2, pDoc->bMovingFlagETC2 ? &BrRed : &BrRed);
		if (pDoc->bCTC == TRUE) dc->FillRgn(&LED_CTC, pDoc->bMovingFlagCTC ? &BrRed : &BrRed);
		if (pDoc->bETC3 == TRUE) dc->FillRgn(&LED_ETC3, pDoc->bMovingFlagETC3 ? &BrRed : &BrRed);*/

		//	delete dc; 
		
		else
		{
			RA_DispMsg(_T("ERROR: Exception null pointer"));
			return FALSE;
		}
	
	ReleaseDC(dc);
//	DeleteObject(pDoc);
	/*DeleteObject(LED_CMTR); DeleteObject(LED_CNSA); DeleteObject(LED_CEWA); DeleteObject(LED_CLA1); DeleteObject(LED_CLA2); DeleteObject(LED_CLA3); DeleteObject(LED_CE2T); DeleteObject(LED_CL3C); DeleteObject(LED_CE3T);
	DeleteObject(LED_NS); DeleteObject(LED_EW); DeleteObject(LED_ELAC1); DeleteObject(LED_ELAC2); DeleteObject(LED_ELAC3); DeleteObject(LED_ETC2); DeleteObject(LED_CTC); DeleteObject(LED_ETC3);
	DeleteObject(LED_BNL); DeleteObject(LED_BEL);
	DeleteObject(LED_XURL1); DeleteObject(LED_XURL2); DeleteObject(LED_XURL3); DeleteObject(LED_XPGL1); DeleteObject(LED_XPGL2); DeleteObject(LED_XPGL3);
	DeleteObject(LED_XN); DeleteObject(LED_XS); DeleteObject(LED_XW); DeleteObject(LED_XE);
	DeleteObject(LED_NHP); DeleteObject(LED_EHP);*/

	return TRUE;
	//}
}

BOOL C6DOFPCMView::Adjust_PM()
{
	//  Move NS Axis First and Adjust it
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	// Enable NS

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
		RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed"));
		GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
		RA_DispMsg(_T("ERROR: Unable to activate Profile Position Mode for NS"));
		GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE;
	}

	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, 600, 1000, 1000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
		RA_DispMsg(_T("ERROR: Setting position profile for NS failed"));
		GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE;
	}


	// Enable EW

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
		RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed"));
		return FALSE;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for EW"));
		RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for EW"));
		 return FALSE;
	}

	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 600, 1000, 1000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for EW failed"));
		RA_DispMsg(_T("ERROR: Setting position profile for EW failed"));
		 return FALSE;
	}

	// Move NS

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, pDoc->m_iCmdCntsNS, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for NS failed"));
		RA_DispMsg(_T("ERROR: Move to position for NS failed"));
		 return FALSE;
	}

	// Move EW

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, pDoc->m_iCmdCntsEW, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for EW failed"));
		RA_DispMsg(_T("ERROR: Move to position for EW failed"));
		return FALSE;
	}

	// Start Updating

	if (!Update_PM_Position())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
		RA_DispMsg(_T("ERROR: Unable to update PM position"));
		return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::PM_Park()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	pDoc->m_iCmdCntsNS = pDoc->iParkPosCntsNS;
	pDoc->m_iCmdCntsEW = pDoc->iParkPosCntsEW;

	if (PM_Ready2Move())
	{
		RA_DispMsg(_T("INFO: PM is moving towards Parking Position"));

		//  Enable PM in PPM

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
			RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed"));
			return FALSE;;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
			RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
			return FALSE;;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, 1800, 1000, 1000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
			RA_DispMsg(_T("ERROR: Setting position profile for NS failed"));
			return FALSE;;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
			RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed"));
			return FALSE;;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unbable to activate Profile Position Mode for EW"));
			RA_DispMsg(_T("ERROR: Unbable to activate Profile Position Mode for EW"));
			return FALSE;;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 1800, 1000, 1000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for EW failed"));
			RA_DispMsg(_T("ERROR: Setting position profile for EW failed"));
			return FALSE;;
		}

		// Park EW

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, pDoc->iParkPosCntsEW, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for EW failed"));
			RA_DispMsg(_T("ERROR: Move to position for EW failed"));
			return FALSE;;
		}

		// Park NS

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, pDoc->iParkPosCntsNS, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for NS failed"));
			RA_DispMsg(_T("ERROR: Move to position for NS failed"));
			return FALSE;;
		}

		pDoc->bHNSL = FALSE; pDoc->bHEWL = FALSE;

		if (!Update_PM_Position())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM parking position"));
			RA_DispMsg(_T("ERROR: Unable to update PM parking position"));
			return FALSE;
		}

		RA_DispMsg(_T("INFO: PM moved to Parking Location"));
		pDoc->RA_LogEvents(_T("INFO: PM moved to Parking Location"));
		pDoc->bParkFlag = TRUE;

		//m_datanaylzerdlg->Display_Motion_Status() m_datanaylzerdlg->UpdateWindow();
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		RA_DispMsg(_T("ERROR: PM not ready to move")); return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::PM_Ready2Move(void)
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!pDoc->bConfigFlag)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to move; while Not Configured")); return FALSE;
	}
	if (pDoc->bBNL)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to move; NS Brake not Released")); return FALSE;
	}
	if (pDoc->bBEL)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to move; EW Brake not Released")); return FALSE;
	}
	if (pDoc->bMC)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to move; Master Controller in Fault Condition")); return FALSE;
	}
	if (pDoc->bNSC)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to move; NS Controller in Fault Condition")); return FALSE;
	}
	if (pDoc->bEWC)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to move; EW Controller in Fault Condition")); return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::RaHomeelac1()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (pDoc->bConfigFlag)
	{
		RA_DispMsg(_T("INFO: Starting Homing LA1"));

		if (pDoc->bHomeELAC1Flag == TRUE)
		{
			if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 controller failed"));
				RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 controller failed"));
				return FALSE;
			}

			if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Position Mode for ELAC1"));
				RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1"));
				return FALSE;
			}
			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt4, 3000, 2000, 2000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC1 failed"));
				RA_DispMsg(_T("ERROR: Setting position profile for ELAC1 failed"));
				return FALSE;
			}
			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt4, 2000, TRUE, TRUE, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC1 failed"));
				RA_DispMsg(_T("ERROR: Move to position for ELAC1 failed"));
				return FALSE;
			}

			if (!Update_LA1_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA1 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA1 position"));
				return FALSE;
			}
		}

		else
		{
			// Move Linear Actuator 1 upward to 36mm hight

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 controller failed"));
				RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 controller failed"));
				return FALSE;
			}

			if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1"));
				RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1"));
				return FALSE;
			}
			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt4, 2000, 3000, 3000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC1 failed"));
				RA_DispMsg(_T("ERROR: Setting position profile for ELAC1 failed"));
				return FALSE;
			}
			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt4, pDoc->m_iCmdCntsELAC1, TRUE, TRUE, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC1 failed"));
				RA_DispMsg(_T("ERROR: Move to position for ELAC1 failed"));
				return FALSE;
			}

			if (!Update_LA1_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA1 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA1 position"));
				return FALSE;
			}

			//ELAC1 AXIS	

			if (!VCM_ActivateHomingMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Homing mode for ELAC1"));
				RA_DispMsg(_T("ERROR: Unable to activate Homing mode for ELAC1"));
				return FALSE;
			}
			if (!VCM_SetHomingParameter(pDoc->hDriveHandleExt4, pDoc->dwHomingAccELAC1, pDoc->dwSpeedSwitchELAC1, pDoc->dwSpeedIndexELAC1, pDoc->lOffsetELAC1, pDoc->wCurrentThresholdELAC1, pDoc->lHomingPositionELAC1, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Homing parameters for ELAC1 failed"));
				RA_DispMsg(_T("ERROR: Setting Homing parameters for ELAC1 failed"));
				return FALSE;
			}

			//HOMING METHODE FOR ELAC1 AXIS - HM_HOME_SWITCH_POSITIVE_SPEED_AND_INDEX

			if (!VCM_FindHome(pDoc->hDriveHandleExt4, HM_HOME_SWITCH_POSITIVE_SPEED, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to find home for ELAC1"));
				RA_DispMsg(_T("ERROR: Unable to find home for ELAC1"));
				return FALSE;
			}

			// Start Updating

			if (!Update_LA1_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA1 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA1 position"));
				return FALSE;
			}

			pDoc->bHomeELAC1Flag = TRUE;
			pDoc->pPositionIsLA1 = pDoc->lHomingPositionELAC1;
			pDoc->RA_LogEvents(_T("INFO: Homing routine for LA1 has been loaded to Master controller"));
			RA_DispMsg(_T("INFO: Homing routine for LA1 has been loaded to Master controller"));

		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: Inputs and Outputs are not configured: Connect All failed"));
		RA_DispMsg(_T("ERROR: Inputs and Outputs are not configured: Connect All failed"));
		return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::RaHomeelac2()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}
	if (pDoc->bConfigFlag)
	{
		if (pDoc->bHomeELAC2Flag == TRUE)
		{
			RA_DispMsg(_T("INFO: Starting Homing LA2"));

			// Move Linear Actuator 2 upward to 36mm hight

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
				RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed"));
				return FALSE;
			}

			if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
				RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
				return FALSE;
			}
			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt5, 4000, 3000, 3000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC2 failed"));
				RA_DispMsg(_T("ERROR: Setting position profile for ELAC2 failed"));
				return FALSE;
			}
			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt5, 1500, TRUE, TRUE, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC2 failed"));
				RA_DispMsg(_T("ERROR: Move to position for ELAC2 failed"));
				return FALSE;
			}

			if (!Update_LA2_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA2 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA2 position"));
				return FALSE;
			}
		}

		else
		{

			RA_DispMsg(_T("INFO: Starting Homing LA2"));

			// Move Linear Actuator 2 upward to 36mm hight

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
				RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed"));
				return FALSE;
			}

			if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
				RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
				return FALSE;
			}
			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt5, 1000, 3000, 3000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC2 failed"));
				RA_DispMsg(_T("ERROR: Setting position profile for ELAC2 failed"));
				return FALSE;
			}
			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt5, pDoc->m_iCmdCntsELAC2, TRUE, TRUE, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC2 failed"));
				RA_DispMsg(_T("ERROR: Move to position for ELAC2 failed"));
				return FALSE;
			}

			if (!Update_LA2_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA2 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA2 position"));
				return FALSE;
			}


			//ELAC2 AXIS	
			if (!VCM_ActivateHomingMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Homing mode for ELAC2"));
				RA_DispMsg(_T("ERROR: Unable to activate Homing mode for ELAC2"));
				return FALSE;
			}
			if (!VCM_SetHomingParameter(pDoc->hDriveHandleExt5, pDoc->dwHomingAccELAC2, pDoc->dwSpeedSwitchELAC2, pDoc->dwSpeedIndexELAC2, pDoc->lOffsetELAC2, pDoc->wCurrentThresholdELAC2, pDoc->lHomingPositionELAC2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Homing parameters for ELAC2 failed"));
				RA_DispMsg(_T("ERROR: Setting Homing parameters for ELAC2 failed"));
				return FALSE;
			}
			//HOMING METHODE FOR ELAC2 AXIS - HM_HOME_SWITCH_POSITIVE_SPEED_AND_INDEX
			if (!VCM_FindHome(pDoc->hDriveHandleExt5, HM_HOME_SWITCH_POSITIVE_SPEED_AND_INDEX, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to find home for ELAC2"));
				RA_DispMsg(_T("ERROR: Unable to find home for ELAC2"));
				return FALSE;
			}

			// Update Position

			if (!Update_LA2_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA2 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA2 position"));
				return FALSE;
			}

			pDoc->bHomeELAC2Flag = TRUE;
			pDoc->pPositionIsLA2 = pDoc->lHomingPositionELAC2;
			pDoc->RA_LogEvents(_T("INFO: Homing routine for LA2 has been loaded to Master controller"));
			RA_DispMsg(_T("INFO: Homing routine for LA2 has been loaded to Master controller"));
		}

	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: Inputs and Outputs are not configured: Connect All failed"));
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::RaHomeelac3()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (pDoc->bConfigFlag)
	{
		RA_DispMsg(_T("INFO: Starting Homing LA3"));
		pDoc->bHELAC2 = FALSE;

		if (pDoc->bHomeELAC3Flag == TRUE)
		{
			pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

			if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode of ELAC3"));
				RA_DispMsg(_T("ERROR: Unable to set Operation Mode of ELAC3"));
				return  FALSE;
			}

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
				RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed"));
				return FALSE;
			}

			if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
				RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
				return FALSE;
			}
			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 2000, 3000, 3000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
				RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed"));
				return FALSE;
			}
			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, 1500, TRUE, TRUE, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
				RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed"));
				return FALSE;
			}

			if (!Update_LA3_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA3 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA3 position"));
				return FALSE;
			}

		}
		// Move Linear Actuator 1 upward to 36mm hight
		else
		{
			if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
				RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed"));
				return FALSE;
			}

			if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
				RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
				return FALSE;
			}
			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 1000, 3000, 3000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
				RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed"));
				return FALSE;
			}
			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, pDoc->m_iCmdCntsELAC3, TRUE, TRUE, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
				RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed"));
				return FALSE;
			}

			//pDoc->bHELAC3 = FALSE;

			if (!Update_LA3_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA3 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA3 position"));
				return FALSE;
			}

			//ELAC3 AXIS

			if (!VCM_ActivateHomingMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Homing mode for ELAC3"));
				RA_DispMsg(_T("ERROR: Unable to activate Homing mode for ELAC3"));
				return FALSE;
			}
			if (!VCM_SetHomingParameter(pDoc->hDriveHandleExt6, pDoc->dwHomingAccELAC3, pDoc->dwSpeedSwitchELAC3, pDoc->dwSpeedIndexELAC3, pDoc->lOffsetELAC3, pDoc->wCurrentThresholdELAC3, pDoc->lHomingPositionELAC3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Homing parameters for ELAC3 failed"));
				RA_DispMsg(_T("ERROR: Setting Homing parameters for ELAC3 failed"));
				return FALSE;
			}
			//HOMING METHODE FOR ELAC3 AXIS - HM_HOME_SWITCH_POSITIVE_SPEED_AND_INDEX
			if (!VCM_FindHome(pDoc->hDriveHandleExt6, HM_HOME_SWITCH_POSITIVE_SPEED_AND_INDEX, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to find home for ELAC3"));
				RA_DispMsg(_T("ERROR: Unable to find home for ELAC3"));
				return FALSE;
			}

			// Update Position

			if (!Update_LA3_Position())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update LA3 position"));
				RA_DispMsg(_T("ERROR: Unable to update LA3 position"));
				return FALSE;
			}

			pDoc->bHomeELAC3Flag = TRUE;
			pDoc->pPositionIsLA3 = pDoc->lHomingPositionELAC3;
			pDoc->RA_LogEvents(_T("INFO: Homing routine for LA3 has been loaded to Master controller"));
			RA_DispMsg(_T("INFO: Homing routine for LA3 has been loaded to Master controller"));


		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: Inputs and Outputs are not configured: Connect All failed")); return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::testETC2(void)
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (pDoc->bConfigFlag)
	{
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ETC2 controller failed"));
			RA_DispMsg(_T("ERROR: Setting enable state of ETC2 controller failed"));
			return FALSE;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ETC2"));
			RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ETC2"));
			return FALSE;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt7, 2000, 3000, 3000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ETC2 failed"));
			RA_DispMsg(_T("ERROR: Setting position profile for ETC2 failed"));
			return FALSE;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt7, 100000, TRUE, TRUE, &(pDoc->dwErrorCode)))	//Testing CW					
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ETC2 failed"));
			RA_DispMsg(_T("ERROR: Move to position for ETC2 failed"));
			return FALSE;
		}

		if (!Update_ETC2_Position())
		{
			pDoc->RA_LogEvents(_T("Unable to update ETC2 position"));
			RA_DispMsg(_T("Unable to update ETC2 position"));
			return FALSE;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt7, 0, TRUE, TRUE, &(pDoc->dwErrorCode)))//Testing CCW						
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ETC2 failed"));
			RA_DispMsg(_T("ERROR: Move to position for ETC2 failed"));
			return FALSE;
		}

		if (!Update_ETC2_Position())
		{
			pDoc->RA_LogEvents(_T("Unable to update ETC2 position"));
			RA_DispMsg(_T("Unable to update ETC2 position"));
			return FALSE;
		}

	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: ETC2 not ready to move; not configured"));
		RA_DispMsg(_T("ERROR: ETC2 not ready to move; not configured"));
		return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::testETC3(void)
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (pDoc->bConfigFlag)
	{
		UpdateData(TRUE);

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ETC3 controller failed"));
			RA_DispMsg(_T("ERROR: Setting enable state of ETC3 controller failed"));
			return FALSE;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ETC3"));
			RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ETC3"));
			return FALSE;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt9, 1000, 2000, 2000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ETC3 failed"));
			RA_DispMsg(_T("ERROR: Setting position profile for ETC3 failed"));
			return FALSE;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt9, -179667, TRUE, TRUE, &(pDoc->dwErrorCode)))	//Testing CW					
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ETC3 failed"));
			RA_DispMsg(_T("ERROR: Move to position for ETC3 failed"));
			return FALSE;
		}

		if (!Update_ETC3_Position())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Update ETC3 Position"));
			RA_DispMsg(_T("ERROR: Unable to Update ETC3 Position"));
			return FALSE;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt9, 179667, TRUE, TRUE, &(pDoc->dwErrorCode)))//Testing CCW						
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ETC3 failed"));
			RA_DispMsg(_T("ERROR: Move to position for ETC3 failed"));
			return FALSE;
		}

		if (!Update_ETC3_Position())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Update ETC3 Position"));
			RA_DispMsg(_T("ERROR: Unable to Update ETC3 Position"));
			return FALSE;
		}

	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: ETC3 not ready to move; not configured"));
		RA_DispMsg(_T("ERROR: ETC3 not ready to move; not configured"));
		return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;

}

BOOL C6DOFPCMView::testCTC(void)
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (pDoc->bConfigFlag)
	{
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of CTC controller failed"));
			RA_DispMsg(_T("ERROR: Setting enable state of CTC controller failed"));
			return FALSE;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for CTC"));
			RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for CTC"));
			return FALSE;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt8, 2000, 3000, 3000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for CTC failed"));
			RA_DispMsg(_T("ERROR: Setting position profile for CTC failed"));
			return FALSE;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt8, -100000, TRUE, TRUE, &(pDoc->dwErrorCode)))	//Testing Closing of Chuck					
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for CTC failed"));
			RA_DispMsg(_T("ERROR: Move to position for CTC failed"));
			return FALSE;
		}

		if (!Update_CTC_Position())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update CTC position"));
			RA_DispMsg(_T("ERROR: Unable to update CTC position"));
			return FALSE;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt8, -10000, TRUE, TRUE, &(pDoc->dwErrorCode)))	//Testing Opening of Chuck					
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for CTC failed"));
			RA_DispMsg(_T("ERROR: Move to position for CTC failed"));
			return FALSE;
		}

		if (!Update_CTC_Position())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update CTC position"));
			RA_DispMsg(_T("ERROR: Unable to update CTC position"));
			return FALSE;
		}

	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: CTC not ready to move; not configured"));
		RA_DispMsg(_T("ERROR: CTC not ready to move; not configured"));
		return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::RaHomectc()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (pDoc->bHomeCTCFlag == TRUE)
	{
		pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

		if (!VCM_SetOperationMode(pDoc->hDriveHandleExt8, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to set CTC operation mode to profile position mode"));
			RA_DispMsg(_T("ERROR: Unable to set CTC operation mode to profile position mode")); return FALSE;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for CTC"));
			RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for CTC")); return FALSE;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of CTC controller failed"));
			RA_DispMsg(_T("ERROR: Setting enable state of CTC controller failed")); return FALSE;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt8, 2000, 1000, 1000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for CTC failed"));
			RA_DispMsg(_T("ERROR: Setting position profile for CTC failed")); return FALSE;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt8, -200000, TRUE, TRUE, &(pDoc->dwErrorCode)))	// Opening of Chuck					
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for CTC failed"));
			RA_DispMsg(_T("ERROR: Move to position for CTC failed")); return FALSE;
		}

		if (!(Update_CTC_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update CTC Current Position"));
			RA_DispMsg(_T("ERROR: Unable to update CTC Current Position")); return FALSE;
		}
	}
	else
	{
		//CTC AXIS	

		if (!VCM_ActivateHomingMode(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Homing mode for CTC"));
			RA_DispMsg(_T("ERROR: Unable to activate Homing mode for CTC"));
			return FALSE;
		}
		if (!VCM_SetHomingParameter(pDoc->hDriveHandleExt8, pDoc->dwHomingAccCTC, pDoc->dwSpeedSwitchCTC, pDoc->dwSpeedIndexCTC, pDoc->lOffsetCTC, pDoc->wCurrentThresholdCTC, pDoc->lHomingPositionCTC, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting Homing parameters for CTC failed"));
			RA_DispMsg(_T("ERROR: Setting Homing parameters for CTC failed"));
			return FALSE;
		}
		//HOMING METHODE FOR CTC AXIS - HM_HOME_SWITCH_POSITIVE_SPEED_AND_INDEX
		if (!VCM_FindHome(pDoc->hDriveHandleExt8, HM_CURRENT_THRESHOLD_POSITIVE_SPEED_AND_INDEX, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to find home for CTC"));
			RA_DispMsg(_T("ERROR: Unable to find home for CTC"));
			return FALSE;
		}

		// Update Position

		if (!Update_CTC_Position())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update CTC position"));
			RA_DispMsg(_T("ERROR: Unable to update CTC position"));
			return FALSE;
		}

		pDoc->bHomeCTCFlag = TRUE;
		pDoc->pPositionIsCTC = pDoc->lOffsetCTC;
		pDoc->RA_LogEvents(_T("INFO: Homing routine for CTC has been loaded to Master controller"));
		RA_DispMsg(_T("INFO: Homing routine for CTC has been loaded to Master controller"));
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Update_PM_Position()
{
	// NS Movement State

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	// NS Movement State

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt2, &(pDoc->bMovingFlagNS), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get NS Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get NS Movement State"));
		 return FALSE;
	}

	// EW Movement State

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt3, &(pDoc->bMovingFlagEW), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get EW Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get EW Movement State"));
		 return FALSE;
	}

	Display_Motion_Status();

	while (pDoc->bMovingFlagNS == 0 || pDoc->bMovingFlagEW == 0)
	{
		// Check Position of NS and EW

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get NS Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get NS Current Position"));
			 return FALSE;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get EW Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get EW Current Position"));
			return FALSE;
		}

		// Display position and movement state of PM

		Display_Motion_Status();
	//	UpdateData(FALSE);
		

		Sleep(100);

		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop NS"));
				RA_DispMsg(_T("ERROR: Unable to quickstop NS"));
				return FALSE;
			}

			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop EW"));
				RA_DispMsg(_T("ERROR: Unable to quickstop EW"));
				return FALSE;
			}
			if (!VCM_GetMovementState(pDoc->hDriveHandleExt2, &(pDoc->bMovingFlagNS), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get NS Movement State"));
				RA_DispMsg(_T("ERROR: Unable to get NS Movement State"));
				return FALSE;
			}

			// EW Movement State

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt3, &(pDoc->bMovingFlagEW), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get EW Movement State"));
				RA_DispMsg(_T("ERROR: Unable to get EW Movement State"));
				return FALSE;
			}


			// Display position and movement state of PM

			Display_Motion_Status();

			break;
		}
		// Monitor PM Limit Switches Status
		// PM Extreme Limit Switxhes Status

		if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt2, &(pDoc->wDigInStateNS), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get NS digital Inputs"));
			RA_DispMsg(_T("ERROR: Unable to get NS digital Inputs"));
			return FALSE;
		}
		if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt3, &(pDoc->wDigInStateEW), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get EW digital Inputs"));
			RA_DispMsg(_T("ERROR: Unable to get EW digital Inputs"));
			return FALSE;
		}

		// Extreme North Limit Switch Status

		if (pDoc->wDigInStateNS & 0x0002)
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quick stop NS as PM reached it's Extreme North Limit"));
				AfxMessageBox("WARNING: PRESS EMERGENCY BUTTON ON THE CONTROL PANNEL TO STOP NS", MB_ICONERROR);
				return FALSE;
			}
			pDoc->bXNL = TRUE;	GetDocument()->UpdateAllViews(NULL);
			pDoc->RA_LogEvents(_T("ERROR: PM reached it's Extreme North Limit "));
			RA_DispMsg(_T("ERROR: PM reached it's Extreme North Limit "));
			return FALSE; break;
		}

		// Extreme South Limit Switch Status

		if (pDoc->wDigInStateNS & 0x0001)
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: ERROR: Unable to quick stop NS as PM reached it's Extreme South Limit"));
				AfxMessageBox("WARNING: PRESS EMERGENCY BUTTON ON THE CONTROL PANNEL TO STOP NS", MB_ICONERROR);
				return FALSE;
			}
			pDoc->bXSL = TRUE; GetDocument()->UpdateAllViews(NULL);
			pDoc->RA_LogEvents(_T("ERROR: PM reached it's Extreme South Limit "));
			RA_DispMsg(_T("ERROR: PM reached it's Extreme South Limit "));
			return FALSE; break;
		}

		// Extreme East Limit Switch Status

		if (pDoc->wDigInStateEW & 0x0002)
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: ERROR: Unable to quick stop EW as PM reached it's Extreme East Limit"));
				AfxMessageBox("WARNING: PRESS EMERGENCY BUTTON ON THE CONTROL PANNEL TO STOP EW", MB_ICONERROR);
				return FALSE;
			}
			pDoc->bXWL = TRUE;	GetDocument()->UpdateAllViews(NULL);
			pDoc->RA_LogEvents(_T("ERROR: PM reached it's Extreme East Limit "));
			RA_DispMsg(_T("ERROR: PM reached it's Extreme East Limit "));
			return FALSE;  break;
		}

		// Extreme West Limit Switch Status

		if (pDoc->wDigInStateEW & 0x0001)
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: ERROR: ERROR: Unable to quick stop EW as PM reached it's Extreme West Limit"));
				AfxMessageBox("WARNING: PRESS EMERGENCY BUTTON ON THE CONTROL PANNEL TO STOP EW", MB_ICONERROR);
				return FALSE;
			}
			pDoc->bXEL = TRUE;  GetDocument()->UpdateAllViews(NULL);
			pDoc->RA_LogEvents(_T("ERROR: PM reached it's Extreme West Limit "));
			RA_DispMsg(_T("ERROR: PM reached it's Extreme West Limit "));
			return FALSE;  break;
		}

		// Check PM controllers status

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt2, &(pDoc->bNSC), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get state of NS controller"));
			RA_DispMsg(_T("ERROR: Unable to get state of NS controller"));
			return FALSE;
		}
		if (!VCM_GetFaultState(pDoc->hDriveHandleExt3, &(pDoc->bEWC), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get state of EW controller"));
			RA_DispMsg(_T("ERROR: Unable to get state of NS controller"));
			return FALSE;
		}

		// Display PM controllers status

		if (pDoc->bNSC == TRUE || pDoc->bEWC == TRUE)
		{
			Display_Motion_Status(); break;
		}

		// Check Movement of NS and EW

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt2, &(pDoc->bMovingFlagNS), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get NS Movement State"));
			RA_DispMsg(_T("ERROR: Unable to get NS Movement State"));
			return FALSE;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt3, &(pDoc->bMovingFlagEW), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get EW Movement State"));
			RA_DispMsg(_T("ERROR: Unable to get EW Movement State"));
			return FALSE;
		}

	}

	// Update Movement and Position Status in View

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt2, &(pDoc->bMovingFlagNS), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get NS Movement State"));
		RA_DispMsg(_T("Unable to get NS Movement State"));
		 return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt3, &(pDoc->bMovingFlagEW), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get EW Movement State"));
		RA_DispMsg(_T("Unable to get EW Movement State"));
		return FALSE;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get NS Current Position"));
		RA_DispMsg(_T("Unable to get NS Current Position"));
		return FALSE;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get EW Current Position"));
		RA_DispMsg(_T("Unable to get EW Current Position"));
		return FALSE;
	}

	// Update PM controllers status in View

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt2, &(pDoc->bNSC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get state of NS controller"));
		RA_DispMsg(_T("ERROR: Unable to get state of NS controller"));
		 return FALSE;
	}
	if (!VCM_GetFaultState(pDoc->hDriveHandleExt3, &(pDoc->bEWC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get state of EW controller"));
		RA_DispMsg(_T("ERROR: Unable to get state of NS controller"));
		 return FALSE;
	}

	Display_Motion_Status();
	DeleteObject(pDoc);
	return TRUE;

}

BOOL C6DOFPCMView::Update_LA1_Position()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt4, &(pDoc->bMovingFlagELAC1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA1 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get LA1 Movement State"));
		return FALSE;
	}

	Display_Motion_Status();

	while (pDoc->bMovingFlagELAC1 == 0)
	{
		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt4, &(pDoc->pPositionIsLA1), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA1 Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get LA1 Current Position"));
			return FALSE;
		}

		if (!LA_LimitSwitches_Status())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to find LA Limit Switches Status"));
			RA_DispMsg(_T("ERROR: Unable to find LA Limit Switches Status"));
			return FALSE;
		}

		// Display position of LA1

		Display_Motion_Status();
		

		Sleep(100);

		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quick stop LA1"));
				RA_DispMsg(_T("ERROR: Unable to quickstop LA1"));
				GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt4, &(pDoc->bMovingFlagELAC1), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get LA1 Movement State"));
				RA_DispMsg(_T("ERROR: Unable to get LA1 Movement State"));
				return FALSE;
			}

			if (!LA_LimitSwitches_Status())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to find LA Limit Switches Status"));
				RA_DispMsg(_T("ERROR: Unable to find LA Limit Switches Status"));
				return FALSE;
			}

			// Display position of LA1

			Display_Motion_Status();

			break;
		}

		/*	// Check the status of linear actuator 1 limit switch

		if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt4, &(pDoc->wDigInStateELAC1), &(pDoc->dwErrorCode)))
		{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ELAC1 digital Inputs"));
		RA_DispMsg(_T("ERROR: Unable to get ELAC1 digital Inputs"));
		GetDocument()->UpdateAllViews(NULL);
		UpdateWindow(); return FALSE;
		}

		if (pDoc->wDigInStateELAC1 & 0x0004)
		{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
		{
		pDoc->RA_LogEvents(_T("ERROR: Unable to quick stop ELAC1"));
		AfxMessageBox("WARNING: PRESS EMERGENCY BUTTON ON THE CONTROL PANNEL TO STOP ELAC1", MB_ICONERROR);
		return FALSE; break;
		}
		pDoc->bHELAC1 = TRUE;
		pDoc->RA_LogEvents(_T("LA1 reached it's Extreme Limit "));
		RA_DispMsg(_T("LA1 reached it's Extreme Limit "));
		GetDocument()->UpdateAllViews(NULL);
		UpdateWindow(); return FALSE; break;
		}
		*/
		// Check Fault State of Controllers

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt4, &(pDoc->bELAC1), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC1 controller"));
			RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC1 controller"));
			GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE;
		}

		if (pDoc->bELAC1 == TRUE)
		{
			Display_Motion_Status();
			 break;
		}
		// Check the Movement State of LA1

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt4, &(pDoc->bMovingFlagELAC1), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA1 Movement State"));
			RA_DispMsg(_T("Unable to get LA1 Movement State"));
			return FALSE;
		}
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt4, &(pDoc->bMovingFlagELAC1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA1 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get LA1 Movement State"));
		return FALSE;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt4, &(pDoc->pPositionIsLA1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA1 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get LA1 Current Position"));
		return FALSE;
	}

	if (!LA_LimitSwitches_Status())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		return FALSE;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt4, &(pDoc->bELAC1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC1 controller"));
		RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC1 controller"));
		return FALSE;
	}
	Display_Motion_Status();
	//m_datanaylzerdlg->Store_Positions();
	DeleteObject(pDoc);

	return TRUE;
}

BOOL C6DOFPCMView::Update_LA2_Position()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt5, &(pDoc->bMovingFlagELAC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA2 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get LA2 Movement State"));
		return FALSE;
	}

	Display_Motion_Status();

	while (pDoc->bMovingFlagELAC2 == 0)
	{
		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt5, &(pDoc->pPositionIsLA2), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA2 Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get LA2 Current Position"));
			 return FALSE;
		}

		if (!LA_LimitSwitches_Status())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
			RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
			return FALSE;
		}

		// Display position of LA2

		Display_Motion_Status();
		

		Sleep(100);


		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop LA2"));
				RA_DispMsg(_T("ERROR: Unable to quickstop LA2"));
				return FALSE;
			}
			
			if (!VCM_GetMovementState(pDoc->hDriveHandleExt5, &(pDoc->bMovingFlagELAC2), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get LA2 Movement State"));
				RA_DispMsg(_T("ERROR: Unable to get LA2 Movement State"));
				return FALSE;
			}

			if (!LA_LimitSwitches_Status())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
				RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
				return FALSE;
			}

			// Display position of LA2

			Display_Motion_Status();
			break;
		}

		/*// Check the status of linear actuator 2 limit switch

		if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt5, &(pDoc->wDigInStateELAC2), &(pDoc->dwErrorCode)))
		{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ELAC2 digital Inputs"));
		RA_DispMsg(_T("ERROR: Unable to get ELAC2 digital Inputs"));
		GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE;
		}

		if (pDoc->wDigInStateELAC2 & 0x0004)
		{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
		{
		pDoc->RA_LogEvents(_T("ERROR: Unable to quick stop ELAC2"));
		AfxMessageBox("WARNING: PRESS EMERGENCY BUTTON ON THE CONTROL PANNEL TO STOP ELAC2", MB_ICONERROR);
		return FALSE;
		}
		pDoc->bHELAC2 = TRUE;
		pDoc->RA_LogEvents(_T("ERROR: LA2 reached it's Extreme Limit "));
		RA_DispMsg(_T("ERROR: LA2 reached it's Extreme Limit "));
		GetDocument()->UpdateAllViews(NULL); UpdateWindow();  return FALSE; break;
		}
		*/
		if (!VCM_GetFaultState(pDoc->hDriveHandleExt5, &(pDoc->bELAC2), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC2 controller"));
			RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC2 controller"));
			return FALSE;
		}

		if (pDoc->bELAC2 == TRUE)
		{
			Display_Motion_Status(); break;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt5, &(pDoc->bMovingFlagELAC2), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA2 Movement State"));
			RA_DispMsg(_T("Unable to get LA2 Movement State"));
			 return FALSE;
		}
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt5, &(pDoc->pPositionIsLA2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA2 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get LA2 Current Position"));
		 return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt5, &(pDoc->bMovingFlagELAC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get LA2 Movement State"));
		RA_DispMsg(_T("Unable to get LA2 Movement State"));
		return FALSE;
	}

	if (!LA_LimitSwitches_Status())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		return FALSE;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt5, &(pDoc->bELAC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC2 controller"));
		RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC2 controller"));
		return FALSE;
	}

	Display_Motion_Status();
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Update_LA3_Position()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
		RA_DispMsg(_T("Unable to get LA3 Movement State"));
		return FALSE;
	}

	Display_Motion_Status();

	while (pDoc->bMovingFlagELAC3 == 0)
	{
		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
			 return FALSE;
		}

		if (!LA_LimitSwitches_Status())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
			RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
			return FALSE;
		}

		// Display position of LA3

		Display_Motion_Status();
		

		Sleep(100);


		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop LA3"));
				RA_DispMsg(_T("ERROR: Unable to quickstop LA3"));
				return FALSE;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
				RA_DispMsg(_T("Unable to get LA3 Movement State"));
				return FALSE;
			}

			if (!LA_LimitSwitches_Status())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
				RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
				return FALSE;
			}

			// Display position of LA3

			Display_Motion_Status();

			break;
		}

		// Check the status of linear actuator 2 limit switch
		/*
		if (!VCM_GetAllDigitalInputs(pDoc->hDriveHandleExt6, &(pDoc->wDigInStateELAC3), &(pDoc->dwErrorCode)))
		{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ELAC3 digital Inputs"));
		RA_DispMsg(_T("ERROR: Unable to get ELAC3 digital Inputs"));
		GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE;
		}

		if (pDoc->wDigInStateELAC3 & 0x0004)
		{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
		pDoc->RA_LogEvents(_T("ERROR: Unable to quick stop ELAC3"));
		AfxMessageBox("WARNING: PRESS EMERGENCY BUTTON ON THE CONTROL PANNEL TO STOP ELAC3", MB_ICONERROR);
		return FALSE; break;
		}
		pDoc->bHELAC3 = TRUE;
		pDoc->RA_LogEvents(_T("ERROR: LA3 reached it's Extreme Limit "));
		RA_DispMsg(_T("ERROR: LA3 reached it's Extreme Limit "));
		GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE; break;
		}
		*/
		if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			return FALSE;
		}

		if (pDoc->bELAC3 == TRUE)
		{
			Display_Motion_Status(); break;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			RA_DispMsg(_T("Unable to get LA3 Movement State"));
			 return FALSE;
		}
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
		RA_DispMsg(_T("Unable to get LA3 Movement State"));
		return FALSE;
	}


	if (!LA_LimitSwitches_Status())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		return FALSE;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
		RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
		return FALSE;
	}

	Display_Motion_Status();
	
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Update_ETC2_Position()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt7, &(pDoc->bMovingFlagETC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get ETC2 Movement State"));
		return FALSE;
	}

	Display_Motion_Status();

	/*if (!VCM_GetPositionIs(pDoc->hDriveHandleExt7, &(pDoc->pPositionIsETC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get ETC2 Current Position"));
		return FALSE;
	}

	
	pDoc->startposetc2 = abs(pDoc->pPositionIsETC2);*/

	while (pDoc->bMovingFlagETC2 == 0)
	{
		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt7, &(pDoc->pPositionIsETC2), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get ETC2 Current Position"));
			return FALSE;
		}

		// Display position of ETC2

		pDoc->notetc2 = (abs(pDoc->pPositionIsETC2))-(pDoc->startposetc2);
		pDoc->notetc2 = pDoc->notetc2/1102500;

		Display_Motion_Status();
		
		if (pDoc->notetc2 > 3.00)
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
				AfxMessageBox((_T("ERROR: Unable to Quick Stop ETC2"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
			}
		}

		Sleep(100);


		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ETC2"));
				RA_DispMsg(_T("ERROR: Unable to quickstop ETC2"));
				 return FALSE;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt7, &(pDoc->bMovingFlagETC2), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Movement State"));
				RA_DispMsg(_T("ERROR: Unable to get ETC2 Movement State"));
				return FALSE;
			}

			Display_Motion_Status();
			break;
		}

		if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt7, &pDoc->pVelocityIsAveragedETC2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
			RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return FALSE;
		}

		if (abs(pDoc->pVelocityIsAveragedETC2) < 150)
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
				AfxMessageBox((_T("ERROR: Unable to Quick Stop ETC2"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
			}

		}

		// Clear fault of ETC2

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt7, &(pDoc->bETC2), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC2 controller"));
			RA_DispMsg(_T("ERROR: Unable to get fault state of ETC2 controller"));
			return FALSE;
		}

		if (pDoc->bETC2 == TRUE)
		{
			Display_Motion_Status();
			break;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt7, &(pDoc->bMovingFlagETC2), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Movement State"));
			RA_DispMsg(_T("ERROR: Unable to get ETC2 Movement State"));
			return FALSE;
		}
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt7, &(pDoc->pPositionIsETC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get ETC2 Current Position"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt7, &(pDoc->bMovingFlagETC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get ETC2 Movement State"));
		return FALSE;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt7, &(pDoc->bETC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC2 controller"));
		RA_DispMsg(_T("ERROR: Unable to get fault state of ETC2 controller"));
		return FALSE;
	}

	Display_Motion_Status();
	
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Update_ETC3_Position()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
		return FALSE;
	}

/*
if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
		return FALSE;
	}
	
	pDoc->startposetc3 = abs(pDoc->pPositionIsETC3);*/

	Display_Motion_Status();

	while (pDoc->bMovingFlagETC3 == 0)
	{
		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
			return FALSE;
		}

		// Display position of ETC3
		pDoc->notetc3 = (abs(pDoc->pPositionIsETC3))-(pDoc->startposetc3);
		pDoc->notetc3 = pDoc->notetc3/179667;
		
		Display_Motion_Status();
		

		Sleep(100);

		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ETC3"));
				RA_DispMsg(_T("ERROR: Unable to quickstop ETC3"));
				 return FALSE;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
				RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
				return FALSE;
			}

			Display_Motion_Status();
			break;
		}


		if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
			RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
			return FALSE;
		}

		if (pDoc->bETC3 == TRUE)
		{
			Display_Motion_Status();
			break;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return FALSE;
		}
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
		return FALSE;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
		RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
		return FALSE;
	}

	Display_Motion_Status();
	
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Update_CTC_Position()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt8, &(pDoc->bMovingFlagCTC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get CTC Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get CTC Movement State"));
		return FALSE;
	}

	Display_Motion_Status();

	while (pDoc->bMovingFlagCTC == 0)
	{
		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt8, &(pDoc->pPositionIsCTC), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get CTC Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get CTC Current Position"));
			return FALSE;
		}

		// Display position of CTC

		Display_Motion_Status();
		

		Sleep(100);

		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop CTC"));
				RA_DispMsg(_T("ERROR: Unable to quickstop CTC"));
				return FALSE;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt8, &(pDoc->bMovingFlagCTC), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get CTC Movement State"));
				RA_DispMsg(_T("ERROR: Unable to get CTC Movement State"));
				return FALSE;
			}

			// Display position of CTC

			Display_Motion_Status();
			break;
		}


		if (!VCM_GetFaultState(pDoc->hDriveHandleExt8, &(pDoc->bCTC), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of CTC controller"));
			RA_DispMsg(_T("ERROR: Unable to get fault state of CTC controller"));
			return FALSE;
		}

		if (pDoc->bCTC == TRUE)
		{
			Display_Motion_Status(); break;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt8, &(pDoc->bMovingFlagCTC), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get CTC Movement State"));
			RA_DispMsg(_T("ERROR: Unable to get CTC Movement State"));
			return FALSE;
		}
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt8, &(pDoc->pPositionIsCTC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get CTC Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get CTC Current Position"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt8, &(pDoc->bMovingFlagCTC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get CTC Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get CTC Movement State"));
		return FALSE;
	}


	if (!VCM_GetFaultState(pDoc->hDriveHandleExt8, &(pDoc->bCTC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of CTC controller"));
		RA_DispMsg(_T("ERROR: Unable to get fault state of CTC controller"));
		return FALSE;
	}

	Display_Motion_Status();
	

	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Update_All_Positions()
{
	Sleep(300);

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get NS Current Position"));
		RA_DispMsg(_T("Unable to get NS Current Position"));
		return FALSE;
	}

	if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt2, &pDoc->pVelocityIsAveragedNS, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
		RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return FALSE;
	}

	if (abs(pDoc->pVelocityIsAveragedNS) < 100)
	{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
			AfxMessageBox((_T("ERROR: Unable to Quick Stop NS"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
		}

	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get EW Current Position"));
		RA_DispMsg(_T("Unable to get EW Current Position"));
		return FALSE;
	}

	if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt3, &pDoc->pVelocityIsAveragedEW, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
		RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return FALSE;
	}

	if (abs(pDoc->pVelocityIsAveragedEW) < 100)
	{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
			AfxMessageBox((_T("ERROR: Unable to Quick Stop EW"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
		}

	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt4, &(pDoc->pPositionIsLA1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA1 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get LA1 Current Position"));
		return FALSE;
	}

	if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt4, &pDoc->pVelocityIsAveragedLA1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
		RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return FALSE;
	}

	if (abs(pDoc->pVelocityIsAveragedLA1) < 100)
	{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
			AfxMessageBox((_T("ERROR: Unable to Quick Stop LA1"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
		}

	}
	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt5, &(pDoc->pPositionIsLA2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA2 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get LA2 Current Position"));
		return FALSE;
	}

	if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt5, &pDoc->pVelocityIsAveragedLA2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
		RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return FALSE;
	}

	if (abs(pDoc->pVelocityIsAveragedLA2) < 100)
	{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
			AfxMessageBox((_T("ERROR: Unable to Quick Stop LA2"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
		}

	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
		return FALSE;
	}

	if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt6, &pDoc->pVelocityIsAveragedLA3, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
		RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return FALSE;
	}

	if (abs(pDoc->pVelocityIsAveragedLA3) < 200)
	{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
			AfxMessageBox((_T("ERROR: Unable to Quick Stop LA3"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
		}

	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt7, &(pDoc->pPositionIsETC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get ETC2 Current Position"));
		return FALSE;
	}

	if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt7, &pDoc->pVelocityIsAveragedETC2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
		RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return FALSE;
	}

	if (abs(pDoc->pVelocityIsAveragedETC2) < 150)
	{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
			AfxMessageBox((_T("ERROR: Unable to Quick Stop ETC2"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
		}

	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt8, &(pDoc->pPositionIsCTC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get CTC Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get CTC Current Position"));
		return FALSE;
	}

	if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt8, &pDoc->pVelocityIsAveragedCTC, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
		RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return FALSE;
	}

	if (abs(pDoc->pVelocityIsAveragedCTC) < 100)
	{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
			AfxMessageBox((_T("ERROR: Unable to Quick Stop CTC"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return FALSE;
		}

	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
		RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
		return FALSE;
	}

	if (!LA_LimitSwitches_Status())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		return FALSE;
	}	
	
	if (GetAsyncKeyState(VK_END))
	{
		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop NS"));
			RA_DispMsg(_T("ERROR: Unable to quickstop NS"));
			return FALSE;
		}

		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop EW"));
			RA_DispMsg(_T("ERROR: Unable to quickstop EW"));
			return FALSE;
		}

		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ELAC1"));
			RA_DispMsg(_T("ERROR: Unable to quickstop ELAC1"));
			return FALSE;
		}

		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ELAC2"));
			RA_DispMsg(_T("ERROR: Unable to quickstop ELAC2"));
			return FALSE;
		}

		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ELAC3"));
			RA_DispMsg(_T("ERROR: Unable to quickstop ELAC3"));
			return FALSE;
		}

		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ETC2"));
			RA_DispMsg(_T("ERROR: Unable to quickstop ETC2"));
			return FALSE;
		}

		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop CTC2"));
			RA_DispMsg(_T("ERROR: Unable to quickstop CTC2"));
			return FALSE;
		}

		if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ETC3"));
			RA_DispMsg(_T("ERROR: Unable to quickstop ETC3"));
			return FALSE;
		}
		return FALSE;
	}

	Display_Motion_Status();
	
	Sleep(100);
	DeleteObject(pDoc);
	return TRUE;
}



void C6DOFPCMView::OnBnClickedDisconnect2()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return;
	}
	if (pDoc->m_login_first == 1)
	{
		if (!RA01_Disconnectall())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Disconnect Controllers"));

		}
		else
			pDoc->RA_LogEvents(_T("INFO: Controllers are successfully disconnected"));
			RA_DispMsg(_T("INFO: Controllers are successfully disconnected"));
		pDoc->PDisconnect++;
	}
	else
		AfxMessageBox("INFO: Only Operator can peform this operation", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL);

	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedHome()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}

	if (pDoc->m_login_first == 1)
	{
		if (pDoc->m_usertype_received == "Operator")
		{
			if (PM_Ready2Home())//Check for Communication and Brake status
			{
				if (!RA01_Home())
				{
					pDoc->RA_LogEvents(_T("ERROR: Homing not successful"));
					RA_DispMsg("ERROR: Homing not Successful");
				}

				else
					pDoc->RA_LogEvents(_T("INFO: Homing Successful, RA01 ready to perform operation"));
				RA_DispMsg(_T("INFO: Homing Successful, RA01 ready to perform operation"));
			}
			else
			{
				pDoc->RA_LogEvents(_T("ERROR: Configure Your Controller's First"));
				RA_DispMsg(_T("ERROR: Configure Your Controller's First"));
			}		return;
		}
		else
			AfxMessageBox("INFO: Only Operator can peform this operation", MB_TOPMOST);
	}
	else
		AfxMessageBox("INFO: Please Login your account first", (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);

	DeleteObject(pDoc);
}




//BOOL C6DOFPCMView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CBrush brNew(RGB(108, 140, 192));                      // To edit the background color give desired color code here
//	CBrush*poldBrush = (CBrush*)pDC->SelectObject(&brNew);
//	CRect rc;
//	pDC->GetClipBox(rc);
//	pDC->PatBlt(0, 0, rc.Width(), rc.Height(), PATCOPY);
//	pDC->SelectObject(poldBrush);
//
//	// Display P Logo
//	{
//
//		CBitmap m_bitmap;
//		BITMAP bmp;
//		CDC dc;
//
//		m_bitmap.LoadBitmap(IDB_P_MONOGRAM);
//		m_bitmap.GetBitmap(&bmp);
//
//		pDC = this->GetDC();
//		dc.CreateCompatibleDC(pDC);
//		dc.SelectObject(m_bitmap);
//		//pDC->BitBlt(1115, 0, bmp.bmWidth, bmp.bmHeight, &dc, 0, 0, SRCCOPY);
//		pDC->StretchBlt(1700, 0, 220, 200, &dc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
//
//	}
//	// Display I Logo
//	{
//
//		CBitmap m_bitmap;
//		BITMAP bmp;
//		CDC dc;
//
//		m_bitmap.LoadBitmap(IDB_I_MONOGRAM);
//		m_bitmap.GetBitmap(&bmp);
//
//		pDC = this->GetDC();
//		dc.CreateCompatibleDC(pDC);
//		dc.SelectObject(m_bitmap);
//		pDC->StretchBlt(2, 0, 220, 200, &dc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
//
//	}
//
//	
//	return TRUE;
//}


void C6DOFPCMView::OnPaint()
{

	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CFormView::OnPaint() for painting messages


	CRect RECT; CWnd* pWnd;

	{
		this->GetClientRect(&RECT);
		CDC MemDC;
		CBitmap tiledImage;
		MemDC.CreateCompatibleDC(&dc);
		tiledImage.LoadBitmapA(IDB_PrgBkgd);
		MemDC.SelectObject(&tiledImage);
		dc.BitBlt(0, 0, RECT.Width(), RECT.Height(), &MemDC, 0, 0, SRCCOPY);
		MemDC.DeleteDC();
		DeleteObject(tiledImage);
	
	}
		
	m_connect.LoadStdImage(IDB_StartComm, _T("PNG"));
//	m_connect.SetToolTipText(_T("Connect"), TRUE);
	m_disconnect.LoadStdImage(IDB_CloseComm, _T("PNG"));
//	m_disconnect.SetToolTipText(_T("Disconnect"), TRUE);
	m_home.LoadStdImage(IDB_Home, _T("PNG"));
//	m_home.SetToolTipText(_T("Home"), TRUE);
	m_park.LoadStdImage(IDB_Park, _T("PNG"));
//	m_park.SetToolTipText(_T("Park"), TRUE);
	m_BNLHold.LoadStdImage(IDB_BrakeHold, _T("PNG"));
//	m_BNLHold.SetToolTipText(_T("Hold NS Brakes"), TRUE);
	m_BNLRel.LoadStdImage(IDB_BrakeRelease, _T("PNG"));
//	m_BNLRel.SetToolTipText(_T("Release NS Brakes"), TRUE);
	m_BELhold.LoadStdImage(IDB_BrakeHold, _T("PNG"));
//	m_BELhold.SetToolTipText(_T("Hold EW Brakes"), TRUE);
	m_BELRel.LoadStdImage(IDB_BrakeRelease, _T("PNG"));
//	m_BELRel.SetToolTipText(_T("Release EW Brakes"), TRUE);
	m_resetmaster.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetmaster.SetToolTipText(_T("Reset Master Device/Clear Fault"), TRUE);
	m_resetNS.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetNS.SetToolTipText(_T("Reset NS/Clear Fault"), TRUE);
	m_resetEW.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetEW.SetToolTipText(_T("Reset EW/Clear Fault"), TRUE);
	m_resetElac1.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetElac1.SetToolTipText(_T("Reset ELAC1/Clear Fault"), TRUE);
	m_resetELAC2.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetELAC2.SetToolTipText(_T("Reset ELAC2/Clear Fault"), TRUE);
	m_resetElac3.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetElac3.SetToolTipText(_T("Reset ELAC3/Clear Fault"), TRUE);
	m_resetETC2.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetETC2.SetToolTipText(_T("Reset ETC2/Clear Fault"), TRUE);
	m_resetCTC.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetCTC.SetToolTipText(_T("Reset CTC/Clear Fault"), TRUE);
	m_resetETC3.LoadStdImage(IDB_Reset, _T("PNG"));
//	m_resetETC3.SetToolTipText(_T("Reset ETC3/Clear Fault"), TRUE);
	m_LoadSchedule.LoadStdImage(IDB_LoadSchedule, _T("PNG"));
//	m_LoadSchedule.SetToolTipText(_T("Load the Schedule"), TRUE);
	m_close.LoadStdImage(IDB_Close, _T("PNG"));
//	m_close.SetToolTipText(_T("Close the Device"), TRUE);
	m_signout.LoadStdImage(IDB_signout, _T("PNG"));
//	m_signout.SetToolTipText(_T("Sign Out your Account"), TRUE);
	


	&dc.MoveTo(1763, 405); // XN->XS vertical right line
	dc.LineTo(1763, 600);

	&dc.MoveTo(1766, 405); // XN->XS vertical right line
	dc.LineTo(1766, 600);

	&dc.MoveTo(1690, 475); // XE->XW horizontal lower line
	dc.LineTo(1855, 475);

	&dc.MoveTo(1690, 472); // XE->XW horizontal lower line
	dc.LineTo(1855, 472);

	&dc.MoveTo(1685, 680); //XPGL1-> XURL1
	dc.LineTo(1685, 860);

	&dc.MoveTo(1765, 680); //XPGL2-> XURL2
	dc.LineTo(1765, 860);

	&dc.MoveTo(1841, 680); //XPGL3-> XURL3
	dc.LineTo(1841, 860);

	DeleteDC(dc);

			
}

BOOL C6DOFPCMView::RA01_Home()
{
	// TODO: Add your command handler code here

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		pDoc->errorcode = 1000;
		pDoc->errormsg = _T("E") + pDoc->errorcode; pDoc->errormsg += _T(": Unable to get document pointer");
		pDoc->RA_LogEvents(pDoc->errormsg);
		RA_DispMsg(pDoc->errormsg);
		return FALSE;
	}

	//NS & EW Homing

	if (AfxMessageBox("QUERY : If you want to Home PM, Press OK", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		// Move NS and EW to adjust for homing

		if (!Adjust_PM())
		{
			
			pDoc->RA_LogEvents(_T("ERROR: Unable to Adjust PM"));
			RA_DispMsg(_T("ERROR: Unable to Adjust PM"));
			return FALSE;
		}

		// Start Homing

		if (!Home_NS_and_EW())
		{
			pDoc->RA_LogEvents(_T("ERROR: NS & EW Axis Homing not successful"));
			RA_DispMsg(_T("ERROR: NS & EW Axis Homing not successful"));
			return FALSE;
		}

		pDoc->bHomeFlag = TRUE;

		RA_DispMsg(_T("INFO: PM Homing routine has been loaded to Master controller"));
		pDoc->RA_LogEvents(_T("INFO: PM Homing routine has been loaded to Master controller"));

		pDoc->pPositionIsNS = pDoc->lHomingPositionNS;
		pDoc->pPositionIsEW = pDoc->lHomingPositionEW;

		Display_Motion_Status();
	}

	//Wait till homing is attained for NS & EW then move back to parking

	if (pDoc->bHomeFlag == TRUE)
	{
		if (AfxMessageBox("INFO: NS & EW Homing Complete. Press OK Button to Park PM", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
		{
			if (!PM_Park())
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to park PM"));
				RA_DispMsg(_T("ERROR: Unable to park PM"));
				return FALSE;
			}
		}
		else
		{
			pDoc->RA_LogEvents(_T("INFO: PM is not at its parking position"));
			RA_DispMsg(_T("INFO: PM is not at its parking position"));

		}
	}

	//Homing for LAs

	if (!Home_LAs())
	{
		pDoc->RA_LogEvents(_T("ERROR: Linear Actuators Homing not successful"));
		RA_DispMsg(_T("ERROR: Linear Actuator's Homing not successful"));
		return FALSE;
	}

	// Testing EET's

	if (!test_EET())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to test End-Effector Tools"));
		RA_DispMsg(_T("ERROR: Unable to test End-Effector Tools"));
		return FALSE;
	}

	RA_DispMsg(_T("INFO: All EET's working/functionality have been tested"));

	if (AfxMessageBox("INFO: CTC tested . CTC will first attain its home and later move to safe position", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!RaHomectc())
		{
			pDoc->RA_LogEvents(_T("ERROR: CTC Homing not successful"));
			RA_DispMsg(_T("ERROR: CTC Homing not successful"));
			return FALSE;
		}

		pDoc->targetposition = -5600000;

		if (!Movectc2tosafelimit())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to move CTC to safe limit"));
			RA_DispMsg(_T("ERROR: Unable to move CTC to safe limit"));
			return FALSE;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("INFO: CTC is not at its Home position"));
		RA_DispMsg(_T("INFO: CTC is not at its Home position"));
	}


	if (AfxMessageBox("INFO: Press OK to test Synchronize Motion", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!test_synchronize_motion())
		{
			pDoc->RA_LogEvents(_T("ERROR: Synchronize motion testing not successful"));
			RA_DispMsg(_T("ERROR: Synchronize motion testing not successful"));
			GetDocument()->UpdateAllViews(NULL); UpdateWindow(); return FALSE;
		}
	}

	pDoc->bHomeandTestFlag = TRUE;
	RA_DispMsg(_T("INFO: RA01 Homing and Testing Successfull"));

	return TRUE;
	DeleteObject(pDoc);
}

BOOL C6DOFPCMView::Home_NS_and_EW()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	// Enable Homing Mode	

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
		RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed"));
		 return FALSE;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
		RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed"));
		return FALSE;
	}

	if (!VCM_ActivateHomingMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Homing mode for NS"));
		RA_DispMsg(_T("ERROR: Unable to activate Homing mode for NS"));
		return FALSE;
	}

	if (!VCM_ActivateHomingMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Homing mode for EW"));
		RA_DispMsg(_T("ERROR: Unable to activate Homing mode for EW"));
		 return FALSE;
	}

	if (!VCM_SetHomingParameter(pDoc->hDriveHandleExt3, pDoc->dwHomingAccEW, pDoc->dwSpeedSwitchEW, pDoc->dwSpeedIndexEW, pDoc->lOffsetEW, pDoc->wCurrentThresholdEw, pDoc->lHomingPositionEW, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting Homing parameters for EW failed"));
		RA_DispMsg(_T("ERROR: Setting Homing parameters for EW failed"));
		 return FALSE;
	}

	//HOMING METHODE FOR EW AXIS - HM_HOME_SWITCH_NEGATIVE_SPEED_AND_INDEX

	RA_DispMsg(_T("INFO: Starting Homing EW Axis"));

	if (!VCM_SetHomingParameter(pDoc->hDriveHandleExt2, pDoc->dwHomingAccNS, pDoc->dwSpeedSwitchNS, pDoc->dwSpeedIndexNS, pDoc->lOffsetNS, pDoc->wCurrentThresholdNS, pDoc->lHomingPositionNS, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting Homing parameters for NS failed"));
		RA_DispMsg(_T("ERROR: Setting Homing parameters for NS failed"));
		 return FALSE;
	}

	//HOMING METHODE FOR NS AXIS - HM_HOME_SWITCH_POSITIVE_SPEED_AND_INDEX

	RA_DispMsg(_T("INFO: Starting Homing NS"));

	if (!VCM_FindHome(pDoc->hDriveHandleExt2, HM_HOME_SWITCH_POSITIVE_SPEED_AND_INDEX, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to find home for NS"));
		RA_DispMsg(_T("ERROR: Unable to find home for NS"));
		return FALSE;
	}

	if (!VCM_FindHome(pDoc->hDriveHandleExt3, HM_HOME_SWITCH_NEGATIVE_SPEED_AND_INDEX, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to find home for EW"));
		RA_DispMsg(_T("ERROR: Unable to find home for EW"));
		 return FALSE;
	}

	// Start Updating

	if (!Update_PM_Position())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
		RA_DispMsg(_T("ERROR: Unable to update PM position"));
		return FALSE;
	}

	pDoc->bHNSL = TRUE;
	pDoc->bHEWL = TRUE;
	
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Home_LAs()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (AfxMessageBox("INFO: NS & EW Homing Complete. PM Parked. Press PCLM1 Button to home ELAC1", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!RaHomeelac1())
		{
			pDoc->RA_LogEvents(_T("ERROR: ELAC1 Homing not successful"));
			RA_DispMsg(_T("ERROR: ELAC1 Homing not successful"));
			return FALSE;
		}
	}

	if (AfxMessageBox("INFO: ELAC1 homing attained. Press PCLM2 Button to home ELAC2", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!RaHomeelac2())
		{
			pDoc->RA_LogEvents(_T("ERROR: ELAC2 Homing not successful"));
			RA_DispMsg(_T("ERROR: ELAC2 Homing not successful"));
			return FALSE;
		}
	}
	if (AfxMessageBox("INFO: ELAC2 homing attained. Press PCLM3 Button to home ELAC3", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!RaHomeelac3())
		{
			pDoc->RA_LogEvents(_T("ERROR: ELAC3 Homing not successful"));
			RA_DispMsg(_T("ERROR: ELAC3 Homing not successful"));
			return FALSE;
		}
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::test_EET()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (AfxMessageBox("INFO: Press PCLM2 & PETM2 Buttons to test ETC2", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!testETC2())
		{
			pDoc->RA_LogEvents(_T("ERROR: ETC2 testing not successful"));
			RA_DispMsg(_T("ERROR: ETC2 testing not successful"));
			return FALSE;
		}
	}

	RA_DispMsg(_T("INFO: ETC2 have been tested"));

	if (AfxMessageBox("INFO: ETC2 tested. Press PCLM3 & PETM3 Buttons to test ETC3", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!testETC3())
		{
			pDoc->RA_LogEvents(_T("ERROR: ETC3 testing not successful"));
			RA_DispMsg(_T("ERROR: ETC3 testing not successful"));
			return FALSE;
		}
	}

	RA_DispMsg(_T("INFO: ETC3 have been tested"));

	if (AfxMessageBox("INFO: ETC3 tested. Press PCLM3 & PCCM Buttons to test CTC", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!testCTC())
		{
			pDoc->RA_LogEvents(_T("ERROR: CTC testing not successful"));
			RA_DispMsg(_T("ERROR: CTC testing not successful"));
			return FALSE;
		}
	}

	RA_DispMsg(_T("INFO: CTC have been tested"));
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::test_synchronize_motion()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (pDoc->bConfigFlag)
	{

		DWORD dwHomingAccELAC3 = 5000, dwSpeedSwitchELAC3 = 600, dwSpeedIndexELAC3 = 10;
		WORD wCurrentThresholdELAC3 = 100;
		long lHomingPositionELAC3 = 0, lOffsetELAC3 = 0;

		DWORD ProfileVelocity, ProfileAcceleration, ProfileDecceleration;
		ProfileVelocity = 600;
		ProfileAcceleration = 50179;
		ProfileDecceleration = 50179;

		// Move Linear Actuator 1 upward to 36mm hight

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
			RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed"));
			return FALSE;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
			RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
			return FALSE;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 600, 1000, 1000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
			RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed"));
			return FALSE;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, -200000, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
			RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed"));
			return FALSE;
		}

		if (!Update_LA3_Position())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 3 Current Position"));
			RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 3 Current Position"));
			return FALSE;
		}

		if (!VCM_SetDisableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to set disable state"));
			RA_DispMsg(_T("ERROR: Unable to set disable state"));
			return FALSE;
		}

		if (!VCM_DisablePositionWindow(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to  disable position Window"));
			RA_DispMsg(_T("ERROR: Unable to  disable position Window"));
			return FALSE;
		}

		RA_DispMsg(_T("INFO: ELAC3 moved upward within safe limits"));

		// Start Mster Encoder Mode

		// Enable ETC3 in PPM

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Activate Master Device"));
			RA_DispMsg(_T("ERROR: Unable to Activate Master Device")); return FALSE;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt9, ProfileVelocity, ProfileAcceleration, ProfileDecceleration, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Set Position profile"));
			RA_DispMsg(_T("ERROR: Unable to Set Position profile"));
			return FALSE;
		}
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Master Device not Enabled"));
			RA_DispMsg(_T("ERROR: Master Device not Enabled"));
			return FALSE;
		}

		// Enable ELAC3 in MEM

		pDoc->pOperationMode = OMD_MASTER_ENCODER_MODE;

		if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode of ELAC3"));
			RA_DispMsg(_T("ERROR: Unable to set Operation Mode of ELAC3"));
			return FALSE;
		}

		if (!VCM_ActivateMasterEncoderMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Activate Master Encoder Mode"));
			RA_DispMsg(_T("ERROR: Unable to Activate Master Encoder Mode"));
			return FALSE;
		}

		pDoc->m_UserInputPolarity = 0;
		pDoc->MaxVelocity = 3000;
		pDoc->MaxAcceleration = 5000;

		if (!VCM_SetMasterEncoderParameter(pDoc->hDriveHandleExt6, 2045, 10000, pDoc->m_UserInputPolarity, pDoc->MaxVelocity, pDoc->MaxAcceleration, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to assign parameters"));
			RA_DispMsg(_T("ERROR: Unable to assign parameters"));
			return FALSE;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Slave Device not Enabled"));
			RA_DispMsg(_T("ERROR: Slave Device not Enabled"));
			return FALSE;
		}

		BOOL Absolute, Immediately;
		Absolute = TRUE;
		Immediately = TRUE;

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt9, 0, Absolute, Immediately, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Move ETC3 to desired position"));
			RA_DispMsg(_T("ERROR: Unable to Move ETC3 to desired position"));
			return FALSE;
		}

		// Update ELAC3 and ETC3 position


		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return FALSE;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return FALSE;
		}

		Display_Motion_Status();

		while (pDoc->bMovingFlagETC3 == 0)
		{
			// Display Position and Motion Status of ELAC3 and ETC3

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
				RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
				return FALSE;
			}

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
				RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
				return FALSE;
			}

			Display_Motion_Status();
			

			Sleep(100);

			// Check and Display Status of ELAC3 and ETC3 Controllers

			if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
				RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
				return FALSE;
			}

			if (pDoc->bELAC3 == TRUE)
			{
				Display_Motion_Status();
				 break;
			}

			if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
				RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
				return FALSE;
			}

			if (pDoc->bETC3 == TRUE)
			{
				Display_Motion_Status();
				 break;
			}

			// Check Movement State of ELAC3 and ETC3 

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
				RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
				return FALSE;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
				RA_DispMsg(_T("Unable to get LA3 Movement State"));
				return FALSE;
			}
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
			return FALSE;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return FALSE;
		}

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			return FALSE;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
			RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
			return FALSE;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return FALSE;
		}

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
			RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
			return FALSE;
		}

		Display_Motion_Status();
		UpdateWindow();

		if (!RaHomeelac3())
		{
			pDoc->RA_LogEvents(_T("ERROR: ELAC3 Homing after synchronization not successful"));
			RA_DispMsg(_T("ERROR: ELAC3 Homing after synchronization not successful"));
			return FALSE;
		}

		RA_DispMsg(_T("INFO: Synchronize Motion tested"));
	}
	DeleteObject(pDoc);
	return TRUE;
}

BOOL C6DOFPCMView::Check_MovementState_Controllers()
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	// NS Movement State

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt2, &(pDoc->bMovingFlagNS), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get NS Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get NS Movement State"));
		return FALSE;
	}

	// EW Movement State

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt3, &(pDoc->bMovingFlagEW), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get EW Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get EW Movement State"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt4, &(pDoc->bMovingFlagELAC1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA1 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get LA1 Movement State"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt5, &(pDoc->bMovingFlagELAC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA2 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get LA2 Movement State"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
		RA_DispMsg(_T("Unable to get LA3 Movement State"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt7, &(pDoc->bMovingFlagETC2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get ETC2 Movement State"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
		return FALSE;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt8, &(pDoc->bMovingFlagCTC), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get CTC Movement State"));
		RA_DispMsg(_T("ERROR: Unable to get CTC Movement State"));
		return FALSE;
	}

	Display_Motion_Status();
	
	DeleteObject(pDoc);
	return TRUE;
}




void C6DOFPCMView::OnBnClickedPark()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}
	if (pDoc->m_login_first == 1)
	{
		if (pDoc->m_usertype_received == "Operator")
		{
			if (pDoc->bHomeandTestFlag == TRUE)
			{
				if (!PM_Park())
				{
					pDoc->RA_LogEvents(_T("ERROR: PM parking not successful"));
					RA_DispMsg("ERROR: PM parking not Successful");
				}
				else
					pDoc->RA_LogEvents(_T("INFO: PM moved to parking area"));
			}
		else
		{
				pDoc->RA_LogEvents(_T("ERROR: Perform Homing and Testing Operation first"));
				RA_DispMsg(_T("ERROR: Perform Homing and Testing Operation first"));
		}
	}
	else
		AfxMessageBox("INFO: Only Operator can peform this operation", MB_TOPMOST);
	}
		else
			AfxMessageBox("INFO: Please Login your accounr first", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL);

	DeleteObject(pDoc);
}




void C6DOFPCMView::OnBnClickedResetMaster()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleInt, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of Master 
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset Master controller"));
			RA_DispMsg(_T("ERROR: Unable to reset Master controller")); return;
		}

		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}
	}

	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedResetNs()
{
	// TODO: Add your control notification handler code here


	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of NS 
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset NS controller"));
			RA_DispMsg(_T("ERROR: Unable to reset NS controller")); return;
		}

		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}
	}
	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedResetEw()
{
	// TODO: Add your control notification handler code here
	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of EW
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset EW controller"));
			RA_DispMsg(_T("ERROR: Unable to reset EW controller")); return;
		}


		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}
	}

	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedResetElac1()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of ELAC1
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset LA1 controller"));
			RA_DispMsg(_T("ERROR: Unable to reset LA1 controller")); return;
		}

		pDoc->bHomeELAC1Flag = FALSE;

		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}
	}

	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedResetMaster2()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of ELAC2 
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset LA2 controller"));
			RA_DispMsg(_T("ERROR: Unable to reset LA2 controller")); return;
		}

		pDoc->bHomeELAC2Flag = FALSE;

		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}
	}

	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedResetElac3()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of ELAC3 
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset LA3 controller"));
			RA_DispMsg(_T("ERROR: Unable to reset LA3 controller")); return;
		}

		pDoc->bHomeELAC3Flag = FALSE;

		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}

		
	}

	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedResetEtc2()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of ETC2 
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset ETC2 controller"));
			RA_DispMsg(_T("ERROR: Unable to reset ETC2 controller")); return;
		}

		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}
	}

	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedResetCtc()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of CTC 
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset CTC controller"));
			RA_DispMsg(_T("ERROR: Unable to reset CTC controller")); return;
		}

		pDoc->bHomeCTCFlag = FALSE;

		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}
	}

	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedResetEtc3()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();   // doc pointer
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (AfxMessageBox("QUERY : To Clear Fault of Press OK, To Reset Device Press CANCEL.", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}
	}
	else
	{
		if (!VCM_ResetDevice(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of ETC3
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to reset ETC3 controller"));
			RA_DispMsg(_T("ERROR: Unable to reset ETC# controller")); return;
		}

		if (!Check_FaultState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Fault State of Controllers"));
			RA_DispMsg("ERROR :Unable to check Fault State of Controllers"); return;
		}

		if (!Check_MovementState_Controllers())
		{
			pDoc->RA_LogEvents(_T("ERROR:  Unable to check Movement State of Controllers"));
			RA_DispMsg("ERROR:  Unable to check Movement State of Controllers"); return;
		}
	}
	DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedClose()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}

	if (pDoc->PDisconnect > 0)
	{
		CWnd* pWnd = AfxGetApp()->GetMainWnd();
		pWnd->PostMessageA(WM_CLOSE);
	}
	else RA_DispMsg(_T("Disconnect the system before closing program"));
	DeleteObject(pDoc);
}


void C6DOFPCMView::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CFormView::OnSysCommand(nID, lParam);
}


HCURSOR C6DOFPCMView::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return static_cast<HCURSOR>(m_hIcon);
}


//BOOL C6DOFPCMView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
//{
//	// TODO: Add your specialized code here and/or call the base class
//
//	return CFormView::OnNotify(wParam, lParam, pResult);
//}


void C6DOFPCMView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	if (m_usertype_received == "Operator")
	{
		ShowWindowNumber(m_cTab.GetCurFocus());
	}

	if (m_usertype_received == "Manager")
	{
		RA_DispMsg(_T("INFO: Only operator can perform operation"));
	}
	// Do something with the "formal parameters" so the compiler is happy in warning level 4
	pNMHDR = NULL;
	pResult = NULL;
}

BOOL C6DOFPCMView::PM_Ready2Home(void)
{
	C6DOFPCMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	if (!pDoc->bConfigFlag)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to home; PM not initialized"));
		return FALSE;
	}
	if (pDoc->bBNL)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to home; NS Brake not Released"));
		return FALSE;
	}
	if (pDoc->bBEL)
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to home; EW Brake not Released"));
		return FALSE;
	}
	DeleteObject(pDoc);
	return TRUE;
}


void C6DOFPCMView::OnBnClickedLoad()
{
	// TODO: Add your control notification handler code here


	
		// TODO: Add your control notification handler code here

		C6DOFPCMDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
		{
			AfxMessageBox("ERROR: Unable to get document pointer");
			return;
		}

		if (pDoc->m_usertype_received == "Operator")
		{
			RA_DispMsg(_T("INFO: Only Manager can Load the Schedule"));
		}
		else
		{
			UpdateData(TRUE);
			CString strText;
			char path[MAX_PATH];
			size_t path_len;

			if (0 != getenv_s(&path_len, path, MAX_PATH, _T("SDISCHEDULE_PATH")) || path_len == 0)
			{
				::AfxMessageBox("ERROR: Cannot find SDISCHEDULE Enviorment Variable");
				return;
			}

			CStdioFile fileSrc;
			CString full_path = CString(path) + CString(_T("\\DFO.dat.txt"));

			//if (!fileSrc.Open((PCTSTR)_T("C:/Users/Roboram/Documents/Visual Studio 2015/Projects/RA01/RA01-Project-16102018/RA01-Project-16102018/SDILogin/Manager.dat.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
			if (!fileSrc.Open(PCTSTR(full_path), CFile::modeCreate | CFile::modeWrite /*| CFile::modeNoTruncate*/))
			{
				//ofstream::app;
				AfxMessageBox("EEROR: Unable to open schedule file");

			}
			else
			{
				fileSrc.Flush();
				for (int index = 0; index <= (Count - 1); index++)
					//for (int index = 0; index <= sizeof(m_ListBox - 1); index++)
				{
					m_ListBox.GetText(index, strText);
					UpdateData(TRUE);
					fileSrc.SeekToEnd();
					fileSrc.WriteString(strText);
					fileSrc.WriteString(_T("\n"));
				}
			}

			pDoc->RA_LogEvents(_T("INFO: Schedule Loaded by Manager"));
			RA_DispMsg(_T("INFO: Schedule Loaded by Manager"));

			//	highlightloadedschedule();
			ScheduleloadedFlag = TRUE;
		
	//		OnBnClickedSignin();
		}
		DeleteObject(pDoc);
}


void C6DOFPCMView::OnBnClickedSignout()
{
	// TODO: Add your control notification handler code here
	
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}

	pDoc->RA_LogEvents(_T("INFO: ") + pDoc->m_usertype_received + _T("\t") + pDoc->m_username_received + _T("\t") + _T("Sign Out"));
	CString tempmsg = _T("INFO: ") + pDoc->m_usertype_received; tempmsg += _T(" "); tempmsg += pDoc->m_username_received; tempmsg += _T(" "); tempmsg += _T("Sign Out");
	RA_DispMsg(tempmsg);
	pDoc->m_usertype_received = _T(" ");
	pDoc->m_username_received = _T(" ");

	m_usertype_received = _T(" ");
	m_username_received = _T(" ");
	pDoc->m_login_first = 0;
	

	DeleteObject(pDoc);

}


void C6DOFPCMView::OnBnClickedSignin()
{
	// TODO: Add your control notification handler code here
	CLoginDlg SignIndlg; // Creating Login Modal Dialog
	SignIndlg.DoModal();
}


void C6DOFPCMView::OnBnClickedremove()
{
	// TODO: Add your control notification handler code here
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}

	if (m_usertype_received == "Manager")
	{
		UpdateData(TRUE);
		--Count;
		int index;
		CString strText;
		index = m_ListBox.GetCurSel();
		m_ListBox.GetText(index, strText);
		m_ListBox.DeleteString(index);
		pDoc->RA_LogEvents(_T("INFO: ") + strText + _T("Removed from Schedule"));
		CString tempmsg = _T("INFO: "); tempmsg += strText; tempmsg += _T(" "); tempmsg += _T("Removed from Schedule");
		RA_DispMsg(tempmsg);
	}
	DeleteObject(pDoc);
}


void C6DOFPCMView::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}

void C6DOFPCMView::Receive_ListBox()
{
	char path[MAX_PATH];
	size_t path_len;

	if (0 != getenv_s(&path_len, path, MAX_PATH, _T("SDISCHEDULE_PATH")) || path_len == 0)
	{
		::AfxMessageBox("ERROR: Cannot find SDISCHEDULE Enviorment Variable");
		return;
	}

	CStdioFile fileSrc;
	CString strline;
	CString strReadString;
	
	CString full_path = CString(path) + CString(_T("\\DFO.dat.txt"));

	if (fileSrc.Open(LPCTSTR(full_path), CFile::modeRead))
	{
		fileSrc.SeekToBegin();
		while ((fileSrc.ReadString(strline)))
		{
			NumFAs++;
			strReadString += strline;
			m_ListBox.AddString(strline);
		}
		fileSrc.Close();
	}
	else
	{
		AfxMessageBox("Error:  Unable to Open File");
	}
	
}

void C6DOFPCMView::DisplayName()
{
	CFont cfont; cfont.Detach(); cfont.CreateFont(50, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, _T("Times New Roman"));
	CWnd* Label;
	
	Label= GetDlgItem(IDC_UserType);
	Label->SetWindowTextA(m_usertype_received);
	Label->SetFont(&cfont, 1);
	Label = GetDlgItem(IDC_UserName);
	Label->SetWindowTextA(m_username_received);
	Label->SetFont(&cfont, 1);
}

bool C6DOFPCMView::Movectc2tosafelimit()
{
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();

	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt8, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set CTC operation mode to profile position mode"));
		RA_DispMsg(_T("ERROR: Unable to set CTC operation mode to profile position mode")); return FALSE;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of CTC controller failed"));
		RA_DispMsg(_T("ERROR: Setting enable state of CTC controller failed")); return FALSE;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for CTC"));
		RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for CTC")); return FALSE;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt8, 4500, 3500, 3500, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for CTC failed"));
		RA_DispMsg(_T("ERROR: Setting position profile for CTC failed")); return FALSE;
	}

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt8, pDoc->targetposition, TRUE, TRUE, &(pDoc->dwErrorCode)))	// Opening of Chuck					
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for CTC failed"));
		RA_DispMsg(_T("ERROR: Move to position for CTC failed")); return FALSE;
	}

	if (!(Update_CTC_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update CTC Current Position"));
		RA_DispMsg(_T("ERROR: Unable to update CTC Current Position")); return FALSE;
	}

	return TRUE;
}

HBRUSH C6DOFPCMView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	HBRUSH hbr;
	//HBRUSH my_color = CreateSolidBrush(RGB(108, 140, 192));
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetBkMode(my_color); 
		pDC->SetBkColor(RGB(108, 140, 192));
		pDC->SetTextColor(RGB(49, 0, 98));

		CFont* m_pFont = new CFont();
		m_pFont->CreatePointFont(80, _T("Times New Roman"));
		pDC->SelectObject(m_pFont);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);

	}

	else
	{
		hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	return hbr;
}


void C6DOFPCMView::OnBnClickedHoldBnl()
{
	// TODO: Add your control notification handler code here
}
