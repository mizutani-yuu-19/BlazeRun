//--------インクルード----------
#include "grass.h"
#include "burn.h"
#include "light.h"
#include "dynamite.h"
#include "collision.h"

//----------定数マクロ-----------
#define MAX_GRASS	(500)
#define TEXTURE_PASS_GRASS1			("data/texture/grass1.png")
#define TEXTURE_PASS_GRASS2			("data/texture/grass2.png")
#define TEXTURE_PASS_GRASS3			("data/texture/grass3.png")
#define TEXTURE_PASS_GRASS_FIRE		("data/texture/fire.png")

#define GRASS_WIDTH		(25)
#define GRASS_HEIGHT	(25)
//---------グローバル変数---------
// 草
static CGrass	g_grass[MAX_GRASS];
// 存在
static bool		g_bExist[MAX_GRASS];
// テクスチャ
static LPDIRECT3DTEXTURE9	g_pTextureGrass[3];
static LPDIRECT3DTEXTURE9	g_pTextureGrassFire;
//---------プロトタイプ-----------
//-------クラス------
void CGrass::InitGrass(D3DXVECTOR2 pos, int num, int pat, int numPat) {
	m_num = num;
	pos.y -= 12.5f;
	m_pos = pos;
	m_numPat = numPat;
	m_GrassSprite.InitSprite(pos, GRASS_WIDTH, GRASS_HEIGHT, 1, 1);
	if (numPat == 0) {
		pos.x += 10;
	}
	else if (numPat == 2) {
		pos.x -= 10;
	}
	m_GrassSpriteFire.InitSprite(pos, GRASS_WIDTH, GRASS_HEIGHT, 5, 5);
	
	// 可燃性
	m_burnNum = CreateBurn(pos, GRASS_WIDTH, GRASS_HEIGHT, false);
	if (pat == 1) {
		m_GrassSprite.m_scale.y *= -1;
		m_GrassSpriteFire.m_scale.y *= -1;
	}
}

void CGrass::UninitGrass() {
	g_bExist[m_num] = false;
	DeleteBurn(m_burnNum);
	m_burnNum = 999;
}

void CGrass::UpdateGrass() {
	// 位置更新
	m_pos.x -= g_scrollSpeed;
	m_GrassSprite.m_pos.x = m_GrassSpriteFire.m_pos.x = m_pos.x;
	m_count++;
	m_GrassSpriteFire.m_patNum = m_count / 3 % 25;
	SetBurnPos(m_burnNum, m_pos);
	if (m_pos.x < VANISHING_POINT) {
		UninitGrass();
	}
}

void CGrass::DrawGrass() {
	SetRenderMode(BLEND_TRANSLUCENT);
	m_GrassSprite.DrawSprite(g_pTextureGrass[m_numPat]);
	if (GetBurn(m_burnNum)) {
		m_GrassSpriteFire.DrawSprite(g_pTextureGrassFire);
		if (!g_bDeleteLight)
			SetLight(m_GrassSpriteFire.m_pos, D3DXVECTOR2(3, 3));
	}
}

//----------関数-----------/
void InitGrass() {
	g_pTextureGrass[0] = SetTexture(TEXTURE_PASS_GRASS1);
	g_pTextureGrass[1] = SetTexture(TEXTURE_PASS_GRASS2);
	g_pTextureGrass[2] = SetTexture(TEXTURE_PASS_GRASS3);
	g_pTextureGrassFire = SetTexture(TEXTURE_PASS_GRASS_FIRE);
}

void UninitGrass() {
	for (int i = 0; i < MAX_GRASS; i++)
		g_bExist[i] = false;
	for (int i = 0; i < 3; i++) {
		g_pTextureGrass[i]->Release();
		g_pTextureGrass[i] = NULL;
	}
	g_pTextureGrassFire->Release();
	g_pTextureGrassFire = NULL;
}

void UpdateGrass() {
	for (int i = 0; i < MAX_GRASS; i++) {
		if (!g_bExist[i])	continue;

		g_grass[i].UpdateGrass();
	}

}

void DrawGrass() {
	for (int i = 0; i < MAX_GRASS; i++) {
		if (!g_bExist[i])	continue;
		g_grass[i].DrawGrass();
	}
}

void CreateGrass(D3DXVECTOR2 pos, float width, int pat) {
	int grassNum = width / GRASS_WIDTH;
	pos.x += GRASS_WIDTH / 2.0f;
	for (int j = 0; j < grassNum; j++) {
		int numPat = 1;
		if (j == 0) {
			numPat = 0;
		}
		else if (j == grassNum - 1) {
			numPat = 2;
		}
		for (int i = 0; i < MAX_GRASS; i++) {
			if (g_bExist[i])	continue;
			g_bExist[i] = true;
			g_grass[i].InitGrass(pos, i, pat, numPat);
			pos.x += GRASS_WIDTH;
			break;
		}
	}
}