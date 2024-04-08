
#include "TicTacToe/TicTacToe.h"

int main(int argc, char* argv[])
{
	ABFramework::MemoryTracker::Init();
    ABFramework::Code retCode = ABFramework::Code::SUCCESS;
	ABFramework::TicTacToe game("Tic Tac Toe", 1200, 900);
	retCode = game.Run();
	return (int)retCode;
}

