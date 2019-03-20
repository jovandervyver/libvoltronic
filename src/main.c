#include "voltronic_crc.h"
#include "voltronic_dev.h"
#include "voltronic_dev_serial.h"
#include "voltronic_dev_usb.h"
#include <stdio.h>
#include <string.h>

int main() {

  //voltronic_dev_t dev = voltronic_serial_create("/dev/tty.usbserial", 2400, DATA_BITS_EIGHT, STOP_BITS_ONE, SERIAL_PARITY_NONE);
  voltronic_dev_t dev = voltronic_usb_create(0x0665, 0x5161, 0);
  if (dev == 0) {
    printf("Could not open /dev/usbserial\n");
    return 1;
  }

  voltronic_dev_write(dev, "\r", 1);
  printf("Written, waiting for output\n");
  char buffer[64];
  char* buff_ptr = buffer;
  int bytes_read = 0;
  int loop_done = 0;
  while((loop_done == 0) && (bytes_read < sizeof(buffer))) {
    int loop_bytes = voltronic_dev_read(dev, buff_ptr, sizeof(buffer) - (bytes_read + 1), 2000);
    if (loop_bytes > 0) {
      for(unsigned int count = 0; count < loop_bytes; ++count) {
        ++bytes_read;
        if (*buff_ptr == '\r') {
          loop_done = 1;
          break;
        }
        buff_ptr += sizeof(char);
      }
    }
  }

  *buff_ptr = 0;
  printf("%s\n", buffer);

  if (voltronic_dev_close(dev) > 0) {
    printf("Serial port closed\n");
    return 0;
  }
}
