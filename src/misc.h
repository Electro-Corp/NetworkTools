/*
    Modified from https://github.com/nmap/npcap/blob/master/Examples/misc/misc.h
*/
#ifdef __WIN32__
#pragma once
#include <tchar.h>
#include <stdio.h>
#include <winuser.h>
#include <sysinfoapi.h>
#include <winbase.h>

static BOOL LoadNpcapDlls() {
    _TCHAR npcap_dir[512];
    UINT len;
    len = GetSystemDirectory(npcap_dir, 480);
    if (!len) {
        fprintf(stderr, "Error in GetSystemDirectory: %x", GetLastError());
        return FALSE;
    }
    _tcscat_s(npcap_dir, 512, _T("\\Npcap"));
    if (SetDllDirectory(npcap_dir) == 0) {
        fprintf(stderr, "Error in SetDllDirectory: %x", GetLastError());
        return FALSE;
    }
    return TRUE;
}
#endif