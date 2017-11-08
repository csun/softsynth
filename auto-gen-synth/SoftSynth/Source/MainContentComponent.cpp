#include "MainContentComponent.h"

MainContentComponent::MainContentComponent() : currentSampleRate (0.0),
    currentAngle (0.0), angleDelta (0.0)
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
}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
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
}

void MainContentComponent::updateAngleDelta()
{
    const double cyclesPerSample = frequencySlider.getValue() / currentSampleRate; // [2]
    angleDelta = cyclesPerSample * 2.0 * double_Pi;                                // [3]
}
