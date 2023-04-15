#include <iostream>
using namespace std;
#include <Windows.h>
#include "RS232.h"

const int BUFSIZE = 140;
wchar_t COMPORT_Rx[] = L"COM7"; // COM port used for Rx (use L"COM6" for transmit program)
wchar_t COMPORT_Tx[] = L"COM6";// COM port used for Tx (use L"COM6" for transmit program)

wchar_t COMPORT1 = "COM1"
wchar_t COMPORT2 = "COM2"
//com needs to have:
//4800 baudrate
//no parity
//8 data bits
//1 stop bit
//ascii mode
// "4800,N,8,1,ASC". in old ass basic
HANDLE hSerialRx;
HANDLE hSerialTx;
int nComRate = 4800;
int nComBits = 8;
COMMTIMEOUTS = timeout;

int main()
{

  int COMPT = 0;
  cout << "Choose either COM1 or COM2 by typing 1 or 2 respectively" << endl;
  cin >> COMPT;

  //calls comport serial here
  if (COMPT < 1.5)
  {
    COM1();
  }
  else
  {
    COM2();
  }
  displayInfo();
}

void COM1()
{
  cout << "Opening COM1 at 4800 baud" << endl;
  /*initPort(&hSerialRx, COMPORT1, nComRate, nComBits, timeout); //rx port
  Sleep(500);
  */
  initPort(&hSerialTx, COMPORT1, nComRate, nComBits, timeout); //Tx port
  Sleep(500);
  //need to transmit based on appendix F in rt21 manual (pg 47)
  
}

void COM2()
{
  cout << "Opening COM2 at 4800 baud" << endl;
    cout << "Opening COM1 at 4800 baud" << endl;
  /*initPort(&hSerialRx, COMPORT2, nComRate, nComBits, timeout); //rx port
  Sleep(500);*/
  initPort(&hSerialTx, COMPORT2, nComRate, nComBits, timeout); //Tx port
  Sleep(500);
   //need to transmit based on appendix F in rt21 manual (pg 47)
}

void displayInfo()
{
  cout << "North = 0, East = 90, South = 180, West = 270" << endl;
  cout << "Enter 999 to exit program" << endl;
  cout << "Enter Destination Bearing (0 - 359)" << endl;

  //enter stuff
  int bearing = 0;

  if (bearing == 999 || bearing > 999)
  {
    //close
  }
  else if(bearing < 0)
  {
    
  }
  else if(bearing)
  {
    
  }
  else if(bearing)
  {
    
  }
    
  cout << "" << endl;
  cout << "" << endl;
  cout << "" << endl;
}

void error()
{
  
}