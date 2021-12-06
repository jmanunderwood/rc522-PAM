
#include<libserial/SerialPort.h>
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<iostream>

#include<security/pam_misc.h>
#include<security/pam_modules.h>


constexpr const char* const SERIAL_PORT = "/dev/ttyACM0";
const char* module_data_name = "CARD_ID";

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv){
    /*
    int retval;
    const char* uname;

    std::string ID = "";
    std::string serial_in = "";

    LibSerial::SerialPort serial_port;

    std::cout<<"Scan card now: "<<std::endl;

    try{
        serial_port.Open(SERIAL_PORT);
    }catch(const LibSerial::OpenFailed&){
        std::cerr<<"Could not open serial port "<<SERIAL_PORT<<std::endl;
    }

    while(!serial_port.IsDataAvailable()){
        usleep(1000);
    }

    serial_port.SetBaudRate(LibSerial::BaudRate::BAUD_9600);
    serial_port.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    serial_port.SetParity(LibSerial::Parity::PARITY_NONE);
    serial_port.SetStopBits(LibSerial::StopBits::STOP_BITS_1);
    
    while(!serial_port.IsDataAvailable()){
        usleep(1000);
    }

    size_t timeout = 250;
    LibSerial::DataBuffer read_buf;

    while(serial_in==""){ //TODO: eek
        try{
            serial_port.Read(read_buf,0,timeout);
        }catch(const LibSerial::ReadTimeout&){
            for(size_t i=0;i<read_buf.size();i++)
                serial_in += read_buf.at(i);
            
            std::cout<<"."<<std::endl;
        }
    }
    ID = serial_in.substr(0,serial_in.find('\n'));
    ID.erase(ID.find_first_of(' '), ID.length()-ID.find_first_of(' '));

    uname = const_cast<char*>(ID.c_str());
    const void** data;
    retval = pam_get_data(pamh, module_data_name, data);

    if (retval!=PAM_SUCCESS){
        return retval;
    }
    */
    return PAM_SUCCESS;
}

