//
//  MonteCarloPluginAdministration.h
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#ifndef __Go__MonteCarloPluginAdministration__
#define __Go__MonteCarloPluginAdministration__

#include "Board.h"
#include "BoardMarker.h"
#include "PointSet.h"
#include "Stack.h"
#include "Types.h"
#include "MersenneTwister.h"

using namespace Go;
using namespace Util;

#define USE_MERCY_RULE true

namespace MonteCarlo
{
    class MonteCarloPluginAdministration
    {
    private:
        bool _inPlayout;
        int _nrPasses;
        Byte _colorToPlay;
        Byte _oppositeColor;
        int _previousMove;
        double _komi;
        Coordinate _koPoint;
        int _nrBlackStones;
        int _nrWhiteStones;
        int _maxGameLength;
        double _mercyThreshold;
        
        Board _board;
        Stack<int,MAX_SIZE*2> _moveStack;
        PointSet _emptyPoints;
        
        Board _neighbours;
        Board _blackNeighbours;
        Board _whiteNeighbours;
        Board _blackDiagonalNeighbours;
        Board _whiteDiagonalNeighbours;
        Board _maxDiagonalsOccupied;

        Board* _ownNeighbours;
        Board* _otherNeighbours;
        Board* _ownDiagonalNeighbours;
        Board* _otherDiagonalNeighbours;

        Board _black;
        Board _white;
        
        Points _chain;
        Points _chainNext;
        Points _liberties;

        Stack<int,MAX_SIZE> _illegalStack;
        
        MersenneTwister RANDOM;
        
        BoardMarker _boardMarker;

    public:
        MonteCarloPluginAdministration(int boardSize);
        
        void clear();
        bool isLegal(int xy);
        bool isVerboten(int xy/*, List<MoveFilter> filterList*/);
        void playMove(int xy);
        void play(int xy);

        void addStone(int xy);
        void removeStone(int xy);
        void removeCapturedChain(int xy);
        int getLiberties(int xy);
        int getSharedLiberties(int xy, int chain);

        bool playout();
        int getNrPasses() { return _nrPasses; }
        
        int selectAndPlay();
        int selectSimulationMove();
        int selectSimulationMove(PointSet& emptyPoints);
        int selectRandomMoveCoordinate(PointSet emptyPoints/*, List<MoveFilter> filterList*/);
        void setNeighbourArrays();
        
        double getScore();

        double getScoreEstimate()
        {
            return (double)_nrBlackStones - (double)_nrWhiteStones - _komi;
        }
        
        bool isGameTooLong()
        {
            return (_moveStack.getSize() > _maxGameLength);
        }
        bool exceedsMercyThreshold()
        {
            double score = getScoreEstimate();
            return (score>_mercyThreshold || score<-_mercyThreshold);
        }
    };
}

#endif /* defined(__Go__MonteCarloPluginAdministration__) */
