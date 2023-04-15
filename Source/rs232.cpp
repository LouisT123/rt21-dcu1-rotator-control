// for serial port intialization

#include <iostream>
// open serial port (rs232)
#include <Windows.h>
using namespace std;
#include "RS232.h"

//intialize port
void initPort(HANDLE* hSerial, wchar_t* COMPORT, int nComRate, int nComBits, COMMTIMEOUTS timeout){
    createPortFile(hSerial, COMPORT);
    purgePort(hSerial); 
    SetCOMParameters(hSerial, nComRate, nComBits, timeout);
    purgePort(hSerial); 
}

void purgePort(HANDLE* hSerial) {
    PurgeComm(*hSerial, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXCLEAR);
}

// output/input messages to/from ports
void outputToPort(HANDLE* hSerial, LPCVOID buf, DWORD szBuf) {
    int i = 0;
    DWORD NumberofBytesTransmitted;
    LPDWORD lpErrors=0;
    LPCOMSTAT lpStat=0;
    i = WriteFile(
        *hSerial,
        buf,
        szBuf,
        &NumberofBytesTransmitted,
        NULL
        );
        //time out error
        if (i == 0) {
            printf("\nWrite Error: 0x%x\n", GetLastError());
            ClearCommError(hSerial, lpErrors, lpStat);
        }
        else 
        {
            printf("\nSuccessful transmission, there were %ld bytes transmitted\n", NumberofBytesTransmitted);
        }
}

DWORD inputFromPort(HANDLE* hSerial, LPVOID buf, DWORD szBuf) {
	int i = 0;
	DWORD NumberofBytesRead;
	LPDWORD lpErrors = 0;
	LPCOMSTAT lpStat = 0;
     i = ReadFile(
        *hSerial,
        buf,
        szBuf,
        &NumberofBytesRead,
        NULL
        );
        //time out error
        if (i == 0) {
            printf("\nRead Error: 0x%x\n", GetLastError());
            ClearCommError(hSerial, lpErrors, lpStat);
        }
        else 
        {
            printf("\nSuccessful reception, there were %ld bytes read\n", NumberofBytesRead);
        }
        return(NumberofBytesRead);
}

void createPortFile(HANDLE *hSerial, wchar_t *COMPORT)
{
    *hSerial = CreateFile(COMPORT,
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         0,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         0);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            cout << "No port found" << endl;
        }
        cout << "Unkown error occured when connecting port" << endl;
    }
}


static int SetCOMParameters(HANDLE* hSerial, int nComRate, 
int ComBits, COMMTIMEOUTS timeout) {
    DCB dcbSerialParameters = {0};

    //clear DCB to reset
    memset(&dcbSerialParameters, 0 , sizeof(dcbSerialParameters));
    dcbSerialParameters.DCBlength=sizeof(dcbSerialParameters);

    if (!GetCommState(hSerial, &dcbSerialParameters)) {
        cout << "Error getting state" << endl;
        return (0);
    }

    //set parameters
    // "4800,N,8,1,ASC". in old ass basic
    dcbSerialParameters.BaudRate=nComRate; //should be 4800 for our purposes
    dcbSerialParameters.ByteSize=(BYTE)nComRate; //can be 8
    dcbSerialParameters.StopBits=ONESTOPBIT; //1 stop bit
    dcbSerialParameters.Parity=NOPARITY; //no parity

    if(!SetCommState(*hSerial, &dcbSerialParameters)){
        cout << "Error setting serial port state" << endl;
        return (0);
    }

    //set timeouts
    timeout.ReadIntervalTimeout = 500; 
    timeout.ReadTotalTimeoutMultiplier = 1;
    timeout.ReadTotalTimeoutConstant = 5000;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeout)) {
        cout << "Error occured" << endl;
        return (1);
    }
}
