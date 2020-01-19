#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//----------インクルード-------------
#include "main.h"
#include "common.h"

//----------プロトタイプ-----------
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

bool GetTutorial();
int GetTutorialButton();
void TutorialPlus();

bool GetTutorialPush(void);
void SetTutorialPush(bool flag);

#endif // !_TUTORIAL_H_
