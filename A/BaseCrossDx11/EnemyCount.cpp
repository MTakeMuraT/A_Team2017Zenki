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
			// CSVフォルダの指定
			wstring CsvMediaPath = App::GetApp()->m_wstrRelativeDataPath + L"CSV\\";
			wstring CsvFileName = CsvMediaPath + L"Stage";
			CsvFileName += Util::IntToWStr(GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->GetStageNumber());
			wstring CSVNum = Util::IntToWStr(GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->GetStageNumber());
			CsvFileName += L".csv";
			//	wstring CsvFileName2 = CsvMediaPath + L"Stage2.csv";

			CsvFile GameStageCsv(CsvFileName);
			//	CsvFile GameStageCsv2(CsvFileName2);
				// ファイルの確認
			if (!GameStageCsv.ReadCsv())
			{
				// ファイルが存在しなかった場合
				throw BaseException(
					L"CSVファイルがありません",
					L"",
					L"選択された場所にアクセスできません"
				);
			}
			//最初の名前分数を入れる
			vector<wstring> LineVec;
			//各エネミー読み込LineVec	
			//SCVのファイルごとに値を保存する
			GameStageCsv.GetSelect(LineVec, 0, L"TackleEnemy");
			for (auto& v : LineVec) {
				m_TackeEnemyCount++;
			}
			//ショットエネミー
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
			App::GetApp()->GetScene<Scene>()->SetCsvStageNum(CSVNum);
		}
	}
	void EnemyCount::ResetCount() {

		m_TackeEnemyCount = 0;
		m_ShotEnemyCount = 0;
		m_TeleportEnemyCount = 0;
		m_BombEnemyCount = 0;
	}

	//--------------------------------------------------------------------------------------
	//	展示用ほっとくとタイトルに戻るやつ
	//--------------------------------------------------------------------------------------
	void TenziTitle::OnCreate()
	{
		//初期化-----------------
		m_time = 0;
		m_BackTitleTime = 20.0f;
		//-----------------------
	}

	void TenziTitle::OnUpdate()
	{
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_BackTitleTime)
		{
			//タイトルに戻す
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");

			m_time = 0;
		}

		//コントローラ取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wButtons & XINPUT_GAMEPAD_A ||
			CntlVec[0].wButtons & XINPUT_GAMEPAD_B ||
			CntlVec[0].wButtons & XINPUT_GAMEPAD_X ||
			CntlVec[0].wButtons & XINPUT_GAMEPAD_Y ||
			CntlVec[0].wButtons & XINPUT_GAMEPAD_BACK ||
			CntlVec[0].wButtons & XINPUT_GAMEPAD_START ||
			CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER ||
			CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER ||
			abs(CntlVec[0].fThumbLX) > 0.1f ||
			abs(CntlVec[0].fThumbLY) > 0.1f)
		{
			m_time = 0;
		}

	}

}