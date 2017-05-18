#include "stdafx.h"
#include "Project.h"

namespace basecross {
	InputCSV::InputCSV(const shared_ptr<Stage>& StagePtr) :
	GameObject(StagePtr)
	{}
	InputCSV::~InputCSV(){}
	void InputCSV::OnCreate() {
		auto PtrEnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		auto PtrCollisionGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup");
		auto PtrTereportGroup = GetStage()->GetSharedObjectGroup(L"TereportPointGroup");
		auto PtrBomGroup = GetStage()->GetSharedObjectGroup(L"BombGroup");
		// CSV�t�H���_�̎w��
		wstring CsvMediaPath = App::GetApp()->m_wstrRelativeDataPath + L"CSV\\";
		wstring CsvFileName = CsvMediaPath + L"Stage1.csv";
		CsvFile GameStageCsv(CsvFileName);
		// �t�@�C���̊m�F
		if (!GameStageCsv.ReadCsv())
		{
			// �t�@�C�������݂��Ȃ������ꍇ
			throw BaseException(
				L"CSV�t�@�C��������܂���",
				L"",
				L"�I�����ꂽ�ꏊ�ɃA�N�Z�X�ł��܂���"
			);
		}
		//�ŏ��̖��O����������
		vector<wstring> LineVec;
		//for (auto& v : LineVec) {
			//�e�G�l�~�[�ǂݍ�LineVec
#pragma region TackleEnemyCSV
			GameStageCsv.GetSelect(LineVec, 0, L"TackleEnemy");
			for (auto& v : LineVec) {
				//�g�[�N���i�J�����j�̔z��
				vector<wstring> Tokens;
				//�����̒l�̎��Ɏg�p
				vector<wstring> Tokens2;
				//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
				Util::WStrToTokenVector(Tokens, v, L',');		
				//�e�l����������̂ŃI�u�W�F�N�g�쐬
				auto PtrTackleEnemy = GetStage()->AddGameObject<TackleEnemy>(
					SinglePos(Tokens), MultiScale(Tokens,Tokens2), MultiHP(Tokens,Tokens2),
					MultiSearch(Tokens,Tokens2), MultiCoolTime(Tokens, Tokens2), MultiSpeed(Tokens, Tokens2), 
					MultiAttackPower(Tokens, Tokens2), MultiAttackTimes(Tokens, Tokens2));
				//�O���[�v�ɓ����
				PtrEnemyGroup->IntoGroup(PtrTackleEnemy);
				PtrCollisionGroup->IntoGroup(PtrTackleEnemy);
				m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_CoolTime = 0; m_Speed = 0; m_AttackPower = 0; m_AttackTimes = 0;
			}
			//������
			LineVec.clear();
#pragma endregion
#pragma region ShotEnemy
			//�V���b�g�G�l�~�[
			GameStageCsv.GetSelect(LineVec, 0, L"ShotEnemy");
			for (auto& v : LineVec) {
				//�g�[�N���i�J�����j�̔z��
				vector<wstring> Tokens;
				//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
				Util::WStrToTokenVector(Tokens, v, L',');
				//�X�P�[��
				vector<wstring> Tokens2;
			
				//�e�l����������̂ŃI�u�W�F�N�g�쐬       �ʒu�A�傫���AHP�A���G�����A�N�[���^�C���A�U���́A�q�@���ˊԊu�A���ː�
				auto PtrShotEnemy = GetStage()->AddGameObject<ShotEnemy>(SinglePos(Tokens), MultiScale(Tokens,Tokens2), 
					MultiHP(Tokens, Tokens2), MultiSearch(Tokens, Tokens2), MultiShotCoolTime(Tokens, Tokens2),
					MultiAttackPower(Tokens, Tokens2), SingleChildDrop(Tokens), SingleShotBullet(Tokens));
				PtrEnemyGroup->IntoGroup(PtrShotEnemy);
				PtrCollisionGroup->IntoGroup(PtrShotEnemy);
				m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_ShotCoolTime = 0;  m_AttackPower = 0; m_ChildDrop = 0; m_ShotBullet = 0;
			}
			LineVec.clear();
#pragma endregion
#pragma region TeleportEnemy
			//�e���|�[�g�G�l�~�[
			GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
			for (auto& v : LineVec) {
				//�g�[�N���i�J�����j�̔z��
				vector<wstring> Tokens;
				vector<wstring> Tokens2;
				//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
				Util::WStrToTokenVector(Tokens, v, L',');
				//�e�l����������̂ŃI�u�W�F�N�g�쐬 

				//!!!!!!!!!!!!!!!!!!!!!��ł����ύX���܂�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				auto A = GetStage()->AddGameObject<TereportPoint>(Vector3(3, 0.5f, 3));
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				PtrTereportGroup->IntoGroup(A);       // �ʒu�A�傫���AHP�A���G�����A�N�[���^�C��M�A���G�^�q�@����S
				auto PtrTeleportEnemy = GetStage()->AddGameObject<TeleportEnemy>(
					SinglePos(Tokens), SingleScale(Tokens),SingleHP(Tokens), 
					MultiSearch(Tokens,Tokens2), MultiCoolTime(Tokens,Tokens2),SingleChildSearch(Tokens)
					);
				PtrEnemyGroup->IntoGroup(PtrTeleportEnemy);
				PtrCollisionGroup->IntoGroup(PtrTeleportEnemy);

				m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_CoolTime = 0;  m_ChildSearch = 0;
			}
			LineVec.clear();
#pragma endregion
#pragma region BombEnemyCSV
			//�����G�l�~�[
			GameStageCsv.GetSelect(LineVec, 0, L"BombEnemy");
			for (auto& v : LineVec) {
				//�g�[�N���i�J�����j�̔z��
				vector<wstring> Tokens;
				vector<wstring> Tokens2;
				//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
				Util::WStrToTokenVector(Tokens, v, L',');
				//�e�l����������̂ŃI�u�W�F�N�g�쐬�@�ʒus�@�傫��s�@HPs�@���Gm�@�X�s�[�hm�@�U����m
				auto PtrBombEnemy = GetStage()->AddGameObject<BombEnemy>(
					SinglePos(Tokens), SingleScale(Tokens), SingleHP(Tokens),
					MultiSearch(Tokens,Tokens2), MultiSpeed(Tokens,Tokens2), MultiAttackPower(Tokens,Tokens2));
				PtrEnemyGroup->IntoGroup(PtrBombEnemy);
				PtrCollisionGroup->IntoGroup(PtrBombEnemy);
				m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_Speed = 0; m_AttackPower = 0;
			}
#pragma endregion

		//}
	}
	//�ʒu
	Vector3 InputCSV::SinglePos(vector<wstring> Tokens) {
		//�g�[�N���i�J�����j�̔z��
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Util::WStrToTokenVector(Tokens, v, L',');
		//�ʒu
		 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
		 return m_Pos;
	}
	//�X�P�[��
	int InputCSV::SingleScale(vector<wstring> Tokens) {
		m_Scale = (float)_wtof(Tokens[4].c_str());
		return m_Scale;
	}
	int InputCSV::MultiScale(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[4].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_Scale = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Scale;
	}
	//HP
	int InputCSV::SingleHP(vector<wstring> Tokens) {
		m_HP = (float)_wtof(Tokens[5].c_str());
		return m_HP;
	}
	int InputCSV::MultiHP(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[5].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_HP = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_HP;
	}
	//���G�͈�
	int InputCSV::SingleSearch(vector<wstring> Tokens) {
		m_Search = (float)_wtof(Tokens[6].c_str());
		return m_Search;
	}
	int InputCSV::MultiSearch(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[6].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_Search = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Search;
	}
	//�N�[���^�C��
	int InputCSV::SingleCoolTime(vector<wstring> Tokens) {
		m_CoolTime = (float)_wtof(Tokens[7].c_str());
		return m_CoolTime;
	}
	int InputCSV::MultiCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[7].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_CoolTime = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_CoolTime;
	}
	//�V���b�g�N�[���^�C��
	int InputCSV::SingleShotCoolTime(vector<wstring> Tokens) {
		m_ShotCoolTime = (float)_wtof(Tokens[7].c_str());
		return m_ShotCoolTime;
	}
	int InputCSV::MultiShotCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[7].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ShotCoolTime = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ShotCoolTime;
	}
	//�X�s�[�h
	int InputCSV::SingleSpeed(vector<wstring> Tokens) {
		m_Speed = (float)_wtof(Tokens[7].c_str());
		return m_Speed;
	}
	int InputCSV::MultiSpeed(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[8].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_Speed = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Speed;
	}
	//�U����
	int InputCSV::SingleAttackPower(vector<wstring> Tokens) {
		m_AttackPower = (float)_wtof(Tokens[9].c_str());
		return m_AttackPower;
	}
	int InputCSV::MultiAttackPower(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[9].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_AttackPower = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_AttackPower;
	}
	//�ˌ���
	int InputCSV::SingleAttackTimes(vector<wstring> Tokens) {
		m_AttackTimes = (float)_wtof(Tokens[10].c_str());
		return m_AttackTimes;
	}
	int InputCSV::MultiAttackTimes(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[10].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_AttackTimes = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_AttackTimes;
	}
	//�q�@���ˊԊu
	int InputCSV::SingleChildDrop(vector<wstring> Tokens) {
		m_ChildDrop = (float)_wtof(Tokens[11].c_str());
		return m_ChildDrop;
	}
	int InputCSV::MultiChildDrop(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[11].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ChildDrop = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ChildDrop;
	}
	//���G�^�q�@�̔��ˊԊu  TeleportEnemy��CSV���12�Ɂu���G�^�q�@�v���L�q
	int InputCSV::SingleChildSearch(vector<wstring> Tokens) {
		m_ChildSearch = (float)_wtof(Tokens[12].c_str());
		return m_ChildSearch;
	}
	int InputCSV::MultiChildSearch(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[12].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ChildSearch = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ChildSearch;
	}
	//���ː��i���Ŕ��˂����e�̐�  ShotEnemy��CSV���12�Ɂu���ː��v���L�q
	int InputCSV::SingleShotBullet(vector<wstring> Tokens) {
		m_ShotBullet = (float)_wtof(Tokens[12].c_str());
		return m_ShotBullet;
	}
	int InputCSV::MultiShotBullet(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[12].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ShotBullet = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ShotBullet;
	}
	//�w��͈͓��Ń����_������Ԃ��֐�
	int InputCSV::Random(const int Min, const int Max) {
		//�����_���̒l�ύX
		srand((unsigned)time(NULL));
		//�����_���͈͂ɑI��
		int RandNum = rand() %(Max - Min);
		m_RnadNum = RandNum + Min;
		return m_RnadNum;
	}


}