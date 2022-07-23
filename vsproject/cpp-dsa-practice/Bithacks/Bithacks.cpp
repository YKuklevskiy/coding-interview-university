#include <iostream>

#include "Bitvector.h"
#include <string>

using std::cout;
using std::string;
using std::to_string;

string bitvectorToString(Bitvector bitvector)
{
    string temp;
    int bytes = bitvector.get_length() / 8;
    for (int i = 0; i < bytes; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            temp += to_string((int)bitvector.get_bit(i*8 + j));
        }
        temp += " ";
    }
    temp.pop_back();
    std::reverse(temp.begin(), temp.end());
    temp += "\n";
    return temp;
}

#define check cout<<bitvectorToString(bv)

int main()
{
    Bitvector bv; 
    check; // 00000000 00000000 00000000 00000000

    cout << bv.count_bits() << "\n";

    bv.set_bit(0);
    bv.set_bit(4);
    bv.set_bit(8);

    check; // 00000000 00000000 00000001 00010001

    cout << bv.count_bits() << "\n";

    bv.clear_bit(0);
    bv.clear_bit(5);
    bv.clear_bit(4);

    check; // 00000000 00000000 00000001 00000000

    cout << bv.count_bits() << "\n";

    bv.modify_bit(0, true);
    bv.modify_bit(4, true);
    bv.modify_bit(9, true);

    check; // 00000000 00000000 00000011 00010001

    cout << bv.count_bits() << "\n";

    bv.modify_bit(0, false);
    bv.modify_bit(1, true);
    bv.modify_bit(4, false);
    bv.modify_bit(8, false);

    check; // 00000000 00000000 00000010 00000010

    cout << bv.count_bits() << "\n";

    bv.flip_bit(0);
    bv.flip_bit(4);
    bv.flip_bit(8);
    bv.flip_bit(12);

    check; // 00000000 00000000 00010011 00010011

    cout << bv.count_bits() << "\n";

    bv.flip_bit(0);
    bv.flip_bit(4);
    bv.flip_bit(8);
    bv.flip_bit(12);

    check; // 00000000 00000000 00000010 00000010

    cout << bv.count_bits() << "\n";

    // checkdiffcount

    bv.flip_bit(0);
    bv.flip_bit(4);
    bv.flip_bit(8);
    bv.flip_bit(12);
    // 00000000 00000000 00010011 00010011

    Bitvector bv2;

    bv2.flip_bit(0);
    bv2.flip_bit(4);
    bv2.flip_bit(8);
    bv2.flip_bit(12);
    bv2.flip_bit(24);
    // 00000001 00000000 00010001 00010001

    cout << "\n" << bv.count_different_bits(bv2) << "\n";
    cout << bv2.count_different_bits(bv) << "\n";
}