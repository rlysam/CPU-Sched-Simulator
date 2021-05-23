#pragma once
// // using namespace std;
class Display
{
    //may constructor na hinihingi lahat...
    //last argument is which technique coming from MainMenu class
    Display();                                                                                      //default
    Display(std::vector<std::string> GanttChart, std::vector<std::string> PID, std::string technique, std::vector<int> AT, std::vector<int> BT, std::vector<int> ST, std::vector<int> ET, std::vector<int> RT, std::vector<int> TT, std::vector<int> WT);
    Display(std::vector<std::string> GanttChart, std::vector<std::string> PID, std::string technique, std::vector<int> AT, std::vector<int> BT, std::vector<int> PR, std::vector<int> ST, std::vector<int> ET, std::vector<int> RT, std::vector<int> TT, std::vector<int> WT);
    Display(std::vector<std::string> GanttChart, std::vector<std::string> PID, std::string technique, std::vector<int> AT, std::vector<int> BT, int TQ, std::vector<int> ST, std::vector<int> ET, std::vector<int> RT, std::vector<int> TT, std::vector<int> WT);
};

class MainMenu
{
protected:
    //CAN BE CHANGED BY USER
    std::string selected_technique = "First Come First Serve";
    int numProcess = 3;
    std::vector<int> AT{0, 0, 0};
    std::vector<int> BT{1, 1, 1};
    std::vector<int> Priority{0, 0, 0};
    int TQ = 1; //at least 1, para di mag loop
    //List of techniques available
    std::vector<std::string> allTechniques{"First Come First Serve", "Shortest Job First", "Shortest Remaining Time First", "Non-Preemtive Priority", "Preemtive Priority", "Round Robin"};

public:
    MainMenu();
    void updateScreen();
    void getEntries(std::vector<int> n);
    void show_option();

    void reset(int n); //set to original value
    void set_technique();
    void set_AT();
    void set_BT();
    void set_Prio();
    void set_TQ();
    void set_num_p();
    void printLabel(int i);

    std::string anongTechnique() { return selected_technique; } //for switch statement

    //Returns data from
    int getNumProcess() { return numProcess; }          //#process
    std::vector<int> getAT() { return AT; }             //mga AT
    std::vector<int> getBT() { return BT; }             //mga BT
    std::vector<int> getPriority() { return Priority; } //mga Priority
    int getTQ() { return TQ; }                          //yung Time Quantum ni Ian

    //return int of corresponding technique. Ex. FCFS = 1..., RR = 6
    int finalize();
};

class FCFS
{
protected: //gagamitin ng child class, ie. SJF & SRTF
    //Data needed by FCFS
    //FROM USER
    int np; //num of process
    std::vector<int> AT;
    std::vector<int> BT;
    //LOCAL VARS
    std::vector<std::string> PID;
    std::vector<int> ST, ET, TT, WT, RT;

    //accessory variables
    int clock = 0;                        //clock always starts at time zero
    int lastpost = 0;                     // ! para to sa PREEMTIVES --- need i-track yung last inserted Process...
    std::vector<std::string> RQ;          //Ready Queue -- mga PID
    std::vector<std::string> vGanntChart; //lalagyan ng idle time saka lahat ng mga occurances ng BT ng bawat process

public:
    FCFS();                                                        //default
    FCFS(int n, std::vector<int> Arrival, std::vector<int> Burst); //get

    void generatePID();

    virtual int firstToCome();
    virtual void fillGanttChart();

    void removeFromReadQueue();
    virtual void addToReadyQueue();
    virtual int alreadyExists(int n);

    // index of process in RQ in PID
    virtual int getOriginalIndex(int n);

    virtual int stillContinue();

    void generateSTET();
    void generateFive();
    virtual void printTable();

    //itong dalawa lang ang kailangan tawagin sa main() after mag gawa ng con...
    void displayTable();
    virtual void displayGanttChart();
};

//inherit SRTF from here...
class SJF : public FCFS
{
protected:
    std::vector<std::string> JUTS;
    int idx1Juts;
    bool firstTime = true;

public:
    //TODO di na ata kailangan lagyan ng cons dito
    SJF();                                                        //need for declaring once before Switch-Case
    SJF(int n, std::vector<int> Arrival, std::vector<int> Burst); //COPY ng FCFS constructor -> pinalitan lang yung class name sa dulo...

    // kagaya sa firstToCome, pero BT yuukkg tinitignan
    int shortest();
    // int idx();//eval whose lowest AT in JUTS

    // override ng fillGanttChart() at saka get originalIndex()
    int firstToCome();           //RQ->JUTS
    int getOriginalIndex(int n); //RQ->JUTS  SJF's version

    int alreadyExists(int n); //ginamit ko sa shortest() -- second part

    void fillGanttChart();
};

class SRTF : public SJF
{
protected:
    std::vector<int> copyBT;

public:
    //cons
    SRTF();
    SRTF(int n, std::vector<int> Arrival, std::vector<int> Burst); //COPY ng FCFS constructor -> pinalitan lang yung class name sa dulo...
    void fillGanttChart();
    // int shortest();
    int remaining_BToFx(int x);
    void addToReadyQueue();
    int stillContinue();
};

class NPP : public FCFS
{
protected:
    std::vector<int> PT;          //Equivalent sa "BT"
    std::vector<std::string> BIP; //Equivalent sa "JUTS"
public:
    NPP(); //default
    NPP(int n, std::vector<int> Arrival, std::vector<int> Burst, std::vector<int> Priotity);

    void fillGanttChart();
    int highestPriority();
    int alreadyExists(int n); //ginamit ko sa highestPrio() -- second part
    //modified for searching Priority...
    int getOriginalIndex(int n);
    int firstToCome();
    void printTable(); //added priority
};

class PP : public NPP
{
public:
    PP(); //default
    PP(int n, std::vector<int> Arrival, std::vector<int> Burst, std::vector<int> Priotity);
    void fillGanttChart();
};

class RR : public FCFS
{
protected:
    bool first = true;
    int TQ;
    bool idle = false; //kapag nag daan sa idle time, magiging true:wall

public:
    //cons
    RR();
    RR(int n, std::vector<int> Arrival, std::vector<int> Burst, int TIME_Q);

    void fillGanttChart();
    void addToReadyQueue();
    virtual int remaining_BToFx(int x);
};
