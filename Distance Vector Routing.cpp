#include<iostream.h>
#include<conio.h>
#define INT_MAX 10
int main()
{
    int nodes, i, j, k, temp;
    cout<<"\n\n\n\t\t\tDISTANCE VECTOR ROUTING";
    cout<<"\n\n\n\tEnter the no. of nodes: ";
    cin>>nodes;
    int distanceVector[nodes][nodes];
    int via[nodes][nodes];
    if(nodes > 0)
    {
    	memset(distanceVector, INT_MAX, sizeof(distanceVector));
       	memset(via, 0, sizeof(via));
        cout<<"\n\n\tFor each pair of nodes, if adjacent - 1, else - any: ";
        cout<<"\n\n";
    }
    else
    {
    	cout<<"\n\n\tInvalid input. Aborted...!!!";
        exit(0);
    }
    for(i = 0; i < nodes; i++)
    {
    	for(j = 0; j < nodes; j++)
        {
            if(i == j)
            {
            	cout<<"\n\t\t"<<(i + 1)<<" - "<<(j + 1)<<": 0\n";
            	continue;
            }
            else if((distanceVector[i][j] != INT_MAX) && (i < j))
            {
            	cout<<"\n\t\t"<<(i + 1)<<" - "<<(j + 1)<<": ";
            	cin>>temp;
            	if(temp == 1)
            	{
               	    cout<<"\n\t\tEnter cost of the link between nodes "<<(i + 1)<<" and "<<(j + 1)<<": ";
                    cin>>distanceVector[i][j];
                    distanceVector[j][i] = distanceVector[i][j];
                    via[i][j] = j + 1;
                }
            }
            else
            {
            	if(distanceVector[i][j] > 50000)
                    cout<<"\n\t\tCost of the link between nodes "<<(i + 1)<<" and "<<(j + 1)<<": -"<<"\n";
                else
            	    cout<<"\n\t\tCost of the link between nodes "<<(i + 1)<<" and "<<(j + 1)<<": "<<distanceVector[i][j]<<"\n";
            }
        }
    }
    for(i = 0; i < nodes; i++)
    {
    	distanceVector[i][i] = i;
        via[i][i] = i;
        for(j = 0; j < nodes; j++)
        {
            if(distanceVector[i][j] != INT_MAX)
            {
            	for(k = 0; k < nodes; k++)
                {
                	if((distanceVector[i][j] + distanceVector[j][k]) < distanceVector[i][k])
                    {
                    	distanceVector[i][k] = distanceVector[i][j] + distanceVector[j][k];
                        via[i][k] = j + 1;
                    }
		}
            }
        }
    }
    if(nodes > 0)
    {
    	cout<<endl<<"\n";
        cout<<"\t\t\tFINAL DISTANCES STORED AT EACH NODE\n\n";
        cout<<"\t\tInformation stored at each node\t\tDistance to reach node\n\n";
        for(i = 0; i < nodes; i++)
        {
            cout<<"\t\t\t\t"<<(i + 1)<<"\t\t\t";
            for(j = 0; j < nodes; j++)
            {
            	if(i != j)
                    cout<<"  "<<distanceVector[i][j];                			
                else
                    cout<<"  "<<0;
            }
            cout<<"\n\n"<< endl<<"\n";
	}
        for(i = 0; i < nodes; i++)
        {
            cout<<"\n\n\t\t\tROUTING TABLE FOR NODE - "<<(i + 1);
            cout<<"\n\n\t\tDestination\t\tCost\t\tNext Hop\n\n";
            for(j = 0; j < nodes; j++)
            {
            	if(i != j)
                    cout<<"\t\t\t"<<(j + 1)<<"\t\t"<<distanceVector[i][j]<<"\t\t"<<via[i][j]<<"\n\n";
            }
            cout<<"\n\n\t\t\t * 0 - denotes direct link.\n";
        }
    }
    getch();
    return 0;
}
