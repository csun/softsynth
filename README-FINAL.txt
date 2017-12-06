Features that have been implemented:

- GUI for controlling Synthesizer parameters and effects
- Control the pitch of the Sythesizer with an external MIDI
  device, such as a keyboard
- Allow the synthesizer to be played polyphonically (more than
  one note at a time)
- Allow the synthesizer to generate tones of varying wave shapes
  (Sine, Saw, and Square)
- A filter, which can be set as High Pass (to filter out low frequencies)
  or Low Pass (to filter out high frequencies), with cutoff and resonance 
  parameters
- A delay effect, with modifiable parameters of delay time, feedback
  and mix amount (how much of the resulting sound is purely the effect 
  itself)

Class Hierarchy

- We have a Main.cpp file that inherits from:
	
	- JUCEApplication, which deals with starting and stopping the application

- The main runner starts a MainContentComponent, which inherits from:

	- AudioAppComponent, which handles audio playback
	- ComboBox::Listener, which deals with changing the MIDI input
	- MidiInputCallback, which recieves incoming MIDI messages
	- MidiKeyboardStateListener, which processes MIDI messages

- The MainContentComponent then has:
	
	- A map of ToneGenerator *, which is our own Abstract Class that generates samples
		- ToneGenerator has 3 implementations: 
			- SawToneGenerator, generates samples to represent a saw wave
			- SineToneGenerator, generates samples to represent a sine wave
 			- SquareToneGenerator, generates samples to represent a square wave

	- A FilterProcessor, which inherits from AudioProcessor
	- A DelayProcessor, which inherits from AudioProcessor
		- AudioProcessor is a Base Class for processing audio

Dynamic Memory Management

- To implement Polyphonic functionality, we create Tone generators on the fly, 
  as the application recieves MIDI notes. For each "Note On" message that is 
  sent, we create a new tone generator, and when a corresponding "Note Off" 
  message is sent, we delete that tone generator, to free memory.
- We also create the filter and delay components dynamically, so the program
  deletes them, as well as clears the tone generator map.

Tests

- We attempted to add some tests in the Test/ directory, but were unable to get them working in time.

DEMO VIDEO LINKS 
Part 1 : https://youtu.be/FULLyt2iPEs
Part 2 : https://youtu.be/iKe-GC_JHFQ

