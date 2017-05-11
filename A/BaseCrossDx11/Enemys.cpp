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
		//生きてれば
		if (m_ActiveFlg)
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
	}

	void TackleEnemy::Search()
	{
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
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

	//なんかにぶつかったら速度反転、横と縦どっちがあたったかだけほしぃ
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

	//攻撃受けたとき
	void TackleEnemy::DamagePlayer()
	{
		//もしHPが1以下なら
		if (m_Hp <= 1)
		{
			//タヒぬ
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;
		}
		else
		{
			m_Hp--;
		}
	}

	void TackleEnemy::Damage(int num)
	{
		//HP減らしてなくなってれば1残す
		m_Hp += -num;
		if (m_Hp < 0)
		{
			m_Hp = 1;
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
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

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

	//Abe20170508
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

		//テレポートポイントを作成
		auto TereportGroup = GetStage()->GetSharedObjectGroup(L"TereportPointGroup");
		auto TereportPtr = GetStage()->AddGameObject<TereportPoint>(posci);
		TereportPtr->SetOnEnemy(true);
		TereportGroup->IntoGroup(TereportPtr);

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
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る
		//１体目
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(1);
		}
		//２体目
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

	}

	void TeleportEnemy::Move()
	{

	}

	void TeleportEnemy::Attack()
	{
		m_time += App::GetApp()->GetElapsedTime();
		//爆弾置く状態になるまで待機
		if (!m_BombPutFlg)
		{
			//攻撃までの時間過ぎたらテレポート
			if (m_time > m_AttackWaitTime)
			{
				//１体目攻撃
				if (m_TargetNum == 1)
				{
					Vector3 pos = m_Player1->GetComponent<Transform>()->GetPosition();
					pos.x += (rand() % 20 - 10) / 10;
					pos.y = m_InitPos.y;
					pos.z += (rand() % 20 - 10) / 10;
					GetComponent<Transform>()->SetPosition(pos);
				}
				//２体目攻撃
				else if (m_TargetNum == 2)
				{
					Vector3 pos = m_Player2->GetComponent<Transform>()->GetPosition();
					pos.x += (rand() % 20 - 10) / 10;
					pos.y = m_InitPos.y;
					pos.z += (rand() % 20 - 10) / 10;
					GetComponent<Transform>()->SetPosition(pos);
				}

				//爆弾置くフラグたてる
				m_BombPutFlg = true;

				//時間リセット
				m_time = 0;
			}
		}
		//爆弾置く
		else
		{
			//爆弾置く前
			if (!m_BombAfterFlg)
			{
				if (m_time > m_BombPutTime)
				{
					//爆弾を生成
					auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
					//置いたかどうか
					bool PutFlg = false;
					for (auto obj : BombGroup)
					{
						auto ptr = dynamic_pointer_cast<Bomb>(obj.lock());
						if (!ptr->GetDrawActive())
						{
							Vector3 topos = GetComponent<Transform>()->GetPosition();
							topos.y = 1;
							ptr->SetActivePosition(topos);
							PutFlg = true;
						}
						if (!PutFlg)
						{
							GetStage()->AddGameObject<Bomb>(GetComponent<Transform>()->GetPosition());
						}
					}
					//爆弾置いたフラグをオン
					m_BombAfterFlg = true;

					//時間リセット
					m_time = 0;
				}
			}
			//爆弾置いた後
			else
			{
				auto Group = GetStage()->GetSharedObjectGroup(L"TereportPointGroup")->GetGroupVector();
				//中身の数を数える
				int count = 0;
				//ちょっと汚いけどまあいいべ
				vector<shared_ptr<GameObject>> Target;
				for (auto obj : Group)
				{
					auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
					//自分の足元のテレポートポインtじゃなかったら追加
					if (ptr != m_UnderTereportPoint)
					{
						Target.push_back(ptr);
						count++;
					}
					//足元のなら自分いないことにする
					else
					{
						dynamic_pointer_cast<TereportPoint>(ptr)->SetOnEnemy(false);
					}
				}
				//移動先を決定
				int randnum = rand() % count;
				//移動
				Vector3 targetpos = Target[randnum]->GetComponent<Transform>()->GetPosition();
				targetpos.y = m_InitPos.y;
				GetComponent<Transform>()->SetPosition(targetpos);
				//足元のポイント設定
				m_UnderTereportPoint = Target[randnum];
				dynamic_pointer_cast<TereportPoint>(m_UnderTereportPoint)->SetOnEnemy(true);

				//クールタイムへ
				ToCoolTime();
			}
		}

	}

	void TeleportEnemy::CoolTime()
	{
		//クールタイム過ぎたら索敵状態へ
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{
			ToSearch();
			m_time = 0;
		}
	}

	void TeleportEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//足元へ移動
		pos.y += -m_ParScale / 2;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
	}

	void TeleportEnemy::ToSearch()
	{
		//計算時間初期化
		m_time = 0;

		//状態変更
		m_State = SearchS;

		//サークル移動
		CircleMove();

	}

	void TeleportEnemy::ToAttack(int num)
	{
		m_time = 0;

		m_TargetNum = num;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		m_State = AttackS;
	}


	void TeleportEnemy::ToCoolTime()
	{
		//計算時間初期化
		m_time = 0;

		//爆弾置く状態初期化
		m_BombPutFlg = false;
		//爆弾置いた状態初期化
		m_BombAfterFlg = false;

		//状態変更
		m_State = CoolTimeS;

	}
	//Abe20170508

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
		//生きてれば
		if (m_ActiveFlg)
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
			}
		}


	}

	void BombEnemy::Search()
	{
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る
		//１体目
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(1);
		
		}
		//２体目
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

		//一定時間で探索状態へ
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_moveInterval)
		{
			ToMove();
		}

	}

	void BombEnemy::Move()
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

	void BombEnemy::Attack()
	{
		if (!m_TackleFlg)
		{
			//時間加算
			m_time += App::GetApp()->GetElapsedTime();
			
			//攻撃までのチャージが終了
			if (m_time > m_AttackTime)
			{
				m_time = 0;
				m_TackleFlg = true;	
			}
		}
	
		
		//m_TackleFlgがtrue、以下突撃中の動作
		else
		{
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
			else
			{
				Vector3 dis = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

				//角度算出
				float angle = atan2(dis.z, dis.x);
				//速度入れる
				m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
			}
			
			//時間加算
			m_time += App::GetApp()->GetElapsedTime();

			//攻撃時間過ぎるまで移動
			if (m_time < m_TackleTime)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += m_Velocity/10;
				GetComponent<Transform>()->SetPosition(pos);
			}
			//突撃時間終わったら
			else 
			{
				m_time = 0;
				//攻撃フラグ解除
				//m_TackleFlg = false;

				//突撃後、自爆の為消滅
				SetDrawActive(false);
				m_Hp = 0;
				m_ActiveFlg = false;
			}
		}
	}


	void BombEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//足元へ移動
		pos.y += -m_ParScale / 2;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
	}




	//それぞれの状態へ移行する関数------------------------------------------
	void BombEnemy::ToSearch()
	{
		//計算時間初期化
		m_time = 0;

		//状態変更
		m_State = SearchS;

		//サークル移動
		CircleMove();

	}

	void BombEnemy::ToMove()
	{
		//計算時間初期化
		m_time = 0;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		//移動ベクトル(?)計算
		//0.5～-0.5までランダムで出してスピードかける
		m_Velocity = Vector3(rand() % 100 - 50, 0, rand() % 100 - 50);
		m_Velocity /= 20; //100
		m_Velocity *= m_Speed;

		//状態変更
		m_State = MoveS;

	}

	void BombEnemy::ToAttack(int num)
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


	//プレイヤーへの攻撃判定
	void BombEnemy::ToDamagePlayer()
	{
		//攻撃中なら
		if (m_TackleFlg)
		{
			//HPを減らす
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(3);
			PtrPlayerHP->SetHit(true);
			
			//自爆の為消滅
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;

		}
	}

	//Abe20170508
	//======================以下子機群=======================
	//************************************
	//	爆弾
	//	一定時間で起動
	//************************************
	Bomb::Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos, float scale, float bombdistance, float power, float explosiontime) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(Vector3(scale, scale, scale)),
		m_BombDistance(bombdistance),
		m_Power(power),
		m_ExplosionTime(explosiontime)
	{}

	//引数ポジションのみ。ていうか基本こっち使ってほしい
	Bomb::Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos) :
		GameObject(StagePtr),
		m_InitPos(pos)
	{
		//その他決定
		m_Scale = Vector3(1, 1, 1);
		m_BombDistance = 3.0f;
		m_Power = 3.0f;
		m_ExplosionTime = 3.0f;
	}

	void Bomb::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(0, 0, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetTextureResource(L"BOMB_TX");
		Draw->SetMeshResource(L"DEFAULT_QUBE");

		m_time = 0;
	}

	void Bomb::OnUpdate()
	{
		if (m_Activeflg)
		{
			m_time += App::GetApp()->GetElapsedTime();
			if (m_time > m_ExplosionTime)
			{
				BombExplosion();
			}
		}
	}

	//挟まれたら爆発
	void Bomb::BombExplosion()
	{
		//動かなく
		m_Activeflg = false;
		SetDrawActive(false);

		//判定
		//プレイヤーのアクセサー的なのをはじめにもってきておく
		auto Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		auto Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//プレイヤーの座標を持ってくる
		Vector3 ppos1 = Player1->GetComponent<Transform>()->GetPosition();
		Vector3 ppos2 = Player2->GetComponent<Transform>()->GetPosition();

		//距離を測る(プレイヤー同士の体の大きさは変わらないと思うので1体目を参照)
		float half = Player1->GetComponent<Transform>()->GetScale().x / 2 + m_BombDistance / 2;
		//平方根とらないように
		half *= half;
		//それぞれの差を計算
		Vector3 dist1 = GetComponent<Transform>()->GetPosition() - Player1->GetComponent<Transform>()->GetPosition();
		Vector3 dist2 = GetComponent<Transform>()->GetPosition() - Player2->GetComponent<Transform>()->GetPosition();
		dist1 = dist1 * dist1;
		dist2 = dist2 * dist2;

		//どっちか当たる
		if (half > dist1.x + dist1.z || half > dist2.x + dist2.z)
		{
			//ダメージを与える
			//HPを減らす
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(m_Power);
			PtrPlayerHP->SetHit(true);
		}
	}

	//再利用
	void Bomb::SetActivePosition(Vector3 pos)
	{
		m_time = 0;
		m_Activeflg = true;

		SetDrawActive(true);

		GetComponent<Transform>()->SetPosition(pos);
	}


	//************************************
	//	テレポートエネミーのテレポート先
	//	一定時間で起動
	//************************************
	TereportPoint::TereportPoint(const shared_ptr<Stage>& StagePtr, Vector3 pos) :
		GameObject(StagePtr),
		m_Pos(pos)
	{}

	void TereportPoint::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(2, 2, 2);
		Trans->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetTextureResource(L"TEREPORTPOINT_TX");
		Draw->SetMeshResource(L"DEFAULT_SQUARE");

		SetAlphaActive(true);

	}
	//Abe20170508
}
