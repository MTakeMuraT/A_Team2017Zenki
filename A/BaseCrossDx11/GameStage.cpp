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
		/*
		//�r���[�̃J�����̐ݒ�
		auto PtrLookAtCamera = ObjectFactory::Create<LookAtCamera>();
		PtrView->SetCamera(PtrLookAtCamera);

		PtrLookAtCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrLookAtCamera->SetAt(Vector3(0.0f, 5.0f, -15.0f));

		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();

		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
		*/
		//�r���[�̃J�����̐ݒ�(�J�����Œ�)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

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

	//�����������̂��e�X�g���鎞�Ɏg�p
	void GameStage::CreateTestLin() {
		AddGameObject<FixdBox>(
			Vector3(1, 1, 1),
			Vector3(0, 0, 0),
			Vector3(0, 1, -5),
			wstring(L"TRACE_TX")
			);
		/*AddGameObject<FixdBox>(
			Vector3(1, 1, 1),
			Vector3(0, 0, 0),
			Vector3(0, 1, 5),
			wstring(L"TRACE_TX")
			);*/
	}

	void GameStage::OnCreate()
	{
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreatePlate();
			CreatePlayerLin();
			CreateGround();
			CreateTestLin();
			//�w�i�̍쐬
			CreateBackGround();


			//Abe20170412
			//�G�l�~�[����Ă݂�
			AddGameObject<Enemy01>(Vector3(0, 1, 5), Vector3(1, 1, 1));
			//Abe20170412

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

		//�J�����X�V
		UpdateCamera();
	}

	//�J�����X�V
	void GameStage::UpdateCamera()
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//���W
		Vector3 Pos = CameraP->GetEye();
		//���镔��
		Vector3 At = CameraP->GetAt();


		//�Q�̂̍��W���炤
		Vector3 Player1Pos = GetSharedGameObject<Player>(L"GamePlayer", false)->GetComponent<Transform>()->GetPosition();
		Vector3 Player2Pos = GetSharedGameObject<Player_Second>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();

		//����_���v���C���[�Ԃ̒��S
		At = (Player1Pos + Player2Pos) / 2;
		//���W��������Ǝ�O��
		Pos = At;
		//�����𑪂�
		Vector3 def = Player2Pos - Player1Pos;
		def = def*def;
		//�㏸��
		float Yup = sqrt(def.x + def.z) - 6;
		//�㏸���ɃJ�����̏���������ǉ�
		Yup += 10;
		if (Yup < 10)
		{
			Yup = 10;
		}
		Pos.y = Yup;
		//�����l��Z�ɂ�
		Pos.z = -Yup;

		//�J�����X�V
		CameraP->SetEye(Pos);
		CameraP->SetAt(At);
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
