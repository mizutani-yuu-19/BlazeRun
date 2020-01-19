#ifndef _LAMP_H_
#define _LAMP_H_

//------------インクルード------------
#include "main.h"
#include "common.h"
#include "sprite.h"
#include "physics.h"

//--------------定数マクロ-------------

//-------------クラス--------------
class CLamp {
public:
	void InitLamp(D3DXVECTOR2 pos, int num);
	void UninitLamp();
	void UpdateLamp();
	void DrawLamp();
	D3DXVECTOR2 GetLampPos();
	bool CollisionLamp(D3DXVECTOR2 pos, float r);
private:
	CSprite m_LampSprite;
	CSprite m_LampAnimSprite;
	CPhysics m_LampPhysics;
	int		m_num;
	int		m_burnNum;
	bool	m_bFall;
	int		m_col;
};

//----------プロトタイプ-----------
void InitLamp();
void UninitLamp();
void UpdateLamp();
void DrawLamp();
void CreateLamp(D3DXVECTOR2 pos);
bool CollisionLamp(D3DXVECTOR2 pos, float r);
#endif