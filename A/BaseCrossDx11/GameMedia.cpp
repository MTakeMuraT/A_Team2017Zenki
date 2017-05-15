#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//リソースの作成
	void GameMedia::OnCreate() {
		//テクスチャの読み込みのテクニック　ファイル名とテクスチャを配列で持ち呼び出す
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

		//数字のスプライト
		strTexture = DataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);

		

		//ゲームステージ画面
		strTexture = DataDir + L"GameStage\\Background.png";
		App::GetApp()->RegisterTexture(L"Background_TX", strTexture); 
		strTexture = DataDir + L"GameStage\\Glass.png";
		App::GetApp()->RegisterTexture(L"Glass_TX", strTexture); 
		//プレイヤー関係
		//HPのフレーム
		strTexture = DataDir + L"HP_Flame.png";
		App::GetApp()->RegisterTexture(L"HP_FLAME_TX", strTexture);
		//HPの中身
		strTexture = DataDir + L"HP.png";
		App::GetApp()->RegisterTexture(L"HP_TX", strTexture);

		//テスト用TX
		strTexture = DataDir + L"TestTexture\\GameS.png";
		App::GetApp()->RegisterTexture(L"TEST_Game_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Serekuto.png";
		App::GetApp()->RegisterTexture(L"TEST_Serekuto_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Taitoru.png";
		App::GetApp()->RegisterTexture(L"TEST_Taitoru_TX", strTexture); 
		////セレクト
		//strTexture = DataDir + L"Stage_Select_Lin\\STAGE_SELECT_TEST.png";
		//App::GetApp()->RegisterTexture(L"SELECT_TEST_TX", strTexture); 
		//タイトル
		strTexture = DataDir + L"Title_Lin\\TITLE_TEST.png";
		App::GetApp()->RegisterTexture(L"Taitoru_TEST_TX", strTexture);
		strTexture = DataDir + L"Title_Lin\\Press_any_button.png";
		App::GetApp()->RegisterTexture(L"Prres_any_boten_TEST_TX", strTexture);
		strTexture = DataDir + L"kuro.png";
		App::GetApp()->RegisterTexture(L"KURO_TX", strTexture);

		//Abe20170421
		//仮ステセレ
		//セレクトのフレーム
		strTexture = DataDir + L"TestTexture\\Select_flameTEST.png";
		App::GetApp()->RegisterTexture(L"SELECT_FLAME_TX", strTexture);		
		//Abe20170512
		//本番
		//セレクトのステージ行くか確認するときのYES
		strTexture = DataDir + L"StageSelect\\Go.png";
		App::GetApp()->RegisterTexture(L"SELECT_YES_TX", strTexture);
		//セレクトのステージ行くか確認するときのNO
		strTexture = DataDir + L"StageSelect\\Back.png";
		App::GetApp()->RegisterTexture(L"SELECT_NO_TX", strTexture);
		//本番
		//Abe20170512

		//仮のシロ
		strTexture = DataDir + L"TestTexture\\siro.png";
		App::GetApp()->RegisterTexture(L"SELECT_SIRO_TX", strTexture);
		//仮のカーソル
		strTexture = DataDir + L"TestTexture\\spark.png";
		App::GetApp()->RegisterTexture(L"SELECT_CURSOR_TX", strTexture);

		//Abe20170421

		//Abe20170505
		//エネミー
		//索敵サークル
		strTexture = DataDir + L"Enemy\\SearchCircle.png";
		App::GetApp()->RegisterTexture(L"SEARCHCIRCLE_TX", strTexture);
		//Abe20170505
		//Abe20170508
		strTexture = DataDir + L"Enemy\\TereportPoint.png";
		App::GetApp()->RegisterTexture(L"TEREPORTPOINT_TX", strTexture);
		strTexture = DataDir + L"Enemy\\Bomb.png";
		App::GetApp()->RegisterTexture(L"BOMB_TX", strTexture);
		//Abe20170508
		//Abe20170512
		strTexture = DataDir + L"Enemy\\BombEffect.png";
		App::GetApp()->RegisterTexture(L"BOMBEFFECT_TX", strTexture);
		//Abe20170512
		
	
		////モデル（ボーンあり
		auto MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Player\\PlayerModel\\Player_animation.bmf");
		App::GetApp()->RegisterResource(L"Player_Model", MadelMesh);

		//検証するのに重いので一時的に消します Abe20170505
		//BGM
	/*	wstring strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Title\\Title_01.wav";
		App::GetApp()->RegisterWav(L"Title_01_BGM", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\StageSelect\\StageSelect_01.wav";
		App::GetApp()->RegisterWav(L"StageSelect_01_BGM", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\GameStage\\GameStage_01.wav";
		App::GetApp()->RegisterWav(L"GameStage_01_BGM", strMusic);*/
	
		//SE
		wstring strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Decision_01.wav";
		App::GetApp()->RegisterWav(L"Decision_01_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Collision_01.wav";
		App::GetApp()->RegisterWav(L"Collision_01_SE", strMusic);
		//テストSE
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Decision_02.wav";
		App::GetApp()->RegisterWav(L"Decision_02_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\PlayerDie.wav";
		App::GetApp()->RegisterWav(L"PlayerDie_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\CursorMove.wav";
		App::GetApp()->RegisterWav(L"CursorMove_SE", strMusic);


	}
	
}