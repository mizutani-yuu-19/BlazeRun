#include "clear.h"
#include "input.h"
#include "collision.h"

#define CLEAR_WIDTH (900)
#define CLEAR_HEIGHT (500)
#define EXIT_WIDTH (300)
#define EXIT_HEIGHT (80)
#define CLEAR_FALL_SPEED (10)

static LPDIRECT3DTEXTURE9 g_textureClear;
static LPDIRECT3DTEXTURE9 g_textureExit;
static LPDIRECT3DTEXTURE9 g_textureNext;
static CSprite g_spriteClear;
static CSprite g_spriteExit;
static CSprite g_spriteNext;
static bool g_bClearPush;
static int g_pushNum;

void InitClear() {
	g_textureClear = SetTexture("data/texture/clear.png");
	g_textureExit = SetTexture("data/texture/exit.png");
	g_textureNext = SetTexture("data/texture/next.png");
	g_spriteClear.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, -CLEAR_HEIGHT / 2.0f), CLEAR_WIDTH, CLEAR_HEIGHT, 1, 1);
	g_spriteExit.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, -70), EXIT_WIDTH, EXIT_HEIGHT, 1, 1);
	g_spriteExit.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_spriteNext.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, -170), EXIT_WIDTH, EXIT_HEIGHT, 1, 1);
	g_spriteNext.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_bClearPush = false;
}

void UninitClear() {
	g_textureClear->Release();
	g_textureClear = NULL;
	g_textureNext->Release();
	g_textureNext = NULL;
	g_textureExit->Release();
	g_textureExit = NULL;
}

void UpdateClear() {
	if (GetGameClear() && !g_bClearPush) {
		static bool once;
		if (!once) {
			StopSound();
			if (GetScene() != SCENE_TUTORIAL)
				PlaySound(SOUND_LABEL_SE_CLEAR);
			once = true;
		}
		bool bHoverExit;
		bool bHoverNext;
		if (bHoverExit = CollisionRect(GetMousePos().x, GetMousePos().y, 1, 1, g_spriteExit.m_pos.x - EXIT_WIDTH / 2, g_spriteExit.m_pos.y - EXIT_HEIGHT / 2, EXIT_WIDTH, EXIT_HEIGHT)) {
			g_spriteExit.m_color = D3DCOLOR_RGBA(200, 200, 200, 255);
		}
		else {
			g_spriteExit.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		if (bHoverNext = CollisionRect(GetMousePos().x, GetMousePos().y, 1, 1, g_spriteNext.m_pos.x - EXIT_WIDTH / 2, g_spriteNext.m_pos.y - EXIT_HEIGHT / 2, EXIT_WIDTH, EXIT_HEIGHT)) {
			g_spriteNext.m_color = D3DCOLOR_RGBA(200, 200, 200, 255);
		}
		else {
			g_spriteNext.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		if (g_spriteClear.m_pos.y < SCREEN_CENTER_Y) {
			g_spriteClear.m_pos.y += CLEAR_FALL_SPEED;
			g_spriteExit.m_pos.y += CLEAR_FALL_SPEED;
			if (GetScene() != SCENE_STAGE3)
				g_spriteNext.m_pos.y += CLEAR_FALL_SPEED;
		}
		else if (DIGetMouseTrigger(0) && bHoverNext) {
			g_bClearPush = true;
			g_pushNum = 1;
			once = false;
		}
		else if (DIGetMouseTrigger(0) && bHoverExit) {
			g_bClearPush = true;
			g_pushNum = 2;
			once = false;
		}
	}
}

void DrawClear() {
	if (GetGameClear()) {
		SetRenderMode(BLEND_TRANSLUCENT);
		g_spriteClear.DrawSprite(g_textureClear);
		g_spriteExit.DrawSprite(g_textureExit);
		g_spriteNext.DrawSprite(g_textureNext);
	}
}

bool GetClearPush() {
	return g_bClearPush;
}

void SetClearPush(bool flag) {
	g_bClearPush = flag;
}
int GetClearPushNum() {
	return g_pushNum;
}
void SetClearPushNum(int num) {
	g_pushNum = num;
}