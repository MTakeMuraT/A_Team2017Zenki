
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------

	void Scene::OnCreate(){
		try {
			//�������Ă΂�Ă���X�e�[�W���Ă΂��
			m_GameMedia = ObjectFactory::Create<GameMedia>();

			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<TitleScene>();
		}
		catch (...) {
			throw;
		}
	}
	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//�^�C�g��
		if (event->m_MsgStr == L"ToTitleScene") {
			auto TitleScenePtr = dynamic_pointer_cast<TitleScene>(GetActiveStage());
			if (!TitleScenePtr) {
				ResetActiveStage<TitleScene>();
			}
		}
		//�Q�[���X�e�[�W�i���j
		if (event->m_MsgStr == L"ToGameScene") {
			auto TitleScenePtr = dynamic_pointer_cast<GameStage>(GetActiveStage());
			if (!TitleScenePtr) {
				ResetActiveStage<GameStage>();
			}
		}

	}

}
//end basecross
