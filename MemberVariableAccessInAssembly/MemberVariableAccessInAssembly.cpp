#include <iostream>
#include <Windows.h>

using namespace std;

struct SA
{
    long long ll0;
    long long ll1;
};

struct SB
{
    SA stA0;
    SA stA1;
};

SB* g_pB = nullptr;

unsigned long __stdcall Thread(void* _pParameter)
{
    g_pB[1].stA0.ll0 = static_cast<long long>(rand());
    g_pB[1].stA0.ll1 = static_cast<long long>(rand());
    g_pB[1].stA1.ll0 = static_cast<long long>(rand());
    g_pB[1].stA1.ll1 = static_cast<long long>(rand());

    long long ll0 = g_pB[1].stA0.ll0;
    long long ll1 = g_pB[1].stA0.ll1;
    long long ll2 = g_pB[1].stA1.ll0;
    long long ll3 = g_pB[1].stA1.ll1;

    wcout << L"[User Thread]" << endl;
    wcout << L"ll0 : \t" << ll0 << endl;
    wcout << L"ll1 : \t" << ll1 << endl;
    wcout << L"ll2 : \t" << ll2 << endl;
    wcout << L"ll3 : \t" << ll3 << endl << endl;

    return 1UL;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    g_pB = new SB[3]{};

    // Main Thread

    g_pB[0].stA0.ll0 = static_cast<long long>(rand());
    g_pB[0].stA0.ll1 = static_cast<long long>(rand());
    g_pB[0].stA1.ll0 = static_cast<long long>(rand());
    g_pB[0].stA1.ll1 = static_cast<long long>(rand());

    long long ll0 = g_pB[0].stA0.ll0;
    long long ll1 = g_pB[0].stA0.ll1;
    long long ll2 = g_pB[0].stA1.ll0;
    long long ll3 = g_pB[0].stA1.ll1;

    wcout << L"[Main Thread]" << endl;
    wcout << L"ll0 : \t" << ll0 << endl;
    wcout << L"ll1 : \t" << ll1 << endl;
    wcout << L"ll2 : \t" << ll2 << endl;
    wcout << L"ll3 : \t" << ll3 << endl << endl;

    // User Thread

    void* pThread = CreateThread(nullptr, 0ULL, &Thread, nullptr, 0UL, nullptr);
    if (pThread == nullptr)
    {
        return 0;
    }

    unsigned long ulExitCode = 0UL;
    while (true)
    {
        GetExitCodeThread(pThread, &ulExitCode);
        if (ulExitCode == 1UL)
        {
            break;
        }
    }

    delete[] g_pB;
    g_pB = nullptr;

    return 0;
}