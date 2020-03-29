#include "voltronic_dev_serial.h"

#define COMMAND "QPI"

int main() {
  // Create a serial port dev
  voltronic_dev_t dev = voltronic_serial_create(
    "invalid_name", 2400, DATA_BITS_EIGHT, STOP_BITS_ONE, SERIAL_PARITY_NONE);

  // Query the device
  char buffer[256];
  int result = voltronic_dev_execute(dev, COMMAND, strlen(COMMAND), buffer, sizeof(buffer), 1000);
  
  // Close the connection to the device
  voltronic_dev_close(dev);

  return 0;
}
