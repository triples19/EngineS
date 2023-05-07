#pragma once

#include <iterator>
#include <string>
#include <vector>

#include "Core/Container/Iterator.hpp"
#include "Core/Macros.hpp"

namespace EngineS {

class String {
  public:
    using Iterator      = RandomAccessIterator<char>;
    using ConstIterator = RandomAccessIterator<const char>;

    static constexpr u32 NPos = static_cast<u32>(-1);

    /// Construct an empty string
    String() noexcept {
        SetShortStringLength(0);
        _data.shortString.buffer[0] = '\0';
    }

    /// Copy construct from another string
    /// \param other The string to copy from
    String(const String& other) : String() {
        Resize(other.Length());
        CopyChars(GetBuffer(), other.GetBuffer(), other.Length());
    }

    /// Move construct from another string
    /// \param other The String to move from
    String(String&& other) noexcept : String() { Swap(other); }

    /// Construct from a C string
    /// \param cstr C String
    String(const char* cstr) : String() {
        auto cstrLen = CStringLength(cstr);
        Resize(cstrLen);
        CopyChars(GetBuffer(), cstr, cstrLen);
    }

    /// Construct from a char array and length
    /// \param cstr Char array or C String
    /// \param len Length
    String(const char* cstr, u32 len) : String() {
        Resize(len);
        CopyChars(GetBuffer(), cstr, len);
    }

    /// Destructor
    ~String() {
        if (!IsShort())
            delete[] _data.longString.buffer;
    }

    /// Assign a string
    String& operator=(const String& rhs) {
        String temp(rhs);
        Swap(temp);
        return *this;
    }

    /// Move assign a string
    String& operator=(String&& rhs) {
        Swap(rhs);
        return *this;
    }

    /// Assign a C stirng
    String& operator=(const char* rhs) {
        String temp(rhs);
        Swap(temp);
        return *this;
    }

    /// Add-assign a stirng
    String& operator+=(const String& rhs) {
        auto oldLen = Length();
        Resize(oldLen + rhs.Length());
        CopyChars(GetBuffer() + oldLen, rhs.GetBuffer(), rhs.Length());
        return *this;
    }

    /// Add-assign a C stirng
    String& operator+=(const char* rhs) {
        auto oldLen = Length();
        auto rhsLen = CStringLength(rhs);
        Resize(oldLen + rhsLen);
        CopyChars(GetBuffer() + oldLen, rhs, rhsLen);
        return *this;
    }

    /// Add-assign a character
    String& operator+=(char rhs) {
        auto oldLen = Length();
        Resize(oldLen + 1);
        GetBuffer()[oldLen] = rhs;
        return *this;
    }

    /// Add a string
    String operator+(const String& rhs) const {
        String result(*this);
        result += rhs;
        return result;
    }

    /// Add a C string
    String operator+(const char* rhs) const {
        String result(*this);
        result += rhs;
        return result;
    }

    /// Return const char at index
    const char& operator[](u32 index) const {
        ES_ASSERT(index >= 0 && index < Length());
        return GetBuffer()[index];
    }

    /// Return char at index
    char& operator[](u32 index) {
        ES_ASSERT(index >= 0 && index < Length());
        return GetBuffer()[index];
    }

    /// Return const char at index
    const char& At(u32 index) const {
        ES_ASSERT(index >= 0 && index < Length());
        return GetBuffer()[index];
    }

    /// Return char at index
    char& At(u32 index) {
        ES_ASSERT(index >= 0 && index < Length());
        return GetBuffer()[index];
    }

    /// Append a character
    String& Append(char c) { return *this += c; }
    /// Append a C string
    String& Append(const char* cstr) { return *this += cstr; }
    /// Append a string
    String& Append(const String& str) { return *this += str; }
    /// Append a char array and length
    String& Append(const char* cstr, u32 len) {
        if (cstr) {
            auto oldLen = Length();
            Resize(oldLen + len);
            CopyChars(GetBuffer() + oldLen, cstr, len);
        }
        return *this;
    }

    /// Equality operator
    bool operator==(const String& rhs) const {
        if (Length() != rhs.Length())
            return false;
        return std::strcmp(CString(), rhs.CString()) == 0;
    }

    /// Three-way comparison
    std::strong_ordering operator<=>(const String& rhs) const {
        int cmp = std::strcmp(CString(), rhs.CString());
        if (cmp < 0)
            return std::strong_ordering::less;
        else if (cmp > 0)
            return std::strong_ordering::greater;
        else
            return std::strong_ordering::equal;
    }

    /// Return the pointer to buffer
    char* GetBuffer() { return IsShort() ? _data.shortString.buffer : _data.longString.buffer; }

    /// Return const pointer to buffer
    const char* GetBuffer() const { return IsShort() ? _data.shortString.buffer : _data.longString.buffer; }

    /// Return the C string
    const char* CString() const { return GetBuffer(); }

    /// Return the length
    u32 Length() const { return IsShort() ? GetShortStringLength() : _data.longString.length; }

    /// Return the capacity
    u32 Capacity() const { return IsShort() ? ShortStringCapacity : _data.longString.capacity; }

    /// Return true if the string is empty
    bool Empty() const { return Length() == 0; }

    /// Resize the string
    void Resize(u32 newLen);

    /// Swap with another string
    void Swap(String& other) { std::swap(_data, other._data); }

    /// Return the length of C string
    /// This function is safe when cstr is nullptr
    static u32 CStringLength(const char* cstr) { return cstr ? std::strlen(cstr) : 0; }

    /// Find the first occurrence of a character in string
    /// \param c The character to find for
    /// \param beginPos The position to start searching
    /// \return The index of the first occurrence of a character or NPos if not found
    u32 Find(char c, u32 beginPos = 0) const;

    /// Find the first occurrence of a string in string
    /// \param str The string to find for
    /// \param beginPos The position to start searching
    /// \return The index of the first occurrence of a string or NPos if not found
    u32 Find(const String& str, u32 beginPos = 0) const;

    /// Find the last occurrence of a character in string
    /// \param c The character to find for
    /// \param beginPos The position to start searching (backwards)
    /// \return The index of the last occurrence of a character or NPos if not found
    u32 FindLast(char c, u32 beginPos = NPos) const;

    /// Find the last occurrence of a string in string
    /// \param str The string to find for
    /// \param beginPos The position to start searching (backwards)
    /// \return The index of the last occurrence of a string or NPos if not found
    u32 FindLast(const String& str, u32 beginPos = NPos) const;

    /// Return true if starts with a string
    bool StartsWith(const String& str) const;

    /// Return true if ends with a string
    bool EndsWith(const String& str) const;

    /// Return string in uppercase
    String ToUpper() const;

    /// Return string in lowercase
    String ToLower() const;

    /// Return a string with whitespaces trimmed from the beginning and the end
    String Trimmed() const;

    /// Return true if contains a character
    bool Contains(char c) const;

    /// Return true if contains a string
    bool Contains(const String& str) const;

    /// Return a substring from \p pos with \p length or to the end if \p length is NPos
    String Substring(u32 pos, u32 length = NPos) const;

    /// Return std::string of the same string
    std::string ToStdString() const;

    /// Clear the string
    void Clear();

    /// Replace \p n characters beginning at index \p pos with the string \p after
    /// and return a reference to this string.
    String& Replace(u32 pos, u32 n, const String& after);

    /// Replace every occurrence of the character \p before with the character \p after
    /// and return a reference to this string.
    String& Replace(char before, char after);

    /// Replace every occurrence of the string \p before with the string \p after
    /// and return a reference to this string.
    String& Replace(const String& before, const String& after);

    /// Insert \p c at the given index \p pos in the string and return a reference to this string.
    ///
    /// This string grows to accommodate the insertion. If position is beyond the end of the string, space characters
    /// are appended to the string to reach this position, followed by \p c.
    String& Insert(u32 pos, char c);

    /// Insert \p str at given index \p pos in the string and return a reference to this string.
    ///
    /// This string grows to accommodate the insertion. If position is beyond the end of the string, space characters
    /// are appended to the string to reach this position, followed by \p str.
    String& Insert(u32 pos, const String& str);

    /// Remove \p n characters beginning at index \p pos and return a reference to this string.
    String& Remove(u32 pos, u32 n);

    /// Return substrings split by \p separator .
    std::vector<String> Split(char spearator) const;

  private:
    struct LongString {
        char* buffer;
        u32   length;
        u32   capacity;
    };

    static constexpr u32 ShortStringCapacity     = sizeof(LongString) - 1;
    static constexpr u8  ShortStringMask         = 0x80;
    static constexpr u8  InvertedShortStringMask = static_cast<u8>(~ShortStringMask);

    struct ShortString {
        char buffer[ShortStringCapacity];
        u8   length;
    };

    static_assert(sizeof(LongString) == sizeof(ShortString));

    union {
        LongString  longString;
        ShortString shortString;
    } _data;

    bool IsShort() const { return static_cast<bool>(_data.shortString.length & ShortStringMask); }

    u32 GetShortStringLength() const { return _data.shortString.length & InvertedShortStringMask; }

    void SetShortStringLength(u8 value) { _data.shortString.length = value | ShortStringMask; }

    /// Copy chars from one buffer to another.
    static void CopyChars(char* dest, const char* src, u32 count) {
        char* end = dest + count;
        while (dest != end) {
            *dest = *src;
            ++dest;
            ++src;
        }
    }

    /// Move a range of characters within the string.
    void MoveRange(u32 dest, u32 src, u32 count) {
        if (count) {
            char* buffer = GetBuffer();
            memmove(buffer + dest, buffer + src, count);
        }
    }

    static std::vector<String> SplitHelper(const char* str, char separator);
};

inline String operator+(const char* lhs, const String& rhs) {
    String ret(lhs);
    ret += rhs;
    return ret;
}

} // namespace EngineS
