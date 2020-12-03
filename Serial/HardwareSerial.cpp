#include "HardwareSerial.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
//#include <inttypes.h>
//#include <PolledTimeout.h>
#include "../Arduino/Arduino.h"
#include "HardwareSerial.h"

//#include "Esp.h"

HardwareSerial::HardwareSerial(int uart_nr)
{
    myUart.uart_nr = uart_nr; 
}

void HardwareSerial::begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin, bool invert)
{
    myUart.baud_rate = baud;
}

void HardwareSerial::end()
{
    rxBuffer.clear();
    txBuffer.clear();
    myUart.uart_nr = -1;
    myUart.baud_rate = -1;
}

void HardwareSerial::updateBaudRate(unsigned long baud)
{
    myUart.baud_rate = baud;
}

size_t HardwareSerial::setRxBufferSize(size_t size) {
    myUart.rxBufferSize = size;
    return  myUart.rxBufferSize;
}

int HardwareSerial::available(void)
{
   
    return rxBuffer.size();
}

void HardwareSerial::flush()
{
    txBuffer.clear();
}

void HardwareSerial::startDetectBaudrate()
{
    
}

unsigned long HardwareSerial::testBaudrate()
{
    return myUart.baud_rate;
}

unsigned long HardwareSerial::detectBaudrate(time_t timeoutMillis)
{
    return myUart.baud_rate;
}

bool HardwareSerial::testRecievedNewPacket(std::deque<uint8_t> newPacket) {
    for (size_t i = 0; i < newPacket.size(); i++) {
        if (rxBuffer.size() >= myUart.rxBufferSize)
            return false;
        rxBuffer.push_back(newPacket[i]);
    }
    return true;
}

deque<uint8_t> HardwareSerial::getRxBuffer() {
    return rxBuffer;
}

deque<uint8_t> HardwareSerial::getTxBuffer() {
    return txBuffer;
}

HardwareSerial::~HardwareSerial() {}

void HardwareSerial::begin(unsigned long baud)
{
    rxBuffer.clear();
    txBuffer.clear();
    begin(baud, SERIAL_8N1, SERIAL_FULL, 1, false);
}
void HardwareSerial::begin(unsigned long baud, SerialConfig config)
{
    begin(baud, config, SERIAL_FULL, 1, false);
}
void HardwareSerial::begin(unsigned long baud, SerialConfig config, SerialMode mode)
{
    begin(baud, config, mode, 1, false);
}

void HardwareSerial::begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin)
{
    begin(baud, config, mode, tx_pin, false);
}



size_t HardwareSerial::getRxBufferSize()
{
    return myUart.rxBufferSize;
}

void HardwareSerial::swap()
{
    swap(1);
}
void HardwareSerial::swap(uint8_t tx_pin)    //toggle between use of GPIO13/GPIO15 or GPIO3/GPIO(1/2) as RX and TX
{
    //uart_swap(_uart, tx_pin);
}

/*
 * Toggle between use of GPIO1 and GPIO2 as TX on UART 0.
 * Note: UART 1 can't be used if GPIO2 is used with UART 0!
 */
void HardwareSerial::set_tx(uint8_t tx_pin)
{
    // uart_set_tx(_uart, tx_pin);
}

/*
 * UART 0 possible options are (1, 3), (2, 3) or (15, 13)
 * UART 1 allows only TX on 2 if UART 0 is not (2, 3)
 */
void HardwareSerial::pins(uint8_t tx, uint8_t rx)
{
    //uart_set_pins(_uart, tx, rx);
}


int HardwareSerial::peek(void) 
{
    // return -1 when data is unvailable (arduino api)
    return rxBuffer[0];
}
int HardwareSerial::read(void) 
{
    if (!available())
        return -1;
    int temp = rxBuffer[0];
    rxBuffer.pop_front();

    return temp;
}

size_t HardwareSerial::read(char* buffer, size_t size)
{
    int min = std::min(available(), (int)size);
    int counter = 0;

    while (min > counter) {
        buffer[counter] = (char)rxBuffer[counter];
        counter++;
        rxBuffer.pop_front();

    }
    return min;
}
size_t HardwareSerial::readBytes(char* buffer, size_t size)  {
    return read(buffer, size);

}
size_t HardwareSerial::readBytes(uint8_t* buffer, size_t size)  {
    return readBytes((char*)buffer, size);
}
int HardwareSerial::availableForWrite(void)
{
    return 0;
}
size_t HardwareSerial::write(uint8_t c)
{
    txBuffer.push_back(c);
    return txBuffer.size();
}
size_t HardwareSerial::write(const uint8_t* buffer, size_t size) 
{
    for (size_t i = 0; i < size; i++) {
        txBuffer.push_back(buffer[i]);
    }
    return txBuffer.size();
}
HardwareSerial::operator bool() const
{
    return true;
}
bool HardwareSerial::isTxEnabled(void)
{
    return myUart.tx_enabled;
}
bool HardwareSerial::isRxEnabled(void)
{
    return myUart.rx_enabled;
}
int HardwareSerial::baudRate(void)
{
    return myUart.baud_rate;
}

bool HardwareSerial::hasOverrun(void)
{
    return myUart.rx_overrun;
}

bool HardwareSerial::hasRxError(void)
{
    return myUart.rx_error;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
HardwareSerial Serial(UART0);
#endif
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL1)
HardwareSerial Serial1(UART1);
#endif