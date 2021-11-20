#include<security/pam_misc.h>
#include<security/pam_modules.h>
#include<iostream>

using namespace std;

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv){
    int retval;
    const char *uname;

    retval = pam_get_user(pamh, &uname, "Username: ");

    if (retval!=PAM_SUCCESS){
        return retval;
    }
    return PAM_SUCCESS;
}