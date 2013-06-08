//
//  Board.cpp
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "GoConstants.h"
#include "Board.h"

namespace Go
{
    Board::Board(int boardSize) : _boardSize(boardSize)
    {
    }
    
    void Board::clear()
    {
        memset(_data,0,sizeof(_data));
    }
    
    void Board::copyFrom(const Board& src)
    {
        memcpy(_data,src._data,sizeof(_data));
    }

    void Board::init()
    {
        memset(_data,EDGE,sizeof(_data));
        for (int row = 1; row<=_boardSize; row++)
        {
            for (int col = 1; col<=_boardSize; col++)
            {
                _data[col+row*WIDTH] = EMPTY;
            }
        }
    }
    

    void Board::print()
    {
        for (int row = 1; row<=_boardSize; row++)
        {
            for (int col = 1; col<=_boardSize; col++)
            {
                Byte b = _data[col+row*WIDTH];
                switch (b)
                {
                    case 0:
                        printf(".");
                        break;
                    case 1:
                        printf("X");
                        break;
                    case -1:
                        printf("O");
                        break;
                    default:
                        printf("#");
                }
            }
            printf("\n");
        }
        printf("\n\n");
    }
}