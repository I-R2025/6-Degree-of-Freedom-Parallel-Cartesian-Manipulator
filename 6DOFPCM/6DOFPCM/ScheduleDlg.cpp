// ScheduleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "6DOFPCM.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"
#include "6DOFPCMView.h"

// CScheduleDlg dialog

IMPLEMENT_DYNAMIC(CScheduleDlg, CDialog)

CScheduleDlg::CScheduleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_Schedule_DLG, pParent)
{

}

CScheduleDlg::~CScheduleDlg()
{
	//delete this;
}

void CScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON63, m_20_K);
	DDX_Control(pDX, IDC_BUTTON76, m_17_L);
	DDX_Control(pDX, IDC_BUTTON79, m_21_L);
	DDX_Control(pDX, IDC_BUTTON91, m_18_M);
	DDX_Control(pDX, IDC_BUTTON90, m_20_M);
	DDX_Control(pDX, IDC_BUTTON139, m_12_R);
	DDX_Control(pDX, IDC_BUTTON138, m_14_R);
	DDX_Control(pDX, IDC_BUTTON148, m_11_S);
	DDX_Control(pDX, IDC_BUTTON147, m_13_S);
	DDX_Control(pDX, IDC_BUTTON146, m_15_S);
	DDX_Control(pDX, IDC_BUTTON156, m_12_T);
	DDX_Control(pDX, IDC_BUTTON155, m_14_T);
	DDX_Control(pDX, IDC_BUTTON75, m_C_T);
	DDX_Control(pDX, IDC_BUTTON33, m_21_G);
	DDX_Control(pDX, IDC_BUTTON38, m_19_G);
	DDX_Control(pDX, IDC_BUTTON32, m_23_G);
	DDX_Control(pDX, IDC_BUTTON48, m_20_H);
	DDX_Control(pDX, IDC_BUTTON43, m_22_H);
	DDX_Control(pDX, IDC_BUTTON23, m_22_F);
	DDX_Control(pDX, IDC_BUTTON24, m_20_F);
	DDX_Control(pDX, IDC_BUTTON64, m_18_K);
}


BEGIN_MESSAGE_MAP(CScheduleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CScheduleDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON4, &CScheduleDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &CScheduleDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON5, &CScheduleDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CScheduleDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CScheduleDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON64, &CScheduleDlg::OnBnClickedButton64)
	ON_BN_CLICKED(IDC_BUTTON75, &CScheduleDlg::OnBnClickedButton75)
	ON_BN_CLICKED(IDC_BUTTON63, &CScheduleDlg::OnBnClickedButton63)
	ON_BN_CLICKED(IDC_BUTTON76, &CScheduleDlg::OnBnClickedButton76)
	ON_BN_CLICKED(IDC_BUTTON79, &CScheduleDlg::OnBnClickedButton79)
	ON_BN_CLICKED(IDC_BUTTON91, &CScheduleDlg::OnBnClickedButton91)
	ON_BN_CLICKED(IDC_BUTTON90, &CScheduleDlg::OnBnClickedButton90)
	ON_BN_CLICKED(IDC_BUTTON139, &CScheduleDlg::OnBnClickedButton139)
	ON_BN_CLICKED(IDC_BUTTON138, &CScheduleDlg::OnBnClickedButton138)
	ON_BN_CLICKED(IDC_BUTTON148, &CScheduleDlg::OnBnClickedButton148)
	ON_BN_CLICKED(IDC_BUTTON147, &CScheduleDlg::OnBnClickedButton147)
	ON_BN_CLICKED(IDC_BUTTON146, &CScheduleDlg::OnBnClickedButton146)
	ON_BN_CLICKED(IDC_BUTTON156, &CScheduleDlg::OnBnClickedButton156)
	ON_BN_CLICKED(IDC_BUTTON155, &CScheduleDlg::OnBnClickedButton155)
	ON_BN_CLICKED(IDC_BUTTON33, &CScheduleDlg::OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON38, &CScheduleDlg::OnBnClickedButton38)
	ON_BN_CLICKED(IDC_BUTTON32, &CScheduleDlg::OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON48, &CScheduleDlg::OnBnClickedButton48)
	ON_BN_CLICKED(IDC_BUTTON43, &CScheduleDlg::OnBnClickedButton43)
	ON_BN_CLICKED(IDC_BUTTON23, &CScheduleDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CScheduleDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON158, &CScheduleDlg::OnBnClickedButton158)
	ON_BN_CLICKED(IDC_BUTTON29, &CScheduleDlg::OnBnClickedButton29)
	
END_MESSAGE_MAP()


// CScheduleDlg message handlers


void CScheduleDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CScheduleDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialog::OnPaint() for painting messages

	CRect RECT; CWnd* pWnd;
	
		{
			/*CBitmap m_bitmap;
			BITMAP bmp;
			CDC dc, *pDC;
	
			m_bitmap.LoadBitmapA(IDB_BKGND);
			m_bitmap.GetBitmap(&bmp);
	
			pDC = this->GetDC();
			dc.CreateCompatibleDC(pDC);
			dc.SelectObject(m_bitmap);
			//pDC->BitBlt(1115, 0, bmp.bmWidth, bmp.bmHeight, &dc, 0, 0, SRCCOPY);
			pDC->StretchBlt(0, 0, 1150, 540, &dc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);*/
			
			this->GetClientRect(&RECT);
			CDC MemDC;
			CBitmap tiledImage; BITMAP bmp;
			MemDC.CreateCompatibleDC(&dc);
			tiledImage.LoadBitmapA(IDB_BKGND); tiledImage.GetBitmap(&bmp);
			MemDC.SelectObject(&tiledImage);
			dc.StretchBlt(0, 0, 1083, 625, &MemDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			MemDC.DeleteDC();
			DeleteObject(tiledImage);// DeleteObject(&bmp);
		}

		DeleteDC(dc);
}


void CScheduleDlg::OnBnClickedButton4()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("26-D"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 16;
		pDoc->m_iLocSelectedEW = 3;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "26-D"; 
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton8()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("18-D"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 13;
		pDoc->m_iLocSelectedEW = 0;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "18-D";
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton5()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("24-D"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 19;
		pDoc->m_iLocSelectedEW = 0;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "24-D";
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton6()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("22-D"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 17;
		pDoc->m_iLocSelectedEW = 0;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "22-D";
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton7()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("20-D"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 15;
		pDoc->m_iLocSelectedEW = 0;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "20-D";
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton64()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("18-K"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 13;
		pDoc->m_iLocSelectedEW = 6;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "18-K";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton75()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("19-L"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 14;
		pDoc->m_iLocSelectedEW = 7;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "19-L";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton63()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("20-K"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 15;
		pDoc->m_iLocSelectedEW = 6;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "20-K";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton76()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("17-L"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 12;
		pDoc->m_iLocSelectedEW = 7;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "17-L";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton79()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("21-L"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 16;
		pDoc->m_iLocSelectedEW = 7;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "21-L";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton91()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("18-M"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 13;
		pDoc->m_iLocSelectedEW = 8;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "18-M";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton90()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("20-M"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 15;
		pDoc->m_iLocSelectedEW = 8;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "20-M";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton139()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("12-R"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 7;
		pDoc->m_iLocSelectedEW = 12;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "12-R";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton138()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("14-R"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 9;
		pDoc->m_iLocSelectedEW = 12;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "14-R";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton148()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("11-S"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 6;
		pDoc->m_iLocSelectedEW = 13;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "11-S";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton147()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("13-S"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 8;
		pDoc->m_iLocSelectedEW = 13;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "13-S";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton146()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("15-S"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 10;
		pDoc->m_iLocSelectedEW = 13;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "15-S";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton156()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("12-T"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 7;
		pDoc->m_iLocSelectedEW = 14;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "12-T";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton155()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("14-T"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 9;
		pDoc->m_iLocSelectedEW = 14;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "14-T";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton33()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("21-G"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 16;
		pDoc->m_iLocSelectedEW = 3;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "21-G";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton38()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("19-G"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 14;
		pDoc->m_iLocSelectedEW = 3;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "19-G";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton32()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("23-G"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 18;
		pDoc->m_iLocSelectedEW = 3;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "23-G";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton48()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("20-H"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

	//	pDoc->m_iLocSelectedNS = 15;
	//	pDoc->m_iLocSelectedEW = 4;

		pDoc->m_iLocSelectedNS = 15;
		pDoc->m_iLocSelectedEW = 2;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "20-H";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton43()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("22-H"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 17;
		pDoc->m_iLocSelectedEW = 4;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "22-H";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton23()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("22-F"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

		pDoc->m_iLocSelectedNS = 17;
		pDoc->m_iLocSelectedEW = 2;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "22-F";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


void CScheduleDlg::OnBnClickedButton24()
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
	if (pDoc->m_usertype_received == "Manager")
	{
		CString tempmsg;
		Assembly = (_T("20-F"));
		pView->m_ListBox.AddString(Assembly);   pDoc->RA_LogEvents(Assembly + _T("\tAdded in Schedule")); tempmsg = _T("INFO: ") + Assembly; tempmsg += _T(" "); tempmsg += _T("Added in Schedule"); pView->Count++;
	}


	if (pDoc->m_usertype_received == "Operator")
	{

	//	pDoc->m_iLocSelectedNS = 15;
	//	pDoc->m_iLocSelectedEW = 2;

		pDoc->m_iLocSelectedNS = 15;
		pDoc->m_iLocSelectedEW = 4;

		// Creating LA01 Modeless Dialog

		pDoc->PM_selected_Location = "20-F";
		pDoc->PM_ReadLocations();
		pView->ShowWindowNumber(1);

	}
}


BOOL CScheduleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_18_K.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_18_K.m_bTransparent = false;//reg for use bg color
	m_18_K.SetFaceColor(RGB(128, 128, 0), true);

	m_20_K.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_20_K.m_bTransparent = false;//reg for use bg color
	m_20_K.SetFaceColor(RGB(128, 128, 0), true);

	m_17_L.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_17_L.m_bTransparent = false;//reg for use bg color
	m_17_L.SetFaceColor(RGB(128, 128, 0), true);

	m_21_L.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_21_L.m_bTransparent = false;//reg for use bg color
	m_21_L.SetFaceColor(RGB(128, 128, 0), true);

	m_18_M.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_18_M.m_bTransparent = false;//reg for use bg color
	m_18_M.SetFaceColor(RGB(128, 128, 0), true);

	m_20_M.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_20_M.m_bTransparent = false;//reg for use bg color
	m_20_M.SetFaceColor(RGB(128, 128, 0), true);

	m_12_R.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_12_R.m_bTransparent = false;//reg for use bg color
	m_12_R.SetFaceColor(RGB(128, 128, 0), true);

	m_14_R.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_14_R.m_bTransparent = false;//reg for use bg color
	m_14_R.SetFaceColor(RGB(128, 128, 0), true);

	m_11_S.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_11_S.m_bTransparent = false;//reg for use bg color
	m_11_S.SetFaceColor(RGB(128, 128, 0), true);

	m_13_S.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_13_S.m_bTransparent = false;//reg for use bg color
	m_13_S.SetFaceColor(RGB(128, 128, 0), true);

	m_15_S.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_15_S.m_bTransparent = false;//reg for use bg color
	m_15_S.SetFaceColor(RGB(128, 128, 0), true);

	m_12_T.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_12_T.m_bTransparent = false;//reg for use bg color
	m_12_T.SetFaceColor(RGB(128, 128, 0), true);

	m_14_T.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_14_T.m_bTransparent = false;//reg for use bg color
	m_14_T.SetFaceColor(RGB(128, 128, 0), true);

	m_C_T.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_C_T.m_bTransparent = false;//reg for use bg color
	m_C_T.SetFaceColor(RGB(128, 128, 0), true);

	m_21_G.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_21_G.m_bTransparent = false;//reg for use bg color
	m_21_G.SetFaceColor(RGB(128, 128, 0), true);

	m_19_G.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_19_G.m_bTransparent = false;//reg for use bg color
	m_19_G.SetFaceColor(RGB(128, 128, 0), true);

	m_23_G.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_23_G.m_bTransparent = false;//reg for use bg color
	m_23_G.SetFaceColor(RGB(128, 128, 0), true);

	m_20_H.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_20_H.m_bTransparent = false;//reg for use bg color
	m_20_H.SetFaceColor(RGB(128, 128, 0), true);

	m_22_H.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_22_H.m_bTransparent = false;//reg for use bg color
	m_22_H.SetFaceColor(RGB(128, 128, 0), true);

	m_22_F.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_22_F.m_bTransparent = false;//reg for use bg color
	m_22_F.SetFaceColor(RGB(128, 128, 0), true);

	m_20_F.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_20_F.m_bTransparent = false;//reg for use bg color
	m_20_F.SetFaceColor(RGB(128, 128, 0), true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CScheduleDlg::OnBnClickedButton158()
{
	// TODO: Add your control notification handler code here

//	m_20_F.EnableWindow(FALSE);

	C6DOFPCMView *pView;
	pView = pView->GetView();
	if (!pView)
	{
		AfxMessageBox("ERROR: Unable to get View pointer");
		return;
	}

	CString strText;
	int i = pView->m_ListBox.GetCount();
	if (i == 0)
	{
		return;
	}
	else
	{
		for (int index = 0; index <= (i -1) ; index++)
		{
			pView->m_ListBox.GetText(index, strText);

			if(strText != "20-F") m_20_F.EnableWindow(FALSE);
			if(strText != "22-F") m_22_F.EnableWindow(FALSE);
			if(strText != "22-H") m_22_H.EnableWindow(FALSE);
			if(strText != "20-H") m_20_H.EnableWindow(FALSE);
			if(strText != "23-G") m_23_G.EnableWindow(FALSE);
			if(strText != "19-G") m_19_G.EnableWindow(FALSE);
			if(strText != "21-G") m_21_G.EnableWindow(FALSE);
			if(strText != "19-L") m_C_T.EnableWindow(FALSE);
			if(strText != "14-T") m_14_T.EnableWindow(FALSE);
			if(strText != "12-T") m_12_T.EnableWindow(FALSE);
			if(strText != "15-S") m_15_S.EnableWindow(FALSE);
			if(strText != "13-S") m_13_S.EnableWindow(FALSE);
			if(strText != "11-S") m_11_S.EnableWindow(FALSE);
			if(strText != "14-R") m_14_R.EnableWindow(FALSE);
			if(strText != "12-R") m_12_R.EnableWindow(FALSE);
			if(strText != "20-M") m_20_M.EnableWindow(FALSE);
			if(strText != "18-M") m_18_M.EnableWindow(FALSE);
			if(strText != "21-L") m_21_L.EnableWindow(FALSE);
			if(strText != "17-L") m_17_L.EnableWindow(FALSE);
			if(strText != "20-K") m_20_K.EnableWindow(FALSE);
			if(strText != "18-K") m_18_K.EnableWindow(FALSE);
		}
	}
	
}




void CScheduleDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
	
}


void CScheduleDlg::OnBnClickedButton29()
{
	// TODO: Add your control notification handler code here

}



