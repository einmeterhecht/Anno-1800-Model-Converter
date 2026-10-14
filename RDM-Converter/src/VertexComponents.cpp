#include "VertexComponents.h"
#include "FloatFormat.h"
#include <algorithm>

template <> std::string GeometricVertex<uint16_t>::toOBJ()
{
    return "v " + formatFloat(Half::halfToFloat(x)) + " " + formatFloat(Half::halfToFloat(y))
           + " " + formatFloat(Half::halfToFloat(z)) + "\n";
}

template <> std::string GeometricVertex<float>::toOBJ()
{
    return "v " + formatFloat(x) + " " + formatFloat(y) + " " + formatFloat(z) + "\n";
}

template <> std::string Normal<uint8_t>::toOBJ()
{
    return "vn " + formatFloat(((x * 2.0F / 255.0F) - 1.0F)) + " "
           + formatFloat(((y * 2.0F / 255.0F) - 1.0F)) + " "
           + formatFloat(((z * 2.0F / 255.0F) - 1.0F)) + "\n";
}
inline uint8_t limit(float value, float min, float max) {

	return std::max(std::min(value, max), min);

}
inline uint8_t singleScale(float value)
{
    float normalised = (value + 1.0F) / 2.0F;
    return limit(normalised * 255.0F, 0.0F, 255.0F);
}
template <> Normal<uint8_t> Normal<float>::scale()
{
    return Normal<uint8_t>(singleScale(x), singleScale(y), singleScale(z));
}
template <> Tangent<uint8_t> Tangent<float>::scale()
{
    return Tangent<uint8_t>({singleScale(x), singleScale(y), singleScale(z)});
}
template <> BiTangent<uint8_t> BiTangent<float>::scale()
{
    return BiTangent<uint8_t>({singleScale(x), singleScale(y), singleScale(z)});
}
template <> std::string TextureVertex<uint16_t>::toOBJ()
{
    // invert v to make the textures a fit
    return "vt " + formatFloat(Half::halfToFloat(u)) + " "
           + formatFloat(1.0F - Half::halfToFloat(v)) + "\n";
}
template <> std::string TextureVertex<float>::toOBJ()
{
    return "vt " + formatFloat(u) + " " + formatFloat(v) + "\n";
}

// let´s just make sure i don´t mess the sizes up anytime soon
static_assert(sizeof(GeometricVertex<uint16_t>) == 6);
static_assert(sizeof(GeometricVertex<float>) == 12);
static_assert(sizeof(Normal<uint8_t>) == 3);
static_assert(sizeof(Tangent<uint8_t>) == 3);
static_assert(sizeof(BiTangent<uint8_t>) == 3);
static_assert(sizeof(TextureVertex<uint16_t>) == 4);
static_assert(sizeof(TextureVertex<float>) == 8);