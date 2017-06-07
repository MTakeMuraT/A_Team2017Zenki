#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//************************************
	//	円形アタリ判定
	//	距離で判定、座標のマイナス反転して加算した分が2(プレイヤーの半径[1]*2)以下のもののみ判定
	//************************************
	//Abe20170504
	CollisionManager::CollisionManager(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void CollisionManager::OnCreate()
	{
		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色黒に変更
		m_Debugtxt->SetColor(Vector3(0, 0, 0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);

	}

	void CollisionManager::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//プレイヤーとアタリとるグループに入ってるもの
			CollisionPlayer();

			//アタリとるグループに入ってるもの全部
			AllCollision();
		}
	}

	void CollisionManager::CollisionPlayer()
	{
		//プレイヤーの座標を持ってくる
		Vector3 ppos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 ppos2 = m_Player2->GetComponent<Transform>()->GetPosition();

		//アタリ判定を行うオブジェクトが入ってるグループを持ってくる
		auto ColGroupVec = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();

		//オブジェクト数分ループ
		for (auto obj : ColGroupVec)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			//描画されてれば判定
			if (ptr->GetDrawActive())
			{
				//距離を測る(プレイヤー同士の体の大きさは変わらないと思うので1体目を参照)
				float half = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + ptr->GetComponent<Transform>()->GetScale().x / 2;
				//平方根とらないように
				half *= half;
				//それぞれの差を計算
				Vector3 dist1 = ptr->GetComponent<Transform>()->GetPosition() - m_Player1->GetComponent<Transform>()->GetPosition();
				Vector3 dist2 = ptr->GetComponent<Transform>()->GetPosition() - m_Player2->GetComponent<Transform>()->GetPosition();
				dist1 = dist1 * dist1;
				dist2 = dist2 * dist2;

				//一体目があたる
				if (half > dist1.x + dist1.z && (dist1.y < 0.5f && dist1.y > -0.5f))
				{
					CollisionAfter(ptr, 1);
				}
				//二体目があたる
				if (half > dist2.x + dist2.z && (dist2.y < 0.5f && dist2.y > -0.5f))
				{
					CollisionAfter(ptr, 2);
				}
			}
		}
	}

	void CollisionManager::AllCollision()
	{
		//アタリ判定を行うオブジェクトが入ってるグループを持ってくる
		auto ColGroupVec = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
		//コンテナ初期化
		m_ColObjs.clear();
		//いったんvectorコンテナに入れる
		for (auto obj : ColGroupVec)
		{
			//描画されてれば判定
			if (obj.lock()->GetDrawActive())
			{
				m_ColObjs.push_back(dynamic_pointer_cast<GameObject>(obj.lock()));
			}
		}

		//一番目から[1,2][1,3]って感じで検証、もし当たってたらそいつをvector配列から除去
		while (m_ColObjs.size() > 1)
		{
			//当たったか
			bool HitFlg = false;

			int VecSize = m_ColObjs.size() - 1;
			for (int i = 1; i < VecSize;i++)
			{		
				
				//アタリ確認
				bool ColFlg = HitTest(m_ColObjs[0]->GetComponent<Transform>()->GetPosition(), m_ColObjs[0]->GetComponent<Transform>()->GetScale().x, 
									  m_ColObjs[i]->GetComponent<Transform>()->GetPosition(), m_ColObjs[i]->GetComponent<Transform>()->GetScale().x);
				//当たった
				if (ColFlg)
				{
					//当たったフラグOn
					HitFlg = true;
					//角度計算
					//0のほう
					Vector3 dis = m_ColObjs[i]->GetComponent<Transform>()->GetPosition() - m_ColObjs[0]->GetComponent<Transform>()->GetPosition();
					int angle = (int)(atan2(dis.z, dis.x) * 180/3.14159265f + 360);
					angle %= 360;

					//iのほう
					Vector3 dis2 = m_ColObjs[0]->GetComponent<Transform>()->GetPosition() - m_ColObjs[i]->GetComponent<Transform>()->GetPosition();
					int angle2 = (int)(atan2(dis2.z, dis2.x) * 180 / 3.14159265f + 360);
					angle2 %= 360;

					CollisionAfterObjs(m_ColObjs[0], angle, m_ColObjs[i], angle2);


					//あたったものをvectorコンテナから消す
					m_ColObjs.erase(m_ColObjs.begin());
					m_ColObjs.erase(m_ColObjs.begin() + i);

					break;
				}
				
			}
			//もし当たったものがなければ一番先頭から消す
			if (!HitFlg)
			{
				m_ColObjs.erase(m_ColObjs.begin()+0);
			}
		}
	}

	bool CollisionManager::HitTest(Vector3 pos1, float half1, Vector3 pos2, float half2)
	{
		//距離を測る
		float half = half1 + half2;
		//平方根とらないように
		half *= half;
		//それぞれの差を計算
		Vector3 dist = pos2 - pos1;
		dist = dist * dist;

		//当たる
		if (half > dist.x + dist.z)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

	void CollisionManager::CollisionAfterObjs(shared_ptr<GameObject> obj,int angle, shared_ptr<GameObject> obj2, int angle2)
	{
		//================================================
		//					１体目
		//================================================
		//if (dynamic_pointer_cast<TackleEnemy>(obj))
		//{
		//	//横が当たってる
		//	if ((angle > 135.0f && angle < 225.0f) || (angle > 315.0f && angle < 45.0f))
		//	{
		//		dynamic_pointer_cast<TackleEnemy>(obj)->TurnVecolity(true, false);
		//	}
		//	//縦の判定[!横]でいけるんじゃね？
		//	else
		//	{
		//		dynamic_pointer_cast<TackleEnemy>(obj)->TurnVecolity(false, true);
		//	}
		//}
		if (dynamic_pointer_cast<ShotEnemyChildMissile>(obj))
		{
			//それぞれのエネミーにダメージを与える
			if (dynamic_pointer_cast<TackleEnemy>(obj2))
			{
				dynamic_pointer_cast<TackleEnemy>(obj2)->Damage((int)dynamic_pointer_cast<ShotEnemyChildMissile>(obj)->GetChildMissileAttackDamage());
			}
			if (dynamic_pointer_cast<TeleportEnemy>(obj2))
			{
				dynamic_pointer_cast<TeleportEnemy>(obj2)->Damage((int)dynamic_pointer_cast<ShotEnemyChildMissile>(obj)->GetChildMissileAttackDamage());
			}
			
		}
		
		//ミサイルがあたった
		if (dynamic_pointer_cast<Missile>(obj))
		{
			//それぞれのエネミーにダメージを与える
			if (dynamic_pointer_cast<TackleEnemy>(obj2))
			{
				dynamic_pointer_cast<TackleEnemy>(obj2)->Damage((int)dynamic_pointer_cast<Missile>(obj)->GetPower());
			}
			if (dynamic_pointer_cast<TeleportEnemy>(obj2))
			{
				dynamic_pointer_cast<TeleportEnemy>(obj2)->Damage((int)dynamic_pointer_cast<Missile>(obj)->GetPower());
			}
			if (dynamic_pointer_cast<ShotEnemy>(obj2))
			{
				//ショットエネミーのみ属性判定(自分のに当たるので)
				if (dynamic_pointer_cast<Missile>(obj)->GetZokusei() == 1)
				{
					dynamic_pointer_cast<ShotEnemy>(obj2)->Damage((int)dynamic_pointer_cast<Missile>(obj)->GetPower());
				}
			}
			if (dynamic_pointer_cast<BombEnemy>(obj2))
			{
				dynamic_pointer_cast<BombEnemy>(obj2)->DamagePlayer();
			}
		}
		//突撃エネミー
		if (dynamic_pointer_cast<TackleEnemy>(obj))
		{
		
			//攻撃してるときのみ
			if (dynamic_pointer_cast<TackleEnemy>(obj)->GetDamageFlg())
			{
				//それぞれのエネミーにダメージを与える
				if (dynamic_pointer_cast<ShotEnemy>(obj2))
				{
					dynamic_pointer_cast<ShotEnemy>(obj2)->Damage((int)dynamic_pointer_cast<TackleEnemy>(obj)->GetPower());
				}
				if (dynamic_pointer_cast<TeleportEnemy>(obj2))
				{
					dynamic_pointer_cast<TeleportEnemy>(obj2)->Damage((int)dynamic_pointer_cast<TackleEnemy>(obj)->GetPower());
				}
				if (dynamic_pointer_cast<TackleEnemy>(obj2))
				{
					dynamic_pointer_cast<TackleEnemy>(obj2)->Damage((int)dynamic_pointer_cast<TackleEnemy>(obj)->GetPower());
				}
				if (dynamic_pointer_cast<BombEnemy>(obj2))
				{
					dynamic_pointer_cast<BombEnemy>(obj2)->DamagePlayer();
				}
			}
		}
		//自爆エネミー
		if (dynamic_pointer_cast<BombEnemy>(obj))
		{
			bool flg = false;
			//攻撃するときのみ
			if (dynamic_pointer_cast<BombEnemy>(obj)->GetAttack())
			{
				if (dynamic_pointer_cast<TackleEnemy>(obj2))
				{
					flg = true;
					dynamic_pointer_cast<TackleEnemy>(obj2)->Damage((int)dynamic_pointer_cast<BombEnemy>(obj)->GetPower());
				}

				if (dynamic_pointer_cast<TeleportEnemy>(obj2))
				{
					flg = true;
					dynamic_pointer_cast<TeleportEnemy>(obj2)->Damage((int)dynamic_pointer_cast<BombEnemy>(obj)->GetPower());
				}
				if (dynamic_pointer_cast<ShotEnemy>(obj2))
				{
					flg = true;
					dynamic_pointer_cast<ShotEnemy>(obj2)->Damage((int)dynamic_pointer_cast<BombEnemy>(obj)->GetPower());
				}
			}

			if (flg)
			{
				dynamic_pointer_cast<BombEnemy>(obj)->ToDamagePlayer();
			}
		}

		//上と同じもの
		//================================================
		//					２体目
		//================================================
		if (dynamic_pointer_cast<TackleEnemy>(obj2))
		{
			//横が当たってる
			if ((angle > 135.0f && angle < 225.0f) || (angle > 315.0f && angle < 45.0f))
			{
				dynamic_pointer_cast<TackleEnemy>(obj2)->TurnVecolity(true, false);
			}
			//縦の判定[!横]でいけるんじゃね？
			else
			{
				dynamic_pointer_cast<TackleEnemy>(obj2)->TurnVecolity(false, true);
			}
		}
		if (dynamic_pointer_cast<ShotEnemyChildMissile>(obj2))
		{
			//それぞれのエネミーにダメージを与える
			if (dynamic_pointer_cast<TackleEnemy>(obj))
			{
				dynamic_pointer_cast<TackleEnemy>(obj)->Damage((int)dynamic_pointer_cast<ShotEnemyChildMissile>(obj2)->GetChildMissileAttackDamage());
			}
			if (dynamic_pointer_cast<TeleportEnemy>(obj))
			{
				dynamic_pointer_cast<TeleportEnemy>(obj)->Damage((int)dynamic_pointer_cast<ShotEnemyChildMissile>(obj2)->GetChildMissileAttackDamage());
			}
		}


		//ミサイルがあたった
		if (dynamic_pointer_cast<Missile>(obj2))
		{
			//それぞれのエネミーにダメージを与える
			if (dynamic_pointer_cast<TackleEnemy>(obj))
			{
				dynamic_pointer_cast<TackleEnemy>(obj)->Damage((int)dynamic_pointer_cast<Missile>(obj2)->GetPower());
			}
			if (dynamic_pointer_cast<TeleportEnemy>(obj))
			{
				dynamic_pointer_cast<TeleportEnemy>(obj)->Damage((int)dynamic_pointer_cast<Missile>(obj2)->GetPower());
			}
			if (dynamic_pointer_cast<ShotEnemy>(obj))
			{
				//ショットエネミーのみ属性判定(自分のに当たるので)
				if (dynamic_pointer_cast<Missile>(obj2)->GetZokusei() == 1)
				{
					dynamic_pointer_cast<ShotEnemy>(obj)->Damage((int)dynamic_pointer_cast<Missile>(obj2)->GetPower());
				}
			}

		}
		//突撃エネミー
		if (dynamic_pointer_cast<TackleEnemy>(obj2))
		{
			//攻撃してるときのみ
			if (dynamic_pointer_cast<TackleEnemy>(obj2)->GetDamageFlg())
			{
				//それぞれのエネミーにダメージを与える
				if (dynamic_pointer_cast<ShotEnemy>(obj))
				{
					dynamic_pointer_cast<ShotEnemy>(obj)->Damage((int)dynamic_pointer_cast<TackleEnemy>(obj2)->GetPower());
				}
				if (dynamic_pointer_cast<TeleportEnemy>(obj))
				{
					dynamic_pointer_cast<TeleportEnemy>(obj)->Damage((int)dynamic_pointer_cast<TackleEnemy>(obj2)->GetPower());
				}
				if (dynamic_pointer_cast<TackleEnemy>(obj))
				{
					dynamic_pointer_cast<TackleEnemy>(obj)->Damage((int)dynamic_pointer_cast<TackleEnemy>(obj2)->GetPower());
				}
				if (dynamic_pointer_cast<BombEnemy>(obj))
				{
					dynamic_pointer_cast<BombEnemy>(obj)->DamagePlayer();
				}
			}
		}
	
		//自爆エネミー
		if (dynamic_pointer_cast<BombEnemy>(obj2))
		{
			//攻撃するときのみ
			if (dynamic_pointer_cast<BombEnemy>(obj2)->GetAttack())
			{
				bool flg = false;
				if (dynamic_pointer_cast<TackleEnemy>(obj))
				{
					flg = true;
					dynamic_pointer_cast<TackleEnemy>(obj)->Damage((int)dynamic_pointer_cast<BombEnemy>(obj2)->GetPower());
				}
				if (dynamic_pointer_cast<TeleportEnemy>(obj))
				{
					flg = true;
					dynamic_pointer_cast<TeleportEnemy>(obj)->Damage((int)dynamic_pointer_cast<BombEnemy>(obj2)->GetPower());
				}
				if (dynamic_pointer_cast<ShotEnemy>(obj))
				{
					flg = true;
					dynamic_pointer_cast<ShotEnemy>(obj)->Damage((int)dynamic_pointer_cast<BombEnemy>(obj2)->GetPower());
				}

				if (flg)
				{
					dynamic_pointer_cast<BombEnemy>(obj2)->ToDamagePlayer();
				}
			}
		}

	}

	void CollisionManager::CollisionAfter(shared_ptr<GameObject> obj , int num)
	{
		//switch使ってもいいけどなんか見づらかったので
		//ていうか一部共通でよくね？←共通するの別で作りました
		//一体目に当たる
		if (num == 1)
		{
			//押し出し処理==================================
			//まず座標を取ってきて当たったオブジェからプレイヤーへの差を取る
			Vector3 obpos = obj->GetComponent<Transform>()->GetPosition();
			Vector3 ppos = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 topos = ppos - obpos;

			//XとZを割合に変換
				//まずマイナス反転
				//XZnormはXPlusZを計算するためだけに使う
			Vector3 XZnorm = topos;
			if (topos.x < 0)
			{
				XZnorm.x *= -1;
			}
			if (topos.z < 0)
			{
				XZnorm.z *= -1;
			}
			//XとZの合計でXとZを割って割合を取る
			float XPlusZ = XZnorm.x + XZnorm.z;

			if (XPlusZ != 0)
			{
				topos /= XPlusZ;
			}

			//当たったオブジェクトを中心にして、あたったオブジェクトとプレイヤーの半径をかけて押し出す
			//この時ちょっとだけ大きめ(Player側依存)に半径を取る
			topos = obpos + topos * (obj->GetComponent<Transform>()->GetScale().x / 1.5f + m_Player1->GetComponent<Transform>()->GetScale().x);

			//Y座標戻す
			topos.y = ppos.y;

			m_Player1->GetComponent<Transform>()->SetPosition(topos);


			//==============================================
			//if (dynamic_pointer_cast<Enemy01>(obj))
			//{
			//	m_Debugtxt->SetText(L"DAMAGE!!");
			//}
			//==============================================
			//************************************************************
			//	↑みたいな感じであたったオブジェクトごとにコードを書いてく(↑のは消してもいいよ?デバッグ用だし、確認済みだし)
			//************************************************************
		}
		//二体目に当たる
		else if (num == 2)
		{
			//押し出し処理==================================
			//まず座標を取ってきて当たったオブジェからプレイヤーへの差を取る
			Vector3 obpos = obj->GetComponent<Transform>()->GetPosition();
			Vector3 ppos = m_Player2->GetComponent<Transform>()->GetPosition();
			Vector3 topos = ppos - obpos;

			//XとZを割合に変換
				//まずマイナス反転
				//XZnormはXPlusZを計算するためだけに使う
			Vector3 XZnorm = topos;
			if (topos.x < 0)
			{
				XZnorm.x *= -1;
			}
			if (topos.z < 0)
			{
				XZnorm.z *= -1;
			}
			//XとZの合計でXとZを割って割合を取る
			float XPlusZ = XZnorm.x + XZnorm.z;

			if (XPlusZ != 0)
			{
				topos /= XPlusZ;
			}
			//当たったオブジェクトを中心にして、あたったオブジェクトとプレイヤーの半径をかけて押し出す
			topos = obpos + topos * (obj->GetComponent<Transform>()->GetScale().x / 2 + m_Player2->GetComponent<Transform>()->GetScale().x);

			//Y座標戻す
			topos.y = ppos.y;

			m_Player2->GetComponent<Transform>()->SetPosition(topos);

			//==============================================
			//if (dynamic_pointer_cast<Enemy01>(obj))
			//{
				//m_Debugtxt->SetText(L"DAMAGE!!");
			//}
			//==============================================
		}

		//以下共通する部分---------------------------------------------------------

		//==============================================
		//if (dynamic_pointer_cast<Enemy01>(obj))
		//{
		//	m_Debugtxt->SetText(L"DAMAGE!!");
		//}
		//==============================================
		//************************************************************
		//	↑みたいな感じで(ry
		//************************************************************

		//==============================================
		//突撃エネミー(TackleEnemy)
		if (dynamic_pointer_cast<TackleEnemy>(obj))
		{
			dynamic_pointer_cast<TackleEnemy>(obj)->ToDamagePlayer();
		}
		//==============================================
		//自爆エネミー(BombEnemy)
		if (dynamic_pointer_cast<BombEnemy>(obj))
		{
			dynamic_pointer_cast<BombEnemy>(obj)->ToDamagePlayer();
		}
		//==============================================


		//ミサイルにあたったら
		if (dynamic_pointer_cast<ShotEnemyChildMissile>(obj))
		{
			//HPを減らす
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(1);
			PtrPlayerHP->SetHit(true);
		}

		//ミサイルに当たったら(本)
		if (dynamic_pointer_cast<Missile>(obj))
		{
			//HPを減らしてミサイルを除去
			dynamic_pointer_cast<Missile>(obj)->ToDamagePleyer();
		}
		//共通する部分---------------------------------------------------------
	}
	//Abe20170504

	//************************************
	//	はさむ時の判定
	//	資料「挟まれる判定考察.txt」を参照
	//************************************

	CollisionSand::CollisionSand(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void CollisionSand::OnCreate()
	{
		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色黒に変更
		m_Debugtxt->SetColor(Vector3(0,0,0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);
	}

	void CollisionSand::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//それぞれの座標を持ってくる
			Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

			//pos1のほうに値が小さいほうをいれる
			if (pos1.x > pos2.x)
			{
				float work = pos2.x;
				pos2.x = pos1.x;
				pos1.x = work;
			}
			//Zの値
			if (pos1.z > pos2.z)
			{
				float work = pos2.z;
				pos2.z = pos1.z;
				pos1.z = work;
			}

			//プレイヤー同士の距離がある程度近ければ判定
			//距離確認用
			//wstring txt;
			//txt += L"dist : " + Util::FloatToWStr(pos2.x-pos1.x + pos2.z - pos1.z);
			//m_Debugtxt->SetText(txt);

			//大体4,4(scaleの2倍*2)でいいかな
			float dist = m_Player1->GetComponent<Transform>()->GetScale().x * 2 + m_Player2->GetComponent<Transform>()->GetScale().x * 2;
			if (pos2.x - pos1.x + pos2.z - pos1.z < dist)
			{
				//エネミーの数だけループ
				//プレイヤーの間にいなければ判定はしない
				auto EGroupVec = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
				for (auto obj : EGroupVec)
				{
					//ポインターと座標持ってくる
					auto eptr = dynamic_pointer_cast<GameObject>(obj.lock());
					Vector3 epos = eptr->GetComponent<Transform>()->GetPosition();
					//若干判定緩めるために半径タス
					Vector3 escale = eptr->GetComponent<Transform>()->GetScale() / 1.0f;
					//2体のプレイヤーの間にいるか
					if ((pos1.x-escale.x < epos.x && epos.x < pos2.x + escale.x) &&
						(pos1.z-escale.z < epos.z && epos.z < pos2.z + escale.z))
					{
						//挟んだ後の処理
						SandAfter(eptr);
						//確認用
						//m_Debugtxt->SetText(L"sand");
					}
					//座標表示
					//wstring txt2;
					//txt2 += L"pos1.x : " + Util::FloatToWStr(pos1.x) + L"\npos1.z : " + Util::FloatToWStr(pos1.z);
					//txt2 += L"\npos2.x : " + Util::FloatToWStr(pos2.x) + L"\npos2.z : " + Util::FloatToWStr(pos2.z);
					//txt2 += L"\nepos.x : " + Util::FloatToWStr(epos.x) + L"\nepos.z : " + Util::FloatToWStr(epos.z);
					//m_Debugtxt->SetText(txt2);
					//２体の間にいなかったらその回は終了
				}
			}
			//else
			//{
				//m_Debugtxt->SetText(L"NOsand");
			//}
		}
	}

	//挟んだ後
	void CollisionSand::SandAfter(shared_ptr<GameObject> obj)
	{
		//==============================================
		if (dynamic_pointer_cast<Enemy01>(obj))
		{
			dynamic_pointer_cast<Enemy01>(obj)->SandAfter();
		}
		//==============================================

		//==============================================
		if (dynamic_pointer_cast<TackleEnemy>(obj))
		{
			dynamic_pointer_cast<TackleEnemy>(obj)->DamagePlayer();
		}
		//==============================================

		//==============================================
		if (dynamic_pointer_cast<BombEnemy>(obj))
		{
			dynamic_pointer_cast<BombEnemy>(obj)->DamagePlayer();
		}
		//==============================================

		//==============================================
		//ミサイルを撃つ子機
		if (dynamic_pointer_cast<ShotEnemyChild>(obj)) {
			//ShotEnemyChildへのフラグ
			dynamic_pointer_cast<ShotEnemyChild>(obj)->SetShotEnemyChildSandFlg(true);
		}
		//==============================================
		//テレポートエネミー
		if (dynamic_pointer_cast<TeleportEnemy>(obj)) {
			//ShotEnemyChildへのフラグ
			dynamic_pointer_cast<TeleportEnemy>(obj)->DamagePlayer();
		}
		//==============================================
		//ミサイルうつエネミー
		if (dynamic_pointer_cast<ShotEnemy>(obj)) {
			//ShotEnemyChildへのフラグ
			dynamic_pointer_cast<ShotEnemy>(obj)->DamagePlayer();
		}
		//==============================================

	}
}