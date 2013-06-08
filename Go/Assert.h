//
//  Assert.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__Assert__
#define __Go__Assert__

#include <iostream>

using namespace std;

namespace Util
{
    extern void assert(bool expression);
    extern void assert(bool expression, string& output);
    extern void assert(bool expression, const char* output);
    extern void assert(bool expression, void (*print)());
    
    class AssertException : exception
    {
        
    };
};

#endif /* defined(__Go__Assert__) */
