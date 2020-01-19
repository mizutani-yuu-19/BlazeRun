#ifndef _GRASS_H_
#define _GRASS_H_
//-------�C���N���[�h---------
#include "main.h"
#include "common.h"
#include "sprite.h"

//-------�N���X----------
class CGrass {
public:
	void InitGrass(D3DXVECTOR2 pos,int num, int pat,int numPat);
	void UninitGrass();
	void UpdateGrass();
	void DrawGrass();

private:
	int m_num;
	int m_burnNum;
	D3DXVECTOR2	m_pos;
	CSprite	m_GrassSprite;
	CSprite	m_GrassSpriteFire;
	int m_count;
	int m_pat;	// �㉺��������
	int m_numPat;	//123 
};

//-------�v���g�^�C�v--------
void InitGrass();
void UninitGrass();
void UpdateGrass();
void DrawGrass();

void CreateGrass(D3DXVECTOR2 pos,float width,int pat);

#endif // !_GRASS_H_
