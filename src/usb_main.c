#include "voltronic_dev_usb.h"

/**
* This class is only here to link everything related to USB to assert compilation
*/

int main() {
  // Create a USB dev
  const char* serial_number = 0; // Optional
  voltronic_dev_t dev = voltronic_usb_create(0x0665, 0x5161, serial_number);

  // Query the device
  char buffer[256];
  int result = voltronic_dev_execute(dev, "QPI", 3, buffer, sizeof(buffer), 1000);
  
  // Close the connection to the device
  voltronic_dev_close(dev);

  return result <= 0 ? 1 : 0;
}
