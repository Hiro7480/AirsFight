//==========================================================
// Effect.cpp
// Auther : ���� ���V
// Data   : 2002/03/09
//==========================================================

#include "Effect.h"

//----------------------------------------------
//	Name:	CEffect
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out:	�Ȃ�
//----------------------------------------------
CEffect::CEffect(LPDIRECT3DDEVICE8 d3dDevice)
		:C3DGraphicObj(d3dDevice)
{
	m_pNext = NULL;					// ���ւ̃|�C���^��NULL��
}
//----------------------------------------------
//	Name:	~CEffect
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CEffect::~CEffect()
{
	SAFE_RELEASE(m_pPointVB);
	SAFE_RELEASE(m_pPointVBRender);
}

//----------------------------------------------
//	Name:	CreateBuffer
//	Func:	���_�o�b�t�@�̍쐬
//	in:		�Ȃ�
//	Out:	bool	= ����������TRUE��Ԃ�
//----------------------------------------------
bool CEffect::CreateBuffer()
{
	/* �����p���_�o�b�t�@�쐬 */
	if(m_pd3dDevice->CreateVertexBuffer(m_nParticleNum * sizeof(tagPointVertex),
				D3DUSAGE_POINTS, D3DFVF_POINTVERTEX, D3DPOOL_MANAGED , &m_pPointVB) != S_OK)
			return false;
	return true;
}

//----------------------------------------------
//	Name:	CreateBufferRender
//	Func:	�`��p���_�o�b�t�@�̍쐬
//	in:		�Ȃ�
//	Out:	bool	= ����������TRUE��Ԃ�
//----------------------------------------------
bool CEffect::CreateBufferRender()
{
	/* �`��p���_�o�b�t�@�̍쐬 */
	if(m_pd3dDevice->CreateVertexBuffer(m_nParticleNum * sizeof(tagPointVertex),
				D3DUSAGE_POINTS, D3DFVF_POINTVERTEX, D3DPOOL_MANAGED , &m_pPointVBRender) != S_OK)
		return false;

	return true;
}

//----------------------------------------------
//	Name:	IsDelete
//	Func:	�����邩�ǂ����̔���
//	in:		�Ȃ�
//	Out:	bool
//----------------------------------------------
bool CEffect::IsDelete()
{
	if(m_nLife <= 0)	return true;
	return				false;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CEffect::Render()
{
	/* ���[���h�}�g���b�N�X�̐ݒ� */
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matBase );
	/* �e�N�X�`���[�̐ݒ� */
	m_pd3dDevice->SetTexture(0, m_pTexture);

	/* �y�o�b�t�@�[�t���O�̔��� */	
	if(m_bZBufferFlg)
		m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	else
		m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	/* �`�� */
	m_pd3dDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(m_fSize));

	m_pd3dDevice->SetStreamSource(0, m_pPointVB, sizeof(tagPointVertex));
	m_pd3dDevice->SetVertexShader(D3DFVF_POINTVERTEX);
	m_pd3dDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_nParticleNum);

	/* �y�o�b�t�@��߂� */
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );	
}

//---------------------------------------------
//	Name:	UpDate
//	Func:	�`����̍X�V
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CEffect::UpDate()
{
	C3DGraphicObj::UpDate();

	tagPointVertex *pPointVertices1, *pPointVertices2;
	m_pPointVB->Lock(0, 0, (BYTE**)&pPointVertices1, 0);		// ���_�o�b�t�@�̃��b�N
	m_pPointVBRender->Lock(0, 0,(BYTE**)&pPointVertices2, 0);	// �`��p���_�o�b�t�@�̃��b�N

	/* �S�ăR�s�[���� */
	for (int i=0; i < m_nParticleNum; i++){
		pPointVertices2->v    =	pPointVertices1->v;
		pPointVertices2->color=	pPointVertices1->color;

		pPointVertices1++;
		pPointVertices2++;
	}

	m_pPointVB->Unlock();		// ���_�o�b�t�@�̃A�����b�N
	m_pPointVBRender->Unlock();	// �`��p���_�o�b�t�@�̃A�����b�N
}