// 24.05.17 Ver.1
#include "pch.h"
#include "framework.h"
#include "TEST_Force_control_v03.h"
#include "TEST_Force_control_v03Dlg.h"
#include "afxdialogex.h"

#include "ThreadFunctions.h"
#include "UtilityFunctions.h"
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CTESTForcecontrolv03Dlg::CTESTForcecontrolv03Dlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TEST_FORCE_CONTROL_V03_DIALOG, pParent),
    m_pThread_force(nullptr),
    m_bRunThread_force(false),
    m_pThread_polishing(nullptr),
    m_bRunThread_polishing(false),
    flag_start(0),
    flag_thread_force(0),
    flag_thread_polishing(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTESTForcecontrolv03Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_Status, msg_status_gui);
    DDX_Control(pDX, IDC_EDIT_force, m_var_force);
    DDX_Control(pDX, IDC_EDIT_freq_force, m_var_freq_force);
    DDX_Control(pDX, IDC_EDIT_freq_UI, m_var_freq_UI);
    DDX_Control(pDX, IDC_EDIT_posX, var_posX);
    DDX_Control(pDX, IDC_EDIT_posY, var_posY);
    DDX_Control(pDX, IDC_EDIT_posZ, var_posZ);
}

BEGIN_MESSAGE_MAP(CTESTForcecontrolv03Dlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUT_Start, &CTESTForcecontrolv03Dlg::OnBnClickedButStart)
    ON_BN_CLICKED(IDC_BUT_Close, &CTESTForcecontrolv03Dlg::OnBnClickedButClose)
    ON_BN_CLICKED(IDC_BUT_Force, &CTESTForcecontrolv03Dlg::OnBnClickedButForce)
    ON_MESSAGE(WM_UPDATE_UI, &CTESTForcecontrolv03Dlg::OnUpdateUI)
END_MESSAGE_MAP()

LRESULT CTESTForcecontrolv03Dlg::OnUpdateUI(WPARAM wParam, LPARAM lParam)
{
    UIUpdateData* data = reinterpret_cast<UIUpdateData*>(lParam);
    SetEditText(var_posX, data->pos[0]);
    SetEditText(var_posY, data->pos[1]);
    SetEditText(var_posZ, data->pos[2]);
    CString strFreq;
    strFreq.Format(_T("%.2f Hz"), data->freq);
    m_var_freq_force.SetWindowTextW(strFreq);
    delete data; // 동적 할당된 메모리 해제
    return 0;
}

BOOL CTESTForcecontrolv03Dlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);  // 큰 아이콘을 설정합니다.
    SetIcon(m_hIcon, FALSE); // 작은 아이콘을 설정합니다.

    return TRUE; // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTESTForcecontrolv03Dlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CTESTForcecontrolv03Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CTESTForcecontrolv03Dlg::OnBnClickedButStart()
{
    flag_start = 1;
    OnBnClickedButForce();

    if (flag_thread_force == 1 && !m_bRunThread_force)
    {
        m_bRunThread_force = true; // Thread가 실행 중임을 표현
        m_pThread_force = AfxBeginThread(Thread_force_test, this);
        Status_gui_str = _T("Random Force 생성 Thread 동작 중...");
        msg_status_gui.SetWindowTextW(Status_gui_str);
    }
}

void CTESTForcecontrolv03Dlg::OnBnClickedButForce()
{
    if (flag_start == 1)
    {
        flag_thread_force = 1;
    }
    else
    {
        OnBnClickedButClose();
    }
}

void CTESTForcecontrolv03Dlg::OnBnClickedButClose()
{
    m_bRunThread_force = false; // Thread를 종료시킴
    if (m_pThread_force != nullptr)
    {
        WaitForSingleObject(m_pThread_force->m_hThread, INFINITE); // Thread가 종료될 때까지 대기함
        m_pThread_force = nullptr;
    }

    EndDialog(IDOK);
}
