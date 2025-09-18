//==========================================================
// EffectManage.h
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================

#if !defined(AFX_EFFECTMANAGE_H__0BE91682_45A4_42E5_8471_10CB2C8DFEF8__INCLUDED_)
#define AFX_EFFECTMANAGE_H__0BE91682_45A4_42E5_8471_10CB2C8DFEF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include <d3dx8.h>
#include "define.h"
#include "Effect.h"

#include "BoostA.h"
#include "BoostB.h"
#include "ExplosionA.h"
#include "ExplosionB.h"
#include "OrbitBul.h"
#include "Revival.h"

//----------------------------------------------
//	�萔��`
//----------------------------------------------
#define TEXTURE_NUM	10

/* �G�t�F�N�g�^�C�v���ʎq */
enum{
	BOOST_A,		// �_�b�V�����̃u�[�X�g
	BOOST_B,		// ��s���̃u�[�X�g

	EXPLOSION_A,	// �e���ǂɓ����������̔���
	EXPLOSION_B,	// �e���L�����N�^�ɓ����������̔���

	ORBIT_BUL,		// �e�̋O��

	REVIVAL			// ����
};

//----------------------------------------------
//	Name:	CEffectManage
//	Func:	�S�ẴG�t�F�N�g�̊Ǘ��N���X
//			���X�g�\�����g���ĊǗ�����
//----------------------------------------------
class CEffectManage  
{
private:
	LPDIRECT3DDEVICE8	m_pd3dDevice;				// D3D�f�o�C�X
	CEffect*			m_pListTop;					// �͂��߂̃G�t�F�N�g�ւ̃|�C���^
	LPDIRECT3DTEXTURE8	m_pTexture[TEXTURE_NUM];	// �e�N�X�`���f�[�^
	CRITICAL_SECTION	m_cs;						// �N���e�B�J���Z�N�V�����I�u�W�F�N�g

public:
	void FrameMove();								// ���t���[���̏���
	void Render();									// ��ʕ`��
	void UpDate();									// �`��p���W�l�ȂǍX�V

	void AddEffect(DWORD dwType, D3DXMATRIX matIn);	// �G�t�F�N�g�̒ǉ�
	void SubEffect();								// �G�t�F�N�g��������

	CEffect* GetListTop(){return m_pListTop;};		// �͂��߂̃G�t�F�N�g�ւ̃|�C���^��Ԃ�
	DWORD FtoDW(FLOAT f) { return *((DWORD*)&f); }	// �Ȃ񂩃L���X�g����

	CEffectManage(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEffectManage();

};

#endif // !defined(AFX_EFFECTMANAGE_H__0BE91682_45A4_42E5_8471_10CB2C8DFEF8__INCLUDED_)
