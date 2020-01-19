#include "gameover.h"
#include "input.h"
#include "collision.h"
#include "fade.h"
#include "scene.h"
#include "light.h"

#define STAGESELECT_WIDTH (1200)
#define STAGESELECT_HEIGHT (700)
#define RETURN_WIDTH (100)
#define RETURN_HEIGHT (100)
#define CLEAR_FALL_SPEED (10)
#define STAGESELECTNO_WIDTH	(200)
#define STAGESELECTNO_HEIGHT (200)

static LPDIRECT3DTEXTURE9 g_textureStageSelectFire;
static LPDIRECT3DTEXTURE9 g_textureReturn;
static LPDIRECT3DTEXTURE9 g_textureStage1;
static LPDIRECT3DTEXTURE9 g_textureStage2;
static LPDIRECT3DTEXTURE9 g_textureStage3;
static CSprite g_spriteStageSelect[3];
static CSprite g_spriteStageSelectFire;
static CSprite g_spriteReturn;
static CSprite g_spriteStage1;
static CSprite g_spriteStage2;
static CSprite g_spriteStage3;
static bool g_bStageSelectPush;
static int g_selectingNum;

void InitStageSelect() {
	g_textureStageSelectFire = SetTexture("data/texture/fire.png");
	g_textureReturn = SetTexture("data/texture/return.png");
	g_textureStage1 = SetTexture("data/texture/stageselect1.png");
	g_textureStage2 = SetTexture("data/texture/stageselect2.png");
	g_textureStage3 = SetTexture("data/texture/stageselect3.png");
	for (int i = 0; i < 3; i++)
		g_spriteStageSelect[i].InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), STAGESELECT_WIDTH, STAGESELECT_HEIGHT, 1, 1);
	g_spriteStageSelectFire.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT - 150 + 10), SCREEN_WIDTH, 300, 5, 5);
	g_spriteStageSelectFire.m_color = D3DCOLOR_RGBA(255, 255, 255, 100);
	g_spriteReturn.InitSprite(D3DXVECTOR2(SCREEN_WIDTH - RETURN_WIDTH, SCREEN_HEIGHT - RETURN_HEIGHT), RETURN_WIDTH, RETURN_HEIGHT, 1, 1);
	g_spriteReturn.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_spriteStage1.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X - 300, SCREEN_CENTER_Y), STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT, 1, 1);
	g_spriteStage2.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT, 1, 1);
	g_spriteStage3.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X + 300, SCREEN_CENTER_Y), STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT, 1, 1);
	g_spriteStage1.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
	g_spriteStage2.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
	g_spriteStage3.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
	g_bStageSelectPush = false;
	PlaySound(SOUND_LABEL_STAGESELECT);
	StartFadeIn();
}

void UninitStageSelect() {
	StopSound(SOUND_LABEL_STAGESELECT);
	g_textureReturn->Release();
	g_textureReturn = NULL;
	g_textureStage1->Release();
	g_textureStage1 = NULL;
	g_textureStage2->Release();
	g_textureStage2 = NULL;
	g_textureStage3->Release();
	g_textureStage3 = NULL;
}

void UpdateStageSelect() {
	int bHoverNo = 0;
	static int animCnt = 0;
	animCnt++;
	g_spriteStageSelectFire.m_patNum = animCnt / 3 % 25;
	static float time = 0;
	static int stage = -1;
	// ホバーステージ1
	if (CollisionRect(GetMousePos().x, GetMousePos().y, 1, 1, g_spriteStage1.m_pos.x - STAGESELECTNO_WIDTH / 2, g_spriteStage1.m_pos.y - STAGESELECTNO_HEIGHT / 2, STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT)) {
		g_spriteStage1.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
		bHoverNo = 1;
		time += 0.3f;
		g_spriteStage1.m_pos.y += sin(time);
	}
	else {
		g_spriteStage1.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
	}
	// ホバーステージ2
	if (CollisionRect(GetMousePos().x, GetMousePos().y, 1, 1, g_spriteStage2.m_pos.x - STAGESELECTNO_WIDTH / 2, g_spriteStage2.m_pos.y - STAGESELECTNO_HEIGHT / 2, STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT)) {
		g_spriteStage2.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
		bHoverNo = 2;
		time += 0.3f;
		g_spriteStage2.m_pos.y += sin(time);
	}
	else {
		g_spriteStage2.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
	}
	// ホバーステージ3
	if (CollisionRect(GetMousePos().x, GetMousePos().y, 1, 1, g_spriteStage3.m_pos.x - STAGESELECTNO_WIDTH / 2, g_spriteStage3.m_pos.y - STAGESELECTNO_HEIGHT / 2, STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT)) {
		g_spriteStage3.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
		bHoverNo = 3;
		time += 0.3f;
		g_spriteStage3.m_pos.y += sin(time);
	}
	else {
		g_spriteStage3.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
	}
	// タイトルへ
	if (CollisionRect(GetMousePos().x, GetMousePos().y, 1, 1, g_spriteReturn.m_pos.x - RETURN_WIDTH / 2, g_spriteReturn.m_pos.y - RETURN_HEIGHT / 2, RETURN_WIDTH, RETURN_HEIGHT)) {
		g_spriteReturn.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
		bHoverNo = 4;
	}
	else {
		g_spriteReturn.m_color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	if (bHoverNo == 0) {
		time = 0;
		g_spriteStage1.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X - 300, SCREEN_CENTER_Y), STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT, 1, 1);
		g_spriteStage2.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT, 1, 1);
		g_spriteStage3.InitSprite(D3DXVECTOR2(SCREEN_CENTER_X + 300, SCREEN_CENTER_Y), STAGESELECTNO_WIDTH, STAGESELECTNO_HEIGHT, 1, 1);
		g_spriteStage1.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
		g_spriteStage2.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
		g_spriteStage3.m_color = D3DCOLOR_RGBA(100, 100, 100, 255);
	}
	if (DIGetMouseTrigger(0) && stage == -1) {
		switch (bHoverNo)
		{
		case 1:
			StartFadeOut();
			stage = SCENE_STAGE1;
			break;
		case 2:
			StartFadeOut();
			stage = SCENE_STAGE2;
			break;
		case 3:
			StartFadeOut();
			stage = SCENE_STAGE3;
			break;
		case 4:
			StartFadeOut();
			stage = SCENE_TITLE;
			break;
		default:
			break;
		}
	}
	if (stage != -1) {
		if (EndFadeOut()) {
			SetScene(stage);
			stage = -1;
		}
	}
}
void DrawStageSelect() {
	SetRenderMode(BLEND_TRANSLUCENT);
	g_spriteStageSelectFire.DrawSprite(g_textureStageSelectFire);
	g_spriteReturn.DrawSprite(g_textureReturn);
	g_spriteStage1.DrawSprite(g_textureStage1);
	g_spriteStage2.DrawSprite(g_textureStage2);
	g_spriteStage3.DrawSprite(g_textureStage3);
	SetFireLight(g_spriteStageSelectFire.m_patNum);
	SetLight(GetMousePos(), D3DXVECTOR2(3, 3));
	DrawLight();
}
