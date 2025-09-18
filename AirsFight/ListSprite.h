//==========================================================
// ListSprite.h
// Auther : ���� ���V
// Data   : 2002/04/29
//==========================================================

#if !defined(AFX_SPRITE_H__E78DACD3_EDEB_47F9_B805_341AB00F7DA7__INCLUDED_)
#define AFX_SPRITE_H__E78DACD3_EDEB_47F9_B805_341AB00F7DA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//	�C���N���[�h
//------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "2DGraphicObj.h"

//----------------------------------------------
//	Name:	CListSprite
//	Func:	���X�g�\���Ŏg�p����X�v���C�g
//----------------------------------------------
class CListSprite : public C2DGraphicObj
{
private:
	CListSprite*		m_pNext;		// ���̃f�[�^�ւ̃|�C���^

protected:
	LPDIRECT3DTEXTURE8	m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	bool				m_bFlg;			// �����t���O

public:
	virtual void FrameMove(){};					// ���t���[���̏���
	virtual void Render(LPD3DXSPRITE pSprite);	// ��ʕ`��
	virtual void UpDate();						// �f�[�^�X�V

	bool	IsDelete();							// ��������

	/* �A�N�Z�X�֐� */
	CListSprite*	GetNext(){return m_pNext;};			// ���̃f�[�^�ւ̃|�C���^��Ԃ�
	void SetNext(CListSprite* pNext){m_pNext = pNext;};	// ���̃f�[�^�ւ̃|�C���^���Z�b�g

	CListSprite(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture);
	virtual ~CListSprite();
};

#endif // !defined(AFX_SPRITE_H__E78DACD3_EDEB_47F9_B805_341AB00F7DA7__INCLUDED_)
