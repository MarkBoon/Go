//
//  Arrays.cpp
//  Go
//
//  Created by Mark Boon on 6/6/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "Array.h"

namespace Go
{
    Array::Array(int boardSize) : _boardSize(boardSize)
    {
        clear();
    }
    
    void Array::clear()
    {
        memset(_data,0,sizeof(_data));
    }
    
    void Array::copyFrom(const Array& src)
    {
        memcpy(_data,src._data,sizeof(_data));
    }
    
    void Array::print()
    {
        for (int row = 1; row<=_boardSize; row++)
        {
            for (int col = 1; col<=_boardSize; col++)
            {
                int value = _data[col+row*WIDTH];
                printf("%2d ",value);
            }
            printf("\n");
        }
        printf("\n");
    }
}
