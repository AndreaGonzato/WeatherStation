#include "src/Time.h"
Time myTime = Time();

#include "src/Mode.h"
Mode mode = Mode();

#include "src/Button.h"
Button setButton = Button(2, "SET");
Button minButton = Button(3, "MIN");
Button plusButton = Button(5, "PLUS");




void setup(){
    Serial.begin(9600);
}

void loop(){
    myTime.update();
    setButton.update(&mode);
    minButton.update(&mode);
    plusButton.update(&mode);

}
