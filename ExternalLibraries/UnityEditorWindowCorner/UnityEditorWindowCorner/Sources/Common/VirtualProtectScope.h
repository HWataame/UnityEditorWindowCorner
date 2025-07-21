/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
部分的なVirtualProtectの操作を補助するスコープ

VirtualProtectScope.h
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#pragma once
#include "Windows.h"

namespace HW::UnityEditorWindowCorner::Common
{
    /// <summary>
    /// 部分的なVirtualProtectの操作を補助するスコープ
    /// </summary>
    class VirtualProtectScope final
    {
    public:
        /// <summary>
        /// スコープを開始する
        /// </summary>
        /// <param name="address">保護状態を変更する領域の開始アドレス</param>
        /// <param name="size">保護状態を変更する領域のサイズ</param>
        /// <param name="protect">設定する保護状態の種別</param>
        VirtualProtectScope(
            void* address, const size_t size, const DWORD protect) noexcept;

        /// <summary>
        /// ムーブコンストラクタ
        /// </summary>
        /// <param name="source">移動元</param>
        VirtualProtectScope(VirtualProtectScope&& source) noexcept;

        /// <summary>
        /// ムーブ代入演算子
        /// </summary>
        /// <param name="source">移動元</param>
        /// <returns>移動先</returns>
        VirtualProtectScope& operator=(VirtualProtectScope&& source) noexcept;

        /// <summary>
        /// スコープが有効か
        /// </summary>
        /// <returns>判定結果</returns>
        const bool IsValid() const noexcept;

        /// <summary>
        /// 領域の開始アドレスを取得する
        /// </summary>
        /// <returns>領域の開始アドレス(スコープが有効ではない場合はnullptr)</returns>
        void* GetAddress() const noexcept;

        /// <summary>
        /// 領域のサイズを取得する
        /// </summary>
        /// <returns>領域のサイズ(スコープが有効ではない場合は0)</returns>
        size_t GetSize() const noexcept;

        /// <summary>
        /// スコープを終了する
        /// </summary>
        ~VirtualProtectScope() noexcept;

    private:
        /// <summary>
        /// このスコープが有効か
        /// </summary>
        bool isValid;
        /// <summary>
        /// 保護状態を変更する領域の先頭アドレス
        /// </summary>
        void* address;
        /// <summary>
        /// 保護状態を変更する領域のサイズ
        /// </summary>
        size_t size;
        /// <summary>
        /// スコープ開始前の保護状態
        /// </summary>
        DWORD originalProtect;
    };
}
