// プレイヤー処理
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "common.h"
#include "sprite.h"
#include "physics.h"
#include "blaze.h"

// ポリゴン サイズ
#define PLAYER_WIDTH		100
#define PLAYER_HEIGHT		100

#define PLAYER_COL_WIDTH	(100)
#define PLAYER_COL_HEIGHT	(100)

#define MAX_BLAZE	(25)	// 同時に投げられる数
//-------クラス---------
class CPlayer {
public:
	void CPlayer::InitPlayer(D3DXVECTOR2 pos);
	void CPlayer::UninitPlayer();
	void CPlayer::UpdatePlayer();
	void CPlayer::DrawPlayer();

	bool GetStart();
	D3DXVECTOR2 GetPos();
	//D3DXVECTOR2 CPlayer::GetBlazePos();
	int GetBlazeNum();
private:
	CSprite		m_PlayerFireSprite;
	CSprite		m_PlayerSprite;
	CPhysics	m_PlayerPhysics;
	CBlaze		m_PlayerBlaze[MAX_BLAZE];
	bool		m_bBlazeExist[MAX_BLAZE];
	D3DXVECTOR2 m_prevPos;
	int 		m_BurnNum;
	bool		m_bJump;
	bool		m_bSecondJump;
	bool		m_bGround;
	int			m_blazeCnt;		// ブレイズを投げられる
	int			m_animRunCnt;
	int			m_animbJumpCnt;
	int			m_animbBlazeCnt;
	float		m_groundPosY;
	int			m_noColTime;
	bool		m_bStart;
	void		StartPlayer();
	void		UpdateTutorial();
};

//---------プロトタイプ---------
void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
bool GetStart();
D3DXVECTOR2 *GetPlayerPos(void);
//D3DXVECTOR2 GetPlayerBlazePos();
int GetBlazeNum();
void DrawTutrialMark();
#endif // !_PLAYER_H_