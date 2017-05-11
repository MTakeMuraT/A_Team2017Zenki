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
			Vector3(0, 1, 0),
			wstring(L"PlayerL")
			);
		SetSharedGameObject(L"GamePlayer_L", PtrPlayer_L);
		auto PtrPlayer_R = AddGameObject<Player>(
			Vector3(5, 1, 0),
			wstring(L"PlayerR")
			);
		auto PtrPlayerManager = AddGameObject<PlayerManager>();
		SetSharedGameObject(L"PtrPlayerManager", false);
		SetSharedGameObject(L"GamePlayer_R", PtrPlayer_R);
		auto PtrPlayerCenter = AddGameObject<PlayerCenter>();
		SetSharedGameObject(L"PlayerCenter", PtrPlayerCenter);
		auto PtrPlayerHP = AddGameObject<PlayerHP>();
		SetSharedGameObject(L"PlayerHP", PtrPlayerHP);
		////HP�֌W
		//AddGameObject<HP>(
		//	Vector2(512, 512),
		//	Vector2(-440, 300));
		//AddGameObject<HPBackGround>(
		//	Vector2(512, 512),
		//	Vector2(-440, 300));
	}

	void GameStage::CreateUILin() {

	}

	//�������������̂��e�X�g���鎞�Ɏg�p
	void GameStage::CreateTestLin() {
		AddGameObject<FixdBox>(
			Vector3(1, 1, 1),
			Vector3(0, 0, 0),
			Vector3(0, 1, -5),
			wstring(L"TRACE_TX")
			);
		AddGameObject<SkySphere>(
			Vector3(300,300,300),
			Vector3(0,0,0));
		AddGameObject<Ground_GameStage>(
			Vector3(300, 300, 300),
			Vector3(0, -50, 0),
			wstring(L"Background_TX")
			);
		/*AddGameObject<FixdBox>(
			Vector3(1, 1, 1),
			Vector3(0, 0, 0),
			Vector3(0, 1, 5),
			wstring(L"TRACE_TX")
			);*/

		
	}
	//�^�C�}�[�쐬------------------------------------------
	void GameStage::CreateTimer()
	{
		auto Ti = AddGameObject<Timer>(60, Vector2(50, 300), Vector2(100, 100), 5);
		SetSharedGameObject(L"Timer", Ti);
	}
	//�^�C�}�[�쐬------------------------------------------
	//���C�t�쐬--------------------------------------------
	void GameStage::CreateLife()
	{
		auto life = AddGameObject<Player_Life>(10, Vector2(-580, 300), Vector2(100, 100), 4);
		SetSharedGameObject(L"Life", life);
	}
	//���C�t�쐬--------------------------------------------

	//�A�^������쐬--------------------------------------------
	void GameStage::CreateCollision()
	{
		AddGameObject<CollisionManager>();
		auto ColSandPtr = AddGameObject<CollisionSand>();
		SetSharedGameObject(L"CollisionSand", ColSandPtr);
	}
	//�A�^������쐬--------------------------------------------
	
	//�~�T�C���q�@
	void GameStage::CreateChildMissile() {
		auto ColGroup = GetSharedObjectGroup(L"EnemyGroup");
		auto PtrShotEnemyChild = AddGameObject<ShotEnemyChild>(
			Vector3(0, 1, 0),
			Vector3(1.0, 1.0, 1.0),
			0.0f
			);
		SetSharedGameObject(L"ShotEnemyChild", PtrShotEnemyChild);
		ColGroup->IntoGroup(PtrShotEnemyChild);
	}
	void GameStage::OnCreate()
	{
		try {
			/*//���؂���̂ɏd���̂ňꎞ�I�ɏ����܂� Abe20170505
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"GameStage_01_BGM");
			m_AudioObjectPtr->Start(L"GameStage_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			*/
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreatePlate();
			CreatePlayerLin();
			CreateGround();
			CreateUILin();
			//��������
			CreateTimer();
			//���C�t
			CreateLife();
			//�w�i�̍쐬
			CreateBackGround();
			CreateTestLin();

			//�A�^������쐬
			CreateCollision();

			

			//Abe20170412
			//�G�l�~�[����Ă݂�[�A�^������Ƃ��e�X�g���邽�߂̉��̂�Ȃ̂�CSV�ŏo����悤�ɂȂ���������Ă�������]

			auto EnemyGroup = CreateSharedObjectGroup(L"EnemyGroup");

			auto Enemy_01Ptr = AddGameObject<Enemy01>(Vector3(0, 1, 5), Vector3(1, 1, 1));
			SetSharedGameObject(L"Enemy01", Enemy_01Ptr);
			auto Enemy_02Ptr = AddGameObject<Enemy01>(Vector3(0, 1, -5), Vector3(1, 1, 1));
			SetSharedGameObject(L"Enemy02", Enemy_02Ptr);

			EnemyGroup->IntoGroup(Enemy_01Ptr);
			EnemyGroup->IntoGroup(Enemy_02Ptr);
			//Abe20170412

			//�q�@�~�T�C��
			CreateChildMissile();

			//Abe20170504
			//�A�^������e�X�g�p[�Ƃ肠�����O���[�v�ɂ�������Ă����΂���ł����ł�]
			auto CollisionGroup = CreateSharedObjectGroup(L"CollisionGroup");
			auto Enemy_03Ptr = AddGameObject<Enemy01>(Vector3(0, 1, 5), Vector3(1, 1, 1));
			SetSharedGameObject(L"Enemy03", Enemy_01Ptr);
			CollisionGroup->IntoGroup(Enemy_03Ptr);

			//Abe20170504

			//Abe20170505
			//�G�l�~�[�e�X�g
			//���� �ʒu�A�傫���AHP�A���G�����A�N�[���^�C���A���x�A�U���́A�ˌ���
			auto PtrTacklEnemy = AddGameObject<TackleEnemy>(Vector3(10, 1, 10), 1, 0, 3, 3, 6, 3, 2);
			CollisionGroup->IntoGroup(PtrTacklEnemy);
			EnemyGroup->IntoGroup(PtrTacklEnemy);
			//PtrTacklEnemy = AddGameObject<TackleEnemy>(Vector3(-10, 1, 10), 1, 0, 3, 3, 6, 3, 2);
			//CollisionGroup->IntoGroup(PtrTacklEnemy);
			//EnemyGroup->IntoGroup(PtrTacklEnemy);
			//PtrTacklEnemy = AddGameObject<TackleEnemy>(Vector3(10, 1, -10), 1, 1, 3, 3, 6, 3, 2);
			//CollisionGroup->IntoGroup(PtrTacklEnemy);
			//EnemyGroup->IntoGroup(PtrTacklEnemy);
			//PtrTacklEnemy = AddGameObject<TackleEnemy>(Vector3(-10, 1, -10), 1, 1, 3, 3, 6, 3, 2);
			//CollisionGroup->IntoGroup(PtrTacklEnemy);
			//EnemyGroup->IntoGroup(PtrTacklEnemy);

			//���� �ʒu�A�傫���AHP�A���G�����A�N�[���^�C���A�U���́A�q�@���ˊԊu�A���ː�
			//AddGameObject<ShotEnemy>(Vector3(10, 1, -10),1,3,5,6,3,10,2);
			//���� �ʒu�A�傫���AHP�A���G�����A�N�[���^�C���A���ː�
			//AddGameObject<TeleportEnemy>(Vector3(-10, 1, 10),2,1,5,8,3);
			//���� �ʒu�A�傫���AHP�A���G�����A���x�A�U����
			//Abe20170505
			auto objbomb = AddGameObject<BombEnemy>(Vector3(20, 1, 20), 1, 1, 3, 2, 8);
			CollisionGroup->IntoGroup(objbomb);
			EnemyGroup->IntoGroup(objbomb);
			
			//Abe20170508
			//�e���|�[�g��쐬
			auto TereportGroup = CreateSharedObjectGroup(L"TereportPointGroup");
			//�K���ɂQ��������Ă���
			TereportGroup->IntoGroup(AddGameObject<TereportPoint>(Vector3(3, 0.5f, 3)));
			TereportGroup->IntoGroup(AddGameObject<TereportPoint>(Vector3(-3, 0.5f, -3)));

			//�e���|�[�g�G�l�~�[
			//���� �ʒu�A�傫���AHP�A���G�����A�N�[���^�C���A���ː�
			AddGameObject<TeleportEnemy>(Vector3(-10, 1, 10), 1, 1, 5, 1, 3);
			//���e�O���[�v
			CreateSharedObjectGroup(L"BombGroup");
			//Abe20170508



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
		if (KeylVec.m_bPressedKeyTbl['D'])
		{
			//���C�t���炷
			GetSharedGameObject<Player_Life>(L"Life")->LifeDown(1);

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
		Vector3 Player1Pos = GetSharedGameObject<Player>(L"GamePlayer_L", false)->GetComponent<Transform>()->GetPosition();
		Vector3 Player2Pos = GetSharedGameObject<Player>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();

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
		Pos.y += Yup;
		//�����l��Z�ɂ�
		Pos.z += -Yup;

		//�J�����X�V
		CameraP->SetEye(Pos);
		CameraP->SetAt(At);
	}
	GameStage::~GameStage() {
		//m_AudioObjectPtr->Stop(L"GameStage_01_BGM");
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
		if (m_TX_Name == L"Background_TX") {
			PtrDraw->SetTextureResource(m_TX_Name);
		}
		else if(m_TX_Name == L"TEST_Game_TX"){
			PtrDraw->SetTextureResource(m_TX_Name);
		}


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
		//PtrDraw->SetDrawActive(false);
	}

}
//end basecross
