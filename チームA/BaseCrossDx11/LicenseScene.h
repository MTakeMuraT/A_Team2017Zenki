#pragma once
#include "stdafx.h"
//提供元の表示シーン
namespace basecross
{
	class LicenseScene : public Stage
	{
		// ビュー、ライト
		void CreateViewLight();

		// ライセンス表示のテクスチャ
		void CreateLicenseTex();

	public:
		// 構築と破棄
		LicenseScene() : Stage() {}
		virtual ~LicenseScene() {};

		// 初期化
		virtual void OnCreate() override;

		// 更新
		virtual void OnUpdate() override;

		// 表示時間等
		bool CountFlg = false;
		float CountTime = 0.0f;
		float LimitTime = 2.0f;
	};
}
// end basecross