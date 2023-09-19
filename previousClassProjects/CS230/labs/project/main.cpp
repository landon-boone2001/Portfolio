// main.cpp
// main.cpp is the driver function for the machine project. In the fetch stage, main attempts to read in a binary file entered on the command line.
// if the file cannot be read, or no file is provided, an error is thrown. if the file can be read, the program will fine the size of the file
// and create a character array with a size equal to the size of the file found. the program will then read the file into the character array.
// the program will then create a Machine object, writing the data from the character array into the new object, then will fetch the instructions
// and convert them to hex
// Landon Boone - CS 230
// 10-21-22

#include <iostream>
#include <fstream>
#include "machine.h"
using namespace std;

int main(int argc, char *argv[])
{
    char *mem    = nullptr;
    int64_t size = 0;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <object file>\n";
        return -1;
    }
    // TODO: write the code that error checks and reads the file
    // given by the command line argument.
    // Used the code provided by Dr. Marz correlating to reading in a binary file in Oct 18 class.
    ifstream fin;
    fin.open(argv[1],ios::binary);
    // error checks to see if fin opens the file.
    if (!fin) {
        perror(argv[1]);
        return -1;
    }
    fin.seekg(0, ios::end);
    size = fin.tellg();
    fin.seekg(0, ios::beg);
    mem = new char[size];
    fin.read(mem, size);
    fin.close();

    Machine mach(mem, MEM_SIZE);
	mach.set_pc(0);
    while (mach.get_pc() < size) {
        mach.fetch();
        cout << mach.fetch_out() << '\n';
        mach.decode();
        cout << mach.decode_out() << '\n';
        mach.execute();
        cout << mach.execute_out() << '\n';
        mach.memory();
        cout << mach.memory_out() << '\n';
        mach.writeback();
        mach.set_pc(mach.get_pc() + 4);
        // TODO: For each stage, you will add to this
        // to see the intermediate results.
    }

    // TODO: Free any memory associated with mem
    delete[] mem;
    return 0;
}
