/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleScene : public Stage {
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

		//�r���[�̍쐬
		void CreateViewLight();
		void CreateBackGround();

		//���
		int m_state = 0;

		//���ԑ���p
		float m_time = 0;

		//�I��ԍ�
		int m_selectNum = 0;

		//�����x
		float m_Alpha = 1;

		//����
		bool m_AlphaFlg = false;
	public:
		//�\�z�Ɣj��
		TitleScene() :Stage() {}
		virtual ~TitleScene();
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross
