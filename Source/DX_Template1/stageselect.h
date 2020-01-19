#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "main.h"
#include "common.h"
#include "sprite.h"


void InitStageSelect();
void UninitStageSelect();
void UpdateStageSelect();
void DrawStageSelect();

bool GetStageSelectPush();
void SetStageSelectPush(bool flag);
#endif // !_STAGESELECT_H_
