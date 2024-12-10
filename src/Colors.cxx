//------------------------------------------------------------------------------
//
// Colors.cxx
//
//------------------------------------------------------------------------------
#include "Colors.hxx"

#include "Utilities.hxx"
#include "WinAPI.hxx"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <wchar.h>

namespace clime {

    struct ColorEntry {
        COLORREF       color;
        const wchar_t* name;
    };

    static ColorEntry g_colors[] = {
        { RGB( 0xF0, 0xF8, 0xFF ), L"AliceBlue" },
        { RGB( 0xFA, 0xEB, 0xD7 ), L"AntiqueWhite" },
        { RGB( 0xFF, 0xEF, 0xDB ), L"AntiqueWhite1" },
        { RGB( 0xEE, 0xDF, 0xCC ), L"AntiqueWhite2" },
        { RGB( 0xCD, 0xC0, 0xB0 ), L"AntiqueWhite3" },
        { RGB( 0x8B, 0x83, 0x78 ), L"AntiqueWhite4" },
        { RGB( 0xFF, 0xEB, 0xCD ), L"BlanchedAlmond" },
        { RGB( 0x8A, 0x2B, 0xE2 ), L"BlueViolet" },
        { RGB( 0x5F, 0x9E, 0xA0 ), L"CadetBlue" },
        { RGB( 0x98, 0xF5, 0xFF ), L"CadetBlue1" },
        { RGB( 0x8E, 0xE5, 0xEE ), L"CadetBlue2" },
        { RGB( 0x7A, 0xC5, 0xCD ), L"CadetBlue3" },
        { RGB( 0x53, 0x86, 0x8B ), L"CadetBlue4" },
        { RGB( 0x64, 0x95, 0xED ), L"CornflowerBlue" },
        { RGB( 0x00, 0x00, 0x8B ), L"DarkBlue" },
        { RGB( 0x00, 0x8B, 0x8B ), L"DarkCyan" },
        { RGB( 0xB8, 0x86, 0x0B ), L"DarkGoldenrod" },
        { RGB( 0xFF, 0xB9, 0x0F ), L"DarkGoldenrod1" },
        { RGB( 0xEE, 0xAD, 0x0E ), L"DarkGoldenrod2" },
        { RGB( 0xCD, 0x95, 0x0C ), L"DarkGoldenrod3" },
        { RGB( 0x8B, 0x65, 0x08 ), L"DarkGoldenrod4" },
        { RGB( 0xA9, 0xA9, 0xA9 ), L"DarkGray" },
        { RGB( 0x00, 0x64, 0x00 ), L"DarkGreen" },
        { RGB( 0xA9, 0xA9, 0xA9 ), L"DarkGrey" },
        { RGB( 0xBD, 0xB7, 0x6B ), L"DarkKhaki" },
        { RGB( 0x8B, 0x00, 0x8B ), L"DarkMagenta" },
        { RGB( 0x55, 0x6B, 0x2F ), L"DarkOliveGreen" },
        { RGB( 0xCA, 0xFF, 0x70 ), L"DarkOliveGreen1" },
        { RGB( 0xBC, 0xEE, 0x68 ), L"DarkOliveGreen2" },
        { RGB( 0xA2, 0xCD, 0x5A ), L"DarkOliveGreen3" },
        { RGB( 0x6E, 0x8B, 0x3D ), L"DarkOliveGreen4" },
        { RGB( 0xFF, 0x8C, 0x00 ), L"DarkOrange" },
        { RGB( 0xFF, 0x7F, 0x00 ), L"DarkOrange1" },
        { RGB( 0xEE, 0x76, 0x00 ), L"DarkOrange2" },
        { RGB( 0xCD, 0x66, 0x00 ), L"DarkOrange3" },
        { RGB( 0x8B, 0x45, 0x00 ), L"DarkOrange4" },
        { RGB( 0x99, 0x32, 0xCC ), L"DarkOrchid" },
        { RGB( 0xBF, 0x3E, 0xFF ), L"DarkOrchid1" },
        { RGB( 0xB2, 0x3A, 0xEE ), L"DarkOrchid2" },
        { RGB( 0x9A, 0x32, 0xCD ), L"DarkOrchid3" },
        { RGB( 0x68, 0x22, 0x8B ), L"DarkOrchid4" },
        { RGB( 0x8B, 0x00, 0x00 ), L"DarkRed" },
        { RGB( 0xE9, 0x96, 0x7A ), L"DarkSalmon" },
        { RGB( 0x8F, 0xBC, 0x8F ), L"DarkSeaGreen" },
        { RGB( 0xC1, 0xFF, 0xC1 ), L"DarkSeaGreen1" },
        { RGB( 0xB4, 0xEE, 0xB4 ), L"DarkSeaGreen2" },
        { RGB( 0x9B, 0xCD, 0x9B ), L"DarkSeaGreen3" },
        { RGB( 0x69, 0x8B, 0x69 ), L"DarkSeaGreen4" },
        { RGB( 0x48, 0x3D, 0x8B ), L"DarkSlateBlue" },
        { RGB( 0x2F, 0x4F, 0x4F ), L"DarkSlateGray" },
        { RGB( 0x97, 0xFF, 0xFF ), L"DarkSlateGray1" },
        { RGB( 0x8D, 0xEE, 0xEE ), L"DarkSlateGray2" },
        { RGB( 0x79, 0xCD, 0xCD ), L"DarkSlateGray3" },
        { RGB( 0x52, 0x8B, 0x8B ), L"DarkSlateGray4" },
        { RGB( 0x2F, 0x4F, 0x4F ), L"DarkSlateGrey" },
        { RGB( 0x00, 0xCE, 0xD1 ), L"DarkTurquoise" },
        { RGB( 0x94, 0x00, 0xD3 ), L"DarkViolet" },
        { RGB( 0xFF, 0x14, 0x93 ), L"DeepPink" },
        { RGB( 0xFF, 0x14, 0x93 ), L"DeepPink1" },
        { RGB( 0xEE, 0x12, 0x89 ), L"DeepPink2" },
        { RGB( 0xCD, 0x10, 0x76 ), L"DeepPink3" },
        { RGB( 0x8B, 0x0A, 0x50 ), L"DeepPink4" },
        { RGB( 0x00, 0xBF, 0xFF ), L"DeepSkyBlue" },
        { RGB( 0x00, 0xBF, 0xFF ), L"DeepSkyBlue1" },
        { RGB( 0x00, 0xB2, 0xEE ), L"DeepSkyBlue2" },
        { RGB( 0x00, 0x9A, 0xCD ), L"DeepSkyBlue3" },
        { RGB( 0x00, 0x68, 0x8B ), L"DeepSkyBlue4" },
        { RGB( 0x69, 0x69, 0x69 ), L"DimGray" },
        { RGB( 0x69, 0x69, 0x69 ), L"DimGrey" },
        { RGB( 0x1E, 0x90, 0xFF ), L"DodgerBlue" },
        { RGB( 0x1E, 0x90, 0xFF ), L"DodgerBlue1" },
        { RGB( 0x1C, 0x86, 0xEE ), L"DodgerBlue2" },
        { RGB( 0x18, 0x74, 0xCD ), L"DodgerBlue3" },
        { RGB( 0x10, 0x4E, 0x8B ), L"DodgerBlue4" },
        { RGB( 0xFF, 0xFA, 0xF0 ), L"FloralWhite" },
        { RGB( 0x22, 0x8B, 0x22 ), L"ForestGreen" },
        { RGB( 0xF8, 0xF8, 0xFF ), L"GhostWhite" },
        { RGB( 0xAD, 0xFF, 0x2F ), L"GreenYellow" },
        { RGB( 0xFF, 0x69, 0xB4 ), L"HotPink" },
        { RGB( 0xFF, 0x6E, 0xB4 ), L"HotPink1" },
        { RGB( 0xEE, 0x6A, 0xA7 ), L"HotPink2" },
        { RGB( 0xCD, 0x60, 0x90 ), L"HotPink3" },
        { RGB( 0x8B, 0x3A, 0x62 ), L"HotPink4" },
        { RGB( 0xCD, 0x5C, 0x5C ), L"IndianRed" },
        { RGB( 0xFF, 0x6A, 0x6A ), L"IndianRed1" },
        { RGB( 0xEE, 0x63, 0x63 ), L"IndianRed2" },
        { RGB( 0xCD, 0x55, 0x55 ), L"IndianRed3" },
        { RGB( 0x8B, 0x3A, 0x3A ), L"IndianRed4" },
        { RGB( 0xFF, 0xF0, 0xF5 ), L"LavenderBlush" },
        { RGB( 0xFF, 0xF0, 0xF5 ), L"LavenderBlush1" },
        { RGB( 0xEE, 0xE0, 0xE5 ), L"LavenderBlush2" },
        { RGB( 0xCD, 0xC1, 0xC5 ), L"LavenderBlush3" },
        { RGB( 0x8B, 0x83, 0x86 ), L"LavenderBlush4" },
        { RGB( 0x7C, 0xFC, 0x00 ), L"LawnGreen" },
        { RGB( 0xFF, 0xFA, 0xCD ), L"LemonChiffon" },
        { RGB( 0xFF, 0xFA, 0xCD ), L"LemonChiffon1" },
        { RGB( 0xEE, 0xE9, 0xBF ), L"LemonChiffon2" },
        { RGB( 0xCD, 0xC9, 0xA5 ), L"LemonChiffon3" },
        { RGB( 0x8B, 0x89, 0x70 ), L"LemonChiffon4" },
        { RGB( 0xAD, 0xD8, 0xE6 ), L"LightBlue" },
        { RGB( 0xBF, 0xEF, 0xFF ), L"LightBlue1" },
        { RGB( 0xB2, 0xDF, 0xEE ), L"LightBlue2" },
        { RGB( 0x9A, 0xC0, 0xCD ), L"LightBlue3" },
        { RGB( 0x68, 0x83, 0x8B ), L"LightBlue4" },
        { RGB( 0xF0, 0x80, 0x80 ), L"LightCoral" },
        { RGB( 0xE0, 0xFF, 0xFF ), L"LightCyan" },
        { RGB( 0xE0, 0xFF, 0xFF ), L"LightCyan1" },
        { RGB( 0xD1, 0xEE, 0xEE ), L"LightCyan2" },
        { RGB( 0xB4, 0xCD, 0xCD ), L"LightCyan3" },
        { RGB( 0x7A, 0x8B, 0x8B ), L"LightCyan4" },
        { RGB( 0xEE, 0xDD, 0x82 ), L"LightGoldenrod" },
        { RGB( 0xFF, 0xEC, 0x8B ), L"LightGoldenrod1" },
        { RGB( 0xEE, 0xDC, 0x82 ), L"LightGoldenrod2" },
        { RGB( 0xCD, 0xBE, 0x70 ), L"LightGoldenrod3" },
        { RGB( 0x8B, 0x81, 0x4C ), L"LightGoldenrod4" },
        { RGB( 0xFA, 0xFA, 0xD2 ), L"LightGoldenrodYellow" },
        { RGB( 0xD3, 0xD3, 0xD3 ), L"LightGray" },
        { RGB( 0x90, 0xEE, 0x90 ), L"LightGreen" },
        { RGB( 0xD3, 0xD3, 0xD3 ), L"LightGrey" },
        { RGB( 0xFF, 0xB6, 0xC1 ), L"LightPink" },
        { RGB( 0xFF, 0xAE, 0xB9 ), L"LightPink1" },
        { RGB( 0xEE, 0xA2, 0xAD ), L"LightPink2" },
        { RGB( 0xCD, 0x8C, 0x95 ), L"LightPink3" },
        { RGB( 0x8B, 0x5F, 0x65 ), L"LightPink4" },
        { RGB( 0xFF, 0xA0, 0x7A ), L"LightSalmon" },
        { RGB( 0xFF, 0xA0, 0x7A ), L"LightSalmon1" },
        { RGB( 0xEE, 0x95, 0x72 ), L"LightSalmon2" },
        { RGB( 0xCD, 0x81, 0x62 ), L"LightSalmon3" },
        { RGB( 0x8B, 0x57, 0x42 ), L"LightSalmon4" },
        { RGB( 0x20, 0xB2, 0xAA ), L"LightSeaGreen" },
        { RGB( 0x87, 0xCE, 0xFA ), L"LightSkyBlue" },
        { RGB( 0xB0, 0xE2, 0xFF ), L"LightSkyBlue1" },
        { RGB( 0xA4, 0xD3, 0xEE ), L"LightSkyBlue2" },
        { RGB( 0x8D, 0xB6, 0xCD ), L"LightSkyBlue3" },
        { RGB( 0x60, 0x7B, 0x8B ), L"LightSkyBlue4" },
        { RGB( 0x84, 0x70, 0xFF ), L"LightSlateBlue" },
        { RGB( 0x77, 0x88, 0x99 ), L"LightSlateGray" },
        { RGB( 0x77, 0x88, 0x99 ), L"LightSlateGrey" },
        { RGB( 0xB0, 0xC4, 0xDE ), L"LightSteelBlue" },
        { RGB( 0xCA, 0xE1, 0xFF ), L"LightSteelBlue1" },
        { RGB( 0xBC, 0xD2, 0xEE ), L"LightSteelBlue2" },
        { RGB( 0xA2, 0xB5, 0xCD ), L"LightSteelBlue3" },
        { RGB( 0x6E, 0x7B, 0x8B ), L"LightSteelBlue4" },
        { RGB( 0xFF, 0xFF, 0xE0 ), L"LightYellow" },
        { RGB( 0xFF, 0xFF, 0xE0 ), L"LightYellow1" },
        { RGB( 0xEE, 0xEE, 0xD1 ), L"LightYellow2" },
        { RGB( 0xCD, 0xCD, 0xB4 ), L"LightYellow3" },
        { RGB( 0x8B, 0x8B, 0x7A ), L"LightYellow4" },
        { RGB( 0x32, 0xCD, 0x32 ), L"LimeGreen" },
        { RGB( 0x66, 0xCD, 0xAA ), L"MediumAquamarine" },
        { RGB( 0x00, 0x00, 0xCD ), L"MediumBlue" },
        { RGB( 0xBA, 0x55, 0xD3 ), L"MediumOrchid" },
        { RGB( 0xE0, 0x66, 0xFF ), L"MediumOrchid1" },
        { RGB( 0xD1, 0x5F, 0xEE ), L"MediumOrchid2" },
        { RGB( 0xB4, 0x52, 0xCD ), L"MediumOrchid3" },
        { RGB( 0x7A, 0x37, 0x8B ), L"MediumOrchid4" },
        { RGB( 0x93, 0x70, 0xDB ), L"MediumPurple" },
        { RGB( 0xAB, 0x82, 0xFF ), L"MediumPurple1" },
        { RGB( 0x9F, 0x79, 0xEE ), L"MediumPurple2" },
        { RGB( 0x89, 0x68, 0xCD ), L"MediumPurple3" },
        { RGB( 0x5D, 0x47, 0x8B ), L"MediumPurple4" },
        { RGB( 0x3C, 0xB3, 0x71 ), L"MediumSeaGreen" },
        { RGB( 0x7B, 0x68, 0xEE ), L"MediumSlateBlue" },
        { RGB( 0x00, 0xFA, 0x9A ), L"MediumSpringGreen" },
        { RGB( 0x48, 0xD1, 0xCC ), L"MediumTurquoise" },
        { RGB( 0xC7, 0x15, 0x85 ), L"MediumVioletRed" },
        { RGB( 0x19, 0x19, 0x70 ), L"MidnightBlue" },
        { RGB( 0xF5, 0xFF, 0xFA ), L"MintCream" },
        { RGB( 0xFF, 0xE4, 0xE1 ), L"MistyRose" },
        { RGB( 0xFF, 0xE4, 0xE1 ), L"MistyRose1" },
        { RGB( 0xEE, 0xD5, 0xD2 ), L"MistyRose2" },
        { RGB( 0xCD, 0xB7, 0xB5 ), L"MistyRose3" },
        { RGB( 0x8B, 0x7D, 0x7B ), L"MistyRose4" },
        { RGB( 0xFF, 0xDE, 0xAD ), L"NavajoWhite" },
        { RGB( 0xFF, 0xDE, 0xAD ), L"NavajoWhite1" },
        { RGB( 0xEE, 0xCF, 0xA1 ), L"NavajoWhite2" },
        { RGB( 0xCD, 0xB3, 0x8B ), L"NavajoWhite3" },
        { RGB( 0x8B, 0x79, 0x5E ), L"NavajoWhite4" },
        { RGB( 0x00, 0x00, 0x80 ), L"NavyBlue" },
        { RGB( 0xFD, 0xF5, 0xE6 ), L"OldLace" },
        { RGB( 0x6B, 0x8E, 0x23 ), L"OliveDrab" },
        { RGB( 0xC0, 0xFF, 0x3E ), L"OliveDrab1" },
        { RGB( 0xB3, 0xEE, 0x3A ), L"OliveDrab2" },
        { RGB( 0x9A, 0xCD, 0x32 ), L"OliveDrab3" },
        { RGB( 0x69, 0x8B, 0x22 ), L"OliveDrab4" },
        { RGB( 0xFF, 0x45, 0x00 ), L"OrangeRed" },
        { RGB( 0xFF, 0x45, 0x00 ), L"OrangeRed1" },
        { RGB( 0xEE, 0x40, 0x00 ), L"OrangeRed2" },
        { RGB( 0xCD, 0x37, 0x00 ), L"OrangeRed3" },
        { RGB( 0x8B, 0x25, 0x00 ), L"OrangeRed4" },
        { RGB( 0xEE, 0xE8, 0xAA ), L"PaleGoldenrod" },
        { RGB( 0x98, 0xFB, 0x98 ), L"PaleGreen" },
        { RGB( 0x9A, 0xFF, 0x9A ), L"PaleGreen1" },
        { RGB( 0x90, 0xEE, 0x90 ), L"PaleGreen2" },
        { RGB( 0x7C, 0xCD, 0x7C ), L"PaleGreen3" },
        { RGB( 0x54, 0x8B, 0x54 ), L"PaleGreen4" },
        { RGB( 0xAF, 0xEE, 0xEE ), L"PaleTurquoise" },
        { RGB( 0xBB, 0xFF, 0xFF ), L"PaleTurquoise1" },
        { RGB( 0xAE, 0xEE, 0xEE ), L"PaleTurquoise2" },
        { RGB( 0x96, 0xCD, 0xCD ), L"PaleTurquoise3" },
        { RGB( 0x66, 0x8B, 0x8B ), L"PaleTurquoise4" },
        { RGB( 0xDB, 0x70, 0x93 ), L"PaleVioletRed" },
        { RGB( 0xFF, 0x82, 0xAB ), L"PaleVioletRed1" },
        { RGB( 0xEE, 0x79, 0x9F ), L"PaleVioletRed2" },
        { RGB( 0xCD, 0x68, 0x89 ), L"PaleVioletRed3" },
        { RGB( 0x8B, 0x47, 0x5D ), L"PaleVioletRed4" },
        { RGB( 0xFF, 0xEF, 0xD5 ), L"PapayaWhip" },
        { RGB( 0xFF, 0xDA, 0xB9 ), L"PeachPuff" },
        { RGB( 0xFF, 0xDA, 0xB9 ), L"PeachPuff1" },
        { RGB( 0xEE, 0xCB, 0xAD ), L"PeachPuff2" },
        { RGB( 0xCD, 0xAF, 0x95 ), L"PeachPuff3" },
        { RGB( 0x8B, 0x77, 0x65 ), L"PeachPuff4" },
        { RGB( 0xB0, 0xE0, 0xE6 ), L"PowderBlue" },
        { RGB( 0xBC, 0x8F, 0x8F ), L"RosyBrown" },
        { RGB( 0xFF, 0xC1, 0xC1 ), L"RosyBrown1" },
        { RGB( 0xEE, 0xB4, 0xB4 ), L"RosyBrown2" },
        { RGB( 0xCD, 0x9B, 0x9B ), L"RosyBrown3" },
        { RGB( 0x8B, 0x69, 0x69 ), L"RosyBrown4" },
        { RGB( 0x41, 0x69, 0xE1 ), L"RoyalBlue" },
        { RGB( 0x48, 0x76, 0xFF ), L"RoyalBlue1" },
        { RGB( 0x43, 0x6E, 0xEE ), L"RoyalBlue2" },
        { RGB( 0x3A, 0x5F, 0xCD ), L"RoyalBlue3" },
        { RGB( 0x27, 0x40, 0x8B ), L"RoyalBlue4" },
        { RGB( 0x8B, 0x45, 0x13 ), L"SaddleBrown" },
        { RGB( 0xF4, 0xA4, 0x60 ), L"SandyBrown" },
        { RGB( 0x2E, 0x8B, 0x57 ), L"SeaGreen" },
        { RGB( 0x54, 0xFF, 0x9F ), L"SeaGreen1" },
        { RGB( 0x4E, 0xEE, 0x94 ), L"SeaGreen2" },
        { RGB( 0x43, 0xCD, 0x80 ), L"SeaGreen3" },
        { RGB( 0x2E, 0x8B, 0x57 ), L"SeaGreen4" },
        { RGB( 0x87, 0xCE, 0xEB ), L"SkyBlue" },
        { RGB( 0x87, 0xCE, 0xFF ), L"SkyBlue1" },
        { RGB( 0x7E, 0xC0, 0xEE ), L"SkyBlue2" },
        { RGB( 0x6C, 0xA6, 0xCD ), L"SkyBlue3" },
        { RGB( 0x4A, 0x70, 0x8B ), L"SkyBlue4" },
        { RGB( 0x6A, 0x5A, 0xCD ), L"SlateBlue" },
        { RGB( 0x83, 0x6F, 0xFF ), L"SlateBlue1" },
        { RGB( 0x7A, 0x67, 0xEE ), L"SlateBlue2" },
        { RGB( 0x69, 0x59, 0xCD ), L"SlateBlue3" },
        { RGB( 0x47, 0x3C, 0x8B ), L"SlateBlue4" },
        { RGB( 0x70, 0x80, 0x90 ), L"SlateGray" },
        { RGB( 0xC6, 0xE2, 0xFF ), L"SlateGray1" },
        { RGB( 0xB9, 0xD3, 0xEE ), L"SlateGray2" },
        { RGB( 0x9F, 0xB6, 0xCD ), L"SlateGray3" },
        { RGB( 0x6C, 0x7B, 0x8B ), L"SlateGray4" },
        { RGB( 0x70, 0x80, 0x90 ), L"SlateGrey" },
        { RGB( 0x00, 0xFF, 0x7F ), L"SpringGreen" },
        { RGB( 0x00, 0xFF, 0x7F ), L"SpringGreen1" },
        { RGB( 0x00, 0xEE, 0x76 ), L"SpringGreen2" },
        { RGB( 0x00, 0xCD, 0x66 ), L"SpringGreen3" },
        { RGB( 0x00, 0x8B, 0x45 ), L"SpringGreen4" },
        { RGB( 0x46, 0x82, 0xB4 ), L"SteelBlue" },
        { RGB( 0x63, 0xB8, 0xFF ), L"SteelBlue1" },
        { RGB( 0x5C, 0xAC, 0xEE ), L"SteelBlue2" },
        { RGB( 0x4F, 0x94, 0xCD ), L"SteelBlue3" },
        { RGB( 0x36, 0x64, 0x8B ), L"SteelBlue4" },
        { RGB( 0xD0, 0x20, 0x90 ), L"VioletRed" },
        { RGB( 0xFF, 0x3E, 0x96 ), L"VioletRed1" },
        { RGB( 0xEE, 0x3A, 0x8C ), L"VioletRed2" },
        { RGB( 0xCD, 0x32, 0x78 ), L"VioletRed3" },
        { RGB( 0x8B, 0x22, 0x52 ), L"VioletRed4" },
        { RGB( 0xF5, 0xF5, 0xF5 ), L"WhiteSmoke" },
        { RGB( 0x9A, 0xCD, 0x32 ), L"YellowGreen" },
        { RGB( 0xF0, 0xF8, 0xFF ), L"alice blue" },
        { RGB( 0xFA, 0xEB, 0xD7 ), L"antique white" },
        { RGB( 0x7F, 0xFF, 0xD4 ), L"aquamarine" },
        { RGB( 0x7F, 0xFF, 0xD4 ), L"aquamarine1" },
        { RGB( 0x76, 0xEE, 0xC6 ), L"aquamarine2" },
        { RGB( 0x66, 0xCD, 0xAA ), L"aquamarine3" },
        { RGB( 0x45, 0x8B, 0x74 ), L"aquamarine4" },
        { RGB( 0xF0, 0xFF, 0xFF ), L"azure" },
        { RGB( 0xF0, 0xFF, 0xFF ), L"azure1" },
        { RGB( 0xE0, 0xEE, 0xEE ), L"azure2" },
        { RGB( 0xC1, 0xCD, 0xCD ), L"azure3" },
        { RGB( 0x83, 0x8B, 0x8B ), L"azure4" },
        { RGB( 0xF5, 0xF5, 0xDC ), L"beige" },
        { RGB( 0xFF, 0xE4, 0xC4 ), L"bisque" },
        { RGB( 0xFF, 0xE4, 0xC4 ), L"bisque1" },
        { RGB( 0xEE, 0xD5, 0xB7 ), L"bisque2" },
        { RGB( 0xCD, 0xB7, 0x9E ), L"bisque3" },
        { RGB( 0x8B, 0x7D, 0x6B ), L"bisque4" },
        { RGB( 0x00, 0x00, 0x00 ), L"black" },
        { RGB( 0xFF, 0xEB, 0xCD ), L"blanched almond" },
        { RGB( 0x00, 0x00, 0xFF ), L"blue" },
        { RGB( 0x8A, 0x2B, 0xE2 ), L"blue violet" },
        { RGB( 0x00, 0x00, 0xFF ), L"blue1" },
        { RGB( 0x00, 0x00, 0xEE ), L"blue2" },
        { RGB( 0x00, 0x00, 0xCD ), L"blue3" },
        { RGB( 0x00, 0x00, 0x8B ), L"blue4" },
        { RGB( 0xA5, 0x2A, 0x2A ), L"brown" },
        { RGB( 0xFF, 0x40, 0x40 ), L"brown1" },
        { RGB( 0xEE, 0x3B, 0x3B ), L"brown2" },
        { RGB( 0xCD, 0x33, 0x33 ), L"brown3" },
        { RGB( 0x8B, 0x23, 0x23 ), L"brown4" },
        { RGB( 0xDE, 0xB8, 0x87 ), L"burlywood" },
        { RGB( 0xFF, 0xD3, 0x9B ), L"burlywood1" },
        { RGB( 0xEE, 0xC5, 0x91 ), L"burlywood2" },
        { RGB( 0xCD, 0xAA, 0x7D ), L"burlywood3" },
        { RGB( 0x8B, 0x73, 0x55 ), L"burlywood4" },
        { RGB( 0x5F, 0x9E, 0xA0 ), L"cadet blue" },
        { RGB( 0x7F, 0xFF, 0x00 ), L"chartreuse" },
        { RGB( 0x7F, 0xFF, 0x00 ), L"chartreuse1" },
        { RGB( 0x76, 0xEE, 0x00 ), L"chartreuse2" },
        { RGB( 0x66, 0xCD, 0x00 ), L"chartreuse3" },
        { RGB( 0x45, 0x8B, 0x00 ), L"chartreuse4" },
        { RGB( 0xD2, 0x69, 0x1E ), L"chocolate" },
        { RGB( 0xFF, 0x7F, 0x24 ), L"chocolate1" },
        { RGB( 0xEE, 0x76, 0x21 ), L"chocolate2" },
        { RGB( 0xCD, 0x66, 0x1D ), L"chocolate3" },
        { RGB( 0x8B, 0x45, 0x13 ), L"chocolate4" },
        { RGB( 0xFF, 0x7F, 0x50 ), L"coral" },
        { RGB( 0xFF, 0x72, 0x56 ), L"coral1" },
        { RGB( 0xEE, 0x6A, 0x50 ), L"coral2" },
        { RGB( 0xCD, 0x5B, 0x45 ), L"coral3" },
        { RGB( 0x8B, 0x3E, 0x2F ), L"coral4" },
        { RGB( 0x64, 0x95, 0xED ), L"cornflower blue" },
        { RGB( 0xFF, 0xF8, 0xDC ), L"cornsilk" },
        { RGB( 0xFF, 0xF8, 0xDC ), L"cornsilk1" },
        { RGB( 0xEE, 0xE8, 0xCD ), L"cornsilk2" },
        { RGB( 0xCD, 0xC8, 0xB1 ), L"cornsilk3" },
        { RGB( 0x8B, 0x88, 0x78 ), L"cornsilk4" },
        { RGB( 0x00, 0xFF, 0xFF ), L"cyan" },
        { RGB( 0x00, 0xFF, 0xFF ), L"cyan1" },
        { RGB( 0x00, 0xEE, 0xEE ), L"cyan2" },
        { RGB( 0x00, 0xCD, 0xCD ), L"cyan3" },
        { RGB( 0x00, 0x8B, 0x8B ), L"cyan4" },
        { RGB( 0x00, 0x00, 0x8B ), L"dark blue" },
        { RGB( 0x00, 0x8B, 0x8B ), L"dark cyan" },
        { RGB( 0xB8, 0x86, 0x0B ), L"dark goldenrod" },
        { RGB( 0xA9, 0xA9, 0xA9 ), L"dark gray" },
        { RGB( 0x00, 0x64, 0x00 ), L"dark green" },
        { RGB( 0xA9, 0xA9, 0xA9 ), L"dark grey" },
        { RGB( 0xBD, 0xB7, 0x6B ), L"dark khaki" },
        { RGB( 0x8B, 0x00, 0x8B ), L"dark magenta" },
        { RGB( 0x55, 0x6B, 0x2F ), L"dark olive green" },
        { RGB( 0xFF, 0x8C, 0x00 ), L"dark orange" },
        { RGB( 0x99, 0x32, 0xCC ), L"dark orchid" },
        { RGB( 0x8B, 0x00, 0x00 ), L"dark red" },
        { RGB( 0xE9, 0x96, 0x7A ), L"dark salmon" },
        { RGB( 0x8F, 0xBC, 0x8F ), L"dark sea green" },
        { RGB( 0x48, 0x3D, 0x8B ), L"dark slate blue" },
        { RGB( 0x2F, 0x4F, 0x4F ), L"dark slate gray" },
        { RGB( 0x2F, 0x4F, 0x4F ), L"dark slate grey" },
        { RGB( 0x00, 0xCE, 0xD1 ), L"dark turquoise" },
        { RGB( 0x94, 0x00, 0xD3 ), L"dark violet" },
        { RGB( 0xFF, 0x14, 0x93 ), L"deep pink" },
        { RGB( 0x00, 0xBF, 0xFF ), L"deep sky blue" },
        { RGB( 0x69, 0x69, 0x69 ), L"dim gray" },
        { RGB( 0x69, 0x69, 0x69 ), L"dim grey" },
        { RGB( 0x1E, 0x90, 0xFF ), L"dodger blue" },
        { RGB( 0xB2, 0x22, 0x22 ), L"firebrick" },
        { RGB( 0xFF, 0x30, 0x30 ), L"firebrick1" },
        { RGB( 0xEE, 0x2C, 0x2C ), L"firebrick2" },
        { RGB( 0xCD, 0x26, 0x26 ), L"firebrick3" },
        { RGB( 0x8B, 0x1A, 0x1A ), L"firebrick4" },
        { RGB( 0xFF, 0xFA, 0xF0 ), L"floral white" },
        { RGB( 0x22, 0x8B, 0x22 ), L"forest green" },
        { RGB( 0xDC, 0xDC, 0xDC ), L"gainsboro" },
        { RGB( 0xF8, 0xF8, 0xFF ), L"ghost white" },
        { RGB( 0xFF, 0xD7, 0x00 ), L"gold" },
        { RGB( 0xFF, 0xD7, 0x00 ), L"gold1" },
        { RGB( 0xEE, 0xC9, 0x00 ), L"gold2" },
        { RGB( 0xCD, 0xAD, 0x00 ), L"gold3" },
        { RGB( 0x8B, 0x75, 0x00 ), L"gold4" },
        { RGB( 0xDA, 0xA5, 0x20 ), L"goldenrod" },
        { RGB( 0xFF, 0xC1, 0x25 ), L"goldenrod1" },
        { RGB( 0xEE, 0xB4, 0x22 ), L"goldenrod2" },
        { RGB( 0xCD, 0x9B, 0x1D ), L"goldenrod3" },
        { RGB( 0x8B, 0x69, 0x14 ), L"goldenrod4" },
        { RGB( 0xBE, 0xBE, 0xBE ), L"gray" },
        { RGB( 0x00, 0x00, 0x00 ), L"gray0" },
        { RGB( 0x03, 0x03, 0x03 ), L"gray1" },
        { RGB( 0x1A, 0x1A, 0x1A ), L"gray10" },
        { RGB( 0xFF, 0xFF, 0xFF ), L"gray100" },
        { RGB( 0x1C, 0x1C, 0x1C ), L"gray11" },
        { RGB( 0x1F, 0x1F, 0x1F ), L"gray12" },
        { RGB( 0x21, 0x21, 0x21 ), L"gray13" },
        { RGB( 0x24, 0x24, 0x24 ), L"gray14" },
        { RGB( 0x26, 0x26, 0x26 ), L"gray15" },
        { RGB( 0x29, 0x29, 0x29 ), L"gray16" },
        { RGB( 0x2B, 0x2B, 0x2B ), L"gray17" },
        { RGB( 0x2E, 0x2E, 0x2E ), L"gray18" },
        { RGB( 0x30, 0x30, 0x30 ), L"gray19" },
        { RGB( 0x05, 0x05, 0x05 ), L"gray2" },
        { RGB( 0x33, 0x33, 0x33 ), L"gray20" },
        { RGB( 0x36, 0x36, 0x36 ), L"gray21" },
        { RGB( 0x38, 0x38, 0x38 ), L"gray22" },
        { RGB( 0x3B, 0x3B, 0x3B ), L"gray23" },
        { RGB( 0x3D, 0x3D, 0x3D ), L"gray24" },
        { RGB( 0x40, 0x40, 0x40 ), L"gray25" },
        { RGB( 0x42, 0x42, 0x42 ), L"gray26" },
        { RGB( 0x45, 0x45, 0x45 ), L"gray27" },
        { RGB( 0x47, 0x47, 0x47 ), L"gray28" },
        { RGB( 0x4A, 0x4A, 0x4A ), L"gray29" },
        { RGB( 0x08, 0x08, 0x08 ), L"gray3" },
        { RGB( 0x4D, 0x4D, 0x4D ), L"gray30" },
        { RGB( 0x4F, 0x4F, 0x4F ), L"gray31" },
        { RGB( 0x52, 0x52, 0x52 ), L"gray32" },
        { RGB( 0x54, 0x54, 0x54 ), L"gray33" },
        { RGB( 0x57, 0x57, 0x57 ), L"gray34" },
        { RGB( 0x59, 0x59, 0x59 ), L"gray35" },
        { RGB( 0x5C, 0x5C, 0x5C ), L"gray36" },
        { RGB( 0x5E, 0x5E, 0x5E ), L"gray37" },
        { RGB( 0x61, 0x61, 0x61 ), L"gray38" },
        { RGB( 0x63, 0x63, 0x63 ), L"gray39" },
        { RGB( 0x0A, 0x0A, 0x0A ), L"gray4" },
        { RGB( 0x66, 0x66, 0x66 ), L"gray40" },
        { RGB( 0x69, 0x69, 0x69 ), L"gray41" },
        { RGB( 0x6B, 0x6B, 0x6B ), L"gray42" },
        { RGB( 0x6E, 0x6E, 0x6E ), L"gray43" },
        { RGB( 0x70, 0x70, 0x70 ), L"gray44" },
        { RGB( 0x73, 0x73, 0x73 ), L"gray45" },
        { RGB( 0x75, 0x75, 0x75 ), L"gray46" },
        { RGB( 0x78, 0x78, 0x78 ), L"gray47" },
        { RGB( 0x7A, 0x7A, 0x7A ), L"gray48" },
        { RGB( 0x7D, 0x7D, 0x7D ), L"gray49" },
        { RGB( 0x0D, 0x0D, 0x0D ), L"gray5" },
        { RGB( 0x7F, 0x7F, 0x7F ), L"gray50" },
        { RGB( 0x82, 0x82, 0x82 ), L"gray51" },
        { RGB( 0x85, 0x85, 0x85 ), L"gray52" },
        { RGB( 0x87, 0x87, 0x87 ), L"gray53" },
        { RGB( 0x8A, 0x8A, 0x8A ), L"gray54" },
        { RGB( 0x8C, 0x8C, 0x8C ), L"gray55" },
        { RGB( 0x8F, 0x8F, 0x8F ), L"gray56" },
        { RGB( 0x91, 0x91, 0x91 ), L"gray57" },
        { RGB( 0x94, 0x94, 0x94 ), L"gray58" },
        { RGB( 0x96, 0x96, 0x96 ), L"gray59" },
        { RGB( 0x0F, 0x0F, 0x0F ), L"gray6" },
        { RGB( 0x99, 0x99, 0x99 ), L"gray60" },
        { RGB( 0x9C, 0x9C, 0x9C ), L"gray61" },
        { RGB( 0x9E, 0x9E, 0x9E ), L"gray62" },
        { RGB( 0xA1, 0xA1, 0xA1 ), L"gray63" },
        { RGB( 0xA3, 0xA3, 0xA3 ), L"gray64" },
        { RGB( 0xA6, 0xA6, 0xA6 ), L"gray65" },
        { RGB( 0xA8, 0xA8, 0xA8 ), L"gray66" },
        { RGB( 0xAB, 0xAB, 0xAB ), L"gray67" },
        { RGB( 0xAD, 0xAD, 0xAD ), L"gray68" },
        { RGB( 0xB0, 0xB0, 0xB0 ), L"gray69" },
        { RGB( 0x12, 0x12, 0x12 ), L"gray7" },
        { RGB( 0xB3, 0xB3, 0xB3 ), L"gray70" },
        { RGB( 0xB5, 0xB5, 0xB5 ), L"gray71" },
        { RGB( 0xB8, 0xB8, 0xB8 ), L"gray72" },
        { RGB( 0xBA, 0xBA, 0xBA ), L"gray73" },
        { RGB( 0xBD, 0xBD, 0xBD ), L"gray74" },
        { RGB( 0xBF, 0xBF, 0xBF ), L"gray75" },
        { RGB( 0xC2, 0xC2, 0xC2 ), L"gray76" },
        { RGB( 0xC4, 0xC4, 0xC4 ), L"gray77" },
        { RGB( 0xC7, 0xC7, 0xC7 ), L"gray78" },
        { RGB( 0xC9, 0xC9, 0xC9 ), L"gray79" },
        { RGB( 0x14, 0x14, 0x14 ), L"gray8" },
        { RGB( 0xCC, 0xCC, 0xCC ), L"gray80" },
        { RGB( 0xCF, 0xCF, 0xCF ), L"gray81" },
        { RGB( 0xD1, 0xD1, 0xD1 ), L"gray82" },
        { RGB( 0xD4, 0xD4, 0xD4 ), L"gray83" },
        { RGB( 0xD6, 0xD6, 0xD6 ), L"gray84" },
        { RGB( 0xD9, 0xD9, 0xD9 ), L"gray85" },
        { RGB( 0xDB, 0xDB, 0xDB ), L"gray86" },
        { RGB( 0xDE, 0xDE, 0xDE ), L"gray87" },
        { RGB( 0xE0, 0xE0, 0xE0 ), L"gray88" },
        { RGB( 0xE3, 0xE3, 0xE3 ), L"gray89" },
        { RGB( 0x17, 0x17, 0x17 ), L"gray9" },
        { RGB( 0xE5, 0xE5, 0xE5 ), L"gray90" },
        { RGB( 0xE8, 0xE8, 0xE8 ), L"gray91" },
        { RGB( 0xEB, 0xEB, 0xEB ), L"gray92" },
        { RGB( 0xED, 0xED, 0xED ), L"gray93" },
        { RGB( 0xF0, 0xF0, 0xF0 ), L"gray94" },
        { RGB( 0xF2, 0xF2, 0xF2 ), L"gray95" },
        { RGB( 0xF5, 0xF5, 0xF5 ), L"gray96" },
        { RGB( 0xF7, 0xF7, 0xF7 ), L"gray97" },
        { RGB( 0xFA, 0xFA, 0xFA ), L"gray98" },
        { RGB( 0xFC, 0xFC, 0xFC ), L"gray99" },
        { RGB( 0x00, 0xFF, 0x00 ), L"green" },
        { RGB( 0xAD, 0xFF, 0x2F ), L"green yellow" },
        { RGB( 0x00, 0xFF, 0x00 ), L"green1" },
        { RGB( 0x00, 0xEE, 0x00 ), L"green2" },
        { RGB( 0x00, 0xCD, 0x00 ), L"green3" },
        { RGB( 0x00, 0x8B, 0x00 ), L"green4" },
        { RGB( 0xBE, 0xBE, 0xBE ), L"grey" },
        { RGB( 0x00, 0x00, 0x00 ), L"grey0" },
        { RGB( 0x03, 0x03, 0x03 ), L"grey1" },
        { RGB( 0x1A, 0x1A, 0x1A ), L"grey10" },
        { RGB( 0xFF, 0xFF, 0xFF ), L"grey100" },
        { RGB( 0x1C, 0x1C, 0x1C ), L"grey11" },
        { RGB( 0x1F, 0x1F, 0x1F ), L"grey12" },
        { RGB( 0x21, 0x21, 0x21 ), L"grey13" },
        { RGB( 0x24, 0x24, 0x24 ), L"grey14" },
        { RGB( 0x26, 0x26, 0x26 ), L"grey15" },
        { RGB( 0x29, 0x29, 0x29 ), L"grey16" },
        { RGB( 0x2B, 0x2B, 0x2B ), L"grey17" },
        { RGB( 0x2E, 0x2E, 0x2E ), L"grey18" },
        { RGB( 0x30, 0x30, 0x30 ), L"grey19" },
        { RGB( 0x05, 0x05, 0x05 ), L"grey2" },
        { RGB( 0x33, 0x33, 0x33 ), L"grey20" },
        { RGB( 0x36, 0x36, 0x36 ), L"grey21" },
        { RGB( 0x38, 0x38, 0x38 ), L"grey22" },
        { RGB( 0x3B, 0x3B, 0x3B ), L"grey23" },
        { RGB( 0x3D, 0x3D, 0x3D ), L"grey24" },
        { RGB( 0x40, 0x40, 0x40 ), L"grey25" },
        { RGB( 0x42, 0x42, 0x42 ), L"grey26" },
        { RGB( 0x45, 0x45, 0x45 ), L"grey27" },
        { RGB( 0x47, 0x47, 0x47 ), L"grey28" },
        { RGB( 0x4A, 0x4A, 0x4A ), L"grey29" },
        { RGB( 0x08, 0x08, 0x08 ), L"grey3" },
        { RGB( 0x4D, 0x4D, 0x4D ), L"grey30" },
        { RGB( 0x4F, 0x4F, 0x4F ), L"grey31" },
        { RGB( 0x52, 0x52, 0x52 ), L"grey32" },
        { RGB( 0x54, 0x54, 0x54 ), L"grey33" },
        { RGB( 0x57, 0x57, 0x57 ), L"grey34" },
        { RGB( 0x59, 0x59, 0x59 ), L"grey35" },
        { RGB( 0x5C, 0x5C, 0x5C ), L"grey36" },
        { RGB( 0x5E, 0x5E, 0x5E ), L"grey37" },
        { RGB( 0x61, 0x61, 0x61 ), L"grey38" },
        { RGB( 0x63, 0x63, 0x63 ), L"grey39" },
        { RGB( 0x0A, 0x0A, 0x0A ), L"grey4" },
        { RGB( 0x66, 0x66, 0x66 ), L"grey40" },
        { RGB( 0x69, 0x69, 0x69 ), L"grey41" },
        { RGB( 0x6B, 0x6B, 0x6B ), L"grey42" },
        { RGB( 0x6E, 0x6E, 0x6E ), L"grey43" },
        { RGB( 0x70, 0x70, 0x70 ), L"grey44" },
        { RGB( 0x73, 0x73, 0x73 ), L"grey45" },
        { RGB( 0x75, 0x75, 0x75 ), L"grey46" },
        { RGB( 0x78, 0x78, 0x78 ), L"grey47" },
        { RGB( 0x7A, 0x7A, 0x7A ), L"grey48" },
        { RGB( 0x7D, 0x7D, 0x7D ), L"grey49" },
        { RGB( 0x0D, 0x0D, 0x0D ), L"grey5" },
        { RGB( 0x7F, 0x7F, 0x7F ), L"grey50" },
        { RGB( 0x82, 0x82, 0x82 ), L"grey51" },
        { RGB( 0x85, 0x85, 0x85 ), L"grey52" },
        { RGB( 0x87, 0x87, 0x87 ), L"grey53" },
        { RGB( 0x8A, 0x8A, 0x8A ), L"grey54" },
        { RGB( 0x8C, 0x8C, 0x8C ), L"grey55" },
        { RGB( 0x8F, 0x8F, 0x8F ), L"grey56" },
        { RGB( 0x91, 0x91, 0x91 ), L"grey57" },
        { RGB( 0x94, 0x94, 0x94 ), L"grey58" },
        { RGB( 0x96, 0x96, 0x96 ), L"grey59" },
        { RGB( 0x0F, 0x0F, 0x0F ), L"grey6" },
        { RGB( 0x99, 0x99, 0x99 ), L"grey60" },
        { RGB( 0x9C, 0x9C, 0x9C ), L"grey61" },
        { RGB( 0x9E, 0x9E, 0x9E ), L"grey62" },
        { RGB( 0xA1, 0xA1, 0xA1 ), L"grey63" },
        { RGB( 0xA3, 0xA3, 0xA3 ), L"grey64" },
        { RGB( 0xA6, 0xA6, 0xA6 ), L"grey65" },
        { RGB( 0xA8, 0xA8, 0xA8 ), L"grey66" },
        { RGB( 0xAB, 0xAB, 0xAB ), L"grey67" },
        { RGB( 0xAD, 0xAD, 0xAD ), L"grey68" },
        { RGB( 0xB0, 0xB0, 0xB0 ), L"grey69" },
        { RGB( 0x12, 0x12, 0x12 ), L"grey7" },
        { RGB( 0xB3, 0xB3, 0xB3 ), L"grey70" },
        { RGB( 0xB5, 0xB5, 0xB5 ), L"grey71" },
        { RGB( 0xB8, 0xB8, 0xB8 ), L"grey72" },
        { RGB( 0xBA, 0xBA, 0xBA ), L"grey73" },
        { RGB( 0xBD, 0xBD, 0xBD ), L"grey74" },
        { RGB( 0xBF, 0xBF, 0xBF ), L"grey75" },
        { RGB( 0xC2, 0xC2, 0xC2 ), L"grey76" },
        { RGB( 0xC4, 0xC4, 0xC4 ), L"grey77" },
        { RGB( 0xC7, 0xC7, 0xC7 ), L"grey78" },
        { RGB( 0xC9, 0xC9, 0xC9 ), L"grey79" },
        { RGB( 0x14, 0x14, 0x14 ), L"grey8" },
        { RGB( 0xCC, 0xCC, 0xCC ), L"grey80" },
        { RGB( 0xCF, 0xCF, 0xCF ), L"grey81" },
        { RGB( 0xD1, 0xD1, 0xD1 ), L"grey82" },
        { RGB( 0xD4, 0xD4, 0xD4 ), L"grey83" },
        { RGB( 0xD6, 0xD6, 0xD6 ), L"grey84" },
        { RGB( 0xD9, 0xD9, 0xD9 ), L"grey85" },
        { RGB( 0xDB, 0xDB, 0xDB ), L"grey86" },
        { RGB( 0xDE, 0xDE, 0xDE ), L"grey87" },
        { RGB( 0xE0, 0xE0, 0xE0 ), L"grey88" },
        { RGB( 0xE3, 0xE3, 0xE3 ), L"grey89" },
        { RGB( 0x17, 0x17, 0x17 ), L"grey9" },
        { RGB( 0xE5, 0xE5, 0xE5 ), L"grey90" },
        { RGB( 0xE8, 0xE8, 0xE8 ), L"grey91" },
        { RGB( 0xEB, 0xEB, 0xEB ), L"grey92" },
        { RGB( 0xED, 0xED, 0xED ), L"grey93" },
        { RGB( 0xF0, 0xF0, 0xF0 ), L"grey94" },
        { RGB( 0xF2, 0xF2, 0xF2 ), L"grey95" },
        { RGB( 0xF5, 0xF5, 0xF5 ), L"grey96" },
        { RGB( 0xF7, 0xF7, 0xF7 ), L"grey97" },
        { RGB( 0xFA, 0xFA, 0xFA ), L"grey98" },
        { RGB( 0xFC, 0xFC, 0xFC ), L"grey99" },
        { RGB( 0xF0, 0xFF, 0xF0 ), L"honeydew" },
        { RGB( 0xF0, 0xFF, 0xF0 ), L"honeydew1" },
        { RGB( 0xE0, 0xEE, 0xE0 ), L"honeydew2" },
        { RGB( 0xC1, 0xCD, 0xC1 ), L"honeydew3" },
        { RGB( 0x83, 0x8B, 0x83 ), L"honeydew4" },
        { RGB( 0xFF, 0x69, 0xB4 ), L"hot pink" },
        { RGB( 0xCD, 0x5C, 0x5C ), L"indian red" },
        { RGB( 0xFF, 0xFF, 0xF0 ), L"ivory" },
        { RGB( 0xFF, 0xFF, 0xF0 ), L"ivory1" },
        { RGB( 0xEE, 0xEE, 0xE0 ), L"ivory2" },
        { RGB( 0xCD, 0xCD, 0xC1 ), L"ivory3" },
        { RGB( 0x8B, 0x8B, 0x83 ), L"ivory4" },
        { RGB( 0xF0, 0xE6, 0x8C ), L"khaki" },
        { RGB( 0xFF, 0xF6, 0x8F ), L"khaki1" },
        { RGB( 0xEE, 0xE6, 0x85 ), L"khaki2" },
        { RGB( 0xCD, 0xC6, 0x73 ), L"khaki3" },
        { RGB( 0x8B, 0x86, 0x4E ), L"khaki4" },
        { RGB( 0xE6, 0xE6, 0xFA ), L"lavender" },
        { RGB( 0xFF, 0xF0, 0xF5 ), L"lavender blush" },
        { RGB( 0x7C, 0xFC, 0x00 ), L"lawn green" },
        { RGB( 0xFF, 0xFA, 0xCD ), L"lemon chiffon" },
        { RGB( 0xAD, 0xD8, 0xE6 ), L"light blue" },
        { RGB( 0xF0, 0x80, 0x80 ), L"light coral" },
        { RGB( 0xE0, 0xFF, 0xFF ), L"light cyan" },
        { RGB( 0xEE, 0xDD, 0x82 ), L"light goldenrod" },
        { RGB( 0xFA, 0xFA, 0xD2 ), L"light goldenrod yellow" },
        { RGB( 0xD3, 0xD3, 0xD3 ), L"light gray" },
        { RGB( 0x90, 0xEE, 0x90 ), L"light green" },
        { RGB( 0xD3, 0xD3, 0xD3 ), L"light grey" },
        { RGB( 0xFF, 0xB6, 0xC1 ), L"light pink" },
        { RGB( 0xFF, 0xA0, 0x7A ), L"light salmon" },
        { RGB( 0x20, 0xB2, 0xAA ), L"light sea green" },
        { RGB( 0x87, 0xCE, 0xFA ), L"light sky blue" },
        { RGB( 0x84, 0x70, 0xFF ), L"light slate blue" },
        { RGB( 0x77, 0x88, 0x99 ), L"light slate gray" },
        { RGB( 0x77, 0x88, 0x99 ), L"light slate grey" },
        { RGB( 0xB0, 0xC4, 0xDE ), L"light steel blue" },
        { RGB( 0xFF, 0xFF, 0xE0 ), L"light yellow" },
        { RGB( 0x32, 0xCD, 0x32 ), L"lime green" },
        { RGB( 0xFA, 0xF0, 0xE6 ), L"linen" },
        { RGB( 0xFF, 0x00, 0xFF ), L"magenta" },
        { RGB( 0xFF, 0x00, 0xFF ), L"magenta1" },
        { RGB( 0xEE, 0x00, 0xEE ), L"magenta2" },
        { RGB( 0xCD, 0x00, 0xCD ), L"magenta3" },
        { RGB( 0x8B, 0x00, 0x8B ), L"magenta4" },
        { RGB( 0xB0, 0x30, 0x60 ), L"maroon" },
        { RGB( 0xFF, 0x34, 0xB3 ), L"maroon1" },
        { RGB( 0xEE, 0x30, 0xA7 ), L"maroon2" },
        { RGB( 0xCD, 0x29, 0x90 ), L"maroon3" },
        { RGB( 0x8B, 0x1C, 0x62 ), L"maroon4" },
        { RGB( 0x66, 0xCD, 0xAA ), L"medium aquamarine" },
        { RGB( 0x00, 0x00, 0xCD ), L"medium blue" },
        { RGB( 0xBA, 0x55, 0xD3 ), L"medium orchid" },
        { RGB( 0x93, 0x70, 0xDB ), L"medium purple" },
        { RGB( 0x3C, 0xB3, 0x71 ), L"medium sea green" },
        { RGB( 0x7B, 0x68, 0xEE ), L"medium slate blue" },
        { RGB( 0x00, 0xFA, 0x9A ), L"medium spring green" },
        { RGB( 0x48, 0xD1, 0xCC ), L"medium turquoise" },
        { RGB( 0xC7, 0x15, 0x85 ), L"medium violet red" },
        { RGB( 0x19, 0x19, 0x70 ), L"midnight blue" },
        { RGB( 0xF5, 0xFF, 0xFA ), L"mint cream" },
        { RGB( 0xFF, 0xE4, 0xE1 ), L"misty rose" },
        { RGB( 0xFF, 0xE4, 0xB5 ), L"moccasin" },
        { RGB( 0xFF, 0xDE, 0xAD ), L"navajo white" },
        { RGB( 0x00, 0x00, 0x80 ), L"navy" },
        { RGB( 0x00, 0x00, 0x80 ), L"navy blue" },
        { RGB( 0xFD, 0xF5, 0xE6 ), L"old lace" },
        { RGB( 0x6B, 0x8E, 0x23 ), L"olive drab" },
        { RGB( 0xFF, 0xA5, 0x00 ), L"orange" },
        { RGB( 0xFF, 0x45, 0x00 ), L"orange red" },
        { RGB( 0xFF, 0xA5, 0x00 ), L"orange1" },
        { RGB( 0xEE, 0x9A, 0x00 ), L"orange2" },
        { RGB( 0xCD, 0x85, 0x00 ), L"orange3" },
        { RGB( 0x8B, 0x5A, 0x00 ), L"orange4" },
        { RGB( 0xDA, 0x70, 0xD6 ), L"orchid" },
        { RGB( 0xFF, 0x83, 0xFA ), L"orchid1" },
        { RGB( 0xEE, 0x7A, 0xE9 ), L"orchid2" },
        { RGB( 0xCD, 0x69, 0xC9 ), L"orchid3" },
        { RGB( 0x8B, 0x47, 0x89 ), L"orchid4" },
        { RGB( 0xEE, 0xE8, 0xAA ), L"pale goldenrod" },
        { RGB( 0x98, 0xFB, 0x98 ), L"pale green" },
        { RGB( 0xAF, 0xEE, 0xEE ), L"pale turquoise" },
        { RGB( 0xDB, 0x70, 0x93 ), L"pale violet red" },
        { RGB( 0xFF, 0xEF, 0xD5 ), L"papaya whip" },
        { RGB( 0xFF, 0xDA, 0xB9 ), L"peach puff" },
        { RGB( 0xCD, 0x85, 0x3F ), L"peru" },
        { RGB( 0xFF, 0xC0, 0xCB ), L"pink" },
        { RGB( 0xFF, 0xB5, 0xC5 ), L"pink1" },
        { RGB( 0xEE, 0xA9, 0xB8 ), L"pink2" },
        { RGB( 0xCD, 0x91, 0x9E ), L"pink3" },
        { RGB( 0x8B, 0x63, 0x6C ), L"pink4" },
        { RGB( 0xDD, 0xA0, 0xDD ), L"plum" },
        { RGB( 0xFF, 0xBB, 0xFF ), L"plum1" },
        { RGB( 0xEE, 0xAE, 0xEE ), L"plum2" },
        { RGB( 0xCD, 0x96, 0xCD ), L"plum3" },
        { RGB( 0x8B, 0x66, 0x8B ), L"plum4" },
        { RGB( 0xB0, 0xE0, 0xE6 ), L"powder blue" },
        { RGB( 0xA0, 0x20, 0xF0 ), L"purple" },
        { RGB( 0x9B, 0x30, 0xFF ), L"purple1" },
        { RGB( 0x91, 0x2C, 0xEE ), L"purple2" },
        { RGB( 0x7D, 0x26, 0xCD ), L"purple3" },
        { RGB( 0x55, 0x1A, 0x8B ), L"purple4" },
        { RGB( 0xFF, 0x00, 0x00 ), L"red" },
        { RGB( 0xFF, 0x00, 0x00 ), L"red1" },
        { RGB( 0xEE, 0x00, 0x00 ), L"red2" },
        { RGB( 0xCD, 0x00, 0x00 ), L"red3" },
        { RGB( 0x8B, 0x00, 0x00 ), L"red4" },
        { RGB( 0xBC, 0x8F, 0x8F ), L"rosy brown" },
        { RGB( 0x41, 0x69, 0xE1 ), L"royal blue" },
        { RGB( 0x8B, 0x45, 0x13 ), L"saddle brown" },
        { RGB( 0xFA, 0x80, 0x72 ), L"salmon" },
        { RGB( 0xFF, 0x8C, 0x69 ), L"salmon1" },
        { RGB( 0xEE, 0x82, 0x62 ), L"salmon2" },
        { RGB( 0xCD, 0x70, 0x54 ), L"salmon3" },
        { RGB( 0x8B, 0x4C, 0x39 ), L"salmon4" },
        { RGB( 0xF4, 0xA4, 0x60 ), L"sandy brown" },
        { RGB( 0x2E, 0x8B, 0x57 ), L"sea green" },
        { RGB( 0xFF, 0xF5, 0xEE ), L"seashell" },
        { RGB( 0xFF, 0xF5, 0xEE ), L"seashell1" },
        { RGB( 0xEE, 0xE5, 0xDE ), L"seashell2" },
        { RGB( 0xCD, 0xC5, 0xBF ), L"seashell3" },
        { RGB( 0x8B, 0x86, 0x82 ), L"seashell4" },
        { RGB( 0xA0, 0x52, 0x2D ), L"sienna" },
        { RGB( 0xFF, 0x82, 0x47 ), L"sienna1" },
        { RGB( 0xEE, 0x79, 0x42 ), L"sienna2" },
        { RGB( 0xCD, 0x68, 0x39 ), L"sienna3" },
        { RGB( 0x8B, 0x47, 0x26 ), L"sienna4" },
        { RGB( 0x87, 0xCE, 0xEB ), L"sky blue" },
        { RGB( 0x6A, 0x5A, 0xCD ), L"slate blue" },
        { RGB( 0x70, 0x80, 0x90 ), L"slate gray" },
        { RGB( 0x70, 0x80, 0x90 ), L"slate grey" },
        { RGB( 0xFF, 0xFA, 0xFA ), L"snow" },
        { RGB( 0xFF, 0xFA, 0xFA ), L"snow1" },
        { RGB( 0xEE, 0xE9, 0xE9 ), L"snow2" },
        { RGB( 0xCD, 0xC9, 0xC9 ), L"snow3" },
        { RGB( 0x8B, 0x89, 0x89 ), L"snow4" },
        { RGB( 0x00, 0xFF, 0x7F ), L"spring green" },
        { RGB( 0x46, 0x82, 0xB4 ), L"steel blue" },
        { RGB( 0xD2, 0xB4, 0x8C ), L"tan" },
        { RGB( 0xFF, 0xA5, 0x4F ), L"tan1" },
        { RGB( 0xEE, 0x9A, 0x49 ), L"tan2" },
        { RGB( 0xCD, 0x85, 0x3F ), L"tan3" },
        { RGB( 0x8B, 0x5A, 0x2B ), L"tan4" },
        { RGB( 0xD8, 0xBF, 0xD8 ), L"thistle" },
        { RGB( 0xFF, 0xE1, 0xFF ), L"thistle1" },
        { RGB( 0xEE, 0xD2, 0xEE ), L"thistle2" },
        { RGB( 0xCD, 0xB5, 0xCD ), L"thistle3" },
        { RGB( 0x8B, 0x7B, 0x8B ), L"thistle4" },
        { RGB( 0xFF, 0x63, 0x47 ), L"tomato" },
        { RGB( 0xFF, 0x63, 0x47 ), L"tomato1" },
        { RGB( 0xEE, 0x5C, 0x42 ), L"tomato2" },
        { RGB( 0xCD, 0x4F, 0x39 ), L"tomato3" },
        { RGB( 0x8B, 0x36, 0x26 ), L"tomato4" },
        { RGB( 0x40, 0xE0, 0xD0 ), L"turquoise" },
        { RGB( 0x00, 0xF5, 0xFF ), L"turquoise1" },
        { RGB( 0x00, 0xE5, 0xEE ), L"turquoise2" },
        { RGB( 0x00, 0xC5, 0xCD ), L"turquoise3" },
        { RGB( 0x00, 0x86, 0x8B ), L"turquoise4" },
        { RGB( 0xEE, 0x82, 0xEE ), L"violet" },
        { RGB( 0xD0, 0x20, 0x90 ), L"violet red" },
        { RGB( 0xF5, 0xDE, 0xB3 ), L"wheat" },
        { RGB( 0xFF, 0xE7, 0xBA ), L"wheat1" },
        { RGB( 0xEE, 0xD8, 0xAE ), L"wheat2" },
        { RGB( 0xCD, 0xBA, 0x96 ), L"wheat3" },
        { RGB( 0x8B, 0x7E, 0x66 ), L"wheat4" },
        { RGB( 0xFF, 0xFF, 0xFF ), L"white" },
        { RGB( 0xF5, 0xF5, 0xF5 ), L"white smoke" },
        { RGB( 0xFF, 0xFF, 0x00 ), L"yellow" },
        { RGB( 0x9A, 0xCD, 0x32 ), L"yellow green" },
        { RGB( 0xFF, 0xFF, 0x00 ), L"yellow1" },
        { RGB( 0xEE, 0xEE, 0x00 ), L"yellow2" },
        { RGB( 0xCD, 0xCD, 0x00 ), L"yellow3" },
        { RGB( 0x8B, 0x8B, 0x00 ), L"yellow4" }
    };

    //--------------------------------------------------------------------------
    //
    // implementation of class Colors
    //
    //--------------------------------------------------------------------------
    int32_t Colors::Create( const wchar_t* pNameOrCode ) {
        if( ::wcslen( pNameOrCode ) == 8 &&
            pNameOrCode[2] == ':' && pNameOrCode[5] == ':' ) {
            unsigned int r, g, b;
            auto cnt = ::swscanf( pNameOrCode, L"%02X:%02X:%02X", &r, &g, &b );
            if( cnt != 3 )
                return 0;
            return RGB( r, g, b );
        }
        ColorEntry key{ 0, pNameOrCode };
        auto p = std::lower_bound( g_colors, g_colors + countof( g_colors ), key,
                                   []( const ColorEntry& ce1, const ColorEntry& ce2 ) -> bool {
                                       return (::wcscmp( ce1.name, ce2.name) < 0);
                                   } );
        if( p == g_colors + countof( g_colors ) )
            return 0;
        if( !!::wcscmp( p->name, pNameOrCode ) )
            return 0;
        return p->color;
    }

    int32_t Colors::Create( uint8_t r, uint8_t g, uint8_t b ) {
        return RGB( r, g, b );
    }

} // namespace clime

