#include "stdafx.h"
#include "Project.h"
//提供元の表示用シーン
namespace basecross
{
	// ビュー、ライト
	void LicenseScene::CreateViewLight()
	{
		auto ViewPtr = CreateView<SingleView>();

		// カメラ設定
		auto LookAtCameraPtr = ObjectFactory::Create<LookAtCamera>();
		ViewPtr->SetCamera(LookAtCameraPtr);
		LookAtCameraPtr->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		LookAtCameraPtr->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		// シングルライト
		auto SingleLightPtr = CreateLight<SingleLight>();

		// ライト設定
		SingleLightPtr->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
	}

	// ライセンス表示のテクスチャ
	void LicenseScene::CreateLicenseTex()
	{
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();

		PtrTrans->SetScale(1280, 800, 0.5f);
		PtrTrans->SetRotation(0.0, 0.0f, 0.0);
		PtrTrans->SetPosition(0.0f, 0.25f, -1.0f);

		// 描画
		auto DrawComp = Ptr->AddComponent<PCTSpriteDraw>();
		DrawComp->SetTextureResource(L"credit_TX");
	}

	// 初期化
	void LicenseScene::OnCreate()
	{
		try
		{
			// ビュー、ライト
			CreateViewLight();

			// ライセンス表示のテクスチャ
			CreateLicenseTex();

		}
		catch (...)
		{
			throw;
		}
	}

	// 更新
	void LicenseScene::OnUpdate()
	{

	}
}
// end basecross