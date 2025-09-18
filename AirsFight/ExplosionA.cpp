//==========================================================
// ExplosionA.cpp
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================
#include "ExplosionA.h"

//----------------------------------------------
//	Name:	CExplosionA
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3D�f�o�C�X
//			LPDIRECT3DTEXTURE8	pTexture	= �e�N�X�`��
//			D3DXMATRIX			matBase		= �}�g���N�X
//	Out:	�Ȃ�
//----------------------------------------------
CExplosionA::CExplosionA(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase)
			:CEffect(d3dDevice)
{
	CEffect::SetTexture(pTexture);				// �e�N�X�`���̃Z�b�g
	C3DGraphicObj::SetMatrix(matBase);			// �}�g���N�X�̃Z�b�g

	m_nParticleNum = 20;						// �p�[�e�B�N�����̃Z�b�g
	m_fSize = 3.0f;								// �T�C�Y�Z�b�g
	m_nMaxLife = 30;							// �ő吶���J�E���^�[�̃Z�b�g
	m_nLife = m_nMaxLife;						// �����J�E���^�[�̏�����
	m_nInitR = 255;								// �����F�̃Z�b�g
	m_nInitG = 150;
	m_nInitB = 0;

	while(!CEffect::CreateBuffer());			// ���_�o�b�t�@�̍쐬(�ł���܂ő�����)
	while(!CEffect::CreateBufferRender());		// �`��p���_�o�b�t�@�̍쐬(�ł���܂ő�����)

	InitParticle();								// �������W�A�����ړ��ʂ̐ݒ�
}

//----------------------------------------------
//	Name:	~CExplosionA
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CExplosionA::~CExplosionA()
{

}

//---------------------------------------------
//	Name:	InitParticle
//	Func:	�p�[�e�B�N���̏������W�A�����ړ��ʂ̐ݒ�
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CExplosionA::InitParticle()
{
	// �����l�Ȃǂ̎Z�o
	D3DXVECTOR3	vecTmp;
	for(int i=0; i<m_nParticleNum; i++)
	{
		// ���ꂼ��̃X�v���C�g�̈ړ��ʂ������_���Ō���
		vecTmp.x = float(rand()%10-5)/20.0f;
		vecTmp.y = float(rand()%8+3)/10.0f;
		vecTmp.z = -1.0f;

		D3DXVec3Normalize(&vecTmp, &vecTmp);		// �P�ʃx�N�g����
		vecTmp.z += (float(rand()%3)/10.0f);		// ���x�ɍ�������
		vecTmp *= 0.2f;								// �S�̓I�ɑ��x��������

		// ���܂����ړ��ʂ����ꂼ��̈ړ��ʂɊi�[���Ă���
		m_Particle[i].dir = vecTmp;

		// �������W�l�̊i�[
		m_Particle[i].pos = D3DXVECTOR3(0,0,0);

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
void CExplosionA::FrameMove()
{
	int i;

	// �p�[�e�B�N���̈ړ�
	for(i=0; i<m_nParticleNum; i++)
	{
		m_Particle[i].dir.y -= 0.02f;			// �ړ��ʂ̍X�V
		m_Particle[i].pos += m_Particle[i].dir;	// �ʒu�̍X�V

		m_Particle[i].r -= (m_nInitR / m_nMaxLife);		// �F�̍X�V
		m_Particle[i].g -= (m_nInitG / m_nMaxLife);
		m_Particle[i].b -= (m_nInitB / m_nMaxLife);
	}

	// ���_�o�b�t�@�̒��g���X�V����
	tagPointVertex* pPointVertices;
	CEffect::GetVB()->Lock(0, 0, (BYTE**)&pPointVertices, 0);
	for (i = 0; i < m_nParticleNum; i++){
		pPointVertices->v = m_Particle[i].pos;
		pPointVertices->color = D3DCOLOR_ARGB(255, m_Particle[i].r, m_Particle[i].g, m_Particle[i].b);
		pPointVertices++;
	}
	CEffect::GetVB()->Unlock();

	// �����J�E���^�[�̃f�N�������g
	m_nLife--;

}
