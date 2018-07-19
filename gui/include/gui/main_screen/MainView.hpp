#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void increaseValue();
    virtual void decreaseValue();

    void setCount(uint8_t countValue);
    void setLimitEffects(bool belowUpper, bool aboveLower);
    
protected:

private:
	uint8_t count;
};

#endif // MAIN_VIEW_HPP
