/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Constants.h"

//==============================================================================
BeatMDAudioProcessor::BeatMDAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
	mFormatManager.registerBasicFormats();

	for (const auto& entry : constants::midiToSampleMap) {
		int midiValue = entry.first;
		const std::string& sampleFileName = entry.second;
		int dataSizeInBytes;
		const char* sourceData = BinaryData::getNamedResource(sampleFileName.c_str(), dataSizeInBytes);
		auto memoryInputStream = std::make_unique<juce::MemoryInputStream>(sourceData, dataSizeInBytes, false);
		juce::AudioFormatReader* reader = mFormatManager.createReaderFor(std::move(memoryInputStream));

		juce::BigInteger range;
		range.setRange(midiValue, 1, true);
		bool isOpenHiHat = midiValue == constants::OpenHiHat;
		double releaseTimeSecs = isOpenHiHat ? 0.1 : 10.0;

		juce::SamplerSound* sound = new juce::SamplerSound(juce::String(sampleFileName), *reader, range, midiValue, 0.0, releaseTimeSecs, 5.0);

		switch (midiValue) {
		case constants::AcousticSnare:
			mAcousticSnareSynthesizer.addSound(sound);
			mAcousticSnareSynthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::SideStick:
			mSideStickSynthesizer.addSound(sound);
			mSideStickSynthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::BassDrum1:
			mBassDrum1Synthesizer.addSound(sound);
			mBassDrum1Synthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::CrashCymbal1:
			mCrashCymbal1Synthesizer.addSound(sound);
			mCrashCymbal1Synthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::ClosedHiHat:
			mClosedHiHatSynthesizer.addSound(sound);
			mClosedHiHatSynthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::HandClap:
			mHandClapSynthesizer.addSound(sound);
			mHandClapSynthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::HiMidTom:
			mHiMidTomSynthesizer.addSound(sound);
			mHiMidTomSynthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::LowTom:
			mLowTomSynthesizer.addSound(sound);
			mLowTomSynthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::LowMidTom:
			mLowMidTomSynthesizer.addSound(sound);
			mLowMidTomSynthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::OpenHiHat:
			mOpenHiHatSynthesizer.addSound(sound);
			mOpenHiHatSynthesizer.addVoice(new juce::SamplerVoice());
			break;
		case constants::RideCymbal1:
			mRideCymbal1Synthesizer.addSound(sound);
			mRideCymbal1Synthesizer.addVoice(new juce::SamplerVoice());
			break;

		}
	}
}

BeatMDAudioProcessor::~BeatMDAudioProcessor()
{
}

//==============================================================================
const juce::String BeatMDAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool BeatMDAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool BeatMDAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool BeatMDAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double BeatMDAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int BeatMDAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int BeatMDAudioProcessor::getCurrentProgram()
{
	return 0;
}

void BeatMDAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String BeatMDAudioProcessor::getProgramName(int index)
{
	return {};
}

void BeatMDAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void BeatMDAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	mAcousticSnareSynthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mSideStickSynthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mBassDrum1Synthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mCrashCymbal1Synthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mClosedHiHatSynthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mHandClapSynthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mHiMidTomSynthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mLowTomSynthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mLowMidTomSynthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mOpenHiHatSynthesizer.setCurrentPlaybackSampleRate(sampleRate);
	mRideCymbal1Synthesizer.setCurrentPlaybackSampleRate(sampleRate);
}

void BeatMDAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BeatMDAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void BeatMDAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	mAcousticSnareSynthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mSideStickSynthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mBassDrum1Synthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mCrashCymbal1Synthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mClosedHiHatSynthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mHandClapSynthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mHiMidTomSynthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mLowTomSynthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mLowMidTomSynthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mOpenHiHatSynthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	mRideCymbal1Synthesizer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool BeatMDAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BeatMDAudioProcessor::createEditor()
{
	return new BeatMDAudioProcessorEditor(*this);
}

void BeatMDAudioProcessor::noteOnSynthesiser(int midiNoteNumber)
{
	mAcousticSnareSynthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mSideStickSynthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mBassDrum1Synthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mCrashCymbal1Synthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mClosedHiHatSynthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mHandClapSynthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mHiMidTomSynthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mLowTomSynthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mLowMidTomSynthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mOpenHiHatSynthesizer.noteOn(10, midiNoteNumber, 1.0f);
	mRideCymbal1Synthesizer.noteOn(10, midiNoteNumber, 1.0f);
}


//==============================================================================
void BeatMDAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void BeatMDAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new BeatMDAudioProcessor();
}
