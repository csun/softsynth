#ifndef _MAINCONTENTCOMPONENT_H_
#define _MAINCONTENTCOMPONENT_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterProcessor.h"


/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
<<<<<<< HEAD
class MainContentComponent   : 
	public AudioAppComponent, 
	public Slider::Listener,
	private ComboBox::Listener,
	private MidiInputCallback,
	private MidiKeyboardStateListener
=======
class MainContentComponent : public AudioAppComponent, public Slider::Listener
>>>>>>> 7b7fc7a43627101627b6cb8056f6a8a77a61df8c
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
    void updateAngleDelta();

    FilterProcessor filter;

    Component *filterComponent;
    Slider levelSlider;
    Label levelLabel;
    Slider frequencySlider;
    Label frequencyLabel;
    double currentSampleRate, currentAngle, angleDelta;

<<<<<<< HEAD
private:
    AudioDeviceManager deviceManager;
    ComboBox midiInputList;
    Label midiInputListLabel;
    int lastInputIndex;
    bool isAddingFromMidiInput;
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
    TextEditor midiMessagesBox;
    double startTime;


=======
>>>>>>> 7b7fc7a43627101627b6cb8056f6a8a77a61df8c
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif