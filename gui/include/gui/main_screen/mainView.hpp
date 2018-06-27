#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/mainViewBase.hpp>
#include <gui/main_screen/mainPresenter.hpp>
#include <touchgfx/containers/clock/DigitalClock.hpp>
#include <touchgfx/containers/clock/AnalogClock.hpp>

class mainView : public mainViewBase
{
public:
    mainView();
    virtual ~mainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	
	virtual void handleTickEvent();
protected:
	DigitalClock digitalClock;
	
	AnalogClock analogClock;
	
	int tickCounter;
    int hours;
    int minutes;
    int seconds;
};

#endif // MAIN_VIEW_HPP
