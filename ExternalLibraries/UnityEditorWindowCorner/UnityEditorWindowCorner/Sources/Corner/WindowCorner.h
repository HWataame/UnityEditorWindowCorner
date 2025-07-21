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
        /// ウィンドウの角の種類を取得する
        /// </summary>
        /// <param name="windowHandle">ウィンドウのハンドル</param>
        /// <param name="type">ウィンドウの角の種類</param>
        /// <returns>処理結果</returns>
        static const bool Get(const HWND windowHandle, WindowCornerType& type) noexcept;

        /// <summary>
        /// ウィンドウの角の種類を設定する
        /// </summary>
        /// <param name="windowHandle">ウィンドウのハンドル</param>
        /// <param name="newType">設定する角の種類</param>
        /// <param name="oldType">設定前の角の種類(nullptr指定可能)</param>
        /// <returns>処理結果</returns>
        static const bool Set(const HWND windowHandle,
            const WindowCornerType newType, WindowCornerType* oldType) noexcept;

        /// <summary>
        /// 自身のプロセスのウィンドウの角を処理する
        /// </summary>
        /// <returns>処理結果</returns>
        static const bool ProcessSelfWindowCorners() noexcept;

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

        /// <summary>
        /// ProcessSelfWindowCornersの列挙処理のコールバック用関数
        /// </summary>
        /// <param name="windowHandle">ウィンドウハンドル</param>
        /// <param name="parameter">パラメーター</param>
        /// <returns>列挙を続行するか</returns>
        static BOOL CALLBACK ProcessSelfWindowCornersCallback(
            HWND windowHandle, LPARAM parameter) noexcept;
    };
}
