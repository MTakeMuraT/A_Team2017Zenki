//************************************
//*		作成日：2017/05/05
//*		作成者：Abe
//*		内容：
//*		エネミーまとめ
//************************************


#pragma once
#include "stdafx.h"

enum EnemyState
{
	SearchS,
	MoveS,
	AttackS,
	CoolTimeS
};

namespace basecross
{
	//************************************
	//	突撃エネミー
	//	索敵で引っかかったプレイヤーを狙う。たぶん同時に入ったら２体目を狙う
	//************************************
	class TackleEnemy : public GameObject
	{
	private :
		//初期位置
		Vector3 m_InitPos;
		//現在の状態
		EnemyState m_State;
		//プレイヤーのアクセサー的なの
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//索敵範囲の画像(スクエア)
		shared_ptr<GameObject> m_SearchCircle;

		//探索までの間隔
		float m_moveInterval = 2;
		//移動時Velocity
		Vector3 m_Velocity;

		//生きてるか
		bool m_ActiveFlg = true;

		//時間測る用
		float m_time = 0;

		//攻撃までのタメ時間
		float m_AttackTime = 2.0f;
		//突撃した回数
		int m_AttackCount = 0;
		//攻撃中(これ、攻撃状態でもあるんで、DamageFlgっても呼ぶかも)
		bool m_TackleFlg = false;
		//攻撃してる対象
		int m_TargetNum = 0;
		//突撃してる時間
		float m_TackleTime = 3.0f;


		/*ぶれぶれするかどうかわからんから放置！ これに関係するものは1Aでコメントアウト
		//ぶれぶれさせる用の座標
		Vector3 m_BurePos;
		*/

		//Abe20170515
		//ステージの幅
		Vector2 m_StageSize;

		//ステージの端に行ったか判定して向きを変える関数
		void StageEndCheck();
		//Abe20170515

		//Abe20170519
		//回転
		void Rot();
		//Abe20170519

		//以下パラメータ
		//大きさ
		float m_ParScale;
		//HP
		int m_Hp;
		//索敵距離
		float m_SearchDistance;
		//クールタイム
		float m_CoolTime;
		//速度
		float m_Speed;
		//攻撃力
		int m_Power;
		//突撃回数
		int m_TackleCount;

		//デバッグ文字表示オブジェ
		shared_ptr<DebugTxt> m_Debugtxt;

	public :
		//引数 位置(pos)、大きさ(parscale)、HP(hp)、索敵距離(serchdistance)、クールタイム(cooltime)、速度(speed)、攻撃力(power)、突撃回数(tacklecount)
		TackleEnemy(const shared_ptr<Stage>& StagePtr,Vector3 pos,float parscale,int hp,float searchdistance,float cooltime,float speed,int power,int tacklecount);

		void OnCreate() override;
		void OnUpdate() override;

		//索敵
		void Search();
		//探索
		void Move();
		//攻撃
		void Attack();
		//クールタイム
		void CoolTime();

		//サークル移動
		void CircleMove();

		//Velocityを反転する 引数(x,z)にtrue入れると反転
		//同時にいろいろあたったら知らん。もう仕様だわそれ、やればわかる
		void TurnVecolity(bool, bool);

		//ダメージ受けるかどうかのフラグ受け渡し用
		bool GetDamageFlg() { return m_TackleFlg; }

		//状態変更
		void ToSearch();
		void ToMove();
		void ToAttack(int);		//攻撃する対象(1なら１体目2なら２体目)
		void ToCoolTime();

		//プレイヤーへの攻撃判定
		void ToDamagePlayer();

		//自分がダメージ受けたときの関数
		//プレイヤーから
		void DamagePlayer();
		//ミサイルとか爆弾とかプレイヤー以外
		void Damage(int num);
	};

	//************************************
	//	玉撃つエネミー
	//	追記なし？
	//************************************

	class ShotEnemy : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos;
		//現在の状態
		EnemyState m_State;
		//プレイヤーのアクセサー的なの
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//索敵範囲の画像(スクエア)
		shared_ptr<GameObject> m_SearchCircle;

		//回転速度
		float m_rotSpeed = 180.0f;

		//時間測る用
		float m_time = 0;
		float m_Childtime = 0;

		//ミサイル
		vector<shared_ptr<GameObject>> m_MissileS;
		//ミサイルの大きさ
		Vector3 m_MissileScale = Vector3(0.5f, 0.5f, 0.5f);
		//子機
		vector<shared_ptr<GameObject>> m_ChildS;

		//子機吐き出す関数
		void ShotChild();
		//一回の索敵中に子機を吐き出したか
		bool m_ShotChild = false;

		//Abe20170517
		//動くフラグ
		bool m_ActiveFlg = true;
		//ランダムで狙うほうを決める
		int m_TargetPlayer = 0;
		//飛ばす力
		float m_ShotPower = 3.0f;
		//Abe20170517

		//以下パラメータ
		//大きさ
		float m_ParScale;
		//HP
		int m_Hp;
		//索敵距離
		float m_SearchDistance;
		//クールタイム
		float m_CoolTime;
		//攻撃力
		int m_Power;
		//子機発射間隔
		float m_ShotChildInterval;
		//発射数(ミサイル)
		int m_ShotAmount;
	public:
		//引数 位置(pos)、大きさ(parscale)、HP(hp)、索敵距離(serchdistance)、クールタイム(cooltime)、攻撃力(power)、子機発射間隔(shotchildinterval)、発射数(shotamount)
		ShotEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime,int power, float shotchildinterval,int shotamount);

		void OnCreate() override;
		void OnUpdate() override;

		//索敵
		void Search();
		//攻撃
		void Attack();
		//状態変更
		void ToSearch();
		void ToAttack();

		//自分がダメージ受けたときの関数
		//プレイヤーから
		void DamagePlayer();
		//ミサイルとか爆弾とか
		void Damage(int power);
	};

	//************************************
	//	爆弾置いてテレポートエネミー
	//	追記なし？
	//************************************

	class TeleportEnemy : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos;
		//現在の状態
		EnemyState m_State;
		//プレイヤーのアクセサー的なの
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//索敵範囲の画像(スクエア)
		shared_ptr<GameObject> m_SearchCircle;

		//時間測る用
		float m_time;

		//攻撃する対象
		int m_TargetNum = 0;
		//攻撃(テレポート)までの時間
		float m_AttackWaitTime = 0.5f;
		//爆弾置く状態
		bool m_BombPutFlg = false;
		//爆弾置いた状態
		bool m_BombAfterFlg = false;
		//爆弾置いてる間の時間
		float m_BombPutTime = 1;
		//置いた後逃げるまでの時間
		float m_TereportTime = 1;

		//自分の足元のテレポートポイント
		shared_ptr<GameObject> m_UnderTereportPoint;

		//アクティブフラグ
		bool m_ActiveFlg = true;

		//デバッグ文字
		shared_ptr<DebugTxt> m_Debugtxt;

		//子機
		vector<shared_ptr<GameObject>> m_Drawns;
		//子機打ち出す処理
		void GoDrawns();

		//子機に自分を認識させるための番号
		int m_number;

		//以下パラメータ
		//大きさ
		float m_ParScale;
		//HP
		int m_Hp;
		//索敵距離
		float m_SearchDistance;
		//クールタイム
		float m_CoolTime;
		//子機発射間隔
		//float m_ShotChildInterval;
		//発射数(子機)
		int m_ShotAmount;


	public:
		//引数 位置(pos)、大きさ(parscale)、HP(hp)、索敵距離(serchdistance)、クールタイム(cooltime)、発射数(shotamount)
		TeleportEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int shotamount);

		void OnCreate() override;
		void OnUpdate() override;

		//索敵
		void Search();
		//攻撃
		void Attack();
		//クールタイム
		void CoolTime();

		//サークル移動
		void CircleMove();

		//状態変更
		void ToSearch();
		void ToAttack(int);		//攻撃する対象(1なら１体目2なら２体目)
		void ToCoolTime();

		//プレイヤーから
		void DamagePlayer();
		//ダメージ受ける関数
		void Damage(int);

		//番号取得
		int GetNumber() {return m_number; }
	};

	//************************************
	//	自爆エネミー
	//	追記なし？
	//************************************
	class BombEnemy : public GameObject
	{
	private:
		//初期位置
		Vector3 m_InitPos;
		//現在の状態
		EnemyState m_State;
		//プレイヤーのアクセサー的なの
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//索敵範囲の画像(スクエア)
		shared_ptr<GameObject> m_SearchCircle;

		
		//探索までの間隔
		float m_moveInterval = 2;
		//移動時Velocity
		Vector3 m_Velocity;

		//生きてるか
		bool m_ActiveFlg = true;


		//時間測る用
		float m_time;

		//攻撃までのタメ時間
		float m_AttackTime = 2.0f;
		//攻撃中(これ、攻撃状態でもあるんで、DamageFlgっても呼ぶかも)
		bool m_TackleFlg = false;
		//攻撃してる対象
		int m_TargetNum = 0;
		//突撃してる時間
		float m_TackleTime = 3.0f;

		//Abe20170519
		//回転
		void Rot();
		//Abe20170519



		//以下パラメータ
		//大きさ
		float m_ParScale;
		//HP
		int m_Hp;
		//索敵距離
		float m_SearchDistance;
		//速度
		float m_Speed;
		//攻撃力
		int m_Power;
		//突撃回数
		int m_TackleCount;


	public:
		//引数 位置(pos)、大きさ(parscale)、HP(hp)、索敵距離(serchdistance)、速度(speed)、攻撃力(power)
		BombEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float speed, int power);

		void OnCreate() override;
		void OnUpdate() override;

		//索敵
		void Search();
		//探索
		void Move();
		//攻撃
		void Attack();
		
		//サークル移動
		void CircleMove();


		//状態変更
		void ToSearch();
		void ToMove();
		void ToAttack(int);		//攻撃する対象(1なら１体目2なら２体目)

		//プレイヤーへの攻撃判定
		void ToDamagePlayer();

		//自分がダメージ受けたときの関数
		//プレイヤーから
		void DamagePlayer();

	};

	//Abe20170508
	//======================以下子機群=======================
	//************************************
	//	爆弾の爆発の部分
	//	拡縮だけでいいかな？
	//************************************
	class BombEffect : public GameObject
	{
	private:
		//状態
		int m_State = 0;
		//アクティブフラグ
		bool m_ActiveFlg = false;
	public:
		BombEffect(const shared_ptr<Stage>& StagePtr);

		void OnCreate() override;
		void OnUpdate() override;

		//起動、止まってれば再起動される。引数は座標
		void SetPosActive(Vector3);
	};

	//************************************
	//	爆弾
	//	一定時間で起動
	//************************************
	class Bomb : public GameObject
	{
	private:
		//座標
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;

		//計算用時間
		float m_time = 0;
		//生きてるか
		bool m_Activeflg = true;

		//以下パラメータ
		//爆発範囲
		float m_BombDistance;
		//攻撃力
		int m_Power;
		//爆発までの時間
		float m_ExplosionTime = 3.0f;

		shared_ptr<BombEffect> m_Effect;
	public:
		//座標、大きさ、爆発範囲、攻撃力、爆発までの時間
		Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos, float scale, float bombdistance, float power, float explosiontime);

		//引数ポジションのみ。ていうか基本こっち使ってほしい
		Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos);
		void OnCreate() override;
		void OnUpdate() override;

		//挟まれたら爆発
		void BombExplosion();

		//再利用
		void SetActivePosition(Vector3 pos);

		bool GetActive() { return m_Activeflg; }
	};

	//************************************
	//	テレポートエネミーのテレポート先
	//	一定時間で起動
	//************************************
	class TereportPoint : public GameObject
	{
	private:
		//座標
		Vector3 m_Pos;
		//今エネミー乗ってるか
		bool m_OnEnemy = false;
	public:
		TereportPoint(const shared_ptr<Stage>& StagePtr, Vector3 pos);

		void OnCreate() override;

		void SetOnEnemy(bool flg) { m_OnEnemy = flg; };
		bool GetOnEnemy() { return m_OnEnemy; };
	};
	//Abe20170508
	//Abe20170512
	//************************************
	//	索敵ドローン
	//	プレイヤー見つけるまで探索
	//************************************
	class SearchDrawn : public GameObject
	{
	private :
		//計算用時間
		float m_time = 0;
		//向き切り替え時間
		float m_ChangeTime = 3.0f;

		//プレイヤーのアクセサー的なの
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//索敵範囲の画像(スクエア)
		shared_ptr<GameObject> m_SearchCircle;

		//移動速度
		Vector3 m_Velocity;

		//起動してるかどうか
		bool m_ActiveFlg = false;
		//プレイヤー見つけたフラグ
		bool m_FindPlayerFlg = false;

		//識別番号
		int m_number;

		//Abe20170515
		//ステージの幅
		Vector2 m_StageSize;

		//ステージの端に行ったか判定して向きを変える関数
		void StageEndCheck();
		//Abe20170515

		//以下パラメータ
		//索敵距離
		float m_SearchDistance = 2.0f;
		//移動速度
		float m_Speed = 5.0f;

	public :
		SearchDrawn(const shared_ptr<Stage>& StagePtr);

		void OnCreate()override;
		void OnUpdate()override;

		//見つける判定
		void Search();
		//放出
		void GoDrawn(Vector3 pos, Vector3 vel,int num);

		bool GetActiveFlg() { return m_ActiveFlg; }

		//収納
		void UpDrawns();
	};
	//Abe20170512

	//Abe20170515
	//************************************
	//	ミサイル
	//	ステージの端に行くか物に当たるまで
	//	向いてる方向に移動
	//************************************
	class Missile : public GameObject
	{
	private:
		//位置
		Vector3 m_Pos;
		//大きさ
		Vector3 m_Scale;
		//移動向き
		Vector3 m_Velocity;
		//生きてるか
		bool m_ActiveFlg = false;

		//爆発エフェクト
		shared_ptr<BombEffect> m_Effect;
		//Abe20170517
		//落ちるフラグ
		bool m_FallFlg = false;
		//Abe20170517

		//Abe20170515
		//ステージの幅
		Vector2 m_StageSize;

		//ステージの端に行ったか判定して向きを変える関数
		void StageEndCheck();
		//Abe20170515


		//Abe20170519
		//足元の影
		shared_ptr<GameObject> m_Shadow;
		//Abe20170519

		//以下パラメータ
		//攻撃力
		int m_power = 0;
	public :
		Missile(const shared_ptr<Stage>& StagePtr);

		void OnCreate()override;
		void OnUpdate()override;

		//ミサイルを起動。最後のフラグをオンにすると落ちるようになる
		void SetMissileActive(Vector3 pos, Vector3 scale, Vector3 velocity,bool falltype,int power);

		//ミサイル消滅
		void DeleteMissile();

		//プレイヤーに攻撃した場合
		void ToDamagePleyer();

		int GetPower() { return m_power; }
	};
	//Abe20170515
	//サーチサークル
	class SearchCircle : public SS5ssae {
		//中略

	public:
		//構築と破棄
		SearchCircle(const shared_ptr<Stage>& StagePtr);
		virtual ~SearchCircle() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}