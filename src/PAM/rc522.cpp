
#include<libserial/SerialPort.h>
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<iostream>
#include<string>

#include<security/pam_misc.h>
#include<security/pam_modules.h>


constexpr const char* const SERIAL_PORT = "/dev/ttyACM0";
const char* module_data_name = "CARD_ID";

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv){
    std::string ID = "";
    std::string serial_in = "";

    LibSerial::SerialPort serial_port;

    std::cout<<"Scan card now: "<<std::endl;

    try{
        serial_port.Open(SERIAL_PORT);
    }catch(const LibSerial::OpenFailed&){
        std::cerr<<"Could not open serial port "<<SERIAL_PORT<<std::endl;
    }

    //Set BAUD,Flow Control, Parity, and stop bits for the serial connection
    serial_port.SetBaudRate(LibSerial::BaudRate::BAUD_9600);
    serial_port.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    serial_port.SetParity(LibSerial::Parity::PARITY_NONE);
    serial_port.SetStopBits(LibSerial::StopBits::STOP_BITS_1);
    
    //Wait for the device to start sending data
    while(!serial_port.IsDataAvailable()){ 
        usleep(1000);
    }

    size_t timeout = 250;
    LibSerial::DataBuffer read_buf;

    //Read the username from the arduino
    while(serial_in==""){ //TODO: eek
        try{
            serial_port.Read(read_buf,0,timeout);
        }catch(const LibSerial::ReadTimeout&){
            for(size_t i=0;i<read_buf.size();i++)
                serial_in += read_buf.at(i);

            std::cout<<"."<<std::endl;
        }
    }
    //Isolate the username, and then trim the whitespace
    ID=serial_in.substr(0,serial_in.find('\n'));
    ID.erase(ID.find_first_of(' '), ID.length()-ID.find_first_of(' '));

    int retval;
    const char* card_uname="";
    const char *uname="";

    card_uname = const_cast<char*>(ID.c_str());
    retval = pam_get_user(pamh,&uname,"Username: ");
    //Allow the user to continue logging in if the username on the card matches the current user
    if (strcmp(uname, card_uname)==0){
        retval=PAM_SUCCESS;
        std::cout<<"Card Success.";
    }else{
        retval=PAM_AUTH_ERR;
    }

    if (retval!=PAM_SUCCESS){
        return retval;
    }
    
    return PAM_SUCCESS;
}

