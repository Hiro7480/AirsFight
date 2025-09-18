//==========================================================
// Revival.cpp
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================
#include "Revival.h"

//----------------------------------------------
//	Name:	CRevival
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	d3dDevice	= D3D�f�o�C�X
//			LPDIRECT3DTEXTURE8	pTexture	= �e�N�X�`��
//			D3DXMATRIX			matBase		= �}�g���N�X
//	Out:	�Ȃ�
//----------------------------------------------
CRevival::CRevival(LPDIRECT3DDEVICE8 d3dDevice, LPDIRECT3DTEXTURE8 pTexture, D3DXMATRIX matBase)
			:CEffect(d3dDevice)
{
	CEffect::SetTexture(pTexture);				// �e�N�X�`���̃Z�b�g
	C3DGraphicObj::SetMatrix(matBase);			// �}�g���N�X�̃Z�b�g

	m_nParticleNum = 100;						// �p�[�e�B�N�����̃Z�b�g
	m_fSize = 2.0f;								// �T�C�Y�Z�b�g
	m_nMaxLife = 50;							// �ő吶���J�E���^�[�̃Z�b�g
	m_nLife = m_nMaxLife;						// �����J�E���^�[�̏�����
	m_nInitR = 255;								// �����F�̃Z�b�g
	m_nInitG = 100;
	m_nInitB = 100;

	while(!CEffect::CreateBuffer());			// ���_�o�b�t�@�̍쐬(�ł���܂ő�����)
	while(!CEffect::CreateBufferRender());		// �`��p���_�o�b�t�@�̍쐬(�ł���܂ő�����)

	InitParticle();								// �������W�A�����ړ��ʂ̐ݒ�
}

//----------------------------------------------
//	Name:	~CRevival
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CRevival::~CRevival()
{

}

//---------------------------------------------
//	Name:	InitParticle
//	Func:	�p�[�e�B�N���̏������W�A�����ړ��ʂ̐ݒ�
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CRevival::InitParticle()
{
	// �����l�Ȃǂ̎Z�o
	D3DXVECTOR3	vecTmp;
	int			nRotate;

	for(int i=0; i<m_nParticleNum; i++)
	{

		/* �����ʒu�̌v�Z */
		nRotate = (int)((360.0f / 100.0f) * i);	

		// �p�x����P�ʕ����x�N�g���̎Z�o
		vecTmp *= 0;
		vecTmp.x = float(sin(D3DXToRadian(nRotate)) * 5.0);
		vecTmp.z = float(cos(D3DXToRadian(nRotate)) * 5.0);

		/* �����ʒu�Ƃ��Ċi�[ */
		m_Particle[i].pos = vecTmp;

		// ���ꂼ��̃X�v���C�g�̈ړ��ʂ������_���Ō���
		vecTmp.x = 0.0f;//float(rand()%2-1)/10.0f;
		vecTmp.y = float(rand()%3+5)/30.0f;
		vecTmp.z = 0.0f;//float(rand()%2-1)/10.0f;

		// ���܂����ړ��ʂ����ꂼ��̈ړ��ʂɊi�[���Ă���
		m_Particle[i].dir = vecTmp;

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
void CRevival::FrameMove()
{
	// �p�[�e�B�N���̈ړ�
	for(int i=0; i<m_nParticleNum; i++)
	{
		m_Particle[i].pos += m_Particle[i].dir;			// �ʒu�̍X�V

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
