#include "pch.h"
#include "UtilityFunctions.h"

void SetEditText(CEdit& editControl, float value)
{
    CString str;
    str.Format(_T("%.2f"), value);
    editControl.SetWindowTextW(str);
}
