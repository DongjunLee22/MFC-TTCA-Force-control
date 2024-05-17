#pragma once

#include "ThreadFunctions.h"

// 사용자 정의 메시지 정의
#define WM_UPDATE_UI (WM_USER + 1)

// 데이터 구조체 정의
struct UIUpdateData
{
    float pos[3];
    int rand_force;
    float freq;
};

// CTESTForcecontrolv03Dlg 대화 상자
class CTESTForcecontrolv03Dlg : public CDialogEx
{
    // 생성입니다.
public:
    CTESTForcecontrolv03Dlg(CWnd* pParent = nullptr); // 표준 생성자입니다.

    // 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TEST_FORCE_CONTROL_V03_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 지원입니다.

    // 구현입니다.
protected:
    HICON m_hIcon;

    // 생성된 메시지 맵 함수
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

public:
    // Button
    afx_msg void OnBnClickedButStart();
    afx_msg void OnBnClickedButClose();
    afx_msg void OnBnClickedButForce();

    // Msg
    CString Status_gui_str;
    CEdit msg_status_gui;
    
    CEdit m_var_force;
    CEdit m_var_freq_force;
    CEdit m_var_freq_UI;
    
    CEdit var_posX;
    CEdit var_posY;
    CEdit var_posZ;

    // Variable
    float var_freq_force; // 주파수 측정 결과를 저장할 변수
    float ini_pos_actual[3] = { 0.0, 0.0, 0.0 }; // 초기 위치

    // Flag
    int flag_thread_force;
    int flag_start;
    int flag_thread_polishing;

    // Thread-related
    CWinThread* m_pThread_force;
    bool m_bRunThread_force;
    CWinThread* m_pThread_polishing;
    bool m_bRunThread_polishing;

    // 사용자 정의 메시지 핸들러
    afx_msg LRESULT OnUpdateUI(WPARAM wParam, LPARAM lParam);
};
