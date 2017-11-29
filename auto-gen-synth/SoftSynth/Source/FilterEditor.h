#ifndef _FILTEREDITOR_H_
#define _FILTEREDITOR_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include <queue>

class FilterEditor : public GenericAudioProcessorEditor {
	FilterEditor(AudioProcessor *owner);
	~FilterEditor();


};


#endif

