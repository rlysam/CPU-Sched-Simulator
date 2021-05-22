// inherit nalang ulit natin yung FCFS... pero yung concept, gayahin sa SFJ
//! BIP  ==  HIGHEST priority... BIP = Priotity; but in STRING

#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "myheader.h"

using namespace std;

// std::vector<int>Priority;

NPP::NPP() {}

// first 3 args are for base class, the last one is for NPP
NPP::NPP(int n, vector<int> Arrival, vector<int> Burst, vector<int> Priotity)
    : FCFS(n, Arrival, Burst)
{
    PT = Priotity;
}

//TODO: Make it for ---- >>>> NPP //! This is the last one...
// virtual function in base class
void NPP::fillGanttChart()
{
    while (FCFS::stillContinue() != 0) // zero means equal na...
    {
        addToReadyQueue(); //1 lang ang laman... pero 3 ang PID
        removeFromReadQueue();
        if (RQ.empty() != true)
        {
            //gawin mo to hanggang di nauubos yung BT
            //* NON-Preemtive
            int x = highestPriority();
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

//returns highest "priotity" from
// instead of "BT", compare "priority"...
//! PREVIOUSLY : "shortest()" from SJF
int NPP::highestPriority()
{
    BIP.clear();
    //* Yung getoriginal index
    //* Bali sinasabi mo, gamitin yung getOriginalIndex() ng FCFS, hindi yung OVERRIDING Function

    int a = FCFS::getOriginalIndex(0); //RQ[0] not necesarrility a BIP

    //1 Look for HIGHEST Priority inside RQ
    for (int i = 0; i < RQ.size(); i++)
    {
        if (PT[a] > PT[FCFS::getOriginalIndex(i)]) //* Done comparison...
        {
            a = FCFS::getOriginalIndex(i);
        }
    }

    BIP.push_back(PID[a]); //This is the JUTS  OR "a" is the BIPIEST

    //2 FILL  --- find if there are similar juts in RQ
    //populate BIP with similar BIP in RQ
    for (int i = 0; i < RQ.size(); i++)
    {
        //* IF walang na specify na "base_class:", THEN ang gagamitin niya ay yung na declare sa kanya OR yung "Overriding Function"
        if (PT[a] == PT[FCFS::getOriginalIndex(i)] && alreadyExists(i) != 1) //same value ng BIPIEST and not existing in BIP
        {
            BIP.push_back(PID.at(FCFS::getOriginalIndex(i)));
        }
    }

    //3 Search inside BIP, AND れturn the BIPIEST
    //RETURN
    if (BIP.size() > 1)
    {
        //If maraming parehas na BIP, THEN execute FCFS
        return firstToCome();
    }
    else
    {
        return a;
    }
}

//nasa BIP na ba?
//Search mo lahat ng (BIP), 1 kapag andon na, 0 kapag wala pa...
//*Sa base class na AddToRQ(), ito tinatawag nya... imbes na yung FCFS::AlreadyExists()
int NPP::alreadyExists(int n)
{
    vector<string>::iterator it;
    it = std::find(BIP.begin(), BIP.end(), PID[n]);
    if (it != RQ.end())
    {
        return 1; //nasa juts na
    }
    else
        return 0; //hindi nakita yung element OR anythin else, maybe walang laman
}

//*DONE
//returns yung pinaka naunang dumating na JUTS Whenever there's a tie
int NPP::firstToCome()
{
    //First BIP that came to RQ
    // getOriginalIndex = lahat nalang ng JUTS ang andito...
    int a = getOriginalIndex(lastpost); //first elem ng JUTS //* dahil yung getOriginalIndex() ng SJF("Derived class") yung gagamitin
    for (int i = 0; i < BIP.size(); i++)
    {
        //AT[a] == unang elem ng JUTS, AT[i] next element
        if (AT[a] > AT[getOriginalIndex(i)])
        { //Existing in RQ
            a = getOriginalIndex(i);
        }
    }
    return a;
}

//*DONE
// search for idx of BIP in PID :: SJF's version of getOriginalIndex()
int NPP::getOriginalIndex(int n)
{
    vector<string>::iterator it;
    it = std::find(PID.begin(), PID.end(), BIP[n]);
    return it - PID.begin();
}

//decoratives
void NPP::printTable()
{
    cout << "Process\tAT\tCPU BT\tPriority\tST\tET\tRT\tTT\tWT\n\n";
    for (int i = 0; i < PID.size(); i++)
    {
        cout << PID[i]<< "\t"  << AT[i] << "\t" << BT[i] << "\t" << PT[i]<< "\t\t"
             << ST[i] << "\t" << ET[i] << "\t"
             << RT[i] << "\t"
             << TT[i] << "\t"
             << WT[i] << "\t" << endl;
    }
}
