/*
  ==============================================================================

    ProLookAndFeel.h
    Created: 24 Apr 2019 10:44:51am
    Author:  minut

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "ProInterfaceDefines.h"

class ProLookAndFeel : public LookAndFeel_V4
{
public:

	ProLookAndFeel()
	{
		// Store image assets
		mSliderImage = ImageCache::getFromMemory(BinaryData::kadenze_knob_png, BinaryData::kadenze_bg_pngSize);

		// ComboBox colours
		setColour(ComboBox::backgroundColourId, ProColour_3);
		setColour(ComboBox::outlineColourId, ProColour_2);
		setColour(ComboBox::arrowColourId, ProColour_1);
		setColour(ComboBox::textColourId, ProColour_1);

		// Button text colours
		setColour(TextButton::buttonColourId, ProColour_1);
		setColour(TextButton::textColourOnId, ProColour_1);
		setColour(TextButton::textColourOffId, ProColour_1);
	}

	virtual ~ProLookAndFeel() {};

	// Button functions
	Font getTextButtonFont(TextButton&, int buttonHeight) override
	{
		return font_1;
	}

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
	{
		Colour fillColour;

		if (isButtonDown)
		{
			fillColour = ProColour_6;
		}
		else if (isMouseOverButton)
		{
			fillColour = ProColour_3;
		}
		else
		{
			fillColour = ProColour_5;
		}

		const float cornerSize = 6.0f;
		const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

		g.setColour(fillColour);
		g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
	}

	// ComboBox functions
	Font getLabelFont(Label& label) override
	{
		return font_1;
	}

	void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area, bool isSeparator,
						   bool isActive, bool isHighlighted, bool isTicked,
						   bool hasSubMenu, const String& text, const String& shortcutKeyText,
						   const Drawable* icon, const Colour* textColour) override
	{
		juce::Rectangle<int> r(area);

		Colour fillColour = isHighlighted ? ProColour_5 : ProColour_4;

		g.setColour(fillColour);
		g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);

		Colour myTextColour = isTicked ? ProColour_7 : ProColour_1;
		g.setColour(myTextColour);
		g.setFont(font_1);

		r.setLeft(10);
		r.setY(1);
		g.drawFittedText(text, r, Justification::left, 1);
	}

	void drawComboBox(Graphics& g, int width, int height, bool isButtonDown,
					  int buttonX, int buttonY, int buttonW, int buttonH,
					  ComboBox& box) override
	{
		const float cornerSize = 3.0f;
		const juce::Rectangle<int> boxBounds(0, 0, width, height);

		g.setColour(ProColour_3);
		g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

		juce::Rectangle<int> arrow(width - 30, 0, 20, height);

		Path path;

		path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
		path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
		path.lineTo(arrow.toFloat().getRight() - 3.0f, arrow.toFloat().getCentreY() - 2.0f);

		Colour arrowColour = box.findColour(ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);

		g.setColour(arrowColour);
		g.strokePath(path, PathStrokeType(2.0f));
	}

	// Slider functions
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
						  float sliderPosProportional, float rotaryStartAngle,
						  float rotaryEndAngle, Slider& slider) override
	{
		const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
		const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));

		const float radius = jmin(width * 0.5, height * 0.5);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;

		g.drawImage(mSliderImage, rx, ry, 2 * radius, 2 * radius, 0, frameIndex * mSliderImage.getWidth(), mSliderImage.getWidth(), mSliderImage.getWidth());
	}

private:

	Image mSliderImage;
};