#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();

		//�r���[�̃J�����̐ݒ�
		auto PtrLookAtCamera = ObjectFactory::Create<LookAtCamera>();
		PtrView->SetCamera(PtrLookAtCamera);

		PtrLookAtCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrLookAtCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();

		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
	}


	//�v���[�g�̍쐬
	void GameStage::CreatePlate()
	{
		AddGameObject<TestLin>(
			Vector3(256, 256, 0),
			Vector3(0, 0, 0),
			3
			);
	}

	// �w�i
	void GameStage::CreateBackGround()
	{


	}
	void GameStage::OnCreate()
	{
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreatePlate();
			

			//�w�i�̍쐬
			CreateBackGround();
			

			
		}
		catch (...) {



			throw;
		}
	}



	// �X�V
	// �V�[���J��
	void GameStage::OnUpdate()
	{
		//�R���g���[��
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
		}
	}

}
//end basecross
