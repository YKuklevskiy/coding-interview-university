#include <iostream>
#include "LinkedList.h"
#include <cassert>
#include <vector>
#include <random>

const size_t LIST_SIZE = 10000;

void log(std::string msg)
{
    std::cout << "\n" << msg << "\n";
}

void log()
{
    log("SUCCESS");
}

template<typename T>
class LinkedList_Tester
{
public:
    static void checkReverse(LinkedList<int>* list)
    {
        log("Checking reverse()...");

        std::vector<int> value_holder(LIST_SIZE);

        auto t = list->_head;
        int i = 0;
        while (t != NULL)
        {
            value_holder[i] = t->_value;
            t = t->_next;
            i++;
        }

        list->reverse();

        t = list->_head;

        bool check = true;

        // check values in vector in reverse
        for (int i = value_holder.size() - 1; i >= 0; i--)
        {
            if (t->_value != value_holder[i])
            {
                check = false;
                std::cout << "\n\n\n\n" << i << "\n\n\n\n";
                break;
            }
            t = t->_next;
        }

        assert(check);

        log();

    }

    static void checkAllParams(LinkedList<int>* list, std::vector<int> vector)
    {
        log("Checking parameters...");

        assert(list->size() == vector.size());

        bool allValuesSame = true;

        auto t = list->_head;
        for (int i = 0; i < vector.size(); i++)
        {
            if (t->_value != vector[i])
                allValuesSame = false;

            t = t->_next;
        }

        assert(allValuesSame);

        log();
    }
};

const int MAXVALUE = 50000;

LinkedList<int>* generateList(LinkedList<int>* list, std::vector<int>& vector)
{
    list = new LinkedList<int>();

    for (int i = 0; i < LIST_SIZE; i++)
    {
        auto val = rand() % 50000;
        list->push_back(val);
        vector[i] = val;
    }

    return list;
}

bool checkRandomElement(LinkedList<int>* mylist, std::vector<int>& stdvector)
{
    size_t index = rand() % mylist->size();
    return (*mylist)[index] == stdvector[index] && mylist->value_at(index) == stdvector[index];
}

int main()
{
    log("Checking reverse()...");

    LinkedList<int>* mylist = NULL;
    std::vector<int> vector(LIST_SIZE);

    mylist = generateList(mylist, vector);

    LinkedList_Tester<int>::checkAllParams(mylist, vector);

    LinkedList_Tester<int>::checkReverse(mylist);

    delete mylist; mylist = NULL;

    mylist = generateList(mylist, vector);

    log("Checking random accessed elements...");

    bool check = true;

    for(int i = 0; i < 1000; i++)
        if (!checkRandomElement(mylist, vector))
        {
            check = false;
            break;
        }

    assert(check);

    log();

    log("Checking insertions.");

    for (int i = 0; i < 300; i++)
    {
        auto val = rand() % 10000;

        mylist->push_front(val);
        vector.insert(vector.begin(), val);
    }

    for (int i = 0; i < 100; i++)
    {
        auto val = rand() % 10000;
        size_t ind = rand() % mylist->size();

        mylist->insert(ind, val);
        vector.insert(vector.begin() + ind, val);
    }

    LinkedList_Tester<int>::checkAllParams(mylist, vector);

    log("Checking deletion.");

    for (int i = 0; i < 500; i++)
    {
        size_t ind = rand() % mylist->size();

        mylist->pop_front();
        vector.erase(vector.begin());
    }

    LinkedList_Tester<int>::checkAllParams(mylist, vector);

    for (int i = 0; i < 100; i++)
    {
        size_t ind = rand() % mylist->size();

        mylist->erase(ind);
        vector.erase(vector.begin() + ind);
    }

    LinkedList_Tester<int>::checkAllParams(mylist, vector);

    log("Checking remove_value()...");

    for (int i = 0; i < 100; i++)
    {
        size_t ind = rand() % mylist->size();

        int value = vector[ind];
        auto it = std::find(vector.begin(), vector.end(), value);

        mylist->remove_value(value);
        vector.erase(it);
    }

    LinkedList_Tester<int>::checkAllParams(mylist, vector);

    system("pause");
}