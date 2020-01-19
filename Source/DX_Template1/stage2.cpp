///////////////////////////////////////////////////////
//
// ステージ2
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
#include "stage2.h"
#include "number.h"
//------------定数マクロ-------------
#define CREATE_STAGE_INTERVAL	((int)(SCREEN_WIDTH/SCROLL_SPEED))
#define OIL_PROBABILITY			(400)	// オイル発生確率　1/〇フレーム
//-----------グローバル変数------------
static int g_count;
static bool g_bEnd;

//------------関数------------------
void InitStage2(void) {
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

void UninitStage2(void) {
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

void UpdateStage2(void) {
	if (!(rand() % OIL_PROBABILITY) && !(GetGameOver() || GetGameClear()))
		CreateOil(D3DXVECTOR2(1200, 50 + rand() % (SCREEN_HEIGHT - 50)));
	switch (g_count)
	{
	case 0:
		CreateGround(D3DXVECTOR2(0, 600), 1200);
		CreateGrass(D3DXVECTOR2(0, 600), 1200, 0);
		CreateFireworks(D3DXVECTOR2(1000, 600));
		CreateFireworks(D3DXVECTOR2(800, 600));
		CreateGround(D3DXVECTOR2(200 + SCREEN_WIDTH, 500), 1000);
		CreateGrass(D3DXVECTOR2(200 + SCREEN_WIDTH, 500), 1000, 0);
		CreateBoard(D3DXVECTOR2(500 + SCREEN_WIDTH, 300), 2);
		CreateFireworks(D3DXVECTOR2(700 + SCREEN_WIDTH, 300));
		g_count = 1;
		break;
	case CREATE_STAGE_INTERVAL * 1:
		CreateGround(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 1000);
		CreateLamp(D3DXVECTOR2(300 + SCREEN_WIDTH, 300));
		CreateLamp(D3DXVECTOR2(700 + SCREEN_WIDTH, 300));
		CreateLamp(D3DXVECTOR2(1100 + SCREEN_WIDTH, 300));
		CreateFireworks(D3DXVECTOR2(1100 + SCREEN_WIDTH, 600));
		break;
	case CREATE_STAGE_INTERVAL * 2:
		CreateBoard(D3DXVECTOR2(0 + SCREEN_WIDTH, 400), 2);
		CreateGrass(D3DXVECTOR2(0 + SCREEN_WIDTH, 400), 300, 0);
		CreateFireworks(D3DXVECTOR2(200 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(600 + SCREEN_WIDTH, 400), 1);
		CreateGrass(D3DXVECTOR2(600 + SCREEN_WIDTH, 400), 100, 0);
		CreateFireworks(D3DXVECTOR2(600 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(1000 + SCREEN_WIDTH, 400), 2);
		CreateGrass(D3DXVECTOR2(1000 + SCREEN_WIDTH, 400), 300, 0);
		CreateFireworks(D3DXVECTOR2(1200 + SCREEN_WIDTH, 400));
		break;
	case CREATE_STAGE_INTERVAL * 3:
		CreateGround(D3DXVECTOR2(0 + SCREEN_WIDTH, 650), 900);
		CreateBoard(D3DXVECTOR2(300 + SCREEN_WIDTH, 400), 2);
		CreateBoard(D3DXVECTOR2(1000 + SCREEN_WIDTH, 500), 1);
		CreateLamp(D3DXVECTOR2(100 + SCREEN_WIDTH, 200));
		CreateLamp(D3DXVECTOR2(1000 + SCREEN_WIDTH, 300));
		CreateLamp(D3DXVECTOR2(600 + SCREEN_WIDTH, 200));
		CreateWall(D3DXVECTOR2(600 + SCREEN_WIDTH, 300));
		CreateGrass(D3DXVECTOR2(0 + SCREEN_WIDTH, 650), 600, 0);
		CreateGrass(D3DXVECTOR2(700 + SCREEN_WIDTH, 650), 200, 0);
		CreateGrass(D3DXVECTOR2(1000 + SCREEN_WIDTH, 500), 100, 0);
		CreateDynamite(D3DXVECTOR2(550 + SCREEN_WIDTH, 400));
		break;
	case CREATE_STAGE_INTERVAL * 4:
		CreateGround(D3DXVECTOR2(100 + SCREEN_WIDTH, 400), 600);
		CreateGrass(D3DXVECTOR2(100 + SCREEN_WIDTH, 400), 600, 0);
		CreateFireworks(D3DXVECTOR2(600 + SCREEN_WIDTH, 400));
		CreateGround(D3DXVECTOR2(900 + SCREEN_WIDTH, 650), 1500);
		CreateGrass(D3DXVECTOR2(900 + SCREEN_WIDTH, 650), 1500, 0);
		break;
	case CREATE_STAGE_INTERVAL * 5:
		CreateLamp(D3DXVECTOR2(100 + SCREEN_WIDTH, 300));
		CreateLamp(D3DXVECTOR2(500 + SCREEN_WIDTH, 200));
		CreateLamp(D3DXVECTOR2(800 + SCREEN_WIDTH, 300));
		CreateBoard(D3DXVECTOR2(100 + SCREEN_WIDTH, 500), 1);
		CreateBoard(D3DXVECTOR2(500 + SCREEN_WIDTH, 400), 1);
		CreateBoard(D3DXVECTOR2(800 + SCREEN_WIDTH, 500), 1);
		CreateGrass(D3DXVECTOR2(100 + SCREEN_WIDTH, 500), 100, 0);
		CreateGrass(D3DXVECTOR2(500 + SCREEN_WIDTH, 400), 100, 0);
		CreateGrass(D3DXVECTOR2(800 + SCREEN_WIDTH, 500), 100, 0);
		CreateFireworks(D3DXVECTOR2(150 + SCREEN_WIDTH, 500));
		CreateFireworks(D3DXVECTOR2(550 + SCREEN_WIDTH, 400));
		CreateFireworks(D3DXVECTOR2(850 + SCREEN_WIDTH, 500));
		CreateFireworks(D3DXVECTOR2(1100 + SCREEN_WIDTH, 650));
		break;
	case CREATE_STAGE_INTERVAL * 6:
		CreateGround(D3DXVECTOR2(SCREEN_WIDTH + 200, 600), 1000);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 200, 600), 1000, 0);
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 300, 600));
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 700, 600));
		CreateWall(D3DXVECTOR2(SCREEN_WIDTH + 500, 250));
		CreateWall(D3DXVECTOR2(SCREEN_WIDTH + 900, 250));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 500, 250));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 900, 250));
		break;
	case CREATE_STAGE_INTERVAL * 7:
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 100, 500), 2);
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 500, 300), 1);
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 750, 400), 1);
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 1000, 500), 1);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 100, 500), 300, 0);
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 500, 200));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 750, 200));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 1000, 200));
		break;
	case CREATE_STAGE_INTERVAL * 8:
		CreateGround(D3DXVECTOR2(SCREEN_WIDTH + 0, 600), 500);
		CreateGround(D3DXVECTOR2(SCREEN_WIDTH + 700, 600), 500);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 0, 600), 500, 0);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 700, 600), 500, 0);
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 100, 400));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 800, 400));
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 400, 600));
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 1000, 600));
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 900, 400), 2);
		break;
	case CREATE_STAGE_INTERVAL * 9:
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 100, 200), 2);
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 600, 200), 2);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 100, 200), 300, 0);
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 675, 200));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 725, 200));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 775, 200));
		CreateGround(D3DXVECTOR2(SCREEN_WIDTH + 400, 600), 1100);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 400, 600), 1100, 0);
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 600, 600));
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 1000, 600));
		break;
	case CREATE_STAGE_INTERVAL * 10:
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 200, 600));
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 600, 500));
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 400, 500), 2);
		CreateBoard(D3DXVECTOR2(SCREEN_WIDTH + 1000, 500), 2);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 400, 500), 300, 0);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 1000, 500), 300, 0);
		break;
	case CREATE_STAGE_INTERVAL * 11:
		CreateFireworks(D3DXVECTOR2(SCREEN_WIDTH + 0, 500));
		CreateGround(D3DXVECTOR2(SCREEN_WIDTH + 300, 600), 900);
		CreateGrass(D3DXVECTOR2(SCREEN_WIDTH + 300, 600), 900, 0);
		CreateWall(D3DXVECTOR2(SCREEN_WIDTH + 1000, 250));
		CreateDynamite(D3DXVECTOR2(SCREEN_WIDTH + 925, 600));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 400, 400));
		CreateLamp(D3DXVECTOR2(SCREEN_WIDTH + 700, 400));
		break;
	case CREATE_STAGE_INTERVAL * 12:
		CreateGoal(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_CENTER_Y));
		break;
	case CREATE_STAGE_INTERVAL * 13:
		CreateGround(D3DXVECTOR2(200 + SCREEN_WIDTH, 500), 900);
		CreateGrass(D3DXVECTOR2(200 + SCREEN_WIDTH, 500), 900, 0);
		CreateBoard(D3DXVECTOR2(300 + SCREEN_WIDTH, 300), 1);
		CreateLamp(D3DXVECTOR2(300 + SCREEN_WIDTH, 200));
		CreateBoard(D3DXVECTOR2(600 + SCREEN_WIDTH, 100), 1);
		CreateLamp(D3DXVECTOR2(600 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(900 + SCREEN_WIDTH, 300), 1);
		CreateLamp(D3DXVECTOR2(900 + SCREEN_WIDTH, 200));
		break;
	case CREATE_STAGE_INTERVAL * 14:
		CreateGoal(D3DXVECTOR2(0 + SCREEN_WIDTH, SCREEN_CENTER_Y));
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
			SetScene(SCENE_STAGE3);
		}
		else if (GetClearPushNum() == 2 || GetGameOverPushNum() == 2) {
			SetScene(SCENE_STAGESELECT);
		}
		else if (GetGameOverPushNum() == 1) {
			UninitStage2();
			InitStage2();
		}
		SetClearPushNum(0);
		SetGameOverPushNum(0);
		g_bEnd = false;
		fadein = false;
	}
}

void DrawStage2(void) {
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
