#include "gameover.h"
#include "input.h"
#include "collision.h"

#define CLEAR_WIDTH (900)
#define CLEAR_HEIGHT (500)
#define EXIT_WIDTH (300)
#define EXIT_HEIGHT (80)
#define CLEAR_FALL_SPEED (10)

static LPDIRECT3DTEXTURE9 g_textureGameOver;
static LPDIRECT3DTEXTURE9 g_textureExit;
static LPDIRECT3DTEXTURE9 g_textureRetry;
static CSprite g_spriteGameOver;
static CSprite g_spriteExit;
static CSprite g_spriteRetry;
static bool g_bGameOverPush;
static int g_pushNum;
void InitGameOver() {
	g_textureGameOver = SetTexture("data/texture/gameover.png");
	g_textureExit = SetTexture("data/texture/exit.png");
	g_textureRetry = SetTexture("data/texture/retry.png");
	g_spriteGameOver.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, -CLEAR_HEIGHT / 2.0f), CLEAR_WIDTH, CLEAR_HEIGHT, 1, 1);
	g_spriteRetry.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, -170), EXIT_WIDTH, EXIT_HEIGHT, 1, 1);
	g_spriteRetry.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_spriteExit.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, -70), EXIT_WIDTH, EXIT_HEIGHT, 1, 1);
	g_spriteExit.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_bGameOverPush = false;
}

void UninitGameOver() {
	g_textureGameOver->Release();
	g_textureExit->Release();
	g_textureGameOver = NULL;
	g_textureExit = NULL;
}

void UpdateGameOver() {
	if (GetGameOver()&&!g_bGameOverPush) {
		static bool once;
		if (!once) {
			StopSound();
			PlaySound(SOUND_LABEL_SE_MISS);
			once = true;
		}
		bool bHoverExit;
		bool bHoverRetry;
		if (bHoverExit = CollisionRect(GetMousePos().x, GetMousePos().y, 1, 1, g_spriteExit.m_pos.x - EXIT_WIDTH / 2, g_spriteExit.m_pos.y - EXIT_HEIGHT / 2, EXIT_WIDTH, EXIT_HEIGHT)) {
			g_spriteExit.m_color = D3DCOLOR_RGBA(200, 200, 200, 255);
		}
		else {
			g_spriteExit.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		if (bHoverRetry = CollisionRect(GetMousePos().x, GetMousePos().y, 1, 1, g_spriteRetry.m_pos.x - EXIT_WIDTH / 2, g_spriteRetry.m_pos.y - EXIT_HEIGHT / 2, EXIT_WIDTH, EXIT_HEIGHT)) {
			g_spriteRetry.m_color = D3DCOLOR_RGBA(200, 200, 200, 255);
		}
		else {
			g_spriteRetry.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		if (g_spriteGameOver.m_pos.y < SCREEN_CENTER_Y) {
			g_spriteGameOver.m_pos.y += CLEAR_FALL_SPEED;
			g_spriteExit.m_pos.y += CLEAR_FALL_SPEED;
			g_spriteRetry.m_pos.y += CLEAR_FALL_SPEED;
		}
		else if (DIGetMouseTrigger(0) && bHoverRetry) {
			g_bGameOverPush = true;
			g_pushNum = 1;
			once = false;
		}
		else if (DIGetMouseTrigger(0)&&bHoverExit) {
			g_bGameOverPush = true;
			g_pushNum = 2;
			once = false;
		}
	}
}

void DrawGameOver() {
	if (GetGameOver()) {
		SetRenderMode(BLEND_TRANSLUCENT);
		g_spriteGameOver.DrawSprite(g_textureGameOver);
		g_spriteExit.DrawSprite(g_textureExit);
		g_spriteRetry.DrawSprite(g_textureRetry);
	}
}

bool GetGameOverPush() {
	return g_bGameOverPush;
}

void SetGameOverPush(bool flag) {
	g_bGameOverPush = flag;
}
void SetGameOverPushNum(int num) {
	g_pushNum = num;
}
int GetGameOverPushNum() {
	return g_pushNum;
}