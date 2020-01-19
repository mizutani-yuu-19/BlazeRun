#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

//------------インクルード------------
#include "main.h"
#include "common.h"
#include "sprite.h"

//--------------定数マクロ-------------
#define DYNAMITE_EXPLOSION_SIZE	(100)
//-------------クラス--------------
class CDynamite {
public:
	void InitDynamite(D3DXVECTOR2 pos, int num);
	void UninitDynamite();
	void UpdateDynamite();
	void DrawDynamite();
	D3DXVECTOR2 CDynamite::GetDynamitePos();
	bool m_bExplosion;
private:
	CSprite m_DynamiteSprite;
	CSprite m_DynamiteExplosionSprite;
	int		m_num;
	int		m_burnNum;
	int		m_burnTime;
	
};

//----------プロトタイプ-----------
void InitDynamite();
void UninitDynamite();
void UpdateDynamite();
void DrawDynamite();
void CreateDynamite(D3DXVECTOR2 pos);
D3DXVECTOR2 GetDynamiteExplosionPos(int num);
#endif