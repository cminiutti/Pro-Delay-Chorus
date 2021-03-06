/*
  ==============================================================================

    ProParameters.h
    Created: 8 Apr 2019 1:21:32pm
    Author:  minut

  ==============================================================================
*/

#pragma once

enum ProParameters
{
	pParameter_InputGain = 0,
	pParameter_DelayTime,
	pParameter_DelayFeedback,
	pParameter_DelayWetDry,
	pParameter_DelayType,
	pParameter_OutputGain,
	pParameter_ModulationRate,
	pParameter_ModulationDepth,
	pParameter_TotalNumParameters,
};

static String ProParameterID[pParameter_TotalNumParameters] =
{
	"InputGain",
	"Time",
	"Feedback",
	"WetDry",
	"Type",
	"OutputGain",
	"ModulationRate",
	"ModulationDepth",
};

static String ProParameterLabel[pParameter_TotalNumParameters] =
{
	"Input Gain",
	"Time",
	"Feedback",
	"Wet Dry",
	"Type",
	"Output Gain",
	"Modulation Rate",
	"Modulation Depth"
};

static std::vector<float> ProParameterDefaultValue{ 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f };