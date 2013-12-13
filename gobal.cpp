#include "global.h"

//Device Handles
HFILE   g_hTs = INVALID_HANDLE_VALUE;
HFILE   g_hRtc = INVALID_HANDLE_VALUE;
HFILE   g_hKeyBoard = INVALID_HANDLE_VALUE;

DWORD		g_uiTimeLastAction = 0;
BOOL            g_uiBuildMenu = FALSE;
USER_INFO       g_UserInfoTemp;
