//==========================================================
// OrderSprite.cpp
// Auther : ���� ���V
// Data   : 2002/05/20
//==========================================================

#include "OrderSprite.h"

//------------------------------------------------------
//	Name:	COrderSprite
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8	d3dDevice = D3D�f�o�C�X
//			int					nOrder    = ����
//			TCHAR*				strName   = ���O
//			int					nDeadNum  = ���񂾐�
//	Out:	�Ȃ�
//------------------------------------------------------
COrderSprite::COrderSprite(LPDIRECT3DDEVICE8 d3dDevice, int nOrder, TCHAR* strName, int nDeadNum)
{
	m_nOrder = nOrder;			/* ���ʂ̊i�[ */
	strcpy(m_strName, strName);	/* ���O�̊i�[ */
	m_nDeadNum = nDeadNum;		/* ���񂾐��̊i�[ */

	/* �����̏��ʂ���A��{�`����W�l���Z�o */
	m_vecBase.x = 100;
	m_vecBase.y = (float)(140+(90*(m_nOrder-1)));

	/* ���ʃt�H�[�}�b�g�̍쐬 */
	m_pFormat = new CSprite(d3dDevice, "Data\\Ending\\OrderFormat.png");
	m_pFormat->SetVec(m_vecBase);
	m_pFormat->SetRec(0, 50*(m_nOrder-1), 400, 50*m_nOrder);

	/* ���O�t�H���g�̍쐬 */
	m_pName = new CFont(d3dDevice, "�l�r �S�V�b�N");
	m_pName->SetString(strName);
	m_pName->SetRec((int)m_vecBase.x+120, (int)m_vecBase.y+20,
					(int)m_vecBase.x+300, (int)m_vecBase.y+50);

	switch(nOrder)
	{
		case 1:	m_pName->SetColor(64,  0,  0);	break;
		case 2: m_pName->SetColor(64, 64,  0);	break;
		case 3: m_pName->SetColor( 0, 64,  0);	break;
		case 4: m_pName->SetColor( 0,  0, 64);	break;
	}

	/* ���񂾐��t�H���g�̍쐬 */
	m_pDeadNum = new CFont(d3dDevice, "�l�r �S�V�b�N");
	m_pDeadNum->SetString(nDeadNum);

	m_pDeadNum->SetRec(	(int)m_vecBase.x+350, (int)m_vecBase.y+20,
						(int)m_vecBase.x+400, (int)m_vecBase.y+50);

	switch(nOrder)
	{
		case 1:	m_pDeadNum->SetColor(64,  0,  0);	break;
		case 2: m_pDeadNum->SetColor(64, 64,  0);	break;
		case 3: m_pDeadNum->SetColor( 0, 64,  0);	break;
		case 4: m_pDeadNum->SetColor( 0,  0, 64);	break;
	}

}

//------------------------------------------------------
//	Name:	~COrderSprite
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------
COrderSprite::~COrderSprite()
{
	/* �g�p�����������̊J�� */
	SAFE_DELETE(m_pFormat);
	SAFE_DELETE(m_pName);
	SAFE_DELETE(m_pDeadNum);
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void COrderSprite::FrameMove()
{
	m_pFormat->FrameMove();
	m_pName->FrameMove();
	m_pDeadNum->FrameMove();
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void COrderSprite::Render()
{
	m_pFormat->Render();
	m_pName->Render();
	m_pDeadNum->Render();
}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	Out:	�Ȃ�
//	In:		�Ȃ�
//----------------------------------------------
void COrderSprite::UpDate()
{
	m_pFormat->UpDate();
	m_pName->UpDate();
	m_pDeadNum->UpDate();
}