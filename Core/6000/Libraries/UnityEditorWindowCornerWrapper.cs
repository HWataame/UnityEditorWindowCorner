/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
UnityEditorWindowCorner.dllの関数を呼び出せるようにするラッパークラス

UnityEditorWindowCornerWrapper.cs
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#if UNITY_EDITOR_WIN
using System.Runtime.InteropServices;

namespace HW.UnityEditorWindowCorner.Libraries
{
    /// <summary>
    /// UnityEditorWindowCorner.dllの関数を呼び出せるようにするラッパークラス
    /// </summary>
    internal static class UnityEditorWindowCornerWrapper
    {
        /// <summary>
        /// UnityEditorの初期化時の処理
        /// </summary>
        /// <param name="targetModuleName">関数をインポートしているモジュール名</param>
        /// <returns>処理結果</returns>
        [DllImport("UnityEditorWindowCorner_x64.dll", EntryPoint = "OnUnityEditorInitialize", CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.U1)]
        internal static extern bool OnUnityEditorInitialize(
            [MarshalAs(UnmanagedType.LPStr)] string targetModuleName);
    }
}
#endif
