#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "myheader.h"
#include <stdlib.h>

using namespace std;

// void constructAll();
int compareBa();
vector<int> whichOnes(vector<string> allTech);

int main()
{
    const int MIN = 3;
    int x = -1;
    MainMenu obj; //MainMenu
    Display disp[6];
    vector<int> compares;
    char ans = 1;
    FCFS fcfs1;
    SJF sjf1;
    SRTF srtf1;
    NPP npp1;
    PP pp1;
    RR rr1;

    while (ans)
    {
        system("cls");
        obj.updateScreen();

        switch (getch()) // change settings, finalize or exit program
        {
        case '1':
            system("cls");
            obj.set_technique();
            break;
        case '2':
            system("cls");
            obj.set_num_p();
            break;
        case '3':
            system("cls");
            obj.set_AT();
            break;
        case '4':
            system("cls");
            obj.set_BT();
            break;
        case '5':
            system("cls");
            obj.set_Prio();
            break;
        case '6':
            system("cls");
            obj.set_TQ();
            break;
        case '0': //FINALIZE

            //* Construct all
            //* GENERATE techniques
            fcfs1 = FCFS(obj.getNumProcess(), obj.getAT(), obj.getBT());
            fcfs1.generateValues();
            sjf1 = SJF(obj.getNumProcess(), obj.getAT(), obj.getBT());
            sjf1.generateValues();
            srtf1 = SRTF(obj.getNumProcess(), obj.getAT(), obj.getBT());
            srtf1.generateValues();
            npp1 = NPP(obj.getNumProcess(), obj.getAT(), obj.getBT(), obj.getPriority());
            npp1.generateValues();
            pp1 = PP(obj.getNumProcess(), obj.getAT(), obj.getBT(), obj.getPriority());
            pp1.generateValues();
            rr1 = RR(obj.getNumProcess(), obj.getAT(), obj.getBT(), obj.getTQ());
            rr1.generateValues();

            //* GENERATE disp[]
            disp[0] = Display(fcfs1.getGC(), fcfs1.getPID(), obj.getTechnique(), obj.getAT(), obj.getBT(), obj.getPriority(), obj.getTQ(), fcfs1.getST(), fcfs1.getET(), fcfs1.getRT(), fcfs1.getTT(), fcfs1.getWT());
            disp[1] = Display(sjf1.getGC(), sjf1.getPID(), obj.getTechnique(), obj.getAT(), obj.getBT(), obj.getPriority(), obj.getTQ(), sjf1.getST(), sjf1.getET(), sjf1.getRT(), sjf1.getTT(), sjf1.getWT());
            disp[2] = Display(srtf1.getGC(), srtf1.getPID(), obj.getTechnique(), obj.getAT(), obj.getBT(), obj.getPriority(), obj.getTQ(), srtf1.getST(), srtf1.getET(), srtf1.getRT(), srtf1.getTT(), srtf1.getWT());
            disp[3] = Display(npp1.getGC(), npp1.getPID(), obj.getTechnique(), obj.getAT(), obj.getBT(), obj.getPriority(), obj.getTQ(), npp1.getST(), npp1.getET(), npp1.getRT(), npp1.getTT(), npp1.getWT());
            disp[4] = Display(pp1.getGC(), pp1.getPID(), obj.getTechnique(), obj.getAT(), obj.getBT(), obj.getPriority(), obj.getTQ(), pp1.getST(), pp1.getET(), pp1.getRT(), pp1.getTT(), pp1.getWT());
            disp[5] = Display(rr1.getGC(), rr1.getPID(), obj.getTechnique(), obj.getAT(), obj.getBT(), obj.getPriority(), obj.getTQ(), rr1.getST(), rr1.getET(), rr1.getRT(), rr1.getTT(), rr1.getWT());

            system("cls");
            x = obj.finalize();
            x--;

            if (x == 0) //FCFS
            {
                disp[x].displayTable();
                disp[x].displayGC();
            }
            else if (x == 1) //SJF
            {
                disp[x].displayTable();
                disp[x].displayGC();
            }
            else if (x == 2) //SRTF
            {
                disp[x].displayTable();
                disp[x].displayGC();
            }
            else if (x == 3) //NPP
            {
                disp[x].displayTable();
                disp[x].displayGC();
            }
            else if (x == 4)
            { //PP
                disp[x].displayTable();
                disp[x].displayGC();
            }
            else if (x == 5)
            { //RR
                disp[x].displayTable();
                disp[x].displayGC();
            }
            else if (x == -1) //may zero sa BT
            {
                cout << "Message: Can't have zero value in BT...";
            }
            else
                cout << "Something went wrong...";

            cout << "Press enter to Continue...\n\n";
            getch();
            //? Do you want to compare? if(yes)
            if (compareBa() == 1) //YES
            {
                auto b = obj.getAllTech();
                system("cls");
                compares = whichOnes(b);
                system("cls");
                // cout<<"compares size: ";
                // cout<<compares.size();
                getch();

                for (int i = 0; i < compares.size(); i++)
                {
                    cout << b[compares[i] - 1];
                    disp[compares[i] - 1].displayGC();
                    cout << endl
                         << endl;
                }

                for (int i = 0; i < compares.size(); i++)
                {
                    disp[compares[i] - 1].displayAverages(b[compares[i] - 1]);
                    cout << endl
                         << endl;
                }
                cout << "\n\nEnd of comparison. Press Enter to conitnue...";
                getch();
            } //exits finalize

            system("cls");
            cout << "...going back to MAIN MENU. Press enter...\n\n";
            getch();
            break; //break case '0' (FINALIZE)
        case 'r':
            obj.reset(MIN); //3 minimum
            break;
        case 'x':
            ans = 0;
            break;
        default:
            cout << "Wala sa options";
            getch();
            break;
        }
    }
    return 0;
}

int compareBa()
{
    char ans2;
    bool go = true;
    do
    {
        cout << "Do you want to compare? [y/n]";
        cin>>ans2 ;
        // (char)tolower(ans2);
        if (ans2 == 'y' || ans2 == 'n')
            go = false;

    } while (go);

    if (ans2 == 'y')
        return 1;
    else
        return 0;
}

//vector of int, kung ano ano didisplay
vector<int> whichOnes(vector<string> allTech)
{

    vector<int> these;
    int numComp;
    bool go = true;
    //ask how many
    cout << "How many? This many: ";
    do
    {
        cin >> numComp;
        if (numComp > 0 && numComp < 7)
            go = false;
    } while (go);

    for (int i = 0; i < allTech.size(); i++)
    {
        cout << i + 1 << " = " << allTech[i] << endl;
    }
    // cout << endl
    //      << endl;
    cout<<"\n\nCompare "<<numComp;
    cout << "\n\n Type number of corresponding PID\n\n";
    for (int i = 0; i < numComp; i++)
    {
        go = true;
        cout << i + 1 << ".)";

        do
        {
            cin >> numComp;
            if (numComp > 0 && numComp < 7) // and not not a duplicate
                go = false;
        } while (go);

        these.push_back(numComp); //magiging int yung char... SANA
        cout << endl;
    }
    return these;
}