//ito e-edit ni voss ian
#include <iostream>
#include <conio.h>
#include <string>
#include <map>
#include <vector>
#include "myheader.h"
#include <stdlib.h>
//! PANSAMANTALA LANG MUNA
#include <windows.h>
#include <iomanip>

using namespace std;

//FCFS, SJF, SRTF
//* accepts gantt chart, pid, technique ,AT,BT,ST,ET,RT,TT, and WT
Display::Display(vector<string> GanttChart, vector<string> PID, string technique, vector<int> AT, vector<int> BT, vector<int> PR, int TQ,
                 vector<int> ST, vector<int> ET, vector<int> RT, vector<int> TT, vector<int> WT)
{
    this->GanttChart = GanttChart;
    this->PID = PID;
    this->technique = technique;
    this->AT = AT;
    this->BT = BT;
    this->PR = PR;
    this->TQ = TQ;
    this->ST = ST;
    this->ET = ET;
    this->RT = RT;
    this->TT = TT;
    this->WT = WT;
}

//for comparison only
void Display::displayAverages(string name)
{
    // ! AVERAGE
    cout << fixed;
    cout << setprecision(2);
    cout << "Average: ";
    cout << "\t" << rtSum / PID.size();
    cout << "\t" << ttSum / PID.size();
    cout << "\t" << wtSum / PID.size();
    cout << "\t"<< "---"<<name ;
}


void Display::displayTable()
{
    // ! TABLE
    cout << "\t---" << technique << "---" << endl
         << endl;

    if (technique == "Round Robin")
    {
        cout << "Time Quantum: " << TQ << "\n\n";
        cout << "PID\tAT\tBT\tST\tET\tRT\tTT\tWT\n\n";
    }
    else if (technique == "Non-Preemtive Priority" || technique == "Preemtive Priority")
        cout << "PID\tAT\tBT\tPR\tST\tET\tRT\tTT\tWT\n\n";
    else
        cout << "PID\tAT\tBT\tST\tET\tRT\tTT\tWT\n\n";

    if (technique == "Non-Preemtive Priority" || technique == "Preemtive Priority")
    {
        for (int i = 0; i < PID.size(); i++)
        {
            cout << PID[i] << "\t" << AT[i] << "\t" << BT[i] << "\t"
                 << PR[i] << "\t"
                 << ST[i] << "\t" << ET[i] << "\t"
                 << RT[i] << "\t"
                 << TT[i] << "\t"
                 << WT[i] << "\t" << endl;
            rtSum += RT[i];
            ttSum += TT[i];
            wtSum += WT[i];
        }
    }
    else
    {
        for (int i = 0; i < PID.size(); i++)
        {
            cout << PID[i] << "\t" << AT[i] << "\t" << BT[i] << "\t"
                 << ST[i] << "\t" << ET[i] << "\t"
                 << RT[i] << "\t"
                 << TT[i] << "\t"
                 << WT[i] << "\t" << endl;
            rtSum += RT[i];
            ttSum += TT[i];
            wtSum += WT[i];
        }
    }

    // ! AVERAGE
    cout << fixed;
    cout << setprecision(1);
    cout << endl;
    cout << "\t\t\t"
         << "Average: ";
    cout << "\t" << rtSum / PID.size();
    cout << "\t" << ttSum / PID.size();
    cout << "\t" << wtSum / PID.size() << endl;
}

void Display::displayGC()
{
    //! IAN's
    //! BUGGED --- ayaw mag print ng BARS
    //gantt chart yung dati ::: palitan 'to ng BAR BAR
    int baseColor = 1;
    signed char c = 219;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // ! ---- SAM GANTT CHART
    map<string, int> pidColor;
    int gray = 8;
    int cCounter = 0;                                          //keeps track if multiple of 12
    int color[12] = {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14}; //COLORS

    //* Generate map   Key : Value --- PID[i] : color[cCounter]
    for (int i = 0; i < PID.size(); i++)
    {
        if (cCounter % 12 == 0)
            cCounter = 0;            //reset yung cCounter every 12
        pidColor[PID[i]] = cCounter; //! assign na!
        cCounter++;
    }

    cout << endl
         << endl;
    //Lagyan ng indication kung anong kulay
    SetConsoleTextAttribute(console, gray);
    cout << "IDLE  ";
    for (int i = 0; i < PID.size(); i++)
    {
        SetConsoleTextAttribute(console, color[pidColor[PID[i]]]);
        cout << PID[i] << "  ";
    }

    cout << endl
         << endl;
    //* GENERATE GC
    cout << " "; //Para may place yung 0
    for (int i = 0; i < GanttChart.size(); i++)
    {
        if (GanttChart[i] == "x")
        {
            SetConsoleTextAttribute(console, gray);
            cout << c << c << c;
        }
        else
        {
            SetConsoleTextAttribute(console, color[pidColor[GanttChart[i]]]);
            cout << c << c << c;
        }
    }

    SetConsoleTextAttribute(console, 15);
    cout << endl;

    cout << "0";
    //* NUMBER    ----- Numbers below...
    cout << " "; //Para may place yung 0
    string num;
    int digits;
    for (int i = 0; i < GanttChart.size(); i++)
    {
        num = to_string(i);
        digits = num.size();
        if (GanttChart[i] != GanttChart[i + 1])
        {

            if (digits == 1)
            {
                cout << "  " << i + 1;
            }
            if (digits == 2)
            {
                cout << "  " << i + 1;
            }
            if (digits == 3)
            {
                cout << "" << i + 1;
            }
        }
        else
        {

            if (digits == 1)
            {
                cout << "   ";
            }
            if (digits == 2)
            {
                cout << "  ";
            }
            if (digits == 3)
            {
                cout << "";
            }
        }
    }

    // return to initial valeus
    SetConsoleTextAttribute(console, 15);
    cout << endl;
}
