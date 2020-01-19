#ifndef _GROUND_H_
#define _GROUND_H_

//-------------インクルード--------------
#include "main.h"
#include "common.h"
#include "sprite.h"

//---------------クラス---------------
class CGround {
public:
	void InitGround(D3DXVECTOR2 pos, int pat,int num);
	void UninitGround();
	void UpdateGround();
	void DrawGround();
	int CollisionGround(D3DXVECTOR2 *PlayerPos, float PlayerWidth, float PlayerHeight);

private:
	CSprite m_GroundSprite;
	int m_num;
	int m_pat;
};

//-------------プロトタイプ------------
void InitGround();
void UninitGround();
void UpdateGround();
void DrawGround(); 
void CreateGround(D3DXVECTOR2 pos,float width);
int CollisionGround(D3DXVECTOR2 *PlayerPos, float PlayerWidth, float PlayerHeight);

#endif // !_GROUND_H_
