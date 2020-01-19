// シーン処理
#include "scene.h"
#include "title.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "tutorial.h"
#include "stageselect.h"

//----- マクロ定義

//----- 構造体宣言

//----- グローバル変数
static int g_nScene = SCENE_TITLE;
static int g_nNextScene = SCENE_TITLE;
static bool g_bGameOver;
static bool g_bGameClear;

// 初期化処理
HRESULT InitScene()
{
	switch (g_nScene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_STAGE1:
		InitStage1();
		break;
	case SCENE_STAGE2:
		InitStage2();
		break;
	case SCENE_STAGE3:
		InitStage3();
		break;
	case SCENE_STAGESELECT:
		InitStageSelect();
		break;
	case SCENE_TUTORIAL:
		InitTutorial();
		break;
	default:
		break;
	}

	return 1;
}

// 終了処理
void UninitScene()
{
	switch (g_nScene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_STAGE1:
		UninitStage1();
		break;
	case SCENE_STAGE2:
		UninitStage2();
		break;
	case SCENE_STAGE3:
		UninitStage3();
		break;
	case SCENE_STAGESELECT:
		UninitStageSelect();
		break;
	case SCENE_TUTORIAL:
		UninitTutorial();
		break;
	default:
		break;
	}
}

// 更新処理
void UpdateScene()
{
	// シーン切り替え
	if (g_nScene != g_nNextScene) {
		UninitScene();
		g_nScene = g_nNextScene;
		InitScene();
	}
	// シーン更新
	switch (g_nScene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_STAGE1:
		UpdateStage1();
		break;
	case SCENE_STAGE2:
		UpdateStage2();
		break;
	case SCENE_STAGE3:
		UpdateStage3();
		break;
	case SCENE_STAGESELECT:
		UpdateStageSelect();
		break;
	case SCENE_TUTORIAL:
		UpdateTutorial();
		break;
	default:
		break;
	}
}

// 描画処理
void DrawScene()
{
	switch (g_nScene)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_STAGE1:
		DrawStage1();
		break;
	case SCENE_STAGE2:
		DrawStage2();
		break;
	case SCENE_STAGE3:
		DrawStage3();
		break;
	case SCENE_STAGESELECT:
		DrawStageSelect();
		break;
	case SCENE_TUTORIAL:
		DrawTutorial();
		break;
	default:
		break;
	}
}
void SetScene(int nNext) {
	g_nNextScene = nNext;
}

void SetGameOver(bool flag) {
	g_bGameOver = flag;
}

bool GetGameOver() {
	return g_bGameOver;
}

void SetGameClear(bool flag) {
	g_bGameClear = flag;
}

bool GetGameClear() {
	return g_bGameClear;
}
int GetScene() {
	return g_nScene;
}
