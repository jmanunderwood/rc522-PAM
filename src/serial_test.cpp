#include<libserial/SerialPort.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

constexpr const char* const SERIAL_PORT_1 = "/dev/ttyACM0";

int main() {
    using namespace LibSerial;

    SerialPort serial_port;

    try{
        serial_port.Open(SERIAL_PORT_1);
    }catch(const OpenFailed&){
        std::cerr<<"Failed to open serial port."<<std::endl;
        return EXIT_FAILURE;
    }

    serial_port.SetBaudRate(BaudRate::BAUD_9600);

    // Set the number of data bits.
    serial_port.SetCharacterSize(CharacterSize::CHAR_SIZE_8) ;

    // Turn off hardware flow control.
    serial_port.SetFlowControl(FlowControl::FLOW_CONTROL_NONE) ;

    // Disable parity.
    serial_port.SetParity(Parity::PARITY_NONE) ;
    
    // Set the number of stop bits.
    serial_port.SetStopBits(StopBits::STOP_BITS_1) ;
    
    // Wait for data to be available at the serial port.
    while(!serial_port.IsDataAvailable()) 
    {
        usleep(1000);
    }

    // Specify a timeout value (in milliseconds).
    size_t ms_timeout = 250 ;

    // Char variable to store data coming from the serial port.
    char data_byte ;

    // Read one byte from the serial port and print it to the terminal.

    DataBuffer read_buffer ;
    while(1){
        try
        {
            // Read as many bytes as are available during the timeout period.
            serial_port.Read(read_buffer, 0, ms_timeout) ;
        }
        catch (const ReadTimeout&)
        {
            for (size_t i = 0 ; i < read_buffer.size() ; i++)
            {
                std::cout << read_buffer.at(i) << std::flush ;
            }

            //std::cerr << "The Read() call timed out waiting for additional data." << std::endl ;
        }
    }
    

    // Successful program completion.
    return EXIT_SUCCESS ;
}