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
    while (stillContinue() != 0) //* Zero means tapos na lahat ngprocess
    {
        addToReadyQueue();
        removeFromReadQueue();

        if (RQ.empty() != true)
        {
            vGanntChart.push_back(PID.at(shortest()));
            clock++;
        }

        else
        {
            vGanntChart.push_back("x"); //IF nothing is in RQ, put x to indicate that it's idle...
            clock++;
        }
    }
}
