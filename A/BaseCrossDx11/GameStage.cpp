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
		//Abe20170525
		//�X�e�[�W�̑傫���擾
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize();
		//Abe20170525

		//Vector3:S�EP  wstring:TX_Name
		AddGameObject<Ground_GameStage>(
			Vector3(m_StageSize.x, m_StageSize.y, 1),
			Vector3(0, 0, 0),
			wstring(L"Glass_TX")
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
		SetSharedGameObject(L"PtrPlayerManager",PtrPlayerManager);
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
		AddGameObject<SkySphere>(
			Vector3(500,500,500),
			Vector3(0,0,0));
		AddGameObject<Ground_GameStage>(
			Vector3(300, 300, 300),
			Vector3(0, -50, 0),
			wstring(L"Background_TX")
			);

		//AddGameObject<Enemycount>();
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
		auto Ti = AddGameObject<Timer>(0, Vector2(35, 300), Vector2(70, 70), 5);
		SetSharedGameObject(L"Timer", Ti);

		//�����O���[�v�ɒǉ�
		GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(Ti);
	}
	//�^�C�}�[�쐬------------------------------------------
	//���C�t�쐬--------------------------------------------
	void GameStage::CreateLife()
	{
		auto life = AddGameObject<Player_Life>(10, Vector2(-580, 300), Vector2(100, 100), 4);
		SetSharedGameObject(L"Life", life);

		//�����O���[�v�ɒǉ�
		GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(life);

	}
	//���C�t�쐬--------------------------------------------

	//�A�^������쐬--------------------------------------------
	void GameStage::CreateCollision()
	{
		auto ColMan = AddGameObject<CollisionManager>();
		auto ColSandPtr = AddGameObject<CollisionSand>();
		SetSharedGameObject(L"CollisionSand", ColSandPtr);

		//�����O���[�v�ɒǉ�
		GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(ColMan);
		GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(ColSandPtr);

	}
	//�A�^������쐬--------------------------------------------

	//�G�l�~�[�J�E���g�쐬--------------------------------------------
	void GameStage::CreateEnemyCounts()
	{
		AddGameObject<EnemyCountA>(Vector2(520, -250), Vector2(100, 100), 3);
	}
	//�G�l�~�[�J�E���g�쐬--------------------------------------------

	//Abe20170605
	//�|�[�Y�쐬--------------------------------------------
	void GameStage::CreatePause()
	{
		SetSharedGameObject(L"PauseMenu",AddGameObject<PauseMenu>());
	}
	//�|�[�Y�쐬--------------------------------------------
	//Abe20170605

	void GameStage::OnCreate()
	{
		try {
			////���؂���̂ɏd���̂ňꎞ�I�ɏ����܂� Abe20170505
			//m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			//m_AudioObjectPtr->AddAudioResource(L"GameStage_01_BGM");
			//m_AudioObjectPtr->Start(L"GameStage_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			//m_AudioObjectPtr->AddAudioResource(L"Win_SE");


			//�O���[�v�ލ쐬
			auto TereportGroup = CreateSharedObjectGroup(L"TereportPointGroup");
			auto BomGroup = CreateSharedObjectGroup(L"BombGroup");
			auto EnemyGroup = CreateSharedObjectGroup(L"EnemyGroup");
			auto CollisionGroup = CreateSharedObjectGroup(L"CollisionGroup");
			//Abe20170529
			//�q�@�O���[�v
			CreateSharedObjectGroup(L"SearchChildGroup");
			CreateSharedObjectGroup(L"UgokuGroup");
			//Abe20170529
			//Abe20170605
			//���U����I�u�W�F�N�g�̃O���[�v
			CreateSharedObjectGroup(L"BakusanObjGroup");
			//���U����I�u�W�F�N�g�𐶐�����I�u�W�F�N�g
			SetSharedGameObject(L"BakuSanSpawn",AddGameObject<BakuSanSpawn>());
			//Abe20170605
			//Abe20170606
			CreateSharedObjectGroup(L"BakusanEFGroup");
			//Abe20170606

			//Abe20170609
			//�Ԃ������G�t�F�N�g�O���[�v
			CreateSharedObjectGroup(L"ButukariEFGroup");
			//Abe20170609


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

			//Abe20170519MukkuMarge
			//�G�l�~�[�̐��쐬
			CreateEnemyCounts();
			//Abe20170519MukkuMarge

			//�A�^������쐬
			CreateCollision();

			//Abe20170605
			//�|�[�Y�쐬
			CreatePause();
			//Abe20170605

			//2017/05/17����CSV//
			AddGameObject<InputCSV>();
			/////////////////////////

			//�e�X�g(���G�T�[�N��)
			//Abe20170523IzumiHikitugi
			//AddGameObject<SearchCircle>();
			//Abe20170523IzumiHikitugi

			//Abe20170602
			//auto ob = AddGameObject<BombEffect>();
			//ob->SetPosActive(Vector3(0, 5, 0));
			//ob->SetDrawLayer(10);
			//Abe20170602

			//Abe20170605
			//****�Ńo�b�N
			//AddGameObject<BakuSanObj>()->SetPosScaleVelo(Vector3(0, 5, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 10, 5));
			//Abe20170605

			//Abe20170606
			//*****�f�o�b�N
			//AddGameObject<BakusanEF>()->SetPosScaActive(Vector3(0, 1, 0), Vector3(100, 100, 100));
			//Abe20170606

			//Abe20170609
			//*****�f�o�b�N
			//AddGameObject<ShotEnemyChildMissile>(Vector3(0, 1, 0), Vector3(1, 1, 1), Vector3(0, 0, 0), Vector3(0, 0, 0));
			//AddGameObject<ButukariEf>()->SetPosScaActive(Vector3(0,5,0),Vector3(1,1,1));
			//Abe20170609

			//Abe20170612
			//�V�[���h
			//SetSharedGameObject(L"Shield",AddGameObject<EnemyShield>(3, Vector3(0, 1, 0), Vector3(1, 1, 1), 1));
			//Abe20170612

		}
		catch (...) {



			throw;
		}
	}



	// �X�V
	// �V�[���J��
	void GameStage::OnUpdate()
	{
		//Abe20170609
		//�n�܂艉�o
		if (!GetSharedGameObject<StartState>(L"StartState", false))
		{
			SetSharedGameObject(L"StartState",AddGameObject<StartState>());
			return;
		}
		//Abe20170609


		auto PlayerLifePtr = GetSharedGameObject<Player_Life>(L"Life", false);
		if (PlayerLifePtr) {
			if (PlayerLifePtr->GetDieFlg() == false) {
				if (StopBGM == true) {
					//m_AudioObjectPtr->Stop(L"GameStage_01_BGM");
					StopBGM = false;
				}
			}
		}

		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//START�{�^���Ń|�[�Y
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START && !GetSharedGameObject<GameObject>(L"ResultS", false)
				&& !GetSharedGameObject<GameObject>(L"GameOverS", false)
				&& GetSharedGameObject<StartState>(L"StartState",false)->GetFinish())
			{
				if (GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->GetPushFlg())
				{
					//�|�[�Y�\��
					GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->Open();

					//�o�O���p
					GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->SetPushFlg(false);
				}
				else
				{
					//�|�[�Y�\��
					GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->Close();

					//�o�O���p
					GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->SetPushFlg(true);

				}
			}
		}

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

			//Abe2010612
			//�f�o�b�O�V�[���h���炷
			//GetSharedGameObject<EnemyShield>(L"Shield")->Damage(10);
			//Abe2010612
			//�j��
			//GetSharedGameObject<BakuSanSpawn>(L"BakuSanSpawn", false)->CreateBakusan(20, Vector3(0, 0.5f, -3));

			//�|�[�Y�\��
		//	GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->Open();
		}

		//Abe20170531
		//���Ń��U���g�\��**********�f�o�b�O*********
		if (KeylVec.m_bPressedKeyTbl['B'])
		{
			//m_AudioObjectPtr->Stop(L"GameStage_01_BGM");
			//m_AudioObjectPtr->Start(L"Win_SE", 0, 0.5f);


			Result();
		}
		//���Ń��U���g�\��**********�f�o�b�O*********
		//Abe20170531

		if (m_CameraMoveFlg)
		{
			//�J�����X�V
			UpdateCamera();
		}
		//�_���[�W�󂯂Ă�Ƃ�
		if (m_DamageFlg)
		{
			//�_���[�W�J����
			DamageCamera();
		}
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
		Yup += 15;
		if (Yup < 15)
		{
			Yup = 15;
		}
		Pos.y += Yup;
		//�����l��Z�ɂ�
		Pos.z += -Yup;

		//�J�����X�V
		CameraP->SetEye(Pos);
		CameraP->SetAt(At);
	}


	GameStage::~GameStage() {
		if (StopBGM == true) {
			//m_AudioObjectPtr->Stop(L"GameStage_01_BGM");
		}
	}

	//Abe20170529
	//�Q�[���I�[�o�[����
	void GameStage::GameOver()
	{
		auto ptr = GetSharedGameObject<GameObject>(L"ResultS", false);
		auto ptr2 = GetSharedGameObject<GameObject>(L"GameOverS", false);
		if (!ptr && !ptr2)
		{
			SetSharedGameObject(L"GameOverS",AddGameObject<GameOverS>());
		}
	}
	//Abe20170529

	//Abe20170530
	//�Q�[���I�[�o�[�����J����
	bool GameStage::GameOverCamera()
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//���W
		Vector3 Pos = CameraP->GetEye();
		//���镔��
		Vector3 At = CameraP->GetAt();

		//�ړ�
		Vector3 targetpos = Vector3(0, 15, -5);
		Vector3 dis = targetpos - Pos;
		dis /= 10;
		Pos += dis;

		At = Pos + Vector3(0, -5, 5);

		//�J�����ړ�
		CameraP->SetEye(Pos);
		CameraP->SetAt(At);

		if (abs(targetpos.x - Pos.x) + abs(targetpos.y - Pos.y) + abs(targetpos.z - Pos.z) < 0.1f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//Abe20170530

	//Abe20170531
	//���U���g����
	void GameStage::Result()
	{
		auto ptr = GetSharedGameObject<GameObject>(L"ResultS", false);
		auto ptr2 = GetSharedGameObject<GameObject>(L"GameOverS", false);
		if (!ptr && !ptr2)
		{
			SetSharedGameObject(L"ResultS", AddGameObject<ResultS>());
		}
	}
	
	//���U���g�J��������
	bool GameStage::ResultCamera(Vector3 pos)
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//���W
		Vector3 Pos = CameraP->GetEye();
		//���镔��
		Vector3 At = CameraP->GetAt();

		//�ړ�
		Vector3 targetpos = pos;
		//������ƌ���ɂ��炷
		targetpos += Vector3(0, 2, -8);
		Vector3 dis = targetpos - Pos;
		dis /= 10;
		Pos += dis;

		//At���ړ��A�ړ����(�v���C���[�̒��S)
		Vector3 targetAt = pos;
		//������Ƃ��炷
		targetAt += Vector3(0, 1, 0);
		Vector3 disAt = targetAt - At;
		disAt /= 10;
		At += disAt;

		//�ڕW�n�_�ɋ߂����true��Ԃ��ĉ�����΃J�������ړ�����false��Ԃ�
		if (abs(targetpos.x - Pos.x) + abs(targetpos.y - Pos.y) + abs(targetpos.z - Pos.z) < 0.1f)
		{
			return true;
		}
		else
		{
			//�J�����ړ�
			CameraP->SetEye(Pos);
			CameraP->SetAt(At);

			return false;
		}

	}
	//Abe20170531

	//Abe20170612
	//�_���[�W�J�������o
	void GameStage::DamageCamera()
	{
		m_CameraMoveFlg = false;

		m_damageTime += App::GetApp()->GetElapsedTime();
		if (m_damageTime > m_damageinterval)
		{
			//�v�Z�p����
			m_damageTime = 0;

			//�h�炷�J�E���g
			m_damageCameraCount++;

			//�J�����h�炷
			auto View = GetView();
			auto CameraP = View->GetTargetCamera();
			//���W
			Vector3 pos = CameraP->GetEye();
			Vector3 at = CameraP->GetAt();

			Vector3 randvec3 = Vector3((rand() % 30 - 15) / 10, 0, (rand() % 30 - 15) / 10);
			pos += randvec3;
			at += randvec3;

			//�J�����ړ�
			CameraP->SetEye(pos);
			CameraP->SetAt(at);

			//�w��񐔕��������
			if (m_damageCameraCount >= 5)
			{
				m_DamageFlg = false;
				m_damageCameraCount = 0;
				m_CameraMoveFlg = true;

			}
		}
		else if (m_damageTime > m_damageinterval/2)
		{
			m_CameraMoveFlg = true;
		}
	}
	//Abe20170612

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
		else if(m_TX_Name == L"Glass_TX"){
			PtrDraw->SetTextureResource(m_TX_Name);
			SetDrawLayer(2);
		}

		
		auto PtrTrans = AddComponent<Transform>();
		Quaternion Qt;
		Qt.RotationRollPitchYawFromVector(Vector3(XM_PIDIV2, 0, 0));
		Matrix4X4 WorldMat;
		WorldMat.DefTransformation(
			Vector3(100.0f, 100.0f, 1.0f),
			Qt,
			Vector3(0.0f, -1.0f, 0.0f)
		);

		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(m_Positon);
		//PtrDraw->SetDrawActive(false);
		SetAlphaActive(true);
	}
}

//end basecross
