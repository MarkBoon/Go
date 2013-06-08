//
//  MersenneTwister.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__MersenneTwister__
#define __Go__MersenneTwister__

#include <climits>

/* Constant definitions! */
#define VEC_L	624				// Length of state-vector
#define SHF_C	397				// Shuffling constant
#define KNU_M	1812433253		// Knuth multiplier
#define ODG_C	2567483615		// Generator constant
#define TWC_1	2636928640		// Twisting constant #1
#define TWC_2	4022730752		// Twisting constant #2

namespace Util
{
    /* MersenneTwister class */
    class MersenneTwister
    {
    private:
        unsigned int state[VEC_L];
        unsigned short int index;
        
        void generateNumbers();
        
    public:
        MersenneTwister();
        MersenneTwister(unsigned int);
        void setSeed(unsigned int);
        unsigned int nextInt(int limit) { return extInt32()%limit; }
        unsigned int extInt32();
        unsigned short int extInt16();
        unsigned char extInt8();
        double extNormalDbl();
        double extSymmetricDbl();
    };
}
#endif /* defined(__Go__MersenneTwister__) */
