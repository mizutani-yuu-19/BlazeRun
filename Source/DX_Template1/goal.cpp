//--------�C���N���[�h--------
#include "goal.h"
#include "collision.h"
#include "main.h"
#include "light.h"

//----------�萔�}�N��-----------
#define GOAL_WIDTH (400)
#define GOAL_HEIGHT (700)

//----------�O���[�o���ϐ�------------
static CGoal	g_Goal;
static LPDIRECT3DTEXTURE9	g_pTextureGoal;
static bool	g_bExist;


//-----------���\�b�h--------------
void CGoal::InitGoal(D3DXVECTOR2 pos) {
	m_GoalSprite.InitSprite(pos, GOAL_WIDTH, GOAL_HEIGHT, 4, 1);
}

void CGoal::UninitGoal() {
}

void CGoal::UpdateGoal() {
	m_time++;
	// �X�N���[���ɍ��킹�Ĉړ�
	m_GoalSprite.m_pos.x -= g_scrollSpeed;
	m_GoalSprite.m_patNum = (int)m_time % 20 / 5;
}

void CGoal::DrawGoal() {
	SetRenderMode(BLEND_TRANSLUCENT);
	m_GoalSprite.DrawSprite(g_pTextureGoal);
	if (!g_bDeleteLight)
		SetLight(m_GoalSprite.m_pos, D3DXVECTOR2(5, 20));
}

bool CGoal::CollisionGoal(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight) {
	if (CollisionRect(PlayerPos.x - PlayerWidth / 2.0f, PlayerPos.y - PlayerHeight / 2.0f, PlayerWidth, PlayerHeight, m_GoalSprite.m_pos.x - (GOAL_WIDTH-300) / 2.0f, m_GoalSprite.m_pos.y - GOAL_HEIGHT / 2.0f, GOAL_WIDTH-300, GOAL_HEIGHT)) {
		UninitGoal();
		return true;
	}
	return false;
}

//===============�֐�=================
void InitGoal(void) {
	g_pTextureGoal = SetTexture("data/texture/goal.png");
}

void UninitGoal(void) {
	g_bExist = false;
	g_pTextureGoal->Release();
	g_pTextureGoal = NULL;
}

void UpdateGoal() {
	// �g�p���Ă�����X�V
	if (!g_bExist)	return;
	g_Goal.UpdateGoal();
}


void DrawGoal() {
	// �g�p���Ă�����`��
	if (!g_bExist)	return;
	g_Goal.DrawGoal();
}

void CreateGoal(D3DXVECTOR2 pos) {
	if (g_bExist)	return;

	g_Goal.InitGoal(pos);
	g_bExist = true;
	return;
}

bool CollisionGoal(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight) {
	if (!g_bExist)	return false;
	return 	g_Goal.CollisionGoal(PlayerPos, PlayerWidth, PlayerHeight);
}