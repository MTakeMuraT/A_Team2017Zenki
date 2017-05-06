#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//************************************
	//	�~�`�A�^������
	//	�����Ŕ���A���W�̃}�C�i�X���]���ĉ��Z��������2(�v���C���[�̔��a[1]*2)�ȉ��̂��̂̂ݔ���
	//************************************
	//Abe20170504
	CollisionManager::CollisionManager(const shared_ptr<Stage>& StagePtr):
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
			//�v���C���[�̍��W�������Ă���
			Vector3 ppos1 = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 ppos2 = m_Player2->GetComponent<Transform>()->GetPosition();

			//�A�^��������s���I�u�W�F�N�g�������Ă�O���[�v�������Ă���
			auto ColGroupVec = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();

			//�I�u�W�F�N�g�������[�v
			for (auto obj : ColGroupVec)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				//�����𑪂�(�v���C���[���m�̑̂̑傫���͕ς��Ȃ��Ǝv���̂�1�̖ڂ��Q��)
				float half = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + ptr->GetComponent<Transform>()->GetScale().x / 2;
				//�������Ƃ�Ȃ��悤��
				half *= half;
				//���ꂼ��̍����v�Z
				Vector3 dist1 = ptr->GetComponent<Transform>()->GetPosition() - m_Player1->GetComponent<Transform>()->GetPosition();
				Vector3 dist2 = ptr->GetComponent<Transform>()->GetPosition() - m_Player2->GetComponent<Transform>()->GetPosition();
				dist1 = dist1 * dist1;
				//�y���v�Z�Ŕ��]
				if (dist1.x < 0)
				{
					dist1.x *= -1;
				}
				if (dist1.z < 0)
				{
					dist1.z *= -1;
				}
				//dist2 *= dist2;		//�ǂ����A�Ȃ��݂�������
				dist2 = dist2 * dist2;
				if (dist2.x < 0)
				{
					dist2.x *= -1;
				}
				if (dist2.z < 0)
				{
					dist2.z *= -1;
				}

				//��̖ڂ�������
				if (half > dist1.x + dist1.z)
				{
					CollisionAfter(ptr, 1);
				}
				//��̖ڂ�������
				if (half > dist2.x + dist2.z)
				{
					CollisionAfter(ptr, 2);
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
			//==============================================
			//if (dynamic_pointer_cast<Enemy01>(obj))
			//{
				//m_Debugtxt->SetText(L"DAMAGE!!");
			//}
			//==============================================
		}
		//���ʂ��镔��---------------------------------------------------------

		//==============================================
		if (dynamic_pointer_cast<Enemy01>(obj))
		{
			//m_Debugtxt->SetText(L"DAMAGE!!");
		}
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


		//�~�T�C���ɂ���������
		if (dynamic_pointer_cast<ShotEnemyChildMissile>(obj))
		{
			//HP�����炷
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(1);
			PtrPlayerHP->SetHit(true);
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
					Vector3 escale = eptr->GetComponent<Transform>()->GetScale() /2;
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
		if (dynamic_pointer_cast<Enemy01>(obj))
		{
			dynamic_pointer_cast<Enemy01>(obj)->SandAfter();
		}
	}
}