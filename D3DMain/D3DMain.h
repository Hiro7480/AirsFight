//==========================================================
// D3DMain.h
// Auther : ���� ���V
// Data   : 2000/12/28
//==========================================================

#if !defined(AFX_D3DMAIN_H__FD26F1E7_215F_48A0_BE96_CA83FB10441A__INCLUDED_)
#define AFX_D3DMAIN_H__FD26F1E7_215F_48A0_BE96_CA83FB10441A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------
//	�C���N���[�h
//----------------------


#include "CompatiDX8.h"
#include <d3dx8.h>
#include <stdio.h>
#include "resource.h"
#include "define.h"





//----------------------
//	�萔��`
//----------------------
#define	STYLE_FULLSCREEN	(WS_POPUP | WS_VISIBLE)
#define	STYLE_WINDOW		((WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU)&~(WS_MAXIMIZEBOX | WS_THICKFRAME))
#define	FLAME_RATE			(16)						// �Q�[���X�s�[�h (�b��60�t���[��)
#define RENDER_FLAME_RATE	(16)		
#define	SCREEN_WIDTH		640								// ��ʉ���
#define	SCREEN_HEIGHT		480								// ��ʏc��

// {DC132EF5-D673-4021-A72E-041FCA2BF28B}
static const GUID c_guidDXGame = 
{ 0xdc132ef5, 0xd673, 0x4021, { 0xa7, 0x2e, 0x4, 0x1f, 0xca, 0x2b, 0xf2, 0x8b } };

#define MAX_NAME_SESSION		64		// �Z�N�V�������ő啶����
#define MAX_NAME_PLAYER			64		// �v���C���[���ő啶����
#define MAX_NAME_IP_ADDRESS		15		// �h�o�A�h���X���ő啶����
#define INPUT_STRING_MIN		3		// �Œ���͕�����

#define MAX_PLAYER				4		//	�ő哯���ڑ��l��

//----------------------------------------------------------
//		�f�[�^���M�p�\����
//----------------------------------------------------------
/* �`���b�g���b�Z�[�W���M�p */
struct TChat{
	DWORD dwDpnType;		// ���b�Z�[�W�^�C�v
	char  str[256];			// �`���b�g���b�Z�[�W
};

/* �J�n�M�����M�p �Ӗ��Ȃ��� */
struct TStart{
	DWORD	dwDpnType;		// ���b�Z�[�W�^�C�v
};

/* ���ʔԍ����M�p */
struct TID{
	DWORD	dwDpnType;		// ���b�Z�[�W�^�C�v
	//DPNID	dpnID;			// �h�c�i���O�j
	int		nIDNum;			// �A�Ԕԍ�
};

//----------------------------------------------------------
//	Name	: CD3DMain
//	Func	: DirectX���쐬����ۂ̃x�[�X�ƂȂ�N���X
//----------------------------------------------------------
class CD3DMain
{
private:
	TCHAR		szTitle[64];			// �E�B���h�E�̃^�C�g���o�[ �e�L�X�g
	TCHAR		szWindowClass[64];		// �E�B���h�E�N���X��
	int			m_nWndWidth;			// �E�B���h�E�̕��T�C�Y
	int			m_nWndHeight;			// �E�B���h�E�̍����T�C�Y

	HINSTANCE	m_hInst;				// ���݂̃C���X�^���X
	HWND		m_hWnd;					// ���C���E�B���h�E�̃n���h��
	bool		m_bWindowMode;			// TRUE:�E�C���h�E	FALSE:�t���X�N���[��

	bool		m_bAppActive;			// �E�B���h�E���A�N�e�B�u���ǂ���
	bool		m_bFpsFlg;				// FPS�̕\���t���O
	bool		m_bEndFlg;				// �A�v���P�[�V�����̏I���t���O�i�����Ă�Ԃ�false�j

	DWORD		m_dwThreadID;			// �X���b�h�̂h�c
	HANDLE		m_hThread;				// �X���b�h�̃n���h��
	bool		m_bThread;				// �X���b�h���s�����ǂ����̃t���O

	float		m_fFrameFps;			// �����X���b�h��FPS
	float		m_fRenderFps;			// �`��X���b�h��FPS
	bool		m_bRenderFlg;			// �`��\�t���O

	//HWND		m_hDlg;					// �`���b�g�_�C�A���O�p�n���h��

	/* �v���C�x�[�g���\�b�h */
	HRESULT	CleanAppli();				// �A�v���P�[�V�����̌�n��
	HRESULT	InitD3D();					// Direct3D�̏�����

protected:

	LPDIRECT3D8 		m_pD3D; 		// D3DDevice���N���G�C�g���邽�߂Ɏg����
	LPDIRECT3DDEVICE8	m_pd3dDevice; 	// D3D�f�o�C�X
	LPD3DXFONT			m_pd3dXFont;	// �f�o�b�O�p�t�H���g

	/* ���[�U�[��� */
	//int			m_nPlayerNum;							// �v���C���[���ʔԍ�
	//TCHAR		m_strPlayer[MAX_NAME_PLAYER+1];			// �v���C���[��
	//TCHAR		m_strSession[MAX_NAME_PLAYER+1];		// �Z�b�V������
	//TCHAR		m_strIPAddress[MAX_NAME_IP_ADDRESS+1];	// �h�o�A�h���X

	virtual HRESULT OneTimeInit(void){return S_OK;};	// ��񂾂��Ă΂�鏉����
	virtual HRESULT FrameMove(void){return S_OK;};		// ���t���[�����Ƃ̏���
	virtual HRESULT Render(void){return S_OK;};			// ��ʕ`��
	virtual HRESULT UpDate(void){return S_OK;};			// �`��p���̍X�V
	virtual HRESULT CleanUp(void){return S_OK;};		// �A�v���P�[�V�����I�����̏���

public:
	int		Run(void);							// �A�v���P�[�V�����̃��C�����[�v
	HRESULT	AllCreate(HINSTANCE hInst);			// �������S��
	void	FrameProc();						// �����p�X���b�h
	void	RenderProc();						// �`��p�X���b�h

	/* ���C���E�B���h�E�̃��b�Z�[�W���� */
	LRESULT	MsgProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam);

	CD3DMain();									// �R���X�g���N�^
};

#endif // !defined(AFX_D3DMAIN_H__FD26F1E7_215F_48A0_BE96_CA83FB10441A__INCLUDED_)
