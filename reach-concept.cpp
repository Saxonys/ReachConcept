#include <iostream>
#include <windows.h>
#include <vector>
#include <tchar.h>
HANDLE pHandle = NULL;
DWORD pID = NULL;

std::vector<DWORD> address45list;
std::vector<DWORD> reachlist;
std::vector<DWORD> reachlistdbl;
std::vector<DWORD> limitlist;
float reachset = 3;
bool reachon = true;
void scan() {

    while (1)
    {
        if (reachon)
        {
            HWND mc_hWnd = FindWindow(_T("LWJGL"), nullptr);
            GetWindowThreadProcessId(mc_hWnd, &pID);
            pHandle = OpenProcess(THREAD_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pID);

            constexpr unsigned min = 0x10000; //minimum
            constexpr unsigned max = 0x06FFFFFF; //maximum

            char buffer[min];
            for (unsigned i = 0; i < max; i += min) {
                if (ReadProcessMemory(pHandle, (LPVOID)i, buffer, sizeof(buffer), nullptr)) {
                    for (int j = 0; j <= min - sizeof(double); ++j) {
                        double nexus;
                        int address1 = i + j;
                        int address2 = i + j;
                        int address3 = i + j;
                        int address4 = i + j;
                        memcpy(&reachset, buffer + j, sizeof(double));
                        if (i + j >= 0x02A0000C)
                        {
                            if (reachset == 4.5)
                            {

                                for (int k = 0; k < 26; k++)
                                {
                                    Sleep(1);
                                    float checks;
                                    address1 = address1 + 0x4;
                                    ReadProcessMemory(pHandle, (void*)address1, &checks, sizeof(checks), 0);
                                    if (checks == 3.0)
                                    {
                                        //std::cout << std::hex << "3.0 float --> " << address1 << std::endl;
                                        //std::cout << std::hex << "4.5 double --> " << i + j << std::endl;
                                        reachlist.push_back(address1);
                                        limitlist.push_back(i + j);
                                    }
                                }
                                Sleep(10);
                                for (int k = 0; k < 16; k++)
                                {
                                    Sleep(1);
                                    float checks;
                                    address2 = address2 - 0x4;
                                    ReadProcessMemory(pHandle, (void*)address2, &checks, sizeof(checks), 0);
                                    if (checks == 3.0)
                                    {
                                        //std::cout << std::hex << "3.0 float --> " << address2 << std::endl;
                                        //std::cout << std::hex << "4.5 double --> " << i + j << std::endl;
                                        reachlist.push_back(address2);
                                        limitlist.push_back(i + j);
                                    }
                                }
                                Sleep(10);
                                for (int k = 0; k < 8; k++)
                                {
                                    Sleep(1);
                                    double checks;
                                    address3 = address3 + 0x8;
                                    ReadProcessMemory(pHandle, (void*)address3, &checks, sizeof(checks), 0);
                                    if (checks == 3.0)
                                    {
                                        //std::cout << std::hex << "3.0 double --> " << address3 << std::endl;
                                        //std::cout << std::hex << "4.5 double --> " << i + j << std::endl;
                                        reachlistdbl.push_back(address3);
                                        limitlist.push_back(i + j);
                                    }
                                }
                                Sleep(10);
                                for (int k = 0; k < 8; k++)
                                {
                                    Sleep(1);
                                    double checks;
                                    address4 = address4 - 0x8;
                                    ReadProcessMemory(pHandle, (void*)address4, &checks, sizeof(checks), 0);
                                    if (checks == 3.0)
                                    {
                                        //std::cout << std::hex << "3.0 double --> " << address4 << std::endl;
                                        //std::cout << std::hex << "4.5 double --> " << i + j << std::endl;
                                        reachlistdbl.push_back(address4);
                                        limitlist.push_back(i + j);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < reachlistdbl.size(); i++)
            {
                double value;
                Sleep(100);
                ReadProcessMemory(pHandle, (LPVOID)(reachlistdbl.at(i)), &value, sizeof(value), NULL);
                if (value <= 6.0)
                {
                    if (value >= 3.0)
                    {
                        if (value != reachset)
                        {
                            WriteProcessMemory(pHandle, (void*)(reachlistdbl.at(i)), &reachset, sizeof(double), 0);
                        }
                    }

                }
            }
            for (int i = 0; i < reachlist.size(); i++)
            {
                float value;
                Sleep(100);
                ReadProcessMemory(pHandle, (LPVOID)(reachlist.at(i)), &value, sizeof(value), NULL);
                if (value <= 6.0)
                {
                    if (value >= 3.0)
                    {
                        if (value != reachset)
                        {
                            WriteProcessMemory(pHandle, (LPVOID)(reachlist.at(i)), &reachset, sizeof(float), 0);
                        }
                    }

                }
            }
            double reachsetlimit = reachset + 1.5;
            for (int i = 0; i < limitlist.size(); i++)
            {
                double value;
                Sleep(100);
                ReadProcessMemory(pHandle, (LPVOID)(limitlist.at(i)), &value, sizeof(value), NULL);
                if (value <= 7.5)
                {
                    if (value >= 4.5)
                    {
                        if (value != reachsetlimit)
                        {
                            WriteProcessMemory(pHandle, (LPVOID)(limitlist.at(i)), &reachsetlimit, sizeof(double), 0);
                        }
                    }

                }
            }
            Sleep(5000);
        }
        else
        {
            Sleep(1000);
        }
    }
}

int main() {

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&scan, NULL, 0, 0);
    while (1)
    {
        //std::cout << "Set amount: ";
        //std::cin >> reachset;
        //Main code here...
        Sleep(1000);
    }
    return 0;
}