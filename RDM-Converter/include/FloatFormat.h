#pragma once
#include <cmath>
#include <cstdio>
#include <string>

// Same output as std::to_string(double) ("%f", 6 decimals), but exact ties are rounded away
// from zero. glibc and msvcrt disagree on ties (round-half-even vs round-half-up), so this keeps
// the .obj output identical on every platform.
inline std::string formatFloat(double value)
{
    // spelled out explicitly: msvcrt (MinGW) prints "nan" and "1.#INF" where UCRT and glibc differ
    if (std::isnan(value))
        return std::signbit(value) ? "-nan" : "nan";
    if (std::isinf(value))
        return value < 0 ? "-inf" : "inf";

    char exact[512];
    // a float has at most 149 fractional decimal digits, so this expansion is exact
    std::snprintf(exact, sizeof exact, "%.150f", value);
    std::string s = exact;

    const size_t keep = s.find('.') + 7; // sign, integer part, dot, 6 decimals
    const bool   roundUp = s[keep] >= '5';
    s.resize(keep);

    if (roundUp) {
        int i = static_cast<int>(s.size()) - 1;
        for (; i >= 0; --i) {
            if (s[i] == '.')
                continue;
            if (s[i] == '-')
                break;
            if (s[i] == '9') {
                s[i] = '0';
                continue;
            }
            s[i]++;
            break;
        }
        if (i < 0 || s[i] == '-')
            s.insert(static_cast<size_t>(i + 1), 1, '1');
    }
    return s;
}
