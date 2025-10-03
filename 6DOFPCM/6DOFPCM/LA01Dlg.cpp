// LA01Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "6DOFPCM.h"
#include "LA01Dlg.h"
#include "afxdialogex.h"
#include "6DOFPCMView.h"

#include <Windows.h>
#include "EposPCmd_Comm.h"
#include "EposPCmd_Drive.h"
#include "EposPCmd_Plc.h"
// CLA01Dlg dialog

IMPLEMENT_DYNAMIC(CLA01Dlg, CDialog)

CLA01Dlg::CLA01Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LA01_DLG, pParent)
	, m_SelectedSpeed_LA01(_T(""))
	, m_cstrFLUpdPw(_T(""))
	, m_SelectedMode(_T(""))
	, m_SelectedDirection(_T(""))
	, m_Value(0)
	, m_ValueLA1(0)
	, m_SelectDirectionLA1(_T(""))
	, m_PM_Selected_Location(_T(""))
	, m_SelectedSpeed(_T(""))
	, m_conectCurrent(0)
{
	
}

CLA01Dlg::~CLA01Dlg()
{
	
}

void CLA01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_CBString(pDX, IDC_COMBO1, m);
	//  DDX_CBString(pDX, IDC_COMBO1, m_SelectedSpeed);
	DDX_CBString(pDX, IDC_LA01_SS, m_SelectedSpeed_LA01);
	DDX_Text(pDX, IDC_EDIT3, m_cstrFLUpdPw);
	DDX_CBString(pDX, IDC_COMBO3, m_SelectedMode);
	DDX_CBString(pDX, IDC_COMBO4, m_SelectedDirection);
	DDX_Text(pDX, IDC_EDIT4, m_Value);
	DDX_Text(pDX, IDC_EDIT5, m_ValueLA1);
	DDX_CBString(pDX, IDC_COMBO6, m_SelectDirectionLA1);
	//  DDX_Control(pDX, IDC_Move_PM, m_movePM);
	//  DDX_Control(pDX, IDC_step1, m_step1);
	//  DDX_Control(pDX, IDC_step3, m_step2);
	//  DDX_Control(pDX, IDC_step4, m_step3);
	//  DDX_Control(pDX, IDC_step2, m_step4);
	//  DDX_Control(pDX, IDC_Update_Locations, m_updateFL);
	//  DDX_Control(pDX, IDC_Reset_Locations_File, m_resetFL);
	//  DDX_Control(pDX, IDC_BUTTON9, m_st_ss);
	//  DDX_Control(pDX, IDC_BUTTON10, m_st_bs);
	//  DDX_Control(pDX, IDC_BUTTON149, m_st_sn);
	//  DDX_Control(pDX, IDC_BUTTON11, m_st_bn);
	//  DDX_Control(pDX, IDC_BUTTON7, m_st_sw);
	//  DDX_Control(pDX, IDC_BUTTON8, m_st_bw);
	//  DDX_Control(pDX, IDC_BUTTON6, m_st_se);
	//  DDX_Control(pDX, IDC_BUTTON5, m_st_be);
	//  DDX_Control(pDX, IDC_BUTTON150, m_st_su);
	//  DDX_Control(pDX, IDC_BUTTON151, m_st_bu);
	//  DDX_Control(pDX, IDC_BUTTON157, m_st_sd);
	//  DDX_Control(pDX, IDC_BUTTON15, m_st_bd);
	//  DDX_Control(pDX, IDC_Move_ELAC2, m_ft_movePM);
	//  DDX_Control(pDX, IDC_Move_ELAC1, m_ft_movela1);
	//  DDX_Control(pDX, IDC_Next, m_Next);
	DDX_Text(pDX, IDC_EDIT1, m_PM_Selected_Location);
	DDX_CBString(pDX, IDC_COMBO5, m_SelectedSpeed);
	DDX_Text(pDX, IDC_EDIT2, m_conectCurrent);
	DDX_Control(pDX, IDC_Move_PM, m_movePM);
	DDX_Control(pDX, IDC_Update_Locations, m_updateFL);
	DDX_Control(pDX, IDC_Reset_Locations_File, m_resetFL);
	DDX_Control(pDX, IDC_Move_ELAC2, m_ft_movePM);
	DDX_Control(pDX, IDC_Move_ELAC1, m_ft_movela1);
	DDX_Control(pDX, IDC_step1, m_step1);
	DDX_Control(pDX, IDC_step3, m_step2);
	DDX_Control(pDX, IDC_step4, m_step3);
	DDX_Control(pDX, IDC_Next, m_Next);
}


BEGIN_MESSAGE_MAP(CLA01Dlg, CDialog)
	ON_BN_CLICKED(IDC_Move_PM, &CLA01Dlg::OnBnClickedMovePm)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_step1, &CLA01Dlg::OnBnClickedstep1)
	ON_BN_CLICKED(IDC_step3, &CLA01Dlg::OnBnClickedstep3)
	ON_BN_CLICKED(IDC_step4, &CLA01Dlg::OnBnClickedstep4)
	ON_BN_CLICKED(IDC_step2, &CLA01Dlg::OnBnClickedstep2)
	ON_BN_CLICKED(IDC_Update_Locations, &CLA01Dlg::OnBnClickedUpdateLocations)
	ON_BN_CLICKED(IDC_Reset_Locations_File, &CLA01Dlg::OnBnClickedResetLocationsFile)
	ON_BN_CLICKED(IDC_BUTTON6, &CLA01Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CLA01Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CLA01Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CLA01Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CLA01Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CLA01Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON149, &CLA01Dlg::OnBnClickedButton149)
	ON_BN_CLICKED(IDC_BUTTON11, &CLA01Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON151, &CLA01Dlg::OnBnClickedButton151)
	ON_BN_CLICKED(IDC_BUTTON150, &CLA01Dlg::OnBnClickedButton150)
	ON_BN_CLICKED(IDC_BUTTON157, &CLA01Dlg::OnBnClickedButton157)
	ON_BN_CLICKED(IDC_BUTTON15, &CLA01Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_Move_ELAC2, &CLA01Dlg::OnBnClickedMoveElac2)
	ON_BN_CLICKED(IDC_Move_ELAC1, &CLA01Dlg::OnBnClickedMoveElac1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Next, &CLA01Dlg::OnBnClickedNext)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLA01Dlg message handlers


void CLA01Dlg::OnBnClickedMovePm()
{
	// TODO: Add your control notification handler code here
//	MessageBeep(0xFFFFFFFF);
//	try{
		C6DOFPCMDoc *pDoc;
		pDoc = pDoc->GetDoc();

		if (!pDoc)
		{
			AfxMessageBox("ERROR: Unable to get document pointer");
			return;
		}

		{
			// TODO: Add your control notification handler code here
			pDoc->m_iCmdCntsNS = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][0];
			pDoc->m_iCmdCntsEW = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][1];
			pDoc->m_iCmdCntsELAC1 = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][6];
			pDoc->bSelectLocFlagNS = TRUE;
			pDoc->bSelectLocFlagEW = TRUE;

			PM_Move_to_Selected_Location();
		}
//	}
//	catch(CException& e)
//	{
		
//	}
		DeleteObject(pDoc);
		
}


BOOL CLA01Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CBrush brNew(RGB(158,180,214));                      // To edit the background color give desired color code here
	//CBrush brNew(RGB(108, 140, 192));
	CBrush*poldBrush = (CBrush*)pDC->SelectObject(&brNew);
	CRect rc;
	pDC->GetClipBox(rc);
	pDC->PatBlt(0, 0, rc.Width(), rc.Height(), PATCOPY);
	pDC->SelectObject(poldBrush);
	DeleteObject(poldBrush);
	return TRUE;
}


BOOL CLA01Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();

	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}
	

//	UpdateData(FALSE);

	NS_FINE_INC = 2500;//Fine Step for Motion along NS & EW
	EW_FINE_INC = 2500;
	NS_COARSE_INC = 10000;//Coarse Step for Motion along NS & EW
	EW_COARSE_INC = 10000;

	LA1_FINE_INC = 24500;//Fine Step for Motion along z-axix LA1
	LA1_COARSE_INC = 49000;//Fine Step for Motion along z-axis LA1

	m_movePM.LoadStdImage(IDB_move_PM,("PNG"));
	m_movePM.SetToolTipText(_T("Move PM to the selected location"), TRUE);
	m_updateFL.LoadStdImage(IDB_UpdateList, ("PNG"));
	m_updateFL.SetToolTipText(_T("Update the Location"), TRUE);
	m_resetFL.LoadStdImage(IDB_ResetLocations, ("PNG"));
	m_resetFL.SetToolTipText(_T("Reset the Location"), TRUE);
//	m_st_ss.LoadStdImage(IDB_Move_UP, ("PNG"));
//	m_st_ss.SetToolTipText(_T("Move PM 1mm towards South"), TRUE);
//	m_st_bs.LoadStdImage(IDB_st_bs, ("PNG"));
//	m_st_bs.SetToolTipText(_T("Move PM 2mm towards South"), TRUE);
//	m_st_sn.LoadStdImage(IDB_move_down, ("PNG"));
//	m_st_sn.SetToolTipText(_T("Move PM 1mm towards North"), TRUE);
//	m_st_bn.LoadStdImage(IDB_st_bn, ("PNG"));
//	m_st_bn.SetToolTipText(_T("Move PM 2mm towards North"), TRUE);
//	m_st_sw.LoadStdImage(IDB_move_right, ("PNG"));
//	m_st_sw.SetToolTipText(_T("Move PM 1mm towards West"), TRUE);
//	m_st_bw.LoadStdImage(IDB_st_bw, ("PNG"));
//	m_st_bw.SetToolTipText(_T("Move PM 2mm towards West"), TRUE);
//	m_st_se.LoadStdImage(IDB_move_left, ("PNG"));
//	m_st_se.SetToolTipText(_T("Move PM 1mm towards East"), TRUE);
//	m_st_be.LoadStdImage(IDB_st_be, ("PNG"));
//	m_st_be.SetToolTipText(_T("Move PM 2mm towards East"), TRUE);
//	m_st_su.LoadStdImage(IDB_LA_up, ("PNG"));
//	m_st_su.SetToolTipText(_T("Move ELAC1 1mm in upward direction"), TRUE);
//	m_st_bu.LoadStdImage(IDB_LA_upward, ("PNG"));
//	m_st_bu.SetToolTipText(_T("Move ELAC1 2mm in upward direction"), TRUE);
//	m_st_sd.LoadStdImage(IDB_LA_Down, ("PNG"));
//	m_st_sd.SetToolTipText(_T("Move ELAC1 1mm in downward direction"), TRUE);
//	m_st_bd.LoadStdImage(IDB_LA_downward, ("PNG"));
//	m_st_bd.SetToolTipText(_T("Move ELAC1 2mm in downward direction"), TRUE);
	m_ft_movePM.LoadStdImage(IDB_move, ("PNG"));
	m_ft_movePM.SetToolTipText(_T("Move PM, To stop press END from keyboard"), TRUE);
	m_ft_movela1.LoadStdImage(IDB_move, ("PNG"));
	m_ft_movela1.SetToolTipText(_T("Move ELAC1, To stop press END from keyboard"), TRUE);
	m_step1.LoadStdImage(IDB_step1, ("PNG"));
	m_step1.SetToolTipText(_T("Move ELAC1 to safe Limit"), TRUE);
	m_step2.LoadStdImage(IDB_step2, ("PNG"));
	m_step2.SetToolTipText(_T("Connect Hansen Socket"), TRUE);
	m_step3.LoadStdImage(IDB_step3, ("PNG"));
	m_step3.SetToolTipText(_T("Leave Hansen Socket"), TRUE);
//	m_step4.LoadStdImage(IDB_laststep, ("PNG"));
//	m_step4.SetToolTipText(_T("Move ELAC1 to parking position"), TRUE);
	m_Next.LoadStdImage(IDB_Next, ("PNG"));
	m_Next.SetToolTipText(_T("Open Next Dialog"), TRUE);

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CLA01Dlg::PM_Move_to_Selected_Location()
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
	
	if (!PM_Speed())
	{
		AfxMessageBox(_T("ERROR: Select PM speed first"));
	}
	
	if (pView->PM_Ready2Move())//&& bSelectLocFlagNS && bSelectLocFlagEW)
	{
	//	UpdateData(TRUE);
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
		}
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for NS")); return;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, ProfileVelocityNS, ProfileAccelerationNS, ProfileDeccelerationNS, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
		}
		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for EW")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, ProfileVelocityEW, ProfileAccelerationEW, ProfileDeccelerationEW, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, pDoc->m_iCmdCntsNS, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for NS failed")); return;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, pDoc->m_iCmdCntsEW, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for EW failed")); return;
		}

		m_PM_Selected_Location = pDoc->PM_selected_Location;
		UpdateData(FALSE);

		pDoc->bMove2PosFlag = TRUE;

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}

		pDoc->RA_LogEvents(_T("INFO: PM Moved to the Selected Location"));
		pView->RA_DispMsg(_T("INFO: PM Moved to the Selected Location"));
	}


}

BOOL CLA01Dlg::PM_Speed()
{	
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	UpdateData(TRUE);

	if (m_SelectedSpeed == "Fast") // FAST
	{
		ProfileVelocityNS = pDoc->FProfileVelocityNS;
		ProfileAccelerationNS = pDoc->FProfileAccelerationNS;
		ProfileDeccelerationNS = pDoc->FProfileDeccelerationNS;

		ProfileVelocityEW = pDoc->FProfileVelocityEW;
		ProfileAccelerationEW = pDoc->FProfileAccelerationEW;
		ProfileDeccelerationEW = pDoc->FProfileDeccelerationEW;
		return TRUE;
	}

	if (m_SelectedSpeed == "Medium") // MEDIUM
	{
		ProfileVelocityNS = pDoc->MProfileVelocityNS;
		ProfileAccelerationNS = pDoc->MProfileAccelerationNS;
		ProfileDeccelerationNS = pDoc->MProfileDeccelerationNS;

		ProfileVelocityEW = pDoc->MProfileVelocityEW;
		ProfileAccelerationEW = pDoc->MProfileAccelerationEW;
		ProfileDeccelerationEW = pDoc->MProfileDeccelerationEW;
		return TRUE;
	}

	if (m_SelectedSpeed == "Slow") // SLOW
	{
		ProfileVelocityNS = pDoc->SProfileVelocityNS;
		ProfileAccelerationNS = pDoc->SProfileAccelerationNS;
		ProfileDeccelerationNS = pDoc->SProfileDeccelerationNS;

		ProfileVelocityEW = pDoc->SProfileVelocityEW;
		ProfileAccelerationEW = pDoc->SProfileAccelerationEW;
		ProfileDeccelerationEW = pDoc->SProfileDeccelerationEW;
		return TRUE;
	}

	
}

bool CLA01Dlg::Get_Pointers()
{
	
	return true;
}

BOOL CLA01Dlg::LA01_Speed()
{
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return FALSE;
	}

	C6DOFPCMView *pView;
	pView = pView->GetView();
	if (!pView)
	{
		AfxMessageBox("ERROR: Unable to get View pointer");
		return FALSE;
	}

	UpdateData(TRUE);
	if (m_SelectedSpeed_LA01 == "Fast") // FAST
	{
		ProfileVelocityLA01 = pDoc->FProfileVelocityLA1;
		ProfileAccelerationLA01 = pDoc->FProfileAccelerationLA1;
		ProfileDeccelerationLA01 = pDoc->FProfileDeccelerationLA1;
		return TRUE;
	}

	if (m_SelectedSpeed_LA01 == "Medium") // MEDIUM
	{
		ProfileVelocityLA01 = pDoc->MProfileVelocityLA1;
		ProfileAccelerationLA01 = pDoc->MProfileAccelerationLA1;
		ProfileDeccelerationLA01 = pDoc->MProfileDeccelerationLA1;
		return TRUE;
	}

	if (m_SelectedSpeed_LA01 == "Slow") // SLOW
	{
		ProfileVelocityLA01 = pDoc->SProfileVelocityLA1;
		ProfileAccelerationLA01 = pDoc->SProfileAccelerationLA1;
		ProfileDeccelerationLA01 = pDoc->SProfileDeccelerationLA1;
		return TRUE;
	}

	
}


void CLA01Dlg::OnBnClickedstep1()
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

	if (!LA01_Speed())
	{
		pView->RA_DispMsg(_T("INFO: Select speed first")); return;
	}

	pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt4, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set Profile Position Mode of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to set Profile Position Mode of ELAC1")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt4, ProfileVelocityLA01, ProfileAccelerationLA01, ProfileDeccelerationLA01, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC1 failed")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	//if (!VCM_MoveToPosition(pDoc->hDriveHandleExt4, -200000, TRUE, TRUE, &(pDoc->dwErrorCode)))
	//{
	//	pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC1 failed")); 
	//	pView->RA_DispMsg(_T("ERROR: Move to position for ELAC1 failed")); return ;
	//}

	pDoc->m_iCmdCntsELAC1 = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][6];

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt4, pDoc->m_iCmdCntsELAC1, TRUE, TRUE, &(pDoc->dwErrorCode))) //-4200000
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC1 failed"));
	}

	if (!(pView->Update_LA1_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update ELAC1 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update ELAC1 Current Position")); return;
	}

	DeleteObject(pDoc); DeleteObject(pView);
	
}


void CLA01Dlg::OnBnClickedstep3()
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

	{
		// TODO: Add your control notification handler code here

		// Start moving LA1 in current mode to fix hansen nut

		// Start moving LA1 in current mode

		UpdateData(TRUE); // retreive m_shCmdCrntELAC1 LA1 current must value from window

		pDoc->pOperationMode = OMD_CURRENT_MODE;

		if (!VCM_SetOperationMode(pDoc->hDriveHandleExt4, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode of ELAC!"));
			pView->RA_DispMsg(_T("ERROR: Unable to set Operation Mode of ELAC1")); return;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 failed")); return;
		}

		if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unbable to activate Current Mode for ELAC1"));
			pView->RA_DispMsg(_T("ERROR: Unbable to activate Current Mode for ELAC1")); return;
		}

		UpdateData(TRUE);

		if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt4, -(abs(m_conectCurrent)), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting Current for ELAC1 failed"));
			pView->RA_DispMsg(_T("ERROR: Setting Current for ELAC1 failed")); return;
		}

		Sleep(200);

		pDoc->RA_LogEvents(_T("INFO: ELAC1 moved in Current mode"));
		pDoc->bMoveWithCurFlagELAC1 = TRUE;


		while (1)
		{

			// Check movement state of ELAC1 and display its status

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt4, &(pDoc->bMovingFlagELAC1), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to read ELAC1 movement state"));
				pView->RA_DispMsg(_T("ERROR: Unable to read ELAC1 movement state")); return;
			}

			// Check the position of LA1

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt4, &(pDoc->pPositionIsLA1), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get current Position of ELAC1"));
				pView->RA_DispMsg(_T("ERROR: Unable to get current Position of ELAC1")); return;
			}

			// Check Fault state of ELAC1 and display its status

			if (!VCM_GetFaultState(pDoc->hDriveHandleExt4, &(pDoc->bELAC1), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get state of ELAC1 controller"));
				pView->RA_DispMsg(_T("ERROR: Unable to get state of ELAC1 controller")); return;
			}

			// Check average velocity of LA1

			if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt4, &(pDoc->pVelocityIsAveraged), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity of ELAC1"));
				pView->RA_DispMsg(_T("ERROR: Unable to Get average velocity of ELAC1")); return;
			}

			pView->Display_Motion_Status();
			

			if (GetAsyncKeyState(VK_END))
			{
				if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ELAC1"));
					pView->RA_DispMsg(_T("ERROR: Unable to quickstop ELAC1"));
					return;
				}

				break;
			}

			SHORT pCurrentIs;

			if (!VCM_GetCurrentIs(pDoc->hDriveHandleExt4, &(pCurrentIs), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("Unable to Get average current"));
				pView->RA_DispMsg(_T("ERROR: Unable to read ELAC1 current")); return;
			}

			if (abs(pDoc->pVelocityIsAveraged) < 10 && abs(pDoc->pPositionIsLA1) < abs(pDoc->m_iCmdCntsELAC1 - 800000)) //abs(pDoc->m_iCmdCntsELAC1 - 850000)
			{
				pCurrentIs = pCurrentIs - 10;

				if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt4, pCurrentIs, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Setting Current for ELAC1 failed"));
					pView->RA_DispMsg(_T("ERROR: Setting Current for ELAC1 failed")); return;
				}
				Sleep(200);
			}
			if (abs(pDoc->pVelocityIsAveraged) < 10 && abs(pDoc->pPositionIsLA1) >= abs(pDoc->m_iCmdCntsELAC1 - 850000)) //5050000
			{
				if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to quick stop ELAC1"));
					AfxMessageBox(_T("WARNING: PRESS EMERGENCY BUTTON ON THE CONTROL PANNEL TO STOP ELAC1"), (MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK);
					return;
				}
				break;
			}


		}

		pView->RA_DispMsg(_T("INFO: Hansen Socket Succesfully Connected"));
	}
	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedstep4()
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

	{
		// TODO: Add your control notification handler code here

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for NS")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, ProfileVelocityNS, ProfileAccelerationNS, ProfileDeccelerationNS, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get NS	current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get NS	current Position")); return;
		}

		pDoc->m_iCmdCntsNS = pDoc->pPositionIsNS + 134000; //114000

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, pDoc->m_iCmdCntsNS, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for NS failed")); return;
		}

		if (!pView->Update_PM_Position())
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Update PM Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to Update PM Position")); return;
		}

	}

	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedstep2()
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

	if (!pView->RaHomeelac1())
	{
		pDoc->RA_LogEvents(_T("ERROR: ELAC1 Homing and Testing not successful"));
		pView->RA_DispMsg(_T("ERROR: ELAC1 Homing and Testing not successful"));
		return;
	}

	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedUpdateLocations()
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
	if (m_cstrFLUpdPw == "RA")
	{

		//Update of location for EET1

		pDoc->NSdiff = (pView->m_pPositionIsNS) - (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][0]);
		pDoc->EWdiff = (pView->m_pPositionIsEW) - (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][1]);

		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][0] = pView->m_pPositionIsNS;
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][1] = pView->m_pPositionIsEW;
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][6] = pView->m_pPositionIsELAC1;

		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][2] = (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][2]) - (pDoc->NSdiff);
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][3] = (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][3]) - (pDoc->EWdiff);
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][4] = (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][4]) - (pDoc->NSdiff);
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][5] = (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][5]) - (pDoc->EWdiff);

		PM_WriteLocations2File();

		m_cstrFLUpdPw = "";
		UpdateData(FALSE);
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: Incorrect Password"));
		pView->RA_DispMsg(_T("ERROR: Incorrect Password"));
	}
	DeleteObject(pDoc); DeleteObject(pView);
}

/*void CLA01Dlg::PM_WriteLocations2File()
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

	CFile WF;
	CFileException ex;

	if (!WF.Open("LocationLattice.dat", CFile::modeCreate | CFile::modeReadWrite, &ex))
	{
		ex.ReportError();
		pDoc->RA_LogEvents("ERROR: Unable to open locations file 'LocationLattice.dat'");
		return;
	}
	CString strVar;
	UINT i, j;

	for (i = 0; i < 29; i++)
	{
		for (j = 0; j < 15; j++)
		{
			/*strVar.Format(_T("%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\r\n"), pDoc->iLocGrid[i][j][0], pDoc->iLocGrid[i][j][1], pDoc->iLocGrid[i][j][2], pDoc->iLocGrid[i][j][3], pDoc->iLocGrid[i][j][4], pDoc->iLocGrid[i][j][5], pDoc->iLocGrid[i][j][6], pDoc->iLocGrid[i][j][7], pDoc->iLocGrid[i][j][8]);
			strVar.Format(strVar + _T("%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\r\n"), pDoc->iLocGrid[i][j][4], pDoc->iLocGrid[i][j][5], pDoc->iLocGrid[i][j][6], pDoc->iLocGrid[i][j][7], pDoc->iLocGrid[i][j][8], pDoc->iLocGrid[i][j][0], pDoc->iLocGrid[i][j][1], pDoc->iLocGrid[i][j][2], pDoc->iLocGrid[i][j][3]);
			strVar.Format(strVar + _T("\r\n"));*/
/*			strVar.Format("%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\r\n", pDoc->iLocGrid[i][j][0], pDoc->iLocGrid[i][j][1], pDoc->iLocGrid[i][j][2], pDoc->iLocGrid[i][j][3], pDoc->iLocGrid[i][j][4], pDoc->iLocGrid[i][j][5], pDoc->iLocGrid[i][j][6], pDoc->iLocGrid[i][j][7], pDoc->iLocGrid[i][j][8]);
			WF.Write((LPCTSTR)strVar, strVar.GetLength());
		}
		strVar.Format("\r\n\r\n");
		WF.Write((LPCTSTR)strVar, strVar.GetLength());
	}
	WF.Close();
	pDoc->RA_LogEvents(_T("INFO: Location Updated"));
	pView->RA_DispMsg(_T("INFO: Location Updated"));

}*/

void CLA01Dlg::PM_WriteLocations2File()
{
	C6DOFPCMDoc* pDoc;
	pDoc = pDoc->GetDoc();
	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}

	C6DOFPCMView* pView;
	pView = pView->GetView();
	if (!pView)
	{
		AfxMessageBox("ERROR: Unable to get View pointer");
		return;
	}

	CFile WF;
	CFileException ex;

	if (!WF.Open("LocationLattice.dat", CFile::modeCreate | CFile::modeReadWrite, &ex))
	{
		ex.ReportError();
		pDoc->RA_LogEvents("ERROR: Unable to open locations file 'LocationLattice.dat'");
		return;
	}
	CString strVar;
	UINT i, j;

	for (i = 0; i < 40; i++)
	{
		for (j = 0; j < 25; j++)
		{
			/*strVar.Format(_T("%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\r\n"), pDoc->iLocGrid[i][j][0], pDoc->iLocGrid[i][j][1], pDoc->iLocGrid[i][j][2], pDoc->iLocGrid[i][j][3], pDoc->iLocGrid[i][j][4], pDoc->iLocGrid[i][j][5], pDoc->iLocGrid[i][j][6], pDoc->iLocGrid[i][j][7], pDoc->iLocGrid[i][j][8]);
			strVar.Format(strVar + _T("%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\r\n"), pDoc->iLocGrid[i][j][4], pDoc->iLocGrid[i][j][5], pDoc->iLocGrid[i][j][6], pDoc->iLocGrid[i][j][7], pDoc->iLocGrid[i][j][8], pDoc->iLocGrid[i][j][0], pDoc->iLocGrid[i][j][1], pDoc->iLocGrid[i][j][2], pDoc->iLocGrid[i][j][3]);
			strVar.Format(strVar + _T("\r\n"));*/
			strVar.Format("%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\r\n", pDoc->iLocGrid[i][j][0], pDoc->iLocGrid[i][j][1], pDoc->iLocGrid[i][j][2], pDoc->iLocGrid[i][j][3], pDoc->iLocGrid[i][j][4], pDoc->iLocGrid[i][j][5], pDoc->iLocGrid[i][j][6], pDoc->iLocGrid[i][j][7], pDoc->iLocGrid[i][j][8]);
			WF.Write((LPCTSTR)strVar, strVar.GetLength());
		}
		strVar.Format("\r\n\r\n");
		WF.Write((LPCTSTR)strVar, strVar.GetLength());
	}
	WF.Close();
	pDoc->RA_LogEvents(_T("INFO: Location Updated"));
	pView->RA_DispMsg(_T("INFO: Location Updated"));

}

void CLA01Dlg::OnBnClickedResetLocationsFile()
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

	{
		// TODO: Add your control notification handler code here

		int NSLINES[29] = { { 0 } }, EWLINES[15] = { { 0 } }, E1NSLINES[29] = { { 0 } }, E2NSO[29] = { { 0 } }, E3NSO[29] = { { 0 } }, E1EWLINES[15] = { { 0 } }, E2EWO[15] = { { 0 } }, E3EWO[15] = { { 0 } }, ZO1[29] = { { 0 } }, ZO2[29] = { { 0 } }, ZO3[29] = { { 0 } };
		UINT i, j;
		//  NS INCREMENT 106351 // EW INCREMENT 298182
		//  NS Reference 21 : 2457000 and EW Reference G : -1320000

		for (i = 0; i < 29; i++)
		{
			E1NSLINES[i] = 2457000 + (i - 12) * 106351;
			E2NSO[i] = -249500;
			E3NSO[i] = -730000;
			//Z-direction travels of EETs
			ZO1[i] = -3500000;
			ZO2[i] = -3800000;
			ZO3[i] = -500000;
		}

		for (i = 0; i < 15; i++)
		{
			E1EWLINES[i] = -1320000 + (i - 3) * 298182;
			E2EWO[i] = -184400;
			E3EWO[i] = 59000;

		}
		for (i = 7; i < 15; i++)
		{

			E2EWO[i] = 114142;
		}

		for (i = 0; i < 29; i++)
		{
			for (j = 0; j < 15; j++)
			{
				pDoc->iLocGrid[i][j][0] = E1NSLINES[i];
				pDoc->iLocGrid[i][j][1] = E1EWLINES[j];
				pDoc->iLocGrid[i][j][2] = E2NSO[i];
				pDoc->iLocGrid[i][j][3] = E2EWO[j];
				pDoc->iLocGrid[i][j][4] = E3NSO[i];
				pDoc->iLocGrid[i][j][5] = E3EWO[j];
				pDoc->iLocGrid[i][j][6] = ZO1[i];
				pDoc->iLocGrid[i][j][7] = ZO2[i];
				pDoc->iLocGrid[i][j][8] = ZO3[i];


			}
		}
		PM_WriteLocations2File();
		pDoc->RA_LogEvents(_T("INFO: locations file 'LocationLattice.dat' Reset"));
		pView->RA_DispMsg(_T("INFO: locations file 'LocationLattice.dat' Reset"));
	}
	
	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton6()
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

	if (pView->PM_Ready2Move())
	{

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for EW")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 1000, 5000, 5000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for EW failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of EW")); return;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, (pDoc->pPositionIsEW) + EW_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for EW failed")); return;
		}

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}
	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton5()
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


	if (pView->PM_Ready2Move())
	{

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for EW")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 1000, 5000, 5000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for EW failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of EW")); return;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, (pDoc->pPositionIsEW) + EW_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for EW failed")); return;
		}

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}
	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton7()
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

	if (pView->PM_Ready2Move())
	{

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for EW")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 1000, 5000, 5000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for EW failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of EW")); return;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, (pDoc->pPositionIsEW) - EW_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for EW failed")); return;
		}

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}

	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton8()
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

	if (pView->PM_Ready2Move())
	{

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for EW")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 1000, 5000, 5000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for EW failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of EW"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of EW")); return;
		}

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, (pDoc->pPositionIsEW) - EW_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for EW failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for EW failed")); return;
		}

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}
	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton9()
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
	if (pView->PM_Ready2Move())
	{
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for NS")); return;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, 1000, 5000, 5000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of NS")); return;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, (pDoc->pPositionIsNS) + NS_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Fine Move for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Fine Move for NS failed")); return;
		}

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}
	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton10()
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
	if (pView->PM_Ready2Move())
	{
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for NS")); return;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, 1000, 5000, 5000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of NS")); return;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, (pDoc->pPositionIsNS) + NS_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Fine Move for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Fine Move for NS failed")); return;
		}

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}

	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton149()
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
	if (pView->PM_Ready2Move())
	{
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for NS")); return;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, 1000, 5000, 5000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of NS")); return;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, (pDoc->pPositionIsNS) - NS_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Fine Move for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Fine Move for NS failed")); return;
		}

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}
	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton11()
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

	if (pView->PM_Ready2Move())
	{
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for NS")); return;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, 1000, 5000, 5000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of NS"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of NS")); return;
		}
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, (pDoc->pPositionIsNS) - NS_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Fine Move for NS failed"));
			pView->RA_DispMsg(_T("ERROR: Fine Move for NS failed")); return;
		}

		if (!(pView->Update_PM_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
			return;
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}
	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedButton151()
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

	pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt4, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC1")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt4, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC1 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt4, &(pDoc->pPositionIsLA1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of ELAC1")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt4, (pDoc->pPositionIsLA1) - LA1_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC1 failed")); return;
	}

	/*	if (!VCM_MoveToPosition(hDriveHandleExt4,-3500000, TRUE, TRUE, &dwErrorCode))
	{
	AfxMessageBox(_T("ERROR: Move to position for ELAC1 failed")); return FALSE;
	}
	*/
	if (!(pView->Update_LA1_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update ELAC1 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update ELAC1 Current Position")); return;
	}
}


void CLA01Dlg::OnBnClickedButton150()
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

	pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt4, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC1")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt4, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC1 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt4, &(pDoc->pPositionIsLA1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of ELAC1")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt4, (pDoc->pPositionIsLA1) - LA1_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC1 failed")); return;
	}

	/*	if (!VCM_MoveToPosition(hDriveHandleExt4,-3500000, TRUE, TRUE, &dwErrorCode))
	{
	AfxMessageBox(_T("ERROR: Move to position for ELAC1 failed")); return FALSE;
	}
	*/
	if (!(pView->Update_LA1_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update ELAC1 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update ELAC1 Current Position")); return;
	}
}


void CLA01Dlg::OnBnClickedButton157()
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
	pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt4, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC1")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt4, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC1 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt4, &(pDoc->pPositionIsLA1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of ELAC1")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000
	if (abs(pDoc->pPositionIsLA1) <= 25000)
	{
		pDoc->RA_LogEvents(_T("ERROR: You have reached Lower Limit (Home Switch), ELAC1 can not move"));
		pView->RA_DispMsg(_T("ERROR : You have reached Lower Limit (Home Switch), ELAC1 can not move")); return;
	}
	else
	{
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt4, (pDoc->pPositionIsLA1) + LA1_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC1 failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for ELAC1 failed")); return;
		}

		/*	if (!VCM_MoveToPosition(hDriveHandleExt4,-3500000, TRUE, TRUE, &dwErrorCode))
		{
		AfxMessageBox(_T("ERROR: Move to position for ELAC1 failed")); return FALSE;
		}
		*/
		if (!(pView->Update_LA1_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update ELAC1 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update ELAC1 Current Position")); return;
		}
	}
}


void CLA01Dlg::OnBnClickedButton15()
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
	pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt4, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC1")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC1")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt4, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC1 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt4, &(pDoc->pPositionIsLA1), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of ELAC1")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000
	if (abs(pDoc->pPositionIsLA1) <= 50000)
	{
		pView->RA_DispMsg(_T("ERROR : You have reached Lower Limit (Home Switch), ELAC1 can not move")); return;
	}
	else
	{
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt4, (pDoc->pPositionIsLA1) + LA1_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC1 failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for ELAC1 failed")); return;
		}

		/*	if (!VCM_MoveToPosition(hDriveHandleExt4,-3500000, TRUE, TRUE, &dwErrorCode))
		{
		AfxMessageBox(_T("ERROR: Move to position for ELAC1 failed")); return FALSE;
		}
		*/
		if (!(pView->Update_LA1_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update ELAC1 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update ELAC1 Current Position")); return;
		}
	}
}


void CLA01Dlg::OnBnClickedMoveElac2()
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
	if (pView->PM_Ready2Move())
	{
		UpdateData(TRUE);

		if (m_SelectedMode == "Profile Velocity Mode" && m_SelectedDirection == "West")
		{

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
			}

			if (!VCM_ActivateProfileVelocityMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Velocity Mode for EW"));
				pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Velocity Mode for EW")); return;
			}

			if (!VCM_SetVelocityProfile(pDoc->hDriveHandleExt3, 1000, 1000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting velocity profile for EW failed"));
				pView->RA_DispMsg(_T("ERROR: Setting velocity profile for EW failed")); return;
			}

			if (!VCM_MoveWithVelocity(pDoc->hDriveHandleExt3, -(abs(m_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move with velocity failed for EW"));
				pView->RA_DispMsg(_T("ERROR: Move with velocity failed for EW")); return;
			}

			while (1)
			{
				pDoc->bMovingFlagEW = 0;
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop EW"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop EW"));
						return;
					}

					break;
				}

				pDoc->bMovingFlagEW = 1;
				pView->Update_All_Positions();
			}

			pDoc->bMoveWithVelFlag = TRUE;

		}

		if (m_SelectedMode == "Profile Velocity Mode" && m_SelectedDirection == "East")
		{

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
			}

			if (!VCM_ActivateProfileVelocityMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unbable to activate Profile Velocity Mode for EW"));
				pView->RA_DispMsg(_T("ERROR: Unbable to activate Profile Velocity Mode for EW")); return;
			}

			if (!VCM_SetVelocityProfile(pDoc->hDriveHandleExt3, 1000, 1000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting velocity profile for EW failed"));
				pView->RA_DispMsg(_T("ERROR: Setting velocity profile for EW failed")); return;
			}

			if (!VCM_MoveWithVelocity(pDoc->hDriveHandleExt3, (abs(m_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move with velocity failed for EW"));
				pView->RA_DispMsg(_T("ERROR: Move with velocity failed for EW")); return;
			}

			while (1)
			{
				pDoc->bMovingFlagEW = 0;
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop EW"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop EW"));
						return;
					}

					break;
				}

				pDoc->bMovingFlagEW = 1;
				pView->Update_All_Positions();
			}

			pDoc->bMoveWithVelFlag = TRUE;

		}

		if (m_SelectedMode == "Profile Velocity Mode" && m_SelectedDirection == "North")
		{

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
			}

			if (!VCM_ActivateProfileVelocityMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Velocity Mode for NS"));
				pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Velocity Mode for NS")); return;
			}

			if (!VCM_SetVelocityProfile(pDoc->hDriveHandleExt2, 1000, 1000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting velocity profile for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting velocity profile for Ns failed")); return;
			}

			if (!VCM_MoveWithVelocity(pDoc->hDriveHandleExt2, -(abs(m_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move with velocity failed for NS"));
				pView->RA_DispMsg(_T("ERROR: Move with velocity failed for NS")); return;
			}

			while (1)
			{
				pDoc->bMovingFlagNS = 0;
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop NS"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop NS"));
						return;
					}

					break;
				}

				pDoc->bMovingFlagNS = 1;
				pView->Update_All_Positions();
			}


			pDoc->bMoveWithVelFlag = TRUE;

		}

		if (m_SelectedMode == "Profile Velocity Mode" && m_SelectedDirection == "South")
		{

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
			}

			if (!VCM_ActivateProfileVelocityMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Velocity Mode for NS"));
				pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Velocity Mode for NS")); return;
			}

			if (!VCM_SetVelocityProfile(pDoc->hDriveHandleExt2, 1000, 1000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting velocity profile for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting velocity profile for Ns failed")); return;
			}

			if (!VCM_MoveWithVelocity(pDoc->hDriveHandleExt2, (abs(m_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move with velocity failed for NS"));
				pView->RA_DispMsg(_T("ERROR: Move with velocity failed for NS")); return;
			}

			while (1)
			{
				pDoc->bMovingFlagNS = 0;
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop NS"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop NS"));
						return;
					}

					break;
				}

				pDoc->bMovingFlagNS = 1;
				pView->Update_All_Positions();
			}

			pDoc->bMoveWithVelFlag = TRUE;

		}

		if (m_SelectedMode == "Current Mode" && m_SelectedDirection == "South")
		{

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
			}

			if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Current Mode for NS"));
				pView->RA_DispMsg(_T("ERROR: Unable to activate Current Mode for NS")); return;
			}

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt2, (SHORT)abs(m_Value), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for NS failed")); return;
			}

			while (1)
			{
				pDoc->bMovingFlagNS = 0;
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop NS"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop NS"));
						return;
					}

					break;
				}

				pDoc->bMovingFlagNS = 1;
				pView->Update_All_Positions();
			}

		}

		if (m_SelectedMode == "Current Mode" && m_SelectedDirection == "North")
		{

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of NS controller failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of NS controller failed")); return;
			}

			if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Current Mode for NS"));
				pView->RA_DispMsg(_T("ERROR: Unable to activate Current Mode for NS")); return;
			}

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt2, -(SHORT)(abs(m_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for NS failed")); return;
			}
			while (1)
			{
				pDoc->bMovingFlagNS = 0;
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt2, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop NS"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop NS"));
						return;
					}

					break;
				}

				pDoc->bMovingFlagNS = 1;
				pView->Update_All_Positions();
			}

		}

		if (m_SelectedMode == "Current Mode" && m_SelectedDirection == "East")
		{

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
			}

			if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Current Mode for EW"));
				pView->RA_DispMsg(_T("ERROR: Unable to activate Current Mode for EW")); return;
			}

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt3, (SHORT)abs(m_Value), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for EW failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for EW failed")); return;
			}

			while (1)
			{
				pDoc->bMovingFlagEW = 0;
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop EW"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop Ew"));
						return;
					}

					break;
				}

				pDoc->bMovingFlagEW = 1;
				pView->Update_All_Positions();
			}

		}

		if (m_SelectedMode == "Current Mode" && m_SelectedDirection == "West")
		{

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of EW controller failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of EW controller failed")); return;
			}

			if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to activate Current Mode for EW"));
				pView->RA_DispMsg(_T("ERROR: Unable to activate Current Mode for EW")); return;
			}

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt3, -(SHORT)(abs(m_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for EW failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for EW failed")); return;
			}

			while (1)
			{
				pDoc->bMovingFlagEW = 0;
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt3, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop EW"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop Ew"));
						return;
					}

					break;
				}

				pDoc->bMovingFlagEW = 1;
				pView->Update_All_Positions();
			}
		}
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}

	DeleteObject(pDoc); DeleteObject(pView);
}


void CLA01Dlg::OnBnClickedMoveElac1()
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

	UpdateData(TRUE); // retreive m_shCmdCrntELAC1 LA1 current must value from window
	m_ValueLA1 = abs(m_ValueLA1);
	pDoc->pOperationMode = OMD_CURRENT_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt4, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode"));
		pView->RA_DispMsg(_T("ERROR: Unable to set Operation Mode")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC1 failed")); return;
	}

	if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unbable to activate Current Mode for ELAC1"));
		pView->RA_DispMsg(_T("ERROR: Unbable to activate Current Mode for ELAC1")); return;
	}

	if (m_ValueLA1 > 250)
	{
		pView->RA_DispMsg(_T("ERROR : ELAC1 current range [-250 - 250] exceed, cannot move")); return;
	}
	if (m_SelectDirectionLA1 == "Up")
	{
		m_ValueLA1 = -m_ValueLA1;
	}

	if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt4, m_ValueLA1, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting Current for ELAC1 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting Current for ELAC1 failed")); return;
	}

	while (1)
	{
		pView->Update_All_Positions();

		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt4, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ELAC1"));
				pView->RA_DispMsg(_T("ERROR: Unable to quickstop ELAc1"));
				return;
			}

			break;
		}
	}

	DeleteObject(pDoc); DeleteObject(pView);
}


HBRUSH CLA01Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr;

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(49, 0, 98));

		CFont* m_pFont = new CFont();
		m_pFont->CreatePointFont(80, _T("Times New Roman"));
		pDC->SelectObject(m_pFont);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);

	}

	else
	{
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	
	return hbr;
}


void CLA01Dlg::OnBnClickedNext()
{
	// TODO: Add your control notification handler code here
	

		C6DOFPCMView *pView;
		pView = pView->GetView();
		if (!pView)
		{
			AfxMessageBox("ERROR: Unable to get View pointer");
			return;
		}

		pView->ShowWindowNumber(2);

		
	
	
		DeleteObject(pView);
	
}



void CLA01Dlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
//	delete this;
}


void CLA01Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialog::OnPaint() for painting messages

	/*CRect RECT; CWnd* pWnd;

	{
		this->GetClientRect(&RECT);
		CDC MemDC;
		CBitmap tiledImage;
		MemDC.CreateCompatibleDC(&dc); tiledImage.LoadBitmapA(IDB_DlgBkgd);
		tiledImage.LoadBitmapA(IDB_DlgBkgd);
		MemDC.SelectObject(&tiledImage);
		dc.BitBlt(0, 0, RECT.Width(), RECT.Height(), &MemDC, 0, 0, SRCCOPY);
		MemDC.DeleteDC();
		DeleteObject(tiledImage);
	}*/

	DeleteDC(dc);
}
