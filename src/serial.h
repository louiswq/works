#pragma once



int OpenDev(char *Dev);
int set_Parity(int fd, int databits, int stopbits, int parity);
void set_speed(int fd, int speed);
