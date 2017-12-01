#ifndef _MAINCONTENTCOMPONENT_H_
#define _MAINCONTENTCOMPONENT_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
#include "FilterProcessor.h"
#include "DelayProcessor.h"
#include "ToneGenerator.hpp"
#include "SineToneGenerator.hpp"
#include "SawToneGenerator.hpp"
#include "SquareToneGenerator.hpp"


/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   :
	public AudioAppComponent,
	public Slider::Listener,
	private ComboBox::Listener,
	private MidiInputCallback,
	private MidiKeyboardStateListener
{
public:
    MainContentComponent();
    ~MainContentComponent();


    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.
    void releaseResources() override;
    void sliderValueChanged (Slider* slider) override;
    //Following functions deal with midi
    //gets the midi message info from provided message
    static String getMidiMessageDescription (const MidiMessage& m);
    //logs the message to the midi messages box
    //We don't need to do this, just added it for ensuring that midi works
    void logMessage (const String& m);
    void setMidiInput (int index);
    void comboBoxChanged (ComboBox * box) override;
    // These methods handle callbacks from the midi device + on-screen keyboard..
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;

    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;

    double getFrequency(MidiMessage m);

    // This is used to dispach an incoming message to the message thread
    class IncomingMessageCallback   : public CallbackMessage
    {
    public:
        IncomingMessageCallback (MainContentComponent* o, const MidiMessage& m, const String& s)
           : owner (o), message (m), source (s)
        {}

        void messageCallback() override
        {
            if (owner != nullptr)
                owner->addMessageToList (message, source);
        }

        Component::SafePointer<MainContentComponent> owner;
        MidiMessage message;
        String source;
    };

    void postMessageToList (const MidiMessage& message, const String& source);

    void addMessageToList (const MidiMessage& message, const String& source);

    void paint (Graphics& g) override;
    void resized() override;

protected:
    void updateToneGenerator(ToneGenerator *toneGenerator);

    FilterProcessor filter;
    DelayProcessor delay;

    Component *filterComponent;
    Component *delayComponent;
    Slider levelSlider;
    Label levelLabel;
    double currentSampleRate;

    int activeMidiNote;

    std::map<String, ToneGenerator*> waveformMap;
    Label waveLabel;
    SawToneGenerator sawToneGenerator;
    SquareToneGenerator squareToneGenerator;
    SineToneGenerator sineToneGenerator;
    ToneGenerator *activeToneGenerator;

private:
    AudioDeviceManager deviceManager;
    ComboBox midiInputList;
    ComboBox waveformList;
    Label midiInputListLabel;
    int lastInputIndex;
    bool isAddingFromMidiInput;
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
    TextEditor midiMessagesBox;
    double startTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif
