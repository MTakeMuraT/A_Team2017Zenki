
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------

	void Scene::OnCreate(){
		try {
			//�������Ă΂�Ă���X�e�[�W���Ă΂��
			m_GameMedia  = ObjectFactory::Create<GameMedia>();

			//�Ƃ肠���������̂�����ł�邩
			srand((unsigned)time(NULL));

			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			//ResetActiveStage<LogoScene>();
			ResetActiveStage<TitleScene>();
			//ResetActiveStage<StageSelectScene>();
			//ResetActiveStage<TutorialScene>();

		}
		catch (...) {
			throw;
		}
	}
	void Scene::OnEvent(const shared_ptr<Event>& event) {
		
		if (event->m_MsgStr == L"ToLogoScene") {
			auto TitleScenePtr = dynamic_pointer_cast<LogoScene>(GetActiveStage());
			if (!TitleScenePtr) {
				ResetActiveStage<LogoScene>();
			}
		}

		if (event->m_MsgStr == L"ToTitleScene") {
			auto TitleScenePtr = dynamic_pointer_cast<TitleScene>(GetActiveStage());
			if (!TitleScenePtr) {
				ResetActiveStage<TitleScene>();
			}
		}
		
		if (event->m_MsgStr == L"ToStageSelectScene") {
			auto StafeSelectPtr = dynamic_pointer_cast<StageSelectScene>(GetActiveStage());
			if (!StafeSelectPtr) {
				ResetActiveStage<StageSelectScene>();
			}
		}
		if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToTutorial") {
			ResetActiveStage<TutorialScene>();
		}

	}


	//�X�e�[�W�ԍ��Ƒ傫���ݒ�
	void Scene::SetStageNumAndStageSize(int stagenum, Vector2 stagesize)
	{
		//�X�e�[�W�ԍ��ݒ�
		m_StageNum = stagenum;

		//�X�e�[�W�T�C�Y�ݒ�
		m_StageSize = stagesize;
	}

	//Abe20170622
	//�X�R�A�o�^
	void Scene::SetStageScore(int score)
	{
		//���ɓ���Ƃ��z��
		int arr[5] = { 0 };

		//CSV�ǂݍ���
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		wstring strTexture = DataDir + L"score\\score.csv";
		//�Ȃ�������G���[
		ifstream ifs(strTexture);
		if (!ifs)
		{

		}
		else
		{
			//csv�t�@�C�����g�ǂݍ���
			string str;
			//�Ȃ񂩂��낢��߂�ǂ�����K���Ɏw�肵��
			int stagecount = 1;
			//�s
			while (getline(ifs, str))
			{
				//�w�肳�ꂽ�X�e�[�W�ԍ��ƈ�v�����玝���Ă���
				if (stagecount == m_StageNum)
				{
					string token;
					istringstream stream(str);

					//�w�肳�ꂽ���ʂ�E�o
					int juncount = 0;
					//�R���}����
					while (getline(stream, token, ','))
					{
						if (juncount != 0)
						{
							//int�ϊ�
							int temp = stoi(token);
							arr[juncount - 1] = temp;
						}
						juncount++;
					}
					break;
				}
				//�X�e�[�W�ԍ��i�߂�A���ꂪ��v�����Ƃ������Ă���
				stagecount++;
			}

			//�Ƃ肠���������܂ł�arr�Ɍ��݂̃X�e�[�W�̐������z��œ����Ă�͂�

			//���Ƃ����X�R�A�����
			for (int i = 0; i < 5; i++)
			{
				//0�Ȃ�X�R�A�����
				if (arr[i] == 0)
				{
					arr[i] = score;
					break;
				}
				//�Ō�̃��[�v
				else if (i == 4)
				{
					//��ԒႢ�X�R�A���㏑��
					if (arr[i] < score)
					{
						arr[i] = score;
					}
				}
			}

			//���肵�ē���ւ��B(score�~��)
			for (int i = 0; i < 5; i++)
			{
				for (int j = i + 1; j < 5; j++)
				{
					//�O���傫��
					if (arr[i] < arr[j])
					{
						int work = arr[i];
						arr[i] = arr[j];
						arr[j] = work;
					}
				}
			}

			//�ۑ����Ƃ����
			vector<string> colsVec;

			//CSV��������---------------------------
			//���܂̃X�e�[�W�̂Ƃ��������������B����ȊO�͂��̂܂ܓ����
			stagecount = 1;
			//�ꉞ������
			str = "";
			ifstream ifs(strTexture);

			//�s
			while (getline(ifs, str))
			{
				string token;
				istringstream stream(str);

				//������X�e�[�W�̂Ƃ��ɂ�����
				if (stagecount == m_StageNum)
				{
					string txt = to_string(m_StageNum);
					for (int i = 0; i < 5; i++)
					{
						txt += ',' + to_string(arr[i]);
					}

					colsVec.push_back(txt);
				}
				//����ȊO�͂��̂܂ܓ����
				else
				{
					//���擾
					while (getline(stream, token))
					{
						colsVec.push_back(token);
					}
				}

				//�X�e�[�W�ԍ��i�߂�
				stagecount++;
			}


			//��������
			//ofstream ofs;
			//ofs.open(strTexture, ios::trunc);	//�S�����œǂݍ���?
			//�ǂ����ł���������
			//CSV�J���Ă�Ə㏑���ł��Ȃ��݂�������
			ofstream ofs(strTexture);

			for (auto st : colsVec)
			{
				ofs << st << endl;
			}

		}
	}

	//Abe20170622

	//Abe20170623
	//�X�e�[�W�X�R�A�擾
	int Scene::GetStageScore(int stage, int num)
	{
		//CSV�ǂݍ���
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		wstring strTexture = DataDir + L"score\\score.csv";

		//�Ȃ�������G���[
		ifstream ifs(strTexture);
		if (!ifs)
		{
			return NULL;
		}
		else
		{
			//csv�t�@�C���ǂݍ���
			string str;
			//�Ȃ񂩂��낢��߂�ǂ�����K���Ɏw�肵��
			int stagecount = 1;
			//�s
			while (getline(ifs, str)) {
				//�w�肳�ꂽ�X�e�[�W�ԍ��ƈ�v�����玝���Ă���
				if (stagecount == stage)
				{
					string token;
					istringstream stream(str);

					//�w�肳�ꂽ���ʂ�E�o
					int juncount = 0;
					//�R���}����
					while (getline(stream, token, ',')) 
					{
						if (juncount == num+1)
						{
							//���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
							//���l�͕ϊ����K�v
							int temp = stoi(token); //stof(string str) : string��float�ɕϊ�
							return temp;
						}
						juncount++;
					}
					break;
				}
				//�X�e�[�W�ԍ��i�߂�A���ꂪ��v�����Ƃ������Ă���
				stagecount++;
			}
		}

		return false;

	}
	//Abe20170623
}


//end basecross
