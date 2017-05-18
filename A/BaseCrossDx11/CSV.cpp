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
//�e�G�l�~�[�ǂݍ���
#pragma region TackleEnemyCSV
		GameStageCsv.GetSelect(LineVec, 0, L"TackleEnemy");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, v, L',');

			//�ʒu
			Vector3 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
			//�X�P�[��
			vector<wstring> Tokens2;
			auto TowValue_Str = Tokens[4].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			int m_Min = (float)_wtof(Tokens2[0].c_str());
			int m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Scale	 = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//HP �l�̕�������
			TowValue_Str = Tokens[5].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_HP = Random((int)m_Min,(int)m_Max);
			Tokens2.clear();
			//�T�[�`
			TowValue_Str = Tokens[6].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Search = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�N�[���^�C��
			TowValue_Str = Tokens[7].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_CoolTime = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�X�s�[�h
			TowValue_Str = Tokens[8].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Speed = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�U����
			TowValue_Str = Tokens[9].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_AttackPower = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�ˌ���
			TowValue_Str = Tokens[10].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_AttackTimes = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�e�l����������̂ŃI�u�W�F�N�g�쐬
			auto PtrTackleEnemy = GetStage()->AddGameObject<TackleEnemy>(m_Pos, m_Scale,m_HP,m_Search, m_CoolTime, m_Speed, m_AttackPower,m_AttackTimes);
			PtrEnemyGroup->IntoGroup(PtrTackleEnemy);
			PtrCollisionGroup->IntoGroup(PtrTackleEnemy);
			m_Pos = Vector3(0,0,0); m_Scale = 0; m_HP = 0; m_Search = 0; m_CoolTime = 0; m_Speed = 0; m_AttackPower = 0; m_AttackTimes = 0;
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

			//�ʒu
			Vector3 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
			//�X�P�[��
			vector<wstring> Tokens2;
			auto TowValue_Str = Tokens[4].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			int m_Min = (float)_wtof(Tokens2[0].c_str());
			int m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Scale = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//HP �l�̕�������
			TowValue_Str = Tokens[5].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_HP = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�T�[�`
			TowValue_Str = Tokens[6].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Search = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�N�[���^�C��
			TowValue_Str = Tokens[7].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_ShotCoolTime = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�U����
			TowValue_Str = Tokens[9].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_AttackPower = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�q�@����
			TowValue_Str = Tokens[11].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_ChildDrop = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�e���ː�
			int m_ShotBullet = (float)_wtof(Tokens[1].c_str());
			//�e�l����������̂ŃI�u�W�F�N�g�쐬                       �ʒu�A�傫���AHP�A���G�����A�N�[���^�C���A�U���́A�q�@���ˊԊu�A���ː�
			auto PtrShotEnemy = GetStage()->AddGameObject<ShotEnemy>(m_Pos, m_Scale, m_HP, m_Search, m_ShotCoolTime, m_AttackPower, m_ChildDrop , m_ShotBullet);
			PtrEnemyGroup->IntoGroup(PtrShotEnemy);
			PtrCollisionGroup->IntoGroup(PtrShotEnemy);
			m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_ShotCoolTime = 0;  m_AttackPower = 0; m_ChildDrop = 0; m_ShotBullet = 0;
		}
		LineVec.clear();
#pragma endregion
#pragma region TeleportEnemy
		//�e���|�[�g�|�C���g
		GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, v, L',');

			//�ʒu
			Vector3 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
		}
		LineVec.clear();
#pragma endregion
#pragma region TeleportEnemy
		//�e���|�[�g�G�l�~�[
		GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, v, L',');

			//�ʒu
			Vector3 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
			//�X�P�[��
			vector<wstring> Tokens2;
			int m_Scale = (float)_wtof(Tokens[4].c_str());
			//HP �l�̕�������
			int m_HP = (float)_wtof(Tokens[5].c_str());
			//�T�[�`
			auto TowValue_Str = Tokens[6].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			int m_Min = (float)_wtof(Tokens2[0].c_str());
			int m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Search = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�N�[���^�C��
			TowValue_Str = Tokens[7].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_CoolTime = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�q�@����
			int m_ChildSearch = (float)_wtof(Tokens[12].c_str());
			//�e�l����������̂ŃI�u�W�F�N�g�쐬 
			auto A = GetStage()->AddGameObject<TereportPoint>(Vector3(3, 0.5f, 3));
			PtrTereportGroup->IntoGroup(A);                     // �ʒu�A�傫���AHP�A���G�����A�N�[���^�C���A���ː�
		//	m_Pos.y = 1.0f;
			auto PtrTeleportEnemy = GetStage()->AddGameObject<TeleportEnemy>(m_Pos, m_Scale, m_HP, m_Search, m_CoolTime, m_ChildSearch);
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
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, v, L',');

			//�ʒu
			Vector3 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
			//�X�P�[��
			vector<wstring> Tokens2;
			int m_Scale = (float)_wtof(Tokens[4].c_str());
			//HP �l�̕�������
			int m_HP = (float)_wtof(Tokens[5].c_str());
			//�T�[�`
			auto TowValue_Str = Tokens[6].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			int m_Min = (float)_wtof(Tokens2[0].c_str());
			int m_Max = (float)_wtof(Tokens2[1].c_str());
			 int m_Search = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//��������
			/*TowValue_Str = Tokens[7].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_BomTime = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();*/
			//�X�s�[�h
			TowValue_Str = Tokens[8].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Speed = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//�U����
			TowValue_Str = Tokens[9].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_AttackPower = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			

			//�e�l����������̂ŃI�u�W�F�N�g�쐬
			auto PtrBombEnemy = GetStage()->AddGameObject<BombEnemy>(m_Pos, m_Scale, m_HP, m_Search, m_Speed, m_AttackPower);
			PtrEnemyGroup->IntoGroup(PtrBombEnemy);
			PtrCollisionGroup->IntoGroup(PtrBombEnemy);
			m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_Speed = 0; m_AttackPower = 0;
		}
#pragma endregion
		

/*

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		Util::WStrToTokenVector(Tokens, LineVec[i], L',');
		for (size_t j = 0; j < Tokens.size(); j++) {
			//X��Z�̈ʒu���v�Z
			float XPos = (float)((int)j - 19);
			float ZPos = (float)(19 - (int)i);
			if (Tokens[j] == L"TackleEnemy") {
					
				//�Q�[���I�u�W�F�N�g�̐���
				//GetStage()->AddGameObject<Enemy01>(Vector3(),Vector3());
			}
			else if (Tokens[j] == L"ShotEnemy") {
				m_InputFlg_B = true;
				//AddGameObject<Enemy2>(Vector3(XPos, 0.25f, ZPos));

			}
			else if (Tokens[j] == L"TeleportEnemy") {
				m_InputFlg_C = true;
				//AddGameObject<Enemy3>(Vector3(XPos, 0.25f, ZPos));
			}
			else if (Tokens[j] == L"BombEnemy") {
				m_InputFlg_D = true;
			}
		}
*/

	}
	
	int InputCSV::Random(const int Min, const int Max) {
		//�����_���̒l�ύX
		srand((unsigned)time(NULL));
		//�����_���͈͂ɑI��
		int RandNum = rand() %(Max - Min);
		m_RnadNum = RandNum + Min;
		return m_RnadNum;
	}


}