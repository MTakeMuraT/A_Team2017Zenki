//************************************
//*		�쐬���F2017/04/10
//*		�쐬�ҁFAbe
//*		���e�F
//*		���̂̃A�^������֐��A�Q�̂̃v���C���[�̊p�x�̍����v�Z����֐�������
//************************************


#pragma once
#include "stdafx.h"

namespace basecross {

	class Collision_Sphere : public GameObject
	{
	private :
		//���O�̌Ăяo���œ������Ă邩�ǂ���
		bool m_beforeCollisionFlg = false;
		//����̌Ăяo���œ������Ă邩
		bool m_nowCollisionFlg = false;

		//���݂̏��
		//�ォ�瓖�������u�ԃt���O�A�������Ă�Œ��t���O�A���ꂽ�u�ԃt���O
		bool m_OnCollisionFlg = false;
		bool m_StayCollisionFlg = false;
		//bool m_ExitCollisionFlg = false;
		
	public :
		Collision_Sphere(const shared_ptr<Stage>& StagePtr):GameObject(StagePtr) {};

		//�������Ă邩�ǂ�������
		void CollisionTest(Vector3 TargetPos, Vector3 PlayerPos1, Vector3 PlayerPos2, Vector3 TargetScale, Vector3 PlayerScale);

		//�t���O�Ƃ��
		bool GetOnCollisionFlg() { return m_OnCollisionFlg; };
		bool GetStayCollisionFlg() { return m_StayCollisionFlg; };
		//bool GetExitCollisionFlg() { return m_ExitCollisionFlg; };
	};
}