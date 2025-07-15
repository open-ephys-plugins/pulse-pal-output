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

#include "PulsePalOutputCanvas.h"
#include "PulsePalOutput.h"

PulsePalOutputCanvas::PulsePalOutputCanvas (PulsePalOutput* PulsePalOutput)
    : processor (PulsePalOutput), labelColour (Colour (200, 255, 0)), labelTextColour (Colour (255, 200, 0)), labelBackgroundColour (Colour (100, 100, 100))
{
    initButtons();
    initLabels();
}

float PulsePalOutputCanvas::my_round (float x)
{
    return x < 0.0 ? ceil (x - 0.5) : floor (x + 0.5);
}

void PulsePalOutputCanvas::paint (Graphics& g)
{
    g.setColour (findColour (ThemeColours::componentParentBackground)); // background color
    g.fillRect (0, 0, getWidth(), getHeight());

    // Check Pulse Pal connection
    if (processor->getPulsePalVersion() > 0)
    {
        pulsePalLabel->setText (String ("Pulse Pal: ") += String ("CONNECTED"), dontSendNotification);
    }
    else
    {
        pulsePalLabel->setText (String ("Pulse Pal: ") += String ("NOT CONNECTED"), dontSendNotification);
    }

    for (int i = 0; i < PULSEPALCHANNELS; i++)
    {
        g.setColour (findColour (ThemeColours::componentBackground)); // component background color
        g.fillRoundedRectangle (0.005 * getWidth() + 0.25 * i * getWidth(), 0.1 * getHeight(), 0.23 * getWidth(), 0.885 * getHeight(), 4.0f);
    }
}

void PulsePalOutputCanvas::resized()
{
    pulsePalLabel->setBounds (0.01 * getWidth(), 0.02 * getHeight(), 0.95 * getWidth(), 0.04 * getHeight());

    for (int i = 0; i < PULSEPALCHANNELS; i++)
    {
        channelLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.11 * getHeight(), 0.2 * getWidth(), 0.04 * getHeight());

        phase1Label[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.2 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        phase1EditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.2 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        voltage1Label[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.25 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        voltage1EditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.25 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        phase2Label[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.3 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        phase2EditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.3 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        voltage2Label[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.35 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        voltage2EditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.35 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        interphaseLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.4 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        interphaseEditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.4 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());

        restingVoltageLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.45 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        restingVoltageEditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.45 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        interpulseLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.5 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        interpulseEditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.5 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        burstDurationLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.55 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        burstDurationEditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.55 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        interburstLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.6 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        interburstEditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.6 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        trainDurationLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.65 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        trainDurationEditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.65 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        trainDelayLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.7 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        trainDelayEditLabel[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.7 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        triggerModeLabel[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.75 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());
        triggerMode[i]->setBounds (0.13 * getWidth() + 0.25 * i * getWidth(), 0.75 * getHeight(), 0.1 * getWidth(), 0.04 * getHeight());

        link2tr1Button[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.83 * getHeight(), 0.11 * getWidth(), 0.03 * getHeight());
        link2tr2Button[i]->setBounds (0.12 * getWidth() + 0.25 * i * getWidth(), 0.83 * getHeight(), 0.11 * getWidth(), 0.03 * getHeight());
        biphasicButton[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.87 * getHeight(), 0.11 * getWidth(), 0.03 * getHeight());
        burstButton[i]->setBounds (0.12 * getWidth() + 0.25 * i * getWidth(), 0.87 * getHeight(), 0.11 * getWidth(), 0.03 * getHeight());
        ttlButton[i]->setBounds (0.01 * getWidth() + 0.25 * i * getWidth(), 0.91 * getHeight(), 0.11 * getWidth(), 0.06 * getHeight());
        continuousButton[i]->setBounds (0.12 * getWidth() + 0.25 * i * getWidth(), 0.91 * getHeight(), 0.11 * getWidth(), 0.06 * getHeight());
    }
}

void PulsePalOutputCanvas::buttonClicked (Button* button)
{
    for (int i = 0; i < PULSEPALCHANNELS; i++)
    {
        if (button == biphasicButton[i].get())
        {
            if (button->getToggleState() == true)
            {
                processor->setIsBiphasic (i, true);
                phase2Label[i]->setVisible (true);
                phase2EditLabel[i]->setVisible (true);
                interphaseLabel[i]->setVisible (true);
                interphaseEditLabel[i]->setVisible (true);
                voltage2Label[i]->setVisible (true);
                voltage2EditLabel[i]->setVisible (true);
            }
            else
            {
                processor->setIsBiphasic (i, false);
                phase2Label[i]->setVisible (false);
                phase2EditLabel[i]->setVisible (false);
                interphaseLabel[i]->setVisible (false);
                interphaseEditLabel[i]->setVisible (false);
                voltage2Label[i]->setVisible (false);
                voltage2EditLabel[i]->setVisible (false);
            }
        }
        else if (button == burstButton[i].get())
        {
            if (button->getToggleState() == true)
            {
                if (processor->getBurstDuration (i) == 0)
                {
                    processor->setBurstDuration (i, DEF_BURSTDURATION);
                    processor->setInterBurstInt (i, DEF_INTER_BURST);
                }
                burstDurationLabel[i]->setVisible (true);
                burstDurationEditLabel[i]->setVisible (true);
                interburstLabel[i]->setVisible (true);
                interburstEditLabel[i]->setVisible (true);
            }
            else
            {
                if (processor->getBurstDuration (i) != 0)
                {
                    processor->setBurstDuration (i, 0);
                    processor->setInterBurstInt (i, 0);
                }
                burstDurationLabel[i]->setVisible (false);
                burstDurationEditLabel[i]->setVisible (false);
                interburstLabel[i]->setVisible (false);
                interburstEditLabel[i]->setVisible (false);
            }
        }
        else if (button == link2tr1Button[i].get())
        {
            if (button->getToggleState() == true)
                processor->setLinkTriggerChannel1 (i, 1);
            else if (button->getToggleState() == false)
                processor->setLinkTriggerChannel1 (i, 0);
        }
        else if (button == link2tr2Button[i].get())
        {
            if (button->getToggleState() == true)
                processor->setLinkTriggerChannel2 (i, 1);
            else if (button->getToggleState() == false)
                processor->setLinkTriggerChannel2 (i, 0);
        }
        else if (button == ttlButton[i].get())
        {
            // set ttl channel i
            processor->setTTLsettings (i);
            processor->setIsBiphasic (i, false);
            phase2Label[i]->setVisible (false);
            phase2EditLabel[i]->setVisible (false);
            interphaseLabel[i]->setVisible (false);
            interphaseEditLabel[i]->setVisible (false);
            voltage2Label[i]->setVisible (false);
            voltage2EditLabel[i]->setVisible (false);
            burstDurationLabel[i]->setVisible (false);
            burstDurationEditLabel[i]->setVisible (false);
            interburstLabel[i]->setVisible (false);
            interburstEditLabel[i]->setVisible (false);
            if (biphasicButton[i]->getToggleState() == true)
            {
                biphasicButton[i]->setToggleState (false, dontSendNotification);
            }
            if (burstButton[i]->getToggleState() == true)
            {
                burstButton[i]->setToggleState (false, dontSendNotification);
            }
        }
        else if (button == continuousButton[i].get())
        {
            if (button->getToggleState() == true)
                processor->setContinuous (i, 1);
            else if (button->getToggleState() == false)
                processor->setContinuous (i, 0);
        }
        if (! processor->checkParameterConsistency (i))
        {
            CoreServices::sendStatusMessage ("Inconsistent parameters: set train duration first");
            processor->adjustParameters (i);
        }
        updateLabels (i);
        processor->updatePulsePal (i);
    }
    repaint();
}

void PulsePalOutputCanvas::labelTextChanged (Label* label)
{
    for (int i = 0; i < PULSEPALCHANNELS; i++)
    {
        if (label == phase1EditLabel[i].get())
        {
            // 100 - 3600*10e3 (3600 s)
            Value val = label->getTextValue();
            float value = float (my_round (float (val.getValue()) * 10) / 10); //only multiple of 100us
            if ((float (val.getValue()) >= 0 && int (val.getValue()) <= MAX_INTERVAL))
            {
                processor->setPhase1Duration (i, value);
                label->setText (String (value), dontSendNotification);
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 3600000 with 0.1 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == phase2EditLabel[i].get())
        {
            // 100 - 3600000 (3600 s)
            Value val = label->getTextValue();
            float value = float (my_round (float (val.getValue()) * 10) / 10); //only multiple of 100us
            if ((float (val.getValue()) >= 0 && int (val.getValue()) <= MAX_INTERVAL))
            {
                processor->setPhase2Duration (i, value);
                label->setText (String (value), dontSendNotification);
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 3600*10e3 with 0.1 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == interphaseEditLabel[i].get())
        {
            Value val = label->getTextValue();
            float value = float (my_round (float (val.getValue()) * 10) / 10); //only multiple of 100us
            if ((float (val.getValue()) >= 0 && int (val.getValue()) <= MAX_INTERVAL))
            {
                processor->setInterPhaseInt (i, value);
                label->setText (String (value), dontSendNotification);
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 3600*10e3 with 0.1 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == voltage1EditLabel[i].get())
        {
            Value val = label->getTextValue();
            if (float (val.getValue()) >= 0 && float (val.getValue()) <= MAX_VOLTAGE)
            {
                processor->setVoltage1 (i, float (val.getValue()));
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 10 with 0.05 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == voltage2EditLabel[i].get())
        {
            Value val = label->getTextValue();
            if (float (val.getValue()) >= 0 && float (val.getValue()) <= MAX_VOLTAGE)
            {
                processor->setVoltage2 (i, float (val.getValue()));
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 10 with 0.05 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == burstDurationEditLabel[i].get())
        {
            Value val = label->getTextValue();
            float value = float (my_round (float (val.getValue()) * 10) / 10); //only multiple of 100us
            if ((float (val.getValue()) >= 0 && int (val.getValue()) <= MAX_INTERVAL))
            {
                processor->setBurstDuration (i, value);
                label->setText (String (value), dontSendNotification);
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 3600*10e3 with 0.1 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == interburstEditLabel[i].get())
        {
            Value val = label->getTextValue();
            float value = float (my_round (float (val.getValue()) * 10) / 10); //only multiple of 100us
            if ((float (val.getValue()) >= 0 && int (val.getValue()) <= MAX_INTERVAL))
            {
                processor->setInterBurstInt (i, value);
                label->setText (String (value), dontSendNotification);
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 3600*10e3 with 0.1 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == interpulseEditLabel[i].get())
        {
            Value val = label->getTextValue();
            float value = float (my_round (float (val.getValue()) * 10) / 10); //only multiple of 100us
            if ((float (val.getValue()) >= 0 && int (val.getValue()) <= MAX_INTERVAL))
            {
                processor->setInterPulseInt (i, value);
                label->setText (String (value), dontSendNotification);
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 3600*10e3 with 0.1 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == trainDurationEditLabel[i].get())
        {
            Value val = label->getTextValue();
            float value = float (my_round (float (val.getValue()) * 10) / 10); //only multiple of 100us
            if ((float (val.getValue()) >= 0 && int (val.getValue()) <= MAX_INTERVAL))
            {
                processor->setTrainDuration (i, value);
                label->setText (String (value), dontSendNotification);
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 3600*10e3 with 0.1 step!");
                label->setText ("", dontSendNotification);
            }
        }
        else if (label == trainDelayEditLabel[i].get())
        {
            Value val = label->getTextValue();
            float value = float (my_round (float (val.getValue()) * 10) / 10); //only multiple of 100us
            if ((float (val.getValue()) >= 0 && int (val.getValue()) <= MAX_INTERVAL))
            {
                processor->setTrainDelay (i, value);
                label->setText (String (value), dontSendNotification);
            }
            else
            {
                CoreServices::sendStatusMessage ("Selected values must be within 0 and 3600*10e3 with 0.1 step!");
                label->setText ("", dontSendNotification);
            }
        }
        if (! processor->checkParameterConsistency (i))
        {
            CoreServices::sendStatusMessage ("Inconsistent parameters: set train duration first");
            processor->adjustParameters (i);
        }
        updateLabels (i);
        processor->updatePulsePal (i);
    }
}

void PulsePalOutputCanvas::comboBoxChanged (ComboBox* combobox)
{
    for (int i = 0; i < PULSEPALCHANNELS; i++)
        if (combobox == triggerMode[i].get())
            processor->setTriggerMode (i, combobox->getSelectedId() - 1);
}

void PulsePalOutputCanvas::initButtons()
{
    for (int i = 0; i < PULSEPALCHANNELS; i++)
    {
        auto biph = std::make_unique<UtilityButton> ("Biphasic");
        biph->setRadius (3.0f);
        biph->setTooltip ("Biphasic mode");
        biph->setFont (FontOptions (15.0f));
        biph->addListener (this);
        biph->setClickingTogglesState (true);
        biphasicButton[i] = std::move (biph);
        addAndMakeVisible (biphasicButton[i].get());

        auto burst = std::make_unique<UtilityButton> ("Burst");
        burst->setRadius (3.0f);
        burst->setTooltip ("Burst mode");
        burst->setFont (FontOptions (15.0f));
        burst->addListener (this);
        burst->setClickingTogglesState (true);
        burstButton[i] = std::move (burst);
        addAndMakeVisible (burstButton[i].get());

        auto link21 = std::make_unique<UtilityButton> ("Link Trig 1");
        link21->setRadius (3.0f);
        link21->setTooltip ("Link trigger channel 1");
        link21->setFont (FontOptions (15.0f));
        link21->addListener (this);
        link21->setClickingTogglesState (true);
        link2tr1Button[i] = std::move (link21);
        addAndMakeVisible (link2tr1Button[i].get());

        auto link22 = std::make_unique<UtilityButton> ("Link Trig 2");
        link22->setRadius (3.0f);
        link22->setTooltip ("Link trigger channel 2");
        link22->setFont (FontOptions (15.0f));
        link22->addListener (this);
        link22->setClickingTogglesState (true);
        link2tr2Button[i] = std::move (link22);
        addAndMakeVisible (link2tr2Button[i].get());

        auto ttl = std::make_unique<UtilityButton> ("TTL");
        ttl->setRadius (3.0f);
        ttl->setFont (FontOptions (20.0f));
        ttl->addListener (this);
        ttlButton[i] = std::move (ttl);
        addAndMakeVisible (ttlButton[i].get());

        auto continuous = std::make_unique<UtilityButton> ("Continuous");
        continuous->setRadius (3.0f);
        continuous->setTooltip ("Continuous mode");
        continuous->setFont (FontOptions (20.0f));
        continuous->addListener (this);
        continuous->setClickingTogglesState (true);
        continuousButton[i] = std::move (continuous);
        addAndMakeVisible (continuousButton[i].get());

        auto mode = std::make_unique<ComboBox>();
        mode->addListener (this);
        for (int j = 0; j < 3; j++)
            mode->addItem (String (j), j + 1);
        mode->setSelectedId (processor->getTriggerMode (i) + 1, dontSendNotification);
        triggerMode[i] = std::move (mode);
        addAndMakeVisible (triggerMode[i].get());

        if (processor->getIsBiphasic (i))
            biphasicButton[i]->triggerClick();
        if (processor->getLinkTriggerChannel1 (i))
            link2tr1Button[i]->triggerClick();
        if (processor->getLinkTriggerChannel2 (i))
            link2tr2Button[i]->triggerClick();
    }
}

void PulsePalOutputCanvas::updateLabels (int i)
{
    phase1EditLabel[i]->setText (String (processor->getPhase1Duration (i)), dontSendNotification);
    phase2EditLabel[i]->setText (String (processor->getPhase2Duration (i)), dontSendNotification);
    voltage1EditLabel[i]->setText (String (processor->getVoltage1 (i)), dontSendNotification);
    voltage2EditLabel[i]->setText (String (processor->getVoltage2 (i)), dontSendNotification);
    interphaseEditLabel[i]->setText (String (processor->getInterPhaseInt (i)), dontSendNotification);
    restingVoltageEditLabel[i]->setText (String (processor->getRestingVoltage (i)), dontSendNotification);
    interpulseEditLabel[i]->setText (String (processor->getInterPulseInt (i)), dontSendNotification);
    burstDurationEditLabel[i]->setText (String (processor->getBurstDuration (i)), dontSendNotification);
    interburstEditLabel[i]->setText (String (processor->getInterBurstInt (i)), dontSendNotification);
    trainDurationEditLabel[i]->setText (String (processor->getTrainDuration (i)), dontSendNotification);
    trainDelayEditLabel[i]->setText (String (processor->getTrainDelay (i)), dontSendNotification);
}

void PulsePalOutputCanvas::initLabels()
{
    pulsePalLabel = std::make_unique<Label> ("s_pp", "Pulse Pal:");
    pulsePalLabel->setColour (Label::textColourId, labelColour);
    pulsePalLabel->setFont (FontOptions ("Inter", "Semi Bold", 40.0f));
    addAndMakeVisible (pulsePalLabel.get());

    FontOptions labelFont ("Inter", "Regular", 18.0f);

    for (int i = 0; i < PULSEPALCHANNELS; i++)
    {
        auto chan = std::make_unique<Label> ("s_phase1", "Channel " + String (i + 1));
        chan->setFont (FontOptions ("Inter", "Regular", 30.0f));
        channelLabel[i] = std::move (chan);
        addAndMakeVisible (channelLabel[i].get());

        auto ph1 = std::make_unique<Label> ("s_phase1", "Phase1 [ms]:");
        ph1->setFont (labelFont);
        phase1Label[i] = std::move (ph1);
        addAndMakeVisible (phase1Label[i].get());

        auto ph2 = std::make_unique<Label> ("s_phase2", "Phase2 [ms]:");
        ph2->setFont (labelFont);
        phase2Label[i] = std::move (ph2);
        addAndMakeVisible (phase2Label[i].get());
        phase2Label[i]->setVisible (false);

        auto intph = std::make_unique<Label> ("s_interphase", "Interphase [ms]:");
        intph->setFont (labelFont);
        interphaseLabel[i] = std::move (intph);
        addAndMakeVisible (interphaseLabel[i].get());
        interphaseLabel[i]->setVisible (false);

        auto v1 = std::make_unique<Label> ("s_v1", "Voltage1 [V]:");
        v1->setFont (labelFont);
        voltage1Label[i] = std::move (v1);
        addAndMakeVisible (voltage1Label[i].get());

        auto v2 = std::make_unique<Label> ("s_v2", "Voltage2 [V]:");
        v2->setFont (labelFont);
        voltage2Label[i] = std::move (v2);
        addAndMakeVisible (voltage2Label[i].get());
        voltage2Label[i]->setVisible (false);

        auto rv = std::make_unique<Label> ("s_v2", "Rest Voltage [V]:");
        rv->setFont (labelFont);
        restingVoltageLabel[i] = std::move (rv);
        addAndMakeVisible (restingVoltageLabel[i].get());

        auto intpul = std::make_unique<Label> ("s_intpul", "Interpulse [ms]:");
        intpul->setFont (labelFont);
        interpulseLabel[i] = std::move (intpul);
        addAndMakeVisible (interpulseLabel[i].get());

        auto burst = std::make_unique<Label> ("s_train", "Burst Duration [ms]:");
        burst->setFont (labelFont);
        burstDurationLabel[i] = std::move (burst);
        addAndMakeVisible (burstDurationLabel[i].get());
        burstDurationLabel[i]->setVisible (false);

        auto burstint = std::make_unique<Label> ("s_train", "Inter Burst [ms]:");
        burstint->setFont (labelFont);
        interburstLabel[i] = std::move (burstint);
        addAndMakeVisible (interburstLabel[i].get());
        interburstLabel[i]->setVisible (false);

        auto train = std::make_unique<Label> ("s_train", "Train Duration [ms]:");
        train->setFont (labelFont);
        trainDurationLabel[i] = std::move (train);
        addAndMakeVisible (trainDurationLabel[i].get());

        auto traindel = std::make_unique<Label> ("s_traindel", "Train Delay [ms]:");
        traindel->setFont (labelFont);
        trainDelayLabel[i] = std::move (traindel);
        addAndMakeVisible (trainDelayLabel[i].get());

        auto trigmode = std::make_unique<Label> ("s_traindel", "Trigger Mode:");
        trigmode->setFont (labelFont);
        triggerModeLabel[i] = std::move (trigmode);
        addAndMakeVisible (triggerModeLabel[i].get());

        auto phEd1 = std::make_unique<Label> ("phase1", String (DEF_PHASE_DURATION));
        phEd1->setFont (labelFont);
        phEd1->setEditable (true);
        phase1EditLabel[i] = std::move (phEd1);
        phase1EditLabel[i]->addListener (this);
        addAndMakeVisible (phase1EditLabel[i].get());

        auto phEd2 = std::make_unique<Label> ("phase2", String (DEF_PHASE_DURATION));
        phEd2->setFont (labelFont);
        phEd2->setEditable (true);
        phase2EditLabel[i] = std::move (phEd2);
        phase2EditLabel[i]->addListener (this);
        addAndMakeVisible (phase2EditLabel[i].get());
        phase2EditLabel[i]->setVisible (false);

        auto intphEd = std::make_unique<Label> ("interphase", String (DEF_INTER_PHASE));
        intphEd->setFont (labelFont);
        intphEd->setEditable (true);
        interphaseEditLabel[i] = std::move (intphEd);
        interphaseEditLabel[i]->addListener (this);
        addAndMakeVisible (interphaseEditLabel[i].get());
        interphaseEditLabel[i]->setVisible (false);

        auto vEd1 = std::make_unique<Label> ("v1", String (DEF_VOLTAGE));
        vEd1->setFont (labelFont);
        vEd1->setEditable (true);
        voltage1EditLabel[i] = std::move (vEd1);
        voltage1EditLabel[i]->addListener (this);
        addAndMakeVisible (voltage1EditLabel[i].get());

        auto vEd2 = std::make_unique<Label> ("v2", String (DEF_VOLTAGE));
        vEd2->setFont (labelFont);
        vEd2->setEditable (true);
        voltage2EditLabel[i] = std::move (vEd2);
        voltage2EditLabel[i]->addListener (this);
        addAndMakeVisible (voltage2EditLabel[i].get());
        voltage2EditLabel[i]->setVisible (false);

        auto rvEd = std::make_unique<Label> ("v2", String (0));
        rvEd->setFont (labelFont);
        rvEd->setEditable (true);
        restingVoltageEditLabel[i] = std::move (rvEd);
        restingVoltageEditLabel[i]->addListener (this);
        addAndMakeVisible (restingVoltageEditLabel[i].get());

        auto intpulEd = std::make_unique<Label> ("pul", String (DEF_INTER_PULSE));
        intpulEd->setFont (labelFont);
        intpulEd->setEditable (true);
        interpulseEditLabel[i] = std::move (intpulEd);
        interpulseEditLabel[i]->addListener (this);
        addAndMakeVisible (interpulseEditLabel[i].get());

        auto burstEd = std::make_unique<Label> ("burst", String (0));
        burstEd->setFont (labelFont);
        burstEd->setEditable (true);
        burstDurationEditLabel[i] = std::move (burstEd);
        burstDurationEditLabel[i]->addListener (this);
        addAndMakeVisible (burstDurationEditLabel[i].get());
        burstDurationEditLabel[i]->setVisible (false);

        auto burstintEd = std::make_unique<Label> ("train", String (0));
        burstintEd->setFont (labelFont);
        burstintEd->setEditable (true);
        interburstEditLabel[i] = std::move (burstintEd);
        interburstEditLabel[i]->addListener (this);
        addAndMakeVisible (interburstEditLabel[i].get());
        interburstEditLabel[i]->setVisible (false);

        auto traindelEd = std::make_unique<Label> ("train", String (0));
        traindelEd->setFont (labelFont);
        traindelEd->setEditable (true);
        trainDelayEditLabel[i] = std::move (traindelEd);
        trainDelayEditLabel[i]->addListener (this);
        addAndMakeVisible (trainDelayEditLabel[i].get());

        auto trainEd = std::make_unique<Label> ("train", String (DEF_TRAINDURATION));
        trainEd->setFont (labelFont);
        trainEd->setEditable (true);
        trainDurationEditLabel[i] = std::move (trainEd);
        trainDurationEditLabel[i]->addListener (this);
        addAndMakeVisible (trainDurationEditLabel[i].get());
    }
}

void PulsePalOutputCanvas::lookAndFeelChanged()
{
    for (int i = 0; i < PULSEPALCHANNELS; i++)
    {
        phase1EditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        phase1EditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        phase2EditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        phase2EditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        interphaseEditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        interphaseEditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        voltage1EditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        voltage1EditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        voltage2EditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        voltage2EditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        restingVoltageEditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        restingVoltageEditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        interpulseEditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        interpulseEditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        burstDurationEditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        burstDurationEditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        interburstEditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        interburstEditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        trainDelayEditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        trainDelayEditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));

        trainDurationEditLabel[i]->setColour (Label::backgroundColourId, findColour (ThemeColours::widgetBackground));
        trainDurationEditLabel[i]->setColour (Label::outlineColourId, findColour (ThemeColours::outline).withAlpha (0.5f));
    }
}
