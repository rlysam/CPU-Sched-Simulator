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
    int ans = 1; //on
    int x = -1;
    MainMenu my_objct; //MainMenu
    Display disp;

    FCFS fcfs1;
    SJF sjf1;
    SRTF srtf1;
    NPP npp1;
    PP pp1;
    RR rr1;

    while (ans)
    {
        system("cls");
        my_objct.updateScreen();

        switch (getch()) // change settings, finalize or exit program
        {
        case '1':
            system("cls");
            my_objct.set_technique();
            break;
        case '2':
            system("cls");
            my_objct.set_num_p();
            break;
        case '3':
            system("cls");
            my_objct.set_AT();
            break;
        case '4':
            system("cls");
            my_objct.set_BT();
            break;
        case '5':
            system("cls");
            my_objct.set_Prio();
            break;
        case '6':
            system("cls");
            my_objct.set_TQ();
            break;
        case '0': //FINALIZE

            //* Construct all
            fcfs1 = FCFS(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT());
            sjf1 = SJF(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT()); //contruct using my_object return data
            srtf1 = SRTF(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT());
            npp1 = NPP(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT(), my_objct.getPriority()); //contruct using my_object return data
            pp1 = PP(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT(), my_objct.getPriority());
            rr1 = RR(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT(), my_objct.getTQ()); //contruct using my_object return data

            system("cls");
            x = my_objct.finalize(); //hahanapin lang kung anong Technique ang pinili...

            if (x == 1) //FCFS
            {
                //Displays Table & Gantt Chart
                disp = Display(fcfs1.getGC(),fcfs1.getPID(),my_objct.getTechnique(),my_objct.getAT(), my_objct.getBT(),fcfs1.getST(),fcfs1.getET(),fcfs1.getRT(),fcfs1.getTT(),fcfs1.getWT());
                cout
                    << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 2) //SJF
            {
                disp = Display(sjf1.getGC(),sjf1.getPID(),my_objct.getTechnique(),my_objct.getAT(), my_objct.getBT(),sjf1.getST(),sjf1.getET(),sjf1.getRT(),sjf1.getTT(),sjf1.getWT());
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 3) //SRTF
            {
                disp = Display(srtf1.getGC(),srtf1.getPID(),my_objct.getTechnique(),my_objct.getAT(), my_objct.getBT(),srtf1.getST(),srtf1.getET(),srtf1.getRT(),srtf1.getTT(),srtf1.getWT());
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 4)//NPP
            { 
                disp = Display(npp1.getGC(),npp1.getPID(),my_objct.getTechnique(),my_objct.getAT(), my_objct.getBT(),npp1.getPR(),npp1.getST(),npp1.getET(),npp1.getRT(),npp1.getTT(),npp1.getWT());
                cout
                    << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 5)
            { //PP
                disp = Display(pp1.getGC(),pp1.getPID(),my_objct.getTechnique(),my_objct.getAT(), my_objct.getBT(),pp1.getPR(),pp1.getST(),pp1.getET(),pp1.getRT(),pp1.getTT(),pp1.getWT());
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 6)
            { //RR
                disp = Display(rr1.getGC(),rr1.getPID(),my_objct.getTechnique(),my_objct.getAT(), my_objct.getBT(), my_objct.getTQ(), rr1.getST(),rr1.getET(),rr1.getRT(),rr1.getTT(),rr1.getWT());
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == -1) //may zero sa BT
            {
                cout << "Message: Can't have zero value in BT...\nPress anykey to continue";
                getch();
            }
            else
                cout << "Something went wrong...";
            getch();
            //? Do you want to compare?
            break; //break case '0' (FINALIZE)
        case 'r':
            my_objct.reset(MIN); //3 minimum
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
