/*
    This code is part of the BeatMD digital instrument.
    Copyright (C) 2023  Paul Jones

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
 */

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