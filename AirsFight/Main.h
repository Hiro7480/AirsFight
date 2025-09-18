//==========================================================
// Main.h
// Auther : ���� ���V
// Data   : 2000/12/28
//==========================================================
#if !defined(AFX_MAIN_H__EF2B446E_7BBD_44BD_8271_B76EB98DA2C1__INCLUDED_)
#define AFX_MAIN_H__EF2B446E_7BBD_44BD_8271_B76EB98DA2C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include <d3dx8.h>
#include "D3DMain.h"

#include "GameStatus.h"

#include "Title.h"
#include "Menu.h"
#include "Game.h"
#include "Ending.h"

#include "resource.h"
//----------------------------------------------
//	Name:	AIRS_FIGHT
//	Func:	�Q�[���S�̂̊Ǘ�
//----------------------------------------------
class AIRS_FIGHT : public CD3DMain
{
private:
	GameStatus*	m_pNowClass;		// ���ݎ��s���̊Ǘ��N���X

	HRESULT OneTimeInit();
	HRESULT FrameMove();
	HRESULT Render();
	HRESULT UpDate();
	HRESULT CleanUp();

	CRITICAL_SECTION	m_cs;		// �N���e�B�J���Z�N�V�����I�u�W�F�N�g
	bool	m_bRenderFlg;			// �`�撆�t���O

public:
	AIRS_FIGHT();
};

#endif // !defined(AFX_MAIN_H__EF2B446E_7BBD_44BD_8271_B76EB98DA2C1__INCLUDED_)