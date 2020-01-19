/////////////////////////////////////////////
//
// light
//
/////////////////////////////////////////////

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

HRESULT InitLight(void);
void UpdateLight(void);
void DrawLight(void);
void UninitLight(void);
void SetLight(D3DXVECTOR2 pos,D3DXVECTOR2 scale);
void SetFireLight(int animnum);

#endif // !_LIGHT_H_
