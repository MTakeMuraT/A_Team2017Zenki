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
	CoolTimeS,
	MutekiS
};

namespace basecross
{

	//Abe20170612
	//************************************
	//　シールド
	//************************************
	class EnemyShield : public GameObject
	{
	private:
		//シールドの数
		int m_ShieldAmout = 0;
		//シールド
		vector<shared_ptr<GameObject>> m_ShieldS;
		//シールドの角度
		vector<float> m_ShieldAngleS;
		//シールドの中心座標
		Vector3 m_ShieldPos;
		//シールドの大きさ
		Vector3 m_ShieldScale;
		//中心からの距離
		float m_Half;

		//現在のシールドの数
		int m_NowShieldNum;
	public:
		EnemyShield(const shared_ptr<Stage>& StagePtr, int num, Vector3 pos, Vector3 sca, float half);

		void OnCreate() override;
		void OnUpdate() override;

		void SetPos(Vector3 pos);

		void Damage(int dam);
	};
	//Abe20170612

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


		//Abe20170526
		//無敵フラグ
		bool m_MutekiFlg = false;
		//無敵時間
		float m_MutekiTime = 3.0f;
		//点滅用
		float m_MutekiTenmetuTime = 0;
		//Abe20170526

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
		

		//Abe20170526
		//アニメーション変更
		void ChangeAnimation(string);
		//Abe20170526

		//Abe20170612
		//シールド
		shared_ptr<EnemyShield> m_Shield;
		//Abe20170612
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
		//Abe20170526
		//無敵時間
		void Muteki();
		//Abe20170526

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
		//Abe20170526
		void ToMuteki();
		//Abe20170526

		//プレイヤーへの攻撃判定
		void ToDamagePlayer();

		//自分がダメージ受けたときの関数
		//プレイヤーから
		void DamagePlayer();
		//ミサイルとか爆弾とかプレイヤー以外
		void Damage(int num);
		int GetPower() { return m_Power; }

		EnemyState GetState() { return m_State; }
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
		Vector3 m_MissileScale = Vector3(0.8f, 0.8f, 0.8f);
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

		//Abe20170526
		//アニメーション変更
		void ChangeAnimation(string);

		//無敵フラグ
		bool m_MutekiFlg = false;
		//無敵時間
		float m_MutekiTime = 3.0f;
		//点滅用
		float m_MutekiTenmetuTime = 0;
		//Abe20170526

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

		//Abe20170612
		//シールド
		shared_ptr<EnemyShield> m_Shield;
		//Abe20170612

	public:
		//引数 位置(pos)、大きさ(parscale)、HP(hp)、索敵距離(serchdistance)、クールタイム(cooltime)、攻撃力(power)、子機発射間隔(shotchildinterval)、発射数(shotamount)
		ShotEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime,int power, float shotchildinterval,int shotamount);

		void OnCreate() override;
		void OnUpdate() override;

		//索敵
		void Search();
		//攻撃
		void Attack();
		//Abe20170526
		//無敵時間
		void Muteki();
		//Abe20170526

		//状態変更
		void ToSearch();
		void ToAttack();		
		//Abe20170526
		void ToMuteki();
		//Abe20170526


		//自分がダメージ受けたときの関数
		//プレイヤーから
		void DamagePlayer();
		//ミサイルとか爆弾とか
		void Damage(int power);

		//Abe20170622
		//デバッグ用
		float GetCoolTime() { return m_CoolTime; }
		//Abe20170622

		EnemyState GetState() { return m_State; }

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

		EnemyState GetState() { return m_State; }

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
		//攻撃中判定
		bool m_AttackFlg = false;
		//攻撃してる対象
		int m_TargetNum = 0;
		//突撃してる時間
		float m_TackleTime = 3.0f;

		void StageEndCheck();
		Vector2 m_StageSize;

		//Abe20170519
		//回転
		void Rot();
		//Abe20170519

		//爆発範囲
		float m_BombDistance;

		//攻撃するまで待つふらぐ
		bool m_Tackleflg = false;


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

		//爆発エフェクト
		shared_ptr<GameObject> m_Effect;

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

		void TurnVecolity(bool, bool);
		bool GetAttack() { return m_AttackFlg; }
		int GetPower() { return m_Power; }

	};

	//Abe20170508
	//======================以下子機群=======================
	//************************************
	//	爆弾の爆発の部分(SS対応版)
	//	分割はいりまーす
	//************************************
	class BombEffect : public GameObject
	{
	private:
		//状態
		//int m_State = 0;
		//アクティブフラグ
		bool m_ActiveFlg = false;

		//分割分のvector配列
		vector<shared_ptr<MeshResource>> m_SpriteS;

		//分割数
		int m_SpriteNum = 0;
		//今の番号
		int m_NowSpriteNum = 0;

		//計算用時間
		float m_time = 0;
		//画像切り替え間隔
		const float m_IntervalTime = 0.01f;
	public:
		BombEffect(const shared_ptr<Stage>& StagePtr);

		void OnCreate() override;
		void OnUpdate() override;

		//起動、止まってれば再起動される。引数は座標
		void SetPosActive(Vector3);

		//レイヤー設定
		void SetLayer(int num) { SetDrawLayer(num); }
	};

	//************************************
	//	敵の爆散エフェクト
	//	分割でーーーーす
	//************************************
	class BakusanEF : public GameObject
	{
	private :
		//分割分のvector配列
		vector<shared_ptr<MeshResource>> m_SpriteS;

		//分割数
		int m_SpriteNum = 0;
		//今の番号
		int m_NowSpriteNum = 0;
		//計算用時間
		float m_time = 0;
		//画像切り替え間隔
		float m_IntervalTime = 0.03f;
	public :
		BakusanEF(const shared_ptr<Stage>& StagePtr): GameObject(StagePtr) {}

		void OnCreate() override;
		void OnUpdate() override;

		void SetPosScaActive(Vector3,Vector3);

		void SetLayer(int num) { SetDrawLayer(num); }
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

		//Abe20170529
		//属性 0でshotエネミーには当たらない、1で当たる
		int m_Zokusei = 0;
		//Abe20170529


		//以下パラメータ
		//攻撃力
		int m_power = 1;
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

		int GetPower() { DeleteMissile(); return m_power;  }

		//属性アクセサー
		int GetZokusei() { return m_Zokusei; }
	};
	//Abe20170515

	//Abe20170523IzumiHikitugi
	//************************************
	//	索敵サークル(SS版)
	//	スプライトスタジオで再生
	//************************************
	class SearchCircle : public SS5ssae {
	private :

	public:
		//構築と破棄
		SearchCircle(const shared_ptr<Stage>& StagePtr);
		virtual ~SearchCircle() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	//Abe20170523IzumiHikitugi

	//Abe20170605
	//************************************
	//	爆散して飛ぶやつ
	//************************************
	class BakuSanObj : public GameObject
	{
	private :
		//速度
		Vector3 m_Velocity;
		//大きさ
		Vector3 m_Scale;
		//位置
		Vector3 m_Pos;

		//回転(ランダムで決める)
		Vector3 m_RotPow;
	public :
		BakuSanObj(const shared_ptr<Stage>& StagePtr):GameObject(StagePtr) {}

		void OnCreate() override;

		void OnUpdate() override;

		//位置、大きさ、速度セット
		void SetPosScaleVelo(Vector3, Vector3, Vector3);
	};
	//************************************
	//	爆散して飛ぶやつを生成するやつ
	//************************************
	class BakuSanSpawn : public GameObject
	{
	private :
	public :
		BakuSanSpawn(const shared_ptr<Stage>& StagePtr):GameObject(StagePtr) {}

		//とりあえず
		void OnCreate() {}

		//生成 引数出す数
		void CreateBakusan(int num , Vector3 pos);
	};
	//Abe20170605

}