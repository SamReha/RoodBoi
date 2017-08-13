//
//  MemoryManager.h
//  RoodBoi
//
//  Created by Sam Reha on 8/9/17.
//  Copyright © 2017 Sam Reha. All rights reserved.
//

#ifndef MemoryManager_h
#define MemoryManager_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "math.h"

#include "FixedWidthTypes.h"
#include "ResourcePath.hpp"

class MemoryManager {
private:
    // Buffers for switchable memory banks
    uint8_t additionalCharDataBank[0x2000];
    
    uint8_t  workingRAMBankOne  [0x1000];
    uint8_t  workingRAMBankTwo  [0x1000];
    uint8_t  workingRAMBankThree[0x1000];
    uint8_t  workingRAMBankFour [0x1000];
    uint8_t  workingRAMBankFive [0x1000];
    uint8_t  workingRAMBankSix  [0x1000];
    uint8_t  workingRAMBankSeven[0x1000];
    uint8_t* workingRAMBanks[7] = {
        workingRAMBankOne,
        workingRAMBankTwo,
        workingRAMBankThree,
        workingRAMBankFour,
        workingRAMBankFive,
        workingRAMBankSix,
        workingRAMBankSeven
    };
    
    // Main memory buffer
    uint8_t mainMemory[0x10000];
    
    // ROMBuffer doesn't use uint8_t and instead counts on chars being 8 bit, which is rough.
    char* ROMBuffer = 0;
    int ROMBufferSize = 0;
public:
    // Some memory is controlled by switchable memory banks (especially in CGB mode).
    // These vals indicate which banks are active.
    // There are up to two Character Data banks and up to 8 Working RAM banks
    uint8_t activeCharacterDataBank = 0;
    uint8_t activeWorkingRAMBank = 0;
    
    // Initialize the memory map to a valid state. Can be used to reset system memory.
    void initialize();
    
    // Load a ROM into memory from disk
    void loadROM(std::string path);
    
    // Read or write data from a memory address, taking into consideration what banks are active
    // and other special circumstances (key input registers, shadow regions, etc)
    uint8_t readData(uint16_t address);
    void writeData(uint16_t address, uint8_t data);
    
    // Output the current state of memory to a file called 'debug_mem_dump.txt'
    void debugDumpMem();
};

#endif /* MemoryManager_h */
