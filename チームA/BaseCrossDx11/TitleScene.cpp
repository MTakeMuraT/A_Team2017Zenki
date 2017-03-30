/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	//�r���[�ƃ��C�g�̍쐬
	void TitleScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrLookAtCamera = ObjectFactory::Create<LookAtCamera>();
		PtrView->SetCamera(PtrLookAtCamera);

		PtrLookAtCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrLookAtCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		/*auto PtrWhiteOut = AddGameObject<WhiteOut>();
		SetSharedGameObject(L"WhiteOut", PtrWhiteOut);*/
	}

	void TitleScene::OnCreate() {
		try {

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
	}
	
	void TitleScene::OnUpdate() {
	//	auto PtrWhiteIn = GetSharedGameObject<WhiteOut>(L"WhiteOut");
	//	//�f�o�b�N�L�[
	//	//�L�[�{�[�h�̎擾
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			//		PtrWhiteIn->StartWhite();
			//	}
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//	if (PtrWhiteIn->GetWhiteFinish()) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameScene");
		}
	}

}
//end basecross
