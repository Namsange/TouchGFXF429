#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

mainView::mainView() :
	tickCounter(0),
    hours(9),
    minutes(18),
    seconds(36)
{
}

void mainView::setupScreen()
{
	// Setup digital clock
    digitalClock.setPosition(20, 40, 150, 30);
    digitalClock.setTypedText(TypedText(T_DIGITAL_CLOCK));
    digitalClock.setColor(Color::getColorFrom24BitRGB(0x7A, 0x7A, 0x7A));
    digitalClock.setDisplayMode(DigitalClock::DISPLAY_24_HOUR);
    digitalClock.displayLeadingZeroForHourIndicator(true);
    add(digitalClock);
	
    // Setup analog clock
    analogClock.setXY(200, 16);
    analogClock.setBackground(BITMAP_CLOCK_00_BACKGROUND_ID, 116, 116);  // (116, 116) will be the center of rotation the clock
    analogClock.setupHourHand(BITMAP_CLOCK_00_HOUR_HAND_ID, 2, 44);      // (2, 44) is the center of rotation of the hour hand image. This point will be placed at the clock center of rotation
    analogClock.setupMinuteHand(BITMAP_CLOCK_00_MINUTE_HAND_ID, 2, 64);  // (2, 64) is the center of rotation of the minute hand image. This point will be placed at the clock center of rotation
    analogClock.setupSecondHand(BITMAP_CLOCK_00_SECOND_HAND_ID, 4, 79);  // (4, 79) is the center of rotation of the second hand image. This point will be placed at the clock center of rotation
    analogClock.setHourHandMinuteCorrection(true);                       // The hour hand will move towards the next hour value as the minute hand moves towards 60.
    analogClock.setMinuteHandSecondCorrection(false);
    analogClock.setAnimation(10, EasingEquations::cubicEaseInOut);       // Use animation when updating the hands.
    add(analogClock);

    // Set start time for the digital clock
    digitalClock.setTime24Hour(hours, minutes, seconds);

    // Set start time for the analog clock. InitializeTime24Hour is
    // used instead of setTime24 hour to avoid animation of the hands.
    analogClock.initializeTime24Hour(hours, minutes, seconds);
}

void mainView::tearDownScreen()
{

}

void mainView::handleTickEvent()
{
    tickCounter++;

    if (tickCounter % 60 == 0)
    {
        if (++seconds >= 60)
        {
            seconds = 0;
            if (++minutes >= 60)
            {
                minutes = 0;
                if (++hours >= 24)
                {
                    hours = 0;
                }
            }
        }

        // Update the clocks
        digitalClock.setTime24Hour(hours, minutes, seconds);
        analogClock.setTime24Hour(hours, minutes, seconds);
    }
}
