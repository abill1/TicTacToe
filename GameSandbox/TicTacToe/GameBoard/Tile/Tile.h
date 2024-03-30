
#ifndef GAMESANDBOX_TIC_TAC_TOE_GAMEBOARD_TILE_H
#define GAMESANDBOX_TIC_TAC_TOE_GAMEBOARD_TILE_H

#include "../../Engine/Core/GameObject/GameObject.h"

namespace ABFramework
{
	class Texture;
	class Sprite;

	struct TileData
	{
		int m_boardPosition;
		int m_State;
		int m_weight;
	};

	class Tile
	{
	public:

		enum class State : int
		{
			EMPTY,
			X,
			O
		};

		// ----- Constructor / Destructor ----- //

		Tile();
		~Tile();

		// ----- Operators ----- //

		// ------ Utility ----- //

		void Update();
		void Draw(const Matrix& _viewProj);

		// ----- Setters ----- //

		void SetPosition(const Point3D& _position);
		void SetScale(float _scale);
		bool SetState(State _state);
		void SetTileData(Point2D _pos, float _weight);
		void SetTileEmpty();

		// ----- Getters ----- //

		class AABB* GetCollider() const;
		inline State GetState() const { return m_State; }
		inline TileData GetTileData() const { return m_Data; }

	private:
		TileData m_Data;
		Sprite* pSprite;
		State m_State;
		const char* const X_TEXTURE = "XSquare";
		const char* const O_TEXTURE = "OSquare";
		const char* const EMPTY_TEXTURE = "Empty";

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_GAMEBOARD_TILE_H


