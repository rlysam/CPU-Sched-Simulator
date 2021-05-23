//inherited from SJF
// TODO: Bali sa SRTF... ang gagawin lang ay...
// 1. make a copy of BT that you will be modifying every tick //* sa loob ng fillGanttChart() mag de-decrement
// 2. override add_to_RQ() -> kapag 0 na ang BT, don't add to RQ //! should have been my initial design

#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "myheader.h"

using namespace std;

//*working --- Dinadala niya sa base class ng base class...
SRTF::SRTF() {}
SRTF::SRTF(int n, vector<int> Arrival, vector<int> Burst) : SJF(n, Arrival, Burst) { }

// ! BUG --- Yung first test_case sa SRTF yung may problema... saka yung nasa Jenny Lecture
// ! BUG --- find difference non sa tatlo
void SRTF::fillGanttChart()
{
   copyBT = BT; //saves original BT
    while (stillContinue() != 0) //* Zero means tapos na lahat ngprocess
    {
        addToReadyQueue();
        // removeFromReadQueue();
        //* Ginamit si BT dito... sa removeFromRQ()
        //? TRY commenting removeFromRQ...
        //? OR try replacing BT in removeFromRQ with copyBT...

        if (RQ.empty() != true)
        {
            int x = shortest();
            vGanntChart.push_back(PID.at(x));
            BT[x]--;
            clock++;
        }

        else
        {
            vGanntChart.push_back("x"); //IF nothing is in RQ, put x to indicate that it's idle...
            clock++;
        }
    }
    BT=copyBT;//restores original BT
}

//* for SRTF... replace BT with copyBT
//condition to stop clock --- 
int SRTF::stillContinue()
{
    //calculate total BT
    int total_bt = 0;
    for (int i = 0; i < copyBT.size(); i++)
    {
        total_bt += copyBT.at(i);
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

//* Dapat ay hindi 0 yung remaining BT
//lagay sa ready queue kapag na meet and requirements [Nag ARRIVE na]
//lalagay nya regardless of which are already completed...
void SRTF::addToReadyQueue()
{
    RQ.clear();
    for (int i = 0; i < PID.size(); i++)
    {
        if ((FCFS::alreadyExists(i) == 0) && ( remaining_BToFx(i) !=0 ) && (AT.at(i) <= clock)) //* NEW: &&
        { //wala pa sa RQ
            RQ.push_back(PID.at(i));
        }
    }
}

//hinahanap yung count PID[x] sa vGC
//similiar to removeFromReadQueue()
// check if BT[x] == count
// return BT[x] - count
int SRTF::remaining_BToFx(int x)
{
    int count = 0;
    // int y = getOriginalIndex(x);
    for (int i = 0; i < vGanntChart.size(); i++)
    {
        if ((PID[x]).compare(vGanntChart.at(i)) == 0)
            count++;
    }
    return copyBT[x] - count;
}
