#include "ForwardDefinitions.h"
#include "DialogButton.h"

#include "Listeners.h"
#include "Resources.h"
#include "Graphics.h"
#include "LawnApp.h"
#include "Font.h"

void LawnStoneButton::ResizeToFit()
{
	int MinWidth;
	auto App = LawnApp::GetApp();
	if (App->mRegisterResourcesLoaded)
		MinWidth = (*Resources::DwarvenTodcraft18GreenInset)->TextWidth(Label);
	else
		MinWidth = Label.length() * 12;
	mBounds.mW = max(72, MinWidth + 46);
	mBounds.mH = 46;
}

LawnStoneButton* __stdcall LawnStoneButton::New(int ID, Sexy::ButtonListener* Listener, const PopString& Text)
{
	CONST DWORD Function = 0x448620;
	__asm
	{
		push Text
		push Listener
		push ID
		call Function
	}
}

void __stdcall LawnStoneButton::Draw(LawnStoneButton* self, Sexy::Graphics* G, int X, int Y, int W, int H, bool Down, bool Highlighted, const PopString& Text)
{
	using namespace Resources;
	auto Right = (Down) ? *StoneButtonRightDown : *StoneButtonRight;
	auto Left = (Down) ? *StoneButtonLeftDown : *StoneButtonLeft;
	auto Middle = (Down) ? *StoneButtonMiddleDown : *StoneButtonMiddle;
	auto Font = (Highlighted) ? *DwarvenTodcraft18BrightGreenInset : *DwarvenTodcraft18GreenInset;

	if (!(Right && Left && Middle && Font)) return;
	int Width = W;
	int StartX = X;
	W -= 71;
	int Segments = W / 46;
	int Remaining = W % 46;
	G->DrawImage(Right, X, Y);
	X += 36;
	for (int i = 0; i < Segments; i++)
	{
		G->DrawImage(Middle, X, Y);
		X += 46;
	}
	if (W > 0)
	{
		G->DrawImage(Middle, X, Y, Remaining, 46);
		X += Remaining;
	}
	G->DrawImage(Left, X, Y);
	G->mFont = Font;

	int SWidth = Font->TextWidth(Text);
	int Height = Font->GetAscent();
	G->mColor = Sexy::Color(255, 255, 255);
	G->DrawString(Text, StartX + 1 + (Width - SWidth) / 2, Y - 4 + (Height + (H - Height / 6) - 1) / 2);
}