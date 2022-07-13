
// MfcDbAdcDlg.h: 헤더 파일
//

#pragma once

// * 추가 부분 시작 *
#include "SerialCom.h"
#include <vector>
using namespace std;
#include "CMysqlController.h"
// * 추가 부분 끝 *

// CMfcDbAdcDlg 대화 상자
class CMfcDbAdcDlg : public CDialogEx
{
// 생성입니다.
public:
	CMfcDbAdcDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDBADC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	/* 추가 부분 시작 */
	CSerialComm* m_comm;
	BOOL comport_state;



protected:
	CComboBox m_combo_comport_list;
	CComboBox m_combo_baudrate_list;
	CString m_str_comport;
	CString m_combo_baudrate;

	afx_msg LRESULT CMfcDbAdcDlg::OnReceive(WPARAM length, LPARAM lParam);
	afx_msg LRESULT CMfcDbAdcDlg::OnThreadClosed(WPARAM wParam, LPARAM lParam);
	
public:

	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnCbnSelchangeComboBaudrate();
	afx_msg void OnBnClickedBtConnect();
	vector<char> rx;
	/* 추가 부분 끝 */
	CListCtrl m_list;
	CListCtrl m_list2;
	void CMfcDbAdcDlg::RenewListControl(int tbNum);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnDestroy();
};
