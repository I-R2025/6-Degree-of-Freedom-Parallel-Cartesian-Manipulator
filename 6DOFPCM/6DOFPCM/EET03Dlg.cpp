// EET03Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "6DOFPCM.h"
#include "EET03Dlg.h"
#include "afxdialogex.h"
#include "6DOFPCMView.h"

#include <Windows.h>
#include "EposPCmd_Comm.h"
#include "EposPCmd_Drive.h"
#include "EposPCmd_Plc.h"

// CEET03Dlg dialog

IMPLEMENT_DYNAMIC(CEET03Dlg, CDialog)

CEET03Dlg::CEET03Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EET03_DLG, pParent)
	, m_SelectedSpeed_PM(_T(""))
	, m_cstrFLUpdPw(_T(""))
	, m_PM_Value(0)
	, m_Select_PM_Mode(_T(""))
	, m_Select_PM_direction(_T(""))
	, m_Number_of_Rev(0)
	, m_Select_Direction_ETC3(_T(""))
	, m_select_tool(_T(""))
	, m_Enter_Value_CTC(0)
	, m_Select_Direction_CTC(_T(""))
	, m_PM_Selected_Location(_T(""))
{

}

CEET03Dlg::~CEET03Dlg()
{
	
}

void CEET03Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_CBString(pDX, IDC_COMBO1, m_SelectedSpeed_PM);
	//  DDX_Control(pDX, IDC_Move_PM, m_move);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit, m_step1);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit2, m_step2);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit3, m_step3);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit5, m_step3);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit3, m_step4);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit4, m_step5);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit6, m_step6);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit7, m_step11);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit8, m_step12);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit9, m_step14);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit10, m_step15);
	//  DDX_Control(pDX, IDC_Update_Location_File, m_updateFL);
	//  DDX_Control(pDX, IDC_Reset_Location_File, m_resetFL);
	//  DDX_Control(pDX, IDC_BUTTON9, m_st_ss);
	//  DDX_Control(pDX, IDC_BUTTON10, m_st_bs);
	//  DDX_Control(pDX, IDC_BUTTON149, m_st_sn);
	//  DDX_Control(pDX, IDC_BUTTON11, m_st_bn);
	//  DDX_Control(pDX, IDC_BUTTON6, m_st_se);
	//  DDX_Control(pDX, IDC_BUTTON7, m_st_sw);
	//  DDX_Control(pDX, IDC_BUTTON5, m_st_be);
	//  DDX_Control(pDX, IDC_BUTTON8, m_st_bw);
	//  DDX_Control(pDX, IDC_BUTTON151, m_st_bu);
	//  DDX_Control(pDX, IDC_BUTTON150, m_st_su);
	//  DDX_Control(pDX, IDC_BUTTON157, m_st_sd);
	//  DDX_Control(pDX, IDC_BUTTON15, m_st_bd);
	//  DDX_Control(pDX, IDC_Move_PmFT, m_ft_movePM);
	//  DDX_Control(pDX, IDC_Move_ELAC2FT2, m_ft_moveSM);
	//  DDX_Control(pDX, IDC_Move_ELAC2FT, m_ft_move_tool);
	DDX_Text(pDX, IDC_EDIT3, m_cstrFLUpdPw);
	DDX_Text(pDX, IDC_EDIT4, m_PM_Value);
	DDX_CBString(pDX, IDC_COMBO3, m_Select_PM_Mode);
	//  DDX_CBString(pDX, IDC_COMBO4, m_Select_PM_Direction);
	DDX_CBString(pDX, IDC_COMBO1, m_SelectedSpeed_PM);
	DDX_CBString(pDX, IDC_COMBO4, m_Select_PM_direction);
	DDX_Text(pDX, IDC_EDIT6, m_Number_of_Rev);
	DDX_CBString(pDX, IDC_COMBO7, m_Select_Direction_ETC3);
	DDX_CBString(pDX, IDC_COMBO2, m_select_tool);
	DDX_Text(pDX, IDC_EDIT5, m_Enter_Value_CTC);
	DDX_CBString(pDX, IDC_COMBO6, m_Select_Direction_CTC);
	//  DDX_Control(pDX, IDC_Next, m_next);
	DDX_Text(pDX, IDC_EDIT1, m_PM_Selected_Location);
	DDX_Control(pDX, IDC_Move_PM, m_move);
	DDX_Control(pDX, IDC_Update_Location_File, m_updateFL);
	DDX_Control(pDX, IDC_Reset_Location_File, m_resetFL);
	DDX_Control(pDX, IDC_Move_PmFT, m_ft_movePM);
	DDX_Control(pDX, IDC_Move_ELAC2FT2, m_ft_moveSM);
	DDX_Control(pDX, IDC_Move_ELAC2FT, m_ft_move_tool);
	DDX_Control(pDX, IDC_MoveLA2tosafelimit2, m_step1);
	DDX_Control(pDX, IDC_MoveLA2tosafelimit5, m_step2);
	DDX_Control(pDX, IDC_MoveLA2tosafelimit3, m_step3);
	DDX_Control(pDX, IDC_MoveLA2tosafelimit, m_step4);
	DDX_Control(pDX, IDC_MoveLA2tosafelimit8, m_step5);
}


BEGIN_MESSAGE_MAP(CEET03Dlg, CDialog)
	ON_BN_CLICKED(IDC_Move_PM, &CEET03Dlg::OnBnClickedMovePm)
	ON_BN_CLICKED(IDC_MoveLA2tosafelimit, &CEET03Dlg::OnBnClickedMovela2tosafelimit)
	ON_BN_CLICKED(IDC_MoveLA2tosafelimit2, &CEET03Dlg::OnBnClickedMovela2tosafelimit2)
	ON_BN_CLICKED(IDC_MoveLA2tosafelimit5, &CEET03Dlg::OnBnClickedMovela2tosafelimit5)
	ON_BN_CLICKED(IDC_MoveLA2tosafelimit3, &CEET03Dlg::OnBnClickedMovela2tosafelimit3)
	ON_BN_CLICKED(IDC_MoveLA2tosafelimit6, &CEET03Dlg::OnBnClickedMovela2tosafelimit6)
	ON_BN_CLICKED(IDC_MoveLA2tosafelimit8, &CEET03Dlg::OnBnClickedMovela2tosafelimit8)
	ON_BN_CLICKED(IDC_MoveLA2tosafelimit9, &CEET03Dlg::OnBnClickedMovela2tosafelimit9)
	ON_BN_CLICKED(IDC_BUTTON9, &CEET03Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CEET03Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON6, &CEET03Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CEET03Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CEET03Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CEET03Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON149, &CEET03Dlg::OnBnClickedButton149)
	ON_BN_CLICKED(IDC_BUTTON11, &CEET03Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON151, &CEET03Dlg::OnBnClickedButton151)
	ON_BN_CLICKED(IDC_BUTTON150, &CEET03Dlg::OnBnClickedButton150)
	ON_BN_CLICKED(IDC_BUTTON157, &CEET03Dlg::OnBnClickedButton157)
	ON_BN_CLICKED(IDC_BUTTON15, &CEET03Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_Move_PmFT, &CEET03Dlg::OnBnClickedMovePmft)
	ON_BN_CLICKED(IDC_Move_ELAC2FT2, &CEET03Dlg::OnBnClickedMoveElac2ft2)
	ON_BN_CLICKED(IDC_Move_ELAC2FT, &CEET03Dlg::OnBnClickedMoveElac2ft)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Update_Location_File, &CEET03Dlg::OnBnClickedUpdateLocationFile)
	ON_BN_CLICKED(IDC_Reset_Location_File, &CEET03Dlg::OnBnClickedResetLocationFile)
	ON_BN_CLICKED(IDC_Next, &CEET03Dlg::OnBnClickedNext)
END_MESSAGE_MAP()


// CEET03Dlg message handlers


void CEET03Dlg::OnBnClickedMovePm()
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

	pDoc->m_iCmdCntsNS = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][0] + pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][4];
	pDoc->m_iCmdCntsEW = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][1] + pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][5];
	pDoc->m_iCmdCntsELAC3 = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][8];
	pDoc->bSelectLocFlagNS = TRUE;
	pDoc->bSelectLocFlagEW = TRUE;

	Move_EET02_to_Selected_PM_Location();

	pDoc->RA_LogEvents(_T("INFO: PM Moved to the Selected Location"));
	pView->RA_DispMsg(_T("INFO: PM Moved to the Selected Location"));
}

void CEET03Dlg::Move_EET02_to_Selected_PM_Location()
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

	if (!Select_PM_Speed())
	{
		pDoc->RA_LogEvents(_T("ERROR: Select PM speed first"));
		pView->RA_DispMsg(_T("ERROR: Select PM speed first")); return;
	}

	if (pView->PM_Ready2Move())//&& bSelectLocFlagNS && bSelectLocFlagEW)
	{
		UpdateData(TRUE);
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

	}
}

BOOL CEET03Dlg::Select_PM_Speed()
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
	if (m_SelectedSpeed_PM == "Fast") // FAST
	{
		ProfileVelocityNS = pDoc->FProfileVelocityNS;
		ProfileAccelerationNS = pDoc->FProfileAccelerationNS;
		ProfileDeccelerationNS = pDoc->FProfileDeccelerationNS;

		ProfileVelocityEW = pDoc->FProfileVelocityEW;
		ProfileAccelerationEW = pDoc->FProfileAccelerationEW;
		ProfileDeccelerationEW = pDoc->FProfileDeccelerationEW;
		return TRUE;
	}

	if (m_SelectedSpeed_PM == "Medium") // MEDIUM
	{
		ProfileVelocityNS = pDoc->MProfileVelocityNS;
		ProfileAccelerationNS = pDoc->MProfileAccelerationNS;
		ProfileDeccelerationNS = pDoc->MProfileDeccelerationNS;

		ProfileVelocityEW = pDoc->MProfileVelocityEW;
		ProfileAccelerationEW = pDoc->MProfileAccelerationEW;
		ProfileDeccelerationEW = pDoc->MProfileDeccelerationEW;
		return TRUE;
	}

	if (m_SelectedSpeed_PM == "Slow") // SLOW
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


void CEET03Dlg::OnBnClickedMovela2tosafelimit()
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt8, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set CTC operation mode to profile position mode"));
		pView->RA_DispMsg(_T("ERROR: Unable to set CTC operation mode to profile position mode")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of CTC controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of CTC controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for CTC"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for CTC")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt8, 3500, 3000, 3000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for CTC failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for CTC failed")); return;
	}

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt8, -5600000, TRUE, TRUE, &(pDoc->dwErrorCode)))	// Opening of Chuck					
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for CTC failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for CTC failed")); return;
	}

	if (!(pView->Update_CTC_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update CTC Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update CTC Current Position")); return;
	}


}


void CEET03Dlg::OnBnClickedMovela2tosafelimit2()
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC3")); return;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set disable state"));
		pView->RA_DispMsg(_T("ERROR: Unable to set disable state")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 3000, 2500, 2500, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed")); return;
	}

	//pDoc->m_iCmdCntsELAC3 = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][8];
	//ptargetpositionELAC3 = -2950000;

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, -6200000, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed")); return;
	}
	if (!pView->Update_LA3_Position())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 3 Current Position")); return;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set disable state"));
		pView->RA_DispMsg(_T("ERROR: Unable to set disable state")); return;
	}

	if (!VCM_DisablePositionWindow(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to  disable position Window"));
		pView->RA_DispMsg(_T("ERROR: Unable to  disable position Window")); return;
	}

	


}


void CEET03Dlg::OnBnClickedMovela2tosafelimit5()
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

	pDoc->pOperationMode = OMD_CURRENT_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt8, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation mode of CTC to current mode"));
		pView->RA_DispMsg(_T("ERROR: Unable to set Operation mode of CTC to current mode")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of CTC failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of CTC failed")); return;
	}

	if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unbable to activate Current Mode for CTC"));
		pView->RA_DispMsg(_T("ERROR: Unbable to activate Current Mode for CTC")); return;
	}

	if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt8, 350, &(pDoc->dwErrorCode)))
	{
		pView->RA_DispMsg(_T("ERROR: Setting Current for CTC failed"));
		pDoc->RA_LogEvents(_T("ERROR: Setting Current for CTC failed")); return;
	}

	Sleep(200);
	pDoc->RA_LogEvents(_T("OK: ET2 moved in Current mode"));
	pDoc->bMoveWithCurFlagCTC = TRUE;



	while (1)
	{
		// Check the  Movement State of CTC 

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt8, &pDoc->bMovingFlagCTC, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read CTC movement state"));
			pView->RA_DispMsg(_T("ERROR: Unable to read CTC movement state")); return;
		}

		/*if (!(pView->LA_LimitSwitches_Status()))
		{
		pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		pView->RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
		return;
		}*/

		// Check the Status of CTC Controller

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt8, &pDoc->bCTC, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get state of CTC controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get state of CTC controller")); return;
		}

		// Check Position of CTC

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt8, &pDoc->pPositionIsCTC, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of CTC"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of CTC")); return;
		}

		// Display and Update the position Status of CTC controller 

		pView->Display_Motion_Status();
		

		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop CTC"));
				pView->RA_DispMsg(_T("ERROR: Unable to quickstop CTC"));
				return;
			}

			break;
		}

		// Check average velocity of LA1

		if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt8, &pDoc->pVelocityIsAveragedCTC, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
			pView->RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return;
		}

		if (abs(pDoc->pVelocityIsAveragedCTC) < 10)
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to Quick Stop"));
				AfxMessageBox((_T("ERROR: Unable to Quick Stop CTC"), _T("PRESS EMERGENCY BUTTON")), MB_ICONERROR); return;
			}
			break;
		}
	}

	Sleep(200);

	/*if (!(pView->LA_LimitSwitches_Status()))
	{
	pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
	pView->RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
	return;
	}*/

	// Check the Status of CTC Controller

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt8, &pDoc->bCTC, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get state of CTC controller"));
		pView->RA_DispMsg(_T("ERROR: Unable to get state of CTC controller")); return;
	}

	// Check Position of CTC

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt8, &pDoc->pPositionIsCTC, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of CTC"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of CTC")); return;
	}

	// Display the Movement State of CTC 

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt8, &pDoc->bMovingFlagCTC, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read CTC movement state"));
		pView->RA_DispMsg(_T("ERROR: Unable to read CTC movement state")); return;
	}

	// Display and Update the position Status of CTC controller

	pView->Display_Motion_Status();
	

}


void CEET03Dlg::OnBnClickedMovela2tosafelimit3()
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

	// Give 10 turns (Close Driving Nut) to ETC3 in PPM and in synchronization move LA3 in MEM 10 mm upward


	// Start Mster Encoder Mode

	// Enable ETC3 in PPM

	pDoc->m_UserInputPolarity = -1;
	pDoc->MaxVelocity = 3000;
	pDoc->MaxAcceleration = 5000;

	DWORD ProfileVelocity, ProfileAcceleration, ProfileDecceleration;
	ProfileVelocity = 600;
	ProfileAcceleration = 50179;
	ProfileDecceleration = 50179;

	BOOL Absolute, Immediately;
	Absolute = TRUE;
	Immediately = TRUE;

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to Activate Master Device"));
		pView->RA_DispMsg(_T("Error: Unable to Activate Master Device")); return;
	}

	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt9, ProfileVelocity, ProfileAcceleration, ProfileDecceleration, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to Set Position profile"));
		pView->RA_DispMsg(_T("Error: Unable to Set Position profile"));
		return;
	}
	if (!VCM_SetEnableState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Master Device not Enabled"));
		pView->RA_DispMsg(_T("Error: Master Device not Enabled"));
		return;
	}

	// Enable ELAC3 in MEM

	pDoc->pOperationMode = OMD_MASTER_ENCODER_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode of ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to set Operation Mode of ELAC3"));
		return;
	}

	if (!VCM_ActivateMasterEncoderMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to Activate Slave Device"));
		pView->RA_DispMsg(_T("Error: Unable to Activate Slave Device"));
		return;
	}

	if (!VCM_SetMasterEncoderParameter(pDoc->hDriveHandleExt6, 2045, 10000, 0, pDoc->MaxVelocity, pDoc->MaxAcceleration, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to assign slave device parameters"));
		pView->RA_DispMsg(_T("Error: Unable to assign slave device parameters"));
		return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Slave Device not Enabled"));
		pView->RA_DispMsg(_T("Error: Slave Device not Enabled"));
		return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
		return;
	}

	int Number_of_turns;
	Number_of_turns = 27;

	ptargetpositionETC3 = pDoc->pPositionIsETC3 - (Number_of_turns * 179667);

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt9, ptargetpositionETC3, Absolute, Immediately, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to Move ETC3 to desired position"));
		pView->RA_DispMsg(_T("Error: Unable to Move ETC3 to desired position"));
		return;
	}

	// Update ELAC3 and ETC3 position


	if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
		pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
		return;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
		pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
		return;
	}

	pDoc->startposetc3 = abs(pDoc->pPositionIsETC3);
	pView->Display_Motion_Status();
	

	while (pDoc->bMovingFlagETC3 == 0)
	{
		// Display Position and Motion Status of ELAC3 and ETC3

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
			return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
			return;
		}

		pDoc->notetc3 = (abs(pDoc->pPositionIsETC3)) - (pDoc->startposetc3);
		pDoc->notetc3 = pDoc->notetc3 / 179667;
		pView->Display_Motion_Status();
		

		Sleep(100);

		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop LA3"));
				pView->RA_DispMsg(_T("ERROR: Unable to quickstop LA3"));
				return;
			}

			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ETC3"));
				pView->RA_DispMsg(_T("ERROR: Unable to quickstop ETC3"));
				return;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
				pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
				return;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
				pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
				return;
			}

			pView->Display_Motion_Status();

			break;
		}

		// Check and Display Status of ELAC3 and ETC3 Controllers

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			return;
		}

		if (pDoc->bELAC3 == TRUE)
		{
			pView->Display_Motion_Status();
			 break;
		}

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
			return;
		}

		if (pDoc->bETC3 == TRUE)
		{
			pView->Display_Motion_Status();
			 break;
		}

		// Check Movement State of ELAC3 and ETC3 

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return;
		}
	}

	Sleep(200);

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
		return;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
		pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
		return;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
		pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
		return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
		return;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
		pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
		return;
	}

//	if (pDoc->bMovingFlagETC3 == TRUE)
//	{
//		pDoc->bMovingFlagELAC3 = TRUE;
//	}
//	else
//	{
		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return;
		}
//	}

	pView->Display_Motion_Status();
	
}





void CEET03Dlg::OnBnClickedMovela2tosafelimit6()
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

	
		// TODO: Add your control notification handler code here

		if (!pView->RaHomeelac3())
		{
			pDoc->RA_LogEvents(_T("ERROR: LA3 Homing not successful"));
			pView->RA_DispMsg(_T("ERROR: LA3 Homing not successful"));
			return;
		}

	
/*		if (!pView->RaHomectc())
		{
			pDoc->RA_LogEvents(_T("ERROR: CTC Homing not successful"));
			pView->RA_DispMsg(_T("ERROR: CTC Homing not successful"));
			return;
		}
	*/
}


void CEET03Dlg::OnBnClickedMovela2tosafelimit8()
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC3")); return;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set disable state"));
		pView->RA_DispMsg(_T("ERROR: Unable to set disable state")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 2500, 1500, 1500, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed")); return;
	}

	ptargetpositionELAC3 = -5750000;

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, -8600000, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed")); return;
	}
	if (!pView->Update_LA3_Position())
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 3 Current Position")); return;
	}

	if (!VCM_SetDisableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set disable state"));
		pView->RA_DispMsg(_T("ERROR: Unable to set disable state")); return;
	}

	if (!VCM_DisablePositionWindow(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to  disable position Window"));
		pView->RA_DispMsg(_T("ERROR: Unable to  disable position Window")); return;
	}

	

}


void CEET03Dlg::OnBnClickedMovela2tosafelimit9()

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

	// Give 10 turns (Close Driving Nut) to ETC3 in PPM and in synchronization move LA3 in MEM 10 mm upward


	// Start Mster Encoder Mode

	// Enable ETC3 in PPM

	if (!VCM_ResetDevice(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))						// Library Function for Reseting Internal Drive of ETC3
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to reset ETC3 controller"));
		pView->RA_DispMsg(_T("ERROR: Unable to reset ETC# controller")); return;
	}

	pDoc->m_UserInputPolarity = -1;
	pDoc->MaxVelocity = 3000;
	pDoc->MaxAcceleration = 5000;

	DWORD ProfileVelocity, ProfileAcceleration, ProfileDecceleration;
	ProfileVelocity = 600;
	ProfileAcceleration = 50179;
	ProfileDecceleration = 50179;

	BOOL Absolute, Immediately;
	Absolute = TRUE;
	Immediately = TRUE;

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to Activate Master Device"));
		pView->RA_DispMsg(_T("Error: Unable to Activate Master Device")); return;
	}

	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt9, ProfileVelocity, ProfileAcceleration, ProfileDecceleration, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to Set Position profile"));
		pView->RA_DispMsg(_T("Error: Unable to Set Position profile"));
		return;
	}
	if (!VCM_SetEnableState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Master Device not Enabled"));
		pView->RA_DispMsg(_T("Error: Master Device not Enabled"));
		return;
	}

	// Enable ELAC3 in MEM

	pDoc->pOperationMode = OMD_MASTER_ENCODER_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode of ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to set Operation Mode of ELAC3"));
		return;
	}

	if (!VCM_ActivateMasterEncoderMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to Activate Slave Device"));
		pView->RA_DispMsg(_T("Error: Unable to Activate Slave Device"));
		return;
	}

	if (!VCM_SetMasterEncoderParameter(pDoc->hDriveHandleExt6, 2045, 10000, 0, pDoc->MaxVelocity, pDoc->MaxAcceleration, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to assign slave device parameters"));
		pView->RA_DispMsg(_T("Error: Unable to assign slave device parameters"));
		return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Slave Device not Enabled"));
		pView->RA_DispMsg(_T("Error: Slave Device not Enabled"));
		return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
		return;
	}

	ptargetpositionETC3 = pDoc->pPositionIsETC3 + 44920;

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt9, ptargetpositionETC3, Absolute, Immediately, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Error: Unable to Move ETC3 to desired position"));
		pView->RA_DispMsg(_T("Error: Unable to Move ETC3 to desired position"));
		return;
	}

	// Update ELAC3 and ETC3 position


	if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
		pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
		return;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
		pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
		return;
	}
	pDoc->startposetc3 = abs(pDoc->pPositionIsETC3);
	pView->Display_Motion_Status();


	while (pDoc->bMovingFlagETC3 == 0)
	{
		// Display Position and Motion Status of ELAC3 and ETC3

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
			return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
			return;
		}

		pDoc->notetc3 = (abs(pDoc->pPositionIsETC3)) - (pDoc->startposetc3);
		pDoc->notetc3 = pDoc->notetc3 / 179667;
		pView->Display_Motion_Status();
		Sleep(100);
		
		if (GetAsyncKeyState(VK_END))
		{
			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop LA3"));
				pView->RA_DispMsg(_T("ERROR: Unable to quickstop LA3"));
				return;
			}

			if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ETC3"));
				pView->RA_DispMsg(_T("ERROR: Unable to quickstop ETC3"));
				return;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
				pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
				return;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
				pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
				return;
			}

			pView->Display_Motion_Status();

			break;
		}

		// Check and Display Status of ELAC3 and ETC3 Controllers

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			return;
		}

		if (pDoc->bELAC3 == TRUE)
		{
			pView->Display_Motion_Status();
			break;
		}

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
			return;
		}

		if (pDoc->bETC3 == TRUE)
		{
			pView->Display_Motion_Status();
			 break;
		}

		// Check Movement State of ELAC3 and ETC3 

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return;
		}
	}
	Sleep(200);

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
		return;
	}

	if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
		pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
		return;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
		pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
		return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
		return;
	}

	if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
		pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
		return;
	}

	if (pDoc->bMovingFlagETC3 == TRUE)
	{
		pDoc->bMovingFlagELAC3 = TRUE;
	}
	else
	{
		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return;
		}
	}

	pView->Display_Motion_Status();
	

}





void CEET03Dlg::OnBnClickedButton9()
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
}


void CEET03Dlg::OnBnClickedButton10()
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
	//	if (pView->PM_Ready2Move())
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
	//	else
	{
		//		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		//		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}
}


BOOL CEET03Dlg::OnInitDialog()
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
	

	UpdateData(FALSE);

	NS_FINE_INC = 2500;//Fine Step for Motion along NS & EW
	EW_FINE_INC = 2500;
	NS_COARSE_INC = 10000;//Coarse Step for Motion along NS & EW
	EW_COARSE_INC = 10000;

	LA3_FINE_INC = 24500;//Fine Step for Motion along z-axix LA2
	LA3_COARSE_INC = 500000; // 49000;//Fine Step for Motion along z-axis LA2

	m_move.LoadStdImage(IDB_move_PM, ("PNG"));
	m_move.SetToolTipText(_T("Move PM to the selected location"), TRUE);
	m_updateFL.LoadStdImage(IDB_UpdateList, ("PNG"));
	m_updateFL.SetToolTipText(_T("Update the Location"), TRUE);
	m_resetFL.LoadStdImage(IDB_ResetLocations, ("PNG"));
	m_resetFL.SetToolTipText(_T("Reset the Location"), TRUE);
/*	m_st_ss.LoadStdImage(IDB_Move_UP, ("PNG"));
	m_st_ss.SetToolTipText(_T("Move PM 1mm towards South"), TRUE);
	m_st_bs.LoadStdImage(IDB_st_bs, ("PNG"));
	m_st_bs.SetToolTipText(_T("Move PM 2mm towards South"), TRUE);
	m_st_sn.LoadStdImage(IDB_move_down, ("PNG"));
	m_st_sn.SetToolTipText(_T("Move PM 1mm towards North"), TRUE);
	m_st_bn.LoadStdImage(IDB_st_bn, ("PNG"));
	m_st_bn.SetToolTipText(_T("Move PM 2mm towards North"), TRUE);
	m_st_sw.LoadStdImage(IDB_move_right, ("PNG"));
	m_st_sw.SetToolTipText(_T("Move PM 1mm towards West"), TRUE);
	m_st_bw.LoadStdImage(IDB_st_bw, ("PNG"));
	m_st_bw.SetToolTipText(_T("Move PM 2mm towards West"), TRUE);
	m_st_se.LoadStdImage(IDB_move_left, ("PNG"));
	m_st_se.SetToolTipText(_T("Move PM 1mm towards East"), TRUE);
	m_st_be.LoadStdImage(IDB_st_be, ("PNG"));
	m_st_be.SetToolTipText(_T("Move PM 2mm towards East"), TRUE);
	m_st_su.LoadStdImage(IDB_LA_up, ("PNG"));
	m_st_su.SetToolTipText(_T("Move ELAC2 1mm in upward direction"), TRUE);
	m_st_bu.LoadStdImage(IDB_LA_upward, ("PNG"));
	m_st_bu.SetToolTipText(_T("Move ELAC2 2mm in upward direction"), TRUE);
	m_st_sd.LoadStdImage(IDB_LA_Down, ("PNG"));
	m_st_sd.SetToolTipText(_T("Move ELAC2 1mm in downward direction"), TRUE);
	m_st_bd.LoadStdImage(IDB_LA_downward, ("PNG"));
	m_st_bd.SetToolTipText(_T("Move ELAC2 2mm in downward direction"), TRUE);*/
	m_ft_movePM.LoadStdImage(IDB_move, ("PNG"));
	m_ft_moveSM.LoadStdImage(IDB_move, ("PNG"));
	m_ft_move_tool.LoadStdImage(IDB_move, ("PNG"));
	m_step1.LoadStdImage(IDB_step1, ("PNG"));
	m_step1.SetToolTipText(_T("Move ELAC3 to safe limit"), TRUE);
	m_step2.LoadStdImage(IDB_step2, ("PNG"));
	m_step2.SetToolTipText(_T("Grip Nut"), TRUE);
	m_step3.LoadStdImage(IDB_step3, ("PNG"));
	m_step3.SetToolTipText(_T("Close Drive Nut"), TRUE);
	m_step4.LoadStdImage(IDB_step4, ("PNG"));
	m_step4.SetToolTipText(_T("Leave Drive Nut"), TRUE);
	m_step5.LoadStdImage(IDB_step5, ("PNG"));
	m_step5.SetToolTipText(_T("Move ELAC3 to safe limit"), TRUE);
/*	m_step6.LoadStdImage(IDB_laststep, ("PNG"));
	m_step6.SetToolTipText(_T("Move ELAC3 and CTC to parking position"), TRUE);
	m_step11.LoadStdImage(IDB_step1, ("PNG"));
	m_step11.SetToolTipText(_T("Open CTC"), TRUE);
	m_step12.LoadStdImage(IDB_step2, ("PNG"));
	m_step12.SetToolTipText(_T("Move ELAC3 to safe limit"), TRUE);
	m_step14.LoadStdImage(IDB_step4, ("PNG"));
	m_step14.SetToolTipText(_T("Close Ring Nut"), TRUE);
	m_step15.LoadStdImage(IDB_step5, ("PNG"));
	m_step15.SetToolTipText(_T("Leave Ring Nut"), TRUE);
	m_next.LoadStdImage(IDB_complete, ("PNG"));
	*/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CEET03Dlg::OnBnClickedButton6()
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
}


void CEET03Dlg::OnBnClickedButton5()
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
}


void CEET03Dlg::OnBnClickedButton7()
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
}


void CEET03Dlg::OnBnClickedButton8()
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
}


void CEET03Dlg::OnBnClickedButton149()
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
}


void CEET03Dlg::OnBnClickedButton11()
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
}


void CEET03Dlg::OnBnClickedButton151()
{
	// TODO: Add your control notification handler code here

	//UpdateData(TRUE);
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC3")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 1600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of LA3"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of LA3")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, (pDoc->pPositionIsLA3) - LA3_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed")); return;
	}

	/*	if (!VCM_MoveToPosition(hDriveHandleExt4,-3500000, TRUE, TRUE, &dwErrorCode))
	{
	AfxMessageBox(_T("ERROR: Move to position for ELAC1 failed")); return FALSE;
	}
	*/
	if (!(pView->Update_LA3_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 3 Current Position")); return;
	}
}


void CEET03Dlg::OnBnClickedButton150()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC3")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of LA3"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of LA3")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, (pDoc->pPositionIsLA3) - LA3_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed")); return;
	}

	/*	if (!VCM_MoveToPosition(hDriveHandleExt4,-3500000, TRUE, TRUE, &dwErrorCode))
	{
	AfxMessageBox(_T("ERROR: Move to position for ELAC1 failed")); return FALSE;
	}
	*/
	if (!(pView->Update_LA3_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 3 Current Position")); return;
	}

}


void CEET03Dlg::OnBnClickedButton157()
{
	// TODO: Add your control notification handler code here

	//	UpdateData(TRUE);
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC3")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of LA3"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of LA3")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000
	if (abs(pDoc->pPositionIsLA3) <= 25000)
	{
		pView->RA_DispMsg(_T("ERROR : You have reached Lower Limit (Home Switch), LA3 can not move")); return;
	}
	else
	{
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, (pDoc->pPositionIsLA3) + LA3_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed")); return;
		}

		if (!(pView->Update_LA3_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 3 Current Position")); return;
		}
	}
}


void CEET03Dlg::OnBnClickedButton15()

{
	// TODO: Add your control notification handler code here

	//UpdateData(TRUE);
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC3")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC3")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt6, 1800, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC3 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of LA3"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of LA3")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	//	if (abs(pDoc->pPositionIsLA3) <= 50000)
	//	{
	//		pView->RA_DispMsg(_T("ERROR : You have reached Lower Limit (Home Switch), LA3 can not move")); return;
	//	}
	//	else
	//	{
	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt6, (pDoc->pPositionIsLA3) + LA3_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC3 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC3 failed")); return;
	}

	if (!(pView->Update_LA3_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 3 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 3 Current Position")); return;
	}
	//	}
}


void CEET03Dlg::OnBnClickedMovePmft()
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

//	if (pView->PM_Ready2Move())
	{
		UpdateData(TRUE);
		if (m_Select_PM_Mode == "Profile Velocity Mode" && m_Select_PM_direction == "West")
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

			if (!VCM_MoveWithVelocity(pDoc->hDriveHandleExt3, -(abs(m_PM_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move with velocity failed for EW"));
				pView->RA_DispMsg(_T("ERROR: Move with velocity failed for EW")); return;
			}

			while (1)
			{
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
			}

			pDoc->bMoveWithVelFlag = TRUE;

		}

		if (m_Select_PM_Mode == "Profile Velocity Mode" && m_Select_PM_direction == "East")
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

			if (!VCM_MoveWithVelocity(pDoc->hDriveHandleExt3, (abs(m_PM_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move with velocity failed for EW"));
				pView->RA_DispMsg(_T("ERROR: Move with velocity failed for EW")); return;
			}

			while (1)
			{
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
			}

			pDoc->bMoveWithVelFlag = TRUE;

		}

		if (m_Select_PM_Mode == "Profile Velocity Mode" && m_Select_PM_direction == "North")
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

			if (!VCM_MoveWithVelocity(pDoc->hDriveHandleExt2, -(abs(m_PM_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move with velocity failed for NS"));
				pView->RA_DispMsg(_T("ERROR: Move with velocity failed for NS")); return;
			}

			while (1)
			{
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
			}


			pDoc->bMoveWithVelFlag = TRUE;

		}

		if (m_Select_PM_Mode == "Profile Velocity Mode" && m_Select_PM_direction == "South")
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

			if (!VCM_MoveWithVelocity(pDoc->hDriveHandleExt2, (abs(m_PM_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move with velocity failed for NS"));
				pView->RA_DispMsg(_T("ERROR: Move with velocity failed for NS")); return;
			}

			while (1)
			{
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
			}

			pDoc->bMoveWithVelFlag = TRUE;

		}

		if (m_Select_PM_Mode == "Current Mode" && m_Select_PM_direction == "South")
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

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt2, abs(m_PM_Value), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for NS failed")); return;
			}

			while (1)
			{
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
			}
		}

		if (m_Select_PM_Mode == "Current Mode" && m_Select_PM_direction == "North")
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

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt2, -(abs(m_PM_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for NS failed")); return;
			}

			while (1)
			{
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
			}
		}

		if (m_Select_PM_Mode == "Current Mode" && m_Select_PM_direction == "East")
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

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt3, abs(m_PM_Value), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for EW failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for EW failed")); return;
			}

			while (1)
			{
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
			}
		}

		if (m_Select_PM_Mode == "Current Mode" && m_Select_PM_direction == "West")
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

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt3, -(abs(m_PM_Value)), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for EW failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for EW failed")); return;
			}

			while (1)
			{
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
			}
		}
	}
//	else
//	{
//		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
//		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
//	}
}


void CEET03Dlg::OnBnClickedMoveElac2ft2()
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

	if (m_Select_Direction_ETC3 == "Close")
	{
		// Start Mster Encoder Mode

		// ETC3 parameters initialization

		pDoc->m_UserInputPolarity = 0;
		pDoc->MaxVelocity = 3000;
		pDoc->MaxAcceleration = 5000;

		DWORD ProfileVelocity, ProfileAcceleration, ProfileDecceleration;
		ProfileVelocity = 800;
		ProfileAcceleration = 50179;
		ProfileDecceleration = 50179;

		BOOL Absolute, Immediately;
		Absolute = TRUE;
		Immediately = TRUE;

		if (pDoc->pPositionIsETC3 >= 5000000)
		{
			pDoc->pPositionIsETC3 = 0;
		}
		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to Activate Master Device"));
			pView->RA_DispMsg(_T("Error: Unable to Activate Master Device")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt9, ProfileVelocity, ProfileAcceleration, ProfileDecceleration, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to Set Position profile"));
			pView->RA_DispMsg(_T("Error: Unable to Set Position profile"));
			return;
		}
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Master Device not Enabled"));
			pView->RA_DispMsg(_T("Error: Master Device not Enabled"));
			return;
		}

		// Enable ELAC3 in MEM

		pDoc->pOperationMode = OMD_MASTER_ENCODER_MODE;

		if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode of ELAC3"));
			pView->RA_DispMsg(_T("ERROR: Unable to set Operation Mode of ELAC3"));
			return;
		}

		if (!VCM_ActivateMasterEncoderMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to Activate Slave Device"));
			pView->RA_DispMsg(_T("Error: Unable to Activate Slave Device"));
			return;
		}

		if (!VCM_SetMasterEncoderParameter(pDoc->hDriveHandleExt6, 2045, 10000, pDoc->m_UserInputPolarity, pDoc->MaxVelocity, pDoc->MaxAcceleration, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to assign slave device parameters"));
			pView->RA_DispMsg(_T("Error: Unable to assign slave device parameters"));
			return;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Slave Device not Enabled"));
			pView->RA_DispMsg(_T("Error: Slave Device not Enabled"));
			return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of ETC3"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of ETC3")); return;
		}

		ptargetpositionETC3 = (pDoc->pPositionIsETC3) - (LONG)(m_Number_of_Rev * 179667);

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt9, ptargetpositionETC3, Absolute, Immediately, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to Move ETC3 to desired position"));
			pView->RA_DispMsg(_T("Error: Unable to Move ETC3 to desired position"));
			return;
		}

		// Update ELAC3 and ETC3 position
		

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Movement State"));
			pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Movement State"));
			return;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return;
		}
		pDoc->startposetc3 = abs(pDoc->pPositionIsETC3);
		pView->Display_Motion_Status();
		

		while (pDoc->bMovingFlagETC3 == 0)
		{
			// Display Position and Motion Status of ELAC3 and ETC3

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
				return;
			}

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
				return;
			}

			pDoc->notetc3 = (abs(pDoc->pPositionIsETC3)) - (pDoc->startposetc3);
			pDoc->notetc3 = pDoc->notetc3 / 179667;
			pView->Display_Motion_Status();
			
			Sleep(100);

			if (GetAsyncKeyState(VK_END))
			{
				if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop LA3"));
					pView->RA_DispMsg(_T("ERROR: Unable to quickstop LA3"));
					return;
				}

				if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ETC3"));
					pView->RA_DispMsg(_T("ERROR: Unable to quickstop ETC3"));
					return;
				}

				break;
			}

			// Check and Display Status of ELAC3 and ETC3 Controllers

			if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
				pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
				return;
			}

			if (pDoc->bELAC3 == TRUE)
			{
				pView->Display_Motion_Status();
				break;
			}

			if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
				pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
				return;
			}

			if (pDoc->bETC3 == TRUE)
			{
				pView->Display_Motion_Status();
				 break;
			}

			// Check Movement State of ELAC3 and ETC3 

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
				pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
				return;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
				pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
				return;
			}
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
			return;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return;
		}

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
			return;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return;
		}

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
			return;
		}

		pView->Display_Motion_Status();
		

	}

	if (m_Select_Direction_ETC3 == "Open")
	{
		// Start Mster Encoder Mode

		// ETC3 parameters initialization

		pDoc->m_UserInputPolarity = 0;
		pDoc->MaxVelocity = 3000;
		pDoc->MaxAcceleration = 5000;

		DWORD ProfileVelocity, ProfileAcceleration, ProfileDecceleration;
		ProfileVelocity = 600;
		ProfileAcceleration = 50179;
		ProfileDecceleration = 50179;

		BOOL Absolute, Immediately;
		Absolute = TRUE;
		Immediately = TRUE;

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to Activate Master Device"));
			pView->RA_DispMsg(_T("Error: Unable to Activate Master Device")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt9, ProfileVelocity, ProfileAcceleration, ProfileDecceleration, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to Set Position profile"));
			pView->RA_DispMsg(_T("Error: Unable to Set Position profile"));
			return;
		}
		if (!VCM_SetEnableState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Master Device not Enabled"));
			pView->RA_DispMsg(_T("Error: Master Device not Enabled"));
			return;
		}

		// Enable ELAC3 in MEM

		pDoc->pOperationMode = OMD_MASTER_ENCODER_MODE;

		if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode of ELAC3"));
			pView->RA_DispMsg(_T("ERROR: Unable to set Operation Mode of ELAC3"));
			return;
		}

		if (!VCM_ActivateMasterEncoderMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to Activate Slave Device"));
			pView->RA_DispMsg(_T("Error: Unable to Activate Slave Device"));
			return;
		}

		if (!VCM_SetMasterEncoderParameter(pDoc->hDriveHandleExt6, 2045, 10000, pDoc->m_UserInputPolarity, pDoc->MaxVelocity, pDoc->MaxAcceleration, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to assign slave device parameters"));
			pView->RA_DispMsg(_T("Error: Unable to assign slave device parameters"));
			return;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Slave Device not Enabled"));
			pView->RA_DispMsg(_T("Error: Slave Device not Enabled"));
			return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of ETC3"));
			pView->RA_DispMsg(_T("ERROR: Unable to read actual position of ETC3")); return;
		}


		ptargetpositionETC3 = (pDoc->pPositionIsETC3) + (LONG)(m_Number_of_Rev * 179667);

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt9, ptargetpositionETC3, Absolute, Immediately, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Error: Unable to Move ETC3 to desired position"));
			pView->RA_DispMsg(_T("Error: Unable to Move ETC3 to desired position"));
			return;
		}

		// Update ELAC3 and ETC3 position


		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return;
		}
		pDoc->startposetc3 = abs(pDoc->pPositionIsETC3);
		pView->Display_Motion_Status();
		
		while (pDoc->bMovingFlagETC3 == 0)
		{
			// Display Position and Motion Status of ELAC3 and ETC3

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
				return;
			}

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
				return;
			}

			pDoc->notetc3 = (abs(pDoc->pPositionIsETC3)) - (pDoc->startposetc3);
			pDoc->notetc3 = pDoc->notetc3 / 179667;
			pView->Display_Motion_Status();
			
			Sleep(100);

			if (GetAsyncKeyState(VK_END))
			{
				if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop LA3"));
					pView->RA_DispMsg(_T("ERROR: Unable to quickstop LA3"));
					return;
				}

				if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt9, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ETC3"));
					pView->RA_DispMsg(_T("ERROR: Unable to quickstop ETC3"));
					return;
				}

				break;
			}

			// Check and Display Status of ELAC3 and ETC3 Controllers

			if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
				pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
				return;
			}

			if (pDoc->bELAC3 == TRUE)
			{
				pView->Display_Motion_Status();
				 break;
			}

			if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
				pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
				return;
			}

			if (pDoc->bETC3 == TRUE)
			{
				pView->Display_Motion_Status();
				 break;
			}

			// Check Movement State of ELAC3 and ETC3 

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
				pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
				return;
			}

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
				pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
				return;
			}
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt6, &(pDoc->pPositionIsLA3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get LA3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get LA3 Current Position"));
			return;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt6, &(pDoc->bMovingFlagELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("Unable to get LA3 Movement State"));
			pView->RA_DispMsg(_T("Unable to get LA3 Movement State"));
			return;
		}

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt6, &(pDoc->bELAC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ELAC3 controller"));
			return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt9, &(pDoc->pPositionIsETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Current Position"));
			return;
		}

		if (!VCM_GetMovementState(pDoc->hDriveHandleExt9, &(pDoc->bMovingFlagETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC3 Movement State"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC3 Movement State"));
			return;
		}

		if (!VCM_GetFaultState(pDoc->hDriveHandleExt9, &(pDoc->bETC3), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get fault state of ETC3 controller"));
			pView->RA_DispMsg(_T("ERROR: Unable to get fault state of ETC3 controller"));
			return;
		}

		pView->Display_Motion_Status();
		

	}
}


void CEET03Dlg::OnBnClickedMoveElac2ft()
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
	m_Enter_Value_CTC = abs(m_Enter_Value_CTC);

	if (m_select_tool == "ELAC3")
	{
			pDoc->pOperationMode = OMD_CURRENT_MODE;

			if (!VCM_SetOperationMode(pDoc->hDriveHandleExt6, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode"));
				pView->RA_DispMsg(_T("ERROR: Unable to set Operation Mode")); return;
			}

			if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unbable to activate Current Mode for ELAC3"));
				pView->RA_DispMsg(_T("ERROR: Unbable to activate Current Mode for ELAC3")); return;
			}

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC3 failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC3 failed")); return;
			}

			if (m_Select_Direction_CTC == "Up")
			{
				m_Enter_Value_CTC = -m_Enter_Value_CTC;
			}


			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt6, m_Enter_Value_CTC, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for ELAC3 failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for ELAC3 failed")); return;
			}

			while (1)
			{
				pView->Update_All_Positions();

				if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt6, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ELAC3"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop ELAC3"));
						return;
					}

					break;
				}
			}

		
	}

	if (m_select_tool == "CTC")
	{
		
			if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unbable to activate Current Mode for CTC"));
				pView->RA_DispMsg(_T("ERROR: Unbable to activate Current Mode for CTC")); return;
			}

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of CTC failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of CTC failed")); return;
			}

			if (m_Enter_Value_CTC > 1200)
			{
				pView->RA_DispMsg(_T("ERROR : CTC current range [-1200 - 1200] exceed, cannot move")); return;
			}

			if (m_Select_Direction_CTC == "Outward")
			{
				m_Enter_Value_CTC = -m_Enter_Value_CTC;
			}

			{
				if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt8, (SHORT)m_Enter_Value_CTC, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Setting Current for CTC failed"));
					pView->RA_DispMsg(_T("ERROR: Setting Current for CTC failed")); return;
				}

				while (1)
				{
					pView->Update_All_Positions();

					if (GetAsyncKeyState(VK_END))
					{
						if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt8, &(pDoc->dwErrorCode)))
						{
							pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop CTC"));
							pView->RA_DispMsg(_T("ERROR: Unable to quickstop CTC"));
							return;
						}

						break;
					}
				}
			}
		}
	

}


BOOL CEET03Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CBrush brNew(RGB(158, 180, 214));                      // To edit the background color give desired color code here
														   //CBrush brNew(RGB(108, 140, 192));
	CBrush*poldBrush = (CBrush*)pDC->SelectObject(&brNew);
	CRect rc;
	pDC->GetClipBox(rc);
	pDC->PatBlt(0, 0, rc.Width(), rc.Height(), PATCOPY);
	pDC->SelectObject(poldBrush);
	return TRUE;
}


HBRUSH CEET03Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr;

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(RGB(158, 180, 214));
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


void CEET03Dlg::OnBnClickedUpdateLocationFile()
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
	if (m_cstrFLUpdPw == "RoboticArm")
	{
		
		//	pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][4] = pView->m_datanaylzerdlg->m_pPositionIsNS - ((pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][0]) - abs(pDoc->EET01OffsetNS));
		//	pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][5] = pView->m_datanaylzerdlg->m_pPositionIsEW - ((pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][1]) - abs(pDoc->EET01OffsetEW));
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][8] = pView->m_pPositionIsELAC3;

		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][4] = pView->m_pPositionIsNS - (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][0]);
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][5] = pView->m_pPositionIsEW - (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][1]);


		PM_WriteLocations2File();
		pDoc->RA_LogEvents(_T("INFO: Location Updated"));
		pView->RA_DispMsg(_T("INFO: Location Updated"));
		m_cstrFLUpdPw = "";
		UpdateData(FALSE);
	}
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: Incorrect Password"));
		pView->RA_DispMsg(_T("ERROR: Incorrect Password"));
	}
}


void CEET03Dlg::OnBnClickedResetLocationFile()
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
	pDoc->RA_LogEvents(_T("OK: locations file 'LocationLattice.dat' Reset"));
	pView->RA_DispMsg(_T("OK: locations file 'LocationLattice.dat' Reset"));

}

void CEET03Dlg::PM_WriteLocations2File()
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

	if (!WF.Open(_T("LocationLattice.dat"), CFile::modeCreate | CFile::modeReadWrite, &ex))
	{
		ex.ReportError();
		pDoc->RA_LogEvents(_T("ERROR: Unable to open locations file 'LocationLattice.dat'"));
		pView->RA_DispMsg(_T("ERROR: Unable to open locations file 'LocationLattice.dat'"));
		return;
	}
	CString strVar;
	UINT i, j;

	for (i = 0; i < 29; i++)
	{
		for (j = 0; j < 15; j++)
		{
			strVar.Format(_T("%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\t\t%+0.7d\r\n"), pDoc->iLocGrid[i][j][0], pDoc->iLocGrid[i][j][1], pDoc->iLocGrid[i][j][2], pDoc->iLocGrid[i][j][3], pDoc->iLocGrid[i][j][4], pDoc->iLocGrid[i][j][5], pDoc->iLocGrid[i][j][6], pDoc->iLocGrid[i][j][7], pDoc->iLocGrid[i][j][8]);
			WF.Write((LPCTSTR)strVar, strVar.GetLength());
		}
		strVar.Format(_T("\r\n\r\n"));
		WF.Write((LPCTSTR)strVar, strVar.GetLength());
	}
	WF.Close();
}

void CEET03Dlg::SelectedPosition()
{
	C6DOFPCMDoc *pDoc;
	pDoc = pDoc->GetDoc();

	if (!pDoc)
	{
		AfxMessageBox("ERROR: Unable to get document pointer");
		return;
	}
	m_PM_Selected_Location = pDoc->PM_selected_Location;

	UpdateData(FALSE);
}


void CEET03Dlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
//	delete this;
}


void CEET03Dlg::OnBnClickedNext()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMView *pView;
	pView = pView->GetView();
	if (!pView)
	{
		AfxMessageBox("ERROR: Unable to get View pointer");
		return;
	}

	pView->ShowWindowNumber(0);
}
