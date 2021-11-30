
#include<libserial/SerialPort.h>
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<iostream>

#include<security/pam_misc.h>
#include<security/pam_modules.h>


constexpr const char* const SERIAL_PORT = "/dev/ttyACM0";

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv){
    
    int retval;
    const char* uname;

    std::string user = "";
    std::string serial_in = "";
    std::string pass = "";

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
    
    retval = pam_get_user(pamh, &uname, "Test: ");



    if (retval!=PAM_SUCCESS){
        return retval;
    }
    
    return PAM_SUCCESS;
}

