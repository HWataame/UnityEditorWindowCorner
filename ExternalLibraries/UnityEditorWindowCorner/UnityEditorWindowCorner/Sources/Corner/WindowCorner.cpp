/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ウィンドウの角に対する処理を保持するクラス

WindowCorner.cpp
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#include "WindowCorner.h"
#pragma comment(lib, "dwmapi.lib")

namespace HW::UnityEditorWindowCorner::Corner
{
    /// <summary>
    /// デフォルトコンストラクタ(外部生成防止用)
    /// </summary>
    WindowCorner::WindowCorner() noexcept {}
    /// <summary>
    /// ウィンドウの角の種類を設定する
    /// </summary>
    /// <param name="windowHandle">ウィンドウのハンドル</param>
    /// <param name="newType">設定する角の種類</param>
    /// <param name="oldType">設定前の角の種類(nullptr指定可能)</param>
    /// <returns>処理結果</returns>
    const bool WindowCorner::Set(const HWND windowHandle,
        const WindowCornerType newType, WindowCornerType* oldType) noexcept
    {
        // ウィンドウハンドルがNULLである場合は失敗
        if (windowHandle == NULL) return false;

        // トップレベルのウィンドウのハンドルを取得する
        HWND topLevelWindowHandle = GetTopLevelWindowHandle(windowHandle);

        if (oldType != nullptr)
        {
            // 変更前の角の種類を受け取る場合は変更前のウィンドウの角の種類の取得を試行する
            auto getResult = DwmGetWindowAttribute(topLevelWindowHandle,
                DWMWA_WINDOW_CORNER_PREFERENCE, oldType, sizeof(DWM_WINDOW_CORNER_PREFERENCE));

            if (FAILED(getResult))
            {
                // 変更前のウィンドウの角の種類を取得できなかった場合は失敗
                *oldType = WindowCornerType::Default;
                return false;
            }
        }

        // ウィンドウの角の種類の変更を試行する
        auto cornerType = static_cast<DWM_WINDOW_CORNER_PREFERENCE>(newType);
        auto setResult = DwmSetWindowAttribute(topLevelWindowHandle,
            DWMWA_WINDOW_CORNER_PREFERENCE, &cornerType, sizeof(DWM_WINDOW_CORNER_PREFERENCE));

        if (FAILED(setResult))
        {
            // ウィンドウの角の種類を変更できなかった場合は失敗
            if (oldType != nullptr) *oldType = WindowCornerType::Default;
            return false;
        }

        return true;
    }

    /// <summary>
    /// トップレベルのウィンドウのハンドルを取得する
    /// </summary>
    /// <param name="windowHandle">ウィンドウのハンドル</param>
    /// <returns>トップレベルのウィンドウのハンドル</returns>
    const HWND WindowCorner::GetTopLevelWindowHandle(const HWND windowHandle) noexcept
    {
        HWND topLevelWindowHandle = windowHandle;
        for (;;)
        {
            // 親ウィンドウを取得する
            auto parentWindow = GetParent(topLevelWindowHandle);

            // 親ウィンドウが存在しない場合はトップレベルウィンドウであるためここで処理終了
            if (parentWindow == NULL) return topLevelWindowHandle;

            // 親ウィンドウを次の判定対象にする
            topLevelWindowHandle = parentWindow;
        }
    }
}
