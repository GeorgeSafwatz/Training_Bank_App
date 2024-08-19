
#include <iostream>
#include <vector>
#include "Utils.h"
#include "Log.h"
int main()
{
    //Do while true
    //Choose option
    //Do something based on option
    bool keepRunning = true;
    vector<stClient> vClients = {};
    string fileName = "clientsFile.txt";
    utils::readFile(fileName, vClients);
    do
    {
        utils::showMainMenuOptions(vClients,keepRunning);
        cout << "Press any key to continue...." << endl;
        system("pause>0");
        system("cls");
    } while (keepRunning);
    utils::saveVectorToFile(fileName, vClients);
    cout << "Thanks for working with us!" << endl;
}