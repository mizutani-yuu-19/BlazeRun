#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "main.h"
#include "common.h"
#include "sprite.h"


void InitGameOver();
void UninitGameOver();
void UpdateGameOver();
void DrawGameOver();

bool GetGameOverPush();
void SetGameOverPush(bool flag);
void SetGameOverPushNum(int num);
int GetGameOverPushNum();
#endif // !_GAMEOVER_H_
