#pragma once
#include "stdafx.h"
//�񋟌��̕\���V�[��
namespace basecross
{
	class LicenseScene : public Stage
	{
		// �r���[�A���C�g
		void CreateViewLight();

		// ���C�Z���X�\���̃e�N�X�`��
		void CreateLicenseTex();

	public:
		// �\�z�Ɣj��
		LicenseScene() : Stage() {}
		virtual ~LicenseScene() {};

		// ������
		virtual void OnCreate() override;

		// �X�V
		virtual void OnUpdate() override;

		// �\�����ԓ�
		bool CountFlg = false;
		float CountTime = 0.0f;
		float LimitTime = 2.0f;
	};
}
// end basecross