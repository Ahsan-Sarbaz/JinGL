#pragma once
#include <glm/glm.hpp>

/**
* Converts a 32-bit color in the format RRGGBBAA to a glm::vec4.
*
* @param color 32-bit color
* 
* @return glm::vec4 
*/
constexpr glm::vec4 Uint32ToVec4(uint32_t color)
{
	return glm::vec4(
		((color >> 24) & 0xFF) / 255.0f,
		((color >> 16) & 0xFF) / 255.0f,
		((color >> 8) & 0xFF) / 255.0f,
		(color & 0xFF) / 255.0f
	);
}

/**
* Converts a 32-bit color in the format RRGGBBXX to a glm::vec4.
* 
* @param color 32-bit color
* @param alpha Alpha value
* 
* @return glm::vec4
*/
constexpr glm::vec4 Uint32ToVec4(uint32_t color, float alpha)
{
	return glm::vec4(
		((color >> 24) & 0xFF) / 255.0f,
		((color >> 16) & 0xFF) / 255.0f,
		((color >> 8) & 0xFF) / 255.0f,
		alpha
	);
}

constexpr glm::vec4 ColorRed = Uint32ToVec4(0xFF0000FF);
constexpr glm::vec4 ColorGreen = Uint32ToVec4(0x00FF00FF);
constexpr glm::vec4 ColorBlue = Uint32ToVec4(0x0000FFFF);
constexpr glm::vec4 ColorYellow = Uint32ToVec4(0xFFFF00FF);
constexpr glm::vec4 ColorMagenta = Uint32ToVec4(0xFF00FFFF);
constexpr glm::vec4 ColorCyan = Uint32ToVec4(0x00FFFFFF);
constexpr glm::vec4 ColorWhite = Uint32ToVec4(0xFFFFFFFF);
constexpr glm::vec4 ColorBlack = Uint32ToVec4(0x000000FF);
constexpr glm::vec4 ColorGray = Uint32ToVec4(0x808080FF);
constexpr glm::vec4 ColorMaroon = Uint32ToVec4(0x800000FF);
constexpr glm::vec4 ColorDarkGreen = Uint32ToVec4(0x008000FF);
constexpr glm::vec4 ColorNavy = Uint32ToVec4(0x000080FF);
constexpr glm::vec4 ColorOlive = Uint32ToVec4(0x808000FF);
constexpr glm::vec4 ColorPurple = Uint32ToVec4(0x800080FF);
constexpr glm::vec4 ColorTeal = Uint32ToVec4(0x008080FF);
constexpr glm::vec4 ColorOrange = Uint32ToVec4(0xFFA500FF);
constexpr glm::vec4 ColorBrown = Uint32ToVec4(0xA52A2AFF);
constexpr glm::vec4 ColorBurlyWood = Uint32ToVec4(0xDEB887FF);
constexpr glm::vec4 ColorCadetBlue = Uint32ToVec4(0x5F9EA0FF);
constexpr glm::vec4 ColorChartreuse = Uint32ToVec4(0x7FFF00FF);
constexpr glm::vec4 ColorChocolate = Uint32ToVec4(0xD2691EFF);
constexpr glm::vec4 ColorCoral = Uint32ToVec4(0xFF7F50FF);
constexpr glm::vec4 ColorCornflowerBlue = Uint32ToVec4(0x6495EDFF);
constexpr glm::vec4 ColorCornsilk = Uint32ToVec4(0xFFF8DCFF);
constexpr glm::vec4 ColorCrimson = Uint32ToVec4(0xDC143CFF);
constexpr glm::vec4 ColorAqua = Uint32ToVec4(0x00FFFFFF);
constexpr glm::vec4 ColorGold = Uint32ToVec4(0xFFD700FF);
constexpr glm::vec4 ColorGoldenRod = Uint32ToVec4(0xDAA520FF);
constexpr glm::vec4 ColorGreenYellow = Uint32ToVec4(0xADFF2FFF);
constexpr glm::vec4 ColorLightCoral = Uint32ToVec4(0xF08080FF);
constexpr glm::vec4 ColorSalmon = Uint32ToVec4(0xFA8072FF);
constexpr glm::vec4 ColorDarkSalmon = Uint32ToVec4(0xE9967AFF);
constexpr glm::vec4 ColorLightSalmon = Uint32ToVec4(0xFFA07AFF);
constexpr glm::vec4 ColorLightSeaGreen = Uint32ToVec4(0x20B2AAFF);
constexpr glm::vec4 ColorMediumSeaGreen = Uint32ToVec4(0x3CB371FF);
constexpr glm::vec4 ColorSeaGreen = Uint32ToVec4(0x2E8B57FF);
constexpr glm::vec4 ColorDarkSlateGray = Uint32ToVec4(0x2F4F4FFF);
constexpr glm::vec4 ColorSlateGray = Uint32ToVec4(0x708090FF);
constexpr glm::vec4 ColorLightSlateGray = Uint32ToVec4(0x778899FF);
constexpr glm::vec4 ColorMediumSlateBlue = Uint32ToVec4(0x7B68EEFF);
constexpr glm::vec4 ColorSlateBlue = Uint32ToVec4(0x6A5ACDFF);
constexpr glm::vec4 ColorDarkSlateBlue = Uint32ToVec4(0x483D8BFF);
constexpr glm::vec4 ColorLavender = Uint32ToVec4(0xE6E6FAFF);
constexpr glm::vec4 ColorThistle = Uint32ToVec4(0xD8BFD8FF);
constexpr glm::vec4 ColorPlum = Uint32ToVec4(0xDDA0DDFF);
constexpr glm::vec4 ColorViolet = Uint32ToVec4(0xEE82EEFF);
constexpr glm::vec4 ColorOrchid = Uint32ToVec4(0xDA70D6FF);
constexpr glm::vec4 ColorFuchsia = Uint32ToVec4(0xFF00FFFF);
constexpr glm::vec4 ColorMediumOrchid = Uint32ToVec4(0xBA55D3FF);
constexpr glm::vec4 ColorDarkOrchid = Uint32ToVec4(0x9932CCFF);
constexpr glm::vec4 ColorDarkViolet = Uint32ToVec4(0x9400D3FF);
constexpr glm::vec4 ColorBlueViolet = Uint32ToVec4(0x8A2BE2FF);
constexpr glm::vec4 ColorDarkMagenta = Uint32ToVec4(0x8B008BFF);
constexpr glm::vec4 ColorMediumPurple = Uint32ToVec4(0x9370DBFF);
constexpr glm::vec4 ColorMediumTurquoise = Uint32ToVec4(0x48D1CCFF);
constexpr glm::vec4 ColorTurquoise = Uint32ToVec4(0x40E0D0FF);
constexpr glm::vec4 ColorLightSkyBlue = Uint32ToVec4(0x87CEFAFF);
constexpr glm::vec4 ColorSkyBlue = Uint32ToVec4(0x87CEEBFF);
constexpr glm::vec4 ColorDeepSkyBlue = Uint32ToVec4(0x00BFFFFF);
constexpr glm::vec4 ColorLightBlue = Uint32ToVec4(0xADD8E6FF);
constexpr glm::vec4 ColorPowderBlue = Uint32ToVec4(0xB0E0E6FF);
constexpr glm::vec4 ColorPaleTurquoise = Uint32ToVec4(0xAFEEEEFF);
constexpr glm::vec4 ColorDarkTurquoise = Uint32ToVec4(0x00CED1FF);
constexpr glm::vec4 ColorLightCyan = Uint32ToVec4(0xE0FFFFFF);
constexpr glm::vec4 ColorLightGoldenrodYellow = Uint32ToVec4(0xFAFAD2FF);
constexpr glm::vec4 ColorLemonChiffon = Uint32ToVec4(0xFFFACDFF);
constexpr glm::vec4 ColorLightYellow = Uint32ToVec4(0xFFFFE0FF);
constexpr glm::vec4 ColorLightGreen = Uint32ToVec4(0x90EE90FF);
constexpr glm::vec4 ColorPaleGreen = Uint32ToVec4(0x98FB98FF);
constexpr glm::vec4 ColorDarkSeaGreen = Uint32ToVec4(0x8FBC8FFF);
constexpr glm::vec4 ColorLinen = Uint32ToVec4(0xFAF0E6FF);
constexpr glm::vec4 ColorMistyRose = Uint32ToVec4(0xFFE4E1FF);
constexpr glm::vec4 ColorMoccasin = Uint32ToVec4(0xFFE4B5FF);
constexpr glm::vec4 ColorNavajoWhite = Uint32ToVec4(0xFFDEADFF);
constexpr glm::vec4 ColorOldLace = Uint32ToVec4(0xFDF5E6FF);
constexpr glm::vec4 ColorPapayaWhip = Uint32ToVec4(0xFFEFD5FF);
constexpr glm::vec4 ColorPeachPuff = Uint32ToVec4(0xFFDAB9FF);
constexpr glm::vec4 ColorPeru = Uint32ToVec4(0xCD853FFF);
constexpr glm::vec4 ColorPink = Uint32ToVec4(0xFFC0CBFF);
constexpr glm::vec4 ColorLightPink = Uint32ToVec4(0xFFB6C1FF);
constexpr glm::vec4 ColorHotPink = Uint32ToVec4(0xFF69B4FF);
constexpr glm::vec4 ColorDeepPink = Uint32ToVec4(0xFF1493FF);
constexpr glm::vec4 ColorMediumVioletRed = Uint32ToVec4(0xC71585FF);
constexpr glm::vec4 ColorPaleVioletRed = Uint32ToVec4(0xDB7093FF);
constexpr glm::vec4 ColorRosyBrown = Uint32ToVec4(0xBC8F8FFF);
constexpr glm::vec4 ColorSandyBrown = Uint32ToVec4(0xF4A460FF);
constexpr glm::vec4 ColorGoldenrod = Uint32ToVec4(0xDAA520FF);
constexpr glm::vec4 ColorKhaki = Uint32ToVec4(0xF0E68CFF);
constexpr glm::vec4 ColorLavenderBlush = Uint32ToVec4(0xFFF0F5FF);
constexpr glm::vec4 ColorLawnGreen = Uint32ToVec4(0x7CFC00FF);
constexpr glm::vec4 ColorLime = Uint32ToVec4(0x00FF00FF);
constexpr glm::vec4 ColorLimeGreen = Uint32ToVec4(0x32CD32FF);
constexpr glm::vec4 ColorMintCream = Uint32ToVec4(0xF5FFFAFF);
constexpr glm::vec4 ColorAliceBlue = Uint32ToVec4(0xF0F8FFFF);
constexpr glm::vec4 ColorAntiqueWhite = Uint32ToVec4(0xFAEBD7FF);
constexpr glm::vec4 ColorAzure = Uint32ToVec4(0xF0FFFFFF);
constexpr glm::vec4 ColorBeige = Uint32ToVec4(0xF5F5DCFF);
constexpr glm::vec4 ColorBisque = Uint32ToVec4(0xFFE4C4FF);
constexpr glm::vec4 ColorBlanchedAlmond = Uint32ToVec4(0xFFEBCDFF);
constexpr glm::vec4 ColorHoneydew = Uint32ToVec4(0xF0FFF0FF);
constexpr glm::vec4 ColorIvory = Uint32ToVec4(0xFFFFF0FF);
constexpr glm::vec4 ColorLightGray = Uint32ToVec4(0xD3D3D3FF);
constexpr glm::vec4 ColorLightSteelBlue = Uint32ToVec4(0xB0C4DEFF);
constexpr glm::vec4 ColorMediumAquamarine = Uint32ToVec4(0x66CDAAFF);
constexpr glm::vec4 ColorMediumBlue = Uint32ToVec4(0x0000CDFF);
