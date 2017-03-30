/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{



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
		PtrCol->SetIsHitAction(IsHitAction::Auto);
		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

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

		//�J�����𓾂�
		auto PtrCamera = dynamic_pointer_cast<LookAtCamera>(OnGetDrawCamera());
		if (PtrCamera) {
			//MyLookAtCamera�ł���
			//MyLookAtCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			PtrCamera->SetTargetObject(GetThis<GameObject>());
			PtrCamera->SetTargetToAt(Vector3(0, 0.25f, 0));
		}
		//�ŏ���A�{�^���̓W�����v
		m_PlayerAction = PlayerAction::Jump;
		//�X�e�[�g�}�V���̍\�z
		m_StatePlayerMachine.reset(new LayeredStateMachine<Player>(GetThis<Player>()));
		//�ŏ��̃X�e�[�g��PlayerDefault�Ƀ��Z�b�g
		m_StatePlayerMachine->Reset(PlayerDefaultState::Instance());
	}

	//�X�V
	void Player::OnUpdate() {
		//�X�e�[�g�}�V���X�V
		m_StatePlayerMachine->Update();
	}

	//��X�V
	void Player::OnUpdate2() {
		//������̕\��
		DrawStrings();
	}


	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		//�v���C���[�������ɓ�������
		if (GetStateMachine()->GetTopState() == PlayerJumpState::Instance()) {
			//���݂��W�����v�X�e�[�g�Ȃ�PlayerDefault�Ƀ��Z�b�g
			GetStateMachine()->Reset(PlayerDefaultState::Instance());
		}
	}

	void Player::ChangeStateJump() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//A�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				if (GetStateMachine()->GetTopState() == PlayerDefaultState::Instance()) {
					GetStateMachine()->Push(PlayerJumpState::Instance());
				}
			}
		}
	}

	//������̕\��
	void Player::DrawStrings() {
		auto PtrPlayerSecnd = GetStage()->GetSharedGameObject<Player_Secnd>(L"Player_S", false)->GetStrings();


		//������\��
		//�s��
		wstring BEHAVIOR;
		if (GetStateMachine()->GetTopState() == PlayerDefaultState::Instance()) {
			BEHAVIOR = L"�f�t�H���g";
		}
		else {
			BEHAVIOR = L"�W�����v";
		}
		BEHAVIOR += L"\n";

		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		FPS += Util::FloatToWStr(ElapsedTime);
		FPS += L"\n";

		auto Pos = GetComponent<Transform>()->GetPosition();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring RididStr(L"Velocity:\t");
		auto Velocity = GetComponent<Rigidbody>()->GetVelocity();
		RididStr += L"X=" + Util::FloatToWStr(Velocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		RididStr += L"Y=" + Util::FloatToWStr(Velocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		RididStr += L"Z=" + Util::FloatToWStr(Velocity.z, 6, Util::FloatModify::Fixed) + L"\n";


		wstring HitObjectStr(L"HitObject: ");
		if (GetComponent<Collision>()->GetHitObjectVec().size() > 0) {
			for (auto&v : GetComponent<Collision>()->GetHitObjectVec()) {
				HitObjectStr += Util::UintToWStr((UINT)v.get()) + L",";
			}
			HitObjectStr += L"\n";
		}
		else {
			HitObjectStr += L"NULL\n";
		}
		wstring str = BEHAVIOR + FPS + PositionStr + RididStr + HitObjectStr + PtrPlayerSecnd;
		//�����������
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}
	

	//--------------------------------------------------------------------------------------
	///	�ʏ�X�e�[�g
	//--------------------------------------------------------------------------------------

	IMPLEMENT_SINGLETON_INSTANCE(PlayerDefaultState)

	void PlayerDefaultState::Enter(const shared_ptr<Player>& Obj) {
		
		//�������Ȃ�
	}

	void PlayerDefaultState::Execute(const shared_ptr<Player>& Obj) {
		auto PtrBehavior = Obj->GetBehavior<PlayerBehavior>();
		PtrBehavior->MovePlayer();
		auto PtrGrav = Obj->GetBehavior<Gravity>();
		PtrGrav->Execute();
		Obj->ChangeStateJump();
		
	}

	void PlayerDefaultState::Exit(const shared_ptr<Player>& Obj) {
		//�������Ȃ�
	}

	//--------------------------------------------------------------------------------------
	///	�W�����v�X�e�[�g
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(PlayerJumpState)

		void PlayerJumpState::Enter(const shared_ptr<Player>& Obj) {
		auto PtrGrav = Obj->GetBehavior<Gravity>();
		PtrGrav->StartJump(Vector3(0, 4.0f, 0));
	}

	void PlayerJumpState::Execute(const shared_ptr<Player>& Obj) {
		//�W�����v���������ύX�\
		auto PtrDefault = Obj->GetBehavior<PlayerBehavior>();
		PtrDefault->MovePlayer();
		auto PtrGrav = Obj->GetBehavior<Gravity>();
		PtrGrav->Execute();
	}

	void PlayerJumpState::Exit(const shared_ptr<Player>& Obj) {
		//�������Ȃ�
	}
	/////////////////////////////////////////////////////////////////////////////////////
	//Player2
	/////////////////////////////////////////////////////////////////////////////////////

	//�\�z�Ɣj��
	Player_Secnd::Player_Secnd(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{}

	//������
	void Player_Secnd::OnCreate() {
		
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();


		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"TRACE_TX");
		//�X�e�[�g�}�V���̍\�z
		m_State_PlayerSecnd_Machine.reset(new LayeredStateMachine<Player_Secnd>(GetThis<Player_Secnd>()));
		//�ŏ��̃X�e�[�g��PlayerDefault�Ƀ��Z�b�g
		m_State_PlayerSecnd_Machine->Reset(PlayerSecndDefaultState::Instance());
	}
	
	void Player_Secnd::OnUpdate() {
		m_State_PlayerSecnd_Machine->Update();
		DrawStrings();
	}
	void Player_Secnd::DrawStrings() {

		//������\��
		wstring P_S = L"�v���C���[�Q";
		P_S += L"\n";
		//�s��
		wstring BEHAVIOR;
		if (GetStatePlayerSecndMachine()->GetTopState() == PlayerSecndDefaultState::Instance()) {
			BEHAVIOR = L"�f�t�H���g";
		}
		else {
			BEHAVIOR = L"�W�����v";
		}
		BEHAVIOR += L"\n";


		DebugCharacter = P_S + BEHAVIOR;
	}
	wstring Player_Secnd::GetStrings() {
		return DebugCharacter;
	}
	//--------------------------------------------------------------------------------------
	///	�ʏ�X�e�[�g
	//--------------------------------------------------------------------------------------

	IMPLEMENT_SINGLETON_INSTANCE(PlayerSecndDefaultState)
		void PlayerSecndDefaultState::Enter(const shared_ptr<Player_Secnd>& Obj) {
		//�������Ȃ�
	}

	void PlayerSecndDefaultState::Execute(const shared_ptr<Player_Secnd>& Obj) {
		auto PtrBehavior = Obj->GetBehavior<PlayerBehavior>();
		PtrBehavior->MovePlayer_Second();
		auto PtrGrav = Obj->GetBehavior<Gravity>();
		PtrGrav->Execute();
		

	}

	void PlayerSecndDefaultState::Exit(const shared_ptr<Player_Secnd>& Obj) {
		//�������Ȃ�
	}



}
//end basecross

