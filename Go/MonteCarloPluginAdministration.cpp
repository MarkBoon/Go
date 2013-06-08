//
//  MonteCarloPluginAdministration.cpp
//  Go
//
//  Created by Mark Boon on 6/7/13.
//  Copyright (c) 2013 Mark Boon. All rights reserved.
//

#include "MonteCarloPluginAdministration.h"

#include "Assert.h"
#include "Array.h"
#include "Macros.h"
#include "GoConstants.h"
#include "FourCursor.h"

using namespace Util;

namespace MonteCarlo
{
    MonteCarloPluginAdministration::MonteCarloPluginAdministration(int boardSize) :
        _board(boardSize),
        _emptyPoints(boardSize),
        _black(boardSize),
        _white(boardSize),
        _neighbours(boardSize),
        _blackNeighbours(boardSize),
        _whiteNeighbours(boardSize),
        _blackDiagonalNeighbours(boardSize),
        _whiteDiagonalNeighbours(boardSize),
        _maxDiagonalsOccupied(boardSize),
        _chain(boardSize),
        _chainNext(boardSize),
        _liberties(boardSize)
    {
        _maxGameLength = MAX_SIZE*2;
		_mercyThreshold = boardSize*3;
        
        clear();
    }
    
    void MonteCarloPluginAdministration::clear()
    {
        _colorToPlay = BLACK;
        _board.init();
        _emptyPoints.clear();
        _black.clear();
        _white.clear();
        _neighbours.clear();
        _blackNeighbours.clear();
        _whiteNeighbours.clear();
        _blackDiagonalNeighbours.clear();
        _whiteDiagonalNeighbours.clear();
        _maxDiagonalsOccupied.clear();

        _ownNeighbours = &_blackNeighbours;
		_otherNeighbours = &_whiteNeighbours;
		_ownDiagonalNeighbours = &_blackDiagonalNeighbours;
		_otherDiagonalNeighbours = &_whiteDiagonalNeighbours;
		
		_koPoint = UNDEFINED_COORDINATE;
		_previousMove = UNDEFINED_COORDINATE;

		for_every(i)
		{
			if (_board[i]!=EDGE)
                //if (_boardModel.get(i)!=EDGE)
			{
				_board[i] = EMPTY;
				//_boardModel.set(i, EMPTY);
				int x = getX(i);
				int y = getY(i);
                
				if (x==1 || y==1 || x==_board.getBoardSize() || y==_board.getBoardSize())
					_maxDiagonalsOccupied[i] = 1;
				else
					_maxDiagonalsOccupied[i] = 2;
				
				_emptyPoints.add(i);
			}
//			else
//				_probabilityMap.reset(i);
			
			for (int n=0; n<4; n++)
			{
				int next = FourCursor::getNeighbour(i, n);
				if (_board[next]==EDGE)
                    //if (_boardModel.get(next)==EDGE)
				{
					_neighbours[i]++;
					_blackNeighbours[i]++;
					_whiteNeighbours[i]++;
				}
			}
		}
        _liberties[0] = 1000;
    }
    
	bool MonteCarloPluginAdministration::isLegal(int xy)
	{
		if (xy<0) // Temporary hack
			return false;
        
        //		byte[] board = _boardModel.getSingleArray();
		if (_board[xy]!=EMPTY)
			return false; // Occupied.
        
		if (_neighbours[xy]!=4)
			return true;
		if (xy==_koPoint && _otherNeighbours->get(xy)==4)
			return false;
        
		for (int n=0; n<4; n++)
		{
			int next = FourCursor::getNeighbour(xy, n);
			int liberties = _liberties[_chain[next]];
			Byte nextBoardValue = _board[next];
			if (nextBoardValue==_oppositeColor)
			{
				if (liberties==1)
					return true;
			}
			else if (nextBoardValue==_colorToPlay)
			{
				if (liberties>1)
					return true;
			}
		}
		return false;
	}

    /**
	 * Check if a move is not allowed, not because it's illegal but because it's undesirable.
	 * This typically will not allow a side to fill its own eyes.
	 *
	 * @param xy - coordinate of the move
	 * @return whether allowed or not
	 */
	bool MonteCarloPluginAdministration::isVerboten(int xy/*, List<MoveFilter> filterList*/)
	{
//		int size = filterList.size();
//		for (int i=0; i<size; i++)
//		{
//			MoveFilter filter = filterList.get(i);
//			if (filter.accept(xy, getColorToMove()))
//				return true;
//		}
//		
//		return false;
		
		// Check for standard 'eye' definition.
        return (_ownNeighbours->get(xy)==4 && _otherDiagonalNeighbours->get(xy)<_maxDiagonalsOccupied[xy]);
	}

    int MonteCarloPluginAdministration::selectAndPlay()
    {
		int xy = selectSimulationMove(_emptyPoints);
		playMove(xy);
//		_checksumStack.push(getPositionalChecksum());
		return xy;        
    }

    void MonteCarloPluginAdministration::playMove(int xy)
    {
		_koPoint = UNDEFINED_COORDINATE;
        
		_moveStack.push(xy);
		play(xy);
		
		if (xy==PASS)
			_nrPasses++;
		else
			_nrPasses = 0;
        
		_previousMove = xy;
		assert (_previousMove==_moveStack.peek() ,"Inconsistent previous move");
    }

	void MonteCarloPluginAdministration::play(int xy)
	{
		if (xy!=PASS)
		{
			bool extended = false;
			bool merged = false;
            //			byte[] board = _boardModel.getSingleArray();
			
			assert (_board[xy] == EMPTY /*: SGFUtil.createSGF(getMoveStack()*/);
            //			assert _boardModel.get(xy) == EMPTY : SGFUtil.createSGF(getMoveStack());
			
			_chain[xy] = xy;
			_chainNext[xy] = xy;
//			_stoneAge[xy] = _moveStack.getSize();
			
			addStone(xy);
            
			for (int n=0; n<4; n++)
			{
				int next = FourCursor::getNeighbour(xy, n);
				if (_board[next]==_colorToPlay)
				{
					if (!extended)
					{
						extended = true;
						_chain[xy] = _chain[next];
						_chainNext[xy] = _chainNext[next];
						_chainNext[next] = xy;
					}
					else if (_chain[next]!=_chain[xy])
					{
						merged = true;
						int mergeLocation = next;
						int chain = _chain[xy];
						do
						{
							_chain[mergeLocation] = chain;
							mergeLocation = _chainNext[mergeLocation];
						}
						while (mergeLocation!=next);
						int temp = _chainNext[xy];
						_chainNext[xy] = _chainNext[next];
						_chainNext[next] = temp;
					}
				}
			}
            
			if (merged) // No way but the expensive way.
				_liberties[_chain[xy]] = getLiberties(xy);
			else if (extended)
			{
				// When adding a stone to an existing chain, just take care of the shared liberties.
				int shared = getSharedLiberties(xy, _chain[xy]);
				_liberties[_chain[xy]] += (3 - _neighbours[xy]) - shared;
			}
			else // For a single stone we get the liberties cheapo.
				_liberties[_chain[xy]] = 4 - _neighbours[xy];
			
			for (int n=0; n<4; n++)
			{
				int next = FourCursor::getNeighbour(xy, n);
				if (_board[next]==_oppositeColor)
				{
					if (_liberties[_chain[next]]==0)
					{
						if (_ownNeighbours->get(next)==4 && _otherNeighbours->get(xy)==4)
							_koPoint = next;
						removeCapturedChain(next);
					}
				}
			}
			
//			assert (_liberties[_chain[xy]]==getLiberties(xy));
            /* : "Computed liberties incorrect at "+GoArray.getX(xy)+","+GoArray.getY(xy)+"\nGot "+_liberties[_chain[xy]]+" but should be "+getLiberties(xy)+"\n\n"+toString(););*/
		}
		
		_oppositeColor = _colorToPlay;
		_colorToPlay = opposite(_colorToPlay);
		
		setNeighbourArrays();
		
//		assert( isLibertiesConsistent() : toString());
	}

	int MonteCarloPluginAdministration::getLiberties(int xy)
	{
		assert( xy!=0 , "Cannot get liberties for pass");
        
		int nrLiberties = 0;
		_boardMarker.getNewMarker();
        //		byte[] board = _boardModel.getSingleArray();
		
		int stoneXY = xy;
		do
		{
			assert( stoneXY!=0 , "Coordinate 0 cannot be part of a chain");
            
			if (_neighbours[stoneXY]!=4)
			{
				int leftXY = left(stoneXY);
				int rightXY = right(stoneXY);
				int aboveXY = above(stoneXY);
				int belowXY = below(stoneXY);
				if (_board[leftXY]==EMPTY && _boardMarker.notSet(leftXY))
				{
					_boardMarker.set(leftXY);
					nrLiberties++;
				}
				if (_board[rightXY]==EMPTY && _boardMarker.notSet(rightXY))
				{
					_boardMarker.set(rightXY);
					nrLiberties++;
				}
				if (_board[aboveXY]==EMPTY && _boardMarker.notSet(aboveXY))
				{
					_boardMarker.set(aboveXY);
					nrLiberties++;
				}
				if (_board[belowXY]==EMPTY && _boardMarker.notSet(belowXY))
				{
					_boardMarker.set(belowXY);
					nrLiberties++;
				}
			}
			
			stoneXY = _chainNext[stoneXY];
		}
		while (stoneXY!=xy);
        
		return nrLiberties;
	}

	/**
	 * Add a stone to the administration.
	 *
	 * @param xy - coordinate of the stone
	 * @param color - color of the stone
	 */
	void MonteCarloPluginAdministration::addStone(int xy)
	{
        //		byte[] board = _boardModel.getSingleArray();
        //		_boardModel.set(xy, _colorToPlay);
		_board[xy] = _colorToPlay;
		_emptyPoints.remove(xy);
//		_checksum.add(xy, _colorToPlay);
		
		int leftXY = left(xy);
		int rightXY = right(xy);
		int aboveXY = above(xy);
		int belowXY = below(xy);
		
		int leftChain = _chain[leftXY];
		int rightChain = _chain[rightXY];
		int aboveChain = _chain[aboveXY];
		int belowChain = _chain[belowXY];
		
		if (_board[leftXY]==_oppositeColor)
			_liberties[leftChain]--;
		if (_board[rightXY]==_oppositeColor && leftChain!=rightChain)
			_liberties[rightChain]--;
		if (_board[aboveXY]==_oppositeColor && leftChain!=aboveChain && rightChain!=aboveChain)
			_liberties[aboveChain]--;
		if (_board[belowXY]==_oppositeColor && leftChain!=belowChain && rightChain!=belowChain && aboveChain!=belowChain)
			_liberties[belowChain]--;
		
		_neighbours[leftXY]++;
		_neighbours[rightXY]++;
		_neighbours[aboveXY]++;
		_neighbours[belowXY]++;
		
		if (_colorToPlay==BLACK) // For some strange reason, using _ownNeighbours without 'if' here is MUCH slower.
		{
			_nrBlackStones++;
			_black[xy] = 1;
			_blackNeighbours[leftXY]++;
			_blackNeighbours[rightXY]++;
			_blackNeighbours[aboveXY]++;
			_blackNeighbours[belowXY]++;
			_blackDiagonalNeighbours[left(aboveXY)]++;
			_blackDiagonalNeighbours[left(belowXY)]++;
			_blackDiagonalNeighbours[right(aboveXY)]++;
			_blackDiagonalNeighbours[right(belowXY)]++;
		}
		else
		{
			_nrWhiteStones++;
			_white[xy] = 1;
			_whiteNeighbours[leftXY]++;
			_whiteNeighbours[rightXY]++;
			_whiteNeighbours[aboveXY]++;
			_whiteNeighbours[belowXY]++;
			_whiteDiagonalNeighbours[left(aboveXY)]++;
			_whiteDiagonalNeighbours[left(belowXY)]++;
			_whiteDiagonalNeighbours[right(aboveXY)]++;
			_whiteDiagonalNeighbours[right(belowXY)]++;
		}
//		_probabilityMap.reset(xy);
	}
    
	/**
	 * Remove a stone from the administration.
	 *
	 * @param xy - coordinate of the stone
	 * @param color - color of the stone
	 */
	void MonteCarloPluginAdministration::removeStone(int xy)
	{
        //		byte[] board = _boardModel.getSingleArray();
        //		if (_inPlayout)
        _board[xy] = EMPTY;
        //		else
        //			_boardModel.set(xy, EMPTY);
		_emptyPoints.add(xy);
//		_checksum.remove(xy, _oppositeColor);
        
		int leftXY = left(xy);
		int rightXY = right(xy);
		int aboveXY = above(xy);
		int belowXY = below(xy);
		
		int leftChain = _chain[leftXY];
		int rightChain = _chain[rightXY];
		int aboveChain = _chain[aboveXY];
		int belowChain = _chain[belowXY];
		
		if (_board[leftXY]==_colorToPlay)
			_liberties[leftChain]++;
		if (_board[rightXY]==_colorToPlay && leftChain!=rightChain)
			_liberties[rightChain]++;
		if (_board[aboveXY]==_colorToPlay && leftChain!=aboveChain && rightChain!=aboveChain)
			_liberties[aboveChain]++;
		if (_board[belowXY]==_colorToPlay && leftChain!=belowChain && rightChain!=belowChain && aboveChain!=belowChain)
			_liberties[belowChain]++;
        
		_neighbours[leftXY]--;
		_neighbours[rightXY]--;
		_neighbours[aboveXY]--;
		_neighbours[belowXY]--;
		if (_oppositeColor==BLACK) // For some strange reason, using _otherNeighbours without 'if' here is MUCH slower.
		{
			_nrBlackStones--;
			_black[xy] = 0;
			_blackNeighbours[leftXY]--;
			_blackNeighbours[rightXY]--;
			_blackNeighbours[aboveXY]--;
			_blackNeighbours[belowXY]--;
			_blackDiagonalNeighbours[left(aboveXY)]--;
			_blackDiagonalNeighbours[left(belowXY)]--;
			_blackDiagonalNeighbours[right(aboveXY)]--;
			_blackDiagonalNeighbours[right(belowXY)]--;
		}
		else
		{
			_nrWhiteStones--;
			_white[xy] = 0;
			_whiteNeighbours[leftXY]--;
			_whiteNeighbours[rightXY]--;
			_whiteNeighbours[aboveXY]--;
			_whiteNeighbours[belowXY]--;
			_whiteDiagonalNeighbours[left(aboveXY)]--;
			_whiteDiagonalNeighbours[left(belowXY)]--;
			_whiteDiagonalNeighbours[right(aboveXY)]--;
			_whiteDiagonalNeighbours[right(belowXY)]--;
		}
//		_probabilityMap.add(xy);
	}

	void MonteCarloPluginAdministration::removeCapturedChain(int xy)
	{
//		assert !hasLiberty(xy) : SGFUtil.createSGF(getMoveStack());
        
		int captive = xy;
		do
		{
//			assert _board[captive]==_oppositeColor : SGFUtil.createSGF(getMoveStack());
            //			assert _boardModel.get(captive)==_oppositeColor : SGFUtil.createSGF(getMoveStack());
			
			_chain[captive] = 0;
			
			removeStone(captive);
			
			captive = _chainNext[captive];
		}
		while (captive!=xy);
	}
	
    
	int MonteCarloPluginAdministration::getSharedLiberties(int xy, int chain)
	{
		int shared = 0;
		int leftXY = left(xy);
		int rightXY = right(xy);
		int aboveXY = above(xy);
		int belowXY = below(xy);
        //		byte[] board = _boardModel.getSingleArray();
		
		if (_board[leftXY]==EMPTY &&
            (_chain[left(leftXY)]==chain || _chain[left(aboveXY)]==chain || _chain[left(belowXY)]==chain))
			shared++;
		if (_board[rightXY]==EMPTY &&
            (_chain[right(rightXY)]==chain || _chain[right(aboveXY)]==chain || _chain[right(belowXY)]==chain))
			shared++;
		if (_board[aboveXY]==EMPTY &&
            (_chain[above(aboveXY)]==chain || _chain[above(leftXY)]==chain || _chain[above(rightXY)]==chain))
			shared++;
		if (_board[belowXY]==EMPTY &&
            (_chain[below(belowXY)]==chain || _chain[below(leftXY)]==chain || _chain[below(rightXY)]==chain))
			shared++;
		return shared;
	}
	
//	public int getLiberty(int xy)
//	{
//		int stone = xy;
//		do
//		{
//			if (_board[left(stone)]==EMPTY)
//				return left(stone);
//			if (_board[right(stone)]==EMPTY)
//				return right(stone);
//			if (_board[above(stone)]==EMPTY)
//				return above(stone);
//			if (_board[below(stone)]==EMPTY)
//				return below(stone);
//			
//			stone = _chainNext[stone];
//		}
//		while (stone!=xy);
//        
//		return 0;
//	}

    int MonteCarloPluginAdministration::selectSimulationMove()
    {
        return selectSimulationMove(_emptyPoints);
    }

	int MonteCarloPluginAdministration::selectSimulationMove(PointSet& emptyPoints)
	{
//		int priorityMove = selectPriorityMove(_simulationMoveGeneratorList);
//		if (priorityMove!=PASS && priorityMove!=UNDEFINED_COORDINATE && isLegal(priorityMove))
//			return priorityMove;
//
//		return selectWeightedMoveCoordinate(emptyPoints, _simulationMoveFilterList);
        return selectRandomMoveCoordinate(emptyPoints);
	}

    int MonteCarloPluginAdministration::selectRandomMoveCoordinate(PointSet emptyPoints/*, List<MoveFilter> filterList*/)
	{
		assert(_illegalStack.isEmpty());
		while (emptyPoints.getSize()!=0)
		{
			int xy = emptyPoints.get(RANDOM.nextInt(emptyPoints.getSize()));
			if (!isVerboten(xy/*,filterList*/) && isLegal(xy))
			{
				while (!_illegalStack.isEmpty())
					emptyPoints.add(_illegalStack.pop());
				return xy;
			}
			emptyPoints.remove(xy);
			_illegalStack.push(xy);
		}
		while (!_illegalStack.isEmpty())
			emptyPoints.add(_illegalStack.pop());
        
		return PASS;
	}

    bool MonteCarloPluginAdministration::playout()
    {
        _inPlayout = true;
		while (true)
		{
			//assert(_probabilityMap.isConsistent());
			selectAndPlay();
            
            //_board.print();
            
			//assert (_emptyPoints.isConsistent(_board));
            
    		// Check some of the criteria that end a game.
			if (getNrPasses()>1)
			{
				_inPlayout = false;
				return (getScore()>0.0);
			}
			else if (USE_MERCY_RULE && exceedsMercyThreshold())
			{
				_inPlayout = false;
				return (getScoreEstimate()>0.0);
			}
			else if (isGameTooLong())
			{
				_inPlayout = false;
				return (getScoreEstimate()>0.0); // Should never happen.
			}
		}        
    }
    
    double MonteCarloPluginAdministration::getScore()
    {
    	double score = getScoreEstimate();
    	
    	for (int i=_emptyPoints.getSize(); --i>=0;)
    	{
    		int xy = _emptyPoints.get(i);
    		
    		assert (_board[xy]==EMPTY ); //: "\n" + GoArray.toString(_board) + "\n" + SGFUtil.createSGF(getMoveStack());
            //    		assert _boardModel.get(xy)==EMPTY : SGFUtil.createSGF(getMoveStack());
    		
    		if (_blackNeighbours[xy]==_neighbours[xy])
    		{
    			score++;
    			_black[xy] = 1;
    		}
    		else if (_whiteNeighbours[xy]==_neighbours[xy])
    		{
    			score--;
    			_white[xy] = 1;
    		}
    		else
    		{
                //    			score = score;
    		}
    	}
    	
    	return score;
        
    }
    
	/**
	 * This sets the aliases of the neighbouring arrays so that 'ownNeighbours' has
	 * the neighbours of the color to play and 'otherNeighbours' has the neighbours
	 * of the opposite color.
	 */
	void MonteCarloPluginAdministration::setNeighbourArrays()
	{
		if (_colorToPlay==BLACK)
		{
			_ownNeighbours = &_blackNeighbours;
			_otherNeighbours = &_whiteNeighbours;
			_ownDiagonalNeighbours = &_blackDiagonalNeighbours;
			_otherDiagonalNeighbours = &_whiteDiagonalNeighbours;
		}
		else
		{
			_ownNeighbours = &_whiteNeighbours;
			_otherNeighbours = &_blackNeighbours;
			_ownDiagonalNeighbours = &_whiteDiagonalNeighbours;
			_otherDiagonalNeighbours = &_blackDiagonalNeighbours;
		}
	}
	
};