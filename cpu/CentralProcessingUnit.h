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

#include "../main/FixedWidthTypes.h"
#include "../memory/MemoryManager.h"

enum CPU_REGISTER {
    AF,
    BC,
    DE,
    HL,
    PC,
    SP
};

class CentralProcessingUnit {
private:
    uint16_t registerAF = 0;
    uint16_t registerBC = 0;
    uint16_t registerDE = 0;
    uint16_t registerHL = 0;
    uint16_t programCounter = 0;
    uint16_t stackPointer = 0;

    // Clockspeed in MHz
    float dmgClockSpeed = 4.194304;
    float cgbClockSpeed = 8.4;

    sf::Clock cpuClock;

    // Operations
    void loadWithStackPointer();
    void loadToRegister(uint8_t);
    void addToHL(uint8_t);

public:
    float clockSpeed = dmgClockSpeed;

    void initialize();
    void tick();

    uint16_t getRegisterValue(CPU_REGISTER reg);
};

#endif /* CentralProcessingUnit_h */
