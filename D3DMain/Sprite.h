//==========================================================
// Sprite.h
// Auther : ���� ���V
// Data   : 2002/05/01
//==========================================================

#if !defined(AFX_SPRITE_H__5CBA9CB1_EE8B_4FE8_A59F_9A9138CE5451__INCLUDED_)
#define AFX_SPRITE_H__5CBA9CB1_EE8B_4FE8_A59F_9A9138CE5451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------
#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CSprite
//	Func:	�P�̃X�v���C�g�̊Ǘ�
//----------------------------------------------
class CSprite : public C2DGraphicObj  
{
protected:
	LPDIRECT3DTEXTURE8	m_pTexture;		// �e�N�X�`��
	LPD3DXSPRITE		m_pSprite;		// �X�v���C�g

public:
	void Render();						// �`�揈��

	CSprite(LPDIRECT3DDEVICE8 d3dDevice, TCHAR* strFileName);
	virtual ~CSprite();

};

#endif // !defined(AFX_SPRITE_H__5CBA9CB1_EE8B_4FE8_A59F_9A9138CE5451__INCLUDED_)
