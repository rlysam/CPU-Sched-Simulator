// * You can use function of parent class gamit yung...
//* ... "base_class : func_name"

//inherited from FCFS

#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "myheader.h"

using namespace std;

SJF::SJF() {}
SJF::SJF(int n, vector<int> Arrival, vector<int> Burst) : FCFS(n, Arrival, Burst) {} //COPY ng FCFS constructor -> pinalitan lang yung class name sa dulo...

// void SJF::generateValues()
// {
//     generatePID();    //PID MUNA //! IMPORTANT
//     fillGanttChart(); //generate Gantt Chart
//     generateFive();   //Generate yung table
// }

// virtual function in base class
//* Gawin nalang non-preemtive sa part na to yung SJf..
void SJF::fillGanttChart()
{
    while (stillContinue() != 0) // zero means equal na...
    {
        addToReadyQueue(); //1 lang ang laman... pero 3 ang PID
        removeFromReadQueue();
        if (RQ.empty() != true)
        {
            //gawin mo to hanggang di nauubos yung BT
            //* NON-Preemtive
            int x = shortest();
            for (int i = 0; i < BT[x]; i++)
            {
                vGanntChart.push_back(PID.at(x));
                clock++;
            }
        }
        else
        {
            vGanntChart.push_back("x"); //IF nothing is in RQ, put x to indicate that it's idle...
            clock++;
        }
    }
}

// search for idx of JUTS in PID :: SJF's version of getOriginalIndex()
int SJF::getOriginalIndex(int n)
{
    vector<string>::iterator it;
    it = std::find(PID.begin(), PID.end(), JUTS[n]);
    return it - PID.begin();
}

//1. POPULATE JUTS
//2. Search for first occurane of JUTS
//3. IF there are more than 1 with same BT, fill then look for Jutest
//PLUS Inheritance notes
int SJF::shortest()
{
    JUTS.clear();

    //* Yung getoriginal index
    //* Bali sinasabi mo, gamitin yung getOriginalIndex() ng FCFS, hindi yung OVERRIDING Function
    int a, idxOfLastPos;
    // ! BUG SRTF --- dapat di 0 index to, dapat last "Last"
    // ! BUG SRTF --- index outofrange kapag yung "(lastpost) gamit"
    // ! BUG --- Closes on other data sets when set to lastpsot
    // * FIX: FIRST EVER RUN:

    //? lastpost === needs to be ==== LAST POS. of Pn in RQ
    //? BUT what is Pn at first?
    //? Possible FIX: gawa ng check if FIRST EVER RUN...

    a = FCFS::getOriginalIndex(0); //RQ[0] not necesarrility a JUTS
    //1 Look for the Real Juts out of all in RQ
    //TODO: Make a new shortest for SRTF without this section
    for (int i = 0; i < RQ.size(); i++)
    {
        if (BT[a] > BT[FCFS::getOriginalIndex(i)])
        {
            a = FCFS::getOriginalIndex(i);
        }
    }

    JUTS.push_back(PID[a]); //This is the JUTS  OR "a" is the JUTSTEST

    //2 FILL  --- find if there are similar juts in RQ
    //populate JUTS with RQ
    for (int i = 0; i < RQ.size(); i++)
    {
        //* IF walang na specify na "base_class:", THEN ang gagamitin niya ay yung na declare sa kanya OR yung "Overriding Function"
        // ! logical error dito... sa SRTF...
        if (BT[a] == BT[FCFS::getOriginalIndex(i)] && alreadyExists(i) != 1) //same value ng JUTEST and not existing in JUTS
        {
            JUTS.push_back(PID.at(FCFS::getOriginalIndex(i)));
        }
    }

    //3 Search inside JUTS, AND れturn the jutest
    //RETURN
    if (JUTS.size() > 1)
    {
        //If maraming parehas na JUTS, THEN execute FCFS
        return firstToCome();
    }
    else
    {
        return a;
    }
}

//nasa JUTS na ba?
//Search mo lahat ng (JUTS), 1 kapag andon na, 0 kapag wala pa...
//*Sa base class na AddToRQ(), ito tinatawag nya... imbes na yung FCFS::AlreadyExists()
int SJF::alreadyExists(int n)
{
    vector<string>::iterator it;
    it = std::find(JUTS.begin(), JUTS.end(), PID[n]);
    if (it != RQ.end())
    {
        return 1; //nasa juts na
    }
    else
        return 0; //hindi nakita yung element OR anythin else, maybe walang laman
}

// imbis na RQ yung evaluate ng firstToCome, JUTS na...
//returns yung pinaka naunang dumating na JUTS
// ! BUG SRTF --- Dapat yung pag filter is mas precise
// ! BUG BUG BUG --- precision nung pag hanap ng last position
//firstToCome() sa JUTS[]
int SJF::firstToCome()
{
    int a, idxOfLastPos;
    if (firstTime)
    {
        a = FCFS::getOriginalIndex(0); //RQ[0] not necesarrility a JUTS
        firstTime = false;
    }
    else
    {
        vector<string>::iterator it;
        it = std::find(RQ.begin(), RQ.end(), PID[lastpost]);
        idxOfLastPos = it - RQ.begin();
        //ano yung position ng lastpost sa RQ
        a = FCFS::getOriginalIndex(idxOfLastPos); //RQ[0] not necesarrility a JUTS
    }

    for (int i = 0; i < JUTS.size(); i++)
    {
        //AT[a] == unang elem ng JUTS, AT[i] next element
        if (AT[a] > AT[getOriginalIndex(i)])
        { //Existing in RQ
            a = getOriginalIndex(i);
        }
    }
    return a;
}
