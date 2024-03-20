
#ifndef GAMESANDBOX_TIC_TAC_TOE_AIPLAYER_H
#define GAMESANDBOX_TIC_TAC_TOE_AIPLAYER_H

namespace ABFramework
{
	class AIPlayer
	{
	public:

		// ----- Constructor / Destructor ----- //

		AIPlayer();
		~AIPlayer();

		// ----- Operators ----- //

		// ------ Utility ----- //

		void TakeAction(class GameBoard* _pBoard);
		struct TileData MiniMax(class GameBoard* _pBoard, bool _bAITurn, int _depth);
		int Max(int _currentMax, int _compare);
		int Min(int _currentMax, int _compare);

		// ----- Setters ----- //

		// ----- Getters ----- //

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_AIPLAYER_H


