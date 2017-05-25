#pragma once
#include "stdafx.h"

namespace basecross 
{
	//Abe20170421
	//--------------------------------------------------------------------------------------
	//	ステージセレクトのオブジェクト
	//　プレイヤーが操作する部分あるのでちょっと多め
	//--------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	//	フレームスプライト
	//--------------------------------------------------------------------------------------
	class SelectFlame : public GameObject
	{
	private :
		//座標（引数でVec2入れるけどSetPositionでVec3入れるし）
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_InitScale;
		//レイヤー
		int m_layer;
	public:
		SelectFlame(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale,int layer);

		void OnCreate() override;
	};

	//Abe20170525
	//--------------------------------------------------------------------------------------
	//	ロゴ
	//--------------------------------------------------------------------------------------
	class SelectLogo : public GameObject
	{
	private:
		//座標（引数でVec2入れるけどSetPositionでVec3入れるし）
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_InitScale;
		//レイヤー
		int m_layer;
	public:
		SelectLogo(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer);

		void OnCreate() override;
	};
	//Abe20170525

	//--------------------------------------------------------------------------------------
	//	プレイヤーの中心
	//--------------------------------------------------------------------------------------
	class SelectPlayer : public GameObject
	{
	private :
		//初期座標
		Vector3 m_InitPos;
		//初期サイズ
		Vector3 m_InitScale;
		//速度
		float m_Speed;

		//初期で離れてる距離
		float m_DifLength = 2;

		//回転速度
		float m_RotSpeedPerSec = 180;

		//プレイヤーの実態
		vector<shared_ptr<GameObject>> m_Player;

		//プレイヤーが合体する状態になってるか
		bool m_SandFlg = false;
		//ある程度近づいた後戻ってる状態か
		bool m_SandFinishFlg = false;
		//関数群
		void SandMove();
		//回転
		void Rot();

		//キャンセルしたときにくっつかないように
		bool m_CancelFlg = false;

		//Abe20170524
		//ステージの幅
		//左制限、右制限、上制限、下制限の順
		Vector4 MoveLimit = Vector4(-20, 66, 10, -36);
		//デバッグ文字表示オブジェ
		shared_ptr<GameObject> m_Debugtxt;
		//Abe20170524

	public :
		SelectPlayer(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, float speed);

		void OnCreate() override;
		void OnUpdate() override;

		//アップデート制御
		void SetPlayerUpdate(bool flg);

		//はさむフラグオン
		void SandFlgOn() { m_SandFlg = true; }
		//元の位置に戻るフラグオン
		void SandFinishFlgOn() { m_SandFinishFlg = true; }


		//座標移動関数
		void SetPos(Vector3);
		//座標とれる
		Vector3 GetPos();
		//動けるようにする関数
		void ActiveMove();
	};

	//--------------------------------------------------------------------------------------
	//	ステージの箱
	//--------------------------------------------------------------------------------------
	class StageBox : public GameObject
	{
	private :
		//初期座標
		Vector3 m_InitPos;
		//初期サイズ
		Vector3 m_InitScale;
		//ステージ番号
		int m_stagenumber;
		//プレイヤー当たってる数
		int m_PlayerHitNum = 0;
		//判定するフラグ
		bool m_PlayerHitFlg = false;
	public :
		StageBox(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, int num);

		void OnCreate()override;
		void OnUpdate()override;

		//アタリ判定(リブ)
		virtual void OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) override;

		//ステージに行くか確認する処理
		void CheckGo();
	};

	//--------------------------------------------------------------------------------------
	//	ステージ行くか確認するオブジェクト
	//--------------------------------------------------------------------------------------
	class GoStageCheck : public GameObject
	{
	private :
		//位置は固定するので書かない
		//大きさ(大きさ変えるアニメーション使うなら)
		Vector3 m_InitScale;

		//背景
		shared_ptr<GameObject> m_CheckBack;
		//中身
		shared_ptr<GameObject> m_CheckBoxIn;
		//カーソル
		shared_ptr<GameObject> m_Cursor;

		//選択してる番号 0でNo、1でYes
		int m_selectnum = 0;

		//Abe20170523
		//ステージ
		int m_stageNum = 0;
		//Abe20170523

		//表示されてるか
		bool m_Dispflg = false;

		//Abe20170525
		//それぞれの数
		//突撃
		shared_ptr<NumberSprite> m_TackleNumSpr;
		//玉撃つ
		shared_ptr<NumberSprite> m_ShotNumSpr;
		//テレポート
		shared_ptr<NumberSprite> m_TerepoNumSpr;
		//自爆
		shared_ptr<NumberSprite> m_BombNumSpr;
		//Abe20170525
	public :
		GoStageCheck(const shared_ptr<Stage>& StagePtr, Vector2 scale);

		void OnCreate()override;
		void OnUpdate()override;

		//スプライトとか出す
		void OpenCheck();

		//スプライトとか消す
		void CloseCheck();

		//Abe20170523
		//ステージ番号設定
		void SetStageNumber(int num) { m_stageNum = num; };
		//Abe20170523

		//Abe20170525
		//エネミーの数入れる
		void SetEnemyNum(int tackle, int shot, int terepo, int bomb);
		//Abe20170525

	};
	//Abe20170421

	//Abe20170427

	//--------------------------------------------------------------------------------------
	//	地面
	//--------------------------------------------------------------------------------------
	class SelectGroud : public GameObject
	{
	private :
		Vector3 m_Pos;
		Vector3 m_Scale;
	public :
		SelectGroud(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);

		void OnCreate() override;
		void OnUpdate() override;
	};
	//Abe20170427

}