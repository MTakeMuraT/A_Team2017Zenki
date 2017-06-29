/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class SE :public GameObject
	{
	private:
		bool SeFlg_Decision_01 = false;
		bool SeFlg_CURSORMOVE = false;
		bool SeFlg_Pause = false;
		bool SePauseCloseSe = false;
	public:
		void ASe();
		void StickSe();
		SE(const shared_ptr<Stage>& StagePtr);
		void OnCreate() override; 
		void SetSeFlg_CURSORMOVE(bool OnTrue) { SeFlg_CURSORMOVE = OnTrue; };
		//�|�[�Y
		void PauseSe();
		void PauseCloseSe();

	};

	
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

		//���S�܂Ő؂�ւ��鎞��
		float m_logocounttime = 0;
		//�I�����̃X�e�B�b�N�㉺��SE�̘A����f���؂�p
		bool OneSeFlg = false;

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
