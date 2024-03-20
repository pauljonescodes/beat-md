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

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Constants.h"

//==============================================================================
/**
*/
class BeatMDAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Button::Listener
{
public:
    BeatMDAudioProcessorEditor (BeatMDAudioProcessor&);
    ~BeatMDAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BeatMDAudioProcessor& audioProcessor;

    //==============================================================================

    juce::TextButton mAcousticSnareButton{ juce::String(constants::AcousticSnare) + " D2" };
    juce::TextButton mSideStickButton{ juce::String(constants::SideStick) + " C#1" };
    juce::TextButton mBassDrum1Button{ juce::String(constants::BassDrum1) + " C1" };
    juce::TextButton mCrashCymbal1Button{ juce::String(constants::CrashCymbal1) + " C#2" };
    juce::TextButton mClosedHiHatButton{ juce::String(constants::ClosedHiHat) + " F#1" };
    juce::TextButton mHandClapButton{ juce::String(constants::HandClap) + " Eb1" };
    juce::TextButton mHiMidTomButton{ juce::String(constants::HiMidTom) + " C2" };
    juce::TextButton mLowTomButton{ juce::String(constants::LowTom) + " A1" };
    juce::TextButton mLowMidTomButton{ juce::String(constants::LowMidTom) + " B1" };
    juce::TextButton mOpenHiHatButton{ juce::String(constants::OpenHiHat) + " Bb1" };
    juce::TextButton mRideCymbal1Button{ juce::String(constants::RideCymbal1) + " Eb2" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeatMDAudioProcessorEditor)
};
