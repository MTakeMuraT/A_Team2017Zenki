#pragma once
#include "stdafx.h"

namespace basecross
{
	//�e���v���[�g�ɂ��s���֐��̎���
	//--------------------------------------------------------------------------------------
	//	�ҋ@�s���N���X
	//--------------------------------------------------------------------------------------
	template<typename T>
	class WaitBehavior_calse {
	public:
		void Enter(const shared_ptr<T>& Obj) {
			auto PtrDraw = Obj->GetComponent<PNTBoneModelDraw>();
			PtrDraw->ChangeCurrentAnimation(L"Wait");
		}
		void Excute(const shared_ptr<T>& Obj) {
			Obj->UpdateAnyAnimation();
		}
		void Exit(const shared_ptr<T>& Obj) {

		}
	};

	//--------------------------------------------------------------------------------------
	//	�ړ��s���N���X
	//--------------------------------------------------------------------------------------
	template<typename T>
	class WalkBehavior_calse {
	public:
		void Enter(const shared_ptr<T>& Obj) {
			auto PtrDraw = Obj->GetComponent<PNTBoneModelDraw>();
			PtrDraw->ChangeCurrentAnimation(L"walk");
		}
		void Excute(const shared_ptr<T>& Obj) {
			Obj->UpdateAnyAnimation();
		}
		void Exit(const shared_ptr<T>& Obj) {

		}
	};

	//--------------------------------------------------------------------------------------
	//	�_���[�W�s���N���X
	//--------------------------------------------------------------------------------------
	template<typename T>
	class DamageBehavior_calse {
		int m_Count;
		float m_MixCunt;
	public:
		void Enter(const shared_ptr<T>& Obj) {
			auto PtrDraw = Obj->GetComponent<PNTBoneModelDraw>();
			PtrDraw->ChangeCurrentAnimation(L"Damage");
			auto ElapsedTime = App::GetApp()->GetElapsedTime();
			m_Count = 0;
			m_MixCunt = 5.0f;
		}
		void Excute(const shared_ptr<T>& Obj) {
			
			if (m_Count > m_MixCunt) {
				m_Count = 0;
				//�X�e�[�g�ړ�
				Obj->ChangeWaitState();
			}

			Obj->UpdateAnyAnimation();
		}
		void Exit(const shared_ptr<T>& Obj) {

		}
	};

}