
// 6DOFPCMDoc.cpp : implementation of the C6DOFPCMDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "6DOFPCM.h"
#endif

#include "6DOFPCMDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// C6DOFPCMDoc

IMPLEMENT_DYNCREATE(C6DOFPCMDoc, CDocument)
BEGIN_MESSAGE_MAP(C6DOFPCMDoc, CDocument)
END_MESSAGE_MAP()


// C6DOFPCMDoc construction/destruction

C6DOFPCMDoc::C6DOFPCMDoc()
{
	// TODO: add one-time construction code here

	targetposition = 0;
	startposetc2 = 0;
	startposetc3 = 0;
	notetc2 = 0;
	notetc3 = 0;
	PM_selected_Location = _T("No Location Selected");
	m_login_name = _T("0");
	m_login_passowrd = _T("0");

	PDisconnect = 0;
	dwBaudRate = 115200;         // 1000000;			     
	dwTimeOut = 500;
	dwErrorCode = 0;

	byteEpos2PNodeID = 1;
	byteEpos2NodeIDInt = 1;  // Node ID of Master Controller CMTR
	byteEpos2NodeIDExt2 = 2; // Node ID of North South Axis Controller CNSA
	byteEpos2NodeIDExt3 = 3; // Node ID of East WEst Axis Controller CEWA
	byteEpos2NodeIDExt4 = 4; // NOde ID of Linear Actuator 1 CLA1 Controller 
	byteEpos2NodeIDExt5 = 5; // Node ID of Linear Actuator 2 CLA2 Controller 
	byteEpos2NodeIDExt6 = 6; // Node ID of Linear Actuator 3 CLA3 Controller 
	byteEpos2NodeIDExt7 = 7; // Node ID of ETC2 controller
	byteEpos2NodeIDExt8 = 8; // Node ID of CTC controller
	byteEpos2NodeIDExt9 = 9; // Node ID of ETC3 controller

	byteRemoteNetworkIDInt = 1; // Remote Network ID of Master Controller
	byteRemoteNetworkIDExt = 2; // Remote Network ID of Slave Controllers

	bMovingFlagNS = TRUE;
	bMovingFlagEW = TRUE;
	bMovingFlagELAC1 = TRUE;
	bMovingFlagELAC2 = TRUE;
	bMovingFlagELAC3 = TRUE;
	bMovingFlagETC2 = TRUE;
	bMovingFlagETC3 = TRUE;
	bMovingFlagCTC = TRUE;

	// Controllers status

	bMC = TRUE; // Master Controller status
	bNSC = TRUE;   // North South Axis Controller status
	bEWC = TRUE; // East West Axis status
	bELAC1 = TRUE;// Linear Actuator 1 Controller status
	bELAC2 = TRUE;// Linear Actuator 2 Controller status
	bELAC3 = TRUE; // Linear Actuator 3 Controller status
	bETC2 = TRUE;  // Endy Effector Tool 1 Controller status
	bCTC = TRUE;  // Endy Effector Tool 2  Controller status
	bETC3 = TRUE;  // Endy Effector Tool 3  Controller status

				   // Limit Switch Status

	bXNL = FALSE;  // Extreme North Limit Switch Status
	bXWL = FALSE;  // Extreme West Limit Switch Status
	bXSL = FALSE;  // Extreme South Limit Switch Status
	bXEL = FALSE;  // Extreme East Limit Switch Status
	bHNSL = FALSE; // North Axis Home Switch
	bHEWL = FALSE; // West Axis Home Switch
	bHELAC1 = FALSE; // Linear Actuator 1 Extreme Limit Switch Status
	bHELAC2 = FALSE; // Linear Actuator 2 Extreme Limit Switch Status
	bHELAC3 = FALSE; // Linear Actuator 3 Extreme Limit Switch Status
	bBNL = TRUE;  // North South Axis Brake Hold and Release Output Status
	bBEL = TRUE;  // East West Axis Brake Hold and Release Output Status

	bConfigFlag = FALSE;


	pPositionIsNS = 0;
	pPositionIsEW = 0;
	pPositionIsLA1 = 0;
	pPositionIsLA2 = 0;
	pPositionIsLA3 = 0;
	pPositionIsETC2 = 0;
	pPositionIsETC3 = 0;
	pPositionIsCTC = 0;

	m_iCmdCntsNS = -100000;//Adjusting Position for NS in Counts
	m_iCmdCntsEW = 100000;//Adjusting Position for EW in Counts
	TONSEW = 10000; // Time out for adjusting motion of NS & EW in msec
	TONSEWHOMING = 100000;// Time out for homing of NS & EW in msec

						  //Homing Parameters

	dwHomingAccNS = 5000;
	dwSpeedSwitchNS = 500;
	dwSpeedIndexNS = 300;
	wCurrentThresholdNS = 100;
	lHomingPositionNS = 702820;
	lOffsetNS = 0;

	dwHomingAccEW = 5000;
	dwSpeedSwitchEW = 500;
	dwSpeedIndexEW = 300;
	wCurrentThresholdEw = 100;
	lHomingPositionEW = -12000;
	lOffsetEW = 0;

	iParkPosCntsNS = 600000;
	iParkPosCntsEW = 40000;

	m_iCmdCntsELAC1 = -300000; // Counts = 36mm Linear displacement

							   // Homing Parameters ELAC1

	dwHomingAccELAC1 = 5000;
	dwSpeedSwitchELAC1 = 900;
	dwSpeedIndexELAC1 = 500;
	wCurrentThresholdELAC1 = 100;
	lHomingPositionELAC1 = 0;
	lOffsetELAC1 = 0;

	// Homing Parameters ELAC2

	m_iCmdCntsELAC2 = -300000;// Counts = 36mm Linear displacement
	dwHomingAccELAC2 = 5000;
	dwSpeedSwitchELAC2 = 900;
	dwSpeedIndexELAC2 = 500;
	wCurrentThresholdELAC2 = 100;
	lHomingPositionELAC2 = 0;
	lOffsetELAC2 = 0;

	// Homing Parameters ELAC3

	m_iCmdCntsELAC3 = -300000;// Counts = 36mm Linear displacement
	dwHomingAccELAC3 = 5000;
	dwSpeedSwitchELAC3 = 900;
	dwSpeedIndexELAC3 = 500;
	wCurrentThresholdELAC3 = 100;
	lHomingPositionELAC3 = 0;
	lOffsetELAC3 = 0;

	// Homing Parameters CTC

	dwHomingAccCTC = 2000;
	dwSpeedSwitchCTC = 900;
	dwSpeedIndexCTC = 500;
	wCurrentThresholdCTC = 400;
	lHomingPositionCTC = -200000;
	lOffsetCTC = -200000;

	m_UserInputPolarity = 0;
	MaxVelocity = 3000;
	MaxAcceleration = 5000;

	SProfileVelocityNS = 1000;
	SProfileAccelerationNS = 1000;
	SProfileDeccelerationNS = 1000;

	SProfileVelocityEW = 1000;
	SProfileAccelerationEW = 1000;
	SProfileDeccelerationEW = 1000;

	MProfileVelocityNS = 1200;
	MProfileAccelerationNS = 1000;
	MProfileDeccelerationNS = 1000;

	MProfileVelocityEW = 1200;
	MProfileAccelerationEW = 1000;
	MProfileDeccelerationEW = 1000;

	FProfileVelocityNS = 1500;
	FProfileAccelerationNS = 1000;
	FProfileDeccelerationNS = 1000;

	FProfileVelocityEW = 1500;
	FProfileAccelerationEW = 1000;
	FProfileDeccelerationEW = 1000;


	SProfileVelocityLA1 = 1000;
	SProfileAccelerationLA1 = 1000;
	SProfileDeccelerationLA1 = 1000;

	MProfileVelocityLA1 = 1500;
	MProfileAccelerationLA1 = 1500;
	MProfileDeccelerationLA1 = 1500;

	FProfileVelocityLA1 = 2200;
	FProfileAccelerationLA1 = 2000;
	FProfileDeccelerationLA1 = 2000;

	SProfileVelocityLA2 = 1000;
	SProfileAccelerationLA2 = 1000;
	SProfileDeccelerationLA2 = 1000;

	MProfileVelocityLA2 = 1300;
	MProfileAccelerationLA2 = 2000;
	MProfileDeccelerationLA2 = 2000;

	FProfileVelocityLA2 = 1800;
	FProfileAccelerationLA2 = 3000;
	FProfileDeccelerationLA2 = 3000;

	NSdiff = 0;
	EWdiff = 0;

	errorcode = 0000;

	errormsg = "NULL";

}

C6DOFPCMDoc::~C6DOFPCMDoc()
{
}

C6DOFPCMDoc * C6DOFPCMDoc::GetDoc()
{
	CFrameWnd *pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	return (C6DOFPCMDoc*)pFrame->GetActiveDocument();
}

BOOL C6DOFPCMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// C6DOFPCMDoc serialization

void C6DOFPCMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void C6DOFPCMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void C6DOFPCMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void C6DOFPCMDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// C6DOFPCMDoc diagnostics

#ifdef _DEBUG
void C6DOFPCMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void C6DOFPCMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
bool C6DOFPCMDoc::PM_ReadLocations()
{
	
	CFile RF;
	CFileException ex;

	if (!RF.Open(_T("LocationLattice.dat"), CFile::modeRead, &ex))
	{
		char buffer[255];

		if (ex.GetErrorMessage(LPTSTR(buffer), sizeof buffer))
			ex.ReportError();
		else
			AfxMessageBox("ERROR: Unable to open locations file 'LocationLattice.dat'", MB_SETFOREGROUND | MB_TOPMOST | MB_APPLMODAL);

		RA_LogEvents(_T("ERROR: Unable to open locations file 'LocationLattice.dat'"));

		return false;
	}
	char buff[300000];

	UINT i, j;

	UINT FileLength = RF.Read(buff, sizeof buff);
	buff[FileLength] = 0;
	CStringA strVar(buff);

	for (i = 0; i < 29; i++)
	{
		for (j = 0; j < 15; j++)
		{
			iLocGrid[i][j][0] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();
			iLocGrid[i][j][1] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();
			iLocGrid[i][j][2] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();
			iLocGrid[i][j][3] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();
			iLocGrid[i][j][4] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();
			iLocGrid[i][j][5] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();
			iLocGrid[i][j][6] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();
			iLocGrid[i][j][7] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();
			iLocGrid[i][j][8] = atoi(strVar.Left(8));
			strVar.Delete(0, 8);
			strVar.TrimLeft();

		}
	}

	int m = iLocGrid[12][7][1];
	m = iLocGrid[12][7][3];
	return true;
}
void C6DOFPCMDoc::RA_LogEvents(CString EventRecord)
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
	CString msg;
	CString FileName;
	CString TimeStamp;
	CFileException ex;
	FileName.Format(_T("PM%04d%02d.log"), YEAR, MONTH);
	if (LogFile.Open(FileName, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite, &ex))
	{
		ULONGLONG FileLength = LogFile.GetLength();

		if (FileLength == 0)
		{
			//msg.Format(_T("OK: New log file opened (%s)"), FileName);
			//RA_DispMsg(msg);
			LogFile.SeekToEnd();
			msg = _T("Log File Generated");
			TimeStamp.Format(_T("%04d-%02d-%02d\t%02d:%02d"), YEAR, MONTH, DAY, HOUR, MINT);
			msg.Format(_T("%s\t%s"), TimeStamp, msg);
			LogFile.WriteString(msg);
			LogFile.WriteString(_T("\n"));
		}


		LogFile.SeekToEnd();
		TimeStamp.Format(_T("%04d-%02d-%02d\t%02d:%02d"), YEAR, MONTH, DAY, HOUR, MINT);
		msg.Format(_T("%s\t%s"), TimeStamp, EventRecord);
		LogFile.WriteString(msg);
		LogFile.WriteString(_T("\n"));

	}
}
#endif //_DEBUG


// C6DOFPCMDoc commands
