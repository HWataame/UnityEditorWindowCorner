/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ウィンドウの角に対する処理を保持するクラス

WindowCorner.h
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#pragma once
#include "WindowCornerType.h"

namespace HW::UnityEditorWindowCorner::Corner
{
    /// <summary>
    /// ウィンドウの角に対する処理を保持するクラス
    /// </summary>
    class WindowCorner final
    {
    public:
        /// <summary>
        /// ウィンドウの角の種類を設定する
        /// </summary>
        /// <param name="windowHandle">ウィンドウのハンドル</param>
        /// <param name="newType">設定する角の種類</param>
        /// <param name="oldType">設定前の角の種類(nullptr指定可能)</param>
        /// <returns>処理結果</returns>
        static const bool Set(const HWND windowHandle,
            const WindowCornerType newType, WindowCornerType* oldType) noexcept;

    private:
        /// <summary>
        /// デフォルトコンストラクタ(外部生成防止用)
        /// </summary>
        WindowCorner() noexcept;

        /// <summary>
        /// トップレベルのウィンドウのハンドルを取得する
        /// </summary>
        /// <param name="windowHandle">ウィンドウのハンドル</param>
        /// <returns>トップレベルのウィンドウのハンドル</returns>
        static const HWND GetTopLevelWindowHandle(const HWND windowHandle) noexcept;
    };
}
