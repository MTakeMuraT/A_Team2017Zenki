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
		PtrLookAtCamera->SetAt(Vector3(0.0f, 5.0f, -15.0f));

		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();

		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
	}


	//�v���[�g�̍쐬
	void GameStage::CreatePlate()
	{
		/*AddGameObject<TestLin>(
			Vector3(256, 256, 0),
			Vector3(0, 0, 0),
			3
			);*/
	}

	// �w�i
	void GameStage::CreateBackGround()
	{


	}
	//�n��
	void GameStage::CreateGround() {
		//Vector3:S�EP  wstring:TX_Name
		AddGameObject<Ground_GameStage>(
			Vector3(25, 25, 25),
			Vector3(0, 0, 0),
			wstring(L"TEST_Game_TX")
			);
	}

	//�v���C���[�֌W
	void GameStage::CreatePlayerLin() {
		auto PtrPlayer_L = AddGameObject<Player>(
			Vector3(0, 1, 0)
			);
		SetSharedGameObject(L"GamePlayer", PtrPlayer_L);
		auto PtrPlayer_R = AddGameObject<Player_Second>(
			Vector3(5, 1, 0)
			);
		SetSharedGameObject(L"GamePlayer_R", PtrPlayer_R);
	}


	void GameStage::OnCreate()
	{
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreatePlate();
			CreatePlayerLin();
			CreateGround();

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
		//�L�[�̓���
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
		}
	}


	//////////////////////////////////////////////////////////////////
	// class Ground_GameStage : public GameObject
	//�R���X�g���N�^�@Vector3 Scale; Vector3 Postion wstring TX_Name
	///////////////////////////////////////////////////////////////////
	Ground_GameStage::Ground_GameStage(const shared_ptr<Stage>& StagePtr,
		const Vector3& Scale,
		const Vector3& Postion,
		const wstring& TX_Name):
	GameObject(StagePtr),
	m_Scale(Scale),
	m_Positon(Postion),
	m_TX_Name(TX_Name)
	{}
	void Ground_GameStage::OnCreate() {
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		PtrDraw->SetTextureResource(m_TX_Name);


		auto PtrTrans = AddComponent<Transform>();
		Quaternion Qt;
		Qt.RotationRollPitchYawFromVector(Vector3(XM_PIDIV2, 0, 0));
		Matrix4X4 WorldMat;
		WorldMat.DefTransformation(
			Vector3(100.0f, 100.0f, 1.0f),
			Qt,
			Vector3(0.0f, 0.0f, 0.0f)
		);

		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(m_Positon);

	}

}
//end basecross
