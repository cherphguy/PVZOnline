#pragma once
#include "MinHook.h"
#include <atlstr.h>
#include "string"
#include "Windows.h"
void doWinMessageBox(std::string text) {
    CString str(text.c_str());
    LPCTSTR lpcstr = str;
   MessageBox(NULL, lpcstr, NULL, MB_OK);
}

void HandleMinHookError(MH_STATUS status) {
    if (status != MH_OK) {
        std::string statusAsString = MH_StatusToString(status);
        doWinMessageBox(statusAsString);
    }
}