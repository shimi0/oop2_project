#pragma once

#include "Button.h"

//a game button - opens the scores window

class ScoreButton :public Button 
{
public:

	ScoreButton();

	virtual void looseFocus() override;
	virtual void gainFocus() override;

private:

};