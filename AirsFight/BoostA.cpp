//==========================================================
// BoostA.cpp
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================

#include "BoostA.h"

//----------------------------------------------
//	Name:	CBoostA
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3D�f�o�C�X
//			LPDIRECT3DTEXTURE8	pTexture	= �e�N�X�`��
//			D3DXMATRIX			matBase		= �}�g���N�X
//	Out:	�Ȃ�
//----------------------------------------------
CBoostA::CBoostA(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase)
		:CEffect(d3dDevice)
{
	CEffect::SetTexture(pTexture);				// �e�N�X�`���̃Z�b�g

	D3DXMATRIX	matTmp = matBase;
	matTmp._42 -= 5.0f;
	C3DGraphicObj::SetMatrix(matTmp);			// �}�g���N�X�̃Z�b�g

	m_nParticleNum = 10;						// �p�[�e�B�N�����̃Z�b�g
	m_fSize = 2.0f;								// �T�C�Y�Z�b�g
	m_nMaxLife = 20;							// �ő吶���J�E���^�[�̃Z�b�g
	m_nLife = m_nMaxLife;						// �����J�E���^�[�̏�����
	m_nInitR = 128;								// �����F�̃Z�b�g
	m_nInitG = 128;
	m_nInitB = 255;

	while(!CEffect::CreateBuffer());			// ���_�o�b�t�@�̍쐬(�ł���܂ő�����)
	while(!CEffect::CreateBufferRender());		// �`��p���_�o�b�t�@�̍쐬(�ł���܂ő�����)

	InitParticle();								// �������W�A�����ړ��ʂ̐ݒ�
}

//----------------------------------------------
//	Name:	~CBoostA
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CBoostA::~CBoostA()
{

}

//---------------------------------------------
//	Name:	InitParticle
//	Func:	�p�[�e�B�N���̏������W�A�����ړ��ʂ̐ݒ�
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CBoostA::InitParticle()
{
	// �����l�Ȃǂ̎Z�o
	D3DXVECTOR3	vecTmp;
	for(int i=0; i<m_nParticleNum; i++)
	{
		// �������W�l�̊i�[
		if(i < m_nParticleNum/2)	m_Particle[i].pos = D3DXVECTOR3( 1.0f, 0, 0);
		else						m_Particle[i].pos = D3DXVECTOR3(-1.0f, 0, 0);

		// ���������x�̊i�[
		m_Particle[i].r = m_nInitR;
		m_Particle[i].g = m_nInitG;
		m_Particle[i].b = m_nInitB;

	}
}

//---------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CBoostA::FrameMove()
{
	int i;

	/* �p�[�e�B�N���̈ړ� */
	for(i=0; i<m_nParticleNum; i++)
	{
		/* �ړ��ʂ̍X�V */
		m_Particle[i].dir.x = float(rand()%20-10)/20.0f;
		m_Particle[i].dir.y = float(rand()%20)/50.0f;
		m_Particle[i].dir.z = float(rand()%20-10)/20.0f;

		/* �ʒu�̍X�V */
		m_Particle[i].pos += m_Particle[i].dir;

		/* �F�̍X�V */
		m_Particle[i].r -= (m_nInitR / m_nMaxLife);
		m_Particle[i].g -= (m_nInitG / m_nMaxLife);
		m_Particle[i].b -= (m_nInitB / m_nMaxLife);
	}

	/* ���_�o�b�t�@�̒��g���X�V���� */
	tagPointVertex* pPointVertices;
	CEffect::GetVB()->Lock(0, 0, (BYTE**)&pPointVertices, 0);
	for (i = 0; i < m_nParticleNum; i++){
		pPointVertices->v = m_Particle[i].pos;
		pPointVertices->color = D3DCOLOR_ARGB(255, m_Particle[i].r, m_Particle[i].g, m_Particle[i].b);
		pPointVertices++;
	}
	CEffect::GetVB()->Unlock();

	/* �����J�E���^�[�̃f�N�������g */
	m_nLife--;

}