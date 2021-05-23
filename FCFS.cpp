#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "myheader.h"

using namespace std;

//!PASSED
//initialize values from main
FCFS::FCFS(int n, std::vector<int> Arrival, std::vector<int> Burst)
{
    //from Class MainMenu
    np = n;
    AT = Arrival;
    BT = Burst;
}
FCFS::FCFS() {}
//generate lang [P1..Pn]
void FCFS::generatePID()
{
    for (int i = 0; i < np; i++)
    {
        PID.push_back("P" + to_string(i + 1));
    }
}

//!PASSED
//Nasa Ready Queue ba? --returns 1 if currently in RQ
int FCFS::alreadyExists(int n)
{
    vector<string>::iterator it;
    it = std::find(RQ.begin(), RQ.end(), PID[n]);

    if (it != RQ.end())
    {
        return 1; //nasa RQ na siya...
    }
    else
        return 0; //hindi nakita yung element OR anythin else, maybe walang laman
}

//lagay sa ready queue kapag na meet and requirements [Nag ARRIVE na]
//lalagay nya regardless of which are already completed...
void FCFS::addToReadyQueue()
{
    RQ.clear();
    for (int i = 0; i < PID.size(); i++)
    {
        if ((FCFS::alreadyExists(i) == 0) && (AT.at(i) <= clock))
        { //wala pa sa RQ
            RQ.push_back(PID.at(i));
        }
    }
}

void FCFS::removeFromReadQueue()
{
    // requirements to be removed from RQ: yung value of BT is == count ng entries sa vGC
    vector<int> s; // Counter -- Entry of P1's in vGC == 23...
    int tmp;
    if (RQ.empty() != true)
    {
        for (int i = 0; i < PID.size(); i++)
        {
            tmp = 0;
            for (int j = 0; j < vGanntChart.size(); j++)
            {
                if (PID.at(i).compare(vGanntChart.at(j)) == 0)
                    tmp++;
            }
            s.push_back(tmp); //
        }
        // ! Kapag parehas na yung s"Total entries sa vGC" sa
        for (int i = 0; i < BT.size(); i++)
        {
            if (BT.at(i) == s.at(i))
            {
                //REMOVE FROM RQ
                vector<string>::iterator it;
                it = std::find(RQ.begin(), RQ.end(), PID.at(i));
                RQ.erase(it);
            }
        }
    }
}

//!PASSED
/*idx of PID bofore RQ(ex. P1 == idx 0) "0 will be returned"
qualifications; 1. In RQ, 2. Lowest arrival arrival time.
para sa SWAP*/
int FCFS::getOriginalIndex(int n)
{
    vector<string>::iterator it;
    it = std::find(PID.begin(), PID.end(), RQ[n]);
    return it - PID.begin();
}

//!PASSED
//condition to stop clock
int FCFS::stillContinue()
{
    //calculate total BT
    int total_bt = 0;
    for (int i = 0; i < BT.size(); i++)
    {
        total_bt += BT.at(i);
    }
    // cout<<"BT[0]: "<<BT[0]<<"\tAT[0]: "<<AT[0] <<"\tTotal BT " <<total_bt;
    int t_entries = 0;
    for (int i = 0; i < vGanntChart.size(); i++)
    {
        if (vGanntChart.at(i) != "x")
            t_entries++;
    }
    //if total BT == total entries in ganttchart
    if (t_entries == total_bt)
        return 0; //!0/false == magkamuka na, so STOP
    else
        return 1;
}

//  FCFS

//! PASSED
//main FCFS Function...
//index of PROCESS with the LOWEST Arrival Time AND is in Ready Queue
//alreadyExist == true && lowest int == 0
int FCFS::firstToCome()
{
    // a = original idx of the process in PID
    int a = getOriginalIndex(0); //first elem ng RQ

    for (int i = 0; i < RQ.size(); i++)
    {
        //AT[a] == unang elem ng RQ, AT[i] next element
        if (AT[a] > AT[getOriginalIndex(i)])
        { //Existing in RQ
            a = getOriginalIndex(i);
        }
    }
    return a;
}

//! PASSED
// Fill Gantt Chart lang... implement idle time solution here...
void FCFS::fillGanttChart()
{
    while (stillContinue() != 0) //starts at time 0
    {
        addToReadyQueue();
        removeFromReadQueue();
        //! INSERT
        if (RQ.empty() != true)
        {
            vGanntChart.push_back(PID.at(firstToCome()));
        }
        else
        {
            vGanntChart.push_back("x"); //IF nothing is in RQ, put x to indicate that it's idle...
        }
        clock++; //keep tract of time every tick
    }
}

//[FCFS] ST & ET
void FCFS::generateSTET()
{

    int n;

    for (int j = 0; j < PID.size(); j++)
    {
        n = 0;
        // catch first instance of ST from idx 0
        while (PID[j] != vGanntChart[n])
            n++;
        ST.push_back(n);

        n = vGanntChart.size() - 1; //set n as last index of vGanttChart

        //catch ET from the last idx
        while (PID[j] != vGanntChart[n])
            n--;
        ET.push_back(n + 1);
    }
}

//[FCFS] ST, ET, TT, WT, RT //expression para makuha
void FCFS::generateFive()
{
    generateSTET();
    for (int i = 0; i < PID.size(); i++)
    {
        RT.push_back(ST[i] - AT[i]);
        TT.push_back(ET[i] - AT[i]);
        WT.push_back(TT[i] - BT[i]);
    }
}

void FCFS::generateValues()
{
    generatePID();    //PID MUNA //! IMPORTANT
    fillGanttChart(); //generate Gantt Chart
    generateFive();   //Generate yung table
}

// * GETTER ng PID, ST, ET, RT, TT, WT
// * Now, every time you want to get PID, ST, ET, RT, TT, or WT... call generateValues() first.

// ? USE POINTERS to return multiple values from one Function
// ? example: https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/

vector<string> FCFS::getGC()
{
    generateValues();
    return vGanntChart;
}

vector<string> FCFS::getPID()
{
    generateValues();
    return PID;
}

vector<int> FCFS::getST()
{
    generateValues();
    return ST;
}

vector<int> FCFS::getET()
{
    generateValues();
    return ET;
}

vector<int> FCFS::getRT()
{
    generateValues();
    return RT;
}

vector<int> FCFS::getTT()
{
    generateValues();
    return TT;
}

vector<int> FCFS::getWT()
{
    generateValues();
    return WT;
}