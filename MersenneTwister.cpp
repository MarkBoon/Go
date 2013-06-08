//
//  MersenneTwister.cpp
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include <ctime>
#include "MersenneTwister.h"

namespace Util
{    
    MersenneTwister::MersenneTwister()
    {
        int t = (int)(time(0) * 1000);
        setSeed(t);
    }
    
    MersenneTwister::MersenneTwister(unsigned int seed)
    {
        setSeed(seed);
    }
    
    void MersenneTwister::setSeed(unsigned int seed)
    {
        unsigned long long temporaryStateVector[VEC_L];
        index = 0;
        temporaryStateVector[0] = (unsigned long long) seed;
        
        unsigned short int i;
        for (i=1; i<VEC_L; i++)
        {
            temporaryStateVector[i] =  ((KNU_M*((temporaryStateVector[i-1]^
                                                 (temporaryStateVector[i-1]>>30))+i))<<32)>>32;
        }
        
        for (i=0; i<VEC_L; i++)
        {
            state[i] = (unsigned int) temporaryStateVector[i];
        }
    }
    
    void MersenneTwister::generateNumbers()
    {
        unsigned int y;
        
        unsigned short int i;
        for (i=0; i<VEC_L; i++)
        {
            y = (state[i]>>31)+((state[(i+1)%VEC_L]<<1)>>1);
            state[i] = state[(i+SHF_C)%VEC_L]^(y >> 1);
            if ((y % 2) != 0)
            {
                state[i] ^= ODG_C;
            }
        }
    }
    
    unsigned int MersenneTwister::extInt32()
    {
        if (index == 0)
        {
            generateNumbers();
        }
        unsigned int y = state[index];
        y = y^(y>>11);
        y = y^((y<<7)&TWC_1);
        y = y^((y<<15)&TWC_2);
        y = y^(y>>18);
        
        index = (index++)%VEC_L;
        return y;
    }
    
/*    unsigned short int MersenneTwister::extInt16()
    {
        unsigned short int y;
        y = unsigned short int (extInt32() % 0xFFFF);
        return y;
    }
    
    unsigned char MersenneTwister::extInt8()
    {
        unsigned char y;
        y = unsigned char (extInt32() % 0xFF);
        return y;
    }*/
    
    double MersenneTwister::extNormalDbl()
    {
        double y;
        y = double(extInt32())/double(0xFFFFFFFF);
        return y;
    }
    
    double MersenneTwister::extSymmetricDbl()
    {
        double y;
        y = (double(extInt32())/double(0xFFFFFFFF)) - 0.5;
        return y;
    }
}