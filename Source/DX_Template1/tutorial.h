#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//----------�C���N���[�h-------------
#include "main.h"
#include "common.h"

//----------�v���g�^�C�v-----------
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
