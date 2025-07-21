/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
インポートアドレステーブルに対する処理を保持するクラス

Injector.h
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#include "../Common/Windows.h"

namespace HW::UnityEditorWindowCorner::IAT
{
    /// <summary>
    /// インポートアドレステーブルに対する処理を保持するクラス
    /// </summary>
    class Injector final
    {
    public:
        /// <summary>
        /// 関数を置き換える
        /// </summary>
        /// <param name="targetModuleName">対象の関数をインポートしているモジュール名(nullptrを指定すると実行中のexeが指定される)</param>
        /// <param name="functionModuleName">対象の関数をエクスポートするモジュール名(nullptrを指定するとインポート対象がすべて検索される)</param>
        /// <param name="targetFunctionName">対象のエクスポートされた関数の関数名</param>
        /// <param name="newFunctionPointer">置き換える関数の関数ポインタ</param>
        /// <param name="oldFunctionPointer">置き換えに成功した場合、置き換える前の関数ポインタ(nullptrを指定すると値が渡されない)</param>
        /// <returns>処理結果</returns>
        static const bool ReplaceFunction(const char* targetModuleName,
            const char* functionModuleName, const char* targetFunctionName,
            const void* newFunctionPointer, void** oldFunctionPointer) noexcept;

    private:
        /// <summary>
        /// ベースアドレスを取得する
        /// </summary>
        /// <param name="targetModuleName">対象の関数をインポートしているモジュール名</param>
        /// <param name="baseAddress">ベースアドレス</param>
        /// <returns>DLLの名前</returns>
        static const bool GetBaseAddress(
            const char* targetModuleName, intptr_t& baseAddress) noexcept;

        /// <summary>
        /// モジュールのインポート情報を取得する
        /// </summary>
        /// <param name="baseAddress">ベースアドレス</param>
        /// <param name="descriptor">インポート情報</param>
        /// <param name="dataSize">データサイズ</param>
        static const bool GetImageImportDescriptor(void* baseAddress,
            PIMAGE_IMPORT_DESCRIPTOR& descriptor, ULONG& dataSize)  noexcept;

        /// <summary>
        /// THUNK情報を取得する
        /// </summary>
        /// <param name="baseAddress">ベースアドレス</param>
        /// <param name="descriptor">インポート情報</param>
        /// <param name="first">descriptorのFirstThunk</param>
        /// <param name="originalFirst">descriptorのOriginalFirstThunk</param>
        static void GetThunks(
            const intptr_t baseAddress, const PIMAGE_IMPORT_DESCRIPTOR descriptor,
            PIMAGE_THUNK_DATA& first, PIMAGE_THUNK_DATA& originalFirst) noexcept;

        /// <summary>
        /// インポートされたDLLの名前を取得する
        /// </summary>
        /// <param name="baseAddress">ベースアドレス</param>
        /// <param name="descriptor">インポート情報</param>
        /// <returns>DLLの名前</returns>
        static const char* GetImportedModuleName(
            const intptr_t baseAddress, const PIMAGE_IMPORT_DESCRIPTOR descriptor) noexcept;

        /// <summary>
        /// 関数のインポート名情報を取得する
        /// </summary>
        /// <param name="baseAddress">ベースアドレス</param>
        /// <param name="originalFirst">descriptorのOriginalFirstThunk</param>
        /// <returns>関数のインポート名情報へのポインタ</returns>
        static const PIMAGE_IMPORT_BY_NAME GetImportName(
            const intptr_t baseAddress, const PIMAGE_THUNK_DATA originalFirstThunk) noexcept;

        /// <summary>
        /// 関数ポインタを置き換える
        /// </summary>
        /// <param name="first">descriptorのFirstThunk</param>
        /// <param name="newFunctionPointer">置き換える関数の関数ポインタ</param>
        /// <param name="oldFunctionPointer">置き換えに成功した場合、置き換える前の関数ポインタ</param>
        /// <returns>処理結果</returns>
        static const bool ReplaceFunctionPointer(const PIMAGE_THUNK_DATA& first,
            const void* newFunctionPointer, void** oldFunctionPointer) noexcept;
    };
}
