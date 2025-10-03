// EET02Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "6DOFPCM.h"
#include "EET02Dlg.h"
#include "afxdialogex.h"
#include "6DOFPCMView.h"

#include <Windows.h>
#include "EposPCmd_Comm.h"
#include "EposPCmd_Drive.h"
#include "EposPCmd_Plc.h"

// CEET02Dlg dialog

IMPLEMENT_DYNAMIC(CEET02Dlg, CDialog)

CEET02Dlg::CEET02Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EET02_DLG, pParent)
	, M_SelectedSpeed_PM(_T(""))
	, m_Select_LA02_Speed(_T(""))
	, m_cstrFLUpdPw(_T(""))
	, m_Select_PM_Mode(_T(""))
	, m_Select_PM_Direction(_T(""))
	, m_Direction(_T(""))
	, m_PM_Value(0)
	, m_Value(0)
	, m_select_tool(_T(""))
	, m_PM_Selected_Location(_T(""))
{

}

CEET02Dlg::~CEET02Dlg()
{
//	delete this;
}

void CEET02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, M_SelectedSpeed_PM);
	//  DDX_Control(pDX, IDC_Move_PM, m_move);
	//  DDX_Control(pDX, IDC_MoveLA2tosafelimit, m_step1);
	//  DDX_Control(pDX, IDC_RotateNut, m_step2);
	//  DDX_Control(pDX, IDC_ROTATE_ETC2, m_step3);
	//  DDX_Control(pDX, IDC_HOME_ELAC2, m_step4);
	
	//  DDX_Control(pDX, IDC_BUTTON6, m_st_se);
	//  DDX_Control(pDX, IDC_BUTTON5, m_st_be);
	//  DDX_Control(pDX, IDC_BUTTON7, m_st_sw);
	//  DDX_Control(pDX, IDC_BUTTON8, m_st_bw);
	//  DDX_Control(pDX, IDC_BUTTON9, m_st_ss);
	//  DDX_Control(pDX, IDC_BUTTON10, m_st_bs);
	//  DDX_Control(pDX, IDC_BUTTON149, m_st_sn);
	//  DDX_Control(pDX, IDC_BUTTON11, m_st_bn);
	//  DDX_Control(pDX, IDC_BUTTON150, m_st_su);
	//  DDX_Control(pDX, IDC_BUTTON157, m_st_sd);
	//  DDX_Control(pDX, IDC_BUTTON151, m_st_bu);
	//  DDX_Control(pDX, IDC_BUTTON15, m_st_bd);
	//  DDX_Control(pDX, IDC_Move_PmFT, m_ft_movePM);
	//  DDX_Control(pDX, IDC_Move_ELAC2FT, m_ft_moveelac2);
	DDX_CBString(pDX, IDC_LA01_SS, m_Select_LA02_Speed);
	DDX_Text(pDX, IDC_EDIT3, m_cstrFLUpdPw);
	DDX_CBString(pDX, IDC_COMBO3, m_Select_PM_Mode);
	DDX_CBString(pDX, IDC_COMBO4, m_Select_PM_Direction);
	DDX_CBString(pDX, IDC_COMBO6, m_Direction);
	DDX_Text(pDX, IDC_EDIT4, m_PM_Value);
	DDX_Text(pDX, IDC_EDIT5, m_Value);
	DDX_CBString(pDX, IDC_COMBO2, m_select_tool);
	DDX_Text(pDX, IDC_EDIT1, m_PM_Selected_Location);
	//  DDX_Control(pDX, IDC_Next, m_next);
	DDX_Control(pDX, IDC_Move_PM, m_move);
	DDX_Control(pDX, IDC_Update_Location_File, m_updateFL);
	DDX_Control(pDX, IDC_Reset_Location_File, m_resetFL);
	DDX_Control(pDX, IDC_Move_PmFT, m_ft_movePM);
	DDX_Control(pDX, IDC_Move_ELAC2FT, m_ft_moveelac2);
	DDX_Control(pDX, IDC_MoveLA2tosafelimit, m_step1);
	DDX_Control(pDX, IDC_RotateNut, m_step2);
	DDX_Control(pDX, IDC_ROTATE_ETC2, m_step3);
	DDX_Control(pDX, IDC_Next, m_next);
}


BEGIN_MESSAGE_MAP(CEET02Dlg, CDialog)
	ON_BN_CLICKED(IDC_Move_PM, &CEET02Dlg::OnBnClickedMovePm)
	ON_BN_CLICKED(IDC_MoveLA2tosafelimit, &CEET02Dlg::OnBnClickedMovela2tosafelimit)
	ON_BN_CLICKED(IDC_RotateNut, &CEET02Dlg::OnBnClickedRotatenut)
	ON_BN_CLICKED(IDC_ROTATE_ETC2, &CEET02Dlg::OnBnClickedRotateEtc2)
	ON_BN_CLICKED(IDC_HOME_ELAC2, &CEET02Dlg::OnBnClickedHomeElac2)
	ON_BN_CLICKED(IDC_Update_Location_File, &CEET02Dlg::OnBnClickedUpdateLocationFile)
	ON_BN_CLICKED(IDC_Reset_Location_File, &CEET02Dlg::OnBnClickedResetLocationFile)
	ON_BN_CLICKED(IDC_BUTTON6, &CEET02Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CEET02Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CEET02Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CEET02Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CEET02Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CEET02Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON149, &CEET02Dlg::OnBnClickedButton149)
	ON_BN_CLICKED(IDC_BUTTON11, &CEET02Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON151, &CEET02Dlg::OnBnClickedButton151)
	ON_BN_CLICKED(IDC_BUTTON150, &CEET02Dlg::OnBnClickedButton150)
	ON_BN_CLICKED(IDC_BUTTON157, &CEET02Dlg::OnBnClickedButton157)
	ON_BN_CLICKED(IDC_BUTTON15, &CEET02Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_Move_PmFT, &CEET02Dlg::OnBnClickedMovePmft)
	ON_BN_CLICKED(IDC_Move_ELAC2FT, &CEET02Dlg::OnBnClickedMoveElac2ft)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Next, &CEET02Dlg::OnBnClickedNext)
END_MESSAGE_MAP()


// CEET02Dlg message handlers


void CEET02Dlg::OnBnClickedMovePm()
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



	pDoc->m_iCmdCntsNS = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][0] + pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][2];
	pDoc->m_iCmdCntsEW = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][1] + pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][3];
	pDoc->m_iCmdCntsELAC2 = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][7];
	pDoc->bSelectLocFlagNS = TRUE;
	pDoc->bSelectLocFlagEW = TRUE;

	Move_EET02_to_Selected_PM_Location();

	pDoc->RA_LogEvents(_T("INFO: PM Moved to the Selected Location"));
	pView->RA_DispMsg(_T("INFO: PM Moved to the Selected Location"));
}

void CEET02Dlg::Move_EET02_to_Selected_PM_Location()
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
		AfxMessageBox("ERROR: Unable to select PM speed");
		return;
	}

	if (pView->PM_Ready2Move())//&& bSelectLocFlagNS && bSelectLocFlagEW)
	{

		// Pipe Adjustment

		if (pDoc->PM_selected_Location == "23-G" || pDoc->PM_selected_Location == "22-F" || pDoc->PM_selected_Location == "22-H" || pDoc->PM_selected_Location == "21-G" || pDoc->PM_selected_Location == "20-H" || pDoc->PM_selected_Location == "19-G" || pDoc->PM_selected_Location == "20-K" || pDoc->PM_selected_Location == "18-K" || pDoc->PM_selected_Location == "20-F")
		{

			// towards East

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get EW Current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get EW Current Position"));
				return;
			}
						
			EWtargetPos = (pDoc->pPositionIsEW) + 179125.02;

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

			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 3000, 2000, 2000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
			}
			
			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, EWtargetPos, TRUE, TRUE, &(pDoc->dwErrorCode)))
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

			// towards North

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt2, &(pDoc->pPositionIsNS), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get NS Current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get NS Current Position"));
				return;
			}

			NStargetPos = (pDoc->pPositionIsNS) - 491800;
			
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
			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt2, 3000, 2000, 2000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
			}
			
			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt2, NStargetPos, TRUE, TRUE, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Move to position for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Move to position for NS failed")); return;
			}
			
			if (!(pView->Update_PM_Position()))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to update PM position"));
				pView->RA_DispMsg(_T("ERROR: Unable to update PM position"));
				return;
			}
			// Moving toward West

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get EW Current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get EW Current Position"));
				return;
			}
			
			EWtargetPos = (pDoc->pPositionIsEW) - 480000;
			
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

			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 3000, 2000, 2000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
			}

			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, EWtargetPos, TRUE, TRUE, &(pDoc->dwErrorCode)))
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

		if (pDoc->PM_selected_Location == "17-L" || pDoc->PM_selected_Location == "19-L" || pDoc->PM_selected_Location == "21-L" || pDoc->PM_selected_Location == "20-M" || pDoc->PM_selected_Location == "18-M" || pDoc->PM_selected_Location == "14-R" || pDoc->PM_selected_Location == "12-R" || pDoc->PM_selected_Location == "15-S" || pDoc->PM_selected_Location == "13-S" || pDoc->PM_selected_Location == "11-S" || pDoc->PM_selected_Location == "14-T" || pDoc->PM_selected_Location == "12-T")
		{

			// towards East

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt3, &(pDoc->pPositionIsEW), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get EW Current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get EW Current Position"));
				return;
			}

			EWtargetPos = (pDoc->pPositionIsEW) + 150000.02;

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

			if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt3, 3000, 2000, 2000, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting position profile for NS failed"));
				pView->RA_DispMsg(_T("ERROR: Setting position profile for NS failed")); return;
			}

			if (!VCM_MoveToPosition(pDoc->hDriveHandleExt3, EWtargetPos, TRUE, TRUE, &(pDoc->dwErrorCode)))
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
//		UpdateData(TRUE);
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

BOOL CEET02Dlg::Select_PM_Speed()
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
	if (M_SelectedSpeed_PM == "Fast") // FAST
	{
		ProfileVelocityNS = pDoc->FProfileVelocityNS;
		ProfileAccelerationNS = pDoc->FProfileAccelerationNS;
		ProfileDeccelerationNS = pDoc->FProfileDeccelerationNS;

		ProfileVelocityEW = pDoc->FProfileVelocityEW;
		ProfileAccelerationEW = pDoc->FProfileAccelerationEW;
		ProfileDeccelerationEW = pDoc->FProfileDeccelerationEW;
		return TRUE;
	}

	if (M_SelectedSpeed_PM == "Medium") // MEDIUM
	{
		ProfileVelocityNS = pDoc->MProfileVelocityNS;
		ProfileAccelerationNS = pDoc->MProfileAccelerationNS;
		ProfileDeccelerationNS = pDoc->MProfileDeccelerationNS;

		ProfileVelocityEW = pDoc->MProfileVelocityEW;
		ProfileAccelerationEW = pDoc->MProfileAccelerationEW;
		ProfileDeccelerationEW = pDoc->MProfileDeccelerationEW;
		return TRUE;
	}

	if (M_SelectedSpeed_PM == "Slow") // SLOW
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


void CEET02Dlg::OnBnClickedMovela2tosafelimit()
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt5, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC2")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt5, 3000, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC2 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC2 failed")); return;
	}

	pDoc->m_iCmdCntsELAC2 = pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][7];

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt5, pDoc->m_iCmdCntsELAC2, TRUE, TRUE, &(pDoc->dwErrorCode))) //-3800000
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC2 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC2 failed")); return;
	}

	if (!(pView->Update_LA2_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 2 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 2 Current Position")); return;
	}
}


void CEET02Dlg::OnBnClickedRotatenut()
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

	if (AfxMessageBox("INFO: Open Trunnion Valve 3.25 turns to grip it", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL | MB_OKCANCEL) == IDOK)
	{
		pDoc->pOperationMode = OMD_CURRENT_MODE;

		if (!VCM_SetOperationMode(pDoc->hDriveHandleExt5, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Set Current Mode of ELAC2 to Current Mode"));
			pView->RA_DispMsg(_T("ERROR: Unable to Set Current Mode of ELAC2 to Current Mode")); return;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed")); return;
		}

		if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2")); return;
		}

		if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt5, -180, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting Current for ELAC1 failed"));
			pView->RA_DispMsg(_T("ERROR: Setting Current for ELAC1 failed")); return;
		}


		Sleep(200);

		pDoc->RA_LogEvents(_T("INFO: Linear Actuator 2 moved in Current mode"));
		pDoc->bMoveWithCurFlagELAC2 = TRUE;


		while (1)
		{
			// Check Status of LA2 controller 

			if (!VCM_GetFaultState(pDoc->hDriveHandleExt5, &(pDoc->bELAC2), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get state of ELAC2 controller"));
				pView->RA_DispMsg(_T("ERROR: Unable to get state of ELAC2 controller")); return;
			}

			if (!(pView->LA_LimitSwitches_Status()))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to find LA LimitsSwitches Status"));
				pView->RA_DispMsg(_T("ERROR: Unable to find LA LimitsSwitches Status"));
				return;
			}

			// Get Movement State of LA2 

			if (!VCM_GetMovementState(pDoc->hDriveHandleExt5, &(pDoc->bMovingFlagELAC2), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to read ELAC2 movement state"));
				pView->RA_DispMsg(_T("ERROR: Unable to read ELAC2 movement state")); return;
			}

			// Check average velocity of LA2

			if (!VCM_GetVelocityIsAveraged(pDoc->hDriveHandleExt5, &pDoc->pVelocityIsAveragedLA2, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to Get average velocity"));
				pView->RA_DispMsg(_T("ERROR: Unable to Get average velocity")); return;
			}

			// Check the position of LA2

			if (!VCM_GetPositionIs(pDoc->hDriveHandleExt5, &(pDoc->pPositionIsLA2), &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to get current Position"));
				pView->RA_DispMsg(_T("ERROR: Unable to get current Position")); return;
			}

			// Display and Update the position Status of LA2 controller 

			pView->Display_Motion_Status();
			

			pDoc->m_lActualCntsELAC2 = pDoc->pPositionIsLA2;

			if (GetAsyncKeyState(VK_END))
			{
				if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop LA2"));
					pView->RA_DispMsg(_T("ERROR: Unable to quickstop LA2"));

				}

				break;
			}

			if (abs(pDoc->pVelocityIsAveragedLA2) < 5)
			{
				if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: UNABLE TO QUICKSTOP ELAC2"));
					AfxMessageBox(_T("ERROR: UNABLE TO QUICKSTOP ELAC2, PRESS EMERGENCY BUTTON")); return;
				}
				break;
			}
			// test bencth finish
		}

		if (!LA02_Speed())
		{
			pDoc->RA_LogEvents(_T("ERROR: Select LA02 speed first"));
			pView->RA_DispMsg(_T("ERROR: Select LA02 speed first")); return;
		}

		pView->RA_DispMsg(_T("INFO: LA2 moving 2mm in downward direction to safe limit"));

		// Move ELAC2 4 mm downward in Profile Position mode

		pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

		if (!VCM_SetOperationMode(pDoc->hDriveHandleExt5, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Set Current Mode of ELAC2 to Current Mode"));
			pView->RA_DispMsg(_T("ERROR: Unable to Set Current Mode of ELAC2 to Current Mode")); return;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
			pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
			pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2")); return;
		}
		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt5, ProfileVelocityLA02, ProfileAccelerationLA02, ProfileDeccelerationLA02, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC2 failed"));
			pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC2 failed")); return;
		}

		pDoc->m_iCmdCntsELAC2 = pDoc->m_lActualCntsELAC2 + 90000;

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt5, pDoc->m_iCmdCntsELAC2, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC2 failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for ELAC2 failed")); return;
		}


		if (!(pView->Update_LA2_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 2 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 2 Current Position")); return;
		}
	}
}

BOOL CEET02Dlg::LA02_Speed()
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
	if (m_Select_LA02_Speed == "Fast") // FAST
	{
		ProfileVelocityLA02 = pDoc->FProfileVelocityLA2;
		ProfileAccelerationLA02 = pDoc->FProfileAccelerationLA2;
		ProfileDeccelerationLA02 = pDoc->FProfileDeccelerationLA2;
		return TRUE;
	}

	if (m_Select_LA02_Speed == "Medium") // MEDIUM
	{
		ProfileVelocityLA02 = pDoc->MProfileVelocityLA2;
		ProfileAccelerationLA02 = pDoc->MProfileAccelerationLA2;
		ProfileDeccelerationLA02 = pDoc->MProfileDeccelerationLA2;
		return TRUE;
	}

	if (m_Select_LA02_Speed == "Slow") // SLOW
	{
		ProfileVelocityLA02 = pDoc->SProfileVelocityLA2;
		ProfileAccelerationLA02 = pDoc->SProfileAccelerationLA2;
		ProfileDeccelerationLA02 = pDoc->SProfileDeccelerationLA2;
		return TRUE;
	}
	
}


void CEET02Dlg::OnBnClickedRotateEtc2()
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

/*	{
		// TODO: Add your control notification handler code here

		pDoc->pOperationMode = OMD_PROFILE_POSITION_MODE;

		if (!VCM_SetOperationMode(pDoc->hDriveHandleExt7, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to set operation mode of ETC2 Profile Position Mode")); return;
		}

		if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to Activate Profile Position Mode of ETC2")); return;
		}

		if (!VCM_SetEnableState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to set Enable State")); return;
		}

		if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt7, 2000, 3000, 3000, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ETC2 failed")); return;
		}

		if (!VCM_GetPositionIs(pDoc->hDriveHandleExt7, &(pDoc->pPositionIsETC2), &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to get ETC2 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to get ETC2 Current Position"));
			return;
		}

		ptargetpositionETC2 = -(abs(pDoc->pPositionIsETC2) + 1800000);

		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt7, ptargetpositionETC2, TRUE, TRUE, &(pDoc->dwErrorCode)))	//Testing CW	3 turns = -3583125		, 2 turns =  -2205000 		
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ETC2 failed")); return;
		}

		if (!(pView->Update_ETC2_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update ETC2 Current Position")); return;
		}

	} */

	pDoc->pOperationMode = OMD_CURRENT_MODE;

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt7, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set operation mode of ETC2 Profile Position Mode")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set Enable State")); return;
	}

	if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to Activate Current Mode of ETC2")); return;
	}


	if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt7, -250, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of ETC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of ETC2")); return;
	}

	pDoc->notetc2 = 0;
	UpdateData(FALSE);

	if (!(pView->Update_ETC2_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update ETC2 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update ETC2 Current Position")); return;
	}

	pDoc->notetc2 = 0;
}


void CEET02Dlg::OnBnClickedHomeElac2()
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

	if (!pView->RaHomeelac2())
	{
		pDoc->RA_LogEvents(_T("ERROR: LA2 Homing not successful"));
		pView->RA_DispMsg(_T("ERROR: LA2 Homing not successful"));
		return;
	}
}


void CEET02Dlg::OnBnClickedUpdateLocationFile()
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

		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][2] = pView->m_pPositionIsNS - (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][0]);
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][3] = pView->m_pPositionIsEW - (pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][1]);
		pDoc->iLocGrid[28 - pDoc->m_iLocSelectedNS][pDoc->m_iLocSelectedEW][7] = pView->m_pPositionIsELAC2;

		//	PM_WriteLocations2File();

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


void CEET02Dlg::OnBnClickedResetLocationFile()
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

void CEET02Dlg::PM_WriteLocations2File()
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


void CEET02Dlg::OnBnClickedButton6()
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


BOOL CEET02Dlg::OnInitDialog()
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

	LA2_FINE_INC = 24500;//Fine Step for Motion along z-axix LA2
	LA2_COARSE_INC = 49000;//Fine Step for Motion along z-axis LA2

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
	m_ft_movePM.SetToolTipText(_T("Move PM, To stop press END from keyboard"), TRUE);
	m_ft_moveelac2.LoadStdImage(IDB_move, ("PNG"));
	m_ft_moveelac2.SetToolTipText(_T("Move ELAC2, To stop press END from keyboard"), TRUE);
	m_step1.LoadStdImage(IDB_step1, ("PNG"));
	m_step1.SetToolTipText(_T("Move ELAC2 to safe Limit"), TRUE);
	m_step2.LoadStdImage(IDB_step2, ("PNG"));
	m_step2.SetToolTipText(_T("Grip Trunnion Nut"), TRUE);
	m_step3.LoadStdImage(IDB_step3, ("PNG"));
	m_step3.SetToolTipText(_T("Close Trunnion Nut"), TRUE);
//	m_step4.LoadStdImage(IDB_laststep, ("PNG"));
//	m_step4.SetToolTipText(_T("Move ELAC2 to parking position"), TRUE);
	m_next.LoadStdImage(IDB_Next, ("PNG"));
	m_next.SetToolTipText(_T("Open Next Dialog"), TRUE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CEET02Dlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here


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
}


void CEET02Dlg::OnBnClickedButton7()
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


void CEET02Dlg::OnBnClickedButton8()
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


void CEET02Dlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here


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
}


void CEET02Dlg::OnBnClickedButton10()
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
}


void CEET02Dlg::OnBnClickedButton149()
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


void CEET02Dlg::OnBnClickedButton11()
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


void CEET02Dlg::OnBnClickedButton151()
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt5, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC2")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt5, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC2 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC2 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt5, &(pDoc->pPositionIsLA2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of LA2"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of LA2")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt5, (pDoc->pPositionIsLA2) - LA2_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC2 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC2 failed")); return;
	}

	/*	if (!VCM_MoveToPosition(hDriveHandleExt4,-3500000, TRUE, TRUE, &dwErrorCode))
	{
	AfxMessageBox(_T("ERROR: Move to position for ELAC1 failed")); return FALSE;
	}
	*/
	if (!(pView->Update_LA2_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 2 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 2 Current Position")); return;
	}
}


void CEET02Dlg::OnBnClickedButton150()
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt5, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC2")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt5, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC2 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC2 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt5, &(pDoc->pPositionIsLA2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of LA2"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of LA2")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	if (!VCM_MoveToPosition(pDoc->hDriveHandleExt5, (pDoc->pPositionIsLA2) - LA2_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC2 failed"));
		pView->RA_DispMsg(_T("ERROR: Move to position for ELAC2 failed")); return;
	}

	/*	if (!VCM_MoveToPosition(hDriveHandleExt4,-3500000, TRUE, TRUE, &dwErrorCode))
	{
	AfxMessageBox(_T("ERROR: Move to position for ELAC1 failed")); return FALSE;
	}
	*/
	if (!(pView->Update_LA2_Position()))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 2 Current Position"));
		pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 2 Current Position")); return;
	}
}


void CEET02Dlg::OnBnClickedButton157()
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt5, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC2")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt5, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC2 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC2 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt5, &(pDoc->pPositionIsLA2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of LA2"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of LA2")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	if (abs(pDoc->pPositionIsLA2) <= 25000)
	{
		pView->RA_DispMsg(_T("ERROR : You have reached Lower Limit (Home Switch), LA2 can not move")); return;
	}
	else
	{
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt5, (pDoc->pPositionIsLA2) + LA2_FINE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC2 failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for ELAC2 failed")); return;
		}

		if (!(pView->Update_LA2_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 2 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 2 Current Position")); return;
		}
	}
}


void CEET02Dlg::OnBnClickedButton15()
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

	if (!VCM_SetOperationMode(pDoc->hDriveHandleExt5, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to set master encoder mode of ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to set master encoder mode of ELAC2")); return;
	}

	if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 controller failed"));
		pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 controller failed")); return;
	}

	if (!VCM_ActivateProfilePositionMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2"));
		pView->RA_DispMsg(_T("ERROR: Unable to activate Profile Postion Mode for ELAC2")); return;
	}
	if (!VCM_SetPositionProfile(pDoc->hDriveHandleExt5, 600, 2000, 2000, &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Setting position profile for ELAC2 failed"));
		pView->RA_DispMsg(_T("ERROR: Setting position profile for ELAC2 failed")); return;
	}

	if (!VCM_GetPositionIs(pDoc->hDriveHandleExt5, &(pDoc->pPositionIsLA2), &(pDoc->dwErrorCode)))
	{
		pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of LA2"));
		pView->RA_DispMsg(_T("ERROR: Unable to read actual position of LA2")); return;
	}

	// To test the position is -3000000 otherwise in actual its -3500000

	if (abs(pDoc->pPositionIsLA2) <= 50000)
	{
		pView->RA_DispMsg(_T("ERROR : You have reached Lower Limit (Home Switch), LA2 can not move")); return;
	}
	else
	{
		if (!VCM_MoveToPosition(pDoc->hDriveHandleExt5, (pDoc->pPositionIsLA2) + LA2_COARSE_INC, TRUE, TRUE, &(pDoc->dwErrorCode)))
		{
			pDoc->RA_LogEvents(_T("ERROR: Move to position for ELAC2 failed"));
			pView->RA_DispMsg(_T("ERROR: Move to position for ELAC2 failed")); return;
		}

		if (!(pView->Update_LA2_Position()))
		{
			pDoc->RA_LogEvents(_T("ERROR: Unable to update Linear Actuator 2 Current Position"));
			pView->RA_DispMsg(_T("ERROR: Unable to update Linear Actuator 2 Current Position")); return;
		}
	}
}


void CEET02Dlg::OnBnClickedMovePmft()
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

		if (m_Select_PM_Mode == "Profile Velocity Mode" && m_Select_PM_Direction == "West")
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

		if (m_Select_PM_Mode == "Profile Velocity Mode" && m_Select_PM_Direction == "East")
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

		if (m_Select_PM_Mode == "Profile Velocity Mode" && m_Select_PM_Direction == "North")
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

		if (m_Select_PM_Mode == "Profile Velocity Mode" && m_Select_PM_Direction == "South")
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

		if (m_Select_PM_Mode == "Current Mode" && m_Select_PM_Direction == "South")
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

		if (m_Select_PM_Mode == "Current Mode" && m_Select_PM_Direction == "North")
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

		if (m_Select_PM_Mode == "Current Mode" && m_Select_PM_Direction == "East")
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

		if (m_Select_PM_Mode == "Current Mode" && m_Select_PM_Direction == "West")
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
	else
	{
		pDoc->RA_LogEvents(_T("ERROR: PM not ready to move"));
		pView->RA_DispMsg(_T("ERROR: PM not ready to move"));
	}
}


void CEET02Dlg::OnBnClickedMoveElac2ft()
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

	//	if (pDoc->bHomeELAC2Flag == TRUE)
	{
		UpdateData(TRUE);
		m_Value = abs(m_Value);

		
		if (m_select_tool == "ELAC2")
		{
			UpdateData(TRUE); // retreive m_shCmdCrntELAC1 LA1 current must value from window
			m_Value = abs(m_Value);

			pDoc->pOperationMode = OMD_CURRENT_MODE;

			if (!VCM_SetOperationMode(pDoc->hDriveHandleExt5, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unable to set Operation Mode"));
				pView->RA_DispMsg(_T("ERROR: Unable to set Operation Mode")); return;
			}

			if (!VCM_SetEnableState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting enable state of ELAC2 failed"));
				pView->RA_DispMsg(_T("ERROR: Setting enable state of ELAC2 failed")); return;
			}

			if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Unbable to activate Current Mode for ELAC2"));
				pView->RA_DispMsg(_T("ERROR: Unbable to activate Current Mode for ELAC2")); return;
			}

			if (m_Value >= 320)
			{
				pView->RA_DispMsg(_T("ERROR : Current Upper Limit exceed, LA2 can not move")); return;
			}

			if (m_Direction == "Up")
			{
				m_Value = -m_Value;
			}

			if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt5, m_Value, &(pDoc->dwErrorCode)))
			{
				pDoc->RA_LogEvents(_T("ERROR: Setting Current for ELAC2 failed"));
				pView->RA_DispMsg(_T("ERROR: Setting Current for ELAC2 failed")); return;
			}

			while (1)
			{
				if (!pView->Update_All_Positions())
				{
					break;
				}

			/*	if (GetAsyncKeyState(VK_END))
				{
					if (!VCM_SetQuickStopState(pDoc->hDriveHandleExt5, &(pDoc->dwErrorCode)))
					{
						pDoc->RA_LogEvents(_T("ERROR: Unable to quickstop ELAC2"));
						pView->RA_DispMsg(_T("ERROR: Unable to quickstop ELAC2"));
						return;
					}

					break;
				}*/
			}

		}

		pDoc->notetc2 = 0;

	}

	if (m_select_tool == "ETC2")
	{
	/*	if (abs(m_Value) > 8)
		{
			pDoc->RA_LogEvents(_T("ERROR: Number of turns should not be greater than eight [8]")); 
			pView->RA_DispMsg(_T("ERROR: Number of turns should not be greater than eight [8]")); return;
		}*/
			// TODO: Add your control notification handler code here

			pDoc->pOperationMode = OMD_CURRENT_MODE;

			UpdateData(TRUE);
			
				if (!VCM_SetOperationMode(pDoc->hDriveHandleExt7, pDoc->pOperationMode, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to set operation mode of ETC2 Profile Position Mode")); return;
				}

				if (!VCM_SetEnableState(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to set Enable State")); return;
				}

				if (!VCM_ActivateCurrentMode(pDoc->hDriveHandleExt7, &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to Activate Current Mode of ETC2")); return;
				}


				if (m_Value >= 320)
				{
					pView->RA_DispMsg(_T("ERROR : Current Upper Limit exceed, ETC2 can not move")); return;
				}

				if (m_Direction == "Close")
				{
					m_Value = -m_Value;
				}

				if (!VCM_SetCurrentMust(pDoc->hDriveHandleExt7, m_Value , &(pDoc->dwErrorCode)))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to read actual position of ETC2"));
					pView->RA_DispMsg(_T("ERROR: Unable to read actual position of ETC2")); return;
				}

				
				if (!(pView->Update_ETC2_Position()))
				{
					pDoc->RA_LogEvents(_T("ERROR: Unable to update ETC2 Current Position")); 
					pView->RA_DispMsg(_T("ERROR: Unable to update ETC2 Current Position")); return;
				}
			
		}
	
}


BOOL CEET02Dlg::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CEET02Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CEET02Dlg::OnBnClickedNext()
{
	// TODO: Add your control notification handler code here

	C6DOFPCMView *pView;
	pView = pView->GetView();
	if (!pView)
	{
		AfxMessageBox("ERROR: Unable to get View pointer");
		return;
	}

	pView->ShowWindowNumber(3);
}

void CEET02Dlg::SelectedPosition()
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


void CEET02Dlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
//	delete this;
}
