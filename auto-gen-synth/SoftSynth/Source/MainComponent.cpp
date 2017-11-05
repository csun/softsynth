/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize (800, 600);

        // specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
        
        addAndMakeVisible (levelSlider);
        levelSlider.setRange (0, 100);
        levelSlider.setTextValueSuffix (" Hz");
        
        addAndMakeVisible (levelLabel);
        levelLabel.setText ("Volume", dontSendNotification);
        levelLabel.attachToComponent (&levelSlider, true);
        
        levelSlider.setValue (100.0);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
        
        String message;
        message << "Preparing to play audio..." << newLine;
        message << " samplesPerBlockExpected = " << samplesPerBlockExpected << newLine;
        message << " sampleRate = " << sampleRate;
        Logger::getCurrentLogger()->writeToLog (message);
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        const float level = (float) levelSlider.getValue();
        const float levelScale = level * 2.0f;
        
        // For more details, see the help for AudioProcessor::getNextAudioBlock()
        Random r  = Random();
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
            // Get a pointer to the start sample in the buffer for this audio output channel
            float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        
            // Fill the required number of samples with noise betweem -0.125 and +0.125
            for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
                buffer[sample] = (sample * levelScale - level) * 0.12f;
            }
        }
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
        
        Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
    }

    //==============================================================================
    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        // You can add your drawing code here!
    }

    void resized() override
    {
        const int sliderLeft = 120;
        levelSlider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    }


private:
    //==============================================================================

    Slider levelSlider;
    Label levelLabel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
