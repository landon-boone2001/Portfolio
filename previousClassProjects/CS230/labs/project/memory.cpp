//memory.cpp
//Landon Boone
//11/28/22
#include "machine.h"

#include "memory.h"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

void Machine::memory() {
    if (mDO.op == STORE) {
        switch (mDO.funct3) {
            case 0b000: // SB
                memory_write<uint8_t>(mMemory, mEO.result, mDO.right_val);
            break;
            // TODO: Finish here SH, SW, and SD
            /*set Store halfword, word as uint32_t and double word to uint64_t*/
            case 0b001: // SH
                memory_write<uint32_t>(mMemory, mEO.result, mDO.right_val);
            break;
            case 0b010: // SW
                memory_write<uint32_t>(mMemory, mEO.result, mDO.right_val);
            break;
            case 0b011: // SD
                memory_write<uint64_t>(mMemory, mEO.result, mDO.right_val);
            break;
            default:
                cerr << "[MEMORY: STORE]: Invalid funct3: " << mDO.funct3 << '\n';
            break;
        }
    }
    else if (mDO.op == LOAD) {
        switch (mDO.funct3) {
            case 0b000: // LB
                mMO.value = memory_read<int8_t>(mMemory, mEO.result);
            break;
            // TODO: Finish here LBU, LH, LHU, LW, LWU, and LD
            // set Store halfword, word as int32_t and double word to int64_t
            // Any unsigned instructions are set to their unsigned size counterpart
             case 0b100: // LBU
                mMO.value = memory_read<uint8_t>(mMemory, mEO.result);
            break;
            case 0b001: // LH
                mMO.value = memory_read<int32_t>(mMemory, mEO.result);
            break;
            case 0b101: // LHU
                mMO.value = memory_read<uint32_t>(mMemory, mEO.result);
            break;
            case 0b010: // LW
                mMO.value = memory_read<int32_t>(mMemory, mEO.result);
            break;
            case 0b110: // LWU
                mMO.value = memory_read<uint32_t>(mMemory, mEO.result);
            break;
            case 0b011: // LD
                mMO.value = memory_read<int64_t>(mMemory, mEO.result);
            break;
            default:
                cerr << "[MEMORY: LOAD]: Invalid funct3: " << mDO.funct3 << '\n';
            break;
        }
    }
    else {
        // If this is not a LOAD or STORE, then this stage just copies
        // the ALU result.
        mMO.value = mEO.result;
    }
}


const MemoryOut &Machine::memory_out() const {
    return mMO;
}

ostream &operator<<(ostream &out, const MemoryOut &mo) {
    ostringstream sout;
    sout << "0x" << hex << right << setfill('0') << setw(16) << mo.value;
    return out << sout.str();
}
