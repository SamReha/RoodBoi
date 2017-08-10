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
public:
    uint8_t readData(uint16_t address);
    void writeData(uint16_t address, uint8_t data);
};

#endif /* MemoryManager_h */
