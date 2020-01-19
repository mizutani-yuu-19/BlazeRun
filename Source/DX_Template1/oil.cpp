//--------�C���N���[�h--------
#include "oil.h"
#include "collision.h"
#include "main.h"

//----------�萔�}�N��-----------
#define MAX_OIL	(10)

#define OIL_WIDTH (40)
#define OIL_HEIGHT (40)

//----------�O���[�o���ϐ�------------
static COil	g_Oil[MAX_OIL];
static LPDIRECT3DTEXTURE9	g_pTextureOil;
static bool	g_bExist[MAX_OIL];


//-----------���\�b�h--------------
void COil::InitOil(D3DXVECTOR2 pos, int num) {
	m_OilSprite.InitSprite(pos, OIL_WIDTH, OIL_HEIGHT, 1, 1);
	m_num = num;
}

void COil::UninitOil() {
	g_bExist[m_num] = false;
}

void COil::UpdateOil() {
	m_time++;
	// �X�N���[���ɍ��킹�Ĉړ�
	m_OilSprite.m_pos.x -= g_scrollSpeed + 2;
	// �T�C���J�[�u
	m_OilSprite.m_pos.y += sin(m_time / 10.0f)*3.0f;
	if (m_OilSprite.m_pos.x < VANISHING_POINT) {
		UninitOil();
	}
}

void COil::DrawOil() {
	SetRenderMode(BLEND_TRANSLUCENT);
	m_OilSprite.DrawSprite(g_pTextureOil);
}

bool COil::CollisionOil(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight) {
	if (CollisionRect(PlayerPos.x - PlayerWidth / 2.0f, PlayerPos.y - PlayerHeight / 2.0f, PlayerWidth, PlayerHeight, m_OilSprite.m_pos.x - OIL_WIDTH / 2.0f, m_OilSprite.m_pos.y - OIL_HEIGHT / 2.0f, OIL_WIDTH, OIL_HEIGHT)) {
		UninitOil();
		return true;
	}
	return false;
}

//===============�֐�=================
void InitOil(void) {
	g_pTextureOil = SetTexture("data/texture/oil.png");
}

void UninitOil(void) {
	for (int i = 0; i < MAX_OIL; i++)
		g_bExist[i] = false;
	g_pTextureOil->Release();
	g_pTextureOil = NULL;
}

void UpdateOil() {
	for (int i = 0; i < MAX_OIL; i++) {
		// �g�p���Ă�����X�V
		if (!g_bExist[i])	continue;
		g_Oil[i].UpdateOil();
	}
}


void DrawOil() {
	for (int i = 0; i < MAX_OIL; i++) {
		if (!g_bExist[i])	continue;
		g_Oil[i].DrawOil();
	}
}

void CreateOil(D3DXVECTOR2 pos) {
	for (int i = 0; i < MAX_OIL; i++) {
		if (g_bExist[i])		continue;

		g_Oil[i].InitOil(pos, i);
		g_bExist[i] = true;
		return;
	}
}

bool CollisionOil(D3DXVECTOR2 PlayerPos, float PlayerWidth, float PlayerHeight) {
	for (int i = 0; i < MAX_OIL; i++) {
		if (!g_bExist[i])		continue;
		bool work = g_Oil[i].CollisionOil(PlayerPos, PlayerWidth, PlayerHeight);
		if (work)
			return work;
	}
	return false;
}