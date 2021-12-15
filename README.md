# rc522 PAM
CSCI-484 Semester Project, James Underwood

A simple PAM module to interface with an RC522 RFID Card reader that requires an RFID card with the user's login name to be scanned.
Using an Arduino Mega 2560 for the serial interface.

## What exactly does this do?
i dunno man, but it's supposed to require an RFID card to be scanned in order to authenticate a user on a linux system.
Maybe it works.. Maybe it doesn't

## Well how does it do that?
Magic!
But also.. 
The PAM module itself opens and reads from the serial port, 
over which the Arduino is going to transmit the information read from the RFID chip. 

Once passed the username from the chip, 
the module compares it with the login name of the user trying to authenticate. 
If this fails, the module returns an Auth Error and lets the user try again. If it succeeds, 
then the user is allowed to input their password and continue  authenticating.

In order for this to occur, you need to add the line "auth required pam_rc522.so" 
to the top of your /etc/pam.d/common-auth file 
(or other pam stack config file for another service). 
This makes sure that whenever a user tries to authenticate on the system, 
the rc522 module is called first.

## Requirements
- This being a PAM module, a linux system is required.
- An arduino is also required for writing to and reading from an RFID card
- The two arduino sketches require the MFRC522 library
- Obviously, also required is a RFID-RC522 card reader, and accompanying RFID card

## Setup
Under src/RC522/RC522_write, there is an arduino sketch which will write your username to the RFID card. 

**Once your card contains the relevant data,**
You can upload the src/RC522/MFRC522_read.ino sketch to your arduino. 
This is the sketch that runs on the arduino, constantly reading data from the RFID-RC522

## Installation
### Step 1:
Put bin/pam_rc522.so in your lib/security directory
    (/lib/security; /lib/x86_64-linux-gnu/security; etc..).
### Step 2:
As stated above, add the line "auth required pam_rc522.so" to the top of your /etc/pam.d/common-auth file.
This will require the RFID card to be scanned, and the usernames to match before authenticating anywhere on the system.
### Step 3:
Make **Absolutely Sure** that the username on the card is correct for your username, 
and that the system can find the module before you restart or log out. 
Otherwise you may have to boot to another OS, 
and revert changes to the common-auth file before being able to authenticate again 
(learned this one the hard way).


Now you shoud only be able to authenticate on your system, if you are able to scan the correct RFID card for your user.


If anyone of you reading this is brave enough to install my software on your machine, 
I would appreciate it if your let me know how it goes, 
and open an Issue here if you encounter a problem along the way.
