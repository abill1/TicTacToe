
#ifndef GAMESANDBOX_TIC_TAC_TOE_GAME_BOARD_H
#define GAMESANDBOX_TIC_TAC_TOE_GAME_BOARD_H

#include "../Engine/Core/GameObject/GameObject.h"
#include "Tile/Tile.h"

namespace ABFramework
{
	class GameBoard : public GameObject 
	{
	public:
		enum class Position : int 
		{
			TOP_LEFT = 0,
			TOP_CENTER = 1,
			TOP_RIGHT = 2,
			MID_LEFT = 3,
			MID_CENTER = 4,
			MID_RIGHT = 5,
			BOTTOM_LEFT = 6,
			BOTTOM_CENTER = 7,
			BOTTOM_RIGHT = 8
		};

	public:
		
		// ----- Constructor / Destructor ----- //

		GameBoard();
		virtual ~GameBoard();

		// ------ Utility ----- //

		virtual void Update() override;
		virtual void Draw(const Matrix& _viewProj) override;
		void ClearBoard();

		// ----- Setters ----- //

		virtual void SetPosition(const Point3D& _position) override {}
		virtual void SetScale(const Scale& _scale) override {}
		virtual void SetScale(float _scale) override {}
		virtual void SetTexture(class Texture* const _pTexture) override {}
		virtual void SetTexture(size_t _handle)override {}
		virtual void SetMesh(class Mesh* _pMesh) override {}
		void MarkTile(GameBoard::Position _index, Tile::State _piece);

		// ----- Getters ----- //

		virtual class AABB* GetCollider() const override { return nullptr; }
		Tile* GetTile(int _index);
		Tile* GetTile(int _row, int _col);
		Tile* GetTile(GameBoard::Position _index);
		TileData* GetTileData();
		bool IsFull();
		inline const int GetBoardSize() const { return BOARD_SIZE; }

	private:
		const int BOARD_SIZE = 9;
		Tile* pTiles;
		TileData* pData;
		int m_CurrentEmptyTiles;
	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_GAME_BOARD_H



