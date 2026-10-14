#include "Half.h"

float Half::halfToFloat(uint16_t half) noexcept
{
    return _cvtsh_ss(half);
}
uint16_t Half::floatToHalf(float input) noexcept
{
    return _cvtss_sh(input, _MM_FROUND_TO_NEAREST_INT);
}
