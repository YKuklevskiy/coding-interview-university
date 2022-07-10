#include <iostream>
#include "LinkedList.h"

#include "ArrayQueue.h"
#include "ListQueue.h"
#include <queue>

const size_t QUEUE_SIZE = 10000;

void log(std::string msg)
{
    std::cout << "\n" << msg << "\n";
}

void log()
{
    log("SUCCESS");
}

void generateQueue(ArrayQueue<int>& myarrqueue, ListQueue<int>& mylistqueue, std::queue<int>& stdqueue)
{
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        auto val = rand() % 50000;
        myarrqueue.enqueue(val);
        mylistqueue.enqueue(val);
        stdqueue.push(val);
    }
}

void checkAllParams(ArrayQueue<int>& myarrqueue, ListQueue<int>& mylistqueue, std::queue<int>& stdqueue)
{
    log("Checking params...");

    assert(myarrqueue.size() == mylistqueue.size() && myarrqueue.size() == stdqueue.size());

    bool check = true;
    while(!myarrqueue.empty())
    {
        int arr = myarrqueue.dequeue();
        int ls = mylistqueue.dequeue();
        int stdq = stdqueue.front();

        stdqueue.pop();

        if (arr != ls || arr != stdq)
        {
            check = false;
            break;
        }
    }

    assert(check);

    log();
}

int main()
{
    ArrayQueue<int> myarrqueue(QUEUE_SIZE + 1); 
    ListQueue<int> mylistqueue; 
    std::queue<int> stdqueue;

    generateQueue(myarrqueue, mylistqueue, stdqueue);

    checkAllParams(myarrqueue, mylistqueue, stdqueue);

    generateQueue(myarrqueue, mylistqueue, stdqueue);

    bool check = false;

    log("Checking overflow on ArrayQueue");

    //myarrqueue.dequeue(); // if this line is commented, the exception is thrown, else its not
    myarrqueue.enqueue(42);

    log();

    system("pause");
}