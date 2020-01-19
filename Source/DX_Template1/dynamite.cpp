//------------インクルード------------
#include "dynamite.h"
#include "burn.h"
#include "light.h"
#include "wall.h"

//-----------定数マクロ-----------
#define MAX_DYNAMITE	(10)
#define DYNAMITE_WIDTH	(50)
#define DYNAMITE_HEIGHT	(50)
#define DYNAMITE_EXPLOSION_WIDTH (300)
#define DYNAMITE_EXPLOSION_HEIGHT (300)

//-----------グローバル変数------------
static CDynamite	g_dynamite[MAX_DYNAMITE];
static bool			g_bExist[MAX_DYNAMITE];
static LPDIRECT3DTEXTURE9 g_pTextureDynamite;
static LPDIRECT3DTEXTURE9 g_pTextureExplosion;

//-------------クラス--------------
void CDynamite::InitDynamite(D3DXVECTOR2 pos, int num) {
	pos.x += DYNAMITE_WIDTH / 2;
	pos.y -= DYNAMITE_HEIGHT / 2;
	m_DynamiteSprite.InitSprite(pos, DYNAMITE_WIDTH, DYNAMITE_HEIGHT, 1, 1);
	m_DynamiteExplosionSprite.InitSprite(pos, DYNAMITE_EXPLOSION_WIDTH, DYNAMITE_EXPLOSION_HEIGHT, 8, 2);
	m_num = num;
	m_burnNum = CreateBurn(m_DynamiteSprite.m_pos, DYNAMITE_WIDTH, DYNAMITE_HEIGHT, false);
}

void CDynamite::UninitDynamite() {
	g_bExist[m_num] = false;
	DeleteBurn(m_burnNum);
	m_burnTime = 0;
	m_bExplosion = false;
}

void CDynamite::UpdateDynamite() {
	m_DynamiteSprite.m_pos.x -= g_scrollSpeed;
	SetBurnPos(m_burnNum, m_DynamiteSprite.m_pos);
	// 火がついたら
	if (GetBurn(m_burnNum)) {
		if (m_burnTime == 0) {
			PlaySound(SOUND_LABEL_SE_DYNAMITE);
		}
		m_bExplosion = true;
		m_DynamiteExplosionSprite.m_patNum = m_burnTime/5;
		m_DynamiteExplosionSprite.m_pos = m_DynamiteSprite.m_pos;
		if (m_burnTime == 75) {
			UninitDynamite();
			return;
		}
		m_burnTime++;
	}
	// 画面外
	if (m_DynamiteSprite.m_pos.x < VANISHING_POINT) {
		UninitDynamite();
	}
}

void CDynamite::DrawDynamite() {
	SetRenderMode(BLEND_TRANSLUCENT);
	if (GetBurn(m_burnNum)) {
		m_DynamiteExplosionSprite.DrawSprite(g_pTextureExplosion);
		if (!g_bDeleteLight)
			SetLight(m_DynamiteSprite.m_pos, D3DXVECTOR2(3, 3));
	}
	else m_DynamiteSprite.DrawSprite(g_pTextureDynamite);
}

D3DXVECTOR2 CDynamite::GetDynamitePos() {
	return m_DynamiteSprite.m_pos;
}

//----------関数-----------
void InitDynamite() {
	g_pTextureDynamite = SetTexture("data/texture/dynamite.png");
	g_pTextureExplosion = SetTexture("data/texture/explosion.png");
}

void UninitDynamite() {
	for (int i = 0; i < MAX_DYNAMITE; i++)
		g_bExist[i] = false;
	g_pTextureDynamite->Release();
	g_pTextureDynamite = NULL;
	g_pTextureExplosion->Release();
	g_pTextureExplosion = NULL;
}

void UpdateDynamite() {
	for (int i = 0; i < MAX_DYNAMITE; i++) {
		// 使用していたら更新
		if (!g_bExist[i])	continue;
		g_dynamite[i].UpdateDynamite();
	}
}

void DrawDynamite() {
	for (int i = 0; i < MAX_DYNAMITE; i++) {
		if (!g_bExist[i])	continue;
		g_dynamite[i].DrawDynamite();
	}
}

void CreateDynamite(D3DXVECTOR2 pos) {
	for (int i = 0; i < MAX_DYNAMITE; i++) {
		if (g_bExist[i])		continue;

		g_dynamite[i].InitDynamite(pos, i);
		g_bExist[i] = true;
		return;
	}
}

D3DXVECTOR2 GetDynamiteExplosionPos(int num) {
	int cnt = 0;
	for (int i = 0; i < MAX_DYNAMITE; i++) {
		if (!g_bExist[i])	continue;
		if (!g_dynamite[i].m_bExplosion)	continue;
		if (cnt == num) {
			return g_dynamite[i].GetDynamitePos();
		}
		cnt++;
	}
	return D3DXVECTOR2(0, 0);
}