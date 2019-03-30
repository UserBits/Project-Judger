// (C)2019 Bits.

//运行

using namespace std;

struct limit{ //测试点限制
    int rtime, // ms
    rmemory; // KB
};

struct result{
    int flag,
    utime, // ms
    umemory; // KB
    result(){
        utime = umemory = 0;
        flag = -2;
    }
    result(int x, int y, int z){
        flag = x, utime = y, umemory = z;
    }
};
/*
flag=-1 CE
flag=0  AC
flag=1  WA
flag=2  TLE
flag=3  MLE
flag=4  OLE
flag=5  RE
flag=6  UKE
*/

inline result execute(string s, string dir, limit lx){
	result rx;
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb           = sizeof(STARTUPINFO);
	si.dwFlags      = STARTF_USESHOWWINDOW;
	si.wShowWindow  = SW_HIDE;
	PROCESS_INFORMATION pi;
	if(!CreateProcess(TEXT(s.c_str()), NULL, NULL, NULL, FALSE,
                   0, NULL, dir.c_str(), &si, &pi)){
		rx.flag = 6;
		TerminateProcess(pi.hProcess, 0);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return rx;
	}
	int st, et;
	DWORD res, exitcode;
	st = clock();
	res = WaitForSingleObject(pi.hProcess, lx.rtime);
	et = clock();
	GetExitCodeProcess(pi.hProcess, &exitcode);
	if(exitcode != 0 && res != WAIT_TIMEOUT){
        rx.flag = 5;
		TerminateProcess(pi.hProcess, 0);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return rx;
	}
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(pi.hProcess, &pmc, sizeof(pmc));
	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
 	if(res == WAIT_TIMEOUT){
		rx.flag = 2;
		return rx;
	}
	rx.umemory = pmc.PeakWorkingSetSize / 1024;
	rx.utime   = et - st;
	if(rx.umemory > lx.rmemory){
        rx.flag = 3;
		return rx;
	}
	return rx;
}
