#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Collision_Sphere::CollisionTest(Vector3 TargetPos, Vector3 PlayerPos1, Vector3 PlayerPos2, Vector3 TargetScale, Vector3 PlayerScale)
	{
		//�v���C���[�Ƃ̐ڐG�͈�(�S��X�łƂ��Ă܂�)
		float ColLength = TargetScale.x + PlayerScale.x;
		Vector3 def = PlayerPos1 - TargetPos;
		//�P�̖ړ������ĂȂ���Ώo��
		if (ColLength*ColLength < (def.x*def.x) + (def.y*def.y))
		{
			return;
		}
		
		def = PlayerPos2 - TargetPos;

		//�Q�̖ړ������ĂȂ���Ώo��
		if (ColLength*ColLength < (def.x*def.x) + (def.y*def.y))
		{
			return;
		}

		//�ǂ������������Ă��画��

		//�Q�̖ڂ̊p�x
		int angle2 = atan2(def.z, def.x);
		angle2 += 360;
		angle2 %= 360;

		//�P�̖ڂ̊p�x
		def = PlayerPos1 - TargetPos;
		int angle1 = atan2(def.z, def.x);
		//�}�C�i�X�𔽓]
		angle1 += 360;
		angle1 %= 360;

		//�O��̏����X�V
		m_beforeCollisionFlg = m_nowCollisionFlg;

		//���ꂽ�u�Ԃ����Z�b�g
		//m_ExitCollisionFlg = false;

		//�v���C���[���Ίp(�}�R�O�x�ȓ�)�ɂ��邩
		int angledef = abs(angle2 - angle1);
		if (angledef >= 120 && angledef <= 220)
		{
			m_nowCollisionFlg = true;
		}
		else
		{
			m_nowCollisionFlg = false;
		}

		//�������Ă��
		if (m_nowCollisionFlg && m_beforeCollisionFlg)
		{
			m_StayCollisionFlg = true;
		}
		////���ꂽ�u��
		//if (!m_nowCollisionFlg && m_beforeCollisionFlg)
		//{
		//	m_ExitCollisionFlg = true;
		//}
	}

}