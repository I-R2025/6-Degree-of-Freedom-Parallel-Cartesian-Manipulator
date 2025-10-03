
// 6DOFPCMDoc.h : interface of the C6DOFPCMDoc class
//


#pragma once


class C6DOFPCMDoc : public CDocument
{
protected: // create from serialization only
	C6DOFPCMDoc();
	DECLARE_DYNCREATE(C6DOFPCMDoc)

// Attributes
public:

// Operations
public:
	static C6DOFPCMDoc* GetDoc();
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~C6DOFPCMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	bool PM_ReadLocations();
	void RA_LogEvents(CString EventRecord);

	WORD errorcode;
	CString errormsg;
	int m_login_first;
	BOOL bConfigFlag;

	CString m_username_received;
	CString m_password_received;
	CString m_usertype_received;

	BYTE byteEpos2PNodeID;
	BYTE byteEpos2NodeIDInt;  // Node ID of Master Controller CMTR
	BYTE byteEpos2NodeIDExt2; // Node ID of North South Axis Controller CNSA
	BYTE byteEpos2NodeIDExt3; // Node ID of East WEst Axis Controller CEWA
	BYTE byteEpos2NodeIDExt4; // NOde ID of Linear Actuator 1 CLA1 Controller 
	BYTE byteEpos2NodeIDExt5; // Node ID of Linear Actuator 2 CLA2 Controller 
	BYTE byteEpos2NodeIDExt6; // Node ID of Linear Actuator 3 CLA3 Controller 
	BYTE byteEpos2NodeIDExt7; // Node ID of ETC2 controller
	BYTE byteEpos2NodeIDExt8; // Node ID of CTC controller
	BYTE byteEpos2NodeIDExt9; // Node ID of ETC3 controller

							  // Gateway Handles

	BYTE byteRemoteNetworkIDInt; // Remote Network ID of Master Controller
	BYTE byteRemoteNetworkIDExt; // Remote Network ID of Slave Controllers
	HANDLE hGatewayHandleInt;  // Master Controller CMTR gateway handle
	HANDLE hGatewayHandleExt2; // North South Axis Controller CNSA gateway handle
	HANDLE hGatewayHandleExt3; // East West Axis Controller CEWA gateway handle
	HANDLE hGatewayHandleExt4; // Linear Actuator 1 CLA1 Controller gateway handle
	HANDLE hGatewayHandleExt5; // Linear Actuator 2 CLA2 Controller gateway handle
	HANDLE hGatewayHandleExt6; // Linear Actuator 3 CLA3 Controller gateway handle
	HANDLE hGatewayHandleExt7; // ETC2 controller gateway handle
	HANDLE hGatewayHandleExt8; // CTC controller gateway handle
	HANDLE hGatewayHandleExt9; // ETC3 controller gateway handle


	DWORD dwBaudRate;         // 1000000;			     
	DWORD dwTimeOut;

	// Drive Handles

	HANDLE hCommHandle;
	HANDLE hDriveHandleInt;
	HANDLE hDriveHandleExt2;
	HANDLE hDriveHandleExt3;
	HANDLE hDriveHandleExt4;
	HANDLE hDriveHandleExt5;
	HANDLE hDriveHandleExt6;
	HANDLE hDriveHandleExt7;
	HANDLE hDriveHandleExt8;
	HANDLE hDriveHandleExt9;
	DWORD dwErrorCode;

	INT PDisconnect;

	BOOL bMovingFlagNS;
	BOOL bMovingFlagEW;
	BOOL bMovingFlagELAC1;
	BOOL bMovingFlagELAC2;
	BOOL bMovingFlagELAC3;
	BOOL bMovingFlagETC2;
	BOOL bMovingFlagETC3;
	BOOL bMovingFlagCTC;

	// Controllers status

	BOOL bMC;    // Master Controller status
	BOOL bNSC;   // North South Axis Controller status
	BOOL bEWC;   // East West Axis status
	BOOL bELAC1; // Linear Actuator 1 Controller status
	BOOL bELAC2; // Linear Actuator 2 Controller status
	BOOL bELAC3; // Linear Actuator 3 Controller status
	BOOL bETC2;  // Endy Effector Tool 1 Controller status
	BOOL bCTC;   // Endy Effector Tool 2  Controller status
	BOOL bETC3;  // Endy Effector Tool 3  Controller status

				 // Limit Switch Status

	BOOL bXNL;  // Extreme North Limit Switch Status
	BOOL bXWL;  // Extreme West Limit Switch Status
	BOOL bXSL;  // Extreme South Limit Switch Status
	BOOL bXEL;  // Extreme East Limit Switch Status
	BOOL bHNSL; // North Axis Home Switch
	BOOL bHEWL; // West Axis Home Switch
	BOOL bHELAC1; // Linear Actuator 1 Extreme Limit Switch Status
	BOOL bHELAC2; // Linear Actuator 2 Extreme Limit Switch Status
	BOOL bHELAC3; // Linear Actuator 3 Extreme Limit Switch Status
	BOOL bBNL;  // North South Axis Brake Hold and Release Output Status
	BOOL bBEL;  // East West Axis Brake Hold and Release Output Status


	WORD wDigInStateNS, wDigOutStateNS, wDigInStateEW, wDigOutStateEW, wDigInStateELAC1, wDigInStateELAC2, wDigInStateELAC3;

	BOOL bCommFlag;

	LONG pPositionIsNS;
	LONG pPositionIsEW;
	LONG pPositionIsLA1;
	LONG pPositionIsLA2;
	LONG pPositionIsLA3;
	LONG pPositionIsETC2;
	LONG pPositionIsETC3;
	LONG pPositionIsCTC;

	int m_iCmdCntsNS;  //Adjusting Position for NS in Counts
	int m_iCmdCntsEW;  //Adjusting Position for EW in Counts
	int TONSEW;        // Time out for adjusting motion of NS & EW in msec
	int TONSEWHOMING;  // Time out for homing of NS & EW in msec

					   //Homing Parameters

	DWORD dwHomingAccNS;
	DWORD dwSpeedSwitchNS;
	DWORD dwSpeedIndexNS;
	WORD wCurrentThresholdNS;
	long lHomingPositionNS;
	long lOffsetNS;

	DWORD dwHomingAccEW;
	DWORD dwSpeedSwitchEW;
	DWORD dwSpeedIndexEW;
	WORD wCurrentThresholdEw;
	long lHomingPositionEW;
	long lOffsetEW;

	BOOL bHomeFlag;
	BOOL bHomeandTestFlag;
	BOOL bParkFlag;
	BOOL bHomeELAC1Flag;

	int iParkPosCntsNS;
	int iParkPosCntsEW;

	int m_iCmdCntsELAC1;// Counts = 36mm Linear displacement
	DWORD dwHomingAccELAC1, dwSpeedSwitchELAC1, dwSpeedIndexELAC1;
	WORD wCurrentThresholdELAC1;
	long lHomingPositionELAC1, lOffsetELAC1;


	
	unsigned int uiTOLA;

	int m_iCmdCntsELAC2;// Counts = 36mm Linear displacement
	DWORD dwHomingAccELAC2, dwSpeedSwitchELAC2, dwSpeedIndexELAC2;
	WORD wCurrentThresholdELAC2;
	long lHomingPositionELAC2, lOffsetELAC2;


	BOOL bHomeELAC2Flag;

	int m_iCmdCntsELAC3;// Counts = 36mm Linear displacement
	DWORD dwHomingAccELAC3, dwSpeedSwitchELAC3, dwSpeedIndexELAC3;
	WORD wCurrentThresholdELAC3;
	long lHomingPositionELAC3, lOffsetELAC3;


	BOOL bHomeELAC3Flag;

	_int8 pOperationMode;
	DWORD MaxVelocity;
	DWORD MaxAcceleration;
	
	BYTE m_UserInputPolarity;

	DWORD dwHomingAccCTC, dwSpeedSwitchCTC, dwSpeedIndexCTC;
	WORD wCurrentThresholdCTC;
	long lHomingPositionCTC, lOffsetCTC;

	BOOL bHomeCTCFlag;
	int m_iCmdCntsCTC;


	bool bMoveWithCurFlagELAC1;
	bool bMoveWithCurFlagCTC;

	public:
		int iLocGrid[40][25][9];
public:
	int NSLINES[29] = { { 0 } }, EWLINES[15] = { { 0 } }, E1NSLINES[29] = { { 0 } }, E2NSO[29] = { { 0 } }, E3NSO[29] = { { 0 } }, E1EWLINES[15] = { { 0 } }, E2EWO[15] = { { 0 } }, E3EWO[15] = { { 0 } }, ZO1[29] = { { 0 } }, ZO2[29] = { { 0 } }, ZO3[29] = { { 0 } };

public:
	BOOL bSelectLocFlagNS;
public:
	BOOL bSelectLocFlagEW;

public:
	int m_iLocSelectedNS;
public:
	int m_iLocSelectedEW;
public:
	BOOL bMove2PosFlag;

	DWORD SProfileVelocityNS;
	DWORD SProfileAccelerationNS;
	DWORD SProfileDeccelerationNS;

	DWORD SProfileVelocityEW;
	DWORD SProfileAccelerationEW;
	DWORD SProfileDeccelerationEW;

	DWORD MProfileVelocityNS;
	DWORD MProfileAccelerationNS;
	DWORD MProfileDeccelerationNS;

	DWORD MProfileVelocityEW;
	DWORD MProfileAccelerationEW;
	DWORD MProfileDeccelerationEW;

	DWORD FProfileVelocityNS;
	DWORD FProfileAccelerationNS;
	DWORD FProfileDeccelerationNS;

	DWORD FProfileVelocityEW;
	DWORD FProfileAccelerationEW;
	DWORD FProfileDeccelerationEW;

	DWORD SProfileVelocityLA1;
	DWORD SProfileAccelerationLA1;
	DWORD SProfileDeccelerationLA1;

	DWORD MProfileVelocityLA1;
	DWORD MProfileAccelerationLA1;
	DWORD MProfileDeccelerationLA1;

	DWORD FProfileVelocityLA1;
	DWORD FProfileAccelerationLA1;
	DWORD FProfileDeccelerationLA1;

	LONG pVelocityIsAveraged;

	LONG NSdiff;
	LONG EWdiff;

	BOOL bMoveWithVelFlag;
	bool bMoveWithCurFlagELAC2;

	LONG pVelocityIsAveragedLA2;
	long m_lActualCntsELAC2;


	DWORD SProfileVelocityLA2;
	DWORD SProfileAccelerationLA2;
	DWORD SProfileDeccelerationLA2;

	DWORD MProfileVelocityLA2;
	DWORD MProfileAccelerationLA2;
	DWORD MProfileDeccelerationLA2;

	DWORD FProfileVelocityLA2;
	DWORD FProfileAccelerationLA2;
	DWORD FProfileDeccelerationLA2;
	LONG pVelocityIsAveragedCTC;
	LONG pVelocityIsAveragedLA1;
	
	LONG pVelocityIsAveragedLA3;
	LONG pVelocityIsAveragedETC2;
	LONG pVelocityIsAveragedETC3;
	LONG pVelocityIsAveragedEW;
	LONG pVelocityIsAveragedNS;

	CString m_login_name;
	CString m_login_passowrd;

	CString PM_selected_Location;
	LONG startposetc2;
	LONG startposetc3;
	float notetc2;
	float notetc3;
	LONG targetposition;

protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
