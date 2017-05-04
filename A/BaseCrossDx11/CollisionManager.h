//************************************
//*		作成日：2017/04/30
//*		作成者：Abe
//*		内容：
//*		アタリ判定(通常円形とはさむ時)
//************************************


#pragma once
#include "stdafx.h"

namespace basecross 
{
	//************************************
	//	円形アタリ判定
	//	距離で判定、座標のマイナス反転して加算した分が2(プレイヤーの半径[1]*2)以下のもののみ判定
	//************************************
	class CollisionManager : public GameObject
	{
	private :
		//プレイヤーのアクセサー的なの
		shared_ptr<GameObject> m_Player1;		//左？たかいとこでやいてんの？
		shared_ptr<GameObject> m_Player2;		//右？はっきりわかんだね

		//判定するかどうか
		bool m_ActiveFlg = true;

		//デバッグ文字表示オブジェ
		shared_ptr<DebugTxt> m_Debugtxt;

		//ぶつかった後の処理、引数は挟んだオブジェクトと当たったプレイヤーの番号
		void CollisionAfter(shared_ptr<GameObject>,int);
	public :
		CollisionManager(const shared_ptr<Stage>& StagePtr);

		void OnCreate() override;
		void OnUpdate() override;

		//一応判定しないようにする関数も作っておく
		void SetActive(bool flg) { m_ActiveFlg = flg; }
	};

	//************************************
	//	はさむ時の判定
	//	資料「挟まれる判定考察.txt」を参照
	//	処理速度を上げるため、上下(Y)軸に関しての判定はしない
	//************************************

	class CollisionSand : public GameObject 
	{
	private :
		//プレイヤーのアクセサー的なの
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;

		//判定するかどうか
		bool m_ActiveFlg = true;

		//デバッグ文字表示オブジェ
		shared_ptr<DebugTxt> m_Debugtxt;

		//挟んだ後の処理引数は挟んだオブジェクト
		void SandAfter(shared_ptr<GameObject>);
	public : 
		CollisionSand(const shared_ptr<Stage>& StagePtr);
		void OnCreate() override;
		void OnUpdate() override;

		//起動設定
		void SetActive(bool flg) { m_ActiveFlg = flg; }
	};
}