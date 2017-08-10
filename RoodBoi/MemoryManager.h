//
//  MemoryManager.h
//  RoodBoi
//
//  Created by Sam Reha on 8/9/17.
//  Copyright © 2017 Sam Reha. All rights reserved.
//

#ifndef MemoryManager_h
#define MemoryManager_h

class MemoryManager {
private:
    // GBC supports switchable memory banks. These vals indicate which banks are active.
    // There are up to two Character Data banks and up to 8 Working RAM banks
    uint8_t activeCharacterDataBank = 0;
    uint8_t activeWorkingRAMBank = 0;
    
    // Buffers for switchable memory banks
    uint8_t additionalCharDataBank[8000];
    uint8_t additionalWorkingRamBankOne[8000];
    uint8_t additionalWorkingRamBankTwo[8000];
    uint8_t additionalWorkingRamBankThree[8000];
    uint8_t additionalWorkingRamBankFour[8000];
    uint8_t additionalWorkingRamBankFive[8000];
    uint8_t additionalWorkingRamBankSix[8000];
    uint8_t additionalWorkingRamBankSeven[8000];
    uint8_t* additionalWorkingRamBanks[7] = {
        additionalWorkingRamBankOne,
        additionalWorkingRamBankTwo,
        additionalWorkingRamBankThree,
        additionalWorkingRamBankFour,
        additionalWorkingRamBankFive,
        additionalWorkingRamBankSix,
        additionalWorkingRamBankSeven
    };
    
    // Main memory buffer
    uint8_t mainMemory[65536];
public:
    // Simply sets the active bank (0 - 1 for Character Data, 0 - 7 for Working RAM)
    void setCharacterDataBank(uint8_t bank);
    void setWorkingRAMBank(uint8_t bank);
    
    // Initialize the memory map to a valid state. Can be used to reset system memory.
    void initialize();
    
    // Load a ROM into memory from disk
    void loadROM();
    
    // Read or write data from a memory address, taking into consideration what banks are active
    // and other special circumstances (key input registers, shadow regions, etc)
    uint8_t readData(uint16_t address);
    void writeData(uint16_t address, uint8_t data);
    
    // Output the current state of memory to a file called 'mem_dump.txt'
    void debugDumpMem();
};

#endif /* MemoryManager_h */
