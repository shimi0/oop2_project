#pragma once

#include "Button.h"

class ScoreButton :public Button 
{
public:

	ScoreButton();

	virtual void looseFocus() override;
	virtual void gainFocus() override;

private:

};