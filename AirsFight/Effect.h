//==========================================================
// Effect.h
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================

#if !defined(AFX_EFFECT_H__FBF1B9C6_9BEB_436F_8CCA_0EF2D335973B__INCLUDED_)
#define AFX_EFFECT_H__FBF1B9C6_9BEB_436F_8CCA_0EF2D335973B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "CompatiDX8.h"
#include <d3dx8.h>
#include "3DGraphicObj.h"
#include "define.h"

//----------------------------------------------
//	�}�N����`
//----------------------------------------------
#define D3DFVF_POINTVERTEX 		(D3DFVF_XYZ | D3DFVF_DIFFUSE)

//----------------------------------------------
//	Name:	tagPointVertex
//	Func:	���_�t�H�[�}�b�g�\����
//----------------------------------------------
typedef struct{
	D3DXVECTOR3	v;
	D3DCOLOR	color;
}tagPointVertex;

//----------------------------------------------
//	Name:	tagParticle
//	Func:	���_���
//----------------------------------------------
typedef struct {
	D3DXVECTOR3		pos;		// �p�[�e�B�N�����W
	D3DXVECTOR3		dir;		// �p�[�e�B�N���ړ���
	unsigned char	r;			// �ԐF���
	unsigned char	g;			// �ΐF���
	unsigned char	b;			// �F���
}tagParticle;

//----------------------------------------------
//	Name:	CEffect
//	Func:	���܂��܂ȃG�t�F�N�g�̊��N���X
//----------------------------------------------
class CEffect:public C3DGraphicObj
{
private:
	CEffect*				m_pNext;			// ���̃G�t�F�N�g�ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER8	m_pPointVB;			// ���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER8	m_pPointVBRender;	// �`��p���_�o�b�t�@
	LPDIRECT3DTEXTURE8		m_pTexture;			// �e�N�X�`��(�Q�Ɨp)
	bool					m_bZBufferFlg;		// �y�o�b�t�@�t���O

protected:
	int						m_nParticleNum;		// �p�[�e�B�N���̐�
	int						m_nMaxLife;			// �ő吶������
	int						m_nLife;			// �����J�E���^
	float					m_fSize;			// �T�C�Y
	int						m_nInitR;			// �����ԐF���
	int						m_nInitG;			// �����ΐF���
	int						m_nInitB;			// �����F���

public:
	virtual void FrameMove(){};				// ���t���[���̏���
	virtual void Render();					// �`�揈��
	void	UpDate();						// �`����̍X�V
	bool	IsDelete();						// �����邩�ǂ����̔���

	bool CreateBuffer();					// ���_�o�b�t�@�̍쐬
	bool CreateBufferRender();				// �`��p���_�o�b�t�@�̍쐬

	/* �A�N�Z�X�֐� */
	void SetDevice(LPDIRECT3DDEVICE8 d3dDevice){m_pd3dDevice = d3dDevice;};	// �f�o�C�X�̃Z�b�g
	void SetZBuffer(bool sw){m_bZBufferFlg = sw;};							// �y�o�b�t�@�[�ݒ�
	void SetTexture(LPDIRECT3DTEXTURE8 pTexture){m_pTexture = pTexture;};	// �e�N�X�`���̃Z�b�g
	void SetNext(CEffect* pEffect){m_pNext = pEffect;};						// ���̃|�C���^���Z�b�g

	LPDIRECT3DVERTEXBUFFER8 GetVB(){return m_pPointVB;};					// ���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER8 GetVBR(){return m_pPointVBRender;};				// �`��p���_�o�b�t�@�̎擾
	CEffect* GetNext(){return m_pNext;};									// ���̃|�C���^��Ԃ�
	DWORD FtoDW(FLOAT f) { return *((DWORD*)&f); }							// �Ȃ񂩃L���X�g����

	CEffect(LPDIRECT3DDEVICE8 d3dDevice);
	virtual ~CEffect();
};

#endif // !defined(AFX_EFFECT_H__FBF1B9C6_9BEB_436F_8CCA_0EF2D335973B__INCLUDED_)
