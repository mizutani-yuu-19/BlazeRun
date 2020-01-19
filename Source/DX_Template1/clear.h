#ifndef _CLEAR_H_
#define _CLEAR_H_

#include "main.h"
#include "common.h"
#include "sprite.h"


void InitClear();
void UninitClear();
void UpdateClear();
void DrawClear();

bool GetClearPush();
void SetClearPush(bool flag);
void SetClearPushNum(int num);
int GetClearPushNum();
#endif // !_CLEAR_H_
