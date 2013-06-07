//
//  Board.cpp
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include <string.h>
#include "Board.h"

void Board::clear()
{
    memset(data,0,sizeof(data));
}

void Board::copyFrom(const Board& src)
{
    memcpy(data,src.data,sizeof(data));
}