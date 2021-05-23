//ito e-edit ni voss ian
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "myheader.h"
#include <stdlib.h>

using namespace std;

Display::Display() {}

//FCFS, SJF, SRTF
//* accepts gantt chart, pid, technique ,AT,BT,ST,ET,RT,TT, and WT
Display::Display(std::vector<std::string> GanttChart, std::vector<std::string> PID, std::string technique, std::vector<int> AT, std::vector<int> BT, std::vector<int> ST, std::vector<int> ET, std::vector<int> RT, std::vector<int> TT, std::vector<int> WT)
{
    //ito yung table...
    cout << "PID\tAT\tBT\tST\tET\tRT\tTT\tWT\n\n";
    for (int i = 0; i < PID.size(); i++)
    {
        cout << PID[i] << "\t" << AT[i] << "\t" << BT[i] << "\t"
             << ST[i] << "\t" << ET[i] << "\t"
             << RT[i] << "\t"
             << TT[i] << "\t"
             << WT[i] << "\t" << endl;
    }

    //gantt chart yung dati ::: palitan 'to ng BAR BAR
    cout << "---GANTT CHART---\n\n|";
    for (int i = 0; i < GanttChart.size(); i++)
    {
        cout << GanttChart[i] << " | ";
    }
}

//NPP, PP
//* accepts pid, technique,AT,BT,priority,ST,ET,RT,TT, and WT
Display::Display(std::vector<std::string> GanttChart, std::vector<std::string> PID, std::string technique, std::vector<int> Arrival, std::vector<int> Burst, std::vector<int> Priority, std::vector<int> ST, std::vector<int> ET, std::vector<int> RT, std::vector<int> TT, std::vector<int> WT)
{
    //lagyan ng Priority sa output...
    cout << "Process\tAT\tBT\tPR\tST\tET\tRT\tTT\tWT\n\n";







    //gantt chart yung dati ::: palitan 'to ng BAR BAR
    cout << "---GANTT CHART---\n\n|";
    for (int i = 0; i < GanttChart.size(); i++)
    {
        cout << GanttChart[i] << " | ";
    }

}


//RR
//* accepts pid, technique,AT,BT,TQ,ST,ET,RT,TT, and WT
Display::Display(std::vector<std::string> GanttChart, std::vector<std::string> PID, std::string technique, std::vector<int> Arrival, std::vector<int> Burst, int TQ, std::vector<int> ST, std::vector<int> ET, std::vector<int> RT, std::vector<int> TT, std::vector<int> WT)
{
    cout << "Time Quantum: " << TQ << "\n";
    cout << "Process\tAT\tBT\tPR\tST\tET\tRT\tTT\tWT\n\n";




    //gantt chart yung dati ::: palitan 'to ng BAR BAR
    cout << "---GANTT CHART---\n\n|";
    for (int i = 0; i < GanttChart.size(); i++)
    {
        cout << GanttChart[i] << " | ";
    }

}