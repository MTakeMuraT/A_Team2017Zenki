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
	Player::Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{}
	//������
	void Player::OnCreate() {

		m_Collision_Sphere = GetStage()->AddGameObject<Collision_Sphere>();

		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(1.0f, 1.0f, 1.0f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		//auto PtrCol = AddComponent<CollisionSphere>();

		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"TRACE_TX");

		//��������
		SetAlphaActive(true);

		m_StatePlayerMachine = make_shared<StateMachine<Player> >(GetThis<Player>());
		m_StatePlayerMachine->ChangeState(MoveState::Instance());
	}
	void Player::OnUpdate() {

		m_StatePlayerMachine->Update();
		//InputRotation();
		//Rot();


		//�R���g���[���擾
		/*	auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wButtons& XINPUT_GAMEPAD_A && GetStanEnemy() == false) {
		StanTime_F += 0.1f;
		}
		else {
		StanTime_F = 0.0f;S
		}

		if (m_Collision_Sphere->GetStayCollisionFlg() && GetStanEnemy() == false) {
		if (dynamic_pointer_cast<Enemy01>(m_HitObject)) {
		dynamic_pointer_cast<Enemy01>(m_HitObject)->Damage(StanTime_F);
		TotalEnemyStanTime = StanTime_F * 2;
		SetStanEnemy(true);
		}


		}

		else if (TotalEnemyStanTime <= 0.0f  || !(CntlVec[0].wButtons& XINPUT_GAMEPAD_A) || !(dynamic_pointer_cast<Enemy01>(m_HitObject)->GetStanFlg()) ) {
		auto PtrEnemy01 = GetStage()->GetSharedGameObject<Enemy01>(L"Enemy01", false);
		SetStanEnemy(false);
		TotalEnemyStanTime = 0.0f;
		PtrEnemy01->Release();
		}
		else {
		TotalEnemyStanTime += -App::GetApp()->GetElapsedTime();
		}*/

	}
	void Player::OnLastUpdate() {
		//������\��
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\n";

		wstring VelocityPowerStr(L"VelocityPower:");
		VelocityPowerStr += Util::FloatToWStr(VelocityPower);
		VelocityPowerStr += L"\n";

		wstring STAN(L"\nStanTime");
		STAN += Util::FloatToWStr(StanTime_F);
		STAN += L"\n";

		wstring Total(L"\n�X�s�[�h:");
		Total += Util::FloatToWStr(Speed_F);
		Total += L"\n";

		wstring RotetoSpeedStr(L"��]�X�s�[�h:");
		RotetoSpeedStr += Util::FloatToWStr(RotSpeedSecond);
		RotetoSpeedStr += L"\n";

		wstring angle_RotetionStr(L"��]:");
		angle_RotetionStr += Util::FloatToWStr(Debug_Rot_F);
		angle_RotetionStr += L"\n";

		wstring DebugDirectionStr(L"����:");
		DebugDirectionStr += Util::FloatToWStr(DebugDirection);
		DebugDirectionStr += L"\n";

		wstring Debug2Str(L"����̈ʒu:\t");
		Debug2Str += L"X=" + Util::FloatToWStr(DeBug2_Vec3.x, 6, Util::FloatModify::Fixed) + L",\t";
		Debug2Str += L"Y=" + Util::FloatToWStr(DeBug2_Vec3.y, 6, Util::FloatModify::Fixed) + L",\t";
		Debug2Str += L"Z=" + Util::FloatToWStr(DeBug2_Vec3.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring DebugStr(L"���~�b�g:\t");
		DebugStr += L"X=" + Util::FloatToWStr(Dubug_Vec3.x, 6, Util::FloatModify::Fixed) + L",\t";
		DebugStr += L"Y=" + Util::FloatToWStr(Dubug_Vec3.y, 6, Util::FloatModify::Fixed) + L",\t";
		DebugStr += L"Z=" + Util::FloatToWStr(Dubug_Vec3.z, 6, Util::FloatModify::Fixed) + L"\n";

		auto Pos = GetComponent<Transform>()->GetWorldMatrix().PosInMatrix();
		wstring PositionStr(L"�����̈ʒu:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		auto Velo = GetComponent<Rigidbody>()->GetVelocity();
		wstring DeBug3_Vec3str(L"����;");
		DeBug3_Vec3str += L"X=" + Util::FloatToWStr(DeBug3_Vec3.x, 6, Util::FloatModify::Fixed) + L",\t";
		DeBug3_Vec3str += L"Y=" + Util::FloatToWStr(DeBug3_Vec3.y, 6, Util::FloatModify::Fixed) + L",\t";
		DeBug3_Vec3str += L"Z=" + Util::FloatToWStr(DeBug3_Vec3.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring m_FixedPos_b(L"�ʒu�Œ�t���O:\t");
		if (FixedPos_b) {
			m_FixedPos_b += L"true\n";
		}
		else {
			m_FixedPos_b += L"false\n";
		}



		wstring m_Debug_StickDown_b(L"����ł��鎞�̈ړ�Flg:");
		if (Debug_StickDown_b) {
			m_Debug_StickDown_b += L"true";
		}
		else {
			m_Debug_StickDown_b += L"false";
		}

		//�X�e�[�g
		wstring State(L"�X�e�[�g��ԁF");
		if (m_StatePlayerMachine->GetCurrentState() == MoveState::Instance()) {

			State += L"�ړ�";
			State += L"\n";
		}
		else if (m_StatePlayerMachine->GetCurrentState() == ToAttractState::Instance()) {

			State += L"�����񂹂���";
			State += L"\n";
		}
		else if (m_StatePlayerMachine->GetCurrentState() == LeaveState::Instance()) {
			State += L"�����";
			State += L"\n";
		}
		/*else if (m_StatePlayerMachine->GetCurrentState() == PinchState::Instance()) {

		State += L"����ł���X�e�[�g";
		State += L"\n";
		}*/
		else {
			State += L"�Y���Ȃ�";
			State += L"\n";
		}


		wstring ObjStr(L"\nPosition:\t");
		if (m_HitObject != NULL) {
			auto Obj = m_HitObject->GetComponent<Transform>()->GetPosition();

			ObjStr += L"X=" + Util::FloatToWStr(Obj.x, 6, Util::FloatModify::Fixed) + L",\t";
			ObjStr += L"Y=" + Util::FloatToWStr(Obj.y, 6, Util::FloatModify::Fixed) + L",\t";
			ObjStr += L"Z=" + Util::FloatToWStr(Obj.z, 6, Util::FloatModify::Fixed) + L"\n";
		}

		wstring Col(L"\n�R���W����HIT\n");
		if (m_Collision_Sphere->GetStayCollisionFlg()) {
			Col += L"true";
		}
		else {
			Col += L"flase";
		}

		Col += L"\n";

		wstring  str = /*FPS  + m_FixedPos_b + m_Debug_StickDown_b + Col +*/ Col + State + STAN + Total + RotetoSpeedStr + angle_RotetionStr + DebugStr + Debug2Str + PositionStr + DebugDirectionStr + DeBug3_Vec3str;
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}

	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		for (auto A : OtherVec) {
			if (CntlVec[0].wButtons& XINPUT_GAMEPAD_A) {
				auto Fixd_Box = dynamic_pointer_cast<FixdBox>(A);
				if (Fixd_Box) {
					m_HitObject = A;
					//����
					//GetStateMachine()->ChangeState(PinchState::Instance());

					//�G�l�~�[�̃t���O��ς���
				}
				//Abe 20170412 14:56
				auto Enemy_01 = dynamic_pointer_cast<Enemy01>(A);
				if (Enemy_01) {
					//Enemy_01->Damage(StanTime_F);
					m_HitObject = A;
					//����
					//	GetStateMachine()->ChangeState(PinchState::Instance());

					//�G�l�~�[�̃t���O��ς���
				}
				//Abe 20170412 14:56
				auto Player2 = dynamic_pointer_cast<Player_Second>(A);
				if (Player2) {
					GetStateMachine()->ChangeState(LeaveState::Instance());
				}
			}
		}
	}



	//�X�e�B�b�N����
	void Player::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		if (m_StatePlayerMachine->GetCurrentState() == MoveState::Instance()) {
			Speed_F = Rig->GetMaxSpeed() / 5.0f;
		}
		else {
			Speed_F = Rig->GetMaxSpeed() / 5.0f;
		}
		Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		Rig->SetVelocity(Vec_Vec3 * Speed_F);

	}



	////////////////////////�X�e�[�g�X�^�[�g�֐�///////////////////////////////////
	//�ړ�
	void Player::EnterMoveBehavior() {
		m_sandwich = false;
	}
	//����
	void Player::EnterToAttractBehavior() {
		auto Trans = GetComponent<Transform>();
		//�����̈ʒu
		My_Pos_Vec3 = Trans->GetPosition();
		//������̃v���C���[�̈ʒu
		Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
		//�i�ތ���
		New_Vec = Move_Velo(My_Pos_Vec3, Partner_Pos_Vec3);

	}

	//�����
	void Player::EnterLeaveBehavior() {
		auto Trans = GetComponent<Transform>();
		My_Pos_Vec3 = Trans->GetPosition();
		New_Vec = Move_Velo(My_Pos_Vec3, SavePos_Vec3);
		//�����Ȃ�

	}
	//���ޑO�@�i�U���O�j
	void Player::EnterBeforeAttractBehavior() {
		auto Trans = GetComponent<Transform>();
		//�����ʒu�̕ۑ�
		SavePos_Vec3 = Trans->GetPosition();
		DeBug3_Vec3 = SavePos_Vec3;
		////������̃v���C���[�̈ʒu
		Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
		My_Pos_Vec3 = Trans->GetPosition();
		New_Vec = Direction(My_Pos_Vec3, Partner_Pos_Vec3);
	}
	////////////////////////�X�e�[�g�p���֐�///////////////////////////////////////
	//�X�e�[�g�}�V�[���Ŏg���֐�
	void Player::ExecuteMoveBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		InputRotation();
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//�X�e�[�g�ړ�
			GetStateMachine()->ChangeState(BeforeAttractState::Instance());
		}
	}

	//�����񂹍����X�e�[�g 
	void Player::ExecuteToAttractBehavior() {

		auto Trans = GetComponent<Transform>();
		auto Rig = GetComponent<Rigidbody>();
		auto Player2Pos = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
		Vector3 Distance_Vec3 = Player2Pos - Trans->GetPosition();


		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 20;
		Speed_F += Rig->GetMaxSpeed() / 30;
		//New_Vec = �i�ޕ����@Speed_F = �ړ��X�s�[�h
		Rig->SetVelocity(New_Vec * Speed_F * ElapsedTime_F);

		if (1.5 > abs(Distance_Vec3.x) && 1.5 > abs(Distance_Vec3.z)) {
			GetStateMachine()->ChangeState(LeaveState::Instance());
		}
	}

	//�����
	void Player::ExecuteLeaveBehavior() {
		//�@����鏈��
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 2;
		auto Trans = GetComponent<Transform>();
		auto Rig = GetComponent<Rigidbody>();
		Vector3 Distance_Vec3 = SavePos_Vec3 - Trans->GetPosition();


		Speed_F += Rig->GetMaxSpeed() / 3;
		//New_Vec = �i�ޕ����@Speed_F = �ړ��X�s�[�h
		Rig->SetVelocity(New_Vec * Speed_F * ElapsedTime_F);


		if (1.1 > abs(Distance_Vec3.x) && 1.1 > abs(Distance_Vec3.z)) {
			Trans->SetPosition(SavePos_Vec3);

			GetStateMachine()->ChangeState(MoveState::Instance());
		}
	}

	//�U���O�@�i�U�������j
	void Player::ExecuteBeforeAttractBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();

		auto PtrPlayer2 = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false);
		auto Player2Pos = PtrPlayer2->GetComponent<Transform>()->GetPosition();
		auto D = Vector3(Pos.x - Player2Pos.x, Pos.y - Player2Pos.y, Pos.z - Player2Pos.z);

		//�@����鏈��
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 10;
		auto Rig = GetComponent<Rigidbody>();

		//New_Vec = �i�ޕ����@Speed_F = �ړ��X�s�[�h
		Rig->SetVelocity(New_Vec * Speed_F * ElapsedTime_F);


		if (D.x*D.x + D.z + D.z > 1000) {
			Speed_F = 0.0f;
		}
		else {
			Speed_F += Rig->GetMaxSpeed() / 30;
		}

		//A��������Ă���@�����̌��ɉ�����


		//A���b���ꂽ��U���X�e�[�g�Ɉړ�
		if (!(CntlVec[0].wButtons& XINPUT_GAMEPAD_A)) {
			GetStateMachine()->ChangeState(ToAttractState::Instance());
		}
	}
	/////////////////////////�X�e�[�g�I���֐�/////////////////////////////////////////
	void Player::ExitMoveBehabior() {
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0, 0, 0);
	}
	void Player::ExitToAttractBehavior() {
		//������
		auto Rig = GetComponent<Rigidbody>();
		//������
		Rig->SetVelocity(0, 0, 0);
		Speed_F = 0.0f;
	}
	//�����
	void Player::ExitLeaveBehavior() {
		//������
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0, 0, 0);
		Speed_F = 0.0f;
	}
	//�U���O�@�i�U�������j
	void Player::ExitBeforeAttractBehavior() {

	}
	/////////////////////////////�֐��Q////////////////////////////////
	//���������Ƃ��Ɏg�p
	Vector3 Player::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 = PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
	}
	//�����Ƃ��Ɏg�p
	Vector3 Player::Direction(Vector3 MyPos, Vector3 PartnerPos) {
		Direction_Vec3 = MyPos - PartnerPos;
		Direction_Vec3.Normalize();
		return Direction_Vec3;
	}
	void Player::InputRotation() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PtrPlayerR = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false);
		CentrPos = PtrPlayerR->GetComponent<Transform>()->GetPosition();
		DeBug2_Vec3 = CentrPos;
		CentrPos = (GetComponent<Transform>()->GetPosition() + CentrPos) / 2;
		//�܂����S����݂��p�x�����߂�
		def = GetComponent<Transform>()->GetPosition() - CentrPos;
		//Dubug_Vec3 = def;
		angle = atan2(def.z, def.x) * 180 / XM_PI;
		if (Debug_flg) {
			Debug_Rot_F = angle;
			Debug_flg = false;
		}
		angle += 360;
		angle_int = (int)angle % 360;


		//
		if (CntlVec[0].wButtons& XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			angle_int += -RotSpeedSecond *  App::GetApp()->GetElapsedTime();
			Debug_flg = true;
		}
		//
		else if (CntlVec[0].wButtons& XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			angle_int += RotSpeedSecond *  App::GetApp()->GetElapsedTime();
			Debug_flg = true;
		}
		angle_int %= 360;
		DebugDirection = angle_int;
		//��������ړ��ʂ����߂�
		//���W�A���ϊ�
		angle = angle_int *  XM_PI / 180;
		//�����Z�o
		float direction = sqrt((def.x * def.x) + (def.z * def.z));

		MovePosVec3 = CentrPos + Vector3(cos(angle) * direction, 0, sin(angle) * direction);
		//DeBug3_Vec3 = MovePosVec3;
		GetComponent<Transform>()->SetPosition(MovePosVec3);
	}


	//�ʒu�Œ�
	void Player::FixedPos() {
		if (FixedPos_b) {
			Now_Pos_Vec3 = GetComponent<Transform>()->GetPosition();
			GetComponent<Transform>()->SetPosition(Now_Pos_Vec3);
			GetComponent<Rigidbody>()->SetVelocity(0, 0, 0);
		}
		FixedPos_b = false;

	}
	//��]
	void Player::Rot() {
		auto PlayerCenterPtr = GetStage()->GetSharedGameObject<PlayerCenter>(L"PlayerCenter");
		auto PlayerCenterPos = PlayerCenterPtr->GetComponent<Transform>()->GetPosition();
		auto PlayerCenterRot = PlayerCenterPtr->GetComponent<Transform>()->GetRotation();
		float RotY = PlayerCenterRot.y;
		RotY -= XM_PIDIV2;
		auto Pos = Vector3(sin(RotY), 0, cos(RotY));
		Pos += PlayerCenterPos;
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(1.0f, 1.0f, 1.0f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(Pos);
	}


	//�ړ��X�e�[�g
	//--------------------------------------------------------------------------------------
	//	class MoveState : public ObjState<Player>;
	//	�p�r:�ړ��X�e�[�g�@
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<MoveState> MoveState::Instance() {
		static shared_ptr<MoveState> instance;
		if (!instance) {
			instance = shared_ptr<MoveState>(new MoveState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void MoveState::Enter(const shared_ptr<Player>& Obj) {
		Obj->EnterMoveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void MoveState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExecuteMoveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void MoveState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitMoveBehabior();
	}

	//�ړ��X�e�[�g
	//--------------------------------------------------------------------------------------
	//	class ToAttractState : public ObjState<Player>;
	//	�p�r:�����񂹍���
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<ToAttractState> ToAttractState::Instance() {
		static shared_ptr<ToAttractState> instance;
		if (!instance) {
			instance = shared_ptr<ToAttractState>(new ToAttractState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void ToAttractState::Enter(const shared_ptr<Player>& Obj) {
		Obj->EnterToAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ToAttractState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExecuteToAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ToAttractState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitToAttractBehavior();
	}

	//--------------------------------------------------------------------------------------
	//	class LeaveState : public ObjState<Player>;
	//	�p�r:�����X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<LeaveState> LeaveState::Instance() {
		static shared_ptr<LeaveState> instance;
		if (!instance) {
			instance = shared_ptr<LeaveState>(new LeaveState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void LeaveState::Enter(const shared_ptr<Player>& Obj) {
		Obj->EnterLeaveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void LeaveState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExecuteLeaveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void LeaveState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitLeaveBehavior();
	}

	//--------------------------------------------------------------------------------------
	//	class BeforeAttractState : public ObjState<Player>;
	//	�p�r:�U���O�X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<BeforeAttractState> BeforeAttractState::Instance() {
		static shared_ptr<BeforeAttractState> instance;
		if (!instance) {
			instance = shared_ptr<BeforeAttractState>(new BeforeAttractState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void BeforeAttractState::Enter(const shared_ptr<Player>& Obj) {
		Obj->EnterBeforeAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void BeforeAttractState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExecuteBeforeAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void BeforeAttractState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitBeforeAttractBehavior();
	}

	////////////////////////////������̂̃v���C���[////////////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------------------
	//	class Player_Second : public Player;
	//	�p�r: �v���C���[2
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Player_Second::Player_Second(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{}
	//������
	void Player_Second::OnCreate() {

		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(1.0f, 1.0f, 1.0f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		//	auto PtrCol = AddComponent<CollisionSphere>();


		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"TRACE_TX");

		//��������
		SetAlphaActive(true);

		m_StatePlayer_SecondMachine = make_shared<StateMachine<Player_Second> >(GetThis<Player_Second>());
		m_StatePlayer_SecondMachine->ChangeState(MoveState_Second::Instance());
	}
	void Player_Second::OnUpdate() {
		m_StatePlayer_SecondMachine->Update();
		//InputRotation();
		// Rot();
	}
	void Player_Second::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto A : OtherVec) {
			auto Fixd_Box = dynamic_pointer_cast<FixdBox>(A);
			if (Fixd_Box) {
				//����
				//GetStateSecondMachine()->ChangeState(PinchState_Second::Instance());
			}
		}
	}


	//�X�e�B�b�N����
	void Player_Second::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		if (m_StatePlayer_SecondMachine->GetCurrentState() == MoveState_Second::Instance()) {
			Speed_F = Rig->GetMaxSpeed() / 5.0f;
			Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		}
		/*else if(m_StatePlayer_SecondMachine->GetCurrentState() == SandwichState_Second::Instance()){
		Speed_F = 3.0f;
		Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		}*/

		Rig->SetVelocity(Vec_Vec3 * Speed_F);

	}

	void Player_Second::InputRotation() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PtrPlayer = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false);
		CentrPos = PtrPlayer->GetComponent<Transform>()->GetPosition();
		CentrPos = (GetComponent<Transform>()->GetPosition() + CentrPos) / 2;
		//�܂����S����݂��p�x�����߂�
		def = GetComponent<Transform>()->GetPosition() - CentrPos;
		angle = atan2(def.z, def.x) * 180 / XM_PI;
		angle += 360;
		angle_int = (int)angle % 360;

		//
		if (CntlVec[0].wButtons& XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			angle_int += -RotSpeedSecond *  App::GetApp()->GetElapsedTime();
		}
		//
		else if (CntlVec[0].wButtons& XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			angle_int += RotSpeedSecond *  App::GetApp()->GetElapsedTime();
		}
		angle_int %= 360;
		//��������ړ��ʂ����߂�
		//���W�A���ϊ�
		angle = angle_int *  XM_PI / 180;

		//�����Z�o
		float direction = sqrt((def.x * def.x) + (def.z * def.z));
		MovePosVec3 = CentrPos + Vector3(cos(angle) * direction, 0, sin(angle) * direction);
		GetComponent<Transform>()->SetPosition(MovePosVec3);
	}


	////////////////////////�X�e�[�g�X�^�[�g�֐�///////////////////////////////////
	//����
	void Player_Second::EnterToAttractBehavior() {
		auto Trans = GetComponent<Transform>();
		//�����̈ʒu
		My_Pos_Vec3 = Trans->GetPosition();
		//������̃v���C���[�̈ʒu
		Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false)->GetComponent<Transform>()->GetPosition();
		New_Vec = Move_Velo(My_Pos_Vec3, Partner_Pos_Vec3);
		//�����ʒu�̕ۑ�
		//SavePos_Vec3 = GetComponent<Transform>()->GetPosition();

	}

	//�����
	void Player_Second::EnterLeaveBehavior() {
		auto Trans = GetComponent<Transform>();
		My_Pos_Vec3 = Trans->GetPosition();
		New_Vec = Move_Velo(My_Pos_Vec3, SavePos_Vec3);

	}
	//���ޑO�@�i�U���O�j
	void Player_Second::EnterBeforeAttractBehavior() {
		auto Trans = GetComponent<Transform>();
		//�����ʒu�̕ۑ�
		SavePos_Vec3 = Trans->GetPosition();
		////������̃v���C���[�̈ʒu
		Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false)->GetComponent<Transform>()->GetPosition();
		My_Pos_Vec3 = Trans->GetPosition();
		New_Vec = Direction(My_Pos_Vec3, Partner_Pos_Vec3);
	}
	////////////////////////�X�e�[�g�p���֐�///////////////////////////////////////
	//�X�e�[�g�}�V�[���Ŏg���֐�
	void Player_Second::ExecuteMoveBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		InputRotation();
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//�X�e�[�g�ړ�
			GetStateSecondMachine()->ChangeState(BeforeAttractState_Second::Instance());

		}
	}
	//���ރX�e�[�g
	void Player_Second::ExecuteToAttractBehavior() {
		auto PlayerL = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false);
		auto PlayerLPos = PlayerL->GetComponent<Transform>()->GetPosition();
		Vector3 Distance_Vec3 = PlayerLPos - GetComponent<Transform>()->GetPosition();
		auto Rig = GetComponent<Rigidbody>();
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 20;
		Speed_F += Rig->GetMaxSpeed() / 30;
		Rig->SetVelocity(Vector3(New_Vec * ElapsedTime_F * Speed_F));


		if (1.0 > abs(Distance_Vec3.x) && 1.0 > abs(Distance_Vec3.z)) {
			GetStateSecondMachine()->ChangeState(LeaveState_Second::Instance());
		}


	}
	//�����
	void Player_Second::ExecuteLeaveBehavior() {
		//�@����鏈��
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 2;
		auto Trans = GetComponent<Transform>();
		auto Rig = GetComponent<Rigidbody>();
		Vector3 Distance_Vec3 = SavePos_Vec3 - Trans->GetPosition();


		Speed_F += Rig->GetMaxSpeed() / 3;
		//New_Vec = �i�ޕ����@Speed_F = �ړ��X�s�[�h
		Rig->SetVelocity(New_Vec * Speed_F * ElapsedTime_F);


		if (1.1 > abs(Distance_Vec3.x) && 1.1 > abs(Distance_Vec3.z)) {
			Trans->SetPosition(SavePos_Vec3);

			GetStateSecondMachine()->ChangeState(MoveState_Second::Instance());
		}
	}
	//�U���O�@�i�U�������j
	void Player_Second::ExecuteBeforeAttractBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();

		auto PtrPlayer2 = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false);
		auto Player2Pos = PtrPlayer2->GetComponent<Transform>()->GetPosition();
		auto D = Vector3(Pos.x - Player2Pos.x, Pos.y - Player2Pos.y, Pos.z - Player2Pos.z);

		//�@����鏈��
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 10;
		auto Rig = GetComponent<Rigidbody>();
		//New_Vec = �i�ޕ����@Speed_F = �ړ��X�s�[�h
		Rig->SetVelocity(New_Vec * Speed_F * ElapsedTime_F);
		if (D.x*D.x + D.z + D.z > 1000) {
			Speed_F = 0.0f;
		}
		else {
			Speed_F += Rig->GetMaxSpeed() / 30;
		}

		//A���b���ꂽ��U���X�e�[�g�Ɉړ�
		if (!(CntlVec[0].wButtons& XINPUT_GAMEPAD_A)) {
			GetStateSecondMachine()->ChangeState(ToAttractState_Second::Instance());
		}
	}




	/////////////////////////�X�e�[�g�I���֐�/////////////////////////////////////////
	void Player_Second::ExitMoveBehabior() {
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0, 0, 0);
	}
	void Player_Second::ExitToAttractBehavior() {
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0, 0, 0);

	}
	void Player_Second::ExitLeaveBehavior() {

	}
	//�U���O�@�i�U�������j
	void Player_Second::ExitBeforeAttractBehavior() {

	}

	//�ʒu�Œ�
	void Player_Second::FixedPos() {
		if (FixedPos_b) {
			Now_Pos_Vec3 = GetComponent<Transform>()->GetPosition();
			GetComponent<Transform>()->SetPosition(Now_Pos_Vec3);
			GetComponent<Rigidbody>()->SetVelocity(0, 0, 0);
		}
		FixedPos_b = false;
	}



	//���������Ƃ��Ɏg�p
	Vector3 Player_Second::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 = PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
	}
	//����鎞�Ɏg�p
	Vector3 Player_Second::Direction(Vector3 MyPos, Vector3 PartnerPos) {
		Direction_Vec3 = MyPos - PartnerPos;
		Direction_Vec3.Normalize();
		return Direction_Vec3;
	}

	//��]
	void Player_Second::Rot() {
		auto PlayerCenterPtr = GetStage()->GetSharedGameObject<PlayerCenter>(L"PlayerCenter");
		auto PlayerCenterPos = PlayerCenterPtr->GetComponent<Transform>()->GetPosition();
		auto PlayerCenterRot = PlayerCenterPtr->GetComponent<Transform>()->GetRotation();
		float RotY = PlayerCenterRot.y;
		RotY += XM_PIDIV2;
		auto Pos = Vector3(sin(RotY), 0, cos(RotY));
		Pos += PlayerCenterPos;
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(1.0f, 1.0f, 1.0f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(Pos);
	}
	////�ړ��X�e�[�g
	////--------------------------------------------------------------------------------------
	////	class MoveState_Second : public ObjState<Player_Second>;
	////	�p�r:�ړ��X�e�[�g�@
	////--------------------------------------------------------------------------------------
	////�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<MoveState_Second> MoveState_Second::Instance() {
		static shared_ptr<MoveState_Second> instance;
		if (!instance) {
			instance = shared_ptr<MoveState_Second>(new MoveState_Second);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void MoveState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void MoveState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExecuteMoveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void MoveState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitMoveBehabior();
	}

	////�ړ��X�e�[�g
	////--------------------------------------------------------------------------------------
	////	class ToAttractState_Second : public ObjState<Player_Second>;
	////	�p�r:�����񂹍���
	////--------------------------------------------------------------------------------------
	////�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<ToAttractState_Second> ToAttractState_Second::Instance() {
		static shared_ptr<ToAttractState_Second> instance;
		if (!instance) {
			instance = shared_ptr<ToAttractState_Second>(new ToAttractState_Second);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void ToAttractState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
		Obj->EnterToAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ToAttractState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExecuteToAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ToAttractState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitToAttractBehavior();
	}

	//--------------------------------------------------------------------------------------
	//	class LeaveState_Second : public ObjState<Player_Second>;
	//	�p�r:�����X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<LeaveState_Second> LeaveState_Second::Instance() {
		static shared_ptr<LeaveState_Second> instance;
		if (!instance) {
			instance = shared_ptr<LeaveState_Second>(new LeaveState_Second);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void LeaveState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
		Obj->EnterLeaveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void LeaveState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExecuteLeaveBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void LeaveState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitLeaveBehavior();
	}

	//--------------------------------------------------------------------------------------
	//	class BeforeAttractState_Second : public ObjState<Player_Second>;
	//	�p�r:�U�������O�X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<BeforeAttractState_Second> BeforeAttractState_Second::Instance() {
		static shared_ptr<BeforeAttractState_Second> instance;
		if (!instance) {
			instance = shared_ptr<BeforeAttractState_Second>(new BeforeAttractState_Second);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void BeforeAttractState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
		Obj->EnterBeforeAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void BeforeAttractState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExecuteBeforeAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void BeforeAttractState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitBeforeAttractBehavior();
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
		/*
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"TRACE_TX");
		//��������
		SetAlphaActive(true);
		*/


	}

	void PlayerCenter::OnUpdate() {
		auto Ptr = GetComponent<Transform>();
		auto Qt = Ptr->GetQuaternion();
		float ElapsedTime = App::GetApp()->GetElapsedTime();


		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
				Quaternion SpanQt(Vector3(0, 1, 0), -ElapsedTime * 2.0f);
				Qt *= SpanQt;
				Ptr->SetQuaternion(Qt);
			}
			else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				Quaternion SpanQt(Vector3(0, 1, 0), ElapsedTime * 2.0f);
				Qt *= SpanQt;
				Ptr->SetQuaternion(Qt);
			}
		}



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
}

//end basecross

