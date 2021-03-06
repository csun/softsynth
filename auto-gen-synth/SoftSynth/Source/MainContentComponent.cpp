#include "MainContentComponent.h"

MainContentComponent::MainContentComponent() :
    currentSampleRate (44100.0),
    lastInputIndex(0),
    isAddingFromMidiInput(false),
    keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard),
    startTime (Time::getMillisecondCounterHiRes() * 0.001)
{
    // specify the number of input and output channels that we want to open
    setAudioChannels (0, 1);

    addAndMakeVisible (levelSlider);
    levelSlider.setRange (0, 1);
    levelSlider.setValue (0.125);
	levelSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	levelSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);


    addAndMakeVisible (levelLabel);
    levelLabel.setText ("Volume", sendNotification);
    levelLabel.attachToComponent (&levelSlider, true);
	levelLabel.setJustificationType(Justification::centredBottom);

    filterComponent = filter.createEditor();
    addAndMakeVisible(filterComponent);

    delayComponent = delay.createEditor();
    addAndMakeVisible(delayComponent);

    addAndMakeVisible (midiInputListLabel);
    midiInputListLabel.setText ("MIDI Input:", dontSendNotification);
    midiInputListLabel.attachToComponent (&midiInputList, true);

    waveformMap[String("Sine")] = Sine;
    waveformMap[String("Saw")] = Saw;
    waveformMap[String("Square")] = Square;
    addAndMakeVisible (waveformList);
    int nextId = 1;
    for(auto it = waveformMap.begin(); it != waveformMap.end(); it++) {
      waveformList.addItem(it->first, nextId);
      nextId++;
    }
    waveformList.addListener(this);
	waveformList.setSelectedId(1);

	//add waveform label
	addAndMakeVisible(waveLabel);
	waveLabel.setText("Waveshape", sendNotification);
	waveLabel.attachToComponent(&waveformList, true);

    addAndMakeVisible (midiInputList);
    midiInputList.setTextWhenNoChoicesAvailable ("No MIDI Inputs Enabled");
    const StringArray midiInputs (MidiInput::getDevices());
    midiInputList.addItemList (midiInputs, 1);
    midiInputList.addListener (this);
    // find the first enabled device and use that by default
    for (int i = 0; i < midiInputs.size(); ++i)
    {
        if (deviceManager.isMidiInputEnabled (midiInputs[i])) {
            setMidiInput (i);
              break;
        }
    }
    // if no enabled devices were found just use the first one in the list
    if (midiInputList.getSelectedId() == 0) setMidiInput (0);

    addAndMakeVisible (keyboardComponent);
    keyboardState.addListener (this);
	//keyboardComponent.setBounds(0, 550, 800, 50);

    addAndMakeVisible (midiMessagesBox);
    midiMessagesBox.setMultiLine (true);
    midiMessagesBox.setReturnKeyStartsNewLine (true);
    midiMessagesBox.setReadOnly (true);
    midiMessagesBox.setScrollbarsShown (true);
    midiMessagesBox.setCaretVisible (false);
    midiMessagesBox.setPopupMenuEnabled (true);
    midiMessagesBox.setColour (TextEditor::backgroundColourId, Colour (0x32ffffff));
    midiMessagesBox.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    midiMessagesBox.setColour (TextEditor::shadowColourId, Colour (0x16000000));

    setOpaque (true);
    setSize(700, 600);
}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();

    keyboardState.removeListener (this);
    deviceManager.removeMidiInputCallback (MidiInput::getDevices()[midiInputList.getSelectedItemIndex()], this);
    midiInputList.removeListener (this);
    waveformList.removeListener (this);

    delete filterComponent;
    delete delayComponent;
    clearToneGenerators();
}


void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    filter.prepareToPlay(sampleRate, samplesPerBlockExpected);
    delay.prepareToPlay(sampleRate, samplesPerBlockExpected);
    currentSampleRate = sampleRate;
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    const float level = (float) levelSlider.getValue();

    // Get a pointer to the start sample in the buffer for this audio output channel
    // NOTE this synth is mono, so there will only ever be one channel.
    float* const buffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);

    playLock.enter();
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
      buffer[sample] = 0.0f;
      for(auto it = noteToneGenerator.begin(); it != noteToneGenerator.end(); it++) {
        float played = (it->second->getSample() * level);
        buffer[sample] = std::max(0.0f, std::min(1.0f,
              buffer[sample] + played));
      }
    }
    playLock.exit();

    MidiBuffer dummyMidi;
    filter.processBlock(*bufferToFill.buffer, dummyMidi);
    delay.processBlock(*bufferToFill.buffer, dummyMidi);
}

void MainContentComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()

    Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
    filter.releaseResources();
    delay.releaseResources();
}

void MainContentComponent::sliderValueChanged (Slider* slider) {
}


void MainContentComponent::paint (Graphics& g)
{
  g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	g.setFont(Font("Helvetica", 60.0f, Font::bold));
	g.setColour(Colours::limegreen);
	g.drawText("SoftSynth", getLocalBounds().removeFromTop(300).removeFromRight(300), Justification::centred, true);
}

void MainContentComponent::resized()
{
    Rectangle<int> area (getLocalBounds());

    //midi resize functions
    midiInputList.setBounds (area.removeFromTop (36).removeFromRight (getWidth() - 100).reduced (8));
    keyboardComponent.setBounds(area.removeFromBottom(100).reduced(8));
    midiMessagesBox.setBounds (area.removeFromTop(80).reduced (8));
	//levelLabel.setBounds(area.removeFromTop(90).removeFromRight(getWidth() - 20));
	levelSlider.setBounds(area.removeFromTop(90).removeFromRight (getWidth()-70));
	levelLabel.setJustificationType(Justification::centredLeft);
	levelSlider.setSize(100, 100);
	waveformList.setBounds(area.removeFromTop(90).removeFromRight(getWidth() - 95).removeFromLeft(getWidth() - 50));
	waveformList.setSize(100, 50);
	filterComponent->setBounds(area.removeFromBottom(91).reduced(8));
	delayComponent->setBounds(area.removeFromBottom(140).reduced(8));
}


String MainContentComponent::getMidiMessageDescription (const MidiMessage& m)
{
    if (m.isNoteOn())           return "Note on "  + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
    if (m.isNoteOff())          return "Note off " + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
    if (m.isProgramChange())    return "Program change " + String (m.getProgramChangeNumber());
    if (m.isPitchWheel())       return "Pitch wheel " + String (m.getPitchWheelValue());
    if (m.isAftertouch())       return "After touch " + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + String (m.getAfterTouchValue());
    if (m.isChannelPressure())  return "Channel pressure " + String (m.getChannelPressureValue());
    if (m.isAllNotesOff())      return "All notes off";
    if (m.isAllSoundOff())      return "All sound off";
    if (m.isMetaEvent())        return "Meta event";

    if (m.isController())
    {
        String name (MidiMessage::getControllerName (m.getControllerNumber()));

        if (name.isEmpty())
            name = "[" + String (m.getControllerNumber()) + "]";

        return "Controller " + name + ": " + String (m.getControllerValue());
    }
    return String::toHexString (m.getRawData(), m.getRawDataSize());
}

void MainContentComponent::logMessage (const String& m)
{
    midiMessagesBox.moveCaretToEnd();
    midiMessagesBox.insertTextAtCaret (m + newLine);
}

/** Starts listening to a MIDI input device, enabling it if necessary. */
void MainContentComponent::setMidiInput (int index)
{
    const StringArray list (MidiInput::getDevices());

    deviceManager.removeMidiInputCallback (list[lastInputIndex], this);

    const String newInput (list[index]);

    if (! deviceManager.isMidiInputEnabled (newInput))
        deviceManager.setMidiInputEnabled (newInput, true);

    deviceManager.addMidiInputCallback (newInput, this);
    midiInputList.setSelectedId (index + 1, dontSendNotification);

    lastInputIndex = index;
}

MainContentComponent::WaveType MainContentComponent::getActiveToneGenerator() {
  return waveformMap[waveformList.getItemText(waveformList.getSelectedItemIndex())];
}

void MainContentComponent::comboBoxChanged (ComboBox* box)
{
    if (box == &midiInputList) {
      setMidiInput (midiInputList.getSelectedItemIndex());
    }
}

// These methods handle callbacks from the midi device + on-screen keyboard..
void MainContentComponent::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
	const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, false);
    keyboardState.processNextMidiEvent (message);
    postMessageToList (message, source->getName());
}

void MainContentComponent::handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    if (! isAddingFromMidiInput)
    {
        MidiMessage m (MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity));
        m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
        postMessageToList (m, "On-Screen Keyboard");

        playLock.enter();
        switch(getActiveToneGenerator()) {
          case Sine:
            noteToneGenerator[midiNoteNumber] = new SineToneGenerator();
            break;
          case Saw:
            noteToneGenerator[midiNoteNumber] = new SawToneGenerator();
            break;
          default:
            noteToneGenerator[midiNoteNumber] = new SquareToneGenerator();
            break;
        }

        noteToneGenerator[midiNoteNumber]->setSampleRate(currentSampleRate);
        noteToneGenerator[midiNoteNumber]->setFrequency(getFrequency(m));
        playLock.exit();
    }
}

void MainContentComponent::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) {
    if (! isAddingFromMidiInput)
    {
        MidiMessage m (MidiMessage::noteOff (midiChannel, midiNoteNumber));
        m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
        postMessageToList (m, "On-Screen Keyboard");

        auto it = noteToneGenerator.find(midiNoteNumber);
        if(it != noteToneGenerator.end()) {
          playLock.enter();
          noteToneGenerator.erase(midiNoteNumber);
          delete it->second;
          playLock.exit();
        }
    }
}

void MainContentComponent::clearToneGenerators() {
  for(auto it = noteToneGenerator.begin(); it != noteToneGenerator.end(); it++) {
    delete it->second;
  }
}

double MainContentComponent::getFrequency(MidiMessage m){
	double hz = m.getMidiNoteInHertz(m.getNoteNumber());
//	std::string str = std::to_string(hz);
//	OutputDebugStringA(str);
	return hz;
}


void MainContentComponent::postMessageToList (const MidiMessage& message, const String& source)
{
    (new IncomingMessageCallback (this, message, source))->post();
}

void MainContentComponent::addMessageToList (const MidiMessage& message, const String& source)
{
    const double time = message.getTimeStamp() - startTime;

    const int hours = ((int) (time / 3600.0)) % 24;
    const int minutes = ((int) (time / 60.0)) % 60;
    const int seconds = ((int) time) % 60;
    const int millis = ((int) (time * 1000.0)) % 1000;

    const String timecode (String::formatted ("%02d:%02d:%02d.%03d",
                                                hours,
                                                minutes,
                                                seconds,
                                                millis));

    const String description (getMidiMessageDescription (message));

    const String midiMessageString (timecode + "  -  " + description + " (" + source + ")"); // [7]
    logMessage (midiMessageString);
}

Component* createMainContentComponent() { return new MainContentComponent(); }
