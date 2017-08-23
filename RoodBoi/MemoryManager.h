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
    // Singleton should keep its constructor private
    MemoryManager() {};
    
    // Buffers for switchable memory banks
    uint8_t VRAMBankZero[0x2000];
    uint8_t VRAMBankOne[0x2000];
    uint8_t* VRAMBanks[2] = {
        VRAMBankZero,
        VRAMBankOne
    };
    
    // May need to be bankable
    uint8_t externalRAM[0x2000];
    
    uint8_t  workingRAMBankZero [0x1000];
    uint8_t  workingRAMBankOne  [0x1000];
    uint8_t  workingRAMBankTwo  [0x1000];
    uint8_t  workingRAMBankThree[0x1000];
    uint8_t  workingRAMBankFour [0x1000];
    uint8_t  workingRAMBankFive [0x1000];
    uint8_t  workingRAMBankSix  [0x1000];
    uint8_t  workingRAMBankSeven[0x1000];
    uint8_t* workingRAMBanks[8] = {
        workingRAMBankZero,
        workingRAMBankOne,
        workingRAMBankTwo,
        workingRAMBankThree,
        workingRAMBankFour,
        workingRAMBankFive,
        workingRAMBankSix,
        workingRAMBankSeven
    };
    
    uint8_t spriteAttributeTable[0x00A0];
    
    // Mashed these all together since they are actually contiguous in the Mem Map
    uint8_t ioPortsHRAMandIEReg[0x0100];
    
    // On-cart ROM Banks are just offsets into this buffer
    uint8_t* ROMBuffer = 0;
    int ROMBufferSize = 0;
public:
    // Singleton should publicly delete = operators
    MemoryManager(MemoryManager const&) = delete;
    MemoryManager& operator=(MemoryManager const&) = delete;
    
    // Get THE instance of the mem manager
    static std::shared_ptr<MemoryManager> instance() {
        static std::shared_ptr<MemoryManager> s{new MemoryManager};
        return s;
    }
    
    // Some memory is controlled by switchable memory banks (especially in CGB mode).
    // These vals indicate which banks are active.
    // There are up to two Character Data banks and up to 8 Working RAM banks
    uint8_t activeROMBank = 1;
    uint8_t activeVRAMBank = 0;
    uint8_t activeWorkingRAMBank = 1;
    
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
