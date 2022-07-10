#include <iostream>
#include "myvector.h"
#include <random>
#include <vector>
#include <cassert>

using std::rand;
using std::cout;
using std::vector;

size_t getRandomIndexFromVector(MyVector<int>& myvector, vector<int>& stdvector)
{
    size_t index = rand() % myvector.size();
    return index;
}

void fillRandom(MyVector<int>& myvector, vector<int>& stdvector)
{
    const int maxValue = 20000;

    for (int i = 0; i < myvector.size(); i++)
    {
        int value = rand() % maxValue;
        myvector[i] = value;
        stdvector[i] = value;
    }
}

void checkAllParams(MyVector<int>& myvector, vector<int>& stdvector)
{
    assert(myvector.size() == stdvector.size());

    cout << "Capacity is currently " << (int) myvector.capacity() << '\n';

    bool allValuesSame = true;
    for (int i = 0; i < myvector.size(); i++)
        if (myvector[i] != stdvector[i] || stdvector[i] != myvector.at(i))
            allValuesSame = false;

    assert(allValuesSame);
}

int main()
{
    const int size = 10000;

    vector<int> std_vector(size);
    MyVector<int> my_vector(size);


    fillRandom(my_vector, std_vector);

    checkAllParams(my_vector, std_vector);

    // erase and pop
    for (int i = 0; i < 6000; i++)
    {
        if (i < 3000)
        {
            auto t = getRandomIndexFromVector(my_vector, std_vector);
            my_vector.erase(t);
            std_vector.erase(std_vector.begin() + t);
        }
        else
        {
            my_vector.pop();
            std_vector.pop_back();
        }
    }

    checkAllParams(my_vector, std_vector);

    const int maxValue = 100000;

    // push
    for (int i = 0; i < 100; i++)
    {
        auto t = rand() % maxValue;

        my_vector.push(t);
        std_vector.push_back(t);
    }

    checkAllParams(my_vector, std_vector);

    // insert
    for (int i = 0; i < 100; i++)
    {
        auto t = rand() % maxValue;
        auto ind = getRandomIndexFromVector(my_vector, std_vector);

        my_vector.insert(ind, t);
        std_vector.insert(std_vector.begin() + ind, t);
    }

    checkAllParams(my_vector, std_vector);

    // prepend
    for (int i = 0; i < 100; i++)
    {
        auto t = rand() % maxValue;

        my_vector.prepend(t);
        std_vector.insert(std_vector.begin(), t);
    }

    checkAllParams(my_vector, std_vector);

    system("pause");
}