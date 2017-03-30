#include "stdafx.h"
#include "Project.h"
//�񋟌��̕\���p�V�[��
namespace basecross
{
	// �r���[�A���C�g
	void LicenseScene::CreateViewLight()
	{
		auto ViewPtr = CreateView<SingleView>();

		// �J�����ݒ�
		auto LookAtCameraPtr = ObjectFactory::Create<LookAtCamera>();
		ViewPtr->SetCamera(LookAtCameraPtr);
		LookAtCameraPtr->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		LookAtCameraPtr->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		// �V���O�����C�g
		auto SingleLightPtr = CreateLight<SingleLight>();

		// ���C�g�ݒ�
		SingleLightPtr->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
	}

	// ���C�Z���X�\���̃e�N�X�`��
	void LicenseScene::CreateLicenseTex()
	{
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();

		PtrTrans->SetScale(1280, 800, 0.5f);
		PtrTrans->SetRotation(0.0, 0.0f, 0.0);
		PtrTrans->SetPosition(0.0f, 0.25f, -1.0f);

		// �`��
		auto DrawComp = Ptr->AddComponent<PCTSpriteDraw>();
		DrawComp->SetTextureResource(L"credit_TX");
	}

	// ������
	void LicenseScene::OnCreate()
	{
		try
		{
			// �r���[�A���C�g
			CreateViewLight();

			// ���C�Z���X�\���̃e�N�X�`��
			CreateLicenseTex();

		}
		catch (...)
		{
			throw;
		}
	}

	// �X�V
	void LicenseScene::OnUpdate()
	{

	}
}
// end basecross