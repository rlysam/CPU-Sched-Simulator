#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "myheader.h"
#include <stdlib.h>

using namespace std;

void constructAll();

int main()
{
    const int MIN = 3;
    int x = -1;

    int numComp;
    vector<int> compares;

    MainMenu obj; //MainMenu
    Display disp[6];

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

            cout << "\n\nPress any key to continue...";
            getch();
            //? Do you want to compare? if(yes)

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

// int compareBa()
// {
//     char ans2;
//     do
//     {
//         cout << "Do you want to compare? [y/n]";
//         ans2 = getch();
//         (char)tolower(ans2);
//         if (ans2 == 'y')
//         {
//             cout << "How";
//         }
//     } while (ans2 != 'y' || ans2 != 'n');
    
//     if (ans2 == 'y') {
//         cout<<"\n\nHow many? Type: ";
//         return getch();
//     }
//     else return 0;
// }

// vector<int> whichOnes(int n, vector<int> PID){
//     vector<int> these;

//     for (int i = 0; i < PID.size(); i++)
//     {
//         cout<<i+1<<" = "<<PID[i] <<endl;
//     }

//    cout<<"\n\nPili ka ng " 
// }