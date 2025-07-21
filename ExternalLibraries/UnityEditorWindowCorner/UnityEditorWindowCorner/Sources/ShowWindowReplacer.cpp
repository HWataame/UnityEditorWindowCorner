/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ShowWindowを独自の処理に置き換えるクラス

ShowWindowReplacer.cpp
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#include "ShowWindowReplacer.h"
#include "Corner/WindowCorner.h"
#include "IAT/Injector.h"
using namespace HW::UnityEditorWindowCorner::Corner;
using namespace HW::UnityEditorWindowCorner::IAT;

namespace HW::UnityEditorWindowCorner
{
    /// <summary>
    /// 置き換え前のShowWindowの関数ポインタ
    /// </summary>
    BOOL(*ShowWindowReplacer::originalFunction)(HWND windowHandle, int showOption);


    /// <summary>
    /// デフォルトコンストラクタ(外部生成防止用)
    /// </summary>
    ShowWindowReplacer::ShowWindowReplacer() noexcept {}

    /// <summary>
    /// ShowWindowを独自の実装に置き換える
    /// </summary>
        /// <param name="targetModuleName">関数をインポートしているモジュール名</param>
    /// <returns>処理結果</returns>
    const bool ShowWindowReplacer::ReplaceShowWindow(const char* targetModuleName) noexcept
    {
        // ShowWindowを置き換える
        void* oldShowWindow;
        if (!Injector::ReplaceFunction("Unity.dll", "USER32.dll", "ShowWindow",
            reinterpret_cast<void*>(CustomShowWindow), &oldShowWindow))
        {
            // ShowWindowを置き換えられなかった場合は失敗
            return false;
        }

        // 置き換え前のShowWindowの関数ポインタを保持する
        originalFunction = reinterpret_cast<BOOL(*)(HWND, int)>(oldShowWindow);

        return true;
    }

    /// <summary>
    /// ShowWindow置き換え用の関数
    /// </summary>
    /// <param name="windowHandle">ウィンドウのハンドル</param>
    /// <param name="showOption">ウィンドウの表示方式</param>
    /// <returns>処理結果</returns>
    BOOL ShowWindowReplacer::CustomShowWindow(HWND windowHandle, int showOption) noexcept
    {
        // ウィンドウの角を丸くしないように設定する
        WindowCorner::Set(windowHandle, WindowCornerType::DoNotRound, nullptr);

        if (originalFunction != nullptr)
        {
            // 元のShowWindowを実行する
            return originalFunction(windowHandle, showOption);
        }
        else
        {
            // 元のShowWindowが存在しない場合は失敗
            return 0;
        }
    }
}
