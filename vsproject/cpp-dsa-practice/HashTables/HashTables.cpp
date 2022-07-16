#include <iostream>
#include "LinearHashTable.h"
#include <fstream>

const size_t TABLE_SIZE = 10000;

// Forgive me for clumpy and unreadable test code
// How does test work:
// Fill up table with words from the text (from textsample.txt), with keys being indices of last word characters in file
// Then read file again and search for elements with keys equal to indices of last word characters
// If we print those words from the initial file separated by \n, and print those words from search requests with table, they should be equal
// and notExistCount should also be zero
int main()
{
    const bool showFirstTest = true;
    const bool showSecondTest = true;

    //
    //      integral key test
    //
    LinearHashTable<size_t, std::string> my_table_integral(TABLE_SIZE);

    std::ifstream fin("textsample.txt");
    char c;
    std::string temp = "";
    std::string text1 = "";
    size_t count = 0;
    // inserting words
    while (fin.get(c))
    {
        text1 += c;
        if (c == ' ' || c == '\n')
        {
            text1 += "\n";
            my_table_integral.insert(count, temp);
            temp = "";
        }
        else
        {
            temp += c;
        }
        count++;
    }
    my_table_integral.insert(count, temp);

    fin.close();

    fin.open("textsample.txt");
    temp = "";
    count = 0;
    int notExistCount = 0;
    std::string text2 = "";
    // searching for words
    while (fin.get(c))
    {
        if (c == ' ' || c == '\n')
        {
            if (my_table_integral.exists(count))
                text2 += my_table_integral.search(count) + "\n";
            else
                notExistCount++;
        }
        count++;
    }
    text2 += my_table_integral.search(count) + "\n";

    if (showFirstTest)
    {
        std::cout << notExistCount << "\n\n\n";

        std::cout << text1;

        std::cout << "\n\n\n";
        for (int i = 0; i < 30; i++)
            std::cout << "-";
        std::cout << "\n\n\n";

        std::cout << text2 << "\n\n\n";

        std::cout << "\n\n\n";
        for (int i = 0; i < 30; i++)
            std::cout << "-";
        std::cout << "\n\n\n";
    }

    fin.close();

    //
    //      iterable key test
    //

    LinearHashTable<std::string, std::string> my_table_string(TABLE_SIZE);

    fin.open("textsample.txt");
    temp = "";
    text1 = "";
    count = 0;
    // inserting words
    while (fin.get(c))
    {
        if (c == ' ' || c == '\n')
        {
            text1 += "\n";
            my_table_string.insert(temp, temp);
            temp = "";
        }
        else
        {
            text1 += c;
            temp += c;
        }
        count++;
    }
    my_table_string.insert(temp, temp);

    fin.close();

    fin.open("textsample.txt");
    temp = "";
    count = 0;
    notExistCount = 0;
    text2 = "";
    // searching for words
    while (fin.get(c))
    {
        if (c == ' ' || c == '\n')
        {
            if (my_table_string.exists(temp))
                text2 += my_table_string.search(temp) + "\n";
            else
                notExistCount++;

            temp = "";
        }
        else
            temp += c;
        count++;
    }
    text2 += my_table_string.search(temp) + "\n";

    if (showSecondTest)
    {
        std::cout << notExistCount << "\n\n\n";

        std::cout << text1;

        std::cout << "\n\n\n";
        for (int i = 0; i < 30; i++)
            std::cout << "-";
        std::cout << "\n\n\n";

        std::cout << text2 << "\n\n\n";
    }

    system("pause");
}