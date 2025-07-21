/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
UnityEditorから呼び出す関数を保持するソースファイル

Main.cpp
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#include "ShowWindowReplacer.h"
#include "Corner/WindowCorner.h"
using namespace HW::UnityEditorWindowCorner::Corner;

namespace HW::UnityEditorWindowCorner
{
    /// <summary>
    /// UnityEditorの初期化時の処理
    /// </summary>
    /// <returns>処理結果</returns>
    bool OnUnityEditorInitialize() noexcept
    {
        if (!ShowWindowReplacer::ReplaceShowWindow())
        {
            // ShowWindowを独自の実装に置き換えられなかった場合は失敗
            return false;
        }

        // 自身のプロセスの既に存在するウィンドウの角を処理する
        WindowCorner::ProcessSelfWindowCorners();

        return true;
    }
}
