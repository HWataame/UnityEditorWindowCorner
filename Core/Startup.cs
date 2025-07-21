/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
エディター初期化時にウィンドウの角の処理を実行するクラス

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
using HW.UnityEditorWindowCorner.Libraries;
using System;
using UnityEditor;
using UnityEngine;

namespace HW.UnityEditorWindowCorner
{
    /// <summary>
    /// エディター初期化時にウィンドウの角の処理を実行するクラス
    /// </summary>
    internal static class Startup
    {
        /// <summary>
        /// エディター初期化時に実行される処理
        /// </summary>
        [InitializeOnLoadMethod]
        private static void OnEditorInitialize()
        {
            // 処理が許可されなかった場合は何もしない
            if (!EditorStartupChecker.TryFirstProcess()) return;

            if (IntPtr.Size != 8)
            {
                // ポインタのサイズが8以外(アプリケーションが64ビット以外)である場合は何もしない
                Debug.LogError("[UnityEditorWindowCorner] 64ビットアプリケーション以外で実行されています\n" +
                    $"現在の環境: {IntPtr.Size * 8}ビットアプリケーションから実行");
            }

            // 初期化時の処理(ウィンドウの角の処理)を実行する
            if (!UnityEditorWindowCornerWrapper.OnUnityEditorInitialize())
            {
                // ウィンドウの角を処理できなかった場合
                Debug.LogError("[UnityEditorWindowCorner] ウィンドウの角を変更できませんでした");
            }
        }
    }
}
