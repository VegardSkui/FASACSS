/* FASACSS 1.0
 * Forsker'n Almost Space Agency CanSat Software
 *
 * Made by some students at HVS
 */

// Bitrate for the serial interface (Radio and logger)
#define BITRATE 9600

// Accelerometer offsets
#define AccXOff 0.0
#define AccYOff 0.0
#define AccZOff 0.0

/**********************************************************/

// Useful variables
long int counter = 0;
int LOOPTIME = 500;

/********** [ Utility functions ] **********/
// Function to convert raw ADC data (0-255) to volt
float Bit2Volt(int pin)
{
  int raw = analogRead(pin);
  float volt = (float) raw * 5.0 / 1023;
  return volt;
}
/**********************************************************/

/********** [ Sensors ] **********/
// The Pressure Sensor (MPX4115)
float pressure()
{
  float volt = Bit2Volt(1);

  return volt;
}

// The LM335 Temperature Sensor
float temperature()
{
  analogReference(INTERNAL);
  analogRead(5);
  delay(5);
  // float Tmp, volt = Bit2Volt(5);  // Reads Analog5
  float Tmp, volt = analogRead(5) * 1.1 / 1023;
  analogReference(DEFAULT);
  analogRead(5);
  delay(10);

  return volt;
}

// The NTC Sensor
// Format 0 for volt, 1 for degrees Celsius
float ntc()
{
  float volt = Bit2Volt(0);

  return volt;
}

// The Accelerometer Sensor (MMA7361L)
float acc(char axis)
{
  // Get the correct pin for the axis
  int pin;
  float offset;
  switch (axis) {
    case 'x':
      pin = 2;
      offset = AccXOff;
      break;
    case 'y':
      pin = 3;
      offset = AccYOff;
      break;
    case 'z':
      pin = 4;
      offset = AccZOff;
  }

  // Get the volt value
  float volt = Bit2Volt(pin) + offset;

  return volt;
}
/**********************************/

void printData2Serial()
{
  // Counter
  Serial.print(counter);

  // Time
  Serial.print(";");
  Serial.print(millis());

  // Temperature
  Serial.print(";");
  Serial.print(temperature());

  // NTC
  Serial.print(";");
  Serial.print(ntc());

  // Pressure
  Serial.print(";");
  Serial.print(pressure());

  // Accelerometer
  Serial.print(";");
  Serial.print(acc('x'));
  Serial.print(";");
  Serial.print(acc('y'));
  Serial.print(";");
  Serial.print(acc('z'));

  Serial.println();
}

// Badass Setup
void setup()
{
  Serial.begin(BITRATE);

  Serial.println("Counter,Time,Temp,NTC,Pressure,Acceleration X,Accleration Y,Acceleration Z");
}

// Do something FASA
void loop()
{
    long int loop_start = millis(), loop_end;

    printData2Serial();

    counter++;
    loop_end = millis();

    // Delay the loop to aquire the correct loop time
    if (LOOPTIME > (loop_end - loop_start)) {
      delay(LOOPTIME - (millis() - loop_start));
    }
}
