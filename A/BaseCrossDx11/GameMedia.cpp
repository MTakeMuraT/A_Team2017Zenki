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

		//数字のスプライト
		strTexture = DataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		strTexture = DataDir + L"spark.png";
		App::GetApp()->RegisterTexture(L"Spark_TX", strTexture);
		App::GetApp()->RegisterTexture(L"TEST_AO_TX", strTexture);
		strTexture = DataDir + L"red.png";
		App::GetApp()->RegisterTexture(L"TEST_Red_TX", strTexture);

		//Abe20170602
		//タイム下地
		strTexture = DataDir + L"Time_Background.png";
		App::GetApp()->RegisterTexture(L"TIMEBACK_TX", strTexture);
		//Abe20170602

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
		//ステセレ
		//セレクトのフレーム大枠
		strTexture = DataDir + L"StageSelect\\Select_Flame.png";
		App::GetApp()->RegisterTexture(L"SELECT_FLAME_TX", strTexture);		
		//Abe20170512
		//セレクトのウィンドウのフレーム
		strTexture = DataDir + L"StageSelect\\Flame.png";
		App::GetApp()->RegisterTexture(L"SELECTCHECK_FLAME_TX", strTexture);
		//Abe20170512
		//Abe20170525
		//中身
		strTexture = DataDir + L"StageSelect\\StageSelect_WindowBack.png";
		App::GetApp()->RegisterTexture(L"SELECT_WINDOWIN_TX", strTexture);
		//ロゴ
		//カーソル
		strTexture = DataDir + L"StageSelect\\StageSelect_Logo.png";
		App::GetApp()->RegisterTexture(L"SELECT_LOGO_TX", strTexture);

		//Abe20170525
		//Abe20170526
		//矢印
		strTexture = DataDir + L"StageSelect\\Yazirushi.png";
		App::GetApp()->RegisterTexture(L"YAZIRUSHI_TX", strTexture);
		//easy
		strTexture = DataDir + L"StageSelect\\Easy.png";
		App::GetApp()->RegisterTexture(L"EASY_TX", strTexture);
		//normal
		strTexture = DataDir + L"StageSelect\\Normal.png";
		App::GetApp()->RegisterTexture(L"NORMAL_TX", strTexture);
		//hard
		strTexture = DataDir + L"StageSelect\\Hard.png";
		App::GetApp()->RegisterTexture(L"HARD_TX", strTexture);
		//Abe20170526
		//カーソル
		strTexture = DataDir + L"StageSelect\\StageSelect_Cursor.png";
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
		//strTexture = DataDir + L"EF\\Explosion.png";
		strTexture = DataDir + L"EF\\Explosion.png";
		App::GetApp()->RegisterTexture(L"BOMBEFFECT_TX", strTexture);
		//Abe20170512
		//Abe20170517
		//ミサイル
		strTexture = DataDir + L"Enemy\\Missile.png";
		App::GetApp()->RegisterTexture(L"MISSILE_TX", strTexture);
		//Abe20170517
		//Abe20170519
		strTexture = DataDir + L"Enemy\\Bomb.png";
		App::GetApp()->RegisterTexture(L"SHOADOW_TX", strTexture);
		//Abe20170519

		//Abe20170529
		//ゲームオーバー---------------------------------------
		//クロ
		strTexture = DataDir + L"GameOver\\OverBlack.png";
		App::GetApp()->RegisterTexture(L"OVERBLACK_TX", strTexture);
		//シロ
		strTexture = DataDir + L"GameOver\\OverWhite.png";
		App::GetApp()->RegisterTexture(L"OVERWHITE_TX", strTexture);
		//Abe20170529

		//Abe20170602
		//オーバーの最後の黒幕
		strTexture = DataDir + L"GameOver\\OverLastBlack.png";
		App::GetApp()->RegisterTexture(L"OVERLASTBLACK_TX", strTexture);
		//オーバーの最後の黒幕
		strTexture = DataDir + L"GameOver\\GameOver_Cursor.png";
		App::GetApp()->RegisterTexture(L"OVERCURSOR_TX", strTexture);
		//Abe20170602

		//Abe20170530
		//ノイズ
		strTexture = DataDir + L"GameOver\\Noise1.png";
		App::GetApp()->RegisterTexture(L"OVERNOISE_TX", strTexture);
		//ゲームオーバーロゴ
		strTexture = DataDir + L"GameOver\\GameOverLogo.png";
		App::GetApp()->RegisterTexture(L"OVERLOGO_TX", strTexture);

		//リトライロゴ
		strTexture = DataDir + L"GameOver\\RetryLogo.png";
		App::GetApp()->RegisterTexture(L"OVERRETRYLOGO_TX", strTexture);
		//ステージセレクトロゴ
		strTexture = DataDir + L"GameOver\\StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"OVERSTASELELOGO_TX", strTexture);
		//タイトルロゴ
		strTexture = DataDir + L"GameOver\\TitleLogo.png";
		App::GetApp()->RegisterTexture(L"OVERTITLELOGO_TX", strTexture);


		//爆発音
		wstring  strMOver = App::GetApp()->m_wstrRelativeDataPath + L"GameOver\\BombSE.wav";
		App::GetApp()->RegisterWav(L"OverBombSE", strMOver);
		//ノイズ音
		strMOver = App::GetApp()->m_wstrRelativeDataPath + L"GameOver\\NoiseSE.wav";
		App::GetApp()->RegisterWav(L"OverNoiseSE", strMOver);

		//Abe20170530

		//ゲームオーバー---------------------------------------
		//Abe20170529

		//Abe20170531
		//リザルト--------------------------------------
		//リザルト黒
		strTexture = DataDir + L"Result\\ResultBlack.png";
		App::GetApp()->RegisterTexture(L"RESULTBLACK_TX", strTexture);
		//リザルト白
		strTexture = DataDir + L"Result\\ResultWhite.png";
		App::GetApp()->RegisterTexture(L"RESULTWHITE_TX", strTexture);
		//ミッションコンプリート文字
		strTexture = DataDir + L"Result\\MissionComplete.png";
		App::GetApp()->RegisterTexture(L"MISSIONCOMPLETE_TX", strTexture);
		//×
		strTexture = DataDir + L"Result\\Batu.png";
		App::GetApp()->RegisterTexture(L"BATU_TX", strTexture);
		//TotalScoreロゴ
		strTexture = DataDir + L"Result\\TotalScore.png";
		App::GetApp()->RegisterTexture(L"TOTALSCORE_TX", strTexture);
		//ランク
		//S
		strTexture = DataDir + L"Result\\RankS.png";
		App::GetApp()->RegisterTexture(L"RANK_S_TX", strTexture);
		//A
		strTexture = DataDir + L"Result\\RankA.png";
		App::GetApp()->RegisterTexture(L"RANK_A_TX", strTexture);
		//B
		strTexture = DataDir + L"Result\\RankB.png";
		App::GetApp()->RegisterTexture(L"RANK_B_TX", strTexture);
		//C
		strTexture = DataDir + L"Result\\RankC.png";
		App::GetApp()->RegisterTexture(L"RANK_C_TX", strTexture);

		//次のステージへロゴ
		strTexture = DataDir + L"Result\\NextStage.png";
		App::GetApp()->RegisterTexture(L"RESULTNEXTSTAGELOGO_TX", strTexture);
		//リトライロゴ
		strTexture = DataDir + L"Result\\RetryLogo.png";
		App::GetApp()->RegisterTexture(L"RESULTRETRYLOGO_TX", strTexture);
		//ステージセレクトロゴ
		strTexture = DataDir + L"Result\\StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"RESULTSTASELELOGO_TX", strTexture);
		//タイトルロゴ
		strTexture = DataDir + L"Result\\TitleLogo.png";
		App::GetApp()->RegisterTexture(L"RESULTTITLELOGO_TX", strTexture);

		//リザルト--------------------------------------
		//Abe20170531


		//Abe20170519
		//エネミーカウントのスラッシュ
		strTexture = DataDir + L"Enemy\\EnemyCountSlash.png";
		App::GetApp()->RegisterTexture(L"ENEMYCOUNTSLASH_TX", strTexture);
		//Abe20170519

		//Abe20170524
		//ステージの番号
		for (int i = 1; i <= 16; i++)
		{
			wstring txt1 = L"StageSelect\\" + Util::IntToWStr(i) + L".png";
			strTexture = DataDir + txt1;
			wstring txt2 = L"STAGEBOX_" + Util::IntToWStr(i) + L"_TX";
			App::GetApp()->RegisterTexture(txt2, strTexture);
		}
		//ステセレの背景
		strTexture = DataDir + L"SELECT_Background.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTGROUND_TX", strTexture);
		//Abe20170524

		//Abe20170605
		//ポーズ
		//ポーズの残り敵数
		strTexture = DataDir + L"Pause\\Pause_EnemyS.png";
		App::GetApp()->RegisterTexture(L"PAUSE_ENEMYS_TX", strTexture);
		//ポーズロゴ
		strTexture = DataDir + L"Pause\\PauseLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSE_LOGO_TX", strTexture);
		//リトライ
		strTexture = DataDir + L"Pause\\ReTry.png";
		App::GetApp()->RegisterTexture(L"PAUSE_RETRY_TX", strTexture);
		//ゲームに戻る
		strTexture = DataDir + L"Pause\\ToGame.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TOGAME_TX", strTexture);
		//セレクトに
		strTexture = DataDir + L"Pause\\ToSelect.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TOSELECT_TX", strTexture);
		//タイトルに
		strTexture = DataDir + L"Pause\\ToTitle.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TOTITLE_TX", strTexture);
		//クロ	
		strTexture = DataDir + L"Pause\\PauseBlack.png";
		App::GetApp()->RegisterTexture(L"PAUSE_BLACK_TX", strTexture);
		//Abe20170605

		//Abe20170606
		//爆散エフェクト
		strTexture = DataDir + L"EF\\bakusan.png";
		App::GetApp()->RegisterTexture(L"BAKUSANEF_TX", strTexture);
		//Abe20170606

		//Abe20170609
		//ぶつかりエフェクト
		strTexture = DataDir + L"EF\\spark.png";
		App::GetApp()->RegisterTexture(L"BUTUKARIEF_TX", strTexture);
		//始まり演出
		//スタートロゴ
		strTexture = DataDir + L"StageStart\\Start.png";
		App::GetApp()->RegisterTexture(L"STARTSTARTLOGO_TX", strTexture);
		//ステージロゴ
		strTexture = DataDir + L"StageStart\\StageLogo.png";
		App::GetApp()->RegisterTexture(L"STARTSTAGELOGO_TX", strTexture);
		//Abe20170609

		//Abe20170614
		//タイトル土台
		strTexture = DataDir + L"Title_Lin\\DODAI.png";
		App::GetApp()->RegisterTexture(L"TITLEDODAI_TX", strTexture);
		//ゲームスタート
		strTexture = DataDir + L"Title_Lin\\Game_start.png";
		App::GetApp()->RegisterTexture(L"TITLEGAMESTART_TX", strTexture);
		//チュートリアル
		strTexture = DataDir + L"Title_Lin\\Tutorial.png";
		App::GetApp()->RegisterTexture(L"TITLETUTORIAL_TX", strTexture);
		//Abe20170614

		//Abe20170615
		//チュートリアルのターゲット
		strTexture = DataDir + L"Tutorial\\Target.png";
		App::GetApp()->RegisterTexture(L"TUTORIALTARGET_TX", strTexture);
		//Abe20170615
		//Abe20170616
		//Aボタン
		strTexture = DataDir + L"Tutorial\\A.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_A_TX", strTexture);
		//Aボタン押された時
		strTexture = DataDir + L"Tutorial\\APush.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_APUSH_TX", strTexture);
		//RBボタン
		strTexture = DataDir + L"Tutorial\\RB.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_RB_TX", strTexture);
		//RBボタン押された時
		strTexture = DataDir + L"Tutorial\\RBPush.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_RBPUSH_TX", strTexture);
		//LBボタン
		strTexture = DataDir + L"Tutorial\\LB.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_LB_TX", strTexture);
		//LBボタン押された時
		strTexture = DataDir + L"Tutorial\\LBPush.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_LBPUSH_TX", strTexture);
		//スティック
		strTexture = DataDir + L"Tutorial\\Stick.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_STICK_TX", strTexture);
		//スティック倒された時
		strTexture = DataDir + L"Tutorial\\StickPush.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_STICKPUSH_TX", strTexture);

		//ポッチ
		strTexture = DataDir + L"Tutorial\\Poch.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_POCH_TX", strTexture);
		//フレーム
		strTexture = DataDir + L"Tutorial\\Frame.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_FRAME_TX", strTexture);
		//Abe20170616


		////モデル（ボーンあり
		auto MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Player\\PlayerModel\\Player_animation.bmf");
		App::GetApp()->RegisterResource(L"Player_Model", MadelMesh);
		//Abe20170519
		//突撃エネミー
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Assault\\Assault.bmf");
		App::GetApp()->RegisterResource(L"TACKLE_MODEL", MadelMesh);
		//テレポートエネミー
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Teleport\\Teleport.bmf");
		App::GetApp()->RegisterResource(L"TELEPORT_MODEL", MadelMesh);
		//ミサイルエネミー/使ってない
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Missile_Enemy\\Missile_Enemy.bmf");
		App::GetApp()->RegisterResource(L"MISSILE_MODEL", MadelMesh);
		//ドローン
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Dorawn\\Dorawn.bmf");
		App::GetApp()->RegisterResource(L"SEARCHDRAWN_MODEL", MadelMesh);
		//自爆エネミー
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\BombEnemy\\Suicide_bomb.bmf");
		App::GetApp()->RegisterResource(L"BOMBENEMY_MODEL", MadelMesh);
		//爆弾
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Bomb\\Bomb.bmf");
		App::GetApp()->RegisterResource(L"BOMB_MODEL", MadelMesh);
		//Abe20170519
		//ミサイル子機
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\ShotChild\\Missile_Enemy_Child.bmf");
		App::GetApp()->RegisterResource(L"MissileEnemyChildModel", MadelMesh); 
		//ミサイル
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Enemy\\Missile\\Missile.bmf");
		App::GetApp()->RegisterResource(L"Missile_Model", MadelMesh); 
		//背景MOD
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"GameStage\\Background\\Background_Effect.bmf");
		App::GetApp()->RegisterResource(L"Background_Model", MadelMesh);
		//装甲
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Enemy\\Shield\\Shild_Player_Sub.bmf");
		App::GetApp()->RegisterResource(L"Shield_Model", MadelMesh);

		//Abe20170605
		//パーツ群
		//1
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts1.bmf");
		App::GetApp()->RegisterResource(L"PARTS1_MODEL", MadelMesh);
		//2
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts2.bmf");
		App::GetApp()->RegisterResource(L"PARTS2_MODEL", MadelMesh);
		//3
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts3.bmf");
		App::GetApp()->RegisterResource(L"PARTS3_MODEL", MadelMesh);
		//4
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts4.bmf");
		App::GetApp()->RegisterResource(L"PARTS4_MODEL", MadelMesh);
		//5
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts5.bmf");
		App::GetApp()->RegisterResource(L"PARTS5_MODEL", MadelMesh);
		//6
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts6.bmf");
		App::GetApp()->RegisterResource(L"PARTS6_MODEL", MadelMesh);
		//7
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts7.bmf");
		App::GetApp()->RegisterResource(L"PARTS7_MODEL", MadelMesh);
		//Abe20170605

		//検証するのに重いので一時的に消します Abe20170505
		//BGM
		/*wstring strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Title\\Title_01.wav";
		App::GetApp()->RegisterWav(L"Title_01_BGM", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\StageSelect\\StageSelect_01.wav";
		App::GetApp()->RegisterWav(L"StageSelect_01_BGM", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\GameStage\\GameStage_01.wav";
		App::GetApp()->RegisterWav(L"GameStage_01_BGM", strMusic);*/
	
		//SE
		
		wstring  strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Decision_01.wav";
		App::GetApp()->RegisterWav(L"Decision_01_SE", strMusic);
		
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Collision_01.wav";
		App::GetApp()->RegisterWav(L"Collision_01_SE", strMusic);
		//テストSE
		//strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Decision_02.wav";
		//App::GetApp()->RegisterWav(L"Decision_02_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\PlayerDie.wav";
		App::GetApp()->RegisterWav(L"PlayerDie_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\CursorMove.wav";
		App::GetApp()->RegisterWav(L"PlayerDie_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Win.wav";
		App::GetApp()->RegisterWav(L"Win_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Win.wav";
		App::GetApp()->RegisterWav(L"Win_SE", strMusic);
		//App::GetApp()->RegisterWav(L"CursorMove_SE", strMusic); 
		//strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\PrayerExposure.wav";
		//App::GetApp()->RegisterWav(L"PrayerDie_SE", strMusic); 
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Enemy\\Computer Launch.wav";
		App::GetApp()->RegisterWav(L"Player_Look_SE", strMusic);
		/*strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Enemy\\Enemy ArmorBreak.wav";
		App::GetApp()->RegisterWav(L"Enemy_Damage_SE", strMusic);*/
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Player\\Shield Break.wav";
		App::GetApp()->RegisterWav(L"Enemy_Damage_SE", strMusic);

		

		//Abe20170530
		//選択音
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\CursorMove.wav";
		App::GetApp()->RegisterWav(L"CURSORMOVE_SE", strMusic);
		//決定音
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Decide.wav";
		App::GetApp()->RegisterWav(L"DECIDE_SE", strMusic);
		//Abe20170530
	}
	
}