#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "myheader.h"
#include <stdlib.h>

using namespace std;

int main()
{
    const int MIN = 3;
    int ans = 1; //on
    int x = -1;
    MainMenu my_objct; //MainMenu

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
            my_objct.set_technique();
            break;
        case '2':
            my_objct.set_num_p();
            break;
        case '3':
            my_objct.set_AT();
            break;
        case '4':
            my_objct.set_BT();
            break;
        case '5':
            my_objct.set_Prio();
            break;
        case '6':
            my_objct.set_TQ();
            break;
        case '0': //FINALIZE

            x = my_objct.finalize();
            
            if (x == 1) //FCFS
            {
                fcfs1 = FCFS(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT()); //contruct using my_object return data
                fcfs1.displayTable();
                fcfs1.displayGanttChart();
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 2) //SJF
            {
                sjf1 = SJF(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT()); //contruct using my_object return data
                sjf1.displayTable();
                sjf1.displayGanttChart();
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 3) //SRTF
            {
                srtf1 = SRTF(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT());
                srtf1.displayTable();//*activate after vGC is gtg
                srtf1.displayGanttChart();//!first to debug
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 4) {//NPP
                //!passed inherited from FCFS
                npp1 = NPP(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT(),my_objct.getPriority()); //contruct using my_object return data
                npp1.displayTable();
                npp1.displayGanttChart();
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 5) {//PP
                //!passed inherited from NPP
                pp1 = PP(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT(),my_objct.getPriority()); 
                pp1.displayTable();
                pp1.displayGanttChart();
                cout << "\n\nPress any key to continue...";
                getch();
            }
            else if (x == 6) {//PP
                rr1 = RR(my_objct.getNumProcess(), my_objct.getAT(), my_objct.getBT(), my_objct.getTQ()); //contruct using my_object return data
                rr1.displayTable();//! BUG
                rr1.displayGanttChart();
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

//comparison(?)
void runTechnique(int n)
{
}