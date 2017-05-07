/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos, const wstring& PlayerLorPlayerR) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_Player_Str(PlayerLorPlayerR)
	{}
	//������
	void Player::OnCreate() {
		shared_ptr<CollisionSand> m_CollisionSand;
		//m_Collision_Sphere = GetStage()->AddGameObject<Collision_Sphere>();
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(1.0f, 1.0f, 1.0f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);
		Vector3 Rot;
		if (m_Player_Str == L"PlayerL") {
			Rot = Vector3(0, -XM_PI / 2, 0);
		}
		else {
			Rot = Vector3(0, XM_PI / 2, 0);
		}

		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 PlayerMat;
		PlayerMat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(Rot),
			Vector3(0.0f, -0.61f, 0.0f)
		);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		//auto PtrCol = AddComponent<CollisionSphere>();

		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFontColor(Color4(1.0f, 0.0f, 0.0f, 1.0f));
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"Player_Model");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTBoneModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"Player_Model");
		//�`�悷��e�N�X�`����ݒ�
		//PtrDraw->SetTextureResource(L"TRACE_TX");

		//��������
		SetAlphaActive(true);
		PtrDraw->SetMeshToTransformMatrix(PlayerMat);

	}
	void Player::OnUpdate() {
		
	}

	
	//////////////////////////////////////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------------------
	///	�v���C���[�Z���^�[
	//--------------------------------------------------------------------------------------
	PlayerCenter::PlayerCenter(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void PlayerCenter::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(0.0f, 0.5f, 5.0f);

		////�e������i�V���h�E�}�b�v��`�悷��j
		//auto ShadowPtr = AddComponent<Shadowmap>();
		////�e�̌`�i���b�V���j��ݒ�
		//ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		////�`��R���|�[�l���g�̐ݒ�
		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		////�`�悷�郁�b�V����ݒ�
		//PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		////�`�悷��e�N�X�`����ݒ�
		//PtrDraw->SetTextureResource(L"TRACE_TX");
		////��������
		//SetAlphaActive(true);
		auto PtrRig = AddComponent<Rigidbody>();

		//�����ʒu���̂̃v���C���[�̐^�񒆂ɐݒ�
		auto Trans = GetComponent<Transform>();
		auto PtrPlayerL_Pos = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false)->GetComponent<Transform>()->GetPosition();
		auto PtrPlayerR_Pos = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
		auto PlayerHalf = (PtrPlayerL_Pos + PtrPlayerR_Pos) / 2;
		Trans->SetPosition(PlayerHalf);

	}

	void PlayerCenter::OnUpdate() {
		auto Trans = GetComponent<Transform>();
		auto Rig = GetComponent<Rigidbody>();
		auto Qt = Trans->GetQuaternion();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrPlayer_Vel = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false)->GetComponent<Rigidbody>()->GetVelocity();
		Rig->SetVelocity(PtrPlayer_Vel);


		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
			Quaternion SpanQt(Vector3(0, 1, 0), -ElapsedTime * 2.0f);
			Qt *= SpanQt;
			Trans->SetQuaternion(Qt);
		}
		else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			Quaternion SpanQt(Vector3(0, 1, 0), ElapsedTime * 2.0f);
			Qt *= SpanQt;
			Trans->SetQuaternion(Qt);
		}

		auto PtrPlayerL_Pos = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false)->GetComponent<Transform>()->GetPosition();
		auto PtrPlayerR_Pos = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
		auto PlayerHalf = (PtrPlayerL_Pos + PtrPlayerR_Pos) / 2;
		Trans->SetPosition(PlayerHalf);
	}
	


	//--------------------------------------------------------------------------------------
	//	class SkySphere : public GameObject;
	//	�p�r: �X�J�C�X�t�B�A
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	SkySphere::SkySphere(const shared_ptr<Stage>& StagePtr,
		const Vector3& Scale,
		const Vector3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SkySphere::~SkySphere() {}

	//������
	void SkySphere::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_Position);


		//�e������
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetTextureResource(L"Background_TX");
		SetAlphaActive(true);

	}
	//--------------------------------------------------------------------------------------
	//	class PlayerManager : public GameObject;
	//	�p�r: �v���C���[�}�l�[�W���[
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	PlayerManager::PlayerManager(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}


	//������
	void PlayerManager::OnCreate() {
		//������

		//�X�e�[�g�}�V�[���쐬�@�����X�e�[�g�ݒ�
		m_StateManagerMachine = make_shared<StateMachine<PlayerManager> >(GetThis<PlayerManager>());
		m_StateManagerMachine->ChangeState(GamePrepareState_Manager::Instance());

		AddComponent<Rigidbody>();
		//�I�[�f�B�I���\�[�X�o�^
		auto pMultiSoundEffect = AddComponent<MultiSoundEffect>();
		pMultiSoundEffect->AddAudioResource(L"Collision_01_SE");


		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//�F���ɕύX
		m_Debugtxt->SetColor(Vector3(0, 0, 0));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);



	}
	void PlayerManager::OnUpdate() {
		m_StateManagerMachine->Update();
	}
	void PlayerManager::OnLastUpdate() {


		/*wstring PosStr(L"�f�o�b�N�����ʒuL�F:\t");
		PosStr += L"X=" + Util::FloatToWStr(GetDebugPlayerL().x, 6, Util::FloatModify::Fixed) + L",\t";
		PosStr += L"Y=" + Util::FloatToWStr(GetDebugPlayerL().y, 6, Util::FloatModify::Fixed) + L",\t";
		PosStr += L"Z=" + Util::FloatToWStr(GetDebugPlayerL().z, 6, Util::FloatModify::Fixed) + L"\n";
		*/


		/*wstring  str = PosStr;
		m_Debugtxt->SetText(str)*/;
	}
	//////////////�X�e�[�g�ȊO�̊֐��Q///////////////////////////////////////////////
	//�X�e�B�b�N����
	void PlayerManager::InputStick() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PlayerL_Rig = PlayerL_Ptr->GetComponent<Rigidbody>();
		auto PlayerR_Rig = PlayerR_Ptr->GetComponent<Rigidbody>();
		auto Rig = GetComponent<Rigidbody>();
		auto Trans = GetComponent<Transform>();
		if (m_StateManagerMachine->GetCurrentState() == MoveState_Manager::Instance()) {
			Move_Speed = Rig->GetMaxSpeed() / 5.0f;
		}
		else {
			Move_Speed = Rig->GetMaxSpeed() / 5.0f;
		}
		Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		PlayerL_Rig->SetVelocity(Vec_Vec3 * Move_Speed);
		PlayerR_Rig->SetVelocity(Vec_Vec3 * Move_Speed);


	}
	//��]
	void PlayerManager::InputRotation() {
		auto PlayerCenterPtr = GetStage()->GetSharedGameObject<PlayerCenter>(L"PlayerCenter");
		auto PlayerCenterPos = PlayerCenterPtr->GetComponent<Transform>()->GetPosition();
		auto PlayerCenterRot = PlayerCenterPtr->GetComponent<Transform>()->GetRotation();
		float RotY_Initialization = PlayerCenterRot.y;
		float RotY = RotY_Initialization;
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Trans = PlayerL_Ptr->GetComponent<Transform>();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Trans = PlayerR_Ptr->GetComponent<Transform>();
		if (PlayerL_Ptr) {
			RotY -= XM_PIDIV2;
		}
		auto PosL = Vector3(sin(RotY), 0, cos(RotY));
		//������//
		RotY = RotY_Initialization;
		//////////
		if (PlayerR_Ptr) {
			RotY += XM_PIDIV2;
		}
		auto PosR = Vector3(sin(RotY), 0, cos(RotY));

		PosL += PlayerCenterPos;
		PosR += PlayerCenterPos;
		PlayerL_Trans->SetScale(1.0, 1.0, 1.0);
		PlayerL_Trans->SetRotation(0, 0, 0);
		PlayerL_Trans->SetPosition(PosL);
		PlayerR_Trans->SetScale(1.0, 1.0, 1.0);
		PlayerR_Trans->SetRotation(0, 0, 0);
		PlayerR_Trans->SetPosition(PosR);

	}
	//������
	void PlayerManager::InitializationVelocity() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		PlayerL_Ptr->GetComponent<Rigidbody>()->SetVelocity(0, 0, 0);
		PlayerR_Ptr->GetComponent<Rigidbody>()->SetVelocity(0, 0, 0);
	}
	//����
	Vector3 PlayerManager::Direction(Vector3 MyPos, Vector3 PartnerPos) {
		//���΂Ɍ����ė~�����̂Ŏ���-����
		Direction_Vec3 = MyPos - PartnerPos;
		Direction_Vec3.Normalize();
		return Direction_Vec3;
	}
	//�ړ�
	Vector3 PlayerManager::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 = PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
	}
	//���f���̃v���C���[����
	void PlayerManager::PlayerAngle() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerCenterPtr = GetStage()->GetSharedGameObject<PlayerCenter>(L"PlayerCenter");
		auto PlayerCenterPos = PlayerCenterPtr->GetComponent<Transform>()->GetPosition();
		Vector3 Distance_Vec3 = PlayerCenterPos - PlayerL_Pos;
		Vector3 Distance2_Vec3 = PlayerCenterPos - PlayerR_Pos;

		float Angl = atan2(Distance_Vec3.z, -Distance_Vec3.x);
		float Angl2 = atan2(Distance2_Vec3.z, -Distance2_Vec3.x);
		Angl += XM_PI;

		Quaternion Qt(Vector3(0, 1, 0), Angl);
		Quaternion Qt2(Vector3(0, 1, 0), Angl2);

		PlayerL_Ptr->GetComponent<Transform>()->SetQuaternion(Qt);
		PlayerR_Ptr->GetComponent<Transform>()->SetQuaternion(Qt2);
	}
	/////////////////////////////////////////////////////////////////////////////////
	////////////////////////�X�e�[�g�V�F���W�֐�///////////////////////////////////
	void PlayerManager::StateChangeDoingInterpose() {
		//���܂ꂽ�Ώۂ���t���O�����炤
		auto PtrShotEnemyChild = GetStage()->GetSharedGameObject<ShotEnemyChild>(L"ShotEnemyChild", false);
		if (PtrShotEnemyChild->GetShotEnemyChildSandFlg()) {
			GetStateMachine_Manager()->ChangeState(DoingInterposeState_Manager::Instance());

		}
	}

	////////////////////////�X�e�[�g�X�^�[�g�֐�///////////////////////////////////
	void PlayerManager::EnterGamePrepare() {
		//�����Ȃ�
	}
	//�ړ�
	void PlayerManager::EnterMoveBehavior() {

	}
	//�����
	void PlayerManager::EnterLeaveBehavior() {


		////�����ʒu�̕ۑ�
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		PlayerL_SavePos_Vec3 = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		PlayerR_SavePos_Vec3 = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();

		PlayerL_Direction_Vec3 = Direction(PlayerL_SavePos_Vec3, PlayerR_SavePos_Vec3);
		PlayerR_Direction_Vec3 = Direction(PlayerR_SavePos_Vec3, PlayerL_SavePos_Vec3);
	}
	//�����t����
	void PlayerManager::EnterToAttractBehavior() {
		//�����蔻��
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		if (PtrCollisionSand) {
			PtrCollisionSand->SetActive(true);
		}
		else {
			throw BaseException(
				L"�G���[",
				L"�X�^�[�g�֐��̒��uEnterToAttractBehavior�v",
				L"PtrCollisionSand�����݂��Ă��܂���"
			);
		}
		////�i�ތ���
		PlayerL_Direction_Vec3 = Move_Velo(PlayerL_SavePos_Vec3, PlayerR_SavePos_Vec3);
		PlayerR_Direction_Vec3 = Move_Velo(PlayerR_SavePos_Vec3, PlayerL_SavePos_Vec3);


	}
	//�ŏ��̈ʒu�ɖ߂�
	void PlayerManager::EnterReturnBehavior() {
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		if (PtrCollisionSand) {
			PtrCollisionSand->SetActive(false);
		}
		else {
			throw BaseException(
				L"�G���[",
				L"�X�^�[�g�֐��̒��uExitLeaveBehavior�v",
				L"PtrCollisionSand�����݂��Ă��܂���"
			);
		}
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlaeyrR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		PlayerL_Velocity_Vec3 = Move_Velo(PlayerL_Pos, PlayerL_SavePos_Vec3);
		PlayerR_Velocity_Vec3 = Move_Velo(PlayerL_Pos, PlayerR_SavePos_Vec3);

	}
	//����ł���Ƃ�
	void PlayerManager::EneterDoingInterpose() {

	}
	////////////////////////�p�����֐�///////////////////////////////////
	void PlayerManager::ExecuteGamePrepare() {
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerCenterPtr = GetStage()->GetSharedGameObject<PlayerCenter>(L"PlayerCenter", false);
		auto PlayerCenterPos = PlayerCenterPtr->GetComponent<Transform>()->GetPosition();


		if (PtrCollisionSand && PlayerCenterPtr) {
			PtrCollisionSand->SetActive(false);
			//�߂�Ƃ��̖ڈ�
			PlayerL_Initial_Vec3 = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
			PLayerR_Initial_Vec3 = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
			PlayerL_Distance_Vec3 = PlayerL_Initial_Vec3 - PlayerCenterPos;
			PlayerR_Distance_Vec3 = PLayerR_Initial_Vec3 - PlayerCenterPos;
			GetStateMachine_Manager()->ChangeState(MoveState_Manager::Instance());
		}
		//		GetStateMachine_Manager()->ChangeState(MoveState_Manager::Instance());
	}
	//�ړ�
	void PlayerManager::ExecuteMoveBehavior() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		InputRotation();
		PlayerAngle();

		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//�X�e�[�g�ړ�
			GetStateMachine_Manager()->ChangeState(LeaveState_Manager::Instance());
		}
	}
	//�����
	void PlayerManager::ExecuteLeaveBehavior() {

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		auto Distance = PlayerL_Pos - PlayerR_Pos;

		//�@����鏈��
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 10;
		auto Rig = GetComponent<Rigidbody>();

		PlayerL_Direction_Vec3.y = 0;
		PlayerR_Direction_Vec3.y = 0;
		//New_Vec = �i�ޕ����@Speed_F = �ړ��X�s�[�h

		if (CntlVec[0].fThumbLX || CntlVec[0].fThumbLY) {
			InputStick();
		}
		else {
			PlayerL_Ptr->GetComponent<Rigidbody>()->SetVelocity(Vector3(PlayerL_Direction_Vec3.x, 0, PlayerL_Direction_Vec3.z)* Speed_F * ElapsedTime_F);
			PlayerR_Ptr->GetComponent<Rigidbody>()->SetVelocity(Vector3(PlayerR_Direction_Vec3.x, 0, PlayerR_Direction_Vec3.z)* Speed_F * ElapsedTime_F);

		}

		if (Distance.x * Distance.x + Distance.z * Distance.z > 100) {
			Speed_F = 0.0f;
		}
		else {
			Speed_F += Rig->GetMaxSpeed() / 30;
		}

		//A���b���ꂽ��U���X�e�[�g�Ɉړ�
		if (!(CntlVec[0].wButtons& XINPUT_GAMEPAD_A)) {
			GetStateMachine_Manager()->ChangeState(ToAttractState_Manager::Instance());
		}
	}
	//�����t����
	void PlayerManager::ExecuteToAttractBehavior() {
		auto Rig = GetComponent<Rigidbody>();
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		Vector3 Distance_Vec3 = PlayerL_Pos - PlayerR_Pos;

		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 20;
		Speed_F += Rig->GetMaxSpeed() / 30;
		PlayerL_Direction_Vec3.y = 0;
		PlayerR_Direction_Vec3.y = 0;
		//New_Vec = �i�ޕ����@Speed_F = �ړ��X�s�[�h
		PlayerL_Ptr->GetComponent<Rigidbody>()->SetVelocity(Vector3(PlayerL_Direction_Vec3.x, 0, PlayerL_Direction_Vec3.z)* Speed_F * ElapsedTime_F);
		PlayerR_Ptr->GetComponent<Rigidbody>()->SetVelocity(Vector3(PlayerR_Direction_Vec3.x, 0, PlayerR_Direction_Vec3.z)* Speed_F * ElapsedTime_F);

		StateChangeDoingInterpose();
		if (1.5 > abs(Distance_Vec3.x) && 1.5 > abs(Distance_Vec3.z)) {

			//SE
			auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
			pMultiSoundEffect->Start(L"Collision_01_SE", 0, 0.4f);

			GetStateMachine_Manager()->ChangeState(ReturnState_Manager::Instance());
		}
	}
	//�ŏ��̈ʒu�ɖ߂�
	void PlayerManager::ExecuteReturnBehavior() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlaeyrR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		//�@����鏈��
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 2;
		auto Trans = GetComponent<Transform>();
		auto Rig = GetComponent<Rigidbody>();
		Vector3 Distance_L_Vec3 = PlayerL_SavePos_Vec3 - PlayerL_Pos;
		Vector3 Distance_R_Vec3 = PlayerR_SavePos_Vec3 - PlaeyrR_Pos;

		Speed_F += Rig->GetMaxSpeed() / 3;
		//New_Vec = �i�ޕ����@Speed_F = �ړ��X�s�[�h
		PlayerL_Ptr->GetComponent<Rigidbody>()->SetVelocity(PlayerL_Velocity_Vec3 * Speed_F * ElapsedTime_F);
		PlayerR_Ptr->GetComponent<Rigidbody>()->SetVelocity(PlayerR_Velocity_Vec3 * Speed_F * ElapsedTime_F);

		if (abs(PlayerL_Pos.x) > abs(PlayerL_Initial_Vec3.x) && abs(PlayerL_Pos.z) > abs(PlayerL_Initial_Vec3.z)) {
			//	PlayerL_Ptr->GetComponent<Transform>()->SetPosition(PlayerL_SavePos_Vec3);
			//PlayerR_Ptr->GetComponent<Transform>()->SetPosition(PlayerR_SavePos_Vec3);
			GetStateMachine_Manager()->ChangeState(MoveState_Manager::Instance());
		}
	}
	//����ł���Ƃ�
	void PlayerManager::ExecuteDoingInterpose() {
		InputStick();
		InputRotation();
		PlayerAngle();

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wPressedButtons& XINPUT_GAMEPAD_B) {
			GetStateMachine_Manager()->ChangeState(MoveState_Manager::Instance());
		}

	}
	////////////////////////�I���֐�///////////////////////////////////
	void PlayerManager::ExitGamePrepare() {

	}
	void PlayerManager::ExitMoveBehabior() {
		InitializationVelocity();
	}
	void PlayerManager::ExitLeaveBehavior() {
		//�����Ȃ�
	}
	void PlayerManager::ExitToAttractBehavior() {
		InitializationVelocity();
		Speed_F = 0.0f;
	}
	void PlayerManager::ExitReturnBehavior() {
		InitializationVelocity();
	}
	void PlayerManager::ExitDoingInterpose() {
		InitializationVelocity();
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		if (PtrCollisionSand) {
			PtrCollisionSand->SetActive(false);
		}
		else {
			throw BaseException(
				L"�G���[",
				L"�X�^�[�g�֐��̒��uExitLeaveBehavior�v",
				L"PtrCollisionSand�����݂��Ă��܂���"
			);
		}
	}
	/////////////////////////�X�e�[�g////////////////////////////////
	//�Q�[���J�n�O�̃X�e�[�g
	//--------------------------------------------------------------------------------------
	//	class GamePrepareState_Manager : public ObjState<MoveState_Manager>;
	//	�p�r:�Q�[���J�n�O�̃X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<GamePrepareState_Manager> GamePrepareState_Manager::Instance() {
		static shared_ptr<GamePrepareState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<GamePrepareState_Manager>(new GamePrepareState_Manager);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void GamePrepareState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterGamePrepare();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void GamePrepareState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteGamePrepare();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void GamePrepareState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitGamePrepare();
	}

	//�ړ��X�e�[�g
	//--------------------------------------------------------------------------------------
	//	class MoveState_Manager : public ObjState<MoveState_Manager>;
	//	�p�r:�ړ��X�e�[�g�@
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<MoveState_Manager> MoveState_Manager::Instance() {
		static shared_ptr<MoveState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<MoveState_Manager>(new MoveState_Manager);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void MoveState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterMoveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void MoveState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteMoveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void MoveState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitMoveBehabior();
	}

	//--------------------------------------------------------------------------------------
	//	class LeaveState_Manager : public ObjState<MoveState_Manager>;
	//	�p�r:�����X�e�[�g�@
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<LeaveState_Manager> LeaveState_Manager::Instance() {
		static shared_ptr<LeaveState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<LeaveState_Manager>(new LeaveState_Manager);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void LeaveState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterLeaveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void LeaveState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteLeaveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void LeaveState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitLeaveBehavior();
	}
	//--------------------------------------------------------------------------------------
	//	class ToAttractState_Manager : public ObjState<MoveState_Manager>;
	//	�p�r:���������X�e�[�g�@
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<ToAttractState_Manager> ToAttractState_Manager::Instance() {
		static shared_ptr<ToAttractState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<ToAttractState_Manager>(new ToAttractState_Manager);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void ToAttractState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterToAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ToAttractState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteToAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ToAttractState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitToAttractBehavior();
	}
	//--------------------------------------------------------------------------------------
	//	class ReturnState_Manager : public ObjState<MoveState_Manager>;
	//	�p�r:�߂�X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<ReturnState_Manager> ReturnState_Manager::Instance() {
		static shared_ptr<ReturnState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<ReturnState_Manager>(new ReturnState_Manager);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void ReturnState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterReturnBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ReturnState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteReturnBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ReturnState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitReturnBehavior();
	}
	//--------------------------------------------------------------------------------------
	//	class DoingInterposeState_Manager : public ObjState<MoveState_Manager>;
	//	�p�r:����ł���Ƃ��̃X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<DoingInterposeState_Manager> DoingInterposeState_Manager::Instance() {
		static shared_ptr<DoingInterposeState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<DoingInterposeState_Manager>(new DoingInterposeState_Manager);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void DoingInterposeState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EneterDoingInterpose();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void DoingInterposeState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteDoingInterpose();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void DoingInterposeState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitDoingInterpose();
	}
	//////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------------------
	//	class PlayerHP : public GameObject;
	//	�p�r: �v���C���[HP����
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	PlayerHP::PlayerHP(const shared_ptr<Stage>& StagePtr
	) :
		GameObject(StagePtr)
	{
	}
	PlayerHP::~PlayerHP() {}

	//������
	void PlayerHP::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(0, 0, 0);
		SetInvincible(false);
		SetHit(false);
	}
	void PlayerHP::OnUpdate() {
		if (!GetInvincible() && GetHit()) {
			GetStage()->GetSharedGameObject<Player_Life>(L"Life")->LifeDown(GetDamage_int());
			SetInvincible(true);

			if (GetDamage_int() > 0) {
				SetDamage_int(0);
			}
		}
		else if (GetInvincible()) {
			float ElapsedTime_F = App::GetApp()->GetElapsedTime();
			InvinciblecCunt += ElapsedTime_F;
			if (InvinciblecCunt > InvinciblecLimit) {
				SetInvincible(false);
				SetHit(false);
				InvinciblecCunt = 0.0f;
			}
		}
	}
}


