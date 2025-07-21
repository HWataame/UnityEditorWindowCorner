/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
文字列に対する処理を保持するヘッダーファイル

TextUtil.h
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#pragma once

namespace HW::UnityEditorWindowCorner::Common
{
	/// <summary>
	/// 文字列がnullまたは空文字列であるか判定する
	/// </summary>
	/// <param name="input">文字列</param>
	/// <returns>判定結果</returns>
	inline const bool StringIsNullOrEmpty(const char* input) noexcept
	{
		// 入力文字列がnullである場合／1バイト目がヌル文字である場合はtrue
		return input == nullptr || *input == '\0';
	}
}
