
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
			m_GameMedia  = ObjectFactory::Create<GameMedia>();

			//�Ƃ肠���������̂�����ł�邩
			srand((unsigned)time(NULL));

			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			//ResetActiveStage<TitleScene>();
			//ResetActiveStage<StageSelectScene>();
			ResetActiveStage<TutorialScene>();

		}
		catch (...) {
			throw;
		}
	}
	void Scene::OnEvent(const shared_ptr<Event>& event) {
		
		if (event->m_MsgStr == L"ToTitleScene") {
			auto TitleScenePtr = dynamic_pointer_cast<TitleScene>(GetActiveStage());
			if (!TitleScenePtr) {
				ResetActiveStage<TitleScene>();
			}
		}
		
		if (event->m_MsgStr == L"ToStageSelectScene") {
			auto StafeSelectPtr = dynamic_pointer_cast<StageSelectScene>(GetActiveStage());
			if (!StafeSelectPtr) {
				ResetActiveStage<StageSelectScene>();
			}
		}
		if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToTutorial") {
			ResetActiveStage<TutorialScene>();
		}

	}


	//�X�e�[�W�ԍ��Ƒ傫���ݒ�
	void Scene::SetStageNumAndStageSize(int stagenum, Vector2 stagesize)
	{
		//�X�e�[�W�ԍ��ݒ�
		m_StageNum = stagenum;

		//�X�e�[�W�T�C�Y�ݒ�
		m_StageSize = stagesize;
	}
}
//end basecross
