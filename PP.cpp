//inherited from NPP

#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "myheader.h"

using namespace std;

PP::PP() {}
// first 3 args are for base class, the last one is for NPP which is parent class nito...
PP::PP(int n, vector<int> Arrival, vector<int> Burst, vector<int> Priotity)
    : NPP(n, Arrival, Burst, Priotity) {}

//TODO: Make it for ---- >>>> NPP //! This is the last one...
// virtual function in base class
void PP::fillGanttChart()
{
    while (FCFS::stillContinue() != 0) // zero means equal na...
    {
        addToReadyQueue(); //1 lang ang laman... pero 3 ang PID
        removeFromReadQueue();
        if (RQ.empty() != true)
        {
            vGanntChart.push_back(PID.at(highestPriority()));
            clock++;
        }
        else
        {
            vGanntChart.push_back("x"); //IF nothing is in RQ, put x to indicate that it's idle...
            clock++;
        }
    }
}