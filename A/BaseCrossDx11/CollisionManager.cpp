#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//************************************
	//	�~�`�A�^������
	//	�����Ŕ���A���W�̃}�C�i�X���]���ĉ��Z��������2(�v���C���[�̔��a[1]*2)�ȉ��̂��̂̂ݔ���
	//************************************
	//Abe20170504
	CollisionManager::CollisionManager(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void CollisionManager::OnCreate()
	{
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//�F���ɕύX
		m_Debugtxt->SetColor(Vector3(0, 0, 0));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);

	}

	void CollisionManager::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//�v���C���[�ƃA�^���Ƃ�O���[�v�ɓ����Ă����
			CollisionPlayer();

			//�A�^���Ƃ�O���[�v�ɓ����Ă���̑S��
			AllCollision();
		}
	}

	void CollisionManager::CollisionPlayer()
	{
		//�v���C���[�̍��W�������Ă���
		Vector3 ppos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 ppos2 = m_Player2->GetComponent<Transform>()->GetPosition();

		//�A�^��������s���I�u�W�F�N�g�������Ă�O���[�v�������Ă���
		auto ColGroupVec = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();

		//�I�u�W�F�N�g�������[�v
		for (auto obj : ColGroupVec)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			//�`�悳��Ă�Δ���
			if (ptr->GetDrawActive())
			{
				//�����𑪂�(�v���C���[���m�̑̂̑傫���͕ς��Ȃ��Ǝv���̂�1�̖ڂ��Q��)
				float half = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + ptr->GetComponent<Transform>()->GetScale().x / 2;
				//�������Ƃ�Ȃ��悤��
				half *= half;
				//���ꂼ��̍����v�Z
				Vector3 dist1 = ptr->GetComponent<Transform>()->GetPosition() - m_Player1->GetComponent<Transform>()->GetPosition();
				Vector3 dist2 = ptr->GetComponent<Transform>()->GetPosition() - m_Player2->GetComponent<Transform>()->GetPosition();
				dist1 = dist1 * dist1;
				dist2 = dist2 * dist2;

				//��̖ڂ�������
				if (half > dist1.x + dist1.z && (dist1.y < 0.5f && dist1.y > -0.5f))
				{
					CollisionAfter(ptr, 1);
				}
				//��̖ڂ�������
				if (half > dist2.x + dist2.z && (dist2.y < 0.5f && dist2.y > -0.5f))
				{
					CollisionAfter(ptr, 2);
				}
			}
		}
	}

	void CollisionManager::AllCollision()
	{
		//�A�^��������s���I�u�W�F�N�g�������Ă�O���[�v�������Ă���
		auto ColGroupVec = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
		//�R���e�i������
		m_ColObjs.clear();
		//��������vector�R���e�i�ɓ����
		for (auto obj : ColGroupVec)
		{
			//�`�悳��Ă�Δ���
			if (obj.lock()->GetDrawActive())
			{
				m_ColObjs.push_back(dynamic_pointer_cast<GameObject>(obj.lock()));
			}
		}

		//��Ԗڂ���[1,2][1,3]���Ċ����Ō��؁A�����������Ă��炻����vector�z�񂩂珜��
		while (m_ColObjs.size() > 1)
		{
			//����������
			bool HitFlg = false;

			int VecSize = m_ColObjs.size() - 1;
			for (int i = 1; i < VecSize;i++)
			{		
				
				//�A�^���m�F
				bool ColFlg = HitTest(m_ColObjs[0]->GetComponent<Transform>()->GetPosition(), m_ColObjs[0]->GetComponent<Transform>()->GetScale().x, 
									  m_ColObjs[i]->GetComponent<Transform>()->GetPosition(), m_ColObjs[i]->GetComponent<Transform>()->GetScale().x);
				//��������
				if (ColFlg)
				{
					//���������t���OOn
					HitFlg = true;
					//�p�x�v�Z
					//0�̂ق�
					Vector3 dis = m_ColObjs[i]->GetComponent<Transform>()->GetPosition() - m_ColObjs[0]->GetComponent<Transform>()->GetPosition();
					int angle = (int)(atan2(dis.z, dis.x) * 180/3.14159265f + 360);
					angle %= 360;

					//i�̂ق�
					Vector3 dis2 = m_ColObjs[0]->GetComponent<Transform>()->GetPosition() - m_ColObjs[i]->GetComponent<Transform>()->GetPosition();
					int angle2 = (int)(atan2(dis2.z, dis2.x) * 180 / 3.14159265f + 360);
					angle2 %= 360;

					CollisionAfterObjs(m_ColObjs[0], angle, m_ColObjs[i], angle2);


					//�����������̂�vector�R���e�i�������
					m_ColObjs.erase(m_ColObjs.begin());
					m_ColObjs.erase(m_ColObjs.begin() + i);

					break;
				}
				
			}
			//���������������̂��Ȃ���Έ�Ԑ擪�������
			if (!HitFlg)
			{
				m_ColObjs.erase(m_ColObjs.begin()+0);
			}
		}
	}

	bool CollisionManager::HitTest(Vector3 pos1, float half1, Vector3 pos2, float half2)
	{
		//�����𑪂�
		float half = half1 + half2;
		//�������Ƃ�Ȃ��悤��
		half *= half;
		//���ꂼ��̍����v�Z
		Vector3 dist = pos2 - pos1;
		dist = dist * dist;

		//������
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
		//					�P�̖�
		//================================================
		//if (dynamic_pointer_cast<TackleEnemy>(obj))
		//{
		//	//�����������Ă�
		//	if ((angle > 135.0f && angle < 225.0f) || (angle > 315.0f && angle < 45.0f))
		//	{
		//		dynamic_pointer_cast<TackleEnemy>(obj)->TurnVecolity(true, false);
		//	}
		//	//�c�̔���[!��]�ł�����񂶂�ˁH
		//	else
		//	{
		//		dynamic_pointer_cast<TackleEnemy>(obj)->TurnVecolity(false, true);
		//	}
		//}
		if (dynamic_pointer_cast<ShotEnemyChildMissile>(obj))
		{
			//���ꂼ��̃G�l�~�[�Ƀ_���[�W��^����
			if (dynamic_pointer_cast<TackleEnemy>(obj2))
			{
				dynamic_pointer_cast<TackleEnemy>(obj2)->Damage((int)dynamic_pointer_cast<ShotEnemyChildMissile>(obj)->GetChildMissileAttackDamage());
			}
			if (dynamic_pointer_cast<TeleportEnemy>(obj2))
			{
				dynamic_pointer_cast<TeleportEnemy>(obj2)->Damage((int)dynamic_pointer_cast<ShotEnemyChildMissile>(obj)->GetChildMissileAttackDamage());
			}
			
		}
		
		//�~�T�C������������
		if (dynamic_pointer_cast<Missile>(obj))
		{
			//���ꂼ��̃G�l�~�[�Ƀ_���[�W��^����
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
				//�V���b�g�G�l�~�[�̂ݑ�������(�����̂ɓ�����̂�)
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
		//�ˌ��G�l�~�[
		if (dynamic_pointer_cast<TackleEnemy>(obj))
		{
		
			//�U�����Ă�Ƃ��̂�
			if (dynamic_pointer_cast<TackleEnemy>(obj)->GetDamageFlg())
			{
				//���ꂼ��̃G�l�~�[�Ƀ_���[�W��^����
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
		//�����G�l�~�[
		if (dynamic_pointer_cast<BombEnemy>(obj))
		{
			bool flg = false;
			//�U������Ƃ��̂�
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

		//��Ɠ�������
		//================================================
		//					�Q�̖�
		//================================================
		if (dynamic_pointer_cast<TackleEnemy>(obj2))
		{
			//�����������Ă�
			if ((angle > 135.0f && angle < 225.0f) || (angle > 315.0f && angle < 45.0f))
			{
				dynamic_pointer_cast<TackleEnemy>(obj2)->TurnVecolity(true, false);
			}
			//�c�̔���[!��]�ł�����񂶂�ˁH
			else
			{
				dynamic_pointer_cast<TackleEnemy>(obj2)->TurnVecolity(false, true);
			}
		}
		if (dynamic_pointer_cast<ShotEnemyChildMissile>(obj2))
		{
			//���ꂼ��̃G�l�~�[�Ƀ_���[�W��^����
			if (dynamic_pointer_cast<TackleEnemy>(obj))
			{
				dynamic_pointer_cast<TackleEnemy>(obj)->Damage((int)dynamic_pointer_cast<ShotEnemyChildMissile>(obj2)->GetChildMissileAttackDamage());
			}
			if (dynamic_pointer_cast<TeleportEnemy>(obj))
			{
				dynamic_pointer_cast<TeleportEnemy>(obj)->Damage((int)dynamic_pointer_cast<ShotEnemyChildMissile>(obj2)->GetChildMissileAttackDamage());
			}
		}


		//�~�T�C������������
		if (dynamic_pointer_cast<Missile>(obj2))
		{
			//���ꂼ��̃G�l�~�[�Ƀ_���[�W��^����
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
				//�V���b�g�G�l�~�[�̂ݑ�������(�����̂ɓ�����̂�)
				if (dynamic_pointer_cast<Missile>(obj2)->GetZokusei() == 1)
				{
					dynamic_pointer_cast<ShotEnemy>(obj)->Damage((int)dynamic_pointer_cast<Missile>(obj2)->GetPower());
				}
			}

		}
		//�ˌ��G�l�~�[
		if (dynamic_pointer_cast<TackleEnemy>(obj2))
		{
			//�U�����Ă�Ƃ��̂�
			if (dynamic_pointer_cast<TackleEnemy>(obj2)->GetDamageFlg())
			{
				//���ꂼ��̃G�l�~�[�Ƀ_���[�W��^����
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
	
		//�����G�l�~�[
		if (dynamic_pointer_cast<BombEnemy>(obj2))
		{
			//�U������Ƃ��̂�
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
		//switch�g���Ă��������ǂȂ񂩌��Â炩�����̂�
		//�Ă������ꕔ���ʂł悭�ˁH�����ʂ���̕ʂō��܂���
		//��̖ڂɓ�����
		if (num == 1)
		{
			//�����o������==================================
			//�܂����W������Ă��ē��������I�u�W�F����v���C���[�ւ̍������
			Vector3 obpos = obj->GetComponent<Transform>()->GetPosition();
			Vector3 ppos = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 topos = ppos - obpos;

			//X��Z�������ɕϊ�
				//�܂��}�C�i�X���]
				//XZnorm��XPlusZ���v�Z���邽�߂����Ɏg��
			Vector3 XZnorm = topos;
			if (topos.x < 0)
			{
				XZnorm.x *= -1;
			}
			if (topos.z < 0)
			{
				XZnorm.z *= -1;
			}
			//X��Z�̍��v��X��Z�������Ċ��������
			float XPlusZ = XZnorm.x + XZnorm.z;

			if (XPlusZ != 0)
			{
				topos /= XPlusZ;
			}

			//���������I�u�W�F�N�g�𒆐S�ɂ��āA���������I�u�W�F�N�g�ƃv���C���[�̔��a�������ĉ����o��
			//���̎�������Ƃ����傫��(Player���ˑ�)�ɔ��a�����
			topos = obpos + topos * (obj->GetComponent<Transform>()->GetScale().x / 1.5f + m_Player1->GetComponent<Transform>()->GetScale().x);

			//Y���W�߂�
			topos.y = ppos.y;

			m_Player1->GetComponent<Transform>()->SetPosition(topos);


			//==============================================
			//if (dynamic_pointer_cast<Enemy01>(obj))
			//{
			//	m_Debugtxt->SetText(L"DAMAGE!!");
			//}
			//==============================================
			//************************************************************
			//	���݂����Ȋ����ł��������I�u�W�F�N�g���ƂɃR�[�h�������Ă�(���̂͏����Ă�������?�f�o�b�O�p�����A�m�F�ς݂���)
			//************************************************************
		}
		//��̖ڂɓ�����
		else if (num == 2)
		{
			//�����o������==================================
			//�܂����W������Ă��ē��������I�u�W�F����v���C���[�ւ̍������
			Vector3 obpos = obj->GetComponent<Transform>()->GetPosition();
			Vector3 ppos = m_Player2->GetComponent<Transform>()->GetPosition();
			Vector3 topos = ppos - obpos;

			//X��Z�������ɕϊ�
				//�܂��}�C�i�X���]
				//XZnorm��XPlusZ���v�Z���邽�߂����Ɏg��
			Vector3 XZnorm = topos;
			if (topos.x < 0)
			{
				XZnorm.x *= -1;
			}
			if (topos.z < 0)
			{
				XZnorm.z *= -1;
			}
			//X��Z�̍��v��X��Z�������Ċ��������
			float XPlusZ = XZnorm.x + XZnorm.z;

			if (XPlusZ != 0)
			{
				topos /= XPlusZ;
			}
			//���������I�u�W�F�N�g�𒆐S�ɂ��āA���������I�u�W�F�N�g�ƃv���C���[�̔��a�������ĉ����o��
			topos = obpos + topos * (obj->GetComponent<Transform>()->GetScale().x / 2 + m_Player2->GetComponent<Transform>()->GetScale().x);

			//Y���W�߂�
			topos.y = ppos.y;

			m_Player2->GetComponent<Transform>()->SetPosition(topos);

			//==============================================
			//if (dynamic_pointer_cast<Enemy01>(obj))
			//{
				//m_Debugtxt->SetText(L"DAMAGE!!");
			//}
			//==============================================
		}

		//�ȉ����ʂ��镔��---------------------------------------------------------

		//==============================================
		//if (dynamic_pointer_cast<Enemy01>(obj))
		//{
		//	m_Debugtxt->SetText(L"DAMAGE!!");
		//}
		//==============================================
		//************************************************************
		//	���݂����Ȋ�����(ry
		//************************************************************

		//==============================================
		//�ˌ��G�l�~�[(TackleEnemy)
		if (dynamic_pointer_cast<TackleEnemy>(obj))
		{
			dynamic_pointer_cast<TackleEnemy>(obj)->ToDamagePlayer();
		}
		//==============================================
		//�����G�l�~�[(BombEnemy)
		if (dynamic_pointer_cast<BombEnemy>(obj))
		{
			dynamic_pointer_cast<BombEnemy>(obj)->ToDamagePlayer();
		}
		//==============================================


		//�~�T�C���ɂ���������
		if (dynamic_pointer_cast<ShotEnemyChildMissile>(obj))
		{
			//HP�����炷
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(1);
			PtrPlayerHP->SetHit(true);
		}

		//�~�T�C���ɓ���������(�{)
		if (dynamic_pointer_cast<Missile>(obj))
		{
			//HP�����炵�ă~�T�C��������
			dynamic_pointer_cast<Missile>(obj)->ToDamagePleyer();
		}
		//���ʂ��镔��---------------------------------------------------------
	}
	//Abe20170504

	//************************************
	//	�͂��ގ��̔���
	//	�����u���܂�锻��l�@.txt�v���Q��
	//************************************

	CollisionSand::CollisionSand(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void CollisionSand::OnCreate()
	{
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//�F���ɕύX
		m_Debugtxt->SetColor(Vector3(0,0,0));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);
	}

	void CollisionSand::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//���ꂼ��̍��W�������Ă���
			Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

			//pos1�̂ق��ɒl���������ق��������
			if (pos1.x > pos2.x)
			{
				float work = pos2.x;
				pos2.x = pos1.x;
				pos1.x = work;
			}
			//Z�̒l
			if (pos1.z > pos2.z)
			{
				float work = pos2.z;
				pos2.z = pos1.z;
				pos1.z = work;
			}

			//�v���C���[���m�̋�����������x�߂���Δ���
			//�����m�F�p
			//wstring txt;
			//txt += L"dist : " + Util::FloatToWStr(pos2.x-pos1.x + pos2.z - pos1.z);
			//m_Debugtxt->SetText(txt);

			//���4,4(scale��2�{*2)�ł�������
			float dist = m_Player1->GetComponent<Transform>()->GetScale().x * 2 + m_Player2->GetComponent<Transform>()->GetScale().x * 2;
			if (pos2.x - pos1.x + pos2.z - pos1.z < dist)
			{
				//�G�l�~�[�̐��������[�v
				//�v���C���[�̊Ԃɂ��Ȃ���Δ���͂��Ȃ�
				auto EGroupVec = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
				for (auto obj : EGroupVec)
				{
					//�|�C���^�[�ƍ��W�����Ă���
					auto eptr = dynamic_pointer_cast<GameObject>(obj.lock());
					Vector3 epos = eptr->GetComponent<Transform>()->GetPosition();
					//�኱����ɂ߂邽�߂ɔ��a�^�X
					Vector3 escale = eptr->GetComponent<Transform>()->GetScale() / 1.0f;
					//2�̂̃v���C���[�̊Ԃɂ��邩
					if ((pos1.x-escale.x < epos.x && epos.x < pos2.x + escale.x) &&
						(pos1.z-escale.z < epos.z && epos.z < pos2.z + escale.z))
					{
						//���񂾌�̏���
						SandAfter(eptr);
						//�m�F�p
						//m_Debugtxt->SetText(L"sand");
					}
					//���W�\��
					//wstring txt2;
					//txt2 += L"pos1.x : " + Util::FloatToWStr(pos1.x) + L"\npos1.z : " + Util::FloatToWStr(pos1.z);
					//txt2 += L"\npos2.x : " + Util::FloatToWStr(pos2.x) + L"\npos2.z : " + Util::FloatToWStr(pos2.z);
					//txt2 += L"\nepos.x : " + Util::FloatToWStr(epos.x) + L"\nepos.z : " + Util::FloatToWStr(epos.z);
					//m_Debugtxt->SetText(txt2);
					//�Q�̂̊Ԃɂ��Ȃ������炻�̉�͏I��
				}
			}
			//else
			//{
				//m_Debugtxt->SetText(L"NOsand");
			//}
		}
	}

	//���񂾌�
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
		//�~�T�C�������q�@
		if (dynamic_pointer_cast<ShotEnemyChild>(obj)) {
			//ShotEnemyChild�ւ̃t���O
			dynamic_pointer_cast<ShotEnemyChild>(obj)->SetShotEnemyChildSandFlg(true);
		}
		//==============================================
		//�e���|�[�g�G�l�~�[
		if (dynamic_pointer_cast<TeleportEnemy>(obj)) {
			//ShotEnemyChild�ւ̃t���O
			dynamic_pointer_cast<TeleportEnemy>(obj)->DamagePlayer();
		}
		//==============================================
		//�~�T�C�����G�l�~�[
		if (dynamic_pointer_cast<ShotEnemy>(obj)) {
			//ShotEnemyChild�ւ̃t���O
			dynamic_pointer_cast<ShotEnemy>(obj)->DamagePlayer();
		}
		//==============================================

	}
}