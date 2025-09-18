//==========================================================
// Define.h
// Auther : 桜井 博之
// Data   : 2002/01/03
//==========================================================

#ifndef	_DEFINE__H
#define _DEFINE__H

//------------------------------
//		定数定義
//------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)      { if(p) { delete (p);     (p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)		{ if(p) { (p)->Release(); (p)=NULL; } }
#endif

/* 送信メッセージタイプ */
enum MSG_TYPE{
	CHAT_MSG,				// チャットメッセージ	全員→全員
	CHAT_START,				// 開始信号				ホスト→全員	
	CHAT_ID,				// ＩＤ連番の振り分け	ホスト→全員

	MENU_SELECT,			// 選択キャラの情報		全員→全員
	MENU_READY,				// 準備OK				全員→全員

	GAME_READY,				// 準備OK信号			全員→全員
	GAME_CHARA,				// キャラクタデータ		全員→全員
	GAME_BULLET,			// 弾発射信号			全員→全員
	GAME_HIT,				// 弾被弾メッセージ
	GAME_EFFECT
};

#endif