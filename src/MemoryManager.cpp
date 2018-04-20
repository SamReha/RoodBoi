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
void MemoryManager::loadROM(std::string path) {
    // Attempt to open file in binary input mode
    std::ifstream rom;
    rom.open(path, std::ios::in | std::ios::binary);

    if (!rom.is_open())
        throw "File Not Found!";

    // Load the entire rom into the ROM buffer
    rom.seekg(0, std::ifstream::end);
    ROMBufferSize = rom.tellg();
    rom.seekg(0, std::ios::beg);

    ROMBuffer = new uint8_t[ROMBufferSize];

    rom.read((char*)ROMBuffer, ROMBufferSize);
    rom.close();
}

uint8_t MemoryManager::readData(uint16_t address) {
    // If we're reading unbanked program ROM...
    if (address >= 0x0000 && address < 0x4000) {
        return ROMBuffer[address];
    }

    // If we're reading banked program ROM...
    if (address >= 0x4000 && address < 0x8000) {
        return ROMBuffer[address + ((activeROMBank-1) * 0x4000)];
    }

    // If we're reading from the VRAM...
    if (address >= 0x8000 && address < 0xA000) {
        return VRAMBanks[activeVRAMBank][address - 0x8000];
    }

    // If we're reading from the external RAM...
    if (address >= 0xA000 && address < 0xBFFF) {
        return externalRAM[address - 0xA000];
    }

    // If we're reading from the unbanked portion of work RAM...
    if (address >= 0xC000 && address < 0xD000) {
        return workingRAMBanks[0][address - 0xC000];
    }

    // If we're looking at the banked portion of working RAM, get the data from the appropriate bank
    if (address >= 0xD000 && address < 0xE000) {
        return workingRAMBanks[activeWorkingRAMBank][address - 0xD000];
    }

    // If we're looking at the shadow memory (same as working RAM)
    if (address >= 0xE000 && address < 0xFE00) {
        return readData(address - 0x2000);
    }

    // If we're reading from the sprite attribute table...
    if (address >= 0xFE00 && address < 0xFEA0) {
        return spriteAttributeTable[address - 0xFE00];
    }

    // If we're reading from the IO Ports, High RAM orrr the Interrupt Escape Register
    if (address >= 0xFF00 && address < 0x1000) {
        return ioPortsHRAMandIEReg[address - 0xFF00];
    }

    // Return null as a default value. Not sure what is supposed to happen?
    return 0x00;
}

void MemoryManager::writeData(uint16_t address, uint8_t data) {
    // If we're writing to the VRAM...
    if (address >= 0x8000 && address < 0xA000) {
        VRAMBanks[activeVRAMBank][address - 0x8000] = data;
        return;
    }

    // If we're writing to the external RAM...
    if (address >= 0xA000 && address < 0xBFFF) {
        externalRAM[address - 0xA000] = data;
        return;
    }

    // If we're writing to the unbanked portion of work RAM...
    if (address >= 0xC000 && address < 0xD000) {
        workingRAMBanks[0][address - 0xC000] = data;
        return;
    }

    // If we're writing to the banked portion of working RAM, get the data from the appropriate bank
    if (address >= 0xD000 && address < 0xE000) {
        workingRAMBanks[activeWorkingRAMBank][address - 0xD000] = data;
        return;
    }

    // If we're writing to the shadow memory (same as working RAM)
    if (address >= 0xE000 && address < 0xFE00) {
        writeData(address - 0x2000, data);
        return;
    }

    // If we're writing to the sprite attribute table...
    if (address >= 0xFE00 && address < 0xFEA0) {
        spriteAttributeTable[address - 0xFE00] = data;
        return;
    }

    // If we're writing to the IO Ports, High RAM orrr the Interrupt Escape Register
    if (address >= 0xFF00 && address < 0x1000) {
        ioPortsHRAMandIEReg[address - 0xFF00] = data;
        return;
    }

    // Not sure what's supposed to happen on an invalid write
}

void MemoryManager::debugDumpMem() {
    std::ofstream myfile;
    myfile.open("debug_mem_dump.txt");

    myfile << "Interrupt Address / RST Address" << std::endl;
    for (int i = 0x0000; i < 0x0100; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)ROMBuffer[i] << std::endl;
    }
    myfile << std::endl;

    myfile << "ROM Data Area" << std::endl;
    for (int i = 0x0100; i < 0x0150; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)ROMBuffer[i] << std::endl;
    }
    myfile << std::endl;

    myfile << "User Program Area (32 KB)" << std::endl;
    for (int i = 0x0150; i < 0x8000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)ROMBuffer[i] << std::endl;
    }
    myfile << std::endl;

    myfile << "Character Data" << std::endl;
    myfile << "       Bank 0, Bank 1" << std::endl;
    for (int i = 0x8000; i < 0x9800; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)VRAMBanks[0][i - 0x8000] << "      " <<
                  std::setw(2) << (uint)VRAMBanks[1][i - 0x8000] << std::endl;
    }
    myfile << std::endl;

    myfile << "Background Display Data 1 (CGB Only)" << std::endl;
    for (int i = 0x9800; i < 0x9C00; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)VRAMBanks[0][i - 0x8000] << "      " <<
                  std::setw(2) << (uint)VRAMBanks[1][i - 0x8000] << std::endl;
    }
    myfile << std::endl;

    myfile << "Background Display Data 2 (CGB Only)" << std::endl;
    for (int i = 0x9C00; i < 0xA000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)VRAMBanks[0][i - 0x8000] << "      " <<
                  std::setw(2) << (uint)VRAMBanks[1][i - 0x8000] << std::endl;
    }
    myfile << std::endl;

    myfile << "External Expansion Working Ram (8 KB)" << std::endl;
    for (int i = 0xA000; i < 0xC000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)externalRAM[i - 0xA000] << std::endl;
    }
    myfile << std::endl;

    myfile << "Unit Working RAM (DMG has unbanked 8k, CGB has fixed bank 0 w/ switched banks 1 - 7 (4k each))" << std::endl;
    myfile << "Bank 0" << std::endl;
    for (int i = 0xC000; i < 0xD000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
                  std::setw(2) << (uint)workingRAMBanks[0][i - 0xC000] << std::endl;
    }
    myfile << std::endl;

    myfile << "       Bank 1, Bank 2, Bank 3, Bank 4, Bank 5, Bank 6, Bank 7" << std::endl;
    for (int i = 0xD000; i < 0xE000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)workingRAMBanks[1][i - 0xD000] << "      " <<
        std::setw(2) << (uint)workingRAMBanks[2][i - 0xD000] << "      " <<
        std::setw(2) << (uint)workingRAMBanks[3][i - 0xD000] << "      " <<
        std::setw(2) << (uint)workingRAMBanks[4][i - 0xD000] << "      " <<
        std::setw(2) << (uint)workingRAMBanks[5][i - 0xD000] << "      " <<
        std::setw(2) << (uint)workingRAMBanks[6][i - 0xD000] << "      " <<
        std::setw(2) << (uint)workingRAMBanks[7][i - 0xD000] << std::endl;
    }
    myfile << std::endl;

    myfile << "Prohibited Area" << std::endl;
    for (int i = 0xE000; i < 0xFE00; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << "--" << std::endl;
    }
    myfile << std::endl;

    myfile << "OAM (40 x 32 bits)" << std::endl;
    for (int i = 0xFE00; i < 0xFEA0; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)spriteAttributeTable[i - 0xFE00] << std::endl;
    }
    myfile << std::endl;

    myfile << "Prohibited Area" << std::endl;
    for (int i = 0xFEA0; i < 0xFF00; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << "--" << std::endl;
    }
    myfile << std::endl;

    myfile << "Port/Mode Registers, Control Register, Sound Register" << std::endl;
    for (int i = 0xFF00; i < 0xFF80; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)ioPortsHRAMandIEReg[i - 0xFF00] << std::endl;
    }
    myfile << std::endl;

    myfile << "Working and Stack RAM (127 Bytes)" << std::endl;
    for (int i = 0xFF80; i < 0xFFFF; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)ioPortsHRAMandIEReg[i - 0xFF00] << std::endl;
    }
    myfile << std::endl;

    myfile << "Interrupt Enable Register" << std::endl;
    for (int i = 0xFFFF; i < 0x10000; i++) {
        myfile << "0x" << std::setfill('0') << std::setw(4) << std::hex << i << " " <<
        std::setw(2) << (uint)ioPortsHRAMandIEReg[i - 0xFF00] << std::endl;
    }
    myfile << std::endl;

    myfile.close();
}
