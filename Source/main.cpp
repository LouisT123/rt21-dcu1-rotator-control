#include <iostream>
using namespace std;
#include <Windows.h>
#include "RS232.h"

const int BUFSIZE = 140;
wchar_t COMPORT_Rx[] = L"COM7"; // COM port used for Rx (use L"COM6" for transmit program)
wchar_t COMPORT_Tx[] = L"COM6";// COM port used for Tx (use L"COM6" for transmit program)

wchar_t COMPORT1[] = L"COM1";
wchar_t COMPORT2[] = L"COM2";
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
  if (COMPT == 1)
  {
    COM1();
  }
  else
  {
    COM2();
  }
  
  for (;;)
  {
    displayInfo();
  }
}

void COM1()
{
  cout << "Opening COM1 at 4800 baud" << endl;
  initPort(&hSerialRx, COMPORT1, nComRate, nComBits, timeout); //rx port
  Sleep(500);

  initPort(&hSerialTx, COMPORT1, nComRate, nComBits, timeout); //Tx port
  Sleep(500);

  cout << "Checking heading for the rotator" << endl;
  //ask for user input for command later, for now check heading
  //need to transmit based on appendix F in rt21 manual (pg 47)
  char commandOut[] = "AI1";
  //cin >> COMPT;

  //send string to port
  outputToPort(&hSerialTx, messageOut, strlen(messageOut)+1);
  Sleep(500);
 
  // Reciever side 
  char messageIn[BUFSIZE];
  DWORD bytesRead;
  //grab string from port
  bytesRead = inputFromPort(&hSerialRx, messageIn, BUFSIZE);

  //length of recieved message
  messageIn[bytesRead] = '\0';
  // Display message from port
  printf("\nMessage Received: %s\n\n", msgIn);				
  

  // Tear down both sides of the comm link
  /*
	purgePort(&hComRx);											// Purge the Rx port
	purgePort(&hComTx);											// Purge the Tx port
	CloseHandle(hComRx);										// Close the handle to Rx port 
	CloseHandle(hComTx);										// Close the handle to Tx port 
	*/
	system("pause");
}

void COM2()
{
  cout << "Opening COM2 at 4800 baud" << endl;

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
  cin >> bearing;

  if (bearing == 999 || bearing > 999)
  {
    exit(0);
  }
  else if(bearing < 0 && bearing > 360.5)
  {
    error();
  }
  else if(bearing > 359.5 && bearing < 360.5)
  {
    bearing = 0;
  }
    
  cout << "Destination Bearing: " << end;
  cout << bearing << end;
  cout << " degree" << endl;
  
  bearing = bearing + 1000;
  //print #1, USING "AP####;"bearing


  cout << "\n Press enter to execute rotation " << endl;
  getchar();
  rotating();
}

void rotating()
{
  cout << "\n Rotating " << endl;

  //add the com port showing that the rotator is rotating
  
  cout << "\n Wait for brake to engage before entering new destination" << endl;

  //make sure brake is engage
}

void error()
{
  cout << "Enter Destination Bearing (0 - 359)" << endl;
}