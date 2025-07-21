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
    /// ウィンドウの角の種類を取得する
    /// </summary>
    /// <param name="windowHandle">ウィンドウのハンドル</param>
    /// <param name="type">ウィンドウの角の種類</param>
    /// <returns>処理結果</returns>
    const bool WindowCorner::Get(const HWND windowHandle, WindowCornerType& type) noexcept
    {
        // ウィンドウハンドルがNULLである場合は失敗
        if (windowHandle == NULL) return false;

        // トップレベルのウィンドウのハンドルを取得する
        HWND topLevelWindowHandle = GetTopLevelWindowHandle(windowHandle);

        DWM_WINDOW_CORNER_PREFERENCE cornerType = DWMWCP_DEFAULT;
        auto result = DwmGetWindowAttribute(topLevelWindowHandle,
            DWMWA_WINDOW_CORNER_PREFERENCE, &cornerType, sizeof(DWM_WINDOW_CORNER_PREFERENCE));

        if (SUCCEEDED(result))
        {
            // ウィンドウの角の種類を取得できた場合
            type = static_cast<WindowCornerType>(cornerType);
            return true;
        }
        else
        {
            // ウィンドウの角の種類を取得できなかった場合は失敗
            type = WindowCornerType::Default;
            return false;
        }
    }

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
    /// 自身のプロセスのウィンドウの角を処理する
    /// </summary>
    /// <returns>処理結果</returns>
    const bool WindowCorner::ProcessSelfWindowCorners() noexcept
    {
        // ウィンドウの角を処理する(自身のプロセスIDをパラメーターとして渡す)
        return EnumWindows(ProcessSelfWindowCornersCallback,
            static_cast<LPARAM>(GetCurrentProcessId())) != 0;
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

    /// <summary>
    /// ProcessSelfWindowCornersの列挙処理のコールバック用関数
    /// </summary>
    /// <param name="windowHandle">ウィンドウハンドル</param>
    /// <param name="parameter">パラメーター</param>
    /// <returns>列挙を続行するか</returns>
    BOOL CALLBACK WindowCorner::ProcessSelfWindowCornersCallback(HWND windowHandle, LPARAM parameter) noexcept
    {
        // ウィンドウのプロセスIDを取得する
        DWORD windowProcessId;
        if (!GetWindowThreadProcessId(windowHandle, &windowProcessId))
        {
            // ウィンドウのプロセスIDを取得できなかった場合は次のウィンドウの処理に進む
            return TRUE;
        }

        // 自身のプロセスID(parameter経由で取得)とウィンドウのプロセスIDが異なる場合は次のウィンドウの処理に進む
        if (static_cast<DWORD>(parameter) != windowProcessId) return TRUE;

        WindowCornerType originalCornerType;
        if (!Get(windowHandle, originalCornerType) || originalCornerType != WindowCornerType::Default)
        {
            // ウィンドウの角の種類がOSの既定値ではない場合は次のウィンドウの処理に進む
            return TRUE;
        }

        // ウィンドウの角を丸めないように設定する
        Set(windowHandle, WindowCornerType::DoNotRound, nullptr);

        // 次のウィンドウの処理に進む
        return TRUE;
    }
}
