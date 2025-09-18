//==========================================================
// Define.h
// Auther : ���� ���V
// Data   : 2002/01/03
//==========================================================

#ifndef	_DEFINE__H
#define _DEFINE__H

//------------------------------
//		�萔��`
//------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)      { if(p) { delete (p);     (p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)		{ if(p) { (p)->Release(); (p)=NULL; } }
#endif

/* ���M���b�Z�[�W�^�C�v */
enum MSG_TYPE{
	CHAT_MSG,				// �`���b�g���b�Z�[�W	�S�����S��
	CHAT_START,				// �J�n�M��				�z�X�g���S��	
	CHAT_ID,				// �h�c�A�Ԃ̐U�蕪��	�z�X�g���S��

	MENU_SELECT,			// �I���L�����̏��		�S�����S��
	MENU_READY,				// ����OK				�S�����S��

	GAME_READY,				// ����OK�M��			�S�����S��
	GAME_CHARA,				// �L�����N�^�f�[�^		�S�����S��
	GAME_BULLET,			// �e���ːM��			�S�����S��
	GAME_HIT,				// �e��e���b�Z�[�W
	GAME_EFFECT
};

#endif