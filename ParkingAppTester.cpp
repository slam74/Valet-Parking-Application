/* ------------------------------------------------------
Final Project Milestone 6
Module: ReadWritable
Filename: ParkingAppTester.cpp
Version 1.0
Author	Fardad Soleimanloo
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/4  Preliminary release
-----------------------------------------------------------*/
#include <fstream>
#include <iostream>
#include <ctype.h>
#include "Parking.h"
using namespace std;
using namespace sdds;
void runParking() {
   Parking P("ParkingData.csv", 11);
   P.run();
}
void ShowDatafile() {
   char ch;
   ifstream file("ParkingData.csv");
   cout << endl << "Content of ParkingData.csv after the program exits" << endl;
   cout << "-----------------------------------------------------------" << endl;
   while (file.get(ch)) {
      cout <<char(tolower(ch));
   }
   cout <<  "-----------------------------------------------------------" << endl;
   cout << "To restore the data back to the original values " << endl;
   cout << "Copy \"ParkingData.csv.bak\" over \"ParkingData.csv\"" << endl;
}
int main() {
   runParking();
   ShowDatafile();
   return 0;
}
