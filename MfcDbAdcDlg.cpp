
// MfcDbAdcDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MfcDbAdc.h"
#include "MfcDbAdcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
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


// CMfcDbAdcDlg 대화 상자



CMfcDbAdcDlg::CMfcDbAdcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDBADC_DIALOG, pParent)
	, m_str_comport(_T(""))
	, m_combo_baudrate(_T(""))
	, m_Date(COleDateTime::GetCurrentTime())
	, m_StartTime(COleDateTime::GetCurrentTime())
	, m_EndTime(COleDateTime::GetCurrentTime())

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcDbAdcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_comport_list);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_str_comport);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST2, m_list2);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_Date);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER7, m_StartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER8, m_EndTime);

	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_CtrlDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER7, m_CtrlStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER8, m_CtrlEndTime);
}

BEGIN_MESSAGE_MAP(CMfcDbAdcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	// * 추가 부분 시작 *
	ON_MESSAGE(WM_MYRECEIVE, &CMfcDbAdcDlg::OnReceive)
	ON_MESSAGE(WM_MYCLOSE, &CMfcDbAdcDlg::OnThreadClosed)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPORT, &CMfcDbAdcDlg::OnCbnSelchangeComboComport)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUDRATE, &CMfcDbAdcDlg::OnCbnSelchangeComboBaudrate)
	ON_BN_CLICKED(IDC_BT_CONNECT, &CMfcDbAdcDlg::OnBnClickedBtConnect)
	// * 추가 부분 끝 *
	ON_BN_CLICKED(IDC_BUTTON2, &CMfcDbAdcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMfcDbAdcDlg::OnBnClickedButton3)
	ON_WM_DESTROY()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER4, &CMfcDbAdcDlg::OnDtnDatetimechangeDatetimepicker4)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER7, &CMfcDbAdcDlg::OnDtnDatetimechangeDatetimepicker7)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER8, &CMfcDbAdcDlg::OnDtnDatetimechangeDatetimepicker8)
	ON_BN_CLICKED(IDC_BUTTON1, &CMfcDbAdcDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_MESSAGE(MYMSG, &CMfcDbAdcDlg::OnMymsg)
	ON_MESSAGE(MYTERMINATEFLAG, &CMfcDbAdcDlg::OnMyterminateflag)
END_MESSAGE_MAP()


// CMfcDbAdcDlg 메시지 처리기

BOOL CMfcDbAdcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// * 추가 부분 시작 *
	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));
	m_combo_comport_list.AddString(_T("COM5"));
	m_combo_comport_list.AddString(_T("COM6"));
	m_combo_comport_list.AddString(_T("COM7"));
	m_combo_comport_list.AddString(_T("COM8"));
	m_combo_comport_list.AddString(_T("COM9"));
	m_combo_comport_list.AddString(_T("COM10"));

	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("115200"));

	comport_state = false;
	GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM9");
	m_combo_baudrate = _T("115200");
	UpdateData(FALSE);
	
	// * 추가 부분 끝 *
	m_list.SetExtendedStyle(
		LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_list.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(1, _T("시간"), LVCFMT_CENTER, 200);
	m_list.InsertColumn(2, _T("ADC값"), LVCFMT_CENTER, 100);


	m_list2.SetExtendedStyle(
		LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_list2.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 80);
	m_list2.InsertColumn(1, _T("시간"), LVCFMT_CENTER, 200);
	m_list2.InsertColumn(2, _T("ADC값"), LVCFMT_CENTER, 100);


	UpdateData(true);

	CString str = m_Date.Format(_T("%Y-%m-%d  "));
	str += m_StartTime.Format(_T("%H:%M:%S ~ "));
	str += m_EndTime.Format(_T("%H:%M:%S"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);

	
	CString formatStyle = _T("HH:mm:ss");
	m_CtrlStartTime.SetFormat(formatStyle);
	m_CtrlEndTime.SetFormat(formatStyle);

	SetTimer(1, 5000, NULL);

	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMfcDbAdcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMfcDbAdcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMfcDbAdcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CMfcDbAdcDlg::OnCbnSelchangeComboComport()	// * 추가 부분 *
{
	UpdateData();
}


void CMfcDbAdcDlg::OnCbnSelchangeComboBaudrate()	// * 추가 부분 *
{
	UpdateData();
}


void CMfcDbAdcDlg::OnBnClickedBtConnect()	// * 추가 부분 *
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
			//GetDlgItem(IDC_BT_SEND)->EnableWindow(false); //버튼 비활성화
		}
	}
	else
	{
		m_comm = new CSerialComm(_T("\\\\.\\") + m_str_comport, m_combo_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("COM 포트열림"));
			comport_state = true;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("CLOSE"));
			//GetDlgItem(IDC_BT_SEND)->EnableWindow(true); //버튼 클릭할 수 있는 상태
		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}
}


afx_msg LRESULT CMfcDbAdcDlg::OnReceive(WPARAM length, LPARAM lParam)	// * 추가 부분 *
{
	CString str;
	char* data = new char[length + 1];

	if (m_comm)
	{
		m_comm->Receive(data, length);	// Length 길이만큼 데이터 받음.
		

		for (int i = 0; i < length; i++)
		{
			rx.push_back(data[i]);
		}
		while (rx.size() >= 7)
		{
			if (rx.at(0) == 'P' && rx.at(6) == '\n')
			{
				if(rx.at(1)=='A')
				{
					int tempValue = 0;
					tempValue = (rx.at(2) - '0') * 1000 + (rx.at(3) - '0') * 100 + (rx.at(4) - '0') * 10
						+ (rx.at(5) - '0') * 1;

										
					CString temp;
					CString strTempValue;
					CString strTempNow;

					temp = _T("INSERT INTO tb_adc1(datetime, adc) VALUES('");
					COleDateTime now = COleDateTime::GetCurrentTime();
					strTempNow = now.Format(_T("%Y-%m-%d %H:%M:%S', "));
					temp += strTempNow;
					strTempValue.Format(_T("%d"), tempValue);
					temp += strTempValue;
					temp += _T("); ");

					querys.push_back(temp);
										
				}else if(rx.at(1)=='B')
				{
					int tempValue = 0;
					tempValue = (rx.at(2) - '0') * 1000 + (rx.at(3) - '0') * 100 + (rx.at(4) - '0') * 10
						+ (rx.at(5) - '0') * 1;

				
					CString temp;
					CString strTempValue;
					CString strTempNow;

					temp = _T("INSERT INTO tb_adc2(datetime, adc) VALUES('");
					COleDateTime now = COleDateTime::GetCurrentTime();
					strTempNow = now.Format(_T("%Y-%m-%d %H:%M:%S', "));
					temp += strTempNow;
					strTempValue.Format(_T("%d"), tempValue);
					temp += strTempValue;
					temp += _T("); ");

					querys.push_back(temp);
					
				}

				rx.erase(rx.begin(), rx.begin() + 6);

			}
			else if (rx.at(0) != 'P')
			{
				rx.erase(rx.begin());

			}
			else if (rx.at(6) != '\n')
			{
				rx.erase(rx.begin(), rx.begin() + 6);
			}

		}
		
		UpdateData(false);

		str = "";
	}
	delete data;


	return 0;
}


afx_msg LRESULT CMfcDbAdcDlg::OnThreadClosed(WPARAM length, LPARAM lParam)	// * 추가 부분 *
{
	((CSerialComm*)lParam)->HandleClose();
	delete ((CSerialComm*)lParam);

	return 0;
}


void CMfcDbAdcDlg::RenewListControl(int tbNum)
{
	CMysqlController conn;
	vector<DataRow*> row;

	switch(tbNum)
	{
	case 1:
		m_list.DeleteAllItems();
		if (conn.SelectQuery("select * from tb_adc1 LIMIT 1000", row) == true){}
		for (size_t i = 0; i < row.size(); i++)
		{
			m_list.InsertItem(i, row.at(i)->getId());
			m_list.SetItem(i, 1, LVIF_TEXT, row.at(i)->getDateTime(), NULL, NULL, NULL, NULL);
			m_list.SetItem(i, 2, LVIF_TEXT, row.at(i)->getAdcValue(), NULL, NULL, NULL, NULL);
		}
		m_list.SendMessage(WM_VSCROLL, SB_BOTTOM);
		break;
	case 2:
		m_list2.DeleteAllItems();
		if (conn.SelectQuery("select * from tb_adc2 LIMIT 1000", row) == true){}
		for (size_t i = 0; i < row.size(); i++)
		{
			m_list2.InsertItem(i, row.at(i)->getId());
			m_list2.SetItem(i, 1, LVIF_TEXT, row.at(i)->getDateTime(), NULL, NULL, NULL, NULL);
			m_list2.SetItem(i, 2, LVIF_TEXT, row.at(i)->getAdcValue(), NULL, NULL, NULL, NULL);
		}
		m_list2.SendMessage(WM_VSCROLL, SB_BOTTOM);
		break;
	}

	for (size_t i = 0; i < row.size(); i++)
	{
		delete row.at(i);
	}

}

void CMfcDbAdcDlg::OnBnClickedButton2()
{

	RenewListControl(1);
}


void CMfcDbAdcDlg::OnBnClickedButton3()
{
	RenewListControl(2);
}


void CMfcDbAdcDlg::OnDtnDatetimechangeDatetimepicker4(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	UpdateData(TRUE);
	CString str = m_Date.Format(_T("%Y-%m-%d  "));
	str += m_StartTime.Format(_T("%H:%M:%S ~ "));
	str += m_EndTime.Format(_T("%H:%M:%S"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);

	*pResult = 0;
}


void CMfcDbAdcDlg::OnDtnDatetimechangeDatetimepicker7(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	UpdateData(TRUE);
	CString str = m_Date.Format(_T("%Y-%m-%d  "));
	str += m_StartTime.Format(_T("%H:%M:%S ~ "));
	str += m_EndTime.Format(_T("%H:%M:%S"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);

	*pResult = 0;
}


void CMfcDbAdcDlg::OnDtnDatetimechangeDatetimepicker8(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	UpdateData(TRUE);
	CString str = m_Date.Format(_T("%Y-%m-%d  "));
	str += m_StartTime.Format(_T("%H:%M:%S ~ "));
	str += m_EndTime.Format(_T("%H:%M:%S"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);

	*pResult = 0;
}


void CMfcDbAdcDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	COleDateTime currentTime = COleDateTime::GetCurrentTime();
	if(m_Date.m_dt > currentTime.m_dt)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T("오늘 이전의 날짜를 선택해주세요"));
	}else if(m_StartTime > m_EndTime)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T("종료시간이 시작시간보다 빠를수 없습니다"));
	}else
	{
		CMysqlController conn;
		vector<DataRow*> row;

		m_list.DeleteAllItems();

		UpdateData(TRUE);

		CString temp = _T("SELECT * FROM tb_adc1 WHERE datetime >= '");
		CString tempDate = m_Date.Format(_T("%Y-%m-%d "));
		temp += tempDate;
		CString tempStartTime = m_StartTime.Format(_T("%H:%M:%S' and datetime <= '"));
		temp += tempStartTime;
		temp += tempDate;
		CString tempEndTime = m_EndTime.Format(_T("%H:%M:%S'"));
		temp += tempEndTime;

		//SELECT* FROM tb_adc1 WHERE datetime >= '2022-07-14 13:17:31' and datetime <= '2022-07-14 13:17:48'

		if (conn.SelectQuery(LPSTR(LPCTSTR(temp)), row) == true) {}
		for (size_t i = 0; i < row.size(); i++)
		{
			m_list.InsertItem(i, row.at(i)->getId());
			m_list.SetItem(i, 1, LVIF_TEXT, row.at(i)->getDateTime(), NULL, NULL, NULL, NULL);
			m_list.SetItem(i, 2, LVIF_TEXT, row.at(i)->getAdcValue(), NULL, NULL, NULL, NULL);
		}
		m_list.SendMessage(WM_VSCROLL, SB_BOTTOM);

		m_list2.DeleteAllItems();

		temp = _T("SELECT * FROM tb_adc2 WHERE datetime >= '");
		tempDate = m_Date.Format(_T("%Y-%m-%d "));
		temp += tempDate;
		tempStartTime = m_StartTime.Format(_T("%H:%M:%S' and datetime <= '"));
		temp += tempStartTime;
		temp += tempDate;
		tempEndTime = m_EndTime.Format(_T("%H:%M:%S'"));
		temp += tempEndTime;

		if (conn.SelectQuery(LPSTR(LPCTSTR(temp)), row) == true) {}
		for (size_t i = 0; i < row.size(); i++)
		{
			m_list2.InsertItem(i, row.at(i)->getId());
			m_list2.SetItem(i, 1, LVIF_TEXT, row.at(i)->getDateTime(), NULL, NULL, NULL, NULL);
			m_list2.SetItem(i, 2, LVIF_TEXT, row.at(i)->getAdcValue(), NULL, NULL, NULL, NULL);
		}
		m_list2.SendMessage(WM_VSCROLL, SB_BOTTOM);


		for (size_t i = 0; i < row.size(); i++)
		{
			delete row.at(i);
		}
	}
}

UINT deleteOldData(LPVOID LpData)
{
	CMfcDbAdcDlg* target = (CMfcDbAdcDlg*)(LpData);

	CMysqlController conn;

	unsigned long long temp1 = 0;
	unsigned long long temp2 = 0;
	conn.SelectCountQuery("SELECT COUNT(*) FROM tb_adc1 WHERE DATETIME < DATE_SUB(NOW(), INTERVAL 10 MINUTE)", temp1);
	conn.SelectCountQuery("SELECT COUNT(*) FROM tb_adc2 WHERE DATETIME < DATE_SUB(NOW(), INTERVAL 10 MINUTE)", temp2);

	for (int i = 0; i < (temp1 / 1000) + 1; i++)
	{
		if (conn.InsertQuery("DELETE FROM tb_adc1 WHERE DATETIME < DATE_SUB(NOW(), INTERVAL 10 MINUTE) LIMIT 1000") == true) {}
	}

	for (int i = 0; i < (temp2 / 1000) + 1; i++)
	{
		if (conn.InsertQuery("DELETE FROM tb_adc2 WHERE DATETIME < DATE_SUB(NOW(), INTERVAL 10 MINUTE) LIMIT 1000") == true) {}
	}

	SendMessage(target->m_hWnd, MYTERMINATEFLAG, NULL, NULL);

	return 0;
}



void CMfcDbAdcDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	AfxBeginThread(deleteOldData, (LPVOID)this);
	
	return;


	CDialogEx::OnClose();
}


void CMfcDbAdcDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}



UINT handleQuerys(LPVOID LpData)
{
	CMfcDbAdcDlg* target = (CMfcDbAdcDlg*)(LpData);
	CMysqlController conn;
	conn.InsertQuerys(target->querys);

	SendMessage(target->m_hWnd, MYMSG, NULL, NULL);

	return 0;

}


void CMfcDbAdcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		
	AfxBeginThread(handleQuerys, (LPVOID)this);
	
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CMfcDbAdcDlg::OnMymsg(WPARAM wParam, LPARAM lParam)
{
	RenewListControl(1);
	RenewListControl(2);

	return 0;
}


afx_msg LRESULT CMfcDbAdcDlg::OnMyterminateflag(WPARAM wParam, LPARAM lParam)
{
	//OnDestroy();
	EndDialog(IDCANCEL);
	return 0;
}
