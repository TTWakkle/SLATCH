int long duration;

const int motor = 10;

void setup() {
    pinMode(motor, OUTPUT);
}

void loop() {
        analogWrite(motor,55);
        delay(1000);
        analogWrite(motor,63);
        delay(2000);
}
