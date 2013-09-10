#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#define maxBufferSize 5
typedef int bufferElement;
bufferElement buffer[maxBufferSize];
using namespace std;
int main(int, char **);
void *producer(void *);
void *consumer(void *);
void *writer(void *);
void *reader(void *);
int insertIndex = 0, removeIndex = 0, totalProducers = 0, totalConsumers = 0, totalProducerItems = 0, totalConsumerItems = 0, boundedBufferSleepTime = 0;
sem_t full, empty, boundedBufferMutex;
int totalWriters, totalReaders, totalWrites, totalReads, readerWriterSleepTime, count = 0;
sem_t readerWriterMutex, dataAccess;
ifstream in;
int main(int argc, char *argv[])
{
    int i, j, choice;
    choice = atoi(argv[1]);
    if(choice == 1)
    {
        sem_init(&full, 0, 0);
        sem_init(&empty, 0, maxBufferSize);
        sem_init(&boundedBufferMutex, 0, 1);
        ::totalProducers = atoi(argv[2]);
        ::totalConsumers = atoi(argv[3]);
        ::totalProducerItems = atoi(argv[4]);
        ::totalConsumerItems = atoi(argv[5]);
        ::boundedBufferSleepTime = atoi(argv[6]);
        cout<<"\n################################################";
        cout<<"\nProblem: Bounded - Buffer / Producer - Consumer";
        cout<<"\nBuffer size: "<<maxBufferSize;
        cout<<"\nProducers: "<<totalProducers;
        cout<<"\nConsumers: "<<totalConsumers;
        cout<<"\nItems / Producer: "<<totalProducerItems;
        cout<<"\nItems / Consumer: "<<totalConsumerItems;
        cout<<"\nSleep time (ms): "<<boundedBufferSleepTime;
        cout<<"\n################################################";
        for(i = 1; i <= totalProducers; i++)
        {
            pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            bool producerResult = pthread_create(&tid, &attr, producer, (void *)((long(i))));
            if(producerResult == true)
                cout<<"\nError creating producer thread...!!!";
            sleep(boundedBufferSleepTime);
        }
        for(j = 1; j <= totalConsumers; j++)
        {
            pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            bool consumerResult = pthread_create(&tid, &attr, consumer, (void *)((long)(j)));
            if(consumerResult == true)
                cout<<"\nError creating consumer thread...!!!";
            sleep(boundedBufferSleepTime);
        }
    }
    else if(choice == 2)
    {
        in.open("07testFile.txt", ios::in);
        sem_init(&readerWriterMutex, 0, 1);
        sem_init(&dataAccess, 0, 1);
        ::totalWriters = atoi(argv[2]);
        ::totalReaders = atoi(argv[3]);
        ::totalWrites = atoi(argv[4]);
        ::totalReads = atoi(argv[5]);
        ::readerWriterSleepTime = atoi(argv[6]);
        cout<<"\n############################";
        cout<<"\nProblem: Readers - Writers";
        cout<<"\nWriters: "<<totalWriters;
        cout<<"\nReaders: "<<totalReaders;
        cout<<"\nWrites / Thread: "<<totalWrites;
        cout<<"\nReads / Thread: "<<totalReads;
        cout<<"\nSleep time (ms): "<<readerWriterSleepTime;
        cout<<"\n############################";
        for(i = 1; i <= totalWriters; i++)
        {
            pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            bool writerResult = pthread_create(&tid, &attr, writer, (void *)((long(i))));
            if(writerResult == true)
                cout<<"\nError creating writer thread...!!!";
            sleep(readerWriterSleepTime);
        }
        for(j = 1; j <= totalReaders; j++)
        {
           pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            bool readerResult = pthread_create(&tid, &attr, reader, (void *)((long(j))));
            if(readerResult == true)
                cout<<"\nError creating reader thread...!!!";
            sleep(readerWriterSleepTime);
        }
        in.close();
    }
    else
    {
        cout<<"\nInvalid input...!!!";
        exit(0);
    }
    pthread_exit(NULL);
    return 0;
}
int rdtsc()
{
    __asm__ __volatile__("rdtsc");
}
void *producer(void *producerThreadID)
{
    long producerID = (long)producerThreadID;
    bufferElement bufferID;
    int randomID, producerItr = 1;
    while(producerItr <= totalProducerItems)
    {
        srand(rdtsc());
        randomID = rand() % (rand () % 100);
        sem_wait(&empty);
        sem_wait(&boundedBufferMutex);
        buffer[insertIndex++] = randomID;
        insertIndex = insertIndex % maxBufferSize;
        cout<<"\nBuffer produced by - "<<producerID<<" , contains: "<<randomID;
        sem_post(&boundedBufferMutex);
        sem_post(&full);
        producerItr++;
    }
}
void *consumer(void *consumerThreadID)
{
    long consumerID = (long)consumerThreadID;
    bufferElement bufferID;
    int randomID, consumerItr = 1;
    while(consumerItr <= totalConsumerItems)
    {
        sem_wait(&full);
        sem_wait(&boundedBufferMutex);
        bufferID = buffer[removeIndex];
        buffer[removeIndex++] = -1;
        removeIndex = removeIndex % maxBufferSize;
        cout<<"\n\t\t\t\t\tBuffer consumed by - "<<consumerID<<" , contains: "<<bufferID;
        sem_post(&boundedBufferMutex);
        sem_post(&empty);
        consumerItr++;
    }
}
void *writer(void *writerThreadID)
{
    long writerID = (long)writerThreadID;
    int writeItr = 1, writeData;
    ofstream out;
    out.open("07testFile.txt", ios::app);
    if(!out)
    {
        cout<<"\nError opening file...!!!";
        exit(0);
    }
    while(writeItr <= totalWrites)
    {
        sem_wait(&dataAccess);
        sem_post(&dataAccess);
        writeItr++;
        srand(rdtsc());
        writeData = rand() % 100;
        out<<writeData<<endl;
        cout<<"\nData written to file by "<<writerID<<": "<<writeData;
    }
    out.close();
}
void *reader(void *readerThreadID)
{
    long readerID = (long)readerThreadID;
    int readData, readItr = 1;
    if(!in)
    {
        cout<<"\nError opening file...!!!";
        exit(0);
    }
    while(readItr <= totalReads)
    {
        sem_wait(&readerWriterMutex);
        count++;
        if(count == 1)
            sem_wait(&dataAccess);
        sem_post(&readerWriterMutex);
        if(!in.eof())
        {
            in>>readData;
            cout<<"\n\t\t\t\tData read from file by "<<readerID<<" : "<<readData;
        }
        sem_wait(&readerWriterMutex);
        count++;
        if(count == 0)
            sem_post(&dataAccess);
        sem_post(&readerWriterMutex);
        readItr++;
    }
}
