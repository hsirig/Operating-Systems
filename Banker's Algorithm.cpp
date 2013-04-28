#include<iostream>
#include<stdlib.h>
#include<time.h>
#define numberOfProcesses 5
#define typesOfResources 3
using namespace std;
int main(int, char **);
void printVectors();
void stateCheck();
void sleep(int);
int requestProcess;
int available[typesOfResources], max[numberOfProcesses][typesOfResources], allocation[numberOfProcesses][typesOfResources], need[numberOfProcesses][typesOfResources], requestResources[typesOfResources];
int rdtsc()
{
    __asm__ __volatile__("rdtsc");
}
int main(int argc, char *argv[])
{
    srand(rdtsc());
    int i, j;
    for(i = 0; i < typesOfResources; i++)
        ::available[i] = rand() % 10;
    ::available[0] = 3;
    ::available[1] = 3;
    ::available[2] = 2;
    for(i = 0; i < numberOfProcesses; i++)
    {
        for(j = 0; j < typesOfResources; j++)
            ::allocation[i][j] = rand() % 10;
    }
    ::allocation[0][0] = 0;
    ::allocation[0][1] = 1;
    ::allocation[0][2] = 0;
    ::allocation[1][0] = 2;
    ::allocation[1][1] = 0;
    ::allocation[1][2] = 0;
    ::allocation[2][0] = 3;
    ::allocation[2][1] = 0;
    ::allocation[2][2] = 2;
    ::allocation[3][0] = 2;
    ::allocation[3][1] = 1;
    ::allocation[3][2] = 1;
    ::allocation[4][0] = 0;
    ::allocation[4][1] = 0;
    ::allocation[4][2] = 2;
    for(i = 0; i < numberOfProcesses; i++)
    {
      for(j = 0; j < typesOfResources; j++)
            ::max[i][j] = rand() % 10;
    }
    ::max[0][0] = 7;
    ::max[0][1] = 5;
    ::max[0][2] = 3;
    ::max[1][0] = 3;
    ::max[1][1] = 2;
    ::max[1][2] = 2;
    ::max[2][0] = 9;
    ::max[2][1] = 0;
    ::max[2][2] = 2;
    ::max[3][0] = 2;
    ::max[3][1] = 2;
    ::max[3][2] = 2;
    ::max[4][0] = 4;
    ::max[4][1] = 3;
    ::max[4][2] = 3;
    for(i = 0; i < numberOfProcesses; i++)
    {
	    for(j = 0; j < typesOfResources; j++)
	    {
            if(::max[i][j] > 0)
                ::need[i][j] = ::max[i][j] - ::allocation[i][j];
	    }
    }
    ::need[0][0] = 7;
    ::need[0][1] = 4;
    ::need[0][2] = 3;
    ::need[1][0] = 1;
    ::need[1][1] = 2;
    ::need[1][2] = 2;
    ::need[2][0] = 6;
    ::need[2][1] = 0;
    ::need[2][2] = 0;
    ::need[3][0] = 0;
    ::need[3][1] = 1;
    ::need[3][2] = 1;
    ::need[4][0] = 4;
    ::need[4][1] = 3;
    ::need[4][2] = 1;
    cout<<"\n###########################################################";
    cout<<"\nProblem: Safety & Banker's algorithms";
    cout<<"\nNo. of processes: "<<numberOfProcesses;
    cout<<"\nTypes of resources: "<<typesOfResources;
    printVectors();
    cout<<"\n###########################################################";
    stateCheck();
}
void printVectors()
{
    int i, j;
    cout<<"\nAllocation: \tNeed: \t\tMax: \t\tAvailable:";
    for(i = 0; i < numberOfProcesses; i++)
    {
        cout<<"\n";
        for(j = 0; j < typesOfResources; j++)
            cout<<::allocation[i][j]<<"   ";
        cout<<"\t";
        for(j = 0; j < typesOfResources; j++)
            cout<<::need[i][j]<<"   ";
        cout<<"\t";
        for(j = 0; j < typesOfResources; j++)
            cout<<::max[i][j]<<"   ";
        if(i == 0)
        {
            cout<<"\t";
            for(j = 0; j < typesOfResources; j++)
                cout<<::available[j]<<"   ";
        }
    }
}
void stateCheck()
{
    bool complete = true;
    int i, j, k, found = 0, count = 0;
    int work[typesOfResources], finish[numberOfProcesses], stateOrder[numberOfProcesses];
    for(i = 0; i < typesOfResources; i++)
        work[i] = ::available[i];
    for(i = 0; i < numberOfProcesses; i++)
        finish[i] = false;
    for(i = 0, k = 0; k < (numberOfProcesses * numberOfProcesses); i++, k++)
    {
        i = k % numberOfProcesses;
        if(finish[i] == false)
        {
            found = 0;
            for(j = 0; j < typesOfResources; j++)
            {
                if(::need[i][j] > work[j])
                {
                    found++;
                    break;
                }
            }
            if(found == 0)
            {
                finish[i] = true;
                stateOrder[count++] = i;
                for(j = 0; j < typesOfResources; j++)
                    work[j]+= ::allocation[i][j];
            }
        }
    }
    for(i = 0; i < numberOfProcesses; i++)
    {
        if(finish[i] != true)
        {
            complete = false;
            break;
        }
    }
    if(complete == true)
    {
        cout<<"\nThe current / resulting state is safe.";
        cout<<"\nSafe state sequence: ";
        cout<<"<";
        for(i = 0; i < numberOfProcesses; i++)
        {
            cout<<stateOrder[i];
            if(i < (numberOfProcesses - 1))
                cout<<", ";
        }
        cout<<">";
        cout<<"\nIncoming request: ";
        //::requestProcess = rand() % numberOfProcesses;
        ::requestProcess = 1;
        cout<<"\n\tProcess: "<<::requestProcess;
        cout<<"\n\tRequested resources: (";
        ::requestResources[0] = 1;
        ::requestResources[1] = 0;
        ::requestResources[2] = 2;
        for(i = 0; i < typesOfResources; i++)
        {
            //::requestResources[i] = rand() % ::available[i];
            cout<<::requestResources[i];
            if(i < (typesOfResources - 1))
                cout<<", ";
        }
        cout<<")";
        found = true;
        for(i = 0; i < typesOfResources; i++)
        {
            if(::requestResources[i] > ::need[::requestProcess][i])
            {
                found = false;
                break;
            }
        }
        if(found == true)
        {
            for(i = 0; i < typesOfResources; i++)
            {
                if(::requestResources[i] > ::available[i])
                {
                    found = false;
                    break;
                }
            }
            if(found == false)
                cout<<"\nRequest cannot be ganted due to one or more of the following reasons:\ni) Resources are not available.\nii) Resulting state is unsafe.\nProcess - "<<requestProcess<<" may have to wait.";
            else
            {
                cout<<"\nRequest can be ganted.";
                for(i = 0; i < typesOfResources; i++)
                {
                    ::available[i]-= ::requestResources[i];
                    ::allocation[::requestProcess][i]+= ::requestResources[i];
                    ::need[::requestProcess][i]-= ::requestResources[i];
                }
                printVectors();
                stateCheck();
            }
        }
        else
            cout<<"\nRequest cannot be granted.\nReason: Maximum claim exceeded.";
    }
    else
    {
        cout<<"\nThe current / resulting state is unsafe.\nRolling back allocation";
        for(i = 0; i < 3; i++)
        {
            sleep(1);
            cout<<".";
        }
        for(i = 0; i < typesOfResources; i++)
        {
            ::available[i]+= ::requestResources[i];
            ::allocation[::requestProcess][i]-= ::requestResources[i];
            ::need[::requestProcess][i]+= ::requestResources[i];
        }
        cout<<"\nRollback successful.";
        printVectors();
    }
}
void sleep(int delay)
{
    time_t now, later;
    now = time(NULL);
    later = now + delay;
    while(now <= later)
        now = time(NULL);
}
