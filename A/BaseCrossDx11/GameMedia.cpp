#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//���\�[�X�̍쐬
	void GameMedia::OnCreate() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"TestTexture\\trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);

		strTexture = DataDir + L"TestTexture\\sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);

		strTexture = DataDir + L"TestTexture\\spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);

		strTexture = DataDir + L"TestTexture\\number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);

		strTexture = DataDir + L"TestTexture\\TEST.png";
		App::GetApp()->RegisterTexture(L"TEST_TX", strTexture);

		//�e�X�g�pTX
		strTexture = DataDir + L"TestTexture\\GameS.png";
		App::GetApp()->RegisterTexture(L"TEST_Game_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Serekuto.png";
		App::GetApp()->RegisterTexture(L"TEST_Serekuto_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Taitoru.png";
		App::GetApp()->RegisterTexture(L"TEST_Taitoru_TX", strTexture); 
		//�Z���N�g
		strTexture = DataDir + L"TestTexture\\SELECT_TEST.png";
		App::GetApp()->RegisterTexture(L"SELECT_TEST_TX", strTexture); 
		//�^�C�g��
		strTexture = DataDir + L"TestTexture\\Taitoru_TEST.png";
		App::GetApp()->RegisterTexture(L"Taitoru_TEST_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Prres_any_boten_TEST.png";
		App::GetApp()->RegisterTexture(L"Prres_any_boten_TEST_TX", strTexture);

		
		
		////���f���̓K�p�T���v��
		//auto MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"���O.bmf");
		//App::GetApp()->RegisterResource(L"�v���W�F�N�g���Ŏg�����O", MadelMesh);

		//BGM�T���v��
		/*wstring strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\nanika.wav";
		App::GetApp()->RegisterWav(L"Nanika", strMusic); */
		
	}
	
}