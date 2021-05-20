#include <Wire.h>

#ifndef Adafruit_I2CDevice_h
#define Adafruit_I2CDevice_h

///< The class which defines how we will talk to this device over I2C
class Adafruit_I2CDevice {
public:
  Adafruit_I2CDevice(uint8_t addr, TwoWire *theWire = &Wire);
  /*!
   *    @brief  Returns the 7-bit address of this device
   *    @return The 7-bit address of this device
   */
  uint8_t address() const noexcept { return _addr; }
  bool begin(bool addr_detect = true);
  bool detected();

  bool read(uint8_t *buffer, size_t len, bool stop = true);
  bool write(const uint8_t *buffer, size_t len, bool stop = true,
             const uint8_t *prefix_buffer = nullptr, size_t prefix_len = 0);
  bool write_then_read(const uint8_t *write_buffer, size_t write_len,
                       uint8_t *read_buffer, size_t read_len,
                       bool stop = false);
  bool setSpeed(uint32_t desiredclk);

  /*!   @brief  How many bytes we can read in a transaction
   *    @return The size of the Wire receive/transmit buffer */
  size_t maxBufferSize() { return _maxBufferSize; }

private:
  uint8_t _addr;
  TwoWire *_wire;
  bool _begun = false;
  // use NSDMI
#ifdef ARDUINO_ARCH_SAMD
#define ADAFRUIT_I2CDEVICE_MAX_BUFFER_SIZE 250 // as defined in Wire.h's RingBuffer
#else
#define ADAFRUIT_I2CDEVICE_MAX_BUFFER_SIZE 32
#endif
  size_t _maxBufferSize = ADAFRUIT_I2CDEVICE_MAX_BUFFER_SIZE;
#undef ADAFRUIT_I2CDEVICE_MAX_BUFFER_SIZE

};

#endif // Adafruit_I2CDevice_h
