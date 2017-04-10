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

		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
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

		auto Pos = GetComponent<Transform>()->GetWorldMatrix().PosInMatrix();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring str = FPS + VelocityPowerStr + PositionStr;
		
		auto PtrString = GetComponent<StringSprite>();
		//PtrString->SetText(str);
	}

	
	
	
	//�X�e�B�b�N����
	void Player::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		Speed_F = 100.0f;
		Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		Rig->SetVelocity(Vec_Vec3 * Speed_F);

	}


	
	
	////////////////////////�X�e�[�g�X�^�[�g�֐�///////////////////////////////////
	//����
	void Player::EnterToAttractBehavior() {
		//A�{�^����������Ă邩�H
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
		//	KeepPushed_A = true;
			
		}
	}

	////////////////////////�X�e�[�g�p���֐�///////////////////////////////////////
	//�X�e�[�g�}�V�[���Ŏg���֐�
	void Player::ExcuteMoveBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//�X�e�[�g�ړ�
			GetStateMachine()->ChangeState(ToAttractState::Instance());
			
		}
	}
	//���ރX�e�[�g
	void Player::ExcuteToAttractBehavior() {
		if (KeepPushed_A == true) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			auto Trans = GetComponent<Transform>();
			auto Rig = GetComponent<Rigidbody>();
			float ElapsedTime_float = App::GetApp()->GetElapsedTime();
			if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
				//�����̈ʒu
				My_Pos_Vec3 = Trans->GetPosition();
				//������̃v���C���[�̈ʒu
				Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
				New_Vec = Move_Velo(My_Pos_Vec3, Partner_Pos_Vec3);
				Rig->SetVelocity(Vector3(New_Vec * ElapsedTime_float * Speed_F * VelocityPower));
				
			}
			else
			{
				VelocityPower = 1.0f;
				GetStateMachine()->ChangeState(MoveState::Instance());
			}
			VelocityPower += AddVec;
		}

	}

	Vector3 Player::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 =  PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
	}
	/////////////////////////�X�e�[�g�I���֐�/////////////////////////////////////////
	void Player::ExitMoveBehabior() {
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0,0,0);
	}
	void Player::ExitToAttractBehavior() {
		

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
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void MoveState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExcuteMoveBehavior();
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
		Obj->ExcuteToAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ToAttractState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitToAttractBehavior();
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
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
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
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Trans = GetComponent<Transform>();
		float ElapsedTime_float = App::GetApp()->GetElapsedTime();
		auto Rig = GetComponent<Rigidbody>();
	}



	//�X�e�B�b�N����
	void Player_Second::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		Speed_F = 100.0f;
		Vec_Vec3 = Vector3(CntlVec[0].fThumbRX, 0, CntlVec[0].fThumbRY);
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

	////////////////////////�X�e�[�g�p���֐�///////////////////////////////////////
	//�X�e�[�g�}�V�[���Ŏg���֐�
	void Player_Second::ExcuteMoveBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//�X�e�[�g�ړ�
			GetStateSecondMachine()->ChangeState(ToAttractState_Second::Instance());
			
		}
	}
	//���ރX�e�[�g
	void Player_Second::ExcuteToAttractBehavior() {
		if (KeepPushed_A == true) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			auto Trans = GetComponent<Transform>();
			auto Rig = GetComponent<Rigidbody>();
			float ElapsedTime_float = App::GetApp()->GetElapsedTime();
			if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
				//�����̈ʒu
				My_Pos_Vec3 = Trans->GetPosition();
				//������̃v���C���[�̈ʒu
				Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false)->GetComponent<Transform>()->GetPosition();
				New_Vec = Move_Velo(My_Pos_Vec3, Partner_Pos_Vec3);
				Rig->SetVelocity(Vector3(New_Vec * ElapsedTime_float * Speed_F * VelocityPower));
				
			}
			else {
				VelocityPower = 1.0f;
				GetStateSecondMachine()->ChangeState(MoveState_Second::Instance());
			}
			VelocityPower += AddVec;
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
		Obj->ExcuteMoveBehavior();
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
		Obj->ExcuteToAttractBehavior();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void ToAttractState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitToAttractBehavior();
	}
}
//end basecross

