#ifndef _MAINCONTENTCOMPONENT_H_
#define _MAINCONTENTCOMPONENT_H_

#include "../JuceLibraryCode/JuceHeader.h"


/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public AudioAppComponent, public Slider::Listener
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


    void paint (Graphics& g) override;
    void resized() override;


protected:
    void updateAngleDelta();


    Slider levelSlider;
    Label levelLabel;
    Slider frequencySlider;
    Label frequencyLabel;
    double currentSampleRate, currentAngle, angleDelta;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif
