// fetch.cpp
// fetches the binary instruction from memory found in main and converts it to hex
// Landon Boone - CS 230
// 10-21-22
#include <iomanip>
#include <iostream>
#include <sstream>
#include "machine.h"
#include "fetch.h"

using namespace std;

void Machine::fetch()
{
    // TODO: Write fetch() here.
    mFO.instruction = memory_read<int>(Machine::mMemory,Machine::get_pc());
}

const FetchOut &Machine::fetch_out() const
{
    return mFO;
}

std::ostream &operator<<(ostream &out, const FetchOut &fo)
{
    // The code below allows us to cout a FetchOut structure.
    // We can use this to debug our code.
    // FetchOut fo = { 0xdeadbeef };
    // cout << fo << '\n';

    // We use a string stream to avoid changing the ostream by using
    // manipulators.
    std::ostringstream sout;
    sout << "0x" << hex << setfill('0') << right << setw(8) << fo.instruction;
    return out << sout.str();
}
