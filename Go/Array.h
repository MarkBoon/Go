//
//  Arrays.h
//  Go
//
//  Created by Mark Boon on 6/6/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__Arrays__
#define __Go__Arrays__

namespace Go
{
    const int MAX_BOARD_SIZE =      19;
    const int WIDTH =               MAX_BOARD_SIZE + 1;
    const int FIRST =               WIDTH + 1;
    const int LAST =                MAX_BOARD_SIZE + (MAX_BOARD_SIZE*WIDTH);
    const int MAX_SIZE =            WIDTH * (WIDTH+1);
 
    static inline int getX(int xy) { return xy%WIDTH; }
    static inline int getY(int xy) { return xy/WIDTH; }
    static inline int left(int xy) { return xy-1; }
    static inline int right(int xy) { return xy+1; }
    static inline int above(int xy) { return xy-WIDTH; }
    static inline int below(int xy) { return xy+WIDTH; }
    
    class Array
    {
    private:
        int _data[MAX_SIZE];
        int _boardSize = 9;
        
    public:
        Array(int boardSize);
        
        int& operator [](int index) { return _data[index]; }
        
        int get(int index) { return _data[index]; }
        
        void clear();
        void init();
        void copyFrom(const Array& src);
        void print();
        
        int getBoardSize() { return _boardSize; }
    };
    
}

#endif /* defined(__Go__Arrays__) */
