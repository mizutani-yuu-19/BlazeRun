#ifndef _BOARD_H_
#define _BOARD_H_

//--------インクルード---------
#include "main.h"
#include "common.h"
#include "sprite.h"

//--------クラス---------
class CBoard
{
public:
	void CBoard::InitBoard(D3DXVECTOR2 pos, int num,int pat);
	void UninitBoard();
	void UpdateBoard();
	void DrawBoard();

	float CollisionBoard(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight);

	D3DXVECTOR2 GetPos();
private:
	float			m_width;
	int				m_num;
	CSprite			m_BoardSprite;
	CSprite			m_BoardSpriteAnim;
	int m_BurnNum;
	int m_pat;
	int m_animTime;
	bool m_bExplosion;
};

//---------プロトタイプ--------
void InitBoard();
void UninitBoard();
void UpdateBoard();
void DrawBoard();
float CollisionBoard(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight);
void CreateBoard(D3DXVECTOR2 pos, int pat);


#endif // !_BOARD_H_
