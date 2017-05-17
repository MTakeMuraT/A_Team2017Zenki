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

		//�V���b�g�G�l�~�[
		GameStageCsv.GetSelect(LineVec, 0, L"ShotEnemy");
		for (auto& v : LineVec) {
	//		GetStage()->AddGameObject<Enemy02>(v);
		}
		LineVec.clear();
		//�e���|�[�g�G�l�~�[
		GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
		for (auto& v : LineVec) {
			//GetStage()->AddGameObject<Enemy02>(v);
		}
		LineVec.clear();
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


	TestEnemy::TestEnemy(const shared_ptr<Stage>& PtrStage, const wstring& line):
	GameObject(PtrStage)
	{
		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		Util::WStrToTokenVector(Tokens, line, L',');
		m_Scale = Vector3(
			(float)_wtof(Tokens[4].c_str()),
			(float)_wtof(Tokens[4].c_str()),
			(float)_wtof(Tokens[4].c_str())
		);
		m_Pos = Vector3(
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str()),
			(float)_wtof(Tokens[3].c_str())
		);
		//�X�P�[��
		TowValue_Str = Tokens[4].c_str();
		vector<wstring> Tokens2;
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		float Mini = (float)_wtof(Tokens2[0].c_str());
		float Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//�f�o�b�N////////////////////////////////////////////////
		Debug_TowValue_Scale_Str = TowValue_Str;
		Debug_Mini_Scale_F = Mini;
		Debug_Mix_Scale_F = Mix;
		//////////////////////////////////////////////////////////HP
		//�l�����wstring�œ����Ă�����̂̕�������
		TowValue_Str = Tokens[5].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//�f�o�b�N////////////////////////////////////////////////
		Debug_TowValue_HP_Str = TowValue_Str;
		Debug_Mini_HP_F = Mini;
		Debug_Mix_HP_F = Mix;
		//////////////////////////////////////////////////////////���G�͈�
		//�l�����wstring�œ����Ă�����̂̕�������
		TowValue_Str = Tokens[6].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//�f�o�b�N////////////////////////////////////////////////
		Debug_Search_Str = TowValue_Str;
		Debug_Mini_Search_F = Mini;
		Debug_Mix_Search_F = Mix;
		//////////////////////////////////////////////////////////�N�[���^�C��
		TowValue_Str = Tokens[7].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//�f�o�b�N////////////////////////////////////////////////
		Debug_CoolTime_Str = TowValue_Str;
		Debug_Mini_CoolTime_F = Mini;
		Debug_Mix_CoolTime_F = Mix;
		//////////////////////////////////////////////////////////���x
		TowValue_Str = Tokens[8].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//�f�o�b�N////////////////////////////////////////////////
		Debug_Speed_Str = TowValue_Str;
		Debug_Mini_Speed_F = Mini;
		Debug_Mix_Speed_F = Mix;
		//////////////////////////////////////////////////////////�U����
		TowValue_Str = Tokens[9].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//�f�o�b�N////////////////////////////////////////////////
		Debug_Attack_Str = TowValue_Str;
		Debug_Mini_Attack_F = Mini;
		Debug_Mix_Attack_F = Mix;
		//////////////////////////////////////////////////////////�ˌ���
		TowValue_Str = Tokens[10].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//�f�o�b�N////////////////////////////////////////////////
		Debug_Assault_Str = TowValue_Str;
		Debug_Mini_Assault_F = Mini;
		Debug_Mix_Assault_F = Mix;
		//////////////////////////////////////////////////////////
	}
	void TestEnemy::OnCreate() {
		auto Trans = GetComponent<Transform>();
		Trans->SetScale(m_Scale);
		Trans->SetRotation(0, 0, 0);
		Trans->SetPosition(m_Pos);
		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}
	void TestEnemy::OnLastUpdate() {
		wstring PosStr(L"\nPosition:\t");
		
			auto Obj = GetComponent<Transform>()->GetPosition();
			PosStr += L"X=" + Util::FloatToWStr(Obj.x, 6, Util::FloatModify::Fixed) + L",\t";
			PosStr += L"Y=" + Util::FloatToWStr(Obj.y, 6, Util::FloatModify::Fixed) + L",\t";
			PosStr += L"Z=" + Util::FloatToWStr(Obj.z, 6, Util::FloatModify::Fixed) + L"\n";
			
			wstring ScalePtr(L"�X�P�[��;\t");
			ScalePtr += Debug_TowValue_Scale_Str;
			ScalePtr += L"\n";
			wstring HPMiniScale(L"�ŏ��l:\t");
			HPMiniScale += Util::FloatToWStr(Debug_Mini_Scale_F);
			wstring ScaleMaxStr(L"\t�ő�l\t");
			ScaleMaxStr += Util::FloatToWStr(Debug_Mix_Scale_F);
			ScaleMaxStr += L"\n";

			wstring HPStr(L"HP:\t");
			HPStr += Debug_TowValue_HP_Str;
			HPStr += L"\n";
			wstring HPMiniStr(L"�ŏ��l:\t");
			HPMiniStr += Util::FloatToWStr(Debug_Mini_HP_F);
			wstring HPMaxStr(L"\t�ő�l\t");
			HPMaxStr += Util::FloatToWStr(Debug_Mix_HP_F);
			HPMaxStr += L"\n";
				
			wstring SearchStr(L"���G:\t");
			SearchStr += Debug_Search_Str;
			SearchStr += L"\n";
			wstring SearchMiniStr(L"�ŏ��l:\t");
			SearchMiniStr += Util::FloatToWStr(Debug_Mini_Search_F);
			wstring SearchMaxStr(L"\t�ő�l\t");
			SearchMaxStr += Util::FloatToWStr(Debug_Mix_Search_F);
			SearchMaxStr += L"\n";

			wstring CoolTimeStr(L"�N�[���^�C��:\t");
			CoolTimeStr += Debug_CoolTime_Str;
			CoolTimeStr += L"\n";
			wstring CoolTimeMiniStr(L"�ŏ��l:\t");
			CoolTimeMiniStr += Util::FloatToWStr(Debug_Mini_CoolTime_F);
			wstring CoolTimeMaxStr(L"\t�ő�l\t");
			CoolTimeMaxStr += Util::FloatToWStr(Debug_Mix_CoolTime_F);
			CoolTimeMaxStr += L"\n";

			wstring SpeedStr(L"���x:\t");
			SpeedStr += Debug_Speed_Str;
			SpeedStr += L"\n";
			wstring SpeedMiniStr(L"�ŏ��l:\t");
			SpeedMiniStr += Util::FloatToWStr(Debug_Mini_Speed_F);
			wstring SpeedMaxStr(L"\t�ő�l\t");
			SpeedMaxStr += Util::FloatToWStr(Debug_Mix_Speed_F);
			SpeedMaxStr += L"\n";

			wstring AttackStr(L"�U����:\t");
			AttackStr += Debug_Attack_Str;
			AttackStr += L"\n";
			wstring AttackMiniStr(L"�ŏ��l:\t");
			AttackMiniStr += Util::FloatToWStr(Debug_Mini_Attack_F);
			wstring AttackMaxStr(L"\t�ő�l\t");
			AttackMaxStr += Util::FloatToWStr(Debug_Mix_Attack_F);
			AttackMaxStr += L"\n";

			wstring Debug_AssaultStr(L"�ˌ���:\t");
			Debug_AssaultStr += Debug_Assault_Str;
			Debug_AssaultStr += L"\n";
			wstring AssaultMiniStr(L"�ŏ��l:\t");
			AssaultMiniStr += Util::FloatToWStr(Debug_Mini_Assault_F);
			wstring AssaultMaxStr(L"\t�ő�l\t");
			AssaultMaxStr += Util::FloatToWStr(Debug_Mix_Assault_F);
			AssaultMaxStr += L"\n";

		wstring  str = PosStr + ScalePtr + HPMiniScale + ScaleMaxStr + HPStr + HPMiniStr + HPMaxStr + SearchStr + SearchMiniStr + SearchMaxStr
						+ CoolTimeStr + CoolTimeMiniStr + CoolTimeMaxStr + SpeedStr + SpeedMiniStr + SpeedMaxStr + AttackStr + AttackMiniStr + AttackMaxStr
						+ Debug_AssaultStr + AssaultMiniStr + AssaultMaxStr;
						
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}
}