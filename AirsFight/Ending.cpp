//==========================================================
// Ending.h
// Auther : ���� ���V
// Data   : 2002/05/20
//==========================================================
#include "Ending.h"

//------------------------------------------------------
//	Name:	CEnding
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice = D3D�f�o�C�X
//	Out:	�Ȃ�
//------------------------------------------------------
CEnding::CEnding(LPDIRECT3DDEVICE8 d3dDevice)
	  :GameStatus(d3dDevice)
{
	/* �v���C���[���̊i�[ */
	strcpy(m_tagChara[0].strName, "PLAYER");
	strcpy(m_tagChara[1].strName, "COMPUTER1");
	strcpy(m_tagChara[2].strName, "COMPUTER2");
	strcpy(m_tagChara[3].strName, "COMPUTER3");

}

//----------------------------------------------
//	Name:	~CEnding
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
CEnding::~CEnding()
{
	/* �g�p�����������̊J�� */
	for(int i=0; i<4; i++)	SAFE_DELETE(m_pOrder[i]);

	SAFE_DELETE(m_pLogo);
	SAFE_DELETE(m_pBackGround);
}

//----------------------------------------------
//	Name:	InitOrder
//	Func:	���ʂɊւ��鏉����
//	In:		int nDeadNum1 = �P�l�ڂ̎��񂾐�
//			int nDeadNum2 = �Q�l�ڂ̎��񂾐�
//			int nDeadNum3 = �R�l�ڂ̎��񂾐�
//			int nDeadNum4 = �S�l�ڂ̎��񂾐�
//	Out:	HRESULT
//----------------------------------------------
HRESULT CEnding::InitOrder(int nDeadNum1, int nDeadNum2, int nDeadNum3, int nDeadNum4)
{
	/* �Ƃ肠�������񂾐����i�[���� */
	m_tagChara[0].nDeadNum = nDeadNum1;
	m_tagChara[1].nDeadNum = nDeadNum2;
	m_tagChara[2].nDeadNum = nDeadNum3;
	m_tagChara[3].nDeadNum = nDeadNum4;

	/* ���񂾐��̑傫������A���ʂ����߂� */
	bool	bOKFlg[4] = {false, false, false, false};
	int		nMaxDeadNum = 0;
	int		nMaxNumber;
	int		i;

	/* �S�ʂ��珇�Ɍ��߂Ă��� */
	for(i=4; i>0; i--)
	{
		for(int j=0; j<4; j++)
		{
			if(nMaxDeadNum <= m_tagChara[j].nDeadNum && !bOKFlg[j])
			{
				nMaxDeadNum = m_tagChara[j].nDeadNum;
				nMaxNumber = j;
			}
		}
		/* �ő�̐��l������������A���ʂ��i�[���� */
		bOKFlg[nMaxNumber] = true;			// ����t���O�𗧂Ă�
		m_tagChara[nMaxNumber].nOrder = i;	// ���ʂ��i�[
		nMaxDeadNum = 0;					// �ő�l�̏�����
	}

	/* �i�[�������ʂ����ɁA���ʕ\���쐬���� */
	for(i=0; i<4; i++)
		m_pOrder[i] = new COrderSprite(	m_pd3dDevice, m_tagChara[i].nOrder,
										m_tagChara[i].strName,m_tagChara[i].nDeadNum);

	/* �w�i�̍쐬 */
	m_pBackGround = new CScrollBG(m_pd3dDevice, const_cast<TCHAR*>("data\\Ending\\EndingBG.png"), 256, 256);
	m_pBackGround->SetVecDir(D3DXVECTOR2(0.0, 1.0));

	/* ���S�̍쐬 */
	m_pLogo = new CSprite(m_pd3dDevice, const_cast<TCHAR*>("Data\\Ending\\EndingLogo.png"));
	m_pLogo->SetVec(D3DXVECTOR2(64, 30));
	m_pLogo->SetRec(0,0,512,64);

	return S_OK;
}

//----------------------------------------------
//	Name:	FrameMove
//	Func:	���t���[���̏���
//	In:		�Ȃ�
//	Out:	int = ��ԕύX���ʎq
//----------------------------------------------
int CEnding::FrameMove()
{
	/* ���^�[������������^�C�g���ֈڍs���� */
	if(GetAsyncKeyState(VK_RETURN) & 0x0001)
		return CHANGE_TITLE;

	/* �w�i�𓮂��� */
	m_pBackGround->FrameMove();

	return NO_CHANGE;
}

//----------------------------------------------
//	Name:	Render
//	Func:	�`�揈��
//	In:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CEnding::Render()
{
	m_pBackGround->Render();
	m_pLogo->Render();

	for(int i=0; i<4; i++)
		m_pOrder[i]->Render();

}

//----------------------------------------------
//	Name:	UpDate
//	Func:	�f�[�^�X�V
//	In:		�Ȃ�
//	Out:	�Ȃ�
//----------------------------------------------
void CEnding::UpDate()
{
	m_pBackGround->UpDate();
	m_pLogo->UpDate();

	for(int i=0; i<4; i++)
		m_pOrder[i]->UpDate();
}
