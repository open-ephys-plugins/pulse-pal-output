/*
    ------------------------------------------------------------------

    This file is part of the Tracking plugin for the Open Ephys GUI
    Written by:

    Alessio Buccino     alessiob@ifi.uio.no
    Mikkel Lepperod
    Svenn-Arne Dragly

    Center for Integrated Neuroplasticity CINPLA
    Department of Biosciences
    University of Oslo
    Norway

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PULSEPALOUTPUTCANVAS_H
#define PULSEPALOUTPUTCANVAS_H

#include "PulsePalOutput.h"
#include "PulsePalOutputEditor.h"
#include <VisualizerWindowHeaders.h>

/**

  Visualizer for the PulsePalOutput. It allows the user tho set all Pulse Pal parameters
  for the 4 stimulation channels.

  @see PulsePalOutput

*/

class PulsePalOutputCanvas : public Visualizer,
                             public Button::Listener,
                             public ComboBox::Listener,
                             public Label::Listener
{
public:
    /** Constructor */
    PulsePalOutputCanvas (PulsePalOutput* PulsePalOutput);

    /** Destructor */
    ~PulsePalOutputCanvas() {}

    /** Draw canvas background */
    void paint (Graphics&) override;

    /** Set position of sub-components */
    void resized() override;

    /** Create buttons */
    void initButtons();

    /** Create labels */
    void initLabels();

    /** Ensure parameters match processor */
    void updateLabels (int i);

    /** Get pointer to the processor */
    PulsePalOutput* getProcessor();

    /** Listener methods */
    void buttonClicked (Button* button) override;
    void labelTextChanged (Label* label) override;
    void comboBoxChanged (ComboBox* combobox) override;

    void lookAndFeelChanged() override;

    /** Visualizer methods (not used) */
    void refreshState() {}
    void update() {}
    void refresh() {}

private:
    PulsePalOutput* processor;

    // displays Pulse Pal status
    std::unique_ptr<Label> pulsePalLabel;

    // all components are arrays for the 4 channels
    std::unique_ptr<UtilityButton> burstButton[PULSEPALCHANNELS];
    std::unique_ptr<UtilityButton> biphasicButton[PULSEPALCHANNELS];
    std::unique_ptr<UtilityButton> ttlButton[PULSEPALCHANNELS];
    std::unique_ptr<UtilityButton> link2tr1Button[PULSEPALCHANNELS];
    std::unique_ptr<UtilityButton> link2tr2Button[PULSEPALCHANNELS];
    std::unique_ptr<UtilityButton> continuousButton[PULSEPALCHANNELS];
    std::unique_ptr<ComboBox> triggerMode[PULSEPALCHANNELS];

    std::unique_ptr<Label> channelLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> phase1Label[PULSEPALCHANNELS];
    std::unique_ptr<Label> phase2Label[PULSEPALCHANNELS];
    std::unique_ptr<Label> interphaseLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> voltage1Label[PULSEPALCHANNELS];
    std::unique_ptr<Label> voltage2Label[PULSEPALCHANNELS];
    std::unique_ptr<Label> restingVoltageLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> interpulseLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> burstDurationLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> interburstLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> repetitionsLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> trainDurationLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> trainDelayLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> triggerModeLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> phase1EditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> phase2EditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> interphaseEditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> voltage1EditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> voltage2EditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> restingVoltageEditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> interpulseEditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> burstDurationEditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> interburstEditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> repetitionsEditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> trainDurationEditLabel[PULSEPALCHANNELS];
    std::unique_ptr<Label> trainDelayEditLabel[PULSEPALCHANNELS];

    Colour labelColour;
    Colour labelTextColour;
    Colour labelBackgroundColour;
    float my_round (float x);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PulsePalOutputCanvas);
};

#endif // PULSEPALOUTPUTCANVAS_H
