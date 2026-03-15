// ClientEncryption.cpp
// Asks user ONLY for:
//   1. Name of the file to encrypt  (source data)
//   2. Password  (to generate the encryption key)
// The output is always saved as data.enc in the background.

#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

typedef int  (*KEYPTR)(const char*);
typedef void (*ENCPTR)(char*, int, int);

int main()
{
    // -----------------------------------------------------------------------
    // 1. Load the DLL
    // -----------------------------------------------------------------------
    HINSTANCE hdll = LoadLibrary(L"ServerSFT.dll");
    if (hdll == NULL)
    {
        cerr << "[ERROR] Unable to load ServerSFT.dll.\n";
        return -1;
    }

    // -----------------------------------------------------------------------
    // 2. Resolve exported functions
    // -----------------------------------------------------------------------
    KEYPTR GenerateKey = (KEYPTR)GetProcAddress(hdll, "GenerateKey");
    ENCPTR Encrypt = (ENCPTR)GetProcAddress(hdll, "CaesarEncrypt");

    if (GenerateKey == NULL || Encrypt == NULL)
    {
        cerr << "[ERROR] Required functions not found in DLL.\n";
        FreeLibrary(hdll);
        return -1;
    }

    // -----------------------------------------------------------------------
    // 3. Ask ONLY input filename and password — nothing else
    // -----------------------------------------------------------------------
    string inputFile, password;

    cout << "Enter file to encrypt : ";
    cin >> inputFile;
    cout << "Enter password        : ";
    cin >> password;

    // -----------------------------------------------------------------------
    // 4. Generate encryption key from password
    // -----------------------------------------------------------------------
    int key = GenerateKey(password.c_str());

    // -----------------------------------------------------------------------
    // 5. Open the source file
    // -----------------------------------------------------------------------
    HANDLE hFile = CreateFileA(
        inputFile.c_str(),
        GENERIC_READ,
        0, NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        cerr << "[ERROR] Cannot open file: " << inputFile << "\n";
        FreeLibrary(hdll);
        return -1;
    }

    // -----------------------------------------------------------------------
    // 6. Read file into buffer
    // -----------------------------------------------------------------------
    DWORD size = GetFileSize(hFile, NULL);
    if (size == 0 || size == INVALID_FILE_SIZE)
    {
        cerr << "[ERROR] File is empty or unreadable.\n";
        CloseHandle(hFile);
        FreeLibrary(hdll);
        return -1;
    }

    char* buffer = new char[size];
    DWORD bytesRead = 0;
    if (!ReadFile(hFile, buffer, size, &bytesRead, NULL) || bytesRead != size)
    {
        cerr << "[ERROR] Failed to read file completely.\n";
        delete[] buffer;
        CloseHandle(hFile);
        FreeLibrary(hdll);
        return -1;
    }
    CloseHandle(hFile);

    // -----------------------------------------------------------------------
    // 7. Encrypt buffer using key derived from password
    // -----------------------------------------------------------------------
    Encrypt(buffer, (int)size, key);

    // -----------------------------------------------------------------------
    // 8. Save encrypted output as data.enc — fixed in background, user never sees this
    // -----------------------------------------------------------------------
    HANDLE hOut = CreateFileA(
        "data.enc",         // always saves as data.enc to match the decryption client
        GENERIC_WRITE,
        0, NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hOut == INVALID_HANDLE_VALUE)
    {
        cerr << "[ERROR] Unable to create encrypted output file.\n";
        delete[] buffer;
        FreeLibrary(hdll);
        return -1;
    }

    DWORD bytesWritten = 0;
    WriteFile(hOut, buffer, size, &bytesWritten, NULL);
    CloseHandle(hOut);
    delete[] buffer;

    // -----------------------------------------------------------------------
    // 9. Done
    // -----------------------------------------------------------------------
    cout << "\n[SUCCESS] File encrypted successfully.\n";
    cout << "          Size : " << bytesWritten << " bytes\n";

    FreeLibrary(hdll);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
