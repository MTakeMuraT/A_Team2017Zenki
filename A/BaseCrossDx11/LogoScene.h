#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	���S�V�[��
	//--------------------------------------------------------------------------------------
	class LogoScene : public Stage
	{
	private :
		//�v�Z�p����
		float m_time;
		//�����x
		float m_Alpha;
		//�����Ă�ҋ@����
		float m_waitTime;
		//����
		shared_ptr<GameObject> m_Black;

		//�����邢���ǂ���
		bool m_BlackFlg;
		//���
		int m_state;
		//���݂̉摜
		int m_stateTex;
	public :

		//�r���[�̍쐬
		void CreateViewLight();

		//�\�z�Ɣj��
		LogoScene() :Stage() {}
		virtual ~LogoScene();

		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}