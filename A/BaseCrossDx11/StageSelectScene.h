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
	public:
		//�\�z�Ɣj��
		StageSelectScene() :Stage() {}
		virtual ~StageSelectScene();
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	

		
	};


}
//end basecross