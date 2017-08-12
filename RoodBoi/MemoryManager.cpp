//
//  MemoryManager.cpp
//  RoodBoi
//
//  Created by Sam Reha on 8/10/17.
//  Copyright © 2017 Sam Reha. All rights reserved.
//

#include "MemoryManager.h"

// private

// public
void MemoryManager::setCharacterDataBank(int bank) {
    activeCharacterDataBank = (uint8_t)std::min(std::max(bank, 0), 1);
}

void MemoryManager::setWorkingRAMBank(int bank) {
    activeWorkingRAMBank = (uint8_t)std::min(std::max(bank, 0), 7);
}

uint8_t MemoryManager::readData(uint16_t address) {
    // If we're looking at the character data bank, show the banked memory if in use
    if (address >= 0x8000 && address < 0xA000 && activeCharacterDataBank == 1) {
        return additionalCharDataBank[address - 0x8000];
    }
    
    // If we're looking at the banked portion of working RAM, get the data from the appropriate bank
    if (address >= 0xD000 && address < 0xE000) {
        return additionalWorkingRamBanks[activeWorkingRAMBank-1][address - 0xD000];
    }
    
    return mainMemory[address];
}

void MemoryManager::writeData(uint16_t address, uint8_t data) {
    // If we're looking at the character data bank, write to the banked memory if in use
    if (address >= 0x8000 && address < 0xA000 && activeCharacterDataBank == 1) {
        additionalCharDataBank[address - 0x8000] = data;
        return;
    }
    
    // If we're looking at working RAM, write the data to the appropriate bank
    if (address >= 0xD000 && address < 0xE000) {
        additionalWorkingRamBanks[activeWorkingRAMBank-1][address - 0xD000] = data;
        return;
    }
    
    mainMemory[address] = data;
}

void MemoryManager::debugDumpMem() {
    std::ofstream myfile;
    myfile.open("debug_mem_dump.txt");
    
    myfile << "Interrupt Address / RST Address" << std::endl;
    for (int i = 0x0000; i < 0x0100; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "ROM Data Area" << std::endl;
    for (int i = 0x0100; i < 0x0150; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "User Program Area (32 KB)" << std::endl;
    for (int i = 0x0150; i < 0x8000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Character Data" << std::endl;
    myfile << "       Bank 0, Bank 1" << std::endl;
    for (int i = 0x8000; i < 0x9800; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)mainMemory[i] << "      " <<
                  std::setw(2) << (uint)additionalCharDataBank[i - 0x8000] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Background Display Data 1 (CGB Only)" << std::endl;
    for (int i = 0x9800; i < 0x9C00; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << "      " <<
        std::setw(2) << (uint)additionalCharDataBank[i - 0x8000] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Background Display Data 2 (CGB Only)" << std::endl;
    for (int i = 0x9C00; i < 0xA000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << "      " <<
        std::setw(2) << (uint)additionalCharDataBank[i - 0x8000] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "External Expansion Working Ram (8 KB)" << std::endl;
    for (int i = 0xA000; i < 0xC000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Unit Working RAM (DMG has unbanked 8k, CGB has fixed bank 0 w/ switched banks 1 - 7 (4k each))" << std::endl;
    myfile << "Bank 0" << std::endl;
    for (int i = 0xC000; i < 0xD000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "       Bank 1, Bank 2, Bank 3, Bank 4, Bank 5, Bank 6, Bank 7" << std::endl;
    for (int i = 0xD000; i < 0xE000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        // std::setw(2) << (uint)mainMemory[i] << "      " << UNUSED
        std::setw(2) << (uint)additionalWorkingRamBanks[0][i - 0xD000] << "      " <<
        std::setw(2) << (uint)additionalWorkingRamBanks[1][i - 0xD000] << "      " <<
        std::setw(2) << (uint)additionalWorkingRamBanks[2][i - 0xD000] << "      " <<
        std::setw(2) << (uint)additionalWorkingRamBanks[3][i - 0xD000] << "      " <<
        std::setw(2) << (uint)additionalWorkingRamBanks[4][i - 0xD000] << "      " <<
        std::setw(2) << (uint)additionalWorkingRamBanks[5][i - 0xD000] << "      " <<
        std::setw(2) << (uint)additionalWorkingRamBanks[6][i - 0xD000] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Prohibited Area" << std::endl;
    for (int i = 0xE000; i < 0xFE00; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "OAM (40 x 32 bits)" << std::endl;
    for (int i = 0xFE00; i < 0xFEA0; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Prohibited Area" << std::endl;
    for (int i = 0xFEA0; i < 0xFF00; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Port/Mode Registers, Control Register, Sound Register" << std::endl;
    for (int i = 0xFF00; i < 0xFF80; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Working and Stack RAM (127 Bytes)" << std::endl;
    for (int i = 0xFF80; i < 0xFFFE; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile << "Unlabeled Area" << std::endl;
    for (int i = 0xFFFE; i < 0x10000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)mainMemory[i] << std::endl;
    }
    myfile << std::endl;
    
    myfile.close();
}
