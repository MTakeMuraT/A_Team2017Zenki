#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	//************************************
	//	突撃エネミー
	//	追記なし？
	//************************************
	TackleEnemy::TackleEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, float speed, int power, int tacklecount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_Speed(speed),
		m_Power(power),
		m_TackleCount(tacklecount)
	{}

	void TackleEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//見た目
		auto Draw = AddComponent<PNTStaticDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		//ステート初期化
		m_State = SearchS;

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//足元へ移動
		posci.y += -m_ParScale / 2;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		m_SearchCircle = circle;



		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色赤に変更
		m_Debugtxt->SetColor(Vector3(1, 0, 0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);

	}

	void TackleEnemy::OnUpdate()
	{
		//m_Debugtxt->SetText(Util::IntToWStr(m_State));

		switch (m_State)
		{
			//索敵
		case SearchS:
			Search();
			break;
			//探索
		case MoveS:
			Move();
			break;
			//攻撃
		case AttackS:
			Attack();
			break;
			//クールタイム
		case CoolTimeS:
			CoolTime();
			break;
		}


	}

	void TackleEnemy::Search()
	{
		//位置情報取得
		Vector3 mypos  = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る
		//１体目
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{			
			ToAttack(1);
			/*1A
			//チャージ中のぶれぶれ中心座標を記録
			//m_BurePos = GetComponent<Transform>()->GetPosition();
			*/
		}
		//２体目
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

		//m_Debugtxt->SetText(Util::FloatToWStr((dis.x*dis.x) + (dis.z*dis.z)) + L"\n" + Util::FloatToWStr(distance*distance));
		//m_Debugtxt->SetText(L"dis:" + Util::FloatToWStr((dis.x*dis.x) + (dis.z*dis.z)));

		//一定時間で探索状態へ
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_moveInterval)
		{
			ToMove();
		}
	}

	void TackleEnemy::Move()
	{
		//ランダムで2秒くらい進む
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time < 2)
		{
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos += m_Velocity * App::GetApp()->GetElapsedTime();
			//なんかオブジェクトに当たった時はVelocityを反転するけどそれは別のとこでやるわ
			GetComponent<Transform>()->SetPosition(pos);
		}
		else
		{
			ToSearch();
		}
	}

	void TackleEnemy::Attack()
	{
		if (!m_TackleFlg)
		{
			//時間加算
			m_time += App::GetApp()->GetElapsedTime();
			/*1A
			//攻撃するまでぶれぶれ残り時間に応じて速さを変える
			//if (m_time < m_AttackTime)
			//{
			//	Vector3 pos = m_BurePos;
			//	//割り未満
			//	if (m_time / m_AttackTime < 0.3f)
			//	{
			//		//-0.2～0.2の間でぶれぶれ
			//		pos += Vector3(rand() % 40 - 20, 0, rand() % 40 - 20) / 100;
			//	}
			//}
			*/
			//攻撃までのチャージが終了
			if (m_time > m_AttackTime)
			{
				m_time = 0;
				m_TackleFlg = true;
				//攻撃した回数加算
				m_AttackCount++;
				//速度計算
				//１体目に突撃
				if (m_TargetNum == 1) 
				{
					Vector3 dis = m_Player1->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
					//角度算出
					float angle = atan2(dis.z, dis.x);
					//速度入れる
					m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
				}
				//２体目に突撃
				else if (m_TargetNum == 2)
				{
					Vector3 dis = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
					//角度算出
					float angle = atan2(dis.z, dis.x);
					//速度入れる
					m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
				}
			}
		}
		//m_TackleFlgがtrue、以下突撃中の動作
		else
		{
			//時間加算
			m_time += App::GetApp()->GetElapsedTime();

			//攻撃時間過ぎるまで移動
			if (m_time < m_TackleTime)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += m_Velocity * App::GetApp()->GetElapsedTime();
				GetComponent<Transform>()->SetPosition(pos);
			}
			//突撃時間終わったら
			else
			{
				m_time = 0;
				//攻撃フラグ解除
				m_TackleFlg = false;

				//攻撃した回数が設定された攻撃回数の上限を満たしたら
				if (m_AttackCount >= m_TackleCount)
				{
					ToCoolTime();
				}
			}
		}
	}

	void TackleEnemy::CoolTime()
	{
		//クールタイム過ぎたら索敵状態へ
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{
			ToSearch();
			m_time = 0;
		}
	}

	void TackleEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//足元へ移動
		pos.y += -m_ParScale / 2;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
	}

	//なんかにぶつかったら速度反転横と縦どっちがあたったかだけほしぃ
	void TackleEnemy::TurnVecolity(bool flgx, bool flgz)
	{
		if (flgx)
		{
			m_Velocity.x *= -1;
		}
		if (flgz)
		{
			m_Velocity.z *= -1;
		}
	}

	//それぞれの状態へ移行する関数------------------------------------------
	void TackleEnemy::ToSearch()
	{
		//計算時間初期化
		m_time = 0;

		//状態変更
		m_State = SearchS;

		//サークル移動
		CircleMove();

	}

	void TackleEnemy::ToMove()
	{
		//計算時間初期化
		m_time = 0;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		//移動ベクトル(?)計算
		//0.5～-0.5までランダムで出してスピードかける
		m_Velocity = Vector3(rand() % 100 - 50, 0, rand() % 100 - 50);
		m_Velocity /= 100;
		m_Velocity *= m_Speed;

		//状態変更
		m_State = MoveS;

	}

	void TackleEnemy::ToAttack(int num)
	{
		//計算時間初期化
		m_time = 0;
		//攻撃する対象を設定
		m_TargetNum = num;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		//状態変更
		m_State = AttackS;
	}

	void TackleEnemy::ToCoolTime()
	{
		//計算時間初期化
		m_time = 0;

		//攻撃フラグ解除
		m_TackleFlg = false;
		//攻撃回数リセット
		m_AttackCount = 0;

		//状態変更
		m_State = CoolTimeS;
	}

	//プレイヤーへの攻撃判定
	void TackleEnemy::ToDamagePlayer() 
	{
		//攻撃中なら
		if (m_TackleFlg)
		{
			//HPを減らす
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(1);
			PtrPlayerHP->SetHit(true);
			ToCoolTime();
		}
	}
	//************************************
	//	玉撃つエネミー
	//	追記なし？
	//************************************

	ShotEnemy::ShotEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int power, float shotchildinterval, int shotamount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_Power(power),
		m_ShotChildInterval(shotchildinterval),
		m_ShotAmount(shotamount)
	{}

	void ShotEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//見た目
		auto Draw = AddComponent<PNTStaticDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		//ステート初期化
		m_State = SearchS;

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//足元へ移動
		posci.y += -m_ParScale / 2;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265/180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		m_SearchCircle = circle;
	}

	void ShotEnemy::OnUpdate()
	{
		switch (m_State)
		{
			//索敵
		case SearchS:
			Search();
			break;
			//探索
		case MoveS:
			Move();
			break;
			//攻撃
		case AttackS:
			Attack();
			break;
			//クールタイム
		case CoolTimeS:
			CoolTime();
			break;
		}
	}

	void ShotEnemy::Search()
	{

	}

	void ShotEnemy::Move()
	{

	}

	void ShotEnemy::Attack()
	{

	}

	void ShotEnemy::CoolTime()
	{

	}

	//************************************
	//	爆弾置いてテレポートエネミー
	//	追記なし？
	//************************************

	TeleportEnemy::TeleportEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int shotamount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_ShotAmount(shotamount)
	{}

	void TeleportEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//見た目
		auto Draw = AddComponent<PNTStaticDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		//ステート初期化
		m_State = SearchS;

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//足元へ移動
		posci.y += -m_ParScale / 2;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		m_SearchCircle = circle;
	}

	void TeleportEnemy::OnUpdate()
	{
		switch (m_State)
		{
			//索敵
		case SearchS:
			Search();
			break;
			//探索
		case MoveS:
			Move();
			break;
			//攻撃
		case AttackS:
			Attack();
			break;
			//クールタイム
		case CoolTimeS:
			CoolTime();
			break;
		}

	}

	void TeleportEnemy::Search()
	{

	}

	void TeleportEnemy::Move()
	{

	}

	void TeleportEnemy::Attack()
	{

	}

	void TeleportEnemy::CoolTime()
	{

	}

	//************************************
	//	自爆エネミー
	//	追記なし？
	//************************************
	BombEnemy::BombEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float speed, int power) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_Speed(speed),
		m_Power(power)
	{}

	void BombEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//見た目
		auto Draw = AddComponent<PNTStaticDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		//ステート初期化
		m_State = SearchS;

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//足元へ移動
		posci.y += -m_ParScale / 2;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		m_SearchCircle = circle;

	}

	void BombEnemy::OnUpdate()
	{
		switch (m_State)
		{
			//索敵
		case SearchS:
			Search();
			break;
			//探索
		case MoveS:
			Move();
			break;
			//攻撃
		case AttackS:
			Attack();
			break;
			break;
		}

	}

	void BombEnemy::Search()
	{

	}

	void BombEnemy::Move()
	{

	}

	void BombEnemy::Attack()
	{

	}


}