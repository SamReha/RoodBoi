//
//  CentralProcessingUnit.h
//  RoodBoi
//
//  Created by Sam Reha on 8/9/17.
//  Copyright © 2017 Sam Reha. All rights reserved.
//

#ifndef CentralProcessingUnit_h
#define CentralProcessingUnit_h

class CentralProcessingUnit {
private:
    uint8_t registers[7];
    uint16_t programCounter = 0;
    uint16_t otherRegister = 0;
    
public:
    void tick();
};

#endif /* CentralProcessingUnit_h */
