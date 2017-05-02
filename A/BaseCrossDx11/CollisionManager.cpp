#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//************************************
	//	�~�`�A�^������
	//	�����Ŕ���A���W�̃}�C�i�X���]���ĉ��Z��������2(�v���C���[�̔��a[1]*2)�ȉ��̂��̂̂ݔ���
	//************************************
	CollisionManager::CollisionManager(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void CollisionManager::OnCreate()
	{

	}

	void CollisionManager::OnUpdate()
	{

	}

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