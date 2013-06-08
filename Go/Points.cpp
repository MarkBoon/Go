//
//  Points.cpp
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "Points.h"

namespace Go
{
    Points::Points(int boardSize) : _boardSize(boardSize)
    {
        clear();
    }
    
    void Points::clear()
    {
        memset(_data,0,sizeof(_data));
    }
    
    void Points::copyFrom(const Points& src)
    {
        memcpy(_data,src._data,sizeof(_data));
    }
    
    void Points::print()
    {
        for (int row = 1; row<=_boardSize; row++)
        {
            for (int col = 1; col<=_boardSize; col++)
            {
                Coordinate c = _data[col+row*WIDTH];
                printf("%2d ",c);
            }
            printf("\n");
        }
        printf("\n");
    }
}