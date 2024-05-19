#include "pch.h"
#include "UtilityFunctions.h"

void SetEditText(CEdit& editControl, float value)
{
    CString str;
    str.Format(_T("%.2f"), value);
    editControl.SetWindowTextW(str);
}

void TTCAcontrol(float Fd, float F_total, float& TTCA_gma_hat, float& TTCA_f_des_dot,
    float& F_old, float& F_old_time, float TTCA_alpha, float TTCA_kf,
    float current_time, float& vz_target, float& TTCA_err_f)
{
    TTCA_err_f = Fd - F_total;

    // Desired force rate change computation
    TTCA_f_des_dot = (F_total - F_old) / (current_time - F_old_time);

    // Gradient update law
    TTCA_gma_hat += -TTCA_alpha * TTCA_f_des_dot * TTCA_err_f;

    // Update vz_target
    vz_target = (TTCA_gma_hat * TTCA_f_des_dot) - (TTCA_kf * TTCA_err_f);

    // Update previous values
    F_old = F_total;
    F_old_time = current_time;
}