//------------インクルード------------
#include "lamp.h"
#include "burn.h"
#include "light.h"
#include "wall.h"
#include "blaze.h"
#include "player.h"
#include "collision.h"
#include "ground.h"
#include "oil.h"
#include "board.h"

//-----------定数マクロ-----------
#define MAX_LAMP	(10)
#define LAMP_WIDTH	(80)
#define LAMP_HEIGHT	(80)

//-----------グローバル変数------------
static CLamp	g_lamp[MAX_LAMP];
static bool			g_bExist[MAX_LAMP];
static LPDIRECT3DTEXTURE9 g_pTextureLamp;
static LPDIRECT3DTEXTURE9 g_pTextureLampAnim;

//-------------クラス--------------
void CLamp::InitLamp(D3DXVECTOR2 pos, int num) {
	pos.x += LAMP_WIDTH / 2;
	pos.y -= LAMP_HEIGHT / 2;
	m_LampSprite.InitSprite(pos, LAMP_WIDTH, LAMP_HEIGHT, 1, 1);
	m_num = num;
	m_burnNum = CreateBurn(m_LampSprite.m_pos, LAMP_WIDTH, LAMP_HEIGHT, true);
	m_LampPhysics.InitPhysics(D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	m_col = 0;
}

void CLamp::UninitLamp() {
	g_bExist[m_num] = false;
	DeleteBurn(m_burnNum);
}

void CLamp::UpdateLamp() {
	m_LampSprite.m_pos.x -= g_scrollSpeed;
	if (m_bFall) {
		m_LampPhysics.Gravity();
		m_LampPhysics.PosCalc(&m_LampSprite.m_pos);
	}
	SetBurnPos(m_burnNum, m_LampSprite.m_pos);
	if (m_col == 0) {
		// 落下中、物に当たったら
		if (CollisionBoard(m_LampSprite.m_pos, LAMP_WIDTH, LAMP_HEIGHT) != 999) {
			m_LampAnimSprite.InitSprite(m_LampSprite.m_pos, LAMP_WIDTH, LAMP_HEIGHT, 2, 1);
			CreateOil(m_LampSprite.m_pos);
			UpdateBurn();
			m_col = 1;
			m_bFall = false;
			PlaySound(SOUND_LABEL_SE_LAMP);
		}
		else if (CollisionGround(&m_LampSprite.m_pos, LAMP_WIDTH, LAMP_HEIGHT)) {
			m_LampAnimSprite.InitSprite(m_LampSprite.m_pos, LAMP_WIDTH, LAMP_HEIGHT, 2, 1);
			CreateOil(m_LampSprite.m_pos);
			UpdateBurn();
			m_bFall = false;
			m_col = 1;
			PlaySound(SOUND_LABEL_SE_LAMP);
		}
		else if (CollisionWall(&m_LampSprite.m_pos, LAMP_WIDTH, LAMP_HEIGHT)) {
			m_LampAnimSprite.InitSprite(m_LampSprite.m_pos, LAMP_WIDTH, LAMP_HEIGHT, 2, 1);
			CreateOil(m_LampSprite.m_pos);
			UpdateBurn();
			m_bFall = false;
			m_col = 1;
			PlaySound(SOUND_LABEL_SE_LAMP);
		}
	}
	if (m_col > 0) {
		m_LampAnimSprite.m_pos.x -= g_scrollSpeed;
		m_col++;
		m_LampAnimSprite.m_patNum = m_col % 16 / 8;
		if (m_col >= 16) {
			UninitLamp();
		}
	}
	// 画面外
	if (m_LampSprite.m_pos.x < VANISHING_POINT) {
		UninitLamp();
	}
}

void CLamp::DrawLamp() {
	if (m_col == 0)
		m_LampSprite.DrawSprite(g_pTextureLamp);
	else
		m_LampAnimSprite.DrawSprite(g_pTextureLampAnim);
	if (!g_bDeleteLight)
		SetLight(m_LampSprite.m_pos, D3DXVECTOR2(4, 4));
}

D3DXVECTOR2 CLamp::GetLampPos() {
	return m_LampSprite.m_pos;
}

bool CLamp::CollisionLamp(D3DXVECTOR2 pos, float r) {
	if (CollisionCircle(pos.x, pos.y, BLAZE_WIDTH, m_LampSprite.m_pos.x, m_LampSprite.m_pos.y, LAMP_WIDTH)) {
		m_bFall = true;
		return true;
	}
	return false;
}
//----------関数-----------
void InitLamp() {
	g_pTextureLamp = SetTexture("data/texture/lamp.png");
	g_pTextureLampAnim = SetTexture("data/texture/lamp_anim.png");
}

void UninitLamp() {
	for (int i = 0; i < MAX_LAMP; i++)
		g_bExist[i] = false;
	g_pTextureLamp->Release();
	g_pTextureLamp = NULL;
}

void UpdateLamp() {
	for (int i = 0; i < MAX_LAMP; i++) {
		// 使用していたら更新
		if (!g_bExist[i])	continue;
		g_lamp[i].UpdateLamp();
	}
}

void DrawLamp() {
	for (int i = 0; i < MAX_LAMP; i++) {
		if (!g_bExist[i])	continue;
		g_lamp[i].DrawLamp();
	}
}

void CreateLamp(D3DXVECTOR2 pos) {
	for (int i = 0; i < MAX_LAMP; i++) {
		if (g_bExist[i])		continue;

		g_lamp[i].InitLamp(pos, i);
		g_bExist[i] = true;
		return;
	}
}

bool CollisionLamp(D3DXVECTOR2 pos, float r) {
	for (int i = 0; i < MAX_LAMP; i++) {
		if (!g_bExist[i])		continue;

		if (g_lamp[i].CollisionLamp(pos, r)) {
			return true;
		}
	}
	return false;
}
