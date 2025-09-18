//==========================================================
// GameStatus.cpp
// Auther : 桜井 博之
// Data   : 2002/01/11
//==========================================================

#include "GameStatus.h"

//------------------------------------------------------
//	Name:	GameStatus
//	Func:	コンストラクタ
//	in	:	LPDIRECT3DDEVICE8 d3dDevice = D3Dデバイス
//	Out	:	なし
//------------------------------------------------------
GameStatus::GameStatus(LPDIRECT3DDEVICE8 d3dDevice)
{
	m_pd3dDevice = d3dDevice;
}

//----------------------------------------------
//	Name:	~GameStatus
//	Func:	デストラクタ
//	in	:	なし
//	Out	:	なし
//----------------------------------------------
GameStatus::~GameStatus()
{

}