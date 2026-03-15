// ServerSFT.cpp — Encryption DLL
// Exports: GenerateKey, CaesarEncrypt, CaesarDecrypt, XOREncrypt, XORDecrypt

#include "pch.h"
#include <windows.h>
#include <cstring>

extern "C" __declspec(dllexport) int GenerateKey(const char* password)
{
    int key = 0;
    for (int i = 0; i < (int)strlen(password); i++)
    {
        key += (unsigned char)password[i];
    }
    key = (key % 255) + 1;  // range 1-255, never 0
    return key;
}

extern "C" __declspec(dllexport) void CaesarEncrypt(char* data, int length, int key)
{
    for (int i = 0; i < length; i++)
    {
        data[i] = (char)(((unsigned char)data[i] + key) % 256);
    }
}

extern "C" __declspec(dllexport) void CaesarDecrypt(char* data, int length, int key)
{
    for (int i = 0; i < length; i++)
    {
        data[i] = (char)(((unsigned char)data[i] - key + 256) % 256);
    }
}

extern "C" __declspec(dllexport) void XOREncrypt(char* data, int length, int key)
{
    char xorKey = (char)(key & 0xFF);
    for (int i = 0; i < length; i++)
    {
        data[i] = data[i] ^ xorKey;
    }
}

extern "C" __declspec(dllexport) void XORDecrypt(char* data, int length, int key)
{
    XOREncrypt(data, length, key);
}
