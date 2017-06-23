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
	private:
		//座標（引数でVec2入れるけどSetPositionでVec3入れるし）
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_InitScale;
		//レイヤー
		int m_layer;
	public:
		SelectFlame(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer);

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
	private:
		//初期座標
		Vector3 m_InitPos;
		//初期サイズ
		Vector3 m_InitScale;
		//速度
		float m_Speed;

		//初期で離れてる距離
		float m_DifLength = 2;
		//距離
		float m_dist = 2;

		//プレイヤーの実態
		vector<shared_ptr<GameObject>> m_Player;
		//初期プレヤー位置
		vector<Vector3> m_InitPlayerPos;
		//プレイヤーが合体する状態になってるか
		bool m_SandFlg = false;
		//ある程度近づいた後戻ってる状態か
		bool m_SandFinishFlg = false;

		//キャンセルしたときにくっつかないように
		bool m_CancelFlg = false;

		//Abe20170524
		//ステージの幅
		//左制限、右制限、上制限、下制限の順
		Vector4 MoveLimit = Vector4(-20, 66, 10, -36);
		//デバッグ文字表示オブジェ
		shared_ptr<GameObject> m_Debugtxt;
		//Abe20170524

		bool m_InitMoveFlg = true;
		bool m_Model_flg = true;
		bool m_Animeflg = true;
		bool m_WaitFlg = true;

		//右の移動最大値と最小値と初期位置の設定
		Vector3 m_RightSandMinit = Vector3(0, 0, 0);
		Vector3 m_RightLeaveMax = Vector3(0, 0, 0);
		Vector3 m_RightInitPos = Vector3(0, 0, 0);
		//左の移動最大値と最小値と初期位置の設定
		Vector3 m_leftSandMinit = Vector3(0, 0, 0);
		Vector3 m_leftLeaveMax = Vector3(0, 0, 0);
		Vector3 m_leftInitPos = Vector3(0, 0, 0);
		int StateNam = 0;
		int selecflg = true;

	public:
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
		void InitPosMove();
		void SandMove();
		void LeaveMove();
		void SetLeaveMove(bool OnTrue) { m_InitMoveFlg = OnTrue; };
		//モデルの最初の向き
		void Model();
		void AnimationWait();
		bool UpdateAnyAnimation();
		bool UpdateAnyAnimation2();
		//ステージ選択時にキャンセルが押されたときにスイッチの内容を書き換えるセッター
		void SetChangeNum(int ChangNum) { StateNam = ChangNum; };

	};
	//--------------------------------------------------------------------------------------
	//	ステージ難易度とステージ選択
	//--------------------------------------------------------------------------------------
	class StageModeControl :public GameObject
	{
	private:
		//難易度
		vector<int> m_Type;
		//ステージ種類
		vector<shared_ptr<GameObject>> m_Easy;
		vector<shared_ptr<GameObject>> m_Normal;
		vector<shared_ptr<GameObject>> m_Hard;
		//各ステージ種類の限界値
		int m_AddEasy = 0;
		int m_AddNormal = 0;
		int m_AddHard = 0;
		//ステージBOXの基準値
		Vector3 m_EasyPosCenter = Vector3(0, 0, 0);
		Vector3 m_EasyPosUP = Vector3(0, 0, 0);
		Vector3 m_EasyPosDown = Vector3(0, 0, 0);
		Vector3 m_EasyOtherPos = Vector3(0, 0, 0);
		Vector3 m_EasyTopPos = Vector3(0, 0, 0);
		//ノーマル
		Vector3 m_NormalPosCenter = Vector3(0, 0, 0);
		Vector3 m_NormalPosUP = Vector3(0, 0, 0);
		Vector3 m_NormalPosDown = Vector3(0, 0, 0);
		Vector3 m_NormalOtherPos = Vector3(0, 0, 0);
		Vector3 m_NormalTopPos = Vector3(0, 0, 0);
		//ハード
		Vector3 m_HardPosCenter = Vector3(0, 0, 0);
		Vector3 m_HardPosUP = Vector3(0, 0, 0);
		Vector3 m_HardPosDown = Vector3(0, 0, 0);
		Vector3 m_HardOtherPos = Vector3(0, 0, 0);
		Vector3 m_HardTopPos = Vector3(0, 0, 0);
		//ステージ選択用
		int m_EasyStageCenter = 0;
		int m_EasyStageUP = 0;
		int m_EasyStageDown = 0;
		int m_NormalStageCenter = 0;
		int m_NormalStageUP = 0;
		int m_NormalStageDown = 0;
		int m_HardStageCenter = 0;
		int m_HardStageUP = 0;
		int m_HardStageDown = 0;
		//配列指定用
		int m_NormalUP = 0;
		int m_NormalDown = 0;
		//難易度の移動が可能か
		bool m_ModeMove = false;
		//基準
		Vector3 m_CenterScalse = Vector3(2, 2, 2);
		Vector3 m_NoCenterScalse = Vector3(1, 1, 1);
		//はじめだけ入るフラグ
		bool InitOneflg = true;
		//要素数の検出　センター
		int m_ElementCenter = 0;
		int m_ElementUp = 0;
		int m_ElementDown = 0;
		int m_ElementTop = 0;
		//移動スピード
		float m_MoveSpeed = 0;
		//配列から取る位置の保存
		Vector3 m_Center = Vector3(0, 0, 0);
		Vector3 m_Up = Vector3(0, 0, 0);
		Vector3 m_Down = Vector3(0, 0, 0);
		Vector3 m_Top = Vector3(0, 0, 0);
		bool m_Flg = false;
		bool m_ElementNumTopFlg = false;
		//なんのステージがセンターにいるのか？ センター:true それ以外:false　StageBoxクラスで使用　
		int m_CenterStageNum = 0;
		//難易度の移動終わりのフラグ
		bool m_ModeMoveEnd = true;
		bool m_GetModeflg = true;
		bool m_StageMoveEnd = true;
		//スティックが元に戻った（0.2より小さい-0.2より大きい）
		bool m_StickDown = false;
		//押され続けてたときのflg
		bool m_APush = false;
		bool m_KeepApudh = false;
		//Aが押し続けてなければfalseになり押し続けている検証をしない
		bool m_KeepPushing = true;
	public:
		StageModeControl(const shared_ptr<Stage>& StagePtr);
		~StageModeControl() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//イージーのステージBOXの配置
		void EasySelect();
		void NormalSelect();
		void HardSelect();

		//難易度の移動ができるかを返すゲッタ
		bool GetModeMove() { return m_ModeMove; };

		//位置の設定
		void  StandardEasyPos();
		void StandardNormalPos();
		void StandardHardPos();
		//最大と最小値を超えていないかを見る関数
		int ExceedNum(int MIni, int Max, int Num);
		//センターから他の場所の要素を検出
		void ElementNum(int Mini, int Max, int CenterNum);
		//移動処理
		void StageMove();
		void EasyMove();
		void NormalMove();
		void EasySideMove();
		void NormalSideMove();
		void HardMove();
		void HardSideMove();
		//拡大縮小処理
		void EasyScale();
		void NormalScale();
		void HardScale();
		//初期配置
		void Init();
		void InitSetCenter();
		void InitSetUp();
		void InitSetDown();
		void InitSetOther();
		//難易度の回転が終わったときのフラグ
		bool ModeMoveEnd() { return m_ModeMoveEnd; };
		bool StageEndMove() { return m_StageMoveEnd; };

	};

	//--------------------------------------------------------------------------------------
	//	ステージ難易度のスプライト ステージモード
	//--------------------------------------------------------------------------------------
	class ModeSelect : public GameObject
	{
	private:
		Vector3 m_Pos = Vector3(0, 0, 0);
		Vector3 m_Scale = Vector3(0, 0, 0);
		bool m_Centerflg = false;
		bool m_Liftflg = false;
		bool m_Rightflg = false;
		int m_ModeNum = 0;
		int m_NowModeNum = 0;
		int m_MoveNum = 0;
		//3つの規定位置
		//中心
		Vector3 m_CenterPos = Vector3(0, 0, 0);
		//右
		Vector3 m_RightPos = Vector3(10, 1, 0);
		//左
		Vector3 m_LeftPos = Vector3(-10, 0, 0);
		//スピード
		float m_Speed = 3.0f;
		//回転フラグ
		bool m_Rotflg = false;
		bool m_RotCenterflg = false;
		bool m_RotRightflg = false;
		bool m_RotLeftflg = false;
		//移動が終わっているか？
		bool m_EndMove = true;
		//コントローラの連続入力の防止
		bool m_StickDown = false;
		bool m_StickLift = false;

	public:
		ModeSelect(const shared_ptr<Stage>& StagePtr, const Vector3& Pos, const Vector3& Scale, const int& ModeNum, const bool& Centerflg, const int& MoveNum);
		~ModeSelect() {};
		virtual void OnCreate();
		virtual void OnUpdate();
		void SetModeSelectNum(int SetModeNum) { m_NowModeNum = SetModeNum; };
		//各難易度の位置移動が終わったかのゲッター //終わってたらfalse　移動中だとtrue
		bool GetRotCenterflg() { return m_RotCenterflg; };
		bool GetRotRightflg() { return m_RotRightflg; };
		bool GetRotLeftflg() { return m_RotLeftflg; };
		//
		int GetMoveNum() { return m_MoveNum; };
		//センターフラグ　センターならtrue それ以外ならfalse
		bool GetCenter() { return m_Centerflg; };
		bool GetLiftf() { return m_Liftflg; };
		bool GetRight() { return m_Rightflg; };
		//難易度の移動
		void ModeSelectMove();
		//センターに移動
		void CenterMove();
		//左に移動
		void LiftMove();
		//右に移動
		void RightMove();
		//移動が終わったか？ゲッター 終わってたらtrue 終わってなかったらfalse
		bool EndMove() { return m_EndMove; };

	};

	//--------------------------------------------------------------------------------------
	//	ステージの箱
	//--------------------------------------------------------------------------------------
	class StageBox : public GameObject
	{
	private:
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
	public:
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
	private:
		//位置は固定するので書かない
		//大きさ(大きさ変えるアニメーション使うなら)
		Vector3 m_InitScale;

		//背景
		shared_ptr<GameObject> m_CheckBack;
		//中身
		shared_ptr<GameObject> m_CheckBoxIn;
		//カーソル
		shared_ptr<GameObject> m_Cursor;
		//Goスプライト
		shared_ptr<GameObject> m_GoSprite;
		//Backスプライト
		shared_ptr<GameObject> m_BackSprite;

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
		bool m_Closeflg = true;
		//押され続けてたときのflg
		bool m_APush = false;
		bool m_KeepApudh = false;
		//Aが押し続けてなければfalseになり押し続けている検証をしない
		bool m_KeepPushing = true;
	public:
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
		int GetStageNumber() { return m_stageNum; };
		//Abe20170523

		//Abe20170525
		//エネミーの数入れる
		void SetEnemyNum(int tackle, int shot, int terepo, int bomb);
		//Abe20170525

		bool GetCloseflg() { return m_Closeflg; };
		void SetCloseflg(bool flg) { m_Closeflg = flg; };
	};
	//Abe20170421

	//Abe20170427

	//--------------------------------------------------------------------------------------
	//	地面
	//--------------------------------------------------------------------------------------
	class SelectGroud : public GameObject
	{
	private:
		Vector3 m_Pos;
		Vector3 m_Scale;
	public:
		SelectGroud(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);

		void OnCreate() override;
	};
	//Abe20170427


	//Abe20170526
	//--------------------------------------------------------------------------------------
	//	地面に貼るやつ
	//--------------------------------------------------------------------------------------
	class SelectGroundSquare : public GameObject
	{
	private:
		Vector3 m_Pos;
		Vector3 m_Scale;
		wstring m_Text;
		float m_rot;
	public:
		SelectGroundSquare(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txt, float rot);

		void OnCreate() override;
	};

	//Abe20170526

	//Abe20170529
	//--------------------------------------------------------------------------------------
	//	地面に貼るやつ(SS版)
	//--------------------------------------------------------------------------------------
	class SelectGroundSquareSS : public SS5ssae
	{
	private:
		Vector3 m_Pos;
		Vector3 m_Scale;
		float m_rot;
	public:
		SelectGroundSquareSS(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, float rot);
		~SelectGroundSquareSS() {};
		void OnCreate() override;
		void OnUpdate() override;
	};
	//Abe20170529

	class ModeSeledctNameSprite :public GameObject {
	private:
		Vector3 m_Scale;
		int m_Type;

	public:
		ModeSeledctNameSprite(const shared_ptr<Stage>& StagePtr, const Vector3& Scale, const int& Type);
		~ModeSeledctNameSprite() {};
		void OnCreate() override;
		void OnUpdate() override;
	};
	//--------------------------------------------------------------------------------------
	//	地面に貼るやつ
	//--------------------------------------------------------------------------------------
	class SelectModeSquare : public GameObject
	{
	private:
		int m_ModeNum = 0;
	public:
		SelectModeSquare(const shared_ptr<Stage>& StagePtr, const int& ModeNum);
		~SelectModeSquare() {};

		void OnCreate() override;
		void OnUpdate() override;
	};

	class SERECT_Background :public GameObject
	{
	private:
		Vector3 m_Scale = Vector3(0, 0, 0);
		Vector3 m_Pos = Vector3(0, 0, 0);
	public:
		SERECT_Background(const shared_ptr<Stage>& StagePtr, const Vector3& m_Scale, const Vector3& m_Pos);
		~SERECT_Background() {};
		void OnCreate() override;
	};
}