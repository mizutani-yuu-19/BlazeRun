// �V�[������
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "common.h"
#include "stage1.h"

// �萔��`
enum {
	SCENE_TITLE = 0,
	SCENE_STAGESELECT,
	SCENE_TUTORIAL,
	SCENE_STAGE1,
	SCENE_STAGE2,
	SCENE_STAGE3,
	SCENE_RETRY,
	//	SCENE_GAMEOVER,
	MAX_SCENE
};

// �v���g�^�C�v�錾
HRESULT InitScene();
void UninitScene();
void UpdateScene();
void DrawScene();
void SetScene(int nNext);
int GetScene();

void SetGameOver(bool flag);
void SetGameClear(bool flag);
bool GetGameOver();
bool GetGameClear();
#endif
