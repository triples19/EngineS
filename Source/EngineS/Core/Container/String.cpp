#include "String.hpp"

namespace EngineS {

void String::Resize(u32 newLen) {
    auto capacity = Capacity();

    if (newLen && capacity < newLen + 1) {
        // Increase the capacity
        while (capacity < newLen + 1) capacity += (capacity + 1) / 2;

        auto newBuffer = new char[capacity];

        u32 oldLen = Length();
        if (oldLen)
            CopyChars(newBuffer, GetBuffer(), oldLen);

        if (!IsShort())
            delete[] _data.longString.buffer;

        newBuffer[newLen]         = '\0';
        _data.longString.buffer   = newBuffer;
        _data.longString.capacity = capacity;
        _data.longString.length   = newLen;
    } else {
        u32 oldLen = Length();
        // Keep the capacity
        if (IsShort()) {
            _data.shortString.buffer[oldLen] = ' ';
            _data.shortString.buffer[newLen] = '\0';
            SetShortStringLength(static_cast<u8>(newLen));
        } else {
            _data.longString.buffer[oldLen] = ' ';
            _data.longString.buffer[newLen] = '\0';
            _data.longString.length         = newLen;
        }
    }
}

u32 String::Find(char c, u32 beginPos) const {
    auto data = GetBuffer();
    auto len  = Length();
    for (u32 i = beginPos; i < len; ++i) {
        if (data[i] == c)
            return i;
    }
    return NPos;
}

u32 String::Find(const String& str, u32 beginPos) const {
    auto thisBuffer = GetBuffer(), otherBuffer = str.GetBuffer();
    auto thisLen = Length(), otherLen = str.Length();

    if (!otherLen || otherLen > thisLen)
        return NPos;

    auto first = otherBuffer[0];
    for (u32 i = beginPos; i <= thisLen - otherLen + 1; ++i) {
        char c = thisBuffer[i];
        if (c == first) {
            u32  skip  = NPos;
            bool found = true;
            for (u32 j = 1; j < otherLen; ++j) {
                c      = thisBuffer[i + j];
                char d = otherBuffer[j];
                if (skip == NPos && c == first) {
                    skip = i + j - 1;
                }
                if (c != d) {
                    found = false;
                    if (skip != NPos)
                        i = skip;
                    break;
                }
            }
            if (found)
                return i;
        }
    }
    return NPos;
}

u32 String::FindLast(char c, u32 beginPos) const {
    auto data = GetBuffer();
    auto len  = Length();

    if (beginPos == NPos || beginPos >= len) {
        beginPos = len - 1;
    }

    for (i32 i = beginPos; i >= 0; --i) {
        if (data[i] == c)
            return i;
    }
    return NPos;
}

u32 String::FindLast(const String& str, u32 beginPos) const {
    u32 thisLen = Length(), otherLen = str.Length();

    if (!otherLen || otherLen > thisLen) {
        return NPos;
    }

    if (beginPos == NPos || beginPos > thisLen - otherLen) {
        beginPos = thisLen - otherLen;
    }

    auto thisBuffer = GetBuffer(), otherBuffer = str.GetBuffer();
    char first = otherBuffer[0];
    for (i32 i = beginPos; i >= 0; --i) {
        char c = thisBuffer[i];
        if (c == first) {
            bool found = true;
            for (u32 j = 1; j < otherLen; ++j) {
                c      = thisBuffer[i + j];
                char d = otherBuffer[j];
                if (c != d) {
                    found = false;
                    break;
                }
            }
            if (found)
                return i;
        }
    }
    return NPos;
}

bool String::StartsWith(const String& str) const {
    auto strLen = str.Length();
    if (!strLen || Length() < strLen)
        return false;
    auto thisBuffer = GetBuffer(), otherBuffer = str.GetBuffer();
    for (u32 i = 0; i < strLen; ++i) {
        if (thisBuffer[i] != otherBuffer[i])
            return false;
    }
    return true;
}

bool String::EndsWith(const String& str) const {
    auto thisLen = Length(), otherLen = str.Length();
    if (!otherLen || thisLen < otherLen)
        return false;
    auto thisBuffer = GetBuffer(), otherBuffer = str.GetBuffer();
    for (u32 i = 0; i < otherLen; ++i) {
        if (thisBuffer[thisLen - 1 - i] != otherBuffer[otherLen - 1 - i])
            return false;
    }
    return true;
}

String String::ToUpper() const {
    String ret(*this);
    auto   buf    = GetBuffer();
    auto   len    = ret.Length();
    auto   retBuf = ret.GetBuffer();
    for (u32 i = 0; i < len; ++i) {
        retBuf[i] = static_cast<char>(toupper(buf[i]));
    }
    return ret;
}

String String::ToLower() const {
    String ret(*this);
    auto   buf    = GetBuffer();
    auto   len    = ret.Length();
    auto   retBuf = ret.GetBuffer();
    for (u32 i = 0; i < len; ++i) {
        retBuf[i] = static_cast<char>(tolower(buf[i]));
    }
    return ret;
}

bool String::Contains(char c) const {
    return Find(c) != NPos;
}

bool String::Contains(const String& str) const {
    return Find(str) != NPos;
}

String String::Substring(u32 pos, u32 length) const {
    auto thisLen = Length();
    if (pos >= thisLen)
        return {};
    if (length == NPos || pos + length > thisLen)
        length = thisLen - pos;
    String ret;
    ret.Resize(length);
    CopyChars(ret.GetBuffer(), GetBuffer() + pos, length);
    return ret;
}

String String::Trimmed() const {
    u32  begin = 0, end = Length();
    auto buf = GetBuffer();
    while (begin < end) {
        auto c = buf[begin];
        if (c != ' ' && c != 9)
            break;
        ++begin;
    }
    while (begin < end) {
        auto c = buf[end - 1];
        if (c != ' ' && c != 9)
            break;
        --end;
    }
    return Substring(begin, end - begin);
}

std::string String::ToStdString() const {
    return std::string(GetBuffer());
}

void String::Clear() {
    Resize(0);
}

String& String::Replace(u32 pos, u32 n, const String& after) {
    auto thisLen = Length(), otherLen = after.Length();
    i32  delta = static_cast<i32>(otherLen) - n;

    if (pos + n < thisLen) {
        if (delta < 0) {
            MoveRange(pos + otherLen, pos + n, thisLen - pos - n);
            Resize(thisLen + delta);
        }
        if (delta > 0) {
            Resize(thisLen + delta);
            thisLen = Length();
            MoveRange(pos + otherLen, pos + n, thisLen - pos - n - delta);
        }
    } else {
        Resize(thisLen + delta);
    }
    CopyChars(GetBuffer() + pos, after.GetBuffer(), after.Length());
    return *this;
}

String& String::Replace(char before, char after) {
    auto len = Length();
    auto buf = GetBuffer();
    for (u32 i = 0; i < len; ++i) {
        if (buf[i] == before)
            buf[i] = after;
    }
    return *this;
}

String& String::Replace(const String& before, const String& after) {
    u32 nextPos = 0;
    u32 thisLen = Length(), beforeLen = before.Length(), afterLen = after.Length();
    while (nextPos < thisLen) {
        auto pos = Find(before, nextPos);
        if (pos == NPos)
            break;
        Replace(pos, beforeLen, after);
        nextPos = pos + afterLen;
    }
    return *this;
}

String& String::Insert(u32 pos, char c) {
    u32 len = Length();
    if (pos >= len) {
        u32 oldLen = len;
        Resize(pos);
        len      = Length();
        auto buf = GetBuffer();
        for (u32 i = oldLen + 1; i < len; ++i) {
            buf[i] = ' ';
        }
        Append(c);
        return *this;
    }
    u32 oldLen = len;
    Resize(len + 1);
    MoveRange(pos + 1, pos, oldLen - pos);
    GetBuffer()[pos] = c;
    return *this;
}

String& String::Insert(u32 pos, const String& str) {
    u32 len = Length();
    if (pos >= len) {
        u32 oldLen = len;
        Resize(pos);
        len      = Length();
        auto buf = GetBuffer();
        for (u32 i = oldLen + 1; i < len; ++i) {
            buf[i] = ' ';
        }
        Append(str);
        return *this;
    }
    return Replace(pos, 0, str);
}

String& String::Remove(u32 pos, u32 n) {
    Replace(pos, n, "");
}

std::vector<String> String::Split(char spearator) const {
    return SplitHelper(CString(), spearator);
}

std::vector<String> String::SplitHelper(const char* str, char separator) {
    std::vector<String> ret;
    const char*         strEnd = str + CStringLength(str);

    for (const char* splitEnd = str; splitEnd != strEnd; ++splitEnd) {
        if (*splitEnd == separator) {
            const auto len = splitEnd - str;
            if (len > 0)
                ret.emplace_back(str, len);
            str = splitEnd + 1;
        }
    }

    const auto len = strEnd - str;
    if (len > 0)
        ret.emplace_back(str, len);

    return ret;
}

} // namespace EngineS
