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
		auto PtrCol = AddComponent<CollisionSphere>();
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

		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wButtons& XINPUT_GAMEPAD_A && GetStanEnemy() == false) {
			StanTime_F += 0.1f;
		}
		else {
			StanTime_F = 0.0f;
		}

		if (m_Collision_Sphere->GetStayCollisionFlg() && GetStanEnemy() == false) {
			auto PtrEnemy01 = GetStage()->GetSharedGameObject<Enemy01>(L"Enemy01", false);
			PtrEnemy01->Damage(StanTime_F);
			TotalEnemyStanTime = StanTime_F * 3;
			SetStanEnemy(true);
		}

		else if (TotalEnemyStanTime <= 0.0f  || !(CntlVec[0].wButtons& XINPUT_GAMEPAD_A)) {
			auto PtrEnemy01 = GetStage()->GetSharedGameObject<Enemy01>(L"Enemy01", false);
			SetStanEnemy(false);
			TotalEnemyStanTime = 0.0f;
			PtrEnemy01->Release();
		}
		else {
			TotalEnemyStanTime += -App::GetApp()->GetElapsedTime();
		}
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
		
		wstring Total(L"\n�g�[�^���X�^���^�C��:");
		Total += Util::FloatToWStr(TotalEnemyStanTime);
		Total += L"\n";

		auto Pos = GetComponent<Transform>()->GetWorldMatrix().PosInMatrix();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

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
		else if (m_StatePlayerMachine->GetCurrentState() == PinchState::Instance()) {

			State += L"����ł���X�e�[�g";
			State += L"\n";
		}
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

		wstring  str = /*FPS + State + m_FixedPos_b + m_Debug_StickDown_b + Col +*/ STAN + Total;
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}

	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		for (auto A : OtherVec) {
			if (CntlVec[0].wButtons& XINPUT_GAMEPAD_A) {
				auto Fixd_Box = dynamic_pointer_cast<FixdBox>(A);
				if (Fixd_Box) {
					m_HitObject = dynamic_pointer_cast<GameObject>(A);
					//����
					GetStateMachine()->ChangeState(PinchState::Instance());
					
					//�G�l�~�[�̃t���O��ς���
				}
				//Abe 20170412 14:56
				auto Enemy_01 = dynamic_pointer_cast<Enemy01>(A);
				if (Enemy_01) {
					//Enemy_01->Damage(StanTime_F);
					m_HitObject = dynamic_pointer_cast<GameObject>(A);
					//����
					GetStateMachine()->ChangeState(PinchState::Instance());
					
					//�G�l�~�[�̃t���O��ς���
				}
				//Abe 20170412 14:56
			}
		}
	}
	
	
	
	//�X�e�B�b�N����
	void Player::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		if (m_StatePlayerMachine->GetCurrentState() == MoveState::Instance()) {
			Speed_F = 100.0f;
		}
		else {
			Speed_F = 3.0f;
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
		//A�{�^����������Ă邩�H
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
		//	KeepPushed_A = true;
			
		}
	}
	//����ł��鎞
	void Player::EnterPinchBehavior() {
		if (FixedPos_b == false) {
			FixedPos_b = true;
		}
	}
	//����ňړ��̎�
	void Player::EnterSandwichBehavior() {
		//�����Ȃ�
	};

	////////////////////////�X�e�[�g�p���֐�///////////////////////////////////////
	//�X�e�[�g�}�V�[���Ŏg���֐�
	void Player::ExecuteMoveBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//�X�e�[�g�ړ�
			GetStateMachine()->ChangeState(ToAttractState::Instance());
		}
	}

	//�����񂹍����X�e�[�g
	void Player::ExecuteToAttractBehavior() {
		if (KeepPushed_A == true) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			auto Trans = GetComponent<Transform>();
			auto Rig = GetComponent<Rigidbody>();
			float ElapsedTime_F = App::GetApp()->GetElapsedTime();
			if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
				//�����̈ʒu
				My_Pos_Vec3 = Trans->GetPosition();
				//������̃v���C���[�̈ʒu
				Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
				New_Vec = Move_Velo(My_Pos_Vec3, Partner_Pos_Vec3);
				Rig->SetVelocity(Vector3(New_Vec * ElapsedTime_F * Speed_F * VelocityPower));
				
			}
			else
			{
				VelocityPower = 1.0f;
				GetStateMachine()->ChangeState(MoveState::Instance());
			}
			VelocityPower += AddVec;
		}

	}

	//����ł���Ƃ�
	void Player::ExecutePinchBehavior() {
		//����
		auto Player_L_Trans = GetComponent<Transform>();
		Vector3 Player_L_Pos_Vec3 = Player_L_Trans->GetPosition();
		//PlayerL/R�͑傫��������
		Vector3 Player_Scale = Player_L_Trans->GetScale();

		//�������
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Player_R_Ptr = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false);
		auto Player_R_Trans = Player_R_Ptr->GetComponent<Transform>();
		Vector3 Player_R_Pos_Vec3 = Player_R_Trans->GetPosition();
		//�Ώۂ̃I�u�W�F�N�g
		auto HitObj_Trans = m_HitObject->GetComponent<Transform>();
		Vector3 HitObj_Pos_Vec3 = HitObj_Trans->GetPosition();
		Vector3 HitObj_Scale = HitObj_Trans->GetScale();
		//����ł��镨�̈ʒu�A�����̈ʒu�A������̂̈ʒu�A����ł��镨�̑傫���A�����̑傫��
		m_Collision_Sphere->CollisionTest(HitObj_Pos_Vec3, Player_L_Pos_Vec3,Player_R_Pos_Vec3, HitObj_Scale, Player_Scale);

		//A��������Ă����炻�̏ꏊ�̈ʒu���Œ肳����
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			FixedPos();
		}
		else {
			GetStateMachine()->ChangeState(MoveState::Instance());
		}
		//�R���g���[����L�X�e�B�b�N�̓��͂�����΋���ňړ��X�e�[�g�Ɉړ�
		if (m_Collision_Sphere->GetStayCollisionFlg() && CntlVec[0].fThumbLX || CntlVec[0].fThumbLY) {
			Debug_StickDown_b = true;
			m_sandwich = true;
			GetStateMachine()->ChangeState(SandwichState::Instance());
		}
		else {
			Debug_StickDown_b = false;
		}
	}

	//����ňړ�
	void Player::ExecuteSandwichBehavior() {
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//�����ړ�
		if (CntlVec[0].wButtons& XINPUT_GAMEPAD_A) {
			InputStick();
		}
		else {
			GetStateMachine()->ChangeState(MoveState::Instance());
		}
	}

	/////////////////////////�X�e�[�g�I���֐�/////////////////////////////////////////
	void Player::ExitMoveBehabior() {
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0,0,0);
	}
	void Player::ExitToAttractBehavior() {
		//�����Ȃ�
	}
	//����ł���Ƃ�
	void Player::ExitPinchBehavior() {
		FixedPos_b = false;
		m_Collision_Sphere->ResetFlg();
		
	}
	//����ňړ��Ƃ�
	void Player::ExitSandwichBehavior() {
	}

	/////////////////////////////�֐��Q////////////////////////////////
	Vector3 Player::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 = PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
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
	//����ł���X�e�[�g
	//--------------------------------------------------------------------------------------
	//	class PinchState : public ObjState<Player>;
	//	�p�r:����ł���X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<PinchState> PinchState::Instance() {
		static shared_ptr<PinchState> instance;
		if (!instance) {
			instance = shared_ptr<PinchState>(new PinchState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void PinchState::Enter(const shared_ptr<Player>& Obj) {
		Obj->EnterPinchBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void PinchState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExecutePinchBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void PinchState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitPinchBehavior();
	}

	//����ł��ǂ����Ă�X�e�[�g
	//--------------------------------------------------------------------------------------
	//	class SandwichState : public ObjState<Player>;
	//	�p�r:����ł���X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<SandwichState> SandwichState::Instance() {
		static shared_ptr<SandwichState> instance;
		if (!instance) {
			instance = shared_ptr<SandwichState>(new SandwichState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void SandwichState::Enter(const shared_ptr<Player>& Obj) {
		Obj->EnterSandwichBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void SandwichState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExecuteSandwichBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void SandwichState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitSandwichBehavior();
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
		auto PtrCol = AddComponent<CollisionSphere>();
		

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
	}
	void Player_Second::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto A : OtherVec) {
			auto Fixd_Box = dynamic_pointer_cast<FixdBox>(A);
			if (Fixd_Box) {
				//����
				GetStateSecondMachine()->ChangeState(PinchState_Second::Instance());
			}
		}
	}


	//�X�e�B�b�N����
	void Player_Second::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		if (m_StatePlayer_SecondMachine->GetCurrentState() == MoveState_Second::Instance()) {
			Speed_F = 100.0f;
			Vec_Vec3 = Vector3(CntlVec[0].fThumbRX, 0, CntlVec[0].fThumbRY);
		}
		else if(m_StatePlayer_SecondMachine->GetCurrentState() == SandwichState_Second::Instance()){
			Speed_F = 3.0f;
			Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		}
		
		Rig->SetVelocity(Vec_Vec3 * Speed_F);

	}




	////////////////////////�X�e�[�g�X�^�[�g�֐�///////////////////////////////////
	//����
	void Player_Second::EnterToAttractBehavior() {
		//A�{�^����������Ă邩�H
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
			//KeepPushed_A = true;

		}
	}
	//����ł��鎞
	void Player_Second::EnterPinchBehavior() {
		if (FixedPos_b == false) {
			FixedPos_b = true;
		}
	}
	//����ňړ��̎�
	void Player_Second::EnterSandwichBehavior() {
		//�����Ȃ�
	};
	////////////////////////�X�e�[�g�p���֐�///////////////////////////////////////
	//�X�e�[�g�}�V�[���Ŏg���֐�
	void Player_Second::ExecuteMoveBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//�X�e�[�g�ړ�
			GetStateSecondMachine()->ChangeState(ToAttractState_Second::Instance());
			
		}
	}
	//���ރX�e�[�g
	void Player_Second::ExecuteToAttractBehavior() {
		auto PlayerL = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false);
		if (KeepPushed_A == true) 
		{
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			auto Trans = GetComponent<Transform>();
			auto Rig = GetComponent<Rigidbody>();
			float ElapsedTime_F = App::GetApp()->GetElapsedTime();
			if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
				//�����̈ʒu
				My_Pos_Vec3 = Trans->GetPosition();
				//������̃v���C���[�̈ʒu
				Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false)->GetComponent<Transform>()->GetPosition();
				New_Vec = Move_Velo(My_Pos_Vec3, Partner_Pos_Vec3);
				Rig->SetVelocity(Vector3(New_Vec * ElapsedTime_F * Speed_F * VelocityPower));
				
			}
			else {
				VelocityPower = 1.0f;
				GetStateSecondMachine()->ChangeState(MoveState_Second::Instance());
			}
			VelocityPower += AddVec;
		}
		if (PlayerL->Getsandwich()) {
			GetStateSecondMachine()->ChangeState(PinchState_Second::Instance());
		}
	}

	//����ł���Ƃ�
	void Player_Second::ExecutePinchBehavior() {
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//A��������Ă����炻�̏ꏊ�̈ʒu���Œ肳����
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			FixedPos();
		}
		else {
			GetStateSecondMachine()->ChangeState(MoveState_Second::Instance());
		}
		
		//�R���g���[����L�X�e�B�b�N�̓��͂�����΋���ňړ��X�e�[�g�Ɉړ�
		if (CntlVec[0].fThumbLX || CntlVec[0].fThumbLY) {
			GetStateSecondMachine()->ChangeState(SandwichState_Second::Instance());
		}
		else {
		}
	}

	//����ňړ�
	void Player_Second::ExecuteSandwichBehavior() {
		auto PtrPlayerL = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false);
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//�����ړ�
		if (CntlVec[0].wButtons& XINPUT_GAMEPAD_A && PtrPlayerL->GetStanEnemy()) {
			InputStick();
		}
		else {
			GetStateSecondMachine()->ChangeState(MoveState_Second::Instance());
		}
	}

	Vector3 Player_Second::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 = PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
	}
	

	/////////////////////////�X�e�[�g�I���֐�/////////////////////////////////////////
	void Player_Second::ExitMoveBehabior() {
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0, 0, 0);
	}
	void Player_Second::ExitToAttractBehavior() {
		

	}
	//����ł���Ƃ�
	void Player_Second::ExitPinchBehavior() {
		FixedPos_b = false;
	}

	//����ňړ��Ƃ�
	void Player_Second::ExitSandwichBehavior() {
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
	//����ł���X�e�[�g
	//--------------------------------------------------------------------------------------
	//	class PinchState_Second : public ObjState<Player_Second>;
	//	�p�r:����ł���X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<PinchState_Second> PinchState_Second::Instance() {
		static shared_ptr<PinchState_Second> instance;
		if (!instance) {
			instance = shared_ptr<PinchState_Second>(new PinchState_Second);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void PinchState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
		Obj->EnterPinchBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void PinchState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExecutePinchBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void PinchState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
	//Obj->ExitPinchBehavior();
	}


	//����ł��ǂ����Ă�X�e�[�g
	//--------------------------------------------------------------------------------------
	//	class SandwichState_Second : public ObjState<Player_Second>;
	//	�p�r:����ňړ��X�e�[�g
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<SandwichState_Second> SandwichState_Second::Instance() {
		static shared_ptr<SandwichState_Second> instance;
		if (!instance) {
			instance = shared_ptr<SandwichState_Second>(new SandwichState_Second);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void SandwichState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
		Obj->EnterSandwichBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void SandwichState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExecuteSandwichBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void SandwichState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitSandwichBehavior();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	




}
//end basecross

