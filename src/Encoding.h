#pragma once

namespace Encoding
{
	std::wstring Utf8ToUtf16(const std::string& a_utf8) noexcept;

	std::string Utf16ToUtf8(const std::wstring& a_utf16) noexcept;
}
