
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
    enClientOptions clientOption;
    vector<stClient> vClients = {};
    string fileName = "clientsFile.txt";
    utils::readFile(fileName, vClients);
    do
    {
        clientOption = utils::chooseOption();
        switch (clientOption)
        {
        case enClientOptions::showClients:
            loggers::printClients(vClients);
            break;
        case enClientOptions::addNewClient:
            utils::addClient(vClients);
            break;
        case enClientOptions::deleteClient:
            utils::deleteClient(vClients);
            break;
        case enClientOptions::updateClient:            
            utils::updateClient(vClients);
            break;
        case enClientOptions::findClient:
            loggers::logInfo(utils::findClientById(vClients));
            break;
        default:
            keepRunning = false;
            break;
        }
    } while (keepRunning);
    utils::saveVectorToFile(fileName, vClients);
    cout << "Thanks for working with us!" << endl;
}