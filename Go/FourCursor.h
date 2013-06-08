//
//  FourCursor.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef Go_FourCursor_h
#define Go_FourCursor_h

#include "Array.h"
#include "Types.h"

namespace Go
{
    class FourCursor
    {
    private:
        static int intOffset[4];
        
        static Coordinate shortOffset[4];
        
    public:
        static int getNeighbour(int xy, int n)
        {
            return xy + FourCursor::intOffset[n];
        }
        
        static Coordinate getNeighbour(Coordinate xy, int n)
        {
            return (Coordinate)(xy + FourCursor::shortOffset[n]);
        }        
    };
}

#endif
