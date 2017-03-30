#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//リソースの作成
	void GameMedia::OnCreate() {
		wstring DataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(DataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		//App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"trace2.png";
		App::GetApp()->RegisterTexture(L"TRACE2_TX", strTexture);
		strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"wall.jpg";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		//フェード系統　白　黒
		strTexture = DataDir + L"siro.png";
		App::GetApp()->RegisterTexture(L"SIRO_TX", strTexture);
		//敵系統TX
		strTexture = DataDir + L"Enemy.png";
		App::GetApp()->RegisterTexture(L"Enemy_TX", strTexture);
	}
}