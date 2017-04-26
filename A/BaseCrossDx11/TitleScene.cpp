/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/
//�v���C���[��LookAtCamera��MyLookAtCamera�ɕύX����Ύ���
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	//�r���[�ƃ��C�g�̍쐬
	void TitleScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�(�J�����Œ�)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();
		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	void TitleScene::CreateBackGround() {
		
		AddGameObject<TitleSprite>(
			Vector2(1280, 720),
			Vector2(0, 0)
			);
		AddGameObject<PressSprite>(
			Vector2(512, 512),
			Vector2(0, -180)
			);
		
		//AddGameObject<InputCSV>();
	}

	void TitleScene::OnCreate() {
		try {
			
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�̍쐬
			CreateBackGround();	
			AddGameObject<DimSprite>(true,
				Vector2(1280, 720),
				Vector2(0, 0));
		}
		
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		//�R���g���[��
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
		}
	}
	//�j��
	 TitleScene::~TitleScene() {
		
	}

}
//end basecross
