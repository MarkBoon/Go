//
//  PointSet.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__PointSet__
#define __Go__PointSet__

#include <iostream>
#include "Points.h"

namespace Go
{
    class PointSet
    {
    private:
        Points _pointList;
        Points _pointIndex;
        int _nrPoints;
    public:
        PointSet(int boardSize);
        
        void add(int xy)
        {
            _pointList[_nrPoints] = xy;
            _pointIndex[xy] = _nrPoints;
            _nrPoints++;	
        }
        
        void remove(int xy)
        {
            Coordinate pointIndex = _pointIndex[xy];
            _nrPoints--;
            _pointIndex[_pointList[_nrPoints]] = pointIndex;
            _pointList[pointIndex] = _pointList[_nrPoints];
        }
        
        int getSize()
        {
            return _nrPoints;
        }
        
        Coordinate get(int index)
        {
            return _pointList[index];
        }
        
        void clear()
        {
            _nrPoints = 0;
        }
    };
}
#endif /* defined(__Go__PointSet__) */
