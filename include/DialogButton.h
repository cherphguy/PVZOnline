#pragma once
#include "ForwardDefinitions.h"
#include "UIButton.h"
class Sexy::DialogButton : public Sexy::UIButton
{
public:
	Image* ComponentImage;
	IVector2 Translation;
	IVector2 TextOffset;

	virtual ~DialogButton();
};

class LawnStoneButton : public Sexy::DialogButton
{
public:
	virtual ~LawnStoneButton();
	void ResizeToFit();
	static LawnStoneButton* __stdcall New(int ID, Sexy::ButtonListener* Listener, const PopString& Text);
	static void __stdcall Draw(LawnStoneButton* self, Sexy::Graphics* G, int X, int Y, int W, int H, bool Down, bool Highlighted, const PopString& Text);
};