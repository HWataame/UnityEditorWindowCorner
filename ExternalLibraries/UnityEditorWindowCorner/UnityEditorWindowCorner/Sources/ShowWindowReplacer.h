/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ShowWindowを独自の処理に置き換えるクラス

ShowWindowReplacer.h
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#include "Common/Windows.h"

namespace HW::UnityEditorWindowCorner
{
    /// <summary>
    /// ShowWindowを独自の処理に置き換えるクラス
    /// </summary>
    class ShowWindowReplacer final
    {
    public:
        /// <summary>
        /// ShowWindowを独自の実装に置き換える
        /// </summary>
        /// <returns>処理結果</returns>
        static const bool ReplaceShowWindow() noexcept;

    private:
        /// <summary>
        /// 置き換え前のShowWindowの関数ポインタ
        /// </summary>
        static BOOL(*originalFunction)(HWND windowHandle, int showOption);


        /// <summary>
        /// デフォルトコンストラクタ(外部生成防止用)
        /// </summary>
        ShowWindowReplacer() noexcept;

        /// <summary>
        /// ShowWindow置き換え用の関数
        /// </summary>
        /// <param name="windowHandle">ウィンドウのハンドル</param>
        /// <param name="showOption">ウィンドウの表示方式</param>
        /// <returns>処理結果</returns>
        static BOOL CustomShowWindow(HWND windowHandle, int showOption) noexcept;
    };
}
