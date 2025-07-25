/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
リソースファイル用の値を定義するヘッダーファイル
(文字化け防止のため、このファイルはUTF-16で保存されている)

resource.h
────────────────────────────────────────
バージョン: 1.0.0
2025 Wataame(HWataame)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
#pragma once
#include <Windows.h>

// 作者名
#define	VERSION_COMPANY_NAME            TEXT("Wataame(HWataame)")
// 著作権表記
#define	VERSION_LEGAL_COPYRIGHT         TEXT("2025 Wataame(HWataame)")

// 内部名
#define	VERSION_INTERNAL_NAME           TEXT("UnityEditorWindowCorner")

#ifdef WIN32
// ファイルの元の名前(32ビットDLL用)
#define	VERSION_ORIGINAL_FILE_NAME      TEXT("UnityEditorWindowCorner_x86.dll")

#else
// ファイルの元の名前(64ビットDLL用)
#define	VERSION_ORIGINAL_FILE_NAME      TEXT("UnityEditorWindowCorner_x64.dll")

#endif

// 製品名
#define	VERSION_PRODUCT_NAME            TEXT("UnityEditor Window Corner")
// 製品バージョン(文字列)
#define	VERSION_PRODUCT_VERSION         TEXT("1.0.0")
// 製品バージョン(数値)
#define	VERSION_PRODUCT_VERSION_ARRAY   1,0,0,0

// ファイルバージョン(文字列)
#define	VERSION_FILE_VERSION            TEXT("1.0.0")
// ファイルバージョン(数値)
#define	VERSION_FILE_VERSION_ARRAY      1,0,0,0

// コメント
#define	VERSION_COMMENT                 TEXT("UnityEditorのウィンドウの角の丸めを抑制するライブラリ")
// ファイルの説明
#define VERSION_FILE_DESCRIPTION        TEXT("UnityEditorのウィンドウの角の丸めを抑制するライブラリ")

#ifdef WIN32
// OS(32ビット用)
#define	VERSION_FILE_OS                 VOS_NT

#else
// OS(64ビット用が存在しないため不明)
#define	VERSION_FILE_OS                 VOS_UNKNOWN

#endif
// ファイルの種別
#define	VERSION_FILE_TYPE               VFT_DLL

// 言語
#define	VERSION_LANGUAGE                0x411
// 文字セット
#define	VERSION_CHARSET                 1200
