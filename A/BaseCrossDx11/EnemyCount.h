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

	//--------------------------------------------------------------------------------------
	//	�W���p�ق��Ƃ��ƃ^�C�g���ɖ߂���
	//--------------------------------------------------------------------------------------
	class TenziTitle : public GameObject
	{
	private :
		//�v�Z�p����
		float m_time;
		//�^�C�g���߂鎞��
		float m_BackTitleTime;
	public :
		TenziTitle(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}
		void OnCreate() override;
		void OnUpdate() override;
	};
}
#pragma once
