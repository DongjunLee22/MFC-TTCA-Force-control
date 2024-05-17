#pragma once

#include <afxwin.h>

void SetEditText(CEdit& editControl, float value);

void TTCAcontrol(float Fd, float F_total, float& TTCA_gma_hat, float& TTCA_f_des_dot,
    float& F_old, float& F_old_time, float TTCA_alpha, float TTCA_kf,
    float current_time, float& vz_target);
