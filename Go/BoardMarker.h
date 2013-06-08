//
//  BoardMarker.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__BoardMarker__
#define __Go__BoardMarker__

#include "Array.h"

namespace Go
{
    class BoardMarker
    {
    private:
        int _labelNr;
        Array _markers;
    public:
        BoardMarker() : _markers(19)
        {
            _labelNr = 1;
        }
        
        /**
         This causes all points previously marked as 'set'
         to be unmarked.
         */
        void getNewMarker()
        {
            _labelNr++;
            if (_labelNr==0)
            {
                _labelNr = 1;
                _markers.clear();
            }
        }
        
        /**
         Mark a point as set.
         
         @param xy is the coordinate of the point to mark as set.
         */
        void set( int xy )
        {
            _markers[xy] = _labelNr;
        }
        
        /**
         Test whether a point was already marked or not.
         
         @param xy coordinate of the point to test
         @return whether the point was already marked or not.
         */
        bool notSet( int xy )
        {
            return _markers[xy]!=_labelNr;
        }
        
        /**
         Test whether a point was already marked or not.
         
         @param xy coordinate of the point to test
         @return whether the point was already marked or not.
         */
        bool isSet( int xy )
        {
            return _markers[xy]==_labelNr;
        }
    };
}

#endif /* defined(__Go__BoardMarker__) */
