//
//  Stack.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__Stack__
#define __Go__Stack__

#include <iostream>
#include "Assert.h"

namespace Util
{
    
    template <class T, int N>
    class Stack
    {
        class Iter
        {
        public:
            Iter (const Stack* p_vec, int pos)
            : _pos( pos )
            , _p_vec( p_vec )
            { }
            
            // these three methods form the basis of an iterator for use with
            // a range-based for loop
            bool
            operator!= (const Iter& other) const
            {
                return _pos != other._pos;
            }
            
            // this method must be defined after the definition of IntVector
            // since it needs to use it
//            int operator* () const;
            int operator* () const
            {
                return _p_vec->get( _pos );
            }
            
            const Iter& operator++ ()
            {
                ++_pos;
                // although not strictly necessary for a range-based for loop
                // following the normal convention of returning a value from
                // operator++ is a good idea.
                return *this;
            }
            
        private:
            int _pos;
            const Stack *_p_vec;
        };

    private:
        T _data[N];
        int _index;
        
    public:
        Stack()
        {
            _index = 0;
        }
        
        void push(T value)
        {
            assert(_index<N);

            _data[_index++] = value;
        }
        
        T pop()
        {
            assert(!isEmpty());

            return _data[--_index];
        }
        
        T peek() const
        {
            return _data[_index-1];
        }
        
        T peek(int n) const
        {
            return _data[_index-1-n];
        }
        
        T get(int n) const
        {
            return _data[n];
        }

        Iter begin () const
        {
            return Iter( this, 0 );
        }
        
        Iter end () const
        {
            return Iter( this, _index );
        }
        
        bool isEmpty() const
        {
            return _index==0;
        }
        
        int getSize() const
        {
            return _index;
        }
    };
}

#endif /* defined(__Go__Stack__) */
