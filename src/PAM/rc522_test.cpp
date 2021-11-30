#include<security/pam_appl.h>
#include<security/pam_misc.h>
#include<libserial/SerialPort.h>
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<iostream>


constexpr const char* const SERIAL_PORT = "/dev/ttyACM0";

const struct pam_conv conv = {
    misc_conv,
    NULL
};

int main(){
    pam_handle_t* pamh = NULL;
    int retval=-1;
    std::string user = "";
    std::string serial_in = "";
    std::string pass = "";
    const char* uname;
    LibSerial::SerialPort serial_port;
    std::cout<<"Scan card now: "<<std::endl;

    try{
        serial_port.Open(SERIAL_PORT);
    }catch(const LibSerial::OpenFailed&){
        std::cerr<<"Could not open serial port "<<SERIAL_PORT<<std::endl;
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
    user = serial_in.substr(0,serial_in.find('\n'));
    user.erase(user.find_first_of(' '), user.length()-user.find_first_of(' '));
    pass = serial_in.substr(serial_in.find('\n')+1, serial_in.size());
    pass.erase(pass.find_first_of(' '), pass.length()-pass.find_first_of(' '));

    std::cout<<"user: "<<user<<" + pass: "<<pass;
    
    user = const_cast<char*>(user.c_str());
    retval = pam_start("check_user", uname, &conv, &pamh);
    std::cout<<retval<<PAM_SUCCESS;

    if(retval == PAM_SUCCESS) retval = pam_authenticate(pamh, 0);

    if(retval == PAM_SUCCESS) retval = pam_acct_mgmt(pamh, 0);

    if(retval == PAM_SUCCESS){
        char *s;
        std::cout<<"Authentication Successful";
    }else{
        std::cout<<"Authentication failed.\n";
    }

    if(pam_end(pamh,retval) != PAM_SUCCESS){
        pamh = NULL;
        std::cout<<"Authentication failed to release.\n";
        exit(1);
    }

    return(retval==PAM_SUCCESS ? 0 : 1);
}