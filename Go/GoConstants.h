//
//  GoConstants.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef Go_GoConstants_h
#define Go_GoConstants_h

#include "Types.h"

namespace Go
{
    const int UNDEFINED_COORDINATE = (1<<31)-1;
    const int PASS = 0;
    
    const Byte EMPTY = 0;
    const Byte BLACK = 1;
    const Byte WHITE = -1;
    const Byte EDGE = 2;
    
    static inline Byte opposite(Byte color) { return color==BLACK? WHITE : BLACK; }

}

#endif
