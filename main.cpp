#include <Novice.h>

const char kWindowTitle[] = "BGM";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	enum Scene {
		SCENE1,//0
		SCENE2,//1
		SCENE3,//2
	};

	int fanfareSE = Novice::LoadAudio("./Resources/Sounds/title.mp3");
	int mokugyoSE = Novice::LoadAudio("./Resources/Sounds/ketei.mp3");
	int startSE = Novice::LoadAudio("./Resources/Sounds/cancel.mp3");
	int playHandle = -1;
	int scene = SCENE1;
	int playingSound = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);



		///
		/// ↓更新処理ここから
		///
		/// 


		switch (scene)
		{
		case SCENE1:
			if (!Novice::IsPlayingAudio(playHandle)) //サウンドが再生されているか
			{
				playHandle = Novice::PlayAudio(fanfareSE, false, 1.0f);//サウンドを再生する
			}

			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE])//押した時、押される前
			{
				scene = SCENE2;//SCENE1がSCENE2に変わる
				Novice::StopAudio(playHandle);//サウンドが停止される
			}
			break;
		case SCENE2:
			if (!Novice::IsPlayingAudio(playHandle))//サウンドが再生されているか
			{
				playHandle = Novice::PlayAudio(mokugyoSE, false, 1.0f);//サウンドを再生する

			}
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE])//押した時、押される前
			{
				scene = SCENE3;//SCENE2がSCENE3に変わる
				Novice::StopAudio(playHandle);//サウンドが停止される
			}

			break;
		case SCENE3:
			if (!Novice::IsPlayingAudio(playHandle)) //サウンドが再生されているか
			{
				playHandle = Novice::PlayAudio(startSE, false, 1.0f);//サウンドを再生する
			}
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE])//押した時、押される前
			{
				scene = SCENE1;//SCENE3がSCENE1に変わる
				Novice::StopAudio(playHandle);//サウンドが停止される
			}
			break;

		}

		if (scene == SCENE1)//sceneがSCENE1のとき
		{
			playingSound = 1;

		}
		if (scene != SCENE1)//sceneがSCENE1ではないとき
		{
			playingSound = 0;

		}
		///
		/// ↑更新処理ここまで
		///







		///
		/// ↓描画処理ここから
		///


		switch (scene)
		{
		case SCENE1:
			Novice::DrawBox(static_cast<int> (0.0f), static_cast<int>(0.0f), static_cast <int>(1280.0f), static_cast<int>(720.0f), static_cast<int>(0.0f), 0xffaaaaff, kFillModeSolid);
			break;
		case SCENE2:
			Novice::DrawBox(static_cast<int>(0.0f), static_cast<int>(0.0f), static_cast<int>(1280.0f), static_cast<int>(720.0f), 0.0f, GREEN, kFillModeSolid);
			break;
		case SCENE3:
			Novice::DrawBox(static_cast<int>(0.0f), static_cast<int>(0.0f), static_cast<int>(1280.0f), static_cast<int>(720.0f), 0.0f, BLUE, kFillModeSolid);
			break;
		}



		Novice::ScreenPrintf(10, 0, "SceneNo %d", scene);
		Novice::ScreenPrintf(10, 20, "is playing sound %d Push spact to change scene ", playingSound);



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;

}