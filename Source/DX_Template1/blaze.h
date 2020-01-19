#ifndef _BLAZE_H_
#define _BLAZE_H_

//-----------インクルード----------
#include "main.h"
#include "common.h"
#include "sprite.h"
#include "physics.h"

//------------定数マクロ--------------
#define BLAZE_WIDTH	(50)
#define BLAZE_HEIGHT (50)
//-----------クラス------------
class CBlaze {
public:
	void InitBlaze(D3DXVECTOR2 pos);
	void UninitBlaze();
	void UpdateBlaze();
	void DrawBlaze();
	int			m_time;
	D3DXVECTOR2 GetBlazePos();
private:
	CSprite		m_BlazeSprite;
	CPhysics	m_BlazePhysics;
	int 		m_BurnNum;
	float		m_rad;
};

//----------プロトタイプ------------
void InitBlaze();
void UninitBlaze();
void SetMousePos(int x, int y);
#endif // !1