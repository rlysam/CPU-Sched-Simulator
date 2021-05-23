#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "myheader.h"

using namespace std;

RR::RR() {}
RR::RR(int n, std::vector<int> Arrival, std::vector<int> Burst, int TIME_Q)
    : FCFS(n, Arrival, Burst)
{
    TQ = TIME_Q;
}

void RR::fillGanttChart()
{
    while (stillContinue() != 0) //* Zero means tapos na lahat ngprocess
    {
        addToReadyQueue();
        removeFromReadQueue();
        if (RQ.empty() != true)
        {
            int x = 0;
            int timeQ = TQ; //TQ gagamitin kapag mas mataas yung bt, kapag BT of x<TQ, yun yung gagawing counter

            int remBT = remaining_BToFx(x);

            if (remBT < TQ)
                timeQ = remBT;

            for (int i = 0; i < timeQ; i++)
            {
                vGanntChart.push_back(PID.at(getOriginalIndex(x)));
                clock++;
            }
            
        }
        else
        {
            idle = true;
            vGanntChart.push_back("x"); //IF nothing is in RQ, put x to indicate that it's idle...
            clock++;
        }
    }
}

//hinahanap yung count PID[x] sa vGC
//similiar to removeFromReadQueue()
// check if BT[x] == count
// return BT[x] - count
int RR::remaining_BToFx(int x)
{
    int count = 0;
    int y = getOriginalIndex(x);
    for (int i = 0; i < vGanntChart.size(); i++)
    {
        if ((PID[y]).compare(vGanntChart.at(i)) == 0)
            count++;
    }
    return BT[y] - count;
}

//lagay sa ready queue kapag na meet and requirements [Nag ARRIVE na]
//lalagay nya regardless of which are already completed...
void RR::addToReadyQueue()
{
    if (first == true) //first time papasok wala pang laman yung vGanttCahrt
    {
        first = false;
        for (int i = 0; i < PID.size(); i++)
        {
            if ((FCFS::alreadyExists(i) == 0) && (AT.at(i) <= clock))
            { //wala pa sa RQ
                RQ.push_back(PID.at(i));
            }
        }
        idle=false;
    }
    else
    {
        //append head to RQ...
        //P1
        for (int i = 0; i < PID.size(); i++)
        {
            if ((FCFS::alreadyExists(i) == 0) && (AT.at(i) <= clock))
            { //wala pa sa RQ
                RQ.push_back(PID.at(i));
            }
        }
        if (idle == false)
        {//x P1 P2 P3 P4 P5
            RQ.push_back(vGanntChart.at(vGanntChart.size() - 1)); //head
            // delete P1 sa unahan
            auto head = RQ.begin();
            RQ.erase(head);
        }else
        {
            idle = false;
        }
        
    }
}
