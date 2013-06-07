//
//  main.cpp
//  Go
//
//  Created by Mark Boon on 6/6/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include <iostream>
#include "Board.h"

int main(int argc, const char * argv[])
{
    Board a;
    Board b;
    
    a[3] = 3;
    b.copyFrom(a);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << "a[3]=" << (int)a[3] << std::endl;
    std::cout << "b[3]=" << (int)b[100] << std::endl;
    return 0;
}

