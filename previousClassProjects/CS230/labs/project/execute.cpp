//execute.cpp
//Landon Boone
//11/18/22
#include "machine.h"
#include "execute.h"

#include <iostream>
#include <sstream>

using namespace std;

ExecuteOut alu(AluCommands cmd, int64_t left, int64_t right) {
    ExecuteOut ret;
    switch (cmd) {
        case ALU_ADD:
            ret.result = left + right;
        break;
        case ALU_SUB:
            ret.result = left - right;
        break;
        // TODO: Finish the commands here.
        case ALU_MUL:
            ret.result = left * right;
        break;
        case ALU_DIV:
            // div by 0 protection
            if (right == 0) {
                break;
            }
            ret.result = left / right;
        break;
        case ALU_REM:
        // div by 0 protection
            if (right == 0) {
                break;
            }
            ret.result = left % right;
        break;
        case ALU_SLL:
            ret.result = left << right;
        break;
        case ALU_SRL:
            ret.result = left >> right;
        break;
        // without using #include <cmath> for power, uses a loop to find 2^right power to find the right shift's result.
        // no need for div by 0 protection as a 0 exponent would yield a 1.
        case ALU_SRA:
            int64_t twoExponent;
            twoExponent = 1;
            for (int i = 0; i < right; i++) {
                twoExponent *= 2;
            }
            ret.result = left / twoExponent;
        break;
        case ALU_AND:
            ret.result = left & right;
        break;
        case ALU_OR:
            ret.result = left | right;
        break;
        case ALU_XOR:
            ret.result = left ^ right;
        break;

    }
    // Now that we have the result, determine the flags.
    uint8_t sign_left = (left >> 63) & 1;
    uint8_t sign_right = (right >> 63) & 1;
    uint8_t sign_result = (ret.result >> 63) & 1;
    ret.z = !ret.result;
    ret.n = sign_result;
    ret.v = ~sign_left & ~sign_right & sign_result |
             sign_left & sign_right & ~sign_result;
    ret.c = (ret.result > left) || (ret.result > right);
    return ret;
}

void Machine::execute() {
   AluCommands cmd;
   // Most instructions will follow left/right
   // but some won't, so we need these:
   int64_t op_left = mDO.left_val;
   int64_t op_right = mDO.right_val; 
   
   if (mDO.op == BRANCH) {
      // A branch needs to subtract the operands
      cmd = ALU_SUB;
   }
   else if (mDO.op == LOAD || mDO.op == STORE) {
      // For loads and stores, we need to add the
      // offset with the base register.
        op_right = mDO.offset; 
        cmd = ALU_ADD;
   }
   else if (mDO.op == OP) {
      // We can't tell which ALU command to use until
      // we read the funct3 and funct7
      switch (mDO.funct3) {
        case 0b000: // ADD or SUB or MUL, as all 3 fall under funct 3 000
            if (mDO.funct7 == 0) {
                cmd = ALU_ADD;
            }
            else if (mDO.funct7 == 32) {
                cmd = ALU_SUB;
            }
            else if (mDO.funct7 == 1) {
                cmd = ALU_MUL;
            }
            break;

         // TODO: Finish the rest of the OP functions here.
         case 0b100: // DIV or XOR
            if (mDO.funct7 == 1) {
                cmd = ALU_DIV;
            }
            else if (mDO.funct7 == 0){
                cmd = ALU_XOR;
            }
            break;
        case 0b110: // REM or OR
            if (mDO.funct7 == 1) {
                cmd = ALU_REM;
            }
            else if (mDO.funct7 == 0){
                cmd = ALU_OR;
            }
            break;
        case 0b001: // SLL
            if (mDO.funct7 == 0) {
                cmd = ALU_SLL;
            }
            break;
        case 0b101: // SRL or SRA
            if (mDO.funct7 == 0) {
                cmd = ALU_SRL;
            }
            else if (mDO.funct7 == 32) {
                cmd = ALU_SRA;
            }
            break;
        case 0b111: //AND
            if (mDO.funct7 == 0) {
                cmd = ALU_AND;
            }
            break;
      }
   }
   else if (mDO.op == OP_32) {
       op_left = sign_extend(op_left, 31);
       op_right = sign_extend(op_right, 31);
       // TODO: You still need to determine the ALU command
        switch (mDO.funct3) {
        case 0b000: // ADDW or SUBW or MULW
            if (mDO.funct7 == 0) {
                cmd = ALU_ADD;
            }
            else if (mDO.funct7 == 32) {
                cmd = ALU_SUB;
            }
            else if (mDO.funct7 == 1) {
                cmd = ALU_MUL;
            }
            break;
         case 0b100: // DIVW
            if (mDO.funct7 == 1) {
                cmd = ALU_DIV;
            }
            break;
        case 0b110: // REMW
            if (mDO.funct7 == 1) {
                cmd = ALU_REM;
            }
            break;
        case 0b001: // SLLW
            if (mDO.funct7 == 0) {
                cmd = ALU_SLL;
            }
            break;
        case 0b101: // SRLW or SRAW
            if (mDO.funct7 == 0) {
                cmd = ALU_SRL;
            }
            else if (mDO.funct7 == 32) {
                cmd = ALU_SRA;
            }
            break;
      }
   }
   else if (mDO.op == OP_IMM) {
       // TODO: Look and see which ALU op needs to be executed.
        switch (mDO.funct3) {
        case 0b000: // ADDI or Subtraction. uses ADD to subtract a negative immediate since there is no SUBI
            cmd = ALU_ADD;
            break;
         case 0b100: //  XORI
            cmd = ALU_XOR;
            break;
        case 0b110: // ORI
            cmd = ALU_OR;
            break;
        case 0b001: // SLLI
            if (mDO.funct7 == 0) {
                cmd = ALU_SLL;
            }
            break;
        case 0b101: // SRLI or SRAI
            if (mDO.funct7 == 0) {
                cmd = ALU_SRL;
            }
            else if (mDO.funct7 == 32) {
                cmd = ALU_SRA;
            }
            break;
        case 0b111: //ANDI
            cmd = ALU_AND;
            break;
      }
   }
   else if (mDO.op == OP_IMM_32) { 
       op_left = sign_extend(op_left, 31);
       op_right = sign_extend(op_right, 31);
       // This is just like OP_IMM except we truncated
       // the left and right ops.
       //TODO: Still need the ALU op
        switch (mDO.funct3) {
        case 0b000: // ADDIW or Subtraction. uses ADD to subtract a negative immediate since there is no SUBIW
            cmd = ALU_ADD;
            break;
        case 0b001: // SLLIW
            if (mDO.funct7 == 0) {
                cmd = ALU_SLL;
            }
            break;
        case 0b101: // SRLIW or SRAIW
            if (mDO.funct7 == 0) {
                cmd = ALU_SRL;
            }
            else if (mDO.funct7 == 32) {
                cmd = ALU_SRA;
            }
            break;
      }

   }
   else if (mDO.op == JALR) {
       // JALR has an offset and a register value that
       // need to be added together.
       op_right = mDO.offset; 
       cmd = ALU_ADD;
   }
   //sets the left register to the program counter
   else if (mDO.op == JAL) {
        op_left = mPC;
        op_right = mDO.offset; 
        cmd = ALU_ADD;
   }
   else if (mDO.op == LUI) {
        op_left = sign_extend(op_left, 31);
        op_right = sign_extend(op_right, 31);
        cmd = ALU_ADD;
   }
    // sets left register to the program counter and sign extends both registers
   else if (mDO.op == AUIPC) {
        op_left = mPC;
        op_left = sign_extend(op_left, 31);
        op_right = sign_extend(op_right, 31);
        cmd = ALU_ADD;    
   }
    //ecall, sets left register to the program counter
    else if (mDO.op == SYSTEM) {
        op_left = mPC;
        cmd = ALU_ADD;
    }
   mEO = alu(cmd, op_left, op_right);
}

const ExecuteOut &Machine::execute_out() const {
    return mEO;
}

ostream &operator<<(ostream &out, const ExecuteOut &eo) {
    ostringstream sout;
    sout << "Result: " << eo.result << " [NZCV]: " 
            << (uint32_t)eo.n 
            << (uint32_t)eo.z 
            << (uint32_t)eo.c
            << (uint32_t)eo.v;
    return out << sout.str();
}
