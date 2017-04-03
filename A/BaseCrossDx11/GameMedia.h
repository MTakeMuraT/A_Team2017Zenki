#pragma once
#pragma once
#include "stdafx.h"

namespace basecross {
	class GameMedia : public ObjectInterface {
		
	public:
		GameMedia() :
			ObjectInterface() {
		};
		virtual ~GameMedia(){
		}

		void OnCreate()override;
	};
}