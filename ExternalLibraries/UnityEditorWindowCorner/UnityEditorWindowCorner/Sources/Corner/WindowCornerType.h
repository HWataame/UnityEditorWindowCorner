/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ウィンドウの角の種類を示す列挙型

WindowCornerType.h
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#pragma once
#include <dwmapi.h>

namespace HW::UnityEditorWindowCorner::Corner
{
	/// <summary>
	/// ウィンドウの角の種類を示す列挙型
	/// </summary>
	enum WindowCornerType
	{
		/// <summary>
		/// OSの既定値
		/// </summary>
		Default = DWMWCP_DEFAULT,
		/// <summary>
		/// 角を丸めない
		/// </summary>
		DoNotRound = DWMWCP_DONOTROUND,
		/// <summary>
		/// 角を丸める
		/// </summary>
		Round = DWMWCP_ROUND,
		/// <summary>
		/// 角を小さく丸める
		/// </summary>
		RoundSmall = DWMWCP_ROUNDSMALL
	};
}
