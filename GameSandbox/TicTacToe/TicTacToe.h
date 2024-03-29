
#ifndef GAMESANDBOX_TIC_TAC_TOE_H
#define GAMESANDBOX_TIC_TAC_TOE_H

#include "../Engine/Game/Game.h"

namespace ABFramework
{

	class TicTacToe : public Game 
	{
	public:

		// ----- Constructor / Destructor ----- //

		TicTacToe(const char* _pName, int _width, int _height);
		virtual ~TicTacToe();

		// ----- Operators ----- //

		// ------ Utility ----- //

		virtual void InitializeSystems() override;
		virtual void LoadContent() override;
		virtual void UnloadContent() override;
		virtual void CloseSystems() override;
		virtual void Update() override;
		virtual void Draw() override;

		// ----- Setters ----- //

		// ----- Getters ----- //
		
	private:

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_H


