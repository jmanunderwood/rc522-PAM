#include<security/pam_appl.h>
#include<security/pam_misc.h>
#include<iostream>

const struct pam_conv conv = {
    misc_conv,
    NULL
};

int main(){
    pam_handle_t* pamh = NULL;
    int retval;
    const char *user = "nobody";
    char *uname;
    
    std::cout<<"Username: ";
    std::cin>>uname;
    user = uname;

    retval = pam_start("check", user, &conv, &pamh);

    if(retval == PAM_SUCCESS) retval = pam_authenticate(pamh, 0);

    if(retval == PAM_SUCCESS) retval = pam_acct_mgmt(pamh, 0);

    if(retval == PAM_SUCCESS){
        /*
            Await RFID Card data..
        */
        char *s;
        std::cout<<"Tap Card..\n";
        std::cin>>s;
        std::cout<<"Authentication successful.\n";
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