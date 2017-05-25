#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EnemyCount::EnemyCount(const shared_ptr<Stage>& StagePtr):
	GameObject(StagePtr)
	{
	}
	EnemyCount::~EnemyCount() {}
	
	void EnemyCount::Count() {

		if (GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->GetStageNumber() != 0) {
			// CSV�t�H���_�̎w��
			wstring CsvMediaPath = App::GetApp()->m_wstrRelativeDataPath + L"CSV\\";
			wstring CsvFileName = CsvMediaPath + L"Stage";
			CsvFileName += Util::IntToWStr(GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->GetStageNumber());
			CsvFileName += L".csv";
			//	wstring CsvFileName2 = CsvMediaPath + L"Stage2.csv";

			CsvFile GameStageCsv(CsvFileName);
			//	CsvFile GameStageCsv2(CsvFileName2);
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
			//�e�G�l�~�[�ǂݍ�LineVec	
			//SCV�̃t�@�C�����Ƃɒl��ۑ�����
			GameStageCsv.GetSelect(LineVec, 0, L"TackleEnemy");
			for (auto& v : LineVec) {
				m_TackeEnemyCount++;
			}
			//�V���b�g�G�l�~�[
			GameStageCsv.GetSelect(LineVec, 0, L"ShotEnemy");
			for (auto& v : LineVec) {
				m_ShotEnemyCount++;
			}
			GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
			for (auto& v : LineVec) {
				m_TeleportEnemyCount++;
			}
			GameStageCsv.GetSelect(LineVec, 0, L"BombEnemy");
			for (auto& v : LineVec) {
				m_BombEnemyCount++;
			}
			GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->SetEnemyNum(m_TackeEnemyCount, m_ShotEnemyCount, m_TeleportEnemyCount, m_BombEnemyCount);
			ResetCount();
		}
	}
	void EnemyCount::ResetCount() {

		m_TackeEnemyCount = 0;
		m_ShotEnemyCount = 0;
		m_TeleportEnemyCount = 0;
		m_BombEnemyCount = 0;
	}
}