///////////////////////////////////////////////////////
//
// ステージ3
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
#include "stage3.h"
#include "number.h"
//------------定数マクロ-------------
#define CREATE_STAGE_INTERVAL	((int)(SCREEN_WIDTH/SCROLL_SPEED))
#define OIL_PROBABILITY			(400)	// オイル発生確率　1/〇フレーム
//-----------グローバル変数------------
static int g_count;
static bool g_bEnd;

//------------関数------------------
void InitStage3(void) {
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
	PlaySound(SOUND_LABEL_STAGE3);
	// フェードイン開始
	//StartFadeIn();
}

void UninitStage3(void) {
	StopSound(SOUND_LABEL_STAGE3);
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

void UpdateStage3(void) {
	if (!(rand() % OIL_PROBABILITY) && !(GetGameOver() || GetGameClear()))
		CreateOil(D3DXVECTOR2(1200, 50 + rand() % (SCREEN_HEIGHT - 50)));
	switch (g_count)
	{
	case 0:
		CreateGround(D3DXVECTOR2(0, 650), 1200);
		CreateGrass(D3DXVECTOR2(0, 650), 1200, 0);
		CreateBoard(D3DXVECTOR2(600, 450), 2);
		CreateFireworks(D3DXVECTOR2(1000, 650));
		CreateFireworks(D3DXVECTOR2(800, 450));
		CreateGround(D3DXVECTOR2(200 + SCREEN_WIDTH, 400), 700);
		CreateGrass(D3DXVECTOR2(200 + SCREEN_WIDTH, 400), 700, 0);
		CreateBoard(D3DXVECTOR2(800 + SCREEN_WIDTH, 250), 2);
		CreateGrass(D3DXVECTOR2(800 + SCREEN_WIDTH, 250), 300, 0);
		CreateLamp(D3DXVECTOR2(300 + SCREEN_WIDTH, 200));
		g_count = 1;
		break;
	case CREATE_STAGE_INTERVAL * 1:
		CreateBoard(D3DXVECTOR2(100 + SCREEN_WIDTH, 350), 1);
		CreateBoard(D3DXVECTOR2(400 + SCREEN_WIDTH, 500), 1);
		CreateLamp(D3DXVECTOR2(100 + SCREEN_WIDTH, 200));
		CreateLamp(D3DXVECTOR2(400 + SCREEN_WIDTH, 300));
		CreateLamp(D3DXVECTOR2(800 + SCREEN_WIDTH, 400));
		CreateGround(D3DXVECTOR2(700 + SCREEN_WIDTH, 600), 500);
		CreateGrass(D3DXVECTOR2(700 + SCREEN_WIDTH, 600), 500, 0);
		CreateFireworks(D3DXVECTOR2(1100 + SCREEN_WIDTH, 600));
		break;
	case CREATE_STAGE_INTERVAL * 2:
		CreateBoard(D3DXVECTOR2(100 + SCREEN_WIDTH, 400), 1);
		CreateDynamite(D3DXVECTOR2(125 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(500 + SCREEN_WIDTH, 300), 1);
		CreateDynamite(D3DXVECTOR2(525 + SCREEN_WIDTH, 300));
		CreateBoard(D3DXVECTOR2(1000 + SCREEN_WIDTH, 400), 1);
		CreateDynamite(D3DXVECTOR2(1025 + SCREEN_WIDTH, 400));
		CreateGround(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 800);
		CreateGrass(D3DXVECTOR2(200 + SCREEN_WIDTH, 600), 800, 0);
		CreateFireworks(D3DXVECTOR2(300 + SCREEN_WIDTH, 600));
		CreateFireworks(D3DXVECTOR2(800 + SCREEN_WIDTH, 600));
		CreateWall(D3DXVECTOR2(600 + SCREEN_WIDTH, 250));
		break;
	case CREATE_STAGE_INTERVAL * 3:
		CreateGround(D3DXVECTOR2(0 + SCREEN_WIDTH, 650), 900);
		CreateBoard(D3DXVECTOR2(300 + SCREEN_WIDTH, 400), 2);
		CreateBoard(D3DXVECTOR2(1000 + SCREEN_WIDTH, 500), 1);
		CreateLamp(D3DXVECTOR2(100 + SCREEN_WIDTH, 200));
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
		CreateBoard(D3DXVECTOR2(1000 + SCREEN_WIDTH, 300), 1);
		break;
	case CREATE_STAGE_INTERVAL * 5:
		CreateBoard(D3DXVECTOR2(200 + SCREEN_WIDTH, 300), 1);
		CreateBoard(D3DXVECTOR2(600 + SCREEN_WIDTH, 300), 1);
		CreateLamp(D3DXVECTOR2(200 + SCREEN_WIDTH, 200));
		CreateLamp(D3DXVECTOR2(600 + SCREEN_WIDTH, 200));
		CreateGround(D3DXVECTOR2(1000 + SCREEN_WIDTH, 600), 600);
		CreateGrass(D3DXVECTOR2(1000 + SCREEN_WIDTH, 600), 600, 0);
		break;
	case CREATE_STAGE_INTERVAL * 6:
		CreateFireworks(D3DXVECTOR2(300 + SCREEN_WIDTH, 600));
		CreateBoard(D3DXVECTOR2(600 + SCREEN_WIDTH, 400), 2);
		CreateGrass(D3DXVECTOR2(600 + SCREEN_WIDTH, 400), 300, 0);
		CreateFireworks(D3DXVECTOR2(800 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(1100 + SCREEN_WIDTH, 200), 2);
		CreateGrass(D3DXVECTOR2(1100 + SCREEN_WIDTH, 200), 300, 0);
		break;
	case CREATE_STAGE_INTERVAL * 7:
		CreateFireworks(D3DXVECTOR2(100 + SCREEN_WIDTH, 200));
		CreateBoard(D3DXVECTOR2(300 + SCREEN_WIDTH, 300), 1);
		CreateBoard(D3DXVECTOR2(500 + SCREEN_WIDTH, 500), 1);
		CreateGround(D3DXVECTOR2(600 + SCREEN_WIDTH, 600), 600);
		CreateGrass(D3DXVECTOR2(600 + SCREEN_WIDTH, 600), 400, 0);
		CreateFireworks(D3DXVECTOR2(700 + SCREEN_WIDTH, 600));
		CreateLamp(D3DXVECTOR2(700 + SCREEN_WIDTH, 200));
		CreateWall(D3DXVECTOR2(1000 + SCREEN_WIDTH, 250));
		CreateDynamite(D3DXVECTOR2(1000 + SCREEN_WIDTH, 250));
		break;
	case CREATE_STAGE_INTERVAL * 8:
		CreateGround(D3DXVECTOR2(100 + SCREEN_WIDTH, 400), 500);
		CreateGrass(D3DXVECTOR2(100 + SCREEN_WIDTH, 400), 500, 0);
		CreateBoard(D3DXVECTOR2(900 + SCREEN_WIDTH, 400), 1);
		CreateGrass(D3DXVECTOR2(900 + SCREEN_WIDTH, 400), 100, 0);
		CreateLamp(D3DXVECTOR2(900 + SCREEN_WIDTH, 200));
		CreateGround(D3DXVECTOR2(1000 + SCREEN_WIDTH, 650), 900);
		break;
	case CREATE_STAGE_INTERVAL * 9:
		CreateBoard(D3DXVECTOR2(0 + SCREEN_WIDTH, 300), 1);
		CreateGrass(D3DXVECTOR2(0 + SCREEN_WIDTH, 300), 100, 0);
		CreateLamp(D3DXVECTOR2(0 + SCREEN_WIDTH, 200));
		CreateBoard(D3DXVECTOR2(300 + SCREEN_WIDTH, 200), 1);
		CreateGrass(D3DXVECTOR2(300 + SCREEN_WIDTH, 200), 100, 0);
		CreateLamp(D3DXVECTOR2(300 + SCREEN_WIDTH, 200));
		CreateDynamite(D3DXVECTOR2(450 + SCREEN_WIDTH, 650));
		CreateWall(D3DXVECTOR2(500 + SCREEN_WIDTH, 300));
		CreateLamp(D3DXVECTOR2(700 + SCREEN_WIDTH, 200));
		CreateBoard(D3DXVECTOR2(700 + SCREEN_WIDTH, 450), 2);
		break;
	case CREATE_STAGE_INTERVAL * 10:
		CreateBoard(D3DXVECTOR2(0 + SCREEN_WIDTH, 500), 1);
		CreateFireworks(D3DXVECTOR2(0 + SCREEN_WIDTH, 500));
		CreateBoard(D3DXVECTOR2(300 + SCREEN_WIDTH, 400), 1);
		CreateFireworks(D3DXVECTOR2(300 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(600 + SCREEN_WIDTH, 500), 1);
		CreateFireworks(D3DXVECTOR2(600 + SCREEN_WIDTH, 500));
		CreateBoard(D3DXVECTOR2(900 + SCREEN_WIDTH, 400), 1);
		CreateFireworks(D3DXVECTOR2(900 + SCREEN_WIDTH, 400));
		CreateGround(D3DXVECTOR2(1000 + SCREEN_WIDTH, 600), 600);
		CreateGrass(D3DXVECTOR2(1000 + SCREEN_WIDTH, 600), 600, 0);
		break;
	case CREATE_STAGE_INTERVAL * 11:
		CreateFireworks(D3DXVECTOR2(300 + SCREEN_WIDTH, 600));
		CreateBoard(D3DXVECTOR2(600 + SCREEN_WIDTH, 400), 2);
		CreateGrass(D3DXVECTOR2(600 + SCREEN_WIDTH, 400), 300, 0);
		CreateFireworks(D3DXVECTOR2(800 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(1100 + SCREEN_WIDTH, 200), 2);
		CreateGrass(D3DXVECTOR2(1100 + SCREEN_WIDTH, 200), 300, 0);
		break;
	case CREATE_STAGE_INTERVAL * 12:
		CreateFireworks(D3DXVECTOR2(100 + SCREEN_WIDTH, 200));
		CreateGround(D3DXVECTOR2(700 + SCREEN_WIDTH, 500), 500);
		CreateGrass(D3DXVECTOR2(700 + SCREEN_WIDTH, 500), 500, 0);
		CreateLamp(D3DXVECTOR2(800 + SCREEN_WIDTH, 200));
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
		CreateGround(D3DXVECTOR2(0 + SCREEN_WIDTH, 600), 2400);
		CreateGrass(D3DXVECTOR2(0 + SCREEN_WIDTH, 600), 400, 0);
		CreateGrass(D3DXVECTOR2(500 + SCREEN_WIDTH, 600), 700, 0);
		CreateBoard(D3DXVECTOR2(400 + SCREEN_WIDTH, 400), 1);
		CreateDynamite(D3DXVECTOR2(400 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(800 + SCREEN_WIDTH, 300), 1);
		CreateDynamite(D3DXVECTOR2(850 + SCREEN_WIDTH, 300));
		CreateWall(D3DXVECTOR2(900 + SCREEN_WIDTH, 250));
		CreateFireworks(D3DXVECTOR2(200 + SCREEN_WIDTH, 600));
		CreateFireworks(D3DXVECTOR2(600 + SCREEN_WIDTH, 600));
		CreateFireworks(D3DXVECTOR2(1100 + SCREEN_WIDTH, 600));
		break;
	case CREATE_STAGE_INTERVAL * 15:
		CreateFireworks(D3DXVECTOR2(200 + SCREEN_WIDTH, 600));
		CreateFireworks(D3DXVECTOR2(500 + SCREEN_WIDTH, 600));
		CreateFireworks(D3DXVECTOR2(800 + SCREEN_WIDTH, 600));
		CreateFireworks(D3DXVECTOR2(1100 + SCREEN_WIDTH, 600));
		CreateBoard(D3DXVECTOR2(100 + SCREEN_WIDTH, 400), 1);
		CreateDynamite(D3DXVECTOR2(100 + SCREEN_WIDTH, 400));
		CreateBoard(D3DXVECTOR2(400 + SCREEN_WIDTH, 300), 1);
		CreateFireworks(D3DXVECTOR2(400 + SCREEN_WIDTH, 300));
		CreateBoard(D3DXVECTOR2(700 + SCREEN_WIDTH, 300), 1);
		CreateFireworks(D3DXVECTOR2(700 + SCREEN_WIDTH, 300));
		CreateBoard(D3DXVECTOR2(1000 + SCREEN_WIDTH, 300), 1);
		CreateFireworks(D3DXVECTOR2(1000 + SCREEN_WIDTH, 300));
		break;
	case CREATE_STAGE_INTERVAL * 16:
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
		if (GetGameOverPushNum() == 2 || GetClearPushNum() == 2) {
			SetScene(SCENE_STAGESELECT);
		}
		else if (GetGameOverPushNum() == 1) {
			UninitStage3();
			InitStage3();
		}
		SetClearPushNum(0);
		SetGameOverPushNum(0);
		g_bEnd = false;
		fadein = false;
	}
}

void DrawStage3(void) {
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
