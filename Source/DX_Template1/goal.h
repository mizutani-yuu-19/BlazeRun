#ifndef _GOAL_H_
#define _GOAL_H_
//---------インクルード--------
#include "main.h"
#include "common.h"
#include "sprite.h"

//---------クラス-----------
class CGoal {
public:
	void InitGoal(D3DXVECTOR2 pos);
	void UninitGoal();
	void UpdateGoal();
	void DrawGoal();
	bool CollisionGoal(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight);
private:
	float		m_time;
	CSprite		m_GoalSprite;

};
//---------プロトタイプ---------
void InitGoal();
void UninitGoal();
void CreateGoal(D3DXVECTOR2 pos);
void UpdateGoal();
void DrawGoal();
bool CollisionGoal(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight);


#endif // !_GOAL_H_
