#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "myheader.h"

using namespace std;

MainMenu::MainMenu() { }

void MainMenu::updateScreen()
{
    cout << "Welcome to CPU Scheduling technique simulation.\n\n";
    cout << "Selected Technique: " << selected_technique << endl;
    cout << "Number of Process(minimum of 3 processes): " << numProcess << endl;
    cout << "Arrival time: "; getEntries(AT);
    cout << endl; cout << "Burst time:   ";
    getEntries(BT); cout << endl;
    cout << "Priority:     "; getEntries(Priority);
    cout << endl; cout << "Time Quantum: " << TQ << endl;

    show_option();
}

void MainMenu::getEntries(vector<int> n)
{
    for (int i = 0; i < numProcess; i++)
    {
        cout << n.at(i) << " ";
    }
}

void MainMenu::show_option()
{
    cout << "\n\tMenu:" << endl;
    cout << "[1] change technique" << endl;
    cout << "[2] change number of processes" << endl;
    cout << "[3] set arrival time" << endl;
    cout << "[4] set burst time" << endl;
    cout << "[5] set priority" << endl;
    cout << "[6] set Time Quantum" << endl;
    cout << "[0] generate Table and Gantt Chart" << endl
         << endl;
    cout << "[r] reset all values" << endl;
    cout << "[x] exit\n"
         << endl;
}

void MainMenu::reset(int n)
{
    numProcess = n, TQ = 1;
    // selected_technique = "First Come First Serve";//!sumakit ulo ko dito, kaya pala laging FCFS
    AT.clear();
    BT.clear();
    Priority.clear();

    for (int i = 0; i < n; i++)
    {
        AT.push_back(0);
        BT.push_back(1);//BT always atleast 1
        Priority.push_back(0);
    }
}
void MainMenu::printLabel(int i)
{
    cout << "\nP" << i + 1 << ": ";
}
//change values functions
void MainMenu::set_technique()
{
    int n;
    cout << "\n";
    //print all options
    for (int i = 0; i < allTechniques.size(); i++)
    {
        cout << i + 1 << ".)" << allTechniques.at(i) << endl;
    }
    cout << "\nOption(Press corresponding number): ";
    do
    {
        n = (int)((char)getch() - '0'); //
    } while (n < 1 || n > allTechniques.size());
    selected_technique = allTechniques.at(n - 1);
}
void MainMenu::set_AT()
{
    int a;
    AT.clear();
    cout << "\n\nARRIVAL TIME:\nEnter number then hit enter each time:";
    for (int i = 0; i < numProcess; i++)
    {
        printLabel(i);
        cin >> a;
        AT.push_back(a);
    }
}
void MainMenu::set_BT()
{
    int a;
    BT.clear();
    cout << "\n\nBURST TIME:\nEnter number then hit enter each time:"
    <<"\nEnter a number greater than zero...\n";
    for (int i = 0; i < numProcess; i++)
    {
        printLabel(i);
        cin >> a;
        BT.push_back(a);
    }
}
void MainMenu::set_Prio()
{
    int a;
    Priority.clear();
    cout << "\n\nPRIORITY:\nEnter number then hit enter each time:";
    for (int i = 0; i < numProcess; i++)
    {
        printLabel(i);
        cin >> a;
        Priority.push_back(a);
    }
}
void MainMenu::set_TQ()
{
    cout << "\n\n SET TIME QUANTUM: "
    <<"\nEnter a number greater than zero...\n";
    cin >> TQ;
}
//changes numProcess in class MainMenu
void MainMenu::set_num_p()
{
    do
    {
        cout << "Enter number of Process(3+)\n";
        cin >> numProcess;
    } while (numProcess < 3);
    reset(numProcess);
}

//titignan lang kung anong technique pinili
int MainMenu::finalize()
{
    int may_zero = 0; //false
    for (int i = 0; i < BT.size(); i++)
    {
        if (BT[i] == 0)
        {
            may_zero = 1;
        }
    }
    if (may_zero == 1)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < allTechniques.size(); i++)
        {
            if (allTechniques.at(i).compare(selected_technique) == 0)
            {
                return i + 1;
            }
        }
    }
}

// TODO check if the CIN is a NATURAL NUMBER FUNCTION()
// TODO Priority BT should not be zero FUNCTION()
// * AT == Whole number
// * priority, TQ & BT  == Natural number