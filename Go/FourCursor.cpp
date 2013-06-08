//
//  FourCursor.cpp
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include "FourCursor.h"

namespace Go
{
    int FourCursor::intOffset[4] =
{
    below(0),
    above(0),
    right(0),
    left(0)
};

    Coordinate FourCursor::shortOffset[4] =
{
    (Coordinate)below(0),
    (Coordinate)above(0),
    (Coordinate)right(0),
    (Coordinate)left(0)
};
}
