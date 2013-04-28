#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#define wSize 5
#define length 140
time_t now, later;
using namespace std;
void sleep(int delay)
{
    now = time(NULL);
    later = now + delay;
    while(now <= later)
        now = time(NULL);
}
void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void showDiagram(int start = 15, int end = 20, int total = 0)
{
    int i, j, x, y, itr = 11;
    i = start * 7;
    x = i;
    j = (end + 1) * 7;
    y = j;
    gotoxy(8, 47);
    cout<<"REPRESENTATION: ";
    gotoxy(i, 49);
    cout<<"+";
    i++;
    for(; i < j; i++)
    {
        gotoxy(i, 49);
        cout<<"-";
        gotoxy(i, 55);
        cout<<"-";
    }
    gotoxy(i, 49);
    cout<<"+";
    gotoxy(3, 50);
    cout<<"+";
    for(i = -10; i <= length; i++)
        cout<<"-";
    gotoxy(155, 50);
    cout<<"+";
    gotoxy(3, 51);
    cout<<"|";
    for(i = 1; i <= total; i++)
    {
        gotoxy(itr, 52);
        cout<<i;
        itr+= 7;
    }
    gotoxy(3, 52);
    cout<<"|";
    gotoxy(3, 53);
    cout<<"|";
    gotoxy(3, 54);
    cout<<"+";
    for(i = -10; i <= length; i++)
        cout<<"-";
    gotoxy(155, 51);
    cout<<"|";
    gotoxy(155, 52);
    cout<<"|";
    gotoxy(155, 53);
    cout<<"|";
    gotoxy(155, 54);
    cout<<"+";
    gotoxy(x, 50);
    cout<<"|";
    gotoxy(x, 51);
    cout<<"|";
    gotoxy(x, 52);
    cout<<"|";
    gotoxy(x, 53);
    cout<<"|";
    gotoxy(x, 54);
    cout<<"|";
    gotoxy(x, 55);
    cout<<"+";
    gotoxy(y, 50);
    cout<<"|";
    gotoxy(y, 51);
    cout<<"|";
    gotoxy(y, 52);
    cout<<"|";
    gotoxy(y, 53);
    cout<<"|";
    if(start > 1)
    {
        gotoxy(1, 57);
        cout<<"<- Sent and";
        gotoxy(1, 59);
        cout<<"ACK";
        gotoxy(1, 61);
        cout<<"received.";
    }
    if(end != total)
    {
        gotoxy(y, 57);
        cout<<"Not ready";
        gotoxy(y, 59);
        cout<<"to be sent ->";
    }
    gotoxy(y, 54);
    cout<<"|";
    gotoxy(y, 55);
    cout<<"+";
    getch();
}
int printFrames(int start, int end, int total)
{
    int i, lastAck;
    cout<<"\n\tSOURCE: ";
    cout<<start<<"==="<<end<<endl;
    for(i = start; i <= end; i++)
    {
        cout<<"\n\n\t\tTransmitting: Frame - "<<i<<" ...";
        sleep(1);
        cout<<"\n\n\t\tDone.\n";
    }
    cout<<"\n\n\n\tDESTINATION: ";
    cout<<"\n\n\t\tLast acknowledgement received: ";
    cin>>lastAck;
    cout<<"\n\n\t\tTransmitting:  Acknowledgement - "<<lastAck<<" ...";
    sleep(1);
    cout<<"\n\n\t\tDone.\n";
    if((lastAck < start) || (lastAck > end))
    {
        cout<<"\n\n\t\tInvalid acknowledgement...!!!";
        cout<<"\n\n\n\t\tRe - transmitting...";
        sleep(2);
        cout<<endl<<endl;
        system("cls");
        printFrames(start, end, total);
    }
    else if(lastAck < end)
    {
        showDiagram(start, lastAck, total);
        system("cls");
        printFrames((lastAck + 1), ((lastAck + wSize) <= total ? (lastAck + wSize) : total), total);
    }
    else if(lastAck == end)
    {
        showDiagram(start, end, total);
        if(!(end == total))
        {
            system("cls");
            printFrames((end + 1), (end + (((end + wSize) <= total) ? wSize : (total - lastAck))) , total);
        }
        else
        {
            cout<<"\n\n\n\n\n\n\tSTATUS: ";
            cout<<"\n\n\t\tTransmission complete...!!!";
            getch();
        }
    }
    cout<<endl<<endl;
    return 1;
}
int main()
{
    int total, start, end;
    cout<<"\n\n\n\t\t\t\t\t\t\t\tSLIDING WINDOW PROTOCOL";
    cout<<"\n\n\n\tNo. of frames to be transmitted: ";
    cin>>total;
    start = 1;
    end = (total < wSize) ? total : wSize;
    printFrames(start, end, total);
    return 0;
}
