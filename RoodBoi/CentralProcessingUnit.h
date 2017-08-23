//
//  CentralProcessingUnit.h
//  RoodBoi
//
//  Created by Sam Reha on 8/9/17.
//  Copyright © 2017 Sam Reha. All rights reserved.
//

#ifndef CentralProcessingUnit_h
#define CentralProcessingUnit_h

#include <SFML/Graphics.hpp>

#include "FixedWidthTypes.h"
#include "MemoryManager.h"

class CentralProcessingUnit {
private:
    uint8_t registers[8];
    uint16_t programCounter = 0;
    uint16_t stackPointer = 0;
    
    // Clockspeed in MHz
    float dmgClockSpeed = 4.194304;
    float cgbClockSpeed = 8.4;
    
    sf::Clock cpuClock;
    
public:
    float clockSpeed = dmgClockSpeed;
    
    void initialize();
    void tick();
};

#endif /* CentralProcessingUnit_h */
