#pragma once
#include <string>
#include "GUI.hh"

//struct used for buttons in menu's
struct Button
{
	Transform transform;
	Color  frontColor = { 0, 150, 0 }, backColor= { 50, 200, 230 };					//default colors
	Sint32 width=0, height=0;
	char* text="";
	bool isActive = true;

	void init(char* newText, Transform newTransform) {
		text = newText;
		transform = newTransform;
		if (TTF_SizeText(R.GetFont<FontID::CANDY>(), text, &width, &height)){		//calculate button size (won't work well if scale isn't 1-1)
			std::cout << "Error";	//usar l'assert?
		}
	}
	bool isInside(Sint32 x, Sint32 y) {												//checks if x,y coordinates are inside the button
		if (isActive && (x > transform.x - width/2) && (x < transform.x + width/2)	//if Button is active, check the x
			&& (y > transform.y - height/2) && (y < transform.y + height/2)) {		//check the y
			return true;
		}
		return false;
	}
	void Draw() {
		if (isActive) {																//only draws button if it's active
			GUI::DrawButton<FontID::CANDY>(text, transform, frontColor, backColor);
		}
	}
};
