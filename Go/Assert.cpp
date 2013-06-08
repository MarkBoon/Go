//
//  Assert.cpp
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include "Assert.h"
#define NDEBUG

namespace Util
{
    void assert(bool expression)
    {
#ifndef NDEBUG
        if (!expression)
        {
            cout << "Assertion failed in " << __FILE__ << "(line=" << __LINE__ <<")" << endl;
            throw new AssertException();
        }
#endif
    }
    
    void assert(bool expression, string& output)
    {
#ifndef NDEBUG
        if (!expression)
        {
            cout << "Assertion failed in " << __FILE__ << "(line=" << __LINE__ <<"): " << output << endl;
            throw new AssertException();
        }
#endif
    }
    
    void assert(bool expression, const char* output)
    {
#ifndef NDEBUG
        if (!expression)
        {
            cout << "Assertion failed in " << __FILE__ << "(line=" << __LINE__ <<"): " << output << endl;
            throw new AssertException();
        }
#endif
    }
    
    void assert(bool expression, void (*print)())
    {
#ifndef NDEBUG
        if (!expression)
        {
            cout << "Assertion failed in " << __FILE__ << "(line=" << __LINE__ <<"): " << endl;
            print();
            throw new AssertException();
        }
#endif
    }
}