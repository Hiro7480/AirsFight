//==========================================================
// SpriteManage.h
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_SPRITEMANAGE_H__2434EF4A_DC7E_4712_A11F_3D93B926ED56__INCLUDED_)
#define AFX_SPRITEMANAGE_H__2434EF4A_DC7E_4712_A11F_3D93B926ED56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>

#include "ListSprite.h"
#include "StartLogo.h"
#include "CountLogo.h"
#include "TimeOverLogo.h"

//------------------------------
//	�萔��`
//------------------------------
/* �X�v���C�g�^�C�v���ʎq */
#define COUNT_LOGO	0
#define START_LOGO	1
#define TIME_OVER	2

//----------------------------------------------
//	Name:	CSpriteManage
//	Func:	�X�v���C�g�Ǘ��N���X
//----------------------------------------------
class CSpriteManage
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;			// D3D�f�o�C�X
	CListSprite*		m_pListTop;				// �͂��߂̃X�v���C�g�ւ̃|�C���^

	LPD3DXSPRITE		m_pSprite;				// �X�v���C�g
	LPDIRECT3DTEXTURE8	m_pTexture[10];			// �e�N�X�`���f�[�^

	CRITICAL_SECTION	m_cs;					// �N���e�B�J���Z�N�V�����I�u�W�F�N�g

public:
	void FrameMove(); 							// ���t���[���̏���
	void Render();								// ��ʕ`��
	void UpDate();								// �f�[�^�X�V

	CListSprite*	AddSprite(int nType);			// �X�v���C�g�̒ǉ�
	HRESULT			SubSprite(CListSprite* pSprite);// �X�v���C�g�̏���
	void			SubSprite();					// �X�v���C�g�̎�������

	/* �A�N�Z�X�֐� */
	CListSprite* GetListTop(){return m_pListTop;};	// �͂��߂̒e�ւ̃|�C���^��Ԃ�

	CSpriteManage(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CSpriteManage();
};

#endif // !defined(AFX_SPRITEMANAGE_H__2434EF4A_DC7E_4712_A11F_3D93B926ED56__INCLUDED_)
