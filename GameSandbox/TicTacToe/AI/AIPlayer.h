
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
		struct TileData MiniMax(struct TileData* _pData, bool _bAITurn, int _depth);
		int Max(int _currentMax, int _compare);
		int Min(int _currentMax, int _compare);

		// ----- Setters ----- //

		// ----- Getters ----- //

	private:
		bool privCheckForWin();
		bool privTestRowWin();
		bool privTestColWin();
		bool privTestDiagonalWin();
		bool privTestDraw();

	private:
		const int HUMAN_WIN = -1;
		const int AI_WIN = 1;
		const int DRAW = 0;
		struct TileData* pData;

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_AIPLAYER_H


