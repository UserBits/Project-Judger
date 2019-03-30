// (C)2019 Bits.

//±àÒë

using namespace std;

/*
val=0 ±àÒëÍ¨¹ı
val>0 ´íÎó
val=-1 ±àÒë³¬Ê±
val=-2 Î´Öª´íÎó
*/

inline int compile(string s, string dir, string cmd){
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb           = sizeof(STARTUPINFO);
	si.dwFlags      = STARTF_USESHOWWINDOW;
	si.wShowWindow  = SW_HIDE;
	PROCESS_INFORMATION pi;
	if(!CreateProcess(TEXT(s.c_str()), (LPSTR)cmd.c_str(), NULL, NULL, FALSE,
                   0, NULL, dir.c_str(), &si, &pi)){
		TerminateProcess(pi.hProcess, 0);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return -2;
	}
	DWORD res, exitcode;
	res = WaitForSingleObject(pi.hProcess, 10000); // 10 sec
	GetExitCodeProcess(pi.hProcess, &exitcode);
	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
 	if(res == WAIT_TIMEOUT)
        return -1;
    if(exitcode > 0)
        return 1;
    return 0;
}
