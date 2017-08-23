//
//  CentralProcessingUnit.cpp
//  RoodBoi
//
//  Created by Sam Reha on 8/13/17.
//  Copyright © 2017 Sam Reha. All rights reserved.
//

#include "CentralProcessingUnit.h"

// private

// public
void CentralProcessingUnit::initialize() {
    cpuClock.restart();
}

void CentralProcessingUnit::tick() {
    if (cpuClock.getElapsedTime().asMicroseconds() >= 1.0 / clockSpeed) {
        uint8_t instruction = MemoryManager::instance()->readData(programCounter);
        
        // Make sure to reset the clock so that we tick at a steady rate
        cpuClock.restart();
    }
}
