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
	//	追記なし？
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