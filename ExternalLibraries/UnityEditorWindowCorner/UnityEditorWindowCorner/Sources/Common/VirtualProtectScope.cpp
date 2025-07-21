/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
部分的なVirtualProtectの操作を補助するスコープ

VirtualProtectScope.cpp
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#include "VirtualProtectScope.h"

namespace HW::UnityEditorWindowCorner::Common
{
    /// <summary>
    /// スコープを開始する
    /// </summary>
    /// <param name="address">保護状態を変更する領域の開始アドレス</param>
    /// <param name="size">保護状態を変更する領域のサイズ</param>
    /// <param name="protect">設定する保護状態の種別</param>
    VirtualProtectScope::VirtualProtectScope(
        void* address, const size_t size, const DWORD protect) noexcept
    {
        // 保護状態の変更を試行する
        DWORD originalProtect = 0;
        isValid = VirtualProtect(address, size, protect, &originalProtect);

        // 保護状態を変更できた場合は変更用の情報と変更前の保護状態を保持する
        this->address = isValid ? address : nullptr;
        this->size = isValid ? size : 0;
        this->originalProtect = isValid ? originalProtect : 0;
    }

    /// <summary>
    /// ムーブコンストラクタ
    /// </summary>
    /// <param name="source">移動元</param>
    VirtualProtectScope::VirtualProtectScope(VirtualProtectScope&& source) noexcept
    {
        isValid = source.isValid;
        if (isValid)
        {
            // 移動元が有効である場合は変更用の情報と変更前の保護状態を引き継ぐ
            address = source.address;
            size = source.size;
            originalProtect = source.originalProtect;

            // 移動元を無効化する
            source.isValid = false;
            source.address = nullptr;
            source.size = 0;
            source.originalProtect = 0;
        }
        else
        {
            // 移動元が有効ではない場合
            address = nullptr;
            size = 0;
            originalProtect = 0;
        }
    }

    /// <summary>
    /// ムーブ代入演算子
    /// </summary>
    /// <param name="source">移動元</param>
    /// <returns>移動先</returns>
    VirtualProtectScope& VirtualProtectScope::operator=(VirtualProtectScope&& source) noexcept
    {
        isValid = source.isValid;
        if (isValid)
        {
            // 移動元が有効である場合は変更用の情報と変更前の保護状態を引き継ぐ
            address = source.address;
            size = source.size;
            originalProtect = source.originalProtect;

            // 移動元を無効化する
            source.isValid = false;
            source.address = nullptr;
            source.size = 0;
            source.originalProtect = 0;
        }
        else
        {
            // 移動元が有効ではない場合
            address = nullptr;
            size = 0;
            originalProtect = 0;
        }

        return *this;
    }

    /// <summary>
    /// スコープが有効か
    /// </summary>
    /// <returns>判定結果</returns>
    const bool VirtualProtectScope::IsValid() const noexcept
    {
        return isValid;
    }

    /// <summary>
    /// 領域の開始アドレスを取得する
    /// </summary>
    /// <returns>領域の開始アドレス(スコープが有効ではない場合はnullptr)</returns>
    void* VirtualProtectScope::GetAddress() const noexcept
    {
        return isValid ? address : nullptr;
    }

    /// <summary>
    /// 領域のサイズを取得する
    /// </summary>
    /// <returns>領域のサイズ(スコープが有効ではない場合は0)</returns>
    size_t VirtualProtectScope::GetSize() const noexcept
    {
        return isValid ? size : 0;
    }

    /// <summary>
    /// スコープを終了する
    /// </summary>
    VirtualProtectScope::~VirtualProtectScope() noexcept
    {
        // スコープが有効ではない場合は何もしない
        if (!isValid) return;

        // 保護状態を復元する
        VirtualProtect(address, size, originalProtect, &originalProtect);
    }
}
