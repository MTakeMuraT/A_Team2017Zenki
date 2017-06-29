#pragma once
#include"stdafx.h"

namespace basecross {
	class EnemyCount : public GameObject {
		CsvFile m_InputCSV;
		vector<int> EnemyCunt;
		int m_TackeEnemyCount = 0;
		int m_ShotEnemyCount = 0;
		int m_TeleportEnemyCount = 0;
		int m_BombEnemyCount = 0;
		bool m_flg = true;
	public:
		//構築と破棄
		EnemyCount(const shared_ptr<Stage>& StagePtr);
		virtual ~EnemyCount();
		//初期化
		void ResetCount();
		void Count();
	};

	//--------------------------------------------------------------------------------------
	//	展示用ほっとくとタイトルに戻るやつ
	//--------------------------------------------------------------------------------------
	class TenziTitle : public GameObject
	{
	private :
		//計算用時間
		float m_time;
		//タイトル戻る時間
		float m_BackTitleTime;
	public :
		TenziTitle(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}
		void OnCreate() override;
		void OnUpdate() override;
	};
}
#pragma once
