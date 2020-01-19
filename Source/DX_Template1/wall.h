#ifndef _WALL_H_
#define _WALL_H_

//-------------�C���N���[�h--------------
#include "main.h"
#include "common.h"
#include "sprite.h"

//---------------�N���X---------------
class CWall {
public:
	void InitWall(D3DXVECTOR2 pos,int num);
	void UninitWall();
	void UpdateWall();
	void DrawWall();
	int CollisionWall(D3DXVECTOR2 *PlayerPos, float PlayerWidth, float PlayerHeight);

private:
	CSprite m_WallSprite;
	CSprite m_WallAnimSprite;
	int m_animCnt;
	int m_num;
	bool m_bDest;
};

//-------------�v���g�^�C�v------------
void InitWall();
void UninitWall();
void UpdateWall();
void DrawWall(); 
void CreateWall(D3DXVECTOR2 pos);
int CollisionWall(D3DXVECTOR2 *PlayerPos, float PlayerWidth, float PlayerHeight);

#endif // !_WALL_H_
