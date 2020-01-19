#ifndef _OIL_H_
#define _OIL_H_
//---------インクルード--------
#include "main.h"
#include "common.h"
#include "sprite.h"

//---------クラス-----------
class COil {
public:
	void InitOil(D3DXVECTOR2 pos, int num);
	void UninitOil();
	void UpdateOil();
	void DrawOil();
	bool COil::CollisionOil(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight);
private:
	int			m_num;
	float		m_time;
	CSprite		m_OilSprite;

};
//---------プロトタイプ---------
void InitOil();
void UninitOil();
void CreateOil(D3DXVECTOR2 pos);
void UpdateOil();
void DrawOil();
bool CollisionOil(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight);


#endif // !_OIL_H_
