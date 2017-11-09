#include "MainContentComponent.h"

MainContentComponent::MainContentComponent() : currentSampleRate (0.0),
    currentAngle (0.0), angleDelta (0.0)
{
    setSize (800, 600);

    // specify the number of input and output channels that we want to open
    setAudioChannels (0, 1);

    addAndMakeVisible (levelSlider);
    levelSlider.setRange (0.0, 1.0);

    addAndMakeVisible (levelLabel);
    levelLabel.setText ("Volume", dontSendNotification);
    levelLabel.attachToComponent (&levelSlider, true);

    addAndMakeVisible (frequencySlider);
    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.setSkewFactorFromMidPoint (500.0); // [4]
    frequencySlider.addListener (this);

    addAndMakeVisible (frequencyLabel);
    frequencyLabel.setText ("Frequency", dontSendNotification);
    frequencyLabel.attachToComponent (&frequencySlider, true);
    frequencySlider.setTextValueSuffix (" Hz");

    filterComponent = filter.createEditor();
    filterComponent->setBounds(getLocalBounds().removeFromBottom(200));
    addAndMakeVisible(filterComponent);

    levelSlider.setValue (0.125);
    frequencySlider.setValue(200.0);
}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
    delete filterComponent;
}


void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    filter.prepareToPlay(sampleRate, samplesPerBlockExpected);
    currentSampleRate = sampleRate;
    updateAngleDelta();
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    const float level = (float) levelSlider.getValue();

    // Get a pointer to the start sample in the buffer for this audio output channel
    // NOTE this synth is mono, so there will only ever be one channel.
    float* const buffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);

    for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
        const float currentSample = (float) std::sin (currentAngle);
        currentAngle += angleDelta;
        buffer[sample] = currentSample * level;
    }

    MidiBuffer dummyMidi;
    filter.processBlock(*bufferToFill.buffer, dummyMidi);
}

void MainContentComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()

    Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
    filter.releaseResources();
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
