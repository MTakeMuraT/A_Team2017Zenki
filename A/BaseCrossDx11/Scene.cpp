
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------

	void Scene::OnCreate(){
		try {
			//こいつが呼ばれてからステージが呼ばれる
			m_GameMedia  = ObjectFactory::Create<GameMedia>();

			//とりあえず乱数のやつここでやるか
			srand((unsigned)time(NULL));

			//最初のアクティブステージの設定
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


	//ステージ番号と大きさ設定
	void Scene::SetStageNumAndStageSize(int stagenum, Vector2 stagesize)
	{
		//ステージ番号設定
		m_StageNum = stagenum;

		//ステージサイズ設定
		m_StageSize = stagesize;
	}

	//Abe20170622
	//スコア登録
	void Scene::SetStageScore(int score)
	{
		//仮に入れとく配列
		int arr[5] = { 0 };

		//CSV読み込み
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		wstring strTexture = DataDir + L"score\\score.csv";
		//なかったらエラー
		ifstream ifs(strTexture);
		if (!ifs)
		{

		}
		else
		{
			//csvファイル中身読み込み
			string str;
			//なんかいろいろめんどいから適当に指定して
			int stagecount = 1;
			//行
			while (getline(ifs, str))
			{
				//指定されたステージ番号と一致したら持ってくる
				if (stagecount == m_StageNum)
				{
					string token;
					istringstream stream(str);

					//指定された順位を摘出
					int juncount = 0;
					//コンマ分割
					while (getline(stream, token, ','))
					{
						if (juncount != 0)
						{
							//int変換
							int temp = stoi(token);
							arr[juncount - 1] = temp;
						}
						juncount++;
					}
					break;
				}
				//ステージ番号進める、これが一致したとこ持ってくる
				stagecount++;
			}

			//とりあえずここまででarrに現在のステージの数字が配列で入ってるはず

			//今とったスコア入れる
			for (int i = 0; i < 5; i++)
			{
				//0ならスコア入れる
				if (arr[i] == 0)
				{
					arr[i] = score;
					break;
				}
				//最後のループ
				else if (i == 4)
				{
					//一番低いスコアを上書き
					if (arr[i] < score)
					{
						arr[i] = score;
					}
				}
			}

			//判定して入れ替え。(score降順)
			for (int i = 0; i < 5; i++)
			{
				for (int j = i + 1; j < 5; j++)
				{
					//前より大きい
					if (arr[i] < arr[j])
					{
						int work = arr[i];
						arr[i] = arr[j];
						arr[j] = work;
					}
				}
			}

			//保存しとくやつ
			vector<string> colsVec;

			//CSV書き込み---------------------------
			//いまのステージのとこだけ書き換え。それ以外はそのまま入れる
			stagecount = 1;
			//一応初期化
			str = "";
			ifstream ifs(strTexture);

			//行
			while (getline(ifs, str))
			{
				string token;
				istringstream stream(str);

				//今いるステージのとこにきたら
				if (stagecount == m_StageNum)
				{
					string txt = to_string(m_StageNum);
					for (int i = 0; i < 5; i++)
					{
						txt += ',' + to_string(arr[i]);
					}

					colsVec.push_back(txt);
				}
				//それ以外はそのまま入れる
				else
				{
					//一列取得
					while (getline(stream, token))
					{
						colsVec.push_back(token);
					}
				}

				//ステージ番号進める
				stagecount++;
			}


			//書き込み
			//ofstream ofs;
			//ofs.open(strTexture, ios::trunc);	//全消去で読み込み?
			//どっちでも動いたわ
			//CSV開いてると上書きできないみたいっす
			ofstream ofs(strTexture);

			for (auto st : colsVec)
			{
				ofs << st << endl;
			}

		}
	}

	//Abe20170622

	//Abe20170623
	//ステージスコア取得
	int Scene::GetStageScore(int stage, int num)
	{
		//CSV読み込み
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		wstring strTexture = DataDir + L"score\\score.csv";

		//なかったらエラー
		ifstream ifs(strTexture);
		if (!ifs)
		{
			return NULL;
		}
		else
		{
			//csvファイル読み込み
			string str;
			//なんかいろいろめんどいから適当に指定して
			int stagecount = 1;
			//行
			while (getline(ifs, str)) {
				//指定されたステージ番号と一致したら持ってくる
				if (stagecount == stage)
				{
					string token;
					istringstream stream(str);

					//指定された順位を摘出
					int juncount = 0;
					//コンマ分割
					while (getline(stream, token, ',')) 
					{
						if (juncount == num+1)
						{
							//すべて文字列として読み込まれるため
							//数値は変換が必要
							int temp = stoi(token); //stof(string str) : stringをfloatに変換
							return temp;
						}
						juncount++;
					}
					break;
				}
				//ステージ番号進める、これが一致したとこ持ってくる
				stagecount++;
			}
		}

		return false;

	}
	//Abe20170623
}


//end basecross
