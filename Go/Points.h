//
//  Points.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__Points__
#define __Go__Points__

#include "Array.h"
#include "Types.h"

namespace Go
{
    class Points
    {
    private:
        Coordinate _data[MAX_SIZE];
        int _boardSize = 9;
        
    public:
        Points(int boardSize);
        
        Coordinate& operator [](int index) { return _data[index]; }
        
        void clear();
        void copyFrom(const Points& src);
        void print();
        
        int getBoardSize() { return _boardSize; }
    };
}

#endif /* defined(__Go__Points__) */
