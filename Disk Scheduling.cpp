#include<iostream>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#define totalRequests 20
using namespace std;
int head, size, index = 0, totalHeadMovement = 0, diskQueue[totalRequests];
int main(int, char **);
void SSTF();
void getShortest(int &, int[], int[]);
void CSCAN();
void LOOK();
int rdtsc()
{
    __asm__ __volatile__("rdtsc");
}
int main(int argc, char *argv[])
{
    srand(rdtsc());
    int i, choice;
    for(i = 0; i < totalRequests; i++)
        ::diskQueue[i] = rand() % 200;
    ::head = rand() % 200;
    ::size = (sizeof(::diskQueue)) / (sizeof(int));
    choice = (atoi(argv[1]));
    if(choice == 1)
        SSTF();
    else if(choice == 2)
        CSCAN();
    else if(choice == 3)
        LOOK();
    else
    {
        cout<<"\nInvalid input...!!!";
        exit(0);
    }
    return 0;
}
void SSTF()
{
    int i, status[totalRequests];
    cout<<"\n##############################################################";
    cout<<"\nProblem: Shortest-Seek-Time-First (SSTF) Scheduling algorithm";
    cout<<"\nNo. of requests: "<<totalRequests;
    cout<<"\nRequest queue: ";
    for(i = 0; i < totalRequests; i++)
    {
        if((i % 5) == 0)
            cout<<"\n";
        cout<<::diskQueue[i]<<"\t";
    }
    sort(::diskQueue, (::diskQueue + ::size));
    for(i = 0; i < totalRequests; i++)
        status[i] = false;
    cout<<"\nCurrent head position: "<<::head;
    cout<<"\n##############################################################";
    cout<<"\nThe requests are serviced in the following order: \n";
    for(i = 0; i < totalRequests; i++)
        getShortest(::head, ::diskQueue, status);
    cout<<"\nTotal head movement (in cylinders.): "<<::totalHeadMovement;
}
void getShortest(int &head, int diskQueue[], int status[])
{
    int i, diff, temp;
    diff = 200;
    for(i = 0; i < totalRequests; i++)
    {
        if(status[i] == false)
        {
            if(abs(head - diskQueue[i]) < diff)
            {
                diff = abs(head - diskQueue[i]);
                temp = i;
            }
        }
    }
    head = diskQueue[temp];
    status[temp] = true;
    ::totalHeadMovement+= diff;
    cout<<diskQueue[temp]<<"\t";
}
void CSCAN()
{
    int i, temp = 0;
    cout<<"\n#####################################################";
    cout<<"\nProblem: Circular SCAN (C-SCAN) Scheduling algorithm";
    cout<<"\nNo. of requests: "<<totalRequests;
    cout<<"\nRequest queue: ";
    for(i = 0; i < totalRequests; i++)
    {
        if((i % 5) == 0)
            cout<<"\n";
        cout<<::diskQueue[i]<<"\t";
    }
    sort(::diskQueue, (::diskQueue + ::size));
    cout<<"\nCurrent head position: "<<::head;
    cout<<"\n#####################################################";
    cout<<"\nThe requests are serviced in the following order: \n";
    for(i = 0; i < totalRequests; i++)
    {
        if(::head <= ::diskQueue[i])
        {
            ::index = i;
            break;
        }
    }
    i = ::index;
    while(i < totalRequests)
    {
        ::totalHeadMovement+= abs(::head - ::diskQueue[i]);
        ::head = ::diskQueue[i];
        cout<<::diskQueue[i]<<"\t";
        i++;
    }
    i = 0;
    ::totalHeadMovement+= (200 - ::head);
    ::head = 0;
    while(i < ::index)
    {
        ::totalHeadMovement+= abs(::head - ::diskQueue[i]);
        ::head = ::diskQueue[i];
        cout<<::diskQueue[i]<<"\t";
        i++;
    }
    cout<<"\nTotal head movement (in cylinders.): "<<::totalHeadMovement;
}
void LOOK()
{
    int i, temp, startIndex = 0, maxIndex = totalRequests;
    cout<<"\n####################################";
    cout<<"\nProblem: LOOK Scheduling algorithm";
    cout<<"\nNo. of requests: "<<totalRequests;
    cout<<"\nRequest queue: ";
    for(i = 0; i < totalRequests; i++)
    {
        if((i % 5) == 0)
            cout<<"\n";
        cout<<::diskQueue[i]<<"\t";
    }
    sort(::diskQueue, (::diskQueue + ::size));
    cout<<"\nCurrent head position: "<<::head;
    cout<<"\n####################################";
    cout<<"\nThe requests are serviced in the following order: \n";
    for(i = 0; i < totalRequests; i++)
    {
        if(::head <= ::diskQueue[i])
        {
            startIndex = i;
            break;
        }
    }
    temp = ::diskQueue[0];
    for(i = 1; i < totalRequests; i++)
    {
        if(temp < ::diskQueue[i])
        {
            temp = ::diskQueue[i];
            maxIndex = i;
        }
    }
    i = startIndex;
    while(i <= maxIndex)
    {
        ::totalHeadMovement+= abs(::head - ::diskQueue[i]);
        ::head = ::diskQueue[i];
        cout<<::diskQueue[i]<<"\t";
        i++;
    }
    cout<<"\nReversing at: "<<::diskQueue[maxIndex]<<"\n";
    i = startIndex - 1;
    while(i >= 0)
    {
        ::totalHeadMovement+= abs(::head - ::diskQueue[i]);
        ::head = ::diskQueue[i];
        cout<<::diskQueue[i]<<"\t";
        i--;
    }
    cout<<"\nStopped at: "<<::diskQueue[0];
    cout<<"\nTotal head movement (in cylinders.): "<<::totalHeadMovement;
}
