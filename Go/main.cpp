//
//  main.cpp
//  Go
//
//  Created by Mark Boon on 6/6/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include <iostream>
#include "Board.h"
#include "Assert.h"
#include "Stack.h"
#include "MonteCarloPluginAdministration.h"
#include <dispatch/dispatch.h>

using namespace Go;
using namespace MonteCarlo;
using namespace Util;

const int NR_PLAYOUTS = 10000000;

void playout()
{
    MonteCarloPluginAdministration mc(9);
    
    for (int i=0; i<NR_PLAYOUTS; i++)
    {
        mc.playout();
        mc.clear();
//        if (mc.getNrPasses()>1)
//            mc.clear();
//        else
//        {
//            int xy = mc.selectSimulationMove();
//            mc.playMove(xy);
//        }
    }
}

int main(int argc, const char * argv[])
{
    Board a(9);
    Board b(9);
    Stack<int,5> stack;
    
    a[23] = 3;
    b.copyFrom(a);
 //   assert(a[23]==1);
    stack.push(5);
    stack.push(4);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << "a[3]=" << (int)a[3] << std::endl;
    std::cout << "b[3]=" << (int)b[100] << std::endl;
    std::cout << "size=" << (int)b.getBoardSize() << std::endl;
    for (int value : stack)
        std::cout << "value=" << value << std::endl;
    
    int t = (int)(time(0) * 1000);
    cout << "Clocks per second: " << CLOCKS_PER_SEC << endl;
    cout << "Time: " << clock() << endl;
    clock_t start = clock();
    playout();
    clock_t end = clock();
    double timeDiff = (double)(end - start)/(double)CLOCKS_PER_SEC;
    cout << "Diff: " << timeDiff << endl;
    cout << "Nr kpos/s. = " << (NR_PLAYOUTS/timeDiff)/1000.0 << endl;
    
    return 0;
}

