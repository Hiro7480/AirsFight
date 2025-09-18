//==========================================================
// BlockA.h
// Auther : 桜井 博之
// Data   : 2002/01/14
//==========================================================

#if !defined(AFX_BLOCKA_H__2E21DAF3_8FCB_42A5_BBAA_6318DE22244A__INCLUDED_)
#define AFX_BLOCKA_H__2E21DAF3_8FCB_42A5_BBAA_6318DE22244A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	インクルード
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "StageObj.h"

//----------------------------------------------
//	Name:	CBlockA
//	Func:	移動しないブロック
//----------------------------------------------
class CBlockA : public CStageObj
{
public:

	void	FrameMove();	// 毎フレームの処理
	void	Render();		// 描画

	CBlockA(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CBlockA();
};

#endif // !defined(AFX_BLOCKA_H__2E21DAF3_8FCB_42A5_BBAA_6318DE22244A__INCLUDED_)
