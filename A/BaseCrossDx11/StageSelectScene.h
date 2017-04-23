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
	class StageSelectScene : public Stage {
		

		//�r���[�̍쐬
		void CreateViewLight();
		void CreatTestLin();

		//Abe20170421
		//�t���[���쐬
		void CreateFlame();
		//�v���C���[�쐬
		void CreatePlayer();
		//�X�e�[�W�{�b�N�X�쐬
		void CreateStageBox();
		//�X�e�[�W�s�����m�F����X�v���C�g
		void CreateGoCheck();
		//Abe20170421
	public:
		//�\�z�Ɣj��
		StageSelectScene() :Stage() {}
		virtual ~StageSelectScene() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	

		
	};


}
//end basecross