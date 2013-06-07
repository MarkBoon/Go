//
//  Board.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__Board__
#define __Go__Board__

#include "Arrays.h"
#include "Types.h"

class Board
{
private:
    Byte data[MAX_SIZE];
public:
    Byte& operator [](int index) { return data[index]; }
    
    void clear();
    void copyFrom(const Board& src);
};

#endif /* defined(__Go__Board__) */
