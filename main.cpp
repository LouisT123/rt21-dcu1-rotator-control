#include <iostream>
using namespace std;

//com needs to have:
//4800 baudrate
//no parity
//8 data bits
//1 stop bit
//ascii mode
// "4800,N,8,1,ASC". in old ass basic
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
  
}

void COM2()
{
  cout << "Opening COM2 at 4800 baud" << endl;
  
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