#include "MainContentComponent.h"

MainContentComponent::MainContentComponent() : 
    currentSampleRate (0.0),
    currentAngle (0.0), 
    angleDelta (0.0),
    lastInputIndex(0),
    isAddingFromMidiInput(false),
    keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard),
    startTime (Time::getMillisecondCounterHiRes() * 0.001)
{
    setSize (800, 600);

    // specify the number of input and output channels that we want to open
    setAudioChannels (0, 2);

    addAndMakeVisible (levelSlider);
    levelSlider.setRange (0, 100);

    addAndMakeVisible (levelLabel);
    levelLabel.setText ("Volume", dontSendNotification);
    levelLabel.attachToComponent (&levelSlider, true);

    addAndMakeVisible (frequencySlider);
    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.setSkewFactorFromMidPoint (500.0); // [4]
    frequencySlider.addListener (this);

    addAndMakeVisible (frequencyLabel);
    levelLabel.setText ("Frequency", dontSendNotification);
    levelLabel.attachToComponent (&levelSlider, true);
    frequencySlider.setTextValueSuffix (" Hz");

    levelSlider.setValue (20.0);
    frequencySlider.setValue(200.0);
    
    
    //Midi initialization
    
    setOpaque (true);

    addAndMakeVisible (midiInputListLabel);
    midiInputListLabel.setText ("MIDI Input:", dontSendNotification);
    midiInputListLabel.attachToComponent (&midiInputList, true);

    addAndMakeVisible (midiInputList);
    midiInputList.setTextWhenNoChoicesAvailable ("No MIDI Inputs Enabled");
    const StringArray midiInputs (MidiInput::getDevices());
    midiInputList.addItemList (midiInputs, 1);
    midiInputList.addListener (this);
    // find the first enabled device and use that by default
    for (int i = 0; i < midiInputs.size(); ++i)
    {
        if (deviceManager.isMidiInputEnabled (midiInputs[i]))
        {
            setMidiInput (i);
              break;
        }
    }
    // if no enabled devices were found just use the first one in the list
    if (midiInputList.getSelectedId() == 0) setMidiInput (0);

    addAndMakeVisible (keyboardComponent);
    keyboardState.addListener (this);

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
    
}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
    keyboardState.removeListener (this);
    deviceManager.removeMidiInputCallback (MidiInput::getDevices()[midiInputList.getSelectedItemIndex()], this);
    midiInputList.removeListener (this);
}


void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

    currentSampleRate = sampleRate;
    updateAngleDelta();
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    const float level = (float) levelSlider.getValue();

    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
        // Get a pointer to the start sample in the buffer for this audio output channel
        float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        // Fill the required number of samples with noise betweem -0.125 and +0.125
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
            const float currentSample = (float) std::sin (currentAngle);
            currentAngle += angleDelta;
            buffer[sample] = currentSample * level;
        }
    }
}

void MainContentComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()

    Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
}

void MainContentComponent::sliderValueChanged (Slider* slider)
{
    if (slider == &frequencySlider)
    {
        if (currentSampleRate > 0.0)
            updateAngleDelta();
    }
}


void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainContentComponent::resized()
{
    const int sliderLeft = 120;
    levelSlider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    frequencySlider.setBounds (sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    //midi resize functions
    Rectangle<int> area (getLocalBounds());
    midiInputList.setBounds (area.removeFromTop (36).removeFromRight (getWidth() - 150).reduced (8));
    keyboardComponent.setBounds (area.removeFromTop (80).reduced(8));
    midiMessagesBox.setBounds (area.reduced (8));
}

void MainContentComponent::updateAngleDelta()
{
    const double cyclesPerSample = frequencySlider.getValue() / currentSampleRate; // [2]
    angleDelta = cyclesPerSample * 2.0 * double_Pi;                                // [3]
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

void MainContentComponent::comboBoxChanged (ComboBox* box)
{
    if (box == &midiInputList)
        setMidiInput (midiInputList.getSelectedItemIndex());
}

// These methods handle callbacks from the midi device + on-screen keyboard..
void MainContentComponent::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    const ScopedValueSetter<bool> scopedInputFlag (isAddingFromMidiInput, true);
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
    }
	
}

void MainContentComponent::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) {
    if (! isAddingFromMidiInput)
    {
        MidiMessage m (MidiMessage::noteOff (midiChannel, midiNoteNumber));
        m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
        postMessageToList (m, "On-Screen Keyboard");
    }
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
