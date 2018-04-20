//
//  CentralProcessingUnit.cpp
//  RoodBoi
//
//  Created by Sam Reha on 8/13/17.
//  Copyright © 2017 Sam Reha. All rights reserved.
//

#include "CentralProcessingUnit.h"

// private
// LD (nn), SP
// Writes the value pointed to by the stack pointer to the given address
void CentralProcessingUnit::loadWithStackPointer() {
    // Load location (nn) with register SP.
    uint16_t destination = (MemoryManager::instance()->readData(programCounter) << 8)
    + MemoryManager::instance()->readData(programCounter + 1);
    
    MemoryManager::instance()->writeData(destination, MemoryManager::instance()->readData(stackPointer));
    
    // Push program counter past 16 bit destination address
    programCounter += 2;
}

// LD R, nn
// Load designated register pair with given 16 bit value
void CentralProcessingUnit::loadToRegister(uint8_t registerCode) {
    // Decode register
    switch (registerCode) {
        case 0b00: // BC
            registerBC = (MemoryManager::instance()->readData(programCounter) << 8)
                + MemoryManager::instance()->readData(programCounter + 1);
            break;
        case 0b01: // DE
            registerDE = (MemoryManager::instance()->readData(programCounter) << 8)
                + MemoryManager::instance()->readData(programCounter + 1);
            break;
        case 0b10: // HL
            registerHL = (MemoryManager::instance()->readData(programCounter) << 8)
                + MemoryManager::instance()->readData(programCounter + 1);
            break;
        case 0b11: // SP
            stackPointer = (MemoryManager::instance()->readData(programCounter) << 8)
                + MemoryManager::instance()->readData(programCounter + 1);
            break;
    }
    
    // Push program counter past 16 bit value
    programCounter += 2;
}

// ADD HL, R
// Add given register pair to HL
void CentralProcessingUnit::addToHL(uint8_t registerCode) {
    // Decode register
    switch (registerCode) {
        case 0b00: // BC
            registerHL += registerBC;
            break;
        case 0b01: // DE
            registerHL += registerDE;
            break;
        case 0b10: // HL
            registerHL += registerHL;
            break;
        case 0b11: // SP
            registerHL += stackPointer;
            break;
    }
}

// public
void CentralProcessingUnit::initialize() {
    cpuClock.restart();
    programCounter = 0x150;
}

void CentralProcessingUnit::tick() {
    if (cpuClock.getElapsedTime().asMicroseconds() >= 1.0 / clockSpeed) {
        // Get an instruction
        uint8_t instruction = MemoryManager::instance()->readData(programCounter);
        
        // Advance PC
        programCounter++;
        
        // Decode and execute
        if (instruction == 0b00000000) {
            // NOP
        } else if (instruction == 0b00001000){
            // LD (nn), SP
            loadWithStackPointer();
        } else if ((instruction & 0b11001111) == 0b00000001) {
            // LD R, nn
            loadToRegister((instruction & 0b00110000) >> 4);
        } else if ((instruction & 0b11001111) == 0b00001001) {
            // ADD HL, R
            addToHL((instruction & 0b00110000) >> 4);
        } else if (false) {
            // LD (R), A | LD A, (R)
        } else if (false) {
            // INC R | DEC R
        } else if (false) {
            // INC D | DEC D
        } else if (false) {
            // LD D, N
        } else if (false) {
            // RdCA
        } else if (false) {
            // RdA
        } else if (false) {
            // STOP
        } else if (false) {
            // JR N
        } else if (false) {
            // JR F, N
        } else if (false) {
            // LDI (HL), A | LDI A, (HL)
        } else if (false) {
            // LDD (HL), A | LDD A, (HL)
        } else if (false) {
            // DAA
        } else if (false) {
            // CPL
        } else if (false) {
            // SCF
        } else if (false) {
            // CCF
        } else if (false) {
            // LD D, D
        } else if (false) {
            // HALT
        } else if (false) {
            // ALU A, D
        } else if (false) {
            // ALU A, N
        } else if (false) {
            // POP R
        } else if (false) {
            // PUSH R
        } else if (false) {
            // RST N
        } else if (false) {
            // RET F
        } else if (false) {
            // RET
        } else if (false) {
            // RETI
        } else if (false) {
            // JP F,N
        } else if (false) {
            // JP N
        } else if (false) {
            // CALL F,N
        } else if (false) {
            // CALL N
        } else if (false) {
            // ADD SP,N
        } else if (false) {
            // LD HL, SP + N
        } else if (false) {
            // LD (FF00 + N), A
        } else if (false) {
            // LD A, (FF00 + N)
        } else if (false) {
            // LD (C), A
        } else if (false) {
            // LD A, (C)
        } else if (false) {
            // LD (N), A
        } else if (false) {
            // LD A, (N)
        } else if (false) {
            // JP HL
        } else if (false) {
            // LD SP, HL
        } else if (false) {
            // DI
        } else if (false) {
            // EI
        } else if (false) {
            // RdC D
        } else if (false) {
            // Rd D
        } else if (false) {
            // SdA D
        } else if (false) {
            // SWAP D
        } else if (false) {
            // SRL D
        } else if (false) {
            // BIT N,D
        } else if (false) {
            // RES N,D
        } else if (false) {
            // SET N,D
        }
        
        // Make sure to reset the clock so that we tick at a steady rate
        cpuClock.restart();
    }
}

uint16_t CentralProcessingUnit::getRegisterValue(CPU_REGISTER reg) {
    switch (reg) {
        case AF:
            return registerAF & 0xFFF0;
        case BC:
            return registerBC;
        case DE:
            return registerDE;
        case HL:
            return registerHL;
        case PC:
            return programCounter;
        case SP:
            return stackPointer;
        default:
            return 0;
    }
}
