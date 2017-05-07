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

		//時間測る用
		float m_time;

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
		//探索
		void Move();
		//攻撃
		void Attack();
		//クールタイム
		void CoolTime();
	};

	//************************************
	//	爆弾置いてテレポートエネミー
	//	追記なし？
	//************************************

	class TeleportEnemy : public GameObject
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

		//時間測る用
		float m_time;

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

	public :
		//引数 位置(pos)、大きさ(parscale)、HP(hp)、索敵距離(serchdistance)、クールタイム(cooltime)、発射数(shotamount)
		TeleportEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int shotamount);

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

		//時間測る用
		float m_time;

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
	};
}