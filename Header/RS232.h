#pragma once

// Prototype the functions to be used
void initPort(HANDLE* hSerial, wchar_t* COMPORT, int nComRate, int nComBits, COMMTIMEOUTS timeout);
void purgePort(HANDLE* hSerial);
void outputToPort(HANDLE* hSerial, LPCVOID buf, DWORD szBuf);
DWORD inputFromPort(HANDLE* hSerial, LPVOID buf, DWORD szBuf);

// Sub functions
void createPortFile(HANDLE* hSerial, wchar_t* COMPORT);
static int SetComParms(HANDLE* hSerial, int nComRate, int nComBits, COMMTIMEOUTS timeout);