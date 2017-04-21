#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//���\�[�X�̍쐬
	void GameMedia::OnCreate() {
		//�e�N�X�`���̓ǂݍ��݂̃e�N�j�b�N�@�t�@�C�����ƃe�N�X�`����z��Ŏ����Ăяo��
		//struct {
		//	wstring filename;
		//	wstring key;
		//}textureString[] = {
		//	{ L"TestTexture\\trace.png" , L"SKY_TX" },
		//};

		//App::GetApp()->RegisterTexture(textureString[0].key, DataDir + textureString[0].filename);

		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		wstring strTexture = DataDir + L"TestTexture\\trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);

		strTexture = DataDir + L"TestTexture\\sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);

		strTexture = DataDir + L"TestTexture\\spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);

		//�����̃X�v���C�g
		strTexture = DataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);

		

		//�Q�[���X�e�[�W���
		strTexture = DataDir + L"GameStage\\Background.png";
		App::GetApp()->RegisterTexture(L"Background_TX", strTexture);
		//�v���C���[�֌W
		//HP�̃t���[��
		strTexture = DataDir + L"HP_Flame.png";
		App::GetApp()->RegisterTexture(L"HP_FLAME_TX", strTexture);
		//HP�̒��g
		strTexture = DataDir + L"HP.png";
		App::GetApp()->RegisterTexture(L"HP_TX", strTexture);

		//�e�X�g�pTX
		strTexture = DataDir + L"TestTexture\\GameS.png";
		App::GetApp()->RegisterTexture(L"TEST_Game_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Serekuto.png";
		App::GetApp()->RegisterTexture(L"TEST_Serekuto_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Taitoru.png";
		App::GetApp()->RegisterTexture(L"TEST_Taitoru_TX", strTexture); 
		//�Z���N�g
		strTexture = DataDir + L"Stage_Select_Lin\\STAGE_SELECT_TEST.png";
		App::GetApp()->RegisterTexture(L"SELECT_TEST_TX", strTexture); 
		//�^�C�g��
		strTexture = DataDir + L"Title_Lin\\TITLE_TEST.png";
		App::GetApp()->RegisterTexture(L"Taitoru_TEST_TX", strTexture);
		strTexture = DataDir + L"Title_Lin\\Press_any_button.png";
		App::GetApp()->RegisterTexture(L"Prres_any_boten_TEST_TX", strTexture);
		strTexture = DataDir + L"kuro.png";
		App::GetApp()->RegisterTexture(L"KURO_TX", strTexture);

		
		
		////���f���̓K�p�T���v��
		//auto MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"���O.bmf");
		//App::GetApp()->RegisterResource(L"�v���W�F�N�g���Ŏg�����O", MadelMesh);

		//BGM�T���v��
		/*wstring strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\nanika.wav";
		App::GetApp()->RegisterWav(L"Nanika", strMusic); */
		
	}
	
}