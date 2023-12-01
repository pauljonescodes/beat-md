#include <string>
#include <map>

#pragma once

namespace constants
{
	constexpr int AcousticSnare = 38;
	constexpr int SideStick = 37;
	constexpr int BassDrum1 = 36;
	constexpr int CrashCymbal1 = 49;
	constexpr int ClosedHiHat = 42;
	constexpr int HandClap = 39;
	constexpr int HiMidTom = 48;
	constexpr int LowTom = 45;
	constexpr int LowMidTom = 47;
	constexpr int OpenHiHat = 46;
	constexpr int RideCymbal1 = 51;

	static const std::map<int, std::string> midiToSampleMap = {
		{AcousticSnare, "SD_01_wav"},
		{SideStick, "RIM_01_wav"},
		{BassDrum1, "BD_01_wav"},
		{CrashCymbal1, "CCY_01_wav"},
		{ClosedHiHat, "CH_01_wav"},
		{HandClap, "HCP_01_wav"},
		{HiMidTom, "HT_01_wav"},
		{LowTom, "LT_01_wav"},
		{LowMidTom, "MT_01_wav"},
		{OpenHiHat, "OH_01_wav"},
		{RideCymbal1, "RCY_01_wav"},
	};
}