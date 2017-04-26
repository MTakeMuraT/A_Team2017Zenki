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
	void StageSelectScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�(�J�����Œ�)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 30.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();
		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	//�e�X�g�\��
	void StageSelectScene::CreatTestLin() {
		AddGameObject<StageSelectSprite>(
			Vector2(1280, 720),
			Vector2(0, 0),
			0
			);
	}

	//Abe20170421
	//�t���[���쐬
	void StageSelectScene::CreateFlame()
	{
		AddGameObject<SelectFlame>(Vector2(0, 0), Vector2(1280, 720), 1);
	}

	//�v���C���[�쐬
	void StageSelectScene::CreatePlayer()
	{
		SetSharedGameObject(L"SelectPlayer", AddGameObject<SelectPlayer>(Vector3(0, 0, 0), Vector3(1, 1, 1),30.0f));
	}

	//�X�e�[�W�{�b�N�X�쐬
	void StageSelectScene::CreateStageBox()
	{
		AddGameObject<StageBox>(Vector3(0,0,0),Vector3(1,1,1),1);
	}

	//�X�e�[�W�s�����`�F�b�N����X�v���C�g
	void StageSelectScene::CreateGoCheck()
	{
		SetSharedGameObject(L"GoStageCheck", AddGameObject<GoStageCheck>(Vector2(200, 200)));
	}
	//Abe20170421

	void StageSelectScene::OnCreate()
	{
		try {
			CreateViewLight();
			//CreatTestLin();
			//Abe20170421
			//�t���[���쐬
			CreateFlame();
			//�v���C���[�쐬
			CreatePlayer();
			//�X�e�[�W�{�b�N�X�쐬
			CreateStageBox();
			//�X�e�[�W�s�����`�F�b�N����X�v���C�g
			CreateGoCheck();
			//Abe20170421

		}
		catch (...) {

			throw;
		}
	}

	void StageSelectScene::OnUpdate() {
		//�L�[�̓���
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
		}
	}

}
//end basecross
