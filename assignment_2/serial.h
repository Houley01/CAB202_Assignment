/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: serial.h             *
*********************************************
*/
void SerialSetup();
void usb_serial_send(char *message);
void send_formatted(char *buffer, int buffer_size, const char *format, ...);
int CheckForSerialInput();
