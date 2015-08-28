
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_selection(0)
	, m_nTimeInterval(60), m_nIDEvent(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOTKEY_VALUE, m_hotKeyCtrl);
	DDX_Text(pDX, IDC_EDIT_TIME_INTERVAL, m_nTimeInterval);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_KEY, &CMFCApplication1Dlg::OnBnClickedRadioKey)
	ON_BN_CLICKED(IDC_RADIO_MOUSE, &CMFCApplication1Dlg::OnBnClickedRadioMouse)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CButton *pCheck = (CButton*) GetDlgItem(IDC_RADIO_KEY);

	pCheck->SetCheck(TRUE);

	// TODO: Add extra initialization here
	m_hotKeyCtrl.EnableWindow(FALSE);
	m_hotKeyCtrl.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	
	OnStart();
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnStop();

	CDialogEx::OnCancel();
}

BOOL CMFCApplication1Dlg::OnStart()
{
	UpdateData();
	m_nIDEvent = SetTimer(0, m_nTimeInterval * 1000, NULL);

	CString strTitle;
	GetWindowText(strTitle);
	strTitle += "---Running";

	SetWindowText(strTitle);

	return TRUE;
}
BOOL CMFCApplication1Dlg::OnStop()
{
	if (m_nIDEvent != -1)
	{
		KillTimer(m_nIDEvent);
	}

	return TRUE;
}

void CMFCApplication1Dlg::OnBnClickedRadioKey()
{
	m_hotKeyCtrl.EnableWindow();
	m_hotKeyCtrl.SetFocus();
	//TRACE(L"The current selection is : %d\n", m_selection);
}


void CMFCApplication1Dlg::OnBnClickedRadioMouse()
{
	m_hotKeyCtrl.EnableWindow(FALSE);
}


void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	static bool flag = false;

	srand((time_t)time(0));

	if (m_selection == 0)
	{
		//DWORD keyValue = m_hotKeyCtrl.GetHotKey();
		if (flag == false)
		{
			keybd_event(VK_DOWN, 0x8f, 0, 0); 
			keybd_event(VK_DOWN, 0x8f, KEYEVENTF_KEYUP, 0); 

			flag = true;
		} else {
			keybd_event(VK_UP, 0x8f, 0, 0); 
			keybd_event(VK_UP, 0x8f, KEYEVENTF_KEYUP, 0); 

			flag = false;
		}

	}
	else if (m_selection == 1)
	{
		mouse_event(MOUSEEVENTF_MOVE, rand() %1000, rand() % 1000, 0, 0);
	}

	CDialogEx::OnTimer(nIDEvent);
}
