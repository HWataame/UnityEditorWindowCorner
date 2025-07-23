/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
UnityEditorWindowCornerの初回処理判定用のクラス

EditorStartupChecker.cs
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#if UNITY_EDITOR_WIN
using System.Runtime.CompilerServices;
using UnityEditor;
using UnityEngine;

namespace HW.UnityEditorWindowCorner
{
    /// <summary>
    /// UnityEditorWindowCornerの初回処理判定用のクラス
    /// </summary>
    [FilePath("Temp/HW/UnityEditorWindowCorner/EditorStartupChecker.asset", FilePathAttribute.Location.ProjectFolder)]
    internal class EditorStartupChecker : ScriptableSingleton<EditorStartupChecker>
    {
        /// <summary>
        /// 既に処理されたか
        /// </summary>
        [SerializeField]
        private bool isAlreadyProcessed = false;

        /// <summary>
        /// 既に処理されたか
        /// </summary>
        internal static bool IsAlreadyProcessed
        {
            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            get => instance.isAlreadyProcessed;
        }


        /// <summary>
        /// 処理を許可するか判定する
        /// </summary>
        /// <returns>処理を許可するか</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static bool TryFirstProcess()
        {
            // インスタンスを取得する
            var instance = EditorStartupChecker.instance;

            // 既に処理されている場合は処理を許可しない
            if (instance.isAlreadyProcessed) return false;

            // 処理フラグを立てる
            instance.isAlreadyProcessed = true;
            instance.Save(true);

            // 処理を許可する
            return true;
        }
    }
}
#endif
