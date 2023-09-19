#include "machine.h"

void Machine::writeback() {
    // TODO: Finish writeback stage here
    // Recall the writeback stage needs to determine:
    // 1. which register (if any) to write to.
    // 2. which PC to set (look for BRANCH, JALR, and JAL)
    // 3. execute any SYSTEM instruction
    
    set_xreg(mDO.rd, mMO.value);
    // if a branch is taken, sets the program counter 
    // to the mmOValue - 4 because the program will
    // automatically increase +4 after the writeup stage
    // in main. This ensures we stick at the newly jumped instruction.
    if (mDO.op == BRANCH) {
        switch (mDO.funct3) { 
            case 0b000 : //BEQ  
                if (mEO.z == 1 && mEO.n == 0) {
                    set_pc(mMO.value-4);
                }
                break;
            case 0b001 : //BNE
                if (mEO.z == 0) {
                    set_pc(mMO.value-4);
                }
                break;
            case 0b100 : //BLT
                if (mEO.n == 1) {
                    set_pc(mMO.value-4);
                }
                break;
            case 0b101 : //BGE
                if (mEO.n == 0 || mEO.z == 1) {
                    set_pc(mMO.value-4);
                }
                break;
        }
    }
    if (mDO.op == JAL) {
        set_pc(mMO.value-4);
    }
    if (mDO.op == JALR) {
        set_xreg(mDO.rd, get_pc()+4);
        set_pc(mMO.value-4);
    }
    //ECALL
    /*Determines if the program will exit with code 0, write a char to a0, or print a char*/
    if (mDO.op == SYSTEM) {
        if (get_xreg(17) == 0) {
            exit(0);
        }
        else if (get_xreg(17) == 1) {
            set_xreg(10, 0); // clears xregister
            set_xreg(10, getchar());
        }
        else if (get_xreg(17) == 2) {
            putchar((char)get_xreg(10));
        }
    }
}

