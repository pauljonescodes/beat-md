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

//==============================================================================
/**
*/
class BeatMDAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BeatMDAudioProcessor();
    ~BeatMDAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void noteOnSynthesiser(int midiNoteNumber);

private:
    //==============================================================================
    juce::AudioFormatManager mFormatManager;

    juce::Synthesiser mAcousticSnareSynthesizer;
    juce::Synthesiser mSideStickSynthesizer;
    juce::Synthesiser mBassDrum1Synthesizer;
    juce::Synthesiser mCrashCymbal1Synthesizer;
    juce::Synthesiser mClosedHiHatSynthesizer;
    juce::Synthesiser mHandClapSynthesizer;
    juce::Synthesiser mHiMidTomSynthesizer;
    juce::Synthesiser mLowTomSynthesizer;
    juce::Synthesiser mLowMidTomSynthesizer;
    juce::Synthesiser mOpenHiHatSynthesizer;
    juce::Synthesiser mRideCymbal1Synthesizer;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeatMDAudioProcessor)
};
