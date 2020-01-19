///////////////////////////////////////////////////////
//
// ステージ1
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
#include "stage1.h"
#include "number.h"
//------------定数マクロ-------------
#define CREATE_STAGE_INTERVAL	((int)(SCREEN_WIDTH/SCROLL_SPEED))
#define OIL_PROBABILITY			(400)	// オイル発生確率　1/〇フレーム
//-----------グローバル変数------------
static int g_count;
static bool g_bEnd;
bool g_bDeleteLight = false;

//------------関数------------------
void InitStage1(void) {
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

	PlaySound(SOUND_LABEL_STAGE1);
	// フェードイン開始
	//StartFadeIn();
}

void UninitStage1(void) {
	StopSound(SOUND_LABEL_STAGE1);
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

void UpdateStage1(void) {
	if (!(rand() % OIL_PROBABILITY) && !(GetGameOver() || GetGameClear()))
		CreateOil(D3DXVECTOR2(1200, 50 + rand() % (SCREEN_HEIGHT - 50)));
	switch (g_count)
	{
	case 0:
		CreateGround(D3DXVECTOR2(0, 600), 1100);
		CreateGrass(D3DXVECTOR2(0, 600), 1100, 0);
		CreateGround(D3DXVECTOR2(100 + SCREEN_WIDTH, 600), 1100);
		CreateGrass(D3DXVECTOR2(100 + SCREEN_WIDTH, 600), 1100, 0);
		CreateFireworks(D3DXVECTOR2(1100 + SCREEN_WIDTH, 600));
		g_count = 1;
		break;
	case CREATE_STAGE_INTERVAL * 1:
		CreateGround(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 1000);
		CreateGrass(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 1000, 0);
		CreateLamp(D3DXVECTOR2(300 + SCREEN_WIDTH, 400));
		CreateLamp(D3DXVECTOR2(700 + SCREEN_WIDTH, 400));
		CreateLamp(D3DXVECTOR2(1100 + SCREEN_WIDTH, 400));
		CreateFireworks(D3DXVECTOR2(800 + SCREEN_WIDTH, 600));
		break;
	case CREATE_STAGE_INTERVAL * 2:
		CreateGround(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 1000);
		CreateGrass(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 1000, 0);
		CreateBoard(D3DXVECTOR2(800 + SCREEN_WIDTH, 400), 1);
		CreateDynamite(D3DXVECTOR2(850 + SCREEN_WIDTH, 400));
		CreateWall(D3DXVECTOR2(900 + SCREEN_WIDTH, 250));
		break;
	case CREATE_STAGE_INTERVAL * 3:
		CreateBoard(D3DXVECTOR2(100 + SCREEN_WIDTH, 500), 2);
		CreateBoard(D3DXVECTOR2(600 + SCREEN_WIDTH, 400), 2);
		CreateBoard(D3DXVECTOR2(1100 + SCREEN_WIDTH, 300), 2);
		CreateGrass(D3DXVECTOR2(100 + SCREEN_WIDTH, 500), 300, 0);
		CreateGrass(D3DXVECTOR2(600 + SCREEN_WIDTH, 400), 300, 0);
		CreateGrass(D3DXVECTOR2(1100 + SCREEN_WIDTH, 300), 300, 0);
		CreateLamp(D3DXVECTOR2(100 + SCREEN_WIDTH, 300));
		CreateLamp(D3DXVECTOR2(600 + SCREEN_WIDTH, 200));
		CreateLamp(D3DXVECTOR2(1100 + SCREEN_WIDTH, 100));
		CreateFireworks(D3DXVECTOR2(300 + SCREEN_WIDTH, 500));
		CreateFireworks(D3DXVECTOR2(800 + SCREEN_WIDTH, 400));
		break;
	case CREATE_STAGE_INTERVAL * 4:
		CreateFireworks(D3DXVECTOR2(100 + SCREEN_WIDTH, 300));
		CreateGround(D3DXVECTOR2(400 + SCREEN_WIDTH, 500), 800);
		CreateGrass(D3DXVECTOR2(400 + SCREEN_WIDTH, 500), 800, 0);
		CreateFireworks(D3DXVECTOR2(1000 + SCREEN_WIDTH, 500));
		CreateLamp(D3DXVECTOR2(400 + SCREEN_WIDTH, 300));
		CreateLamp(D3DXVECTOR2(700 + SCREEN_WIDTH, 200));
		CreateLamp(D3DXVECTOR2(1000 + SCREEN_WIDTH, 100));
		break;
	case CREATE_STAGE_INTERVAL * 5:
		CreateGround(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 1200);
		CreateGrass(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 1200, 0);
		CreateBoard(D3DXVECTOR2(300 + SCREEN_WIDTH, 400), 2);
		CreateBoard(D3DXVECTOR2(700 + SCREEN_WIDTH, 400), 1);
		CreateDynamite(D3DXVECTOR2(750 + SCREEN_WIDTH, 400));
		CreateDynamite(D3DXVECTOR2(750 + SCREEN_WIDTH, 600));
		CreateWall(D3DXVECTOR2(800 + SCREEN_WIDTH, 250));
		break;
	case CREATE_STAGE_INTERVAL * 6:
		CreateFireworks(D3DXVECTOR2(100 + SCREEN_WIDTH, 600));
		CreateGround(D3DXVECTOR2(400 + SCREEN_WIDTH, 600), 400);
		CreateGrass(D3DXVECTOR2(400 + SCREEN_WIDTH, 600), 400, 0);
		CreateFireworks(D3DXVECTOR2(700 + SCREEN_WIDTH, 600));
		CreateGround(D3DXVECTOR2(1000 + SCREEN_WIDTH, 600), 400);
		CreateGrass(D3DXVECTOR2(1000 + SCREEN_WIDTH, 600), 400, 0);
		break;
	case CREATE_STAGE_INTERVAL * 7:
		CreateGround(D3DXVECTOR2(SCREEN_WIDTH + 400, 600), 1300);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 400, 600), 1300, 0);
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 400, 400));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 650, 600));
		CreateWall(D3DXVECTOR2(SCREEN_WIDTH + 700, 250));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 850, 600));
		CreateWall(D3DXVECTOR2(SCREEN_WIDTH + 900, 250));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 1250, 600));
		CreateWall(D3DXVECTOR2(SCREEN_WIDTH + 1300, 250));
		break;
	case CREATE_STAGE_INTERVAL * 8:
		CreateGoal(D3DXVECTOR2(SCREEN_WIDTH + 600, SCREEN_CENTER_Y));
		break;
	default:
		break;
	}
	UpdateBG();
	if (!GetGameClear() && !GetGameOver()) {
		UpdatePlayer();
		//1フレームごとにカウント＋
		if (GetStart())
			g_count++;
	}
	UpdateOil();
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
		if (GetClearPush() || GetGameOverPush()) {
			StartFadeOut();
			g_bEnd = true;
		}
	}
	if (g_bEnd&&EndFadeOut()) {
		if (GetClearPushNum() == 1) {
			SetScene(SCENE_STAGE2);
		}
		else if (GetClearPushNum() == 2 || GetGameOverPushNum() == 2) {
			SetScene(SCENE_STAGESELECT);
		}
		else if (GetGameOverPushNum() == 1) {
			UninitStage1();
			InitStage1();
		}
		SetClearPushNum(0);
		SetGameOverPushNum(0);
		g_bEnd = false;
		fadein = false;
	}
}

void DrawStage1(void) {
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
	DrawNumber();
	DrawClear();
	DrawGameOver();
}
