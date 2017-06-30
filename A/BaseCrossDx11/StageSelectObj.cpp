#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//Abe20170421
	//--------------------------------------------------------------------------------------
	//	�t���[���X�v���C�g
	//--------------------------------------------------------------------------------------
	SelectFlame::SelectFlame(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_layer(layer)
	{}

	void SelectFlame::OnCreate()
	{
		//���W�ݒ�
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(0, 0, 0);

		//�`��ݒ�
		auto Draw = AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECT_FLAME_TX");

		//�����x�ݒ�
		SetAlphaActive(true);
		//���C���[�ݒ�
		SetDrawLayer(m_layer);
	}

	//Abe20170525
	//--------------------------------------------------------------------------------------
	//	���S
	//--------------------------------------------------------------------------------------
	SelectLogo::SelectLogo(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_layer(layer)
	{}

	void SelectLogo::OnCreate()
	{
		//���W�ݒ�
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(0, 0, 0);

		//�`��ݒ�
		auto Draw = AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECT_LOGO_TX");

		//�����x�ݒ�
		SetAlphaActive(true);
		//���C���[�ݒ�
		SetDrawLayer(m_layer);
	}
	//Abe20170525

	//--------------------------------------------------------------------------------------
	//	�v���C���[
	//--------------------------------------------------------------------------------------
	SelectPlayer::SelectPlayer(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, float speed) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_Speed(speed)
	{}

	void SelectPlayer::OnCreate()
	{
		//obj�쐬
		for (int i = 0; i < 2; i++)
		{
			auto PlayerPtr = GetStage()->AddGameObject<GameObject>();
			//���W�ݒ�
			auto Trans = PlayerPtr->AddComponent<Transform>();
			//���W�ύX
			Vector3 pos = m_InitPos;
			pos.x += -m_DifLength + (i * m_DifLength * 2);
			Trans->SetPosition(pos);
			Trans->SetScale(m_InitScale);
			Trans->SetRotation(0, 0, 0);

			//�`��ݒ�
			auto PtrDraw = PlayerPtr->AddComponent<PNTBoneModelDraw>();

			PtrDraw->SetMeshResource(L"Player_Model");
			//	PtrDraw->SetTextureResource(L"TRACE_TX");

			//��������
			SetAlphaActive(true);

			//Rigidbody������
			auto PtrRedid = PlayerPtr->AddComponent<Rigidbody>();
			//�Փ˔��������
			auto PtrCol = PlayerPtr->AddComponent<CollisionSphere>();
			//	PtrCol->SetDrawActive(true);
			PtrCol->SetUpdateActive(false);
			PlayerPtr->SetDrawLayer(0);

			//�v���C���[�̃A�N�Z�T?
			m_Player.push_back(PlayerPtr);
			//Player�����ʒu
			m_InitPlayerPos.push_back(pos);
			PtrDraw->AddAnimation(L"Wait", 0, 30, true, 30.0f);
			PtrDraw->AddAnimation(L"LeftRot", 80, 15, false, 30.0f);
			PtrDraw->AddAnimation(L"RightRot", 120, 15, false, 30.0f);
			//����PLayer
			if (i == 0) {
				//�����ő�l�̐ݒ�
				m_leftLeaveMax = Vector3(pos.x - 2, pos.y, pos.z);
				//���ލŏ��l�̐ݒ�
				m_leftSandMinit = Vector3(pos.x + 2, pos.y, pos.z);
				//�����ʒu�̐ݒ�
				m_leftInitPos = Vector3(pos);
			}
			else if (i == 1) {
				//�����ő�l�̐ݒ�
				m_RightLeaveMax = Vector3(pos.x + 2, pos.y, pos.z);
				//���ލŏ��l�̐ݒ�
				m_RightSandMinit = Vector3(pos.x - 2, pos.y, pos.z);
				//�����ʒu�̐ݒ�
				m_RightInitPos = Vector3(pos);
			}
			PtrDraw->SetDrawActive(false);
		}
		//�f�o�b�O��������
		auto debtxt = GetStage()->AddGameObject<DebugTxt>();
		debtxt->SetLayer(10);
		//�F�ԂɕύX
		debtxt->SetColor(Vector3(1, 0, 0));
		//�傫���ύX
		debtxt->SetScaleTxt(40);

		m_Debugtxt = debtxt;
		//Abe20170524

		m_InitMoveFlg = true;


	}

	void SelectPlayer::OnUpdate()
	{
		SetUpdateActive(false);
		//��Փx�̈ړ������ꂽ�Ƃ��̃v���C���[�̓����蔻�������
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && selecflg == true && StateNam == 0) {
			StateNam = 1;
			selecflg = false;
		}

		switch (StateNam) {
		case 0:
			break;
		case 1:
			LeaveMove();
			break;
		case 2:
			SandMove();
			break;
		case 3:
			InitPosMove();
			break;
		}

	}
	//�s���֐�
	//���ނ��珉���ʒu�ɖ߂鎞�Ɏg�p
	void SelectPlayer::InitPosMove() {
		//�v���C���[�̎擾
		auto Player1 = m_Player[0];
		auto Player1Trans = Player1->GetComponent<Transform>();
		auto Player2 = m_Player[1];
		auto Player2Trans = Player2->GetComponent<Transform>();
		//�ړ�
		if (Player1) {
			if (Player1Trans->GetPosition() <= m_leftInitPos) {
				Player1Trans->SetPosition(m_leftInitPos);
			}
			else if (!(Player1Trans->GetPosition() <= m_leftInitPos)) {
				auto Pos = Player1Trans->GetPosition();
				Pos.x -= m_Speed * App::GetApp()->GetElapsedTime();
				Player1Trans->SetPosition(Pos);
			}
		}
		if (Player2) {
			if (Player2Trans->GetPosition() >= m_RightInitPos) {
				Player2Trans->SetPosition(m_RightInitPos);
			}
			else if (!(Player2Trans->GetPosition() >= m_RightInitPos)) {
				auto Pos = Player2Trans->GetPosition();
				Pos.x += m_Speed * App::GetApp()->GetElapsedTime();
				Player2Trans->SetPosition(Pos);
			}
		}
		//���E�l
		if (Player1Trans->GetPosition() <= m_RightInitPos) {
			Player1Trans->SetPosition(m_RightInitPos);
		}
		if (Player2Trans->GetPosition() >= m_leftInitPos) {
			Player2Trans->SetPosition(m_leftInitPos);
		}
		//���݂̓��Player�̈ʒu�̎擾
		auto Player1Pos = Player1Trans->GetPosition();
		auto Player2Pos = Player2Trans->GetPosition();
		//�ǂ���������l�ɖ߂�����
		if (Player1Pos >= m_leftInitPos || Player2Pos <= m_RightInitPos) {
			//�����l�ɖ߂�s����false�ɂ���
			//m_InitMoveFlg = false;
			StateNam = 0;
		}
	}
	//���ނƂ��Ɏg�p
	void SelectPlayer::SandMove() {
		//�v���C���[�̎擾
		auto Player1 = m_Player[0];
		auto Player1Trans = Player1->GetComponent<Transform>();
		//	Player1->GetComponent<CollisionSphere>()->SetUpdateActive(true);
		auto Player2 = m_Player[1];
		auto Player2Trans = Player2->GetComponent<Transform>();
		//	Player2->GetComponent<CollisionSphere>()->SetUpdateActive(true);
		if (Player1) {
			auto Pos = Player1Trans->GetPosition();
			Pos.x += m_Speed * App::GetApp()->GetElapsedTime();
			Player1Trans->SetPosition(Pos);
		}
		else if (m_leftSandMinit >= Player1Trans->GetPosition()) {
			Player1Trans->SetPosition(m_leftSandMinit);
		}
		if (Player2) {
			auto Pos = Player2Trans->GetPosition();
			Pos.x -= m_Speed * App::GetApp()->GetElapsedTime();
			Player2Trans->SetPosition(Pos);
		}
		else if (m_RightSandMinit <= Player2Trans->GetPosition()) {
			Player2Trans->SetPosition(m_RightSandMinit);
		}
		if (m_leftSandMinit >= Player1Trans->GetPosition() &&
			m_RightSandMinit <= Player2Trans->GetPosition()) {
			StateNam = 2;
		}
	}
	//����鎞�Ɏg�p
	void SelectPlayer::LeaveMove() {
		//�v���C���[�̎擾
		auto Player1 = m_Player[0];
		auto Player1Trans = Player1->GetComponent<Transform>();
		//	Player1->GetComponent<CollisionSphere>()->SetUpdateActive(false);
		auto Player2 = m_Player[1];
		auto Player2Trans = Player2->GetComponent<Transform>();
		//Player2->GetComponent<CollisionSphere>()->SetUpdateActive(false);
		if (Player1) {
			auto Pos = Player1Trans->GetPosition();
			Pos.x -= m_Speed * App::GetApp()->GetElapsedTime();
			Player1Trans->SetPosition(Pos);
			if (m_leftLeaveMax >= Player1Trans->GetPosition()) {
				Player1Trans->SetPosition(m_leftLeaveMax);
			}
		}
		if (Player2) {
			auto Pos = Player2Trans->GetPosition();
			Pos.x += m_Speed * App::GetApp()->GetElapsedTime();
			Player2Trans->SetPosition(Pos);
			if (m_RightLeaveMax >= Player1Trans->GetPosition()) {
				Player2Trans->SetPosition(m_RightLeaveMax);
			}
		}
		if (m_leftLeaveMax >= Player1Trans->GetPosition() &&
			m_RightLeaveMax >= Player2Trans->GetPosition()) {
			StateNam = 2;
		}
	}



	void SelectPlayer::SetPlayerUpdate(bool flg)
	{
		SetUpdateActive(flg);

		//�L�����Z�������Ƃ��ɓ����̖h�~
		m_CancelFlg = true;

		//�����o�O�o�邩��O�̂���
		for (auto obj : m_Player)
		{
			obj->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
		}
	}

	//���W�ړ�
	void SelectPlayer::SetPos(Vector3 pos)
	{
		int count = 0;
		for (auto obj : m_Player)
		{
			obj->GetComponent<CollisionSphere>()->SetUpdateActive(false);
			Vector3 pos1 = pos;
			pos1.x += -m_DifLength + (count * m_DifLength * 2);
			obj->GetComponent<Transform>()->SetPosition(pos1);
			count++;
		}
	}

	//���W�擾
	Vector3 SelectPlayer::GetPos()
	{
		Vector3 ppos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
		Vector3 ppos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();

		return (ppos1 + ppos2) / 2;
	}

	//���f���̌���
	void SelectPlayer::Model() {
		if (m_Model_flg) {
			auto Player1 = m_Player[0];
			auto Player2 = m_Player[1];
			Player1->GetComponent<Transform>()->SetRotation(0, -XM_PI / 2, 0);
			Player2->GetComponent<Transform>()->SetRotation(0, XM_PI / 2, 0);

			m_Model_flg = false;
		}
	}
	//�ҋ@�A�j���[�V����
	void SelectPlayer::AnimationWait() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		auto PtrDraw2 = m_Player[1]->GetComponent<PNTBoneModelDraw>();
		if (!(PtrDraw->GetCurrentAnimation() == L"Wait") && m_WaitFlg) {
			PtrDraw->ChangeCurrentAnimation(L"Wait");
			PtrDraw2->ChangeCurrentAnimation(L"Wait");
		}
		UpdateAnyAnimation();
		UpdateAnyAnimation2();
	}

	//�A�j���[�V�����X�V�֐�
	bool SelectPlayer::UpdateAnyAnimation() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		return PtrDraw->UpdateAnimation(ElapsedTime);
	}
	bool SelectPlayer::UpdateAnyAnimation2() {
		auto PtrDraw = m_Player[1]->GetComponent<PNTBoneModelDraw>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		return PtrDraw->UpdateAnimation(ElapsedTime);
	}

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W��Փx�ƃX�e�[�W�I��
	//--------------------------------------------------------------------------------------
	StageModeControl::StageModeControl(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void StageModeControl::OnCreate() {
		//��Փx�X�v���C�g�̒ǉ�

		GetStage()->SetSharedGameObject(L"Easy", GetStage()->AddGameObject<ModeSelect>(Vector3(0, -60, -4), Vector3(305, 615, 1), 1, false, 1));
		GetStage()->SetSharedGameObject(L"Normal", GetStage()->AddGameObject<ModeSelect>(Vector3(320, -60, -4), Vector3(305, 615, 1), 2, false, 3));
		GetStage()->SetSharedGameObject(L"Hard", GetStage()->AddGameObject<ModeSelect>(Vector3(-320, -60, -4), Vector3(305, 615, 1), 3, false, 2));
		//��Փx�X�v���C�g�̔z�u 1�C�[�W�[�@�Q�m�[�}���@�R�n�[�h
		GetStage()->AddGameObject<SelectModeSquare>(1);
		GetStage()->AddGameObject<SelectModeSquare>(2);
		GetStage()->AddGameObject<SelectModeSquare>(3);


		//�X�e�[�W�̒ǉ�
		int m_AddEasy = 4;
		int m_AddNormal = 12;
		int m_AddHard = 16;
		//��Փx�̎擾
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		auto EasyTrans = EasyPtr->GetComponent<Transform>();
		auto EasyPos = EasyTrans->GetPosition();
		auto EasyScale = EasyTrans->GetScale();
		auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		auto NormalTrans = NormalPtr->GetComponent<Transform>();
		auto NormalPos = NormalTrans->GetPosition();
		auto NormalScale = NormalTrans->GetScale();
		auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
		auto HardTrans = HardPtr->GetComponent<Transform>();
		auto HardPos = HardTrans->GetPosition();
		auto HardScale = HardTrans->GetScale();



		//�e�X�e�[�W�̐���
		for (int StageNumber = 1; StageNumber < 17; StageNumber++) {
			//��Փx�̔z��ɃX�e�[�W��ǉ�����
			if (StageNumber <= m_AddEasy) {
				m_Easy.push_back(GetStage()->AddGameObject<StageBox>(Vector3(EasyPos.x, EasyPos.y, EasyPos.z), Vector3(1, 1, 1), StageNumber));
			}
			else if (StageNumber <= m_AddNormal) {
				m_Normal.push_back(GetStage()->AddGameObject<StageBox>(Vector3(NormalPos.x, NormalPos.y, NormalPos.z), Vector3(1, 1, 1), StageNumber));
			}
			else if (StageNumber <= m_AddHard) {
				m_Hard.push_back(GetStage()->AddGameObject<StageBox>(Vector3(HardPos.x, HardPos.y, HardPos.z), Vector3(1, 1, 1), StageNumber));
			}
		}
		m_NormalStageCenter = 0;
		m_NormalUP = 7;
		m_NormalDown = 1;

		m_CenterScalse = Vector3(256, 256, 5);
		m_NoCenterScalse = Vector3(156, 156, 2);
		m_MoveSpeed = 20.0f;
		m_Center = Vector3(0, 0, 0);
		m_Up = Vector3(0, 0, 0);
		m_Down = Vector3(0, 0, 0);
		m_Top = Vector3(0, 0, 0);
		m_ElementNumTopFlg = true;
		m_EasyStageCenter = 0;
		SetUpdateActive(true);
		auto pMultiSoundEffect = AddComponent<MultiSoundEffect>();
		pMultiSoundEffect->AddAudioResource(L"StageSe_SE");
		m_StickUpUnder = true;

	}
	void StageModeControl::OnUpdate() {

		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
		auto PtrStageModeControl = GetStage()->GetSharedGameObject<StageModeControl>(L"StageModeControl", false);
		auto PtrGoStageCheck = GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false);

		//�͂��߂���������
		if (InitOneflg == true) {
			StandardEasyPos();
			StandardNormalPos();
			StandardHardPos();
			//InitSetCenter�@InitSetUp�@InitSetDown�@InitSetOther�̂S��
			Init();
			InitOneflg = false;
		}
		else {
			//w�L�[�œ�Փx�̈ړ��������Ƃ��Ɉʒu�X�V
			if (KeylVec.m_bPressedKeyTbl['W'] || KeylVec.m_bPressedKeyTbl['E'] ||
				CntlVec[0].fThumbLY > 0.5 || CntlVec[0].fThumbLY < -0.5 && m_ModeMoveEnd && m_StageMoveEnd &&
				m_StickDown) {
				if (m_OneSE == false) {
					auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
					pMultiSoundEffect->Start(L"StageSe_SE", 0, 1.0f);
					m_OneSE = true;
				}
				m_ElementCenter = 0;
				m_ElementUp = 0;
				m_ElementDown = 0;
				m_ElementTop = 0;
				m_Center = Vector3(0, 0, 0);
				m_Up = Vector3(0, 0, 0);
				m_Down = Vector3(0, 0, 0);
				m_Top = Vector3(0, 0, 0);

			}
			else {
				m_OneSE = false;
			}
		}
		//�e�X�e�[�W�̈ړ�
		StageMove();
		if (m_KeepPushing) {
			if (CntlVec[0].wButtons& XINPUT_GAMEPAD_A) {
				m_KeepApudh = true;
			}
			else if (!(CntlVec[0].wButtons& XINPUT_GAMEPAD_A)) {
				m_KeepApudh = false;
				m_KeepPushing = false;
			}
		}

		if (m_KeepPushing == false && m_KeepApudh == false) {
			//select�̃��j���[����A�{�^�����������
			if (CntlVec[0].wPressedButtons& XINPUT_GAMEPAD_A) {
				m_APush = true;
			}
			else {
				m_APush = false;
			}
		}



		if (KeylVec.m_bPressedKeyTbl['Y'] || m_APush && m_ModeMoveEnd && m_StageMoveEnd &&
			m_StickDown && m_ModeMoveEnd) {
			m_KeepPushing = true;
			m_KeepApudh = true;
			m_APush = false;
			PtrGoStageCheck->SetCloseflg(true);
			GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false)->SetUpdateActive(false);
			GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false)->SetUpdateActive(false);
			GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false)->SetUpdateActive(false);
			//�m�F�E�B���h�E�N��
			GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->OpenCheck();
			GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->SetStageNumber(m_CenterStageNum);
			GetStage()->GetSharedGameObject<EnemyCount>(L"Count", false)->Count();

			//Abe20170623
			//�X�R�A�\��
			GetStage()->GetSharedGameObject<ScoreDisplay>(L"ScoreDisplay", false)->Disp(GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->GetStageNumber());
			//Abe20170623

			SetUpdateActive(false);
		}

		//�ړ��\��Modeselect
		if (EasyPtr->EndMove() == true && NormalPtr->EndMove() == true && HardPtr->EndMove() == true) {
			m_ModeMoveEnd = true;
		}
		else {
			m_ModeMoveEnd = false;
		}
	}

	//��ƂȂ�ʒu�̐ݒ�
	void StageModeControl::StandardEasyPos() {
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		auto EasyTrans = EasyPtr->GetComponent<Transform>();
		auto EasyPos = EasyTrans->GetPosition();
		//��ʒu�̎擾
		m_EasyPosCenter = Vector3(EasyPos.x, EasyPos.y, EasyPos.z);
		m_EasyPosUP = Vector3(m_EasyPosCenter.x, m_EasyPosCenter.y + 460, m_EasyPosCenter.z + 15);
		m_EasyPosDown = Vector3(m_EasyPosCenter.x, m_EasyPosCenter.y - 460, m_EasyPosCenter.z - 15);
		m_EasyOtherPos = Vector3(m_EasyPosDown.x, m_EasyPosDown.y - 100, m_EasyPosDown.z - 15);
		m_EasyTopPos = Vector3(m_EasyPosUP.x, m_EasyPosUP.y + 100, m_EasyPosUP.z + 15);
	}
	void StageModeControl::StandardNormalPos() {
		auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		auto NormalTrans = NormalPtr->GetComponent<Transform>();
		auto NormalPos = NormalTrans->GetPosition();

		//��ʒu�̎擾
		m_NormalPosCenter = Vector3(NormalPos.x, NormalPos.y, NormalPos.z);
		m_NormalPosUP = Vector3(m_NormalPosCenter.x, m_NormalPosCenter.y + 460, m_NormalPosCenter.z + 15);
		m_NormalPosDown = Vector3(m_NormalPosCenter.x, m_NormalPosCenter.y - 460, m_NormalPosCenter.z - 15);
		m_NormalOtherPos = Vector3(m_NormalPosDown.x, m_NormalPosDown.y - 100, m_NormalPosDown.z - 15);
		m_NormalTopPos = Vector3(m_NormalPosUP.x, m_NormalPosUP.y + 100, m_NormalPosUP.z + 15);
	}
	void StageModeControl::StandardHardPos() {
		auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
		auto HardTrans = HardPtr->GetComponent<Transform>();
		auto HardPos = HardTrans->GetPosition();


		//��ʒu�̎擾
		m_HardPosCenter = Vector3(HardPos.x, HardPos.y + 1, HardPos.z);
		m_HardPosUP = Vector3(m_HardPosCenter.x, m_HardPosCenter.y + 460, m_HardPosCenter.z + 15);
		m_HardPosDown = Vector3(m_HardPosCenter.x, m_HardPosCenter.y - 460, m_HardPosCenter.z - 15);
		m_HardOtherPos = Vector3(m_HardPosDown.x, m_HardPosDown.y - 100, m_HardPosDown.z - 15);
		m_HardTopPos = Vector3(HardPos.x, HardPos.y + 100, m_HardPosUP.z + 15);
	}
	//�e��Փx�̊e�X�e�[�W�̏����z�u
	void StageModeControl::Init() {
		InitSetCenter();
		InitSetUp();
		InitSetDown();
		InitSetOther();
	}
	void StageModeControl::InitSetCenter() {
		m_Easy[0]->GetComponent<Transform>()->SetPosition(m_EasyPosCenter);
		m_Easy[0]->GetComponent<Transform>()->SetScale(m_CenterScalse);
		m_Normal[0]->GetComponent<Transform>()->SetPosition(m_NormalPosCenter);
		m_Hard[0]->GetComponent<Transform>()->SetPosition(m_HardPosCenter);
	}
	void StageModeControl::InitSetUp() {
		m_Easy[3]->GetComponent<Transform>()->SetPosition(m_EasyPosUP);
		m_Normal[7]->GetComponent<Transform>()->SetPosition(m_NormalPosUP);
		m_Hard[3]->GetComponent<Transform>()->SetPosition(m_HardPosUP);
	}
	void StageModeControl::InitSetDown() {
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		m_Easy[1]->GetComponent<Transform>()->SetPosition(m_EasyPosDown);
		m_Normal[1]->GetComponent<Transform>()->SetPosition(m_NormalPosDown);
		m_Hard[1]->GetComponent<Transform>()->SetPosition(m_HardPosDown);


	}
	void StageModeControl::InitSetOther() {
		m_Easy[2]->GetComponent<Transform>()->SetPosition(m_EasyOtherPos);
		m_Easy[2]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
		for (int i = 0; i < 8; i++)
		{
			if (i != 0 && i != 1 && i != 7) {
				m_Normal[i]->GetComponent<Transform>()->SetPosition(m_NormalOtherPos);
				m_Normal[i]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			}
		}
		m_Hard[2]->GetComponent<Transform>()->SetPosition(m_HardOtherPos);
		m_Hard[2]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);



	}
	//�C�[�W�̈ړ��������ĂԂƂ�
	void StageModeControl::EasySelect() {
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (CntlVec[0].fThumbLY < 0.3 && CntlVec[0].fThumbLY > -0.3 && m_StickDown == false) {
			m_StickDown = true;
		}
		//��Փx�C�[�W�[���Z���^�[�ɂ�������X�e�[�W�I�����o����
		if (EasyPtr->GetCenter()) {
			StandardEasyPos();
			if (KeylVec.m_bPressedKeyTbl['R'] || CntlVec[0].fThumbLY > 0.5 &&CntlVec[0].fThumbLX < 0.3 && CntlVec[0].fThumbLX > -0.3
				&& m_ModeMoveEnd && m_StageMoveEnd && m_StickDown) {
				m_EasyStageCenter++;
				m_Flg = true;
				m_ElementNumTopFlg = true;
				m_StageMoveEnd = false;
				m_StickDown = false;
				m_StickUpUnder = true;
			}
			if (KeylVec.m_bPressedKeyTbl['T'] || CntlVec[0].fThumbLY < -0.5 &&CntlVec[0].fThumbLX < 0.3 && CntlVec[0].fThumbLX > -0.3
				&& m_ModeMoveEnd && m_StageMoveEnd && m_StickDown) {
				m_EasyStageCenter--;
				m_Flg = true;
				m_ElementNumTopFlg = true;
				m_StageMoveEnd = false;
				m_StickDown = false;
				m_StickUpUnder = false;
			}
			if (m_EasyStageCenter > 3) {
				m_EasyStageCenter = 0;
			}
			if (m_EasyStageCenter < 0) {
				m_EasyStageCenter = 3;
			}


			switch (m_EasyStageCenter)
			{
			case 0:
				ElementNum(0, 3, m_EasyStageCenter);
				EasyScale();
				EasyMove();
				m_CenterStageNum = 1;
				break;
			case 1:
				ElementNum(0, 3, m_EasyStageCenter);
				EasyScale();
				EasyMove();
				m_CenterStageNum = 2;
				break;
			case 2:
				ElementNum(0, 3, m_EasyStageCenter);
				EasyScale();
				EasyMove();
				m_CenterStageNum = 3;
				break;
			case 3:
				ElementNum(0, 3, m_EasyStageCenter);
				EasyScale();
				EasyMove();
				m_CenterStageNum = 4;
				break;
			}
		}
	}
	//�m�[�}���̑I���ړ����ĂԂƂ�
	void StageModeControl::NormalSelect() {
		auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].fThumbLY < 0.3 && CntlVec[0].fThumbLY > -0.3 && m_StickDown == false) {
			m_StickDown = true;
		}
		//��Փx�m�[�}�����Z���^�[�ɂ�������X�e�[�W�I�����o����
		if (NormalPtr->GetCenter()) {
			StandardNormalPos();
			if (KeylVec.m_bPressedKeyTbl['R'] || CntlVec[0].fThumbLY > 0.5 && m_ModeMoveEnd &&CntlVec[0].fThumbLX < 0.3 && CntlVec[0].fThumbLX > -0.3
				&& m_StageMoveEnd && m_StickDown) {
				m_NormalStageCenter++;
				m_Flg = true;
				m_ElementNumTopFlg = true;
				m_StageMoveEnd = false;
				m_StickDown = false;
				m_StickUpUnder = true;
			}
			if (KeylVec.m_bPressedKeyTbl['T'] || CntlVec[0].fThumbLY < -0.5 &&CntlVec[0].fThumbLX < 0.3 && CntlVec[0].fThumbLX > -0.3
				&& m_ModeMoveEnd && m_StageMoveEnd && m_StickDown) {
				m_NormalStageCenter--;
				m_Flg = true;
				m_ElementNumTopFlg = true;
				m_StageMoveEnd = false;
				m_StickDown = false;
				m_StickUpUnder = false;

			}
			if (m_NormalStageCenter > 7) {
				m_NormalStageCenter = 0;
			}
			if (m_NormalStageCenter < 0) {
				m_NormalStageCenter = 7;
			}
			switch (m_NormalStageCenter)
			{
			case 0:
				ElementNum(0, 7, m_NormalStageCenter);
				NormalScale();
				NormalMove();
				m_CenterStageNum = 5;
				break;
			case 1:
				ElementNum(0, 7, m_NormalStageCenter);
				NormalScale();
				NormalMove();
				m_CenterStageNum = 6;
				break;
			case 2:
				ElementNum(0, 7, m_NormalStageCenter);
				NormalScale();
				NormalMove();
				m_CenterStageNum = 7;
				break;
			case 3:
				ElementNum(0, 7, m_NormalStageCenter);
				NormalScale();
				NormalMove();
				m_CenterStageNum = 8;
				break;
			case 4:
				ElementNum(0, 7, m_NormalStageCenter);
				NormalScale();
				NormalMove();
				m_CenterStageNum = 9;
				break;
			case 5:
				ElementNum(0, 7, m_NormalStageCenter);
				NormalScale();
				NormalMove();
				m_CenterStageNum = 10;
				break;
			case 6:
				ElementNum(0, 7, m_NormalStageCenter);
				NormalScale();
				NormalMove();
				m_CenterStageNum = 11;
				break;
			case 7:
				ElementNum(0, 7, m_NormalStageCenter);
				NormalScale();
				NormalMove();
				m_CenterStageNum = 12;
				break;

			}
		}
		NormalSideMove();
	}
	//�n�[�h�I���ړ����ĂԂƂ�
	void StageModeControl::HardSelect() {
		auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//��Փx�n�[�h���Z���^�[�ɂ�������X�e�[�W�I�����o����
		if (HardPtr->GetCenter()) {
			StandardHardPos();
			if (CntlVec[0].fThumbLY < 0.3 && CntlVec[0].fThumbLY > -0.3 && m_StickDown == false) {
				m_StickDown = true;
			}

			if (KeylVec.m_bPressedKeyTbl['R'] || CntlVec[0].fThumbLY > 0.5 && m_ModeMoveEnd &&CntlVec[0].fThumbLX < 0.3 && CntlVec[0].fThumbLX > -0.3
				&& m_StageMoveEnd && m_StickDown) {
				m_HardStageCenter++;
				m_Flg = true;
				m_ElementNumTopFlg = true;
				m_StageMoveEnd = false;
				m_StickDown = false;
				m_StickUpUnder = true;
			}
			if (KeylVec.m_bPressedKeyTbl['T'] || CntlVec[0].fThumbLY < -0.5 &&CntlVec[0].fThumbLX < 0.3 && CntlVec[0].fThumbLX > -0.3
				&& m_ModeMoveEnd && m_StageMoveEnd && m_StickDown) {
				m_HardStageCenter--;
				m_Flg = true;
				m_ElementNumTopFlg = true;
				m_StageMoveEnd = false;
				m_StickDown = false;
				m_StickUpUnder = false;
			}
		}
		if (m_HardStageCenter > 3) {
			m_HardStageCenter = 0;
		}
		if (m_HardStageCenter < 0) {
			m_HardStageCenter = 3;
		}
		switch (m_HardStageCenter)
		{
		case 0:
			ElementNum(0, 3, m_HardStageCenter);
			HardScale();
			HardMove();
			m_CenterStageNum = 13;
			break;
		case 1:
			ElementNum(0, 3, m_HardStageCenter);
			HardScale();
			HardMove();
			m_CenterStageNum = 14;
			break;
		case 2:
			ElementNum(0, 3, m_HardStageCenter);
			HardScale();
			HardMove();
			m_CenterStageNum = 15;
			break;
		case 3:
			ElementNum(0, 3, m_HardStageCenter);
			HardScale();
			HardMove();
			m_CenterStageNum = 16;
			break;
		}
	}
	//�ړ����� Center��������Z���^�[�� UP���Z���^�[�����Ɉړ��@Down��������Z���^�[�Ɉړ�
	//�e��Փx�̃X�e�[�W�ړ�
	void StageModeControl::EasyMove() {
		//�ړ�����v�f�ԍ�
		m_Center = m_Easy[m_ElementCenter]->GetComponent<Transform>()->GetPosition();
		m_Up = m_Easy[m_ElementUp]->GetComponent<Transform>()->GetPosition();
		m_Down = m_Easy[m_ElementDown]->GetComponent<Transform>()->GetPosition();
		//	m_Top = m_Easy[m_ElementTop]->GetComponent<Transform>()->GetPosition();
		//�������ړ�������ύX
		if (m_StickUpUnder == false) {
			m_MoveSpeed = -20.0f;
			m_EasyOtherPos = m_EasyPosUP;
		}
		else if (m_StickUpUnder == true) {
			m_MoveSpeed = 20.0f;
			m_EasyOtherPos = m_EasyPosDown;

		}
		//��L�ɓ��Ă͂܂�Ȃ����̌��o�ƈړ�
		for (int i = 0; i < 4; i++) {
			if (m_ElementUp != i && m_ElementCenter != i && m_ElementDown != i /*&& m_ElementTop != i*/) {
				m_Easy[i]->GetComponent<Transform>()->SetPosition(m_EasyOtherPos);
				m_Easy[i]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);

			}
		}

		//�ړ����� �Z���^�[�ړ����ĂȂ�������
		if (m_Center.y != m_EasyPosCenter.y) {
			m_Center.y += m_MoveSpeed;
			m_Easy[m_ElementCenter]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Easy[m_ElementCenter]->GetComponent<Transform>()->SetPosition(m_Center);

			if (m_Center.y >= m_EasyPosCenter.y - 20.0f &&m_Center.y <= m_EasyPosCenter.y + 20.0f) {
				m_Easy[m_ElementCenter]->GetComponent<Transform>()->SetPosition(m_EasyPosCenter);
			}

			/*if (m_Center.y >= m_EasyPosCenter.y && m_StickUpUnder == true) {
			m_Easy[m_ElementCenter]->GetComponent<Transform>()->SetPosition(m_EasyPosCenter);
			m_StageMoveEnd = true;
			}
			else if (m_Center.y <= m_EasyPosCenter.y && m_StickUpUnder == false) {
			m_Easy[m_ElementCenter]->GetComponent<Transform>()->SetPosition(m_EasyPosCenter);
			m_StageMoveEnd = true;
			}*/

		}


		//��Ɉړ����ĂȂ�������
		if (m_Up.y != m_EasyPosUP.y) {
			m_Up.y += m_MoveSpeed;
			m_Easy[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Easy[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_Up);
		}
		//���E�l�̏���
		if (m_Up.y >= m_EasyPosUP.y) {
			m_Easy[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Easy[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_EasyPosUP);
			if (m_StickUpUnder == true) {
				m_StageMoveEnd = true;
			}

		}
		if (m_Up.y <= m_EasyPosDown.y) {
			m_Easy[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Easy[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_EasyPosUP);
		}
		//���Ɉړ����ĂȂ�������
		if (m_Down.y != m_EasyPosDown.y) {
			m_Down.y += m_MoveSpeed;
			m_Easy[m_ElementDown]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Easy[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_Down);
		}
		//���E�l�̏���
		if (m_Down.y <= m_EasyPosDown.y) {
			m_Easy[m_ElementDown]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Easy[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_EasyPosDown);
			if (m_StickUpUnder == false) {
				m_StageMoveEnd = true;
			}

		}
		if (m_Down.y >= m_EasyPosUP.y) {
			m_Easy[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_EasyPosDown);
		}


		////�����ĂȂ���̕����Ɉړ����ĂȂ�������
		//if (m_Flg == true) {
		//	if (m_Top.y != m_EasyTopPos.y) {
		//		//��ɂ����ď���
		//		m_Top.y += m_MoveSpeed;
		//		m_Easy[m_ElementTop]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
		//		m_Easy[m_ElementTop]->GetComponent<Transform>()->SetPosition(m_Top);
		//	}
		//	if (m_Top.y >= m_EasyTopPos.y) {
		//		m_Flg = false;
		//		m_Easy[m_ElementTop]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
		//		m_Easy[m_ElementTop]->GetComponent<Transform>()->SetPosition(m_EasyOtherPos);
		//	}
		//}

	}
	void StageModeControl::NormalMove() {
		//auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		m_Center = m_Normal[m_ElementCenter]->GetComponent<Transform>()->GetPosition();
		m_Up = m_Normal[m_ElementUp]->GetComponent<Transform>()->GetPosition();
		m_Down = m_Normal[m_ElementDown]->GetComponent<Transform>()->GetPosition();
		//m_Top = m_Normal[m_ElementTop]->GetComponent<Transform>()->GetPosition();
		if (m_StickUpUnder == false) {
			m_MoveSpeed = -20.0f;
			m_NormalOtherPos = m_NormalPosUP;
		}
		else if (m_StickUpUnder == true) {
			m_MoveSpeed = 20.0f;
			m_NormalOtherPos = m_NormalPosDown;
		}
		//��L�ɓ��Ă͂܂�Ȃ����̌��o�ƈړ�
		for (int i = 0; i < 8; i++) {
			if (m_ElementUp != i && m_ElementCenter != i && m_ElementDown != i /*&& m_ElementTop != i*/) {
				m_Normal[i]->GetComponent<Transform>()->SetPosition(m_NormalOtherPos);
				m_Normal[i]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);

			}
		}

		//�ړ����� �Z���^�[�ړ����ĂȂ�������
		if (m_Center.y != m_NormalPosCenter.y) {
			m_Center.y += m_MoveSpeed;
			m_Normal[m_ElementCenter]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Normal[m_ElementCenter]->GetComponent<Transform>()->SetPosition(m_Center);
			if (m_Center.y >= m_NormalPosCenter.y - 20.0f &&m_Center.y <= m_NormalPosCenter.y + 20.0f) {
				m_Normal[m_ElementCenter]->GetComponent<Transform>()->SetPosition(m_NormalPosCenter);
			}
		}



		//��Ɉړ����ĂȂ�������
		if (m_Up.y != m_NormalPosUP.y) {
			m_Up.y += m_MoveSpeed;
			m_Normal[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Normal[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_Up);
		}
		if (m_Up.y >= m_NormalPosUP.y) {
			m_Normal[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Normal[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_NormalPosUP);
			if (m_StickUpUnder == true) {
				m_StageMoveEnd = true;
			}
		}
		if (m_Up.y <= m_NormalPosDown.y) {
			m_Normal[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Normal[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_NormalPosUP);
		}

		//���Ɉړ����ĂȂ�������
		if (m_Down.y != m_NormalPosDown.y) {
			m_Down.y += m_MoveSpeed;
			m_Normal[m_ElementDown]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Normal[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_Down);
		}
		if (m_Down.y <= m_NormalPosDown.y) {
			m_Normal[m_ElementDown]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Normal[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_NormalPosDown);
			if (m_StickUpUnder == false) {
				m_StageMoveEnd = true;
			}
		}
		if (m_Down.y >= m_NormalPosUP.y) {
			m_Normal[m_ElementDown]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Normal[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_NormalPosDown);
		}

		////�����ĂȂ���̕����Ɉړ����ĂȂ�������
		//if (m_Flg == true) {
		//	if (m_Top.y != m_NormalTopPos.y) {
		//		//��ɂ����ď���
		//		m_Top.y += m_MoveSpeed;
		//		m_Normal[m_ElementTop]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
		//		m_Normal[m_ElementTop]->GetComponent<Transform>()->SetPosition(m_Top);
		//	}
		//	if (m_Top.y >= m_NormalTopPos.y) {
		//		m_Flg = false;
		//		m_Normal[m_ElementTop]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
		//		m_Normal[m_ElementTop]->GetComponent<Transform>()->SetPosition(m_NormalOtherPos);
		//	}
		//}

	}
	void StageModeControl::HardMove() {
		m_Center = m_Hard[m_ElementCenter]->GetComponent<Transform>()->GetPosition();
		m_Up = m_Hard[m_ElementUp]->GetComponent<Transform>()->GetPosition();
		m_Down = m_Hard[m_ElementDown]->GetComponent<Transform>()->GetPosition();
		//	m_Top = m_Hard[m_ElementTop]->GetComponent<Transform>()->GetPosition();
		if (m_StickUpUnder == false) {
			m_MoveSpeed = -20.0f;
			m_HardOtherPos = m_HardPosUP;
		}
		else if (m_StickUpUnder == true) {
			m_MoveSpeed = 20.0f;
			m_HardOtherPos = m_HardPosDown;
		}

		//��L�ɓ��Ă͂܂�Ȃ����̌��o�ƈړ�
		for (int i = 0; i < 4; i++) {
			if (m_ElementUp != i && m_ElementCenter != i && m_ElementDown != i/* && m_ElementTop != i*/) {
				m_Hard[i]->GetComponent<Transform>()->SetPosition(m_HardOtherPos);
				m_Hard[i]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);

			}
		}

		//�ړ����� �Z���^�[�ړ����ĂȂ�������
		if (m_Center.y != m_HardPosCenter.y) {
			m_Center.y += m_MoveSpeed;
			m_Hard[m_ElementCenter]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Hard[m_ElementCenter]->GetComponent<Transform>()->SetPosition(m_Center);
			if (m_Center.y >= m_HardPosCenter.y - 20.0f &&m_Center.y <= m_HardPosCenter.y + 20.0f) {
				m_Hard[m_ElementCenter]->GetComponent<Transform>()->SetPosition(m_HardPosCenter);
				//m_StageMoveEnd = true;
			}
		}


		//��Ɉړ����ĂȂ�������
		if (m_Up.y != m_HardPosUP.y) {
			m_Up.y += m_MoveSpeed;
			m_Hard[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Hard[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_Up);

		}
		//���E�l�̏���
		if (m_Up.y >= m_HardPosUP.y) {
			m_Hard[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Hard[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_HardPosUP);
			if (m_StickUpUnder == true) {
				m_StageMoveEnd = true;
			}
		}
		if (m_Up.y <= m_HardPosDown.y) {
			m_Hard[m_ElementUp]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Hard[m_ElementUp]->GetComponent<Transform>()->SetPosition(m_HardPosUP);
		}
		//���Ɉړ����ĂȂ�������
		if (m_Down.y != m_HardPosDown.y) {
			m_Down.y += m_MoveSpeed;
			m_Hard[m_ElementDown]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
			m_Hard[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_Down);

		}
		//���E�l�̏���
		if (m_Down.y <= m_HardPosDown.y) {
			m_Hard[m_ElementDown]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			m_Hard[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_HardPosDown);
			if (m_StickUpUnder == false) {
				m_StageMoveEnd = true;
			}
		}
		if (m_Down.y >= m_HardPosUP.y) {
			m_Hard[m_ElementDown]->GetComponent<Transform>()->SetPosition(m_HardPosDown);
		}
		////�����ĂȂ���̕����Ɉړ����ĂȂ�������
		//if (m_Flg == true) {
		//	if (m_Top.y != m_HardTopPos.y) {
		//		//��ɂ����ď���
		//		m_Top.y += m_MoveSpeed;
		//		m_Hard[m_ElementTop]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
		//		m_Hard[m_ElementTop]->GetComponent<Transform>()->SetPosition(m_Top);
		//	}
		//	if (m_Top.y >= m_HardTopPos.y) {
		//		m_Flg = false;
		//		m_Hard[m_ElementTop]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
		//		m_Hard[m_ElementTop]->GetComponent<Transform>()->SetPosition(m_HardOtherPos);
		//	}
		//}

	}
	//�g��k��
	void StageModeControl::EasyScale() {
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		if (EasyPtr->GetCenter()) {
			m_Easy[m_ElementCenter]->GetComponent<Transform>()->SetScale(m_CenterScalse);
			m_Easy[m_ElementUp]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
			m_Easy[m_ElementDown]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
		}
		else
		{
			for (int i = 0; i < 4; i++) {
				m_Easy[i]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
			}
		}
	}
	void StageModeControl::NormalScale() {
		auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		if (NormalPtr->GetCenter()) {
			m_Normal[m_ElementCenter]->GetComponent<Transform>()->SetScale(m_CenterScalse);
			m_Normal[m_ElementUp]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
			m_Normal[m_ElementDown]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
		}
		else {
			for (int i = 0; i < 8; i++) {
				m_Normal[i]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
			}
		}
	}
	void StageModeControl::HardScale() {
		auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
		if (HardPtr->GetCenter()) {
			m_Hard[m_ElementCenter]->GetComponent<Transform>()->SetScale(m_CenterScalse);
			m_Hard[m_ElementUp]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
			m_Hard[m_ElementDown]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
		}
		else {
			for (int i = 0; i < 4; i++) {
				m_Hard[i]->GetComponent<Transform>()->SetScale(m_NoCenterScalse);
			}
		}
	}
	//�ŏ����ő�l�𒴂��Ă��Ȃ���������@�����Ă��璲������return����
	int StageModeControl::ExceedNum(int Mini, int Max, int Num) {
		if (Num < Mini)
		{
			//�ŏ��l��艺�������ő�l��Ԃ�
			return Max;
		}
		else if (Num >Max)
		{
			//�ő�l����������ŏ��l��Ԃ�
			return Mini;
		}
		else
		{
			return Num;
		}
	}
	//�Z���^�[����v�f�������o
	void StageModeControl::ElementNum(int Mini, int Max, int CenterNum) {
		m_ElementCenter = CenterNum;
		m_ElementUp = CenterNum - 1;
		m_ElementDown = CenterNum + 1;
		if (m_ElementNumTopFlg == true) {
			m_ElementTop = m_ElementCenter - 2;
			m_ElementUp;
			m_ElementDown;
		}
		else if (m_ElementNumTopFlg == false) {
			//1���ڈȍ~�̒l���㏑������Ȃ��悤�ɂ���
			m_ElementTop = m_ElementTop;
		}
		if (m_ElementUp < Mini) {
			m_ElementUp = Max;
		}

		if (m_ElementDown > Max) {
			m_ElementDown = Mini;
		}

		if (m_ElementNumTopFlg == true) {
			//Up�̏�Ɉړ�������v�f��
			if (m_ElementTop < Mini) {
				if (m_ElementTop <= -2) {
					m_ElementTop = Max - 1;
				}
				else if (m_ElementTop <= -1) {
					m_ElementTop = Max;
				}
			}
			m_ElementNumTopFlg = false;
		}



	}
	//���E�̈ړ� �������e�@�K�؂ȓ�Փx�̉��̈ړ�
	void StageModeControl::EasySideMove() {
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		auto EasyTrans = EasyPtr->GetComponent<Transform>();
		auto EasyPos = EasyTrans->GetPosition();
		float E_MoveSpeed = 1.0f;
		/*if (EasyPtr->GetCenter()) {
		E_Pos = Vector3(10, 1, 0);
		}
		else if (EasyPos.x <= -310) {
		E_Pos = Vector3(-10, 1, 0);
		}
		else {
		E_Pos = Vector3(0, 1, 0);
		}*/
		for (int i = 0; i < 4; i++) {
			auto Pos = m_Easy[i]->GetComponent<Transform>()->GetPosition();
			m_Easy[i]->GetComponent<Transform>()->SetPosition(EasyPos.x, Pos.y, Pos.z);
		}
	}
	void StageModeControl::NormalSideMove() {
		auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		auto NormalTrans = NormalPtr->GetComponent<Transform>();
		auto NormalPos = NormalTrans->GetPosition();
		/*Vector3  N_Pos = Vector3(0, 0, 0);
		if (NormalPtr->GetCenter()) {
		N_Pos = Vector3(0, 1, 0);
		}
		else if (NormalPos.x <= -320) {
		N_Pos = Vector3(-10, 1, 0);
		}
		else {
		N_Pos = Vector3(10, 1, 0);
		}*/
		for (int i = 0; i < 8; i++) {
			auto Pos = m_Normal[i]->GetComponent<Transform>()->GetPosition();
			m_Normal[i]->GetComponent<Transform>()->SetPosition(NormalPos.x, Pos.y, Pos.z);
		}
	}
	void StageModeControl::HardSideMove() {
		auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
		auto HardTrans = HardPtr->GetComponent<Transform>();
		auto HardPos = HardTrans->GetPosition();
		/*Vector3 H_Pos = Vector3(0, 0, 0);
		if (HardPtr->GetCenter()) {
		H_Pos = Vector3(0, 1, 0);
		}
		else if (HardPos.x <= -320) {
		H_Pos = Vector3(-10, 1, 0);
		}
		else {
		H_Pos = Vector3(10, 1, 0);
		}*/
		for (int i = 0; i < 4; i++) {
			auto Pos = m_Hard[i]->GetComponent<Transform>()->GetPosition();
			m_Hard[i]->GetComponent<Transform>()->SetPosition(HardPos.x, Pos.y, Pos.z);
		}
	}
	//ModeSelect�N���X����Z���^�[�̃t���O���擾���K�؂ȓ�Փx�̈ړ����o����悤�ɂ���
	void StageModeControl::StageMove() {
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
		if (EasyPtr->GetCenter()) {
			EasySelect();
		}
		else {
			EasyScale();
		}
		if (NormalPtr->GetCenter()) {
			NormalSelect();
		}
		else {
			NormalScale();
		}
		if (HardPtr->GetCenter()) {
			HardSelect();
		}
		else {
			HardScale();
		}

		EasySideMove();
		NormalSideMove();
		HardSideMove();


	}


	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�X�v���C�g������Ă�t���[��
	//--------------------------------------------------------------------------------------
	ModeSelect::ModeSelect(const shared_ptr<Stage>& StagePtr, const Vector3& Pos, const Vector3& Scale, const int& ModeNum, const bool& Centerflg, const int& MoveNum) :
		GameObject(StagePtr),
		m_Pos(Pos),
		m_Scale(Scale),
		m_ModeNum(ModeNum),
		m_Centerflg(Centerflg),
		m_MoveNum(MoveNum)
	{}

	void ModeSelect::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(90 * XM_PI / 180, 0, 0);
		auto Draw = AddComponent<PCTSpriteDraw>();
		//�e�N�X�`���̕���
		if (m_ModeNum == 1) {
			Draw->SetTextureResource(L"flame_TX");
			SetDrawLayer(2);
		}
		else if (m_ModeNum == 2) {
			Draw->SetTextureResource(L"flame_TX");
			SetDrawLayer(1);
		}
		else if (m_ModeNum == 3) {
			Draw->SetTextureResource(L"flame_TX");
			SetDrawLayer(1);
		}
		SetAlphaActive(true);
		m_NowModeNum = 1;
		m_Speed = 10.0f;
		//���S
		m_CenterPos = Vector3(0, -60, -4);
		//�E
		m_RightPos = Vector3(320, -60, -4);
		//��
		m_LeftPos = Vector3(-320, -60, -4);
		// Draw->SetDrawActive(false);
		SetDrawLayer(2);
		auto pMultiSoundEffect = AddComponent<MultiSoundEffect>();
		pMultiSoundEffect->AddAudioResource(L"SaidSelectSe_SE");
		m_OneSE = false;
	}
	void ModeSelect::OnUpdate() {
		ModeSelectMove();
	}

	//�ړ��֐�
	void ModeSelect::ModeSelectMove() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto PtrStageModeControl = GetStage()->GetSharedGameObject<StageModeControl>(L"StageModeControl", false);
		if (CntlVec[0].fThumbLX > -0.2f &&  CntlVec[0].fThumbLX < 0.2f &&
			CntlVec[0].fThumbLY > -0.2f &&  CntlVec[0].fThumbLY < 0.2f && m_StickDown == false) {
			m_StickDown = true;
		}

		if (PtrStageModeControl->ModeMoveEnd()) {
			if (KeylVec.m_bPressedKeyTbl['W'] || CntlVec[0].fThumbLX < -0.5f&&CntlVec[0].fThumbLY < 0.1 && CntlVec[0].fThumbLY > -0.1f && PtrStageModeControl->ModeMoveEnd() && PtrStageModeControl->StageEndMove() && m_StickDown) {
				if (m_OneSE == false) {
					auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
					pMultiSoundEffect->Start(L"SaidSelectSe_SE", 0, 0.5f);
					m_OneSE = true;
				}
				m_EndMove = false;
				m_Speed = 10.0f;
				m_MoveNum++;
				m_StickDown = false;
				m_StickLift = true;
			}
			if (KeylVec.m_bPressedKeyTbl['E'] || CntlVec[0].fThumbLX > 0.5f &&CntlVec[0].fThumbLY < 0.1 && CntlVec[0].fThumbLY > -0.1f&& PtrStageModeControl->ModeMoveEnd() && PtrStageModeControl->StageEndMove() && m_StickDown) {
				if (m_OneSE == false) {
					auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
					pMultiSoundEffect->Start(L"SaidSelectSe_SE", 0, 0.5f);
					m_OneSE = true;
				}
				m_EndMove = false;
				m_Speed = 10.0f;
				m_MoveNum--;
				m_StickDown = false;
				m_StickLift = false;
			}
			if (m_MoveNum > 3) {
				m_MoveNum = 1;
			}
			if (m_MoveNum <= 0) {
				m_MoveNum = 3;
			}
		}
		else {
			m_OneSE = false;
		}

		switch (m_MoveNum)
		{
		case 1://�Z���^�[�Ɉړ�
			m_Centerflg = true;
			m_Liftflg = false;
			m_Rightflg = false;
			CenterMove();
			SetDrawLayer(2);
			break;
		case 2://���Ɉړ�
			m_Centerflg = false;
			m_Liftflg = true;
			m_Rightflg = false;
			LiftMove();
			SetDrawLayer(3);
			break;
		case 3://�E�Ɉړ�
			m_Centerflg = false;
			m_Liftflg = false;
			m_Rightflg = true;
			RightMove();
			SetDrawLayer(3);
			break;
		}


	}
	//�Z���^�[�Ɉړ�
	void ModeSelect::CenterMove() {
		auto Draw = GetComponent<PCTSpriteDraw>();
		Draw->SetDiffuse(Color4(1.0f, 1.0f, 1.0f, 0.5f));
		auto Pos = GetComponent<Transform>()->GetPosition();
		//�E����Z���^�[
		if (m_StickLift == true) {
			if (GetComponent<Transform>()->GetPosition().x <= m_CenterPos.x) {
				GetComponent<Transform>()->SetPosition(m_CenterPos);
				m_Speed = 0;
				m_EndMove = true;
			}
			else {
				Pos.x -= m_Speed;
				GetComponent<Transform>()->SetPosition(Pos);
			}
		}
		else {
			if (GetComponent<Transform>()->GetPosition().x >= m_CenterPos.x) {
				GetComponent<Transform>()->SetPosition(m_CenterPos);
				m_Speed = 0;
				m_EndMove = true;
			}
			else {

				Pos.x += m_Speed;
				GetComponent<Transform>()->SetPosition(Pos);
			}
		}
	}
	//���Ɉړ�
	void ModeSelect::LiftMove() {
		auto Draw = GetComponent<PCTSpriteDraw>();
		Draw->SetDiffuse(Color4(1.0f, 1.0f, 1.0f, 0.3));
		auto Pos = GetComponent<Transform>()->GetPosition();
		//��������������Ȃ�����
		if (GetComponent<Transform>()->GetPosition().x <= m_LeftPos.x) {
			GetComponent<Transform>()->SetPosition(m_LeftPos);
			m_Speed = 0;
			m_EndMove = true;
		}
		else {
			Pos.x -= m_Speed;
			GetComponent<Transform>()->SetPosition(Pos);
		}
	}
	//�E�Ɉړ�
	void ModeSelect::RightMove() {
		auto Draw = GetComponent<PCTSpriteDraw>();
		Draw->SetDiffuse(Color4(1.0f, 1.0f, 1.0f, 0.3));
		auto Pos = GetComponent<Transform>()->GetPosition();
		//��E�����傫���Ȃ�����
		if (GetComponent<Transform>()->GetPosition().x >= m_RightPos.x) {
			GetComponent<Transform>()->SetPosition(m_RightPos);
			m_Speed = 0;
			m_EndMove = true;
		}
		else {
			//������E
			Pos.x += m_Speed;
			GetComponent<Transform>()->SetPosition(Pos);
		}
	}





	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�̔�
	//--------------------------------------------------------------------------------------
	StageBox::StageBox(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, int num) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_stagenumber(num)
	{}

	void StageBox::OnCreate()
	{
		//���W�ݒ�
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(90 * 3.14159265f / 180, 0, 0);

		//�`��ݒ�
		auto PtrDraw = AddComponent<PCTSpriteDraw>();
		//PtrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		//PtrDraw->SetDrawActive(false);
		wstring stageString = L"STAGEBOX_" + Util::IntToWStr(m_stagenumber) + L"_TX";
		PtrDraw->SetTextureResource(stageString);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetFixed(true);

		PtrCol->SetDrawActive(false);
		SetDrawLayer(4);
		SetAlphaActive(true);
	}

	void StageBox::OnUpdate()
	{

		////�擾
		//auto PtrCol = GetComponent<CollisionSphere>();
		//
		//		if (!(PtrCol->GetUpdateActive())) {
		//			PtrCol->SetFixed(false);
		//		}
		//
		////�v���C���[���P�̈ȏ㓖�����Ă�Ƃ��̂ݏ���
		//if (m_PlayerHitFlg)
		//{
		//	//�v���C���[���������Ă鐔���Q��
		//	if (m_PlayerHitNum == 2)
		//	{
		//		//A�{�^��������Ă邩�̏����͂����BA�͂Ȃ���Ȃ���Έ�����Ȃ�����
		//		CheckGo();
		//	}
		//	//�Ȃ�ɂ��������ĂȂ����
		//	else if(m_PlayerHitNum == 0)
		//	{
		//		//�]�v�ȏ������Ȃ��悤�ɐ؂��Ă���(�{���̓A�b�v�f�[�g���̎~�߂�̂������񂾂��ǃo�O��������)
		//		m_PlayerHitFlg = false;
		//	}
		//	m_PlayerHitNum = 0;
		//}
	}

	void StageBox::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec)
	{
		//�v���C���[�ȊO���������Ȃ��͂��Ȃ̂łƂ肠��������������v���C���[����
		for (auto obj : OtherVec)
		{
			m_PlayerHitNum++;

			//�v���C���[�̗����t���O�N��
			GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFlgOn();
		}
		if (m_PlayerHitNum > 0)
		{
			m_PlayerHitFlg = true;
		}
	}

	void StageBox::CheckGo()
	{
		//���̈ʒu�ɖ߂�t���O�N��
		//GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFinishFlgOn();

		//��������A�b�v�f�[�g�~�߂�
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetPlayerUpdate(false);

		//�m�F�E�B���h�E�N��
		GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->OpenCheck();
		GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->SetStageNumber(m_stagenumber);
		GetStage()->GetSharedGameObject<EnemyCount>(L"Count", false)->Count();
	}

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�s�����m�F����I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	GoStageCheck::GoStageCheck(const shared_ptr<Stage>& StagePtr, Vector2 scale) :
		GameObject(StagePtr),
		m_InitScale(scale)
	{}

	void GoStageCheck::OnCreate()
	{
		GetStage()->SetSharedGameObject(L"Go", GetStage()->AddGameObject<GoBackSprite>(Vector2(150, 75), Vector2(-320, -190), 1));
		GetStage()->SetSharedGameObject(L"Back", GetStage()->AddGameObject<GoBackSprite>(Vector2(150, 75), Vector2(0, -190), 2));

		//�w�i�쐬------------------------------------
		auto CheckBack = GetStage()->AddGameObject<GameObject>();

		//���W
		auto Trans = CheckBack->AddComponent<Transform>();
		Trans->SetPosition(-100, -30, 0);
		Trans->SetScale(Vector3(1140, 740, 1));
		Trans->SetRotation(0, 0, 0);

		//�`��
		auto Draw = CheckBack->AddComponent<PCTSpriteDraw>();
		//Draw->SetTextureResource(L"SELECTCHECK_FLAME_TX");

		//���C���[�ݒ�
		CheckBack->SetDrawLayer(5);
		//�����x�L����
		CheckBack->SetAlphaActive(true);

		//�����Ƃ�
		CheckBack->SetDrawActive(false);

		m_CheckBack = CheckBack;

		//���g�쐬----------------------------------------
		auto CheckBackIn = GetStage()->AddGameObject<GameObject>();

		//���W
		auto CITrans = CheckBackIn->AddComponent<Transform>();
		CITrans->SetPosition(0, 0, 0);
		CITrans->SetScale(Vector3(1280, 720, 1));
		CITrans->SetRotation(0, 0, 0);

		//�`��
		auto CIDraw = CheckBackIn->AddComponent<PCTSpriteDraw>();
		CIDraw->SetTextureResource(L"SERECT_TX");

		//���C���[�ݒ�
		CheckBackIn->SetDrawLayer(6);
		//�����x�L����
		CheckBackIn->SetAlphaActive(true);

		//�����Ƃ�
		CheckBackIn->SetDrawActive(false);

		m_CheckBoxIn = CheckBackIn;



		//�J�[�\���쐬------------------------------------
		auto CursorSprite = GetStage()->AddGameObject<GameObject>();
		//���W
		auto CTrans = CursorSprite->AddComponent<Transform>();
		CTrans->SetPosition(-320, -230, 0);
		CTrans->SetScale(100, 50, 1);
		CTrans->SetRotation(0, 0, 0);

		//�`��
		auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
		CDraw->SetTextureResource(L"SELECT_CURSOR_TX");

		//���C���[�ݒ�
		CursorSprite->SetDrawLayer(7);

		//�����x�L����
		CursorSprite->SetAlphaActive(true);

		//�����Ƃ�
		CursorSprite->SetDrawActive(false);

		m_Cursor = CursorSprite;


		//Abe20170525
		//���ꂼ��̐����쐬
		//�ˌ�
		auto tacklenum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(-240, 60), Vector2(100, 100), 7);
		tacklenum->SetNumDraw(false);
		m_TackleNumSpr = tacklenum;
		//��
		auto shotnum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(100, 60), Vector2(100, 100), 7);
		shotnum->SetNumDraw(false);
		m_ShotNumSpr = shotnum;
		//�Ă�
		auto terenum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(-240, -115), Vector2(100, 100), 7);
		terenum->SetNumDraw(false);
		m_TerepoNumSpr = terenum;
		//��
		auto bombnum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(100, -115), Vector2(100, 100), 7);
		bombnum->SetNumDraw(false);
		m_BombNumSpr = bombnum;
		//Abe20170525

		//������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		SetCloseflg(false);
		//����SE
		auto pMultiSoundEffect = AddComponent<MultiSoundEffect>();
		pMultiSoundEffect->AddAudioResource(L"Pause_SE");
		m_OneSE = false;
	}

	void GoStageCheck::OnUpdate()
	{
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();

		if (m_Dispflg)
		{

			if (m_KeepPushing) {
				if (CntlVec[0].wButtons& XINPUT_GAMEPAD_A) {
					
					m_KeepApudh = true;
				}
				else if (!(CntlVec[0].wButtons& XINPUT_GAMEPAD_A)) {
					m_KeepApudh = false;
					m_KeepPushing = false;
					
				}
			}
			

			if (m_KeepPushing == false && m_KeepApudh == false) {
				//select�̃��j���[����A�{�^�����������
				if (CntlVec[0].wPressedButtons& XINPUT_GAMEPAD_A) {
					m_APush = true;
				}
				else {
					m_APush = false;
				}
			}
			

			if (CntlVec[0].bConnected)
			{
				//�R���g���[���[�����ɓ|���ꂽ��
				if (CntlVec[0].fThumbLX < -0.5f)
				{
					//�I������Yes
					m_selectnum = 1;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(-320, -230, 0));
					m_Cursor->GetComponent<Transform>()->SetScale(Vector3(100, 50, 1));
				}
				//�E
				else if (CntlVec[0].fThumbLX > 0.5f)
				{
					m_selectnum = 0;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(0, -230, 0));
					m_Cursor->GetComponent<Transform>()->SetScale(Vector3(200, 50, 1));
				}

				//A��B�{�^�������ꂽ��
				if (m_APush || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || KeylVec.m_bPressedKeyTbl['N'])
				{
					auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();

					switch (m_selectnum)
					{
						//No
					case 0:
						pMultiSoundEffect->Start(L"Pause_SE", 0, 1.0f);
						CloseCheck();
						break;
						//Yes
					case 1:
						GetStage()->GetSharedGameObject<SE>(L"TitleSE", false)->ASe();

						//�X�e�[�W�ԍ���Scene.cpp�ɓn��
						//====================================================
						//	�P�`�S(25,25)�@�T�`�P�Q(50,50)�@�P�R�`�P�U(75,75)
						//====================================================
						Vector2 StageSize;
						StageSize = Vector2(25, 25);
						if (m_stageNum >= 1 && m_stageNum <= 4)
						{
							StageSize = Vector2(25, 25);
						}
						else if (m_stageNum >= 5 && m_stageNum <= 12)
						{
							StageSize = Vector2(50, 50);
						}
						else if (m_stageNum >= 13 && m_stageNum <= 16)
						{
							StageSize = Vector2(75, 75);
						}

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						//�X�e�[�W�ԍ��Ɣԍ��ɂ������X�e�[�W�̑傫����n��
						ScenePtr->SetStageNumAndStageSize(m_stageNum, StageSize);
						PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						break;
					}
				}
			}
			else
			{
				//�R���g���[���[�����ɓ|���ꂽ��
				if (KeylVec.m_bPressedKeyTbl[VK_LEFT])
				{
					//�I������Yes
					m_selectnum = 1;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(-320, -230, 0));
					m_Cursor->GetComponent<Transform>()->SetScale(Vector3(100, 50, 1));
				}
				//�E
				else if (KeylVec.m_bPressedKeyTbl[VK_RIGHT])
				{
					m_selectnum = 0;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(0, -230, 0));
					m_Cursor->GetComponent<Transform>()->SetScale(Vector3(200, 50, 1));
				}

				//A��B�{�^�������ꂽ��
				if (KeylVec.m_bPressedKeyTbl['N'])
				{
					switch (m_selectnum)
					{
						//No
					case 0:
						CloseCheck();
						break;
						//Yes
					case 1:
						//�X�e�[�W�ԍ���Scene.cpp�ɓn��
						//====================================================
						//	�P�`�S(25,25)�@�T�`�P�Q(50,50)�@�P�R�`�P�U(75,75)
						//====================================================
						Vector2 StageSize;
						StageSize = Vector2(25, 25);
						if (m_stageNum >= 1 && m_stageNum <= 4)
						{
							StageSize = Vector2(25, 25);
						}
						else if (m_stageNum >= 5 && m_stageNum <= 12)
						{
							StageSize = Vector2(50, 50);
						}
						else if (m_stageNum >= 13 && m_stageNum <= 16)
						{
							StageSize = Vector2(75, 75);
						}

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						//�X�e�[�W�ԍ��Ɣԍ��ɂ������X�e�[�W�̑傫����n��
						ScenePtr->SetStageNumAndStageSize(m_stageNum, StageSize);
						PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						break;
					}
				}

			}
		}
	}

	//�N��
	void GoStageCheck::OpenCheck()
	{
		m_Dispflg = true;
		m_CheckBack->SetDrawActive(true);
		m_CheckBoxIn->SetDrawActive(true);
		m_Cursor->SetDrawActive(true);
		m_TackleNumSpr->SetNumDraw(true);
		m_ShotNumSpr->SetNumDraw(true);
		m_TerepoNumSpr->SetNumDraw(true);
		m_BombNumSpr->SetNumDraw(true);
		m_KeepPushing = true;
		m_KeepApudh = true;
		m_APush = false;
		GetStage()->GetSharedGameObject<GoBackSprite>(L"Go", false)->OnDisp(true);
		GetStage()->GetSharedGameObject<GoBackSprite>(L"Back", false)->OnDisp(true);
		auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
		pMultiSoundEffect->Start(L"Pause_SE", 0, 1.0f);

	}

	//�I��
	void GoStageCheck::CloseCheck()
	{
		auto PtrStageModeControl = GetStage()->GetSharedGameObject<StageModeControl>(L"StageModeControl", false);

		m_Dispflg = false;
		m_CheckBack->SetDrawActive(false);
		m_CheckBoxIn->SetDrawActive(false);
		m_Cursor->SetDrawActive(false);
		m_TackleNumSpr->SetNumDraw(false);
		m_ShotNumSpr->SetNumDraw(false);
		m_TerepoNumSpr->SetNumDraw(false);
		m_BombNumSpr->SetNumDraw(false);
		SetCloseflg(false);
		PtrStageModeControl->SetUpdateActive(true);
		m_KeepPushing = true;
		m_KeepApudh = true;
		m_APush = false;
		GetStage()->GetSharedGameObject<GoBackSprite>(L"Go", false)->OnDisp(false);
		GetStage()->GetSharedGameObject<GoBackSprite>(L"Back", false)->OnDisp(false);


		//�X�R�A��\��
		GetStage()->GetSharedGameObject<ScoreDisplay>(L"ScoreDisplay", false)->Delete();


		//���N������Ƃ��p�ɏ�����
		//Yes�ɏ�����
		m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(-320, -230, 0));
		m_Cursor->GetComponent<Transform>()->SetScale(Vector3(100, 50, 1));
		m_selectnum = 1;

		//�v���C���[�̃A�b�v�f�[�g�ĊJ
		//GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetUpdateActive(true);
		GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false)->SetUpdateActive(true);
		GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false)->SetUpdateActive(true);
		GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false)->SetUpdateActive(true);
		//���ꂳ����
		//GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFinishFlgOn();
		//GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetChangeNum(3);
	}
	//Abe20170421

	//Abe20170525
	void GoStageCheck::SetEnemyNum(int tackle, int shot, int terepo, int bomb)
	{
		//�����̃X�v���C�g�ύX
		m_TackleNumSpr->SetNum(tackle);
		m_ShotNumSpr->SetNum(shot);
		m_TerepoNumSpr->SetNum(terepo);
		m_BombNumSpr->SetNum(bomb);
	}
	//Abe20170427
	//--------------------------------------------------------------------------------------
	//	�n��
	//--------------------------------------------------------------------------------------
	SelectGroud::SelectGroud(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale) :
		GameObject(StagePtr),
		m_Pos(pos),
		m_Scale(scale)
	{}

	void SelectGroud::OnCreate()
	{
		//�K�v�Œ��------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(0, 0, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"STAGESELECTGROUND_TX");
		//�K�v�Œ��------


	}
	//Abe20170427

	//Abe20170526
	//--------------------------------------------------------------------------------------
	//	�n�ʂɓ\����
	//--------------------------------------------------------------------------------------
	SelectGroundSquare::SelectGroundSquare(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txt, float rot) :
		GameObject(StagePtr),
		m_Pos(pos),
		m_Scale(scale),
		m_Text(txt),
		m_rot(rot)
	{}

	void SelectGroundSquare::OnCreate()
	{
		//�K�v�Œ��------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(m_Text);
		//�K�v�Œ��------

		SetDrawLayer(1);
		SetAlphaActive(true);
	}
	//Abe20170526

	//Abe20170529
	//--------------------------------------------------------------------------------------
	//	�n�ʂɓ\����(SS��)
	//--------------------------------------------------------------------------------------
	SelectGroundSquareSS::SelectGroundSquareSS(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, float rot) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + txtdire, txtname, L"anime_1"),
		m_Pos(pos),
		m_Scale(scale),
		m_rot(rot)
	{}

	void SelectGroundSquareSS::OnCreate()
	{
		/*
		//�K�v�Œ��------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(m_Text);
		//�K�v�Œ��------

		SetDrawLayer(1);
		SetAlphaActive(true);
		*/
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

		//�A�j���[�V�����֘A
		Matrix4X4 mat;
		mat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(0, 0, 0),
			Vector3(0, 0, 0)
		);
		SetToAnimeMatrix(mat);

		//�e�N���X��Create
		SS5ssae::OnCreate();
		//�b������̃t���[����
		SetFps(60.0f);
		//���[�v����
		SetLooped(true);


		//�����x�L����
		SetAlphaActive(true);
		//�`��
		SetDrawActive(true);
		//�\�����C���[
		SetDrawLayer(2);

	}


	void SelectGroundSquareSS::OnUpdate()
	{
		//�A�j���\�V�����X�V
		UpdateAnimeTime(App::GetApp()->GetElapsedTime() / 4);

	}
	//Abe20170529

	//--------------------------------------------------------------------------------------------
	//��Փx�̃X�v���C�g
	SelectModeSquare::SelectModeSquare(const shared_ptr<Stage>& StagePtr, const int& ModeNum) :
		GameObject(StagePtr),
		m_ModeNum(ModeNum)
	{}
	void SelectModeSquare::OnCreate() {
		auto Trans = AddComponent<Transform>();
		auto Draw = AddComponent<PCTSpriteDraw>();

		if (m_ModeNum == 1) {
			auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
			auto Pos = EasyPtr->GetComponent<Transform>()->GetPosition();
			Trans->SetPosition(Pos.x, Pos.y + 250, Pos.z + 10);
			Draw->SetTextureResource(L"EASY_TX");
		}
		else if (m_ModeNum == 2) {
			auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
			auto Pos = NormalPtr->GetComponent<Transform>()->GetPosition();
			Trans->SetPosition(Pos.x, Pos.y + 250, Pos.z + 10);
			Draw->SetTextureResource(L"NORMAL_TX");
		}
		else if (m_ModeNum == 3) {
			auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
			auto Pos = HardPtr->GetComponent<Transform>()->GetPosition();
			Trans->SetPosition(Pos.x, Pos.y + 250, Pos.z + 10);
			Draw->SetTextureResource(L"HARD_TX");
		}
		SetDrawActive(true);
		SetAlphaActive(true);
		SetDrawLayer(5);
		Trans->SetScale(260, 130, 1);
		Trans->SetRotation(90 * 3.14159265f / 180, 0, 0);
	}
	void SelectModeSquare::OnUpdate() {
		auto EasyPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Easy", false);
		auto NormalPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Normal", false);
		auto HardPtr = GetStage()->GetSharedGameObject<ModeSelect>(L"Hard", false);
		auto Trans = GetComponent<Transform>();

		if (m_ModeNum == 1) {
			auto Pos = EasyPtr->GetComponent<Transform>()->GetPosition();
			Trans->SetPosition(Pos.x, Pos.y + 250, Pos.z + 10);
		}
		else if (m_ModeNum == 2) {
			auto Pos = NormalPtr->GetComponent<Transform>()->GetPosition();
			Trans->SetPosition(Pos.x, Pos.y + 250, Pos.z + 10);
		}
		else if (m_ModeNum == 3) {
			auto Pos = HardPtr->GetComponent<Transform>()->GetPosition();
			Trans->SetPosition(Pos.x, Pos.y + 250, Pos.z + 10);
		}
	}


	//�w�i�z�u
	SERECT_Background::SERECT_Background(const shared_ptr<Stage>& StagePtr, const Vector3& Scale, const Vector3& Pos) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Pos(Pos)
	{}
	void SERECT_Background::OnCreate() {
		auto Draw = AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SERECT_Background_TX");
		auto Trans = AddComponent<Transform>();
		//�����l
		Trans->SetPosition(m_Pos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(90 * XM_PI / 180, 0, 0);
		SetDrawLayer(0);

	}

	GoBackSprite::GoBackSprite(const shared_ptr<Stage>& StagePtr, const Vector2& Scale, const Vector2& Pos, const int& Num) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Pos(Pos),
		m_Num(Num)
	{};
	void GoBackSprite::OnCreate() {
		auto Trans = AddComponent<Transform>();
		auto Draw = AddComponent<PCTSpriteDraw>();
		if (m_Num == 1) {
			Trans->SetPosition(Vector3(m_Pos.x, m_Pos.y, 0));
			Trans->SetScale(m_Scale.x, m_Scale.y, 0);
			Draw->SetTextureResource(L"Go_TX");
		}
		if (m_Num == 2) {
			Trans->SetPosition(Vector3(m_Pos.x, m_Pos.y, 0));
			Trans->SetScale(Vector3(m_Scale.x, m_Scale.y, 0));
			Draw->SetTextureResource(L"Back_TX");
		}
		SetDrawActive(false);
		SetDrawLayer(7);
		SetAlphaActive(true);
	}
	void GoBackSprite::OnDisp(bool flg) {
		auto Draw = AddComponent<PCTSpriteDraw>();
		if (m_Num == 1) {
			Draw->SetTextureResource(L"Go_TX");
		}
		if (m_Num == 2) {
			Draw->SetTextureResource(L"Back_TX");
		}
		SetDrawActive(flg);
	}
}