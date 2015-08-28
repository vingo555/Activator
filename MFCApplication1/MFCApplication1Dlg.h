
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	BOOL OnStart();
	BOOL OnStop();
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CHotKeyCtrl m_hotKeyCtrl;
	int m_selection;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	long m_nTimeInterval;
	UINT_PTR m_nIDEvent;
	afx_msg void OnBnClickedRadioKey();
	afx_msg void OnBnClickedRadioMouse();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
