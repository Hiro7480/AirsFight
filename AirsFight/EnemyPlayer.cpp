//==========================================================
// EnemyPlayer.cpp
// Auther : ���� ���V
// Data   : 2002/05/05
//==========================================================
#include "EnemyPlayer.h"

//------------------------------------------------------
//	Name:	EnemyPlayer
//	Func:	�R���X�g���N�^
//	in:		LPDIRECT3DDEVICE8 d3dDevice	= D3D�f�o�C�X
//	Out:	�Ȃ�
//------------------------------------------------------
CEnemyPlayer::CEnemyPlayer(LPDIRECT3DDEVICE8 d3dDevice):CChara(d3dDevice)
{

}

//------------------------------------------------------
//	Name:	~EnemyPlayer
//	Func:	�f�X�g���N�^
//	in:		�Ȃ�
//	Out:	�Ȃ�
//------------------------------------------------------
CEnemyPlayer::~CEnemyPlayer()
{

}

//----------------------------------------------------------------------
//	Name:	FrameMoveGame
//	Func:	�Q�[�����̖��t���[���̏���
//	in:		CStage*			pStage			= �X�e�[�W�N���X�|�C���^
//			CBulManage*		pBulManage		= �e�Ǘ��N���X�|�C���^
//			CSpriteManage*	pSpriteManage	= �X�v���C�g�Ǘ��N���X�|�C���^
//			CEffectManage*	pEffectManage	= �G�t�F�N�g�Ǘ��N���X�|�C���^
//	Out:	�Ȃ�
//----------------------------------------------------------------------
void CEnemyPlayer::FrameMoveGame(CStage* pStage, CBulManage* pBulManage, 
			CSpriteManage* pSpriteManage,CEffectManage* pEffectManage)
{
	/* ���݂̏�Ԃɂ���ăG�t�F�N�g�𔭐������� */
	switch(m_nNowAction)
	{
	case DASH:
		pEffectManage->AddEffect(BOOST_A, m_matBase);
		break;

	case FLYGHT:
		pEffectManage->AddEffect(BOOST_B, m_matBase);
		break;
	}
}