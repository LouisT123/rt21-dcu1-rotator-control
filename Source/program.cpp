// for serial port intialization

#include <iostream>
// open serial port (rs232)
#include <Windows.h>
using namespace std;

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
