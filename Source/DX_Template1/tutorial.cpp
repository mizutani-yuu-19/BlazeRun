///////////////////////////////////////////////////////
//
// チュートリアル
//
///////////////////////////////////////////////////////

//------------インクルード----------------
#include "scene.h"
#include "fireworks.h"
#include "grass.h"
#include "ground.h"
#include "oil.h"
#include "wall.h"
#include "dynamite.h"
#include "lamp.h"
#include "light.h"
#include "background.h"
#include "player.h"
#include "burn.h"
#include "fade.h"
#include "input.h"
#include "goal.h"
#include "clear.h"
#include "gameover.h"
#include "board.h"
#include "tutorial.h"
#include "number.h"
//------------定数マクロ-------------
#define CREATE_STAGE_INTERVAL	((int)(SCREEN_WIDTH/SCROLL_SPEED))
#define OIL_PROBABILITY			(400)	// オイル発生確率　1/〇フレーム
//-----------グローバル変数------------
static int g_count;
static bool g_bEnd;
static bool g_bTutorial;	// 一回のみ
static int g_tutorialButton;
static int g_bTutorialPush;

//------------関数------------------
void InitTutorial(void) {
	InitBG();
	InitClear();
	InitGameOver();
	InitPlayer();
	InitFireworks();
	InitBoard();
	InitGrass();
	InitBlaze();
	InitOil();
	InitWall();
	InitDynamite();
	InitLamp();
	InitGoal();
	InitGround();
	InitNumber();
	g_count = CREATE_STAGE_INTERVAL * 0;
	if (g_count != 0) {
		CreateGround(D3DXVECTOR2(0, 600), 1000);
	}
	g_bDeleteLight = false;
	SetGameOver(false);
	SetGameClear(false);

	PlaySound(SOUND_LABEL_STAGE2);
	// フェードイン開始
	//StartFadeIn();
}

void UninitTutorial(void) {
	StopSound(SOUND_LABEL_STAGE2);
	UninitBurn();
	UninitGameOver();
	UninitClear();
	UninitDynamite();
	UninitBG();
	UninitPlayer();
	UninitBoard();
	UninitGrass();
	UninitBlaze();
	UninitOil();
	UninitWall();
	UninitLamp();
	UninitFireworks();
	UninitGoal();
	UninitGround();
	UninitNumber();
	g_count = 0;
}

void UpdateTutorial(void) {
	switch (g_count)
	{
	case 0:
		CreateGround(D3DXVECTOR2(0, 600), 2200);
		CreateGrass(D3DXVECTOR2(0, 600), 2200, 0);
		g_count = 1;
		break;
	case CREATE_STAGE_INTERVAL * 1:
		CreateGround(D3DXVECTOR2(SCREEN_WIDTH + 100, 600), 900);
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 200, 400));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 600, 400));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 1000, 400));
		break;
	case CREATE_STAGE_INTERVAL * 2:
		CreateGround(D3DXVECTOR2(SCREEN_WIDTH + 200, 600), 3900);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 200, 600), 900, 0);
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 200, 400));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 900, 400));
		break;
	case CREATE_STAGE_INTERVAL * 3:
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 0, 600), 1100, 0);
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 500, 300));
		CreateWall(D3DXVECTOR2(SCREEN_WIDTH + 700, 250));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 650, 600));
		break;
	case CREATE_STAGE_INTERVAL * 4:
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 0, 600), 1100, 0);
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 200, 400));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 800, 400));
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 500, 600));
		break;
	case CREATE_STAGE_INTERVAL * 5:
		CreateGoal(D3DXVECTOR2(SCREEN_WIDTH + 500, SCREEN_CENTER_Y));
		break;
	default:
		break;
	}
	if (!GetGameClear() && !GetGameOver()) {
		UpdatePlayer();
		//1フレームごとにカウント＋
		if (GetStart() && g_scrollSpeed != 0) {
			g_count++;
			UpdateOil();
			if (!(rand() % OIL_PROBABILITY) && !(GetGameOver() || GetGameClear()))
				CreateOil(D3DXVECTOR2(1200, 50 + rand() % (SCREEN_HEIGHT - 50)));
			// チュートリアル説明
			if ((SCREEN_WIDTH / g_scrollSpeed - 50) == g_count && (g_tutorialButton == 0 || g_tutorialButton == 1)) {
				g_scrollSpeed = 0;
				g_count--;
				g_tutorialButton = 1;
				g_bTutorialPush = false;
			}
			else if ((SCREEN_WIDTH / g_scrollSpeed * 2 - 50) == g_count && (g_tutorialButton == 2)) {
				g_scrollSpeed = 0;
				g_count--;
				g_bTutorialPush = false;
			}
			else if ((SCREEN_WIDTH / g_scrollSpeed * 3 - 50) == g_count && (g_tutorialButton == 3)) {
				g_scrollSpeed = 0;
				g_count--;
				g_bTutorialPush = false;
			}
			else if ((SCREEN_WIDTH / g_scrollSpeed * 3 - 20) == g_count && (g_tutorialButton == 4)) {
				g_scrollSpeed = 0;
				g_count--;
				g_bTutorialPush = false;
			}
			else if ((SCREEN_WIDTH / g_scrollSpeed * 3 + 50) == g_count && (g_tutorialButton == 5)) {
				g_scrollSpeed = 0;
				g_count--;
				g_bTutorialPush = false;
			}
			else if ((SCREEN_WIDTH / g_scrollSpeed * 4 + 40) == g_count && (g_tutorialButton == 6)) {
				g_scrollSpeed = 0;
				g_count--;
				g_bTutorialPush = false;
			}
			else if ((SCREEN_WIDTH / g_scrollSpeed * 5 + 20) == g_count && (g_tutorialButton == 7)) {
				g_scrollSpeed = 0;
				g_count--;
				g_bTutorialPush = false;
			}
		}
	}
	UpdateBG();
	UpdateDynamite();
	UpdateLamp();
	UpdateBurn();
	UpdateBoard();
	UpdateWall();
	UpdateGround();
	UpdateFireworks();
	UpdateGrass();
	UpdateGoal();
	UpdateNumber();
	UpdateClear();
	UpdateGameOver();
	static bool fadein = false;
	if ((GetGameOver() || GetGameClear()) && !EndFadeIn() && !fadein) {
		StartFadeIn();
		fadein = true;
		g_scrollSpeed = 0;
	}
	if ((GetGameOver() || GetGameClear()) && !g_bEnd&&EndFadeIn()) {
		g_bDeleteLight = true;
		StartFadeOut();
		g_bEnd = true;
	}
	if (g_bEnd&&EndFadeOut()) {
		SetScene(SCENE_STAGESELECT);
		SetClearPushNum(0);
		SetGameOverPushNum(0);
		g_bEnd = false;
		fadein = false;
		g_bTutorial = true;
	}
}

void DrawTutorial(void) {
	DrawBG();
	DrawGround();
	DrawBoard();
	DrawWall();
	DrawGrass();
	DrawLamp();
	DrawDynamite();
	DrawFireworks();
	DrawOil();
	DrawPlayer();
	DrawGoal();
}

bool GetTutorial() {
	return g_bTutorial;
}

int GetTutorialButton() {
	return g_tutorialButton;
}

void TutorialPlus() {
	g_tutorialButton++;
}
bool GetTutorialPush(void) {
	return g_bTutorialPush;
}
void SetTutorialPush(bool flag) {
	g_bTutorialPush = flag;
}