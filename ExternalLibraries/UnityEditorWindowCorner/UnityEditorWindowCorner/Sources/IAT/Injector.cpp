/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
インポートアドレステーブルに対する処理を保持するクラス

Injector.cpp
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#include "Injector.h"
#include "../Common/TextUtil.h"
#include "../Common/VirtualProtectScope.h"
#include <ImageHlp.h>
#pragma comment(lib, "imagehlp.lib")
using namespace HW::UnityEditorWindowCorner::Common;

namespace HW::UnityEditorWindowCorner::IAT
{
    /// <summary>
    /// 関数を置き換える
    /// </summary>
    /// <param name="targetModuleName">対象の関数をインポートしているモジュール名(nullptrを指定すると実行中のexeが指定される)</param>
    /// <param name="functionModuleName">対象の関数をエクスポートするモジュール名(nullptrを指定するとインポート対象がすべて検索される)</param>
    /// <param name="targetFunctionName">対象のエクスポートされた関数の関数名</param>
    /// <param name="newFunctionPointer">置き換える関数の関数ポインタ</param>
    /// <param name="oldFunctionPointer">置き換えに成功した場合、置き換える前の関数ポインタ(nullptrを指定すると値が渡されない)</param>
    /// <returns>処理結果</returns>
    const bool Injector::ReplaceFunction(
        const char* targetModuleName, const char* functionModuleName, const char* targetFunctionName,
        const void* newFunctionPointer, void** oldFunctionPointer) noexcept
    {
        // 関数名がnullptrまたは空文字列である場合は失敗
        if (StringIsNullOrEmpty(targetFunctionName)) return false;

        // 指定されたモジュールのベースアドレスを取得できなかった場合は失敗
        intptr_t baseAddress;
        if (!GetBaseAddress(targetModuleName, baseAddress)) return false;

        PIMAGE_IMPORT_DESCRIPTOR descriptor;
        ULONG dataSize;
        if (!GetImageImportDescriptor(reinterpret_cast<void*>(baseAddress), descriptor, dataSize))
        {
            // インポートテーブルを取得出来なかった場合は失敗
            return false;
        }

        for (; descriptor->Name != NULL; ++descriptor)
        {
            // THUNK情報を取得する
            PIMAGE_THUNK_DATA firstThunk, originalFirstThunk;
            GetThunks(baseAddress, descriptor, firstThunk, originalFirstThunk);

            // モジュール名を取得する
            const char* moduleName = GetImportedModuleName(baseAddress, descriptor);

            // エクスポート元のモジュール名が指定されていて、
            // 処理中のモジュール名と一致しない場合は次の関数の判定に進む
            if (functionModuleName != nullptr && _stricmp(functionModuleName, moduleName)) continue;

            // インポートテーブルの関数を列挙する
            for (; firstThunk->u1.Function != NULL; ++firstThunk, ++originalFirstThunk)
            {
                // 序数でのインポートである場合は次の関数の判定に進む
                if (IMAGE_SNAP_BY_ORDINAL(originalFirstThunk->u1.Ordinal)) continue;

                // インポート名情報を取得する
                auto importName = GetImportName(baseAddress, originalFirstThunk);

                if (!strcmp(targetFunctionName, importName->Name))
                {
                    // 関数名が一致した場合は関数ポインタの置き換えを試行する
                    return ReplaceFunctionPointer(firstThunk, newFunctionPointer, oldFunctionPointer);
                }
            }
        }

        // 指定された名前の関数が指定されたモジュールに存在しない場合は失敗
        return false;
    }

    /// <summary>
    /// ベースアドレスを取得する
    /// </summary>
    /// <param name="targetModuleName">対象の関数をインポートしているモジュール名</param>
    /// <param name="baseAddress">ベースアドレス</param>
    /// <returns>DLLの名前</returns>
    const bool Injector::GetBaseAddress(const char* targetModuleName, intptr_t& baseAddress) noexcept
    {
        // ベースアドレスを取得する
        baseAddress = reinterpret_cast<intptr_t>(GetModuleHandleA(targetModuleName));

        // ベースアドレスがNULLではない場合は成功
        return baseAddress != NULL;
    }

    /// <summary>
    /// モジュールのインポート情報を取得する
    /// </summary>
    /// <param name="baseAddress">ベースアドレス</param>
    /// <param name="descriptor">インポート情報</param>
    /// <param name="dataSize">データサイズ</param>
    /// <returns>処理結果</returns>
    const bool Injector::GetImageImportDescriptor(
        void* baseAddress, PIMAGE_IMPORT_DESCRIPTOR& descriptor, ULONG& dataSize) noexcept
    {
        // インポート情報の取得を試行する
        descriptor = static_cast<PIMAGE_IMPORT_DESCRIPTOR>(
            ImageDirectoryEntryToData(baseAddress, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &dataSize));

        // 結果がNULL以外であれば成功
        return descriptor != NULL;
    }

    /// <summary>
    /// インポートされたDLLの名前を取得する
    /// </summary>
    /// <param name="baseAddress">ベースアドレス</param>
    /// <param name="descriptor">インポート情報</param>
    /// <returns>DLLの名前</returns>
    const char* Injector::GetImportedModuleName(
        const intptr_t baseAddress, const PIMAGE_IMPORT_DESCRIPTOR descriptor) noexcept
    {
        return reinterpret_cast<char*>(baseAddress + descriptor->Name);
    }

    /// <summary>
    /// THUNK情報を取得する
    /// </summary>
    /// <param name="baseAddress">ベースアドレス</param>
    /// <param name="descriptor">インポート情報</param>
    /// <param name="first">descriptorのFirstThunk</param>
    /// <param name="originalFirst">descriptorのOriginalFirstThunk</param>
    void Injector::GetThunks(
        const intptr_t baseAddress, const PIMAGE_IMPORT_DESCRIPTOR descriptor,
        PIMAGE_THUNK_DATA& first, PIMAGE_THUNK_DATA& originalFirst) noexcept
    {
        // THUNK情報を取得する
        first = reinterpret_cast<PIMAGE_THUNK_DATA>(baseAddress + descriptor->FirstThunk);
        originalFirst = reinterpret_cast<PIMAGE_THUNK_DATA>(baseAddress + descriptor->OriginalFirstThunk);
    }

    /// <summary>
    /// 関数のインポート名情報を取得する
    /// </summary>
    /// <param name="baseAddress">ベースアドレス</param>
    /// <param name="originalFirst">descriptorのOriginalFirstThunk</param>
    /// <returns>関数のインポート名情報へのポインタ</returns>
    const PIMAGE_IMPORT_BY_NAME Injector::GetImportName(
        const intptr_t baseAddress, const PIMAGE_THUNK_DATA originalFirstThunk) noexcept
    {
        return reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(baseAddress + originalFirstThunk->u1.AddressOfData);
    }

    /// <summary>
    /// 関数ポインタを置き換える
    /// </summary>
    /// <param name="first">descriptorのFirstThunk</param>
    /// <param name="newFunctionPointer">置き換える関数の関数ポインタ</param>
    /// <param name="oldFunctionPointer">置き換えに成功した場合、置き換える前の関数ポインタ</param>
    /// <returns>処理結果</returns>
    const bool Injector::ReplaceFunctionPointer(const PIMAGE_THUNK_DATA& first,
        const void* newFunctionPointer, void** oldFunctionPointer) noexcept
    {
        // 書き換えるメモリの保護状態を一時的に変更する(スコープ終了時に復元される)
        auto function = &first->u1.Function;
        auto protectScope = VirtualProtectScope(
            reinterpret_cast<void*>(function), sizeof(function), PAGE_READWRITE);

        // メモリの保護状態を変更できなかった場合は失敗
        if (!protectScope.IsValid()) return false;

        if (oldFunctionPointer != nullptr)
        {
            // 変更前の関数ポインタを取得する
            *oldFunctionPointer = reinterpret_cast<void*>(*function);
        }

        // メモリを書き換える
        if (!WriteProcessMemory(GetCurrentProcess(),
            protectScope.GetAddress(), &newFunctionPointer, protectScope.GetSize(), NULL))
        {
            // 書き換えられなかった場合は失敗
            if (oldFunctionPointer != nullptr) *oldFunctionPointer = nullptr;
            return false;
        }

        return true;
    }
}
