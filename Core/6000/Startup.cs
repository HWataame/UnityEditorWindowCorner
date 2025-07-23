/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
エディター初期化時にウィンドウの角の処理を実行するクラス

Startup.cs
────────────────────────────────────────
バージョン: 1.0.1
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#if UNITY_EDITOR_WIN
using HW.UnityEditorWindowCorner.Libraries;
using System;
using System.Runtime.CompilerServices;
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

            // UnityEditorのメジャーバージョンを取得する
            if (GetUnityEditorMajorVersion(out var versionMajor))
            {
                bool isActive = false;
                string targetModuleName = null;
                switch (versionMajor)
                {
                    case 6000:
                        // 6000.xの場合(ShowWindowの参照はUnity.dllに分離されている)
                        targetModuleName = "Unity.dll";
                        isActive = true;
                        break;
                    default:
                        Debug.LogError($"[UnityEditorWindowCorner] Unityのバージョン{versionMajor}には対応していません");
                        break;
                }

                // 初期化時の処理(ウィンドウの角の処理)を実行する
                if (isActive && !UnityEditorWindowCornerWrapper.OnUnityEditorInitialize(targetModuleName))
                {
                    // ウィンドウの角を処理できなかった場合
                    Debug.LogError("[UnityEditorWindowCorner] ウィンドウの角を変更できませんでした");
                }
            }
        }

        /// <summary>
        /// UnityEditorのメジャーバージョンを取得する
        /// </summary>
        /// <param name="majorVersion">UnityEditorのメジャーバージョン</param>
        /// <returns>処理結果</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static bool GetUnityEditorMajorVersion(out int majorVersion)
        {
            // バージョンの文字列からメジャーバージョンの取得を試行する
            var appVersionSplit = Application.unityVersion.Split('.');
            if (appVersionSplit == null || appVersionSplit.Length == 0 ||
                !int.TryParse(appVersionSplit[0], out majorVersion))
            {
                // メジャーバージョンを取得できなかった場合は失敗
                majorVersion = 0;
                return false;
            }

            return true;
        }
    }
}
#endif
