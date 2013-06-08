//
//  PointSet.cpp
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include "PointSet.h"

namespace Go
{
    PointSet::PointSet(int boardSize) : _pointList(boardSize), _pointIndex(boardSize)
    {
        _nrPoints = 0;
    }
}