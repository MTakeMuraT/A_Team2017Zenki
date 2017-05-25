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
		//�\�z�Ɣj��
		EnemyCount(const shared_ptr<Stage>& StagePtr);
		virtual ~EnemyCount();
		//������
		void ResetCount();
		void Count();
	};
}
#pragma once
