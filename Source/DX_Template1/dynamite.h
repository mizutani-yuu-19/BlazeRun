#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

//------------�C���N���[�h------------
#include "main.h"
#include "common.h"
#include "sprite.h"

//--------------�萔�}�N��-------------
#define DYNAMITE_EXPLOSION_SIZE	(100)
//-------------�N���X--------------
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

//----------�v���g�^�C�v-----------
void InitDynamite();
void UninitDynamite();
void UpdateDynamite();
void DrawDynamite();
void CreateDynamite(D3DXVECTOR2 pos);
D3DXVECTOR2 GetDynamiteExplosionPos(int num);
#endif