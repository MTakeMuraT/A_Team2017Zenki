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
		
		//�r���[�̍쐬
		void CreateViewLight();

	public:
		
		//�\�z�Ɣj��
		TitleScene() :Stage() {}
		virtual ~TitleScene() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross
