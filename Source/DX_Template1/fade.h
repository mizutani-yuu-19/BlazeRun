// フェード処理
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

// プロトタイプ宣言
HRESULT InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void StartFadeIn();
void StartFadeOut();
int EndFadeIn();
int EndFadeOut();

#endif
