#include "Windows.h"
#include <iostream>
#pragma comment(lib, "advapi32.lib")

int main(int argc, char *argv[])
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    wchar_t cmdline[] = L"./PasswordManager.exe";

    if (CreateProcess(
                cmdline, NULL,
                NULL, NULL,
                TRUE, NULL,
                NULL, NULL,
                &si, &pi
                )) {
        std::cout << "Created process with PID " << pi.dwProcessId << std::endl;
    } else {
        std::cout << "CreateProcessW FAILED" << std::endl;
    }

    bool isAttached = DebugActiveProcess(pi.dwProcessId);
    if (isAttached) {
        std::cout << "DebugActiveProcess SUCCESS!" << std::endl;
    }else{
        DWORD lastError = GetLastError();
        std::cout << "DebugActiveProcess FAILED, lastError = " << lastError << std::endl;
    }


    for(;;) {
        DEBUG_EVENT debugEvent;
        WaitForDebugEvent(&debugEvent, INFINITE);
        ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_EXCEPTION_NOT_HANDLED);

//        std::cout << result1 << result2 << std::endl;
    }

    return 0;
}
