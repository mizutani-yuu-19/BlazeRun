//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include <XAudio2.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// BGM0
	SOUND_LABEL_STAGESELECT,			// BGM1
	SOUND_LABEL_STAGE1,			// BGM2
	SOUND_LABEL_STAGE2,			// BGM2
	SOUND_LABEL_STAGE3,			// BGM2
	SOUND_LABEL_SE_BLAZE,
	SOUND_LABEL_SE_JUMP,
	SOUND_LABEL_SE_CLEAR,
	SOUND_LABEL_SE_MISS,
	SOUND_LABEL_SE_DYNAMITE,
	SOUND_LABEL_SE_LAMP,
	SOUND_LABEL_SE_FIREWORKSPAN,
	SOUND_LABEL_SE_FIREWORKSSHOT,
	SOUND_LABEL_MAX,			// �o�^���̎����ݒ�
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);

void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
