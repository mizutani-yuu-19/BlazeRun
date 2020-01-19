#ifndef _BURN_H_
#define _BURN_H_

//--------インクルード--------
#include "main.h" 
#include "common.h"
#include "sprite.h"

class CBurn {
public:
	void InitBurn(D3DXVECTOR2 pos, float width, float height, int num, bool bBurn);
	void UninitBurn();
	void UpdateBurn();
	void DrawBurn();

	bool m_bBurn;
	int m_num;
	D3DXVECTOR2 m_pos;
private:
	float m_width;
	float m_height;
	int	m_burnTime;
};

void InitBurn();
void UninitBurn();
void UpdateBurn();
void DrawBurn();

int CreateBurn(D3DXVECTOR2 pos, float width, float height, bool bBurn);
void DeleteBurn(int num);
void SetBurnPos(int num, D3DXVECTOR2 pos);

bool GetBurn(int num);

#endif // !_BURN_H_
