#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//���\�[�X�̍쐬
	void GameMedia::OnCreate() {
		wstring DataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(DataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		//App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"trace2.png";
		App::GetApp()->RegisterTexture(L"TRACE2_TX", strTexture);
		strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"wall.jpg";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		//�t�F�[�h�n���@���@��
		strTexture = DataDir + L"siro.png";
		App::GetApp()->RegisterTexture(L"SIRO_TX", strTexture);
		//�G�n��TX
		strTexture = DataDir + L"Enemy.png";
		App::GetApp()->RegisterTexture(L"Enemy_TX", strTexture);
	}
}