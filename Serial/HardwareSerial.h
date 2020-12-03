#ifndef HardwareSerial_h
#define HardwareSerial_h
#include <deque>
//#include <time> // See issue #6714
#include "../Stream/Stream.h"
#include "uart.h"
#include <algorithm>
using namespace std;
enum SerialConfig {
    SERIAL_5N1 = UART_5N1,
    SERIAL_6N1 = UART_6N1,
    SERIAL_7N1 = UART_7N1,
    SERIAL_8N1 = UART_8N1,
    SERIAL_5N2 = UART_5N2,
    SERIAL_6N2 = UART_6N2,
    SERIAL_7N2 = UART_7N2,
    SERIAL_8N2 = UART_8N2,
    SERIAL_5E1 = UART_5E1,
    SERIAL_6E1 = UART_6E1,
    SERIAL_7E1 = UART_7E1,
    SERIAL_8E1 = UART_8E1,
    SERIAL_5E2 = UART_5E2,
    SERIAL_6E2 = UART_6E2,
    SERIAL_7E2 = UART_7E2,
    SERIAL_8E2 = UART_8E2,
    SERIAL_5O1 = UART_5O1,
    SERIAL_6O1 = UART_6O1,
    SERIAL_7O1 = UART_7O1,
    SERIAL_8O1 = UART_8O1,
    SERIAL_5O2 = UART_5O2,
    SERIAL_6O2 = UART_6O2,
    SERIAL_7O2 = UART_7O2,
    SERIAL_8O2 = UART_8O2,
};

enum SerialMode {
    SERIAL_FULL = UART_FULL,
    SERIAL_RX_ONLY = UART_RX_ONLY,
    SERIAL_TX_ONLY = UART_TX_ONLY
};

class HardwareSerial : public Stream
{
    std::deque<uint8_t> rxBuffer;
    std::deque<uint8_t> txBuffer;
    //size_t rpos;
    //size_t wpos;
    struct uart_
    {
        int uart_nr;
        int baud_rate;
        bool rx_enabled;
        bool tx_enabled;
        bool rx_overrun;
        bool rx_error;
        uint8_t rx_pin;
        uint8_t tx_pin;
        size_t rxBufferSize=64;
        struct uart_rx_buffer_* rx_buffer;
    }myUart;

public:
    bool testRecievedNewPacket(std::deque<uint8_t> newPacket);
    deque<uint8_t> getRxBuffer();

    deque<uint8_t> getTxBuffer();
    HardwareSerial(int uart_nr);
    virtual ~HardwareSerial();
    void begin(unsigned long baud);
    void begin(unsigned long baud, SerialConfig config);
    void begin(unsigned long baud, SerialConfig config, SerialMode mode);

    void begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin);

    void begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin, bool invert);

    void end();

    void updateBaudRate(unsigned long baud);

    size_t setRxBufferSize(size_t size);
    size_t getRxBufferSize();

    void swap();
    void swap(uint8_t tx_pin);

    /*
     * Toggle between use of GPIO1 and GPIO2 as TX on UART 0.
     * Note: UART 1 can't be used if GPIO2 is used with UART 0!
     */
    void set_tx(uint8_t tx_pin);

    /*
     * UART 0 possible options are (1, 3), (2, 3) or (15, 13)
     * UART 1 allows only TX on 2 if UART 0 is not (2, 3)
     */
    void pins(uint8_t tx, uint8_t rx);

    int available(void) override;

    int peek(void) override;
    int read(void) override;

    size_t read(char* buffer, size_t size);
    size_t readBytes(char* buffer, size_t size) override;
    size_t readBytes(uint8_t* buffer, size_t size) override;
    int availableForWrite(void);
    void flush(void) override;
    size_t write(uint8_t c) override;
    size_t write(const uint8_t* buffer, size_t size) override;
    using Print::write; // Import other write() methods to support things like write(0) properly
    operator bool() const;
    void setDebugOutput(bool);
    bool isTxEnabled(void);
    bool isRxEnabled(void);
    int baudRate(void);

    bool hasOverrun(void);

    bool hasRxError(void);

    void startDetectBaudrate();

    unsigned long testBaudrate();

    unsigned long detectBaudrate(time_t timeoutMillis);

protected:

};

extern HardwareSerial Serial;
extern HardwareSerial Serial1;

#endif
