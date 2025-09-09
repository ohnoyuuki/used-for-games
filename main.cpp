#include <Novice.h>
#include <vector>
#include <cmath> // sin, cos
#include <cstdlib> // rand

const char kWindowTitle[] = "不思議な波紋エフェクト";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;


struct Ripple {
    float x, y;
    float radius;
    float alpha;
    float expandSpeed;

    bool isAlive() const {
        return alpha > 0.0f;
    }

    void Update() {
        radius += expandSpeed;
        alpha -= 3.0f; // 透明度を減らす
        if (alpha < 0.0f) {
            alpha = 0.0f;
        }
    }

    void Draw() const {
        // ARGBの32bitカラーを手動で作成
        unsigned int color =
            (static_cast<unsigned int>(alpha) << 24) | // A
            (255 << 16) | // R
            (255 << 8) |  // G
            (255);        // B

        Novice::DrawEllipse(static_cast<int>(x), static_cast<int>(y),
            static_cast<int>(radius), static_cast<int>(radius),
            0.0f, color, kFillModeWireFrame);
    }
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    std::vector<Ripple> ripples;

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///
        int mouseX, mouseY;
        Novice::GetMousePosition(&mouseX, &mouseY);

        // 左クリックで波紋を追加
        if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
            Ripple newRipple;
            newRipple.x = static_cast<float>(mouseX);
            newRipple.y = static_cast<float>(mouseY);
            newRipple.radius = 0.0f;
            newRipple.alpha = 255.0f;
            newRipple.expandSpeed = 4.0f + (rand() % 100) / 50.0f; // ランダム感

            ripples.push_back(newRipple);

        }

        // 各波紋を更新
        for (auto& ripple : ripples) {
            ripple.Update();
        }

        // 消えた波紋を削除
        ripples.erase(
            std::remove_if(ripples.begin(), ripples.end(),
                [](const Ripple& r) { return !r.isAlive(); }),
            ripples.end());

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///
        for (const auto& ripple : ripples) {
            ripple.Draw();
        }
        ///
        /// ↑描画処理ここまで
        ///

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}