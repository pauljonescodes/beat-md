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

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BeatMDAudioProcessorEditor::BeatMDAudioProcessorEditor (BeatMDAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p) 
{
    setSize (594, 186);

    mAcousticSnareButton.setComponentID(juce::String(constants::AcousticSnare));
    mSideStickButton.setComponentID(juce::String(constants::SideStick));
    mBassDrum1Button.setComponentID(juce::String(constants::BassDrum1));
    mCrashCymbal1Button.setComponentID(juce::String(constants::CrashCymbal1));
    mClosedHiHatButton.setComponentID(juce::String(constants::ClosedHiHat));
    mHandClapButton.setComponentID(juce::String(constants::HandClap));
    mHiMidTomButton.setComponentID(juce::String(constants::HiMidTom));
    mLowTomButton.setComponentID(juce::String(constants::LowTom));
    mLowMidTomButton.setComponentID(juce::String(constants::LowMidTom));
    mOpenHiHatButton.setComponentID(juce::String(constants::OpenHiHat));
    mRideCymbal1Button.setComponentID(juce::String(constants::RideCymbal1));

    addAndMakeVisible(mAcousticSnareButton);
    addAndMakeVisible(mSideStickButton);
    addAndMakeVisible(mBassDrum1Button);
    addAndMakeVisible(mCrashCymbal1Button);
    addAndMakeVisible(mClosedHiHatButton);
    addAndMakeVisible(mHandClapButton);
    addAndMakeVisible(mHiMidTomButton);
    addAndMakeVisible(mLowTomButton);
    addAndMakeVisible(mLowMidTomButton);
    addAndMakeVisible(mOpenHiHatButton);
    addAndMakeVisible(mRideCymbal1Button);

    mAcousticSnareButton.addListener(this);
    mSideStickButton.addListener(this);
    mBassDrum1Button.addListener(this);
    mCrashCymbal1Button.addListener(this);
    mClosedHiHatButton.addListener(this);
    mHandClapButton.addListener(this);
    mHiMidTomButton.addListener(this);
    mLowTomButton.addListener(this);
    mLowMidTomButton.addListener(this);
    mOpenHiHatButton.addListener(this);
    mRideCymbal1Button.addListener(this);
}

BeatMDAudioProcessorEditor::~BeatMDAudioProcessorEditor()
{
}

//==============================================================================
void BeatMDAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::DR220A_jpg, BinaryData::DR220A_jpgSize);
    g.drawImageAt(background, 0, 0);
}

void BeatMDAudioProcessorEditor::resized()
{
    int buttonWidth = 50;
    int buttonHeight = 36; 

    int buttonXStart = 370;
    int buttonYStart = 34;
    int buttonGap = 5;

    mLowTomButton.setBounds(buttonXStart, buttonYStart, buttonWidth, buttonHeight);
    mLowMidTomButton.setBounds(buttonXStart + buttonWidth + buttonGap, buttonYStart, buttonWidth, buttonHeight);
    mHiMidTomButton.setBounds(buttonXStart + 2 * (buttonWidth + buttonGap), buttonYStart, buttonWidth, buttonHeight);
    mCrashCymbal1Button.setBounds(buttonXStart + 3 * (buttonWidth + buttonGap), buttonYStart, buttonWidth, buttonHeight);

    mSideStickButton.setBounds(buttonXStart, buttonYStart + buttonHeight + buttonGap, buttonWidth, buttonHeight);
    mHandClapButton.setBounds(buttonXStart + buttonWidth + buttonGap, buttonYStart + buttonHeight + buttonGap, buttonWidth, buttonHeight);
    mClosedHiHatButton.setBounds(buttonXStart + 2 * (buttonWidth + buttonGap), buttonYStart + buttonHeight + buttonGap, buttonWidth, buttonHeight);
    mOpenHiHatButton.setBounds(buttonXStart + 3 * (buttonWidth + buttonGap), buttonYStart + buttonHeight + buttonGap, buttonWidth, buttonHeight);

    mBassDrum1Button.setBounds(buttonXStart, buttonYStart + 2 * (buttonHeight + buttonGap), buttonWidth, buttonHeight);
    mAcousticSnareButton.setBounds(buttonXStart + buttonWidth + buttonGap, buttonYStart + 2 * (buttonHeight + buttonGap), buttonWidth, buttonHeight);
    mRideCymbal1Button.setBounds(buttonXStart + 2 * (buttonWidth + buttonGap), buttonYStart + 2 * (buttonHeight + buttonGap), buttonWidth, buttonHeight);


}

void BeatMDAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    const juce::String componentID = button->getComponentID();

    // Convert the component ID (string) back to a MIDI note value (integer)
    int midiNoteValue = componentID.getIntValue();

    audioProcessor.noteOnSynthesiser(midiNoteValue);
}