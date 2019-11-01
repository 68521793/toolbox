#ifndef UTILITY_HPP
#define UTILITY_HPP
#define FILTERMASKMAX 128
#define E_OUT_OF_BOUNDARY -1
#define E_SIGNAL_INTERRUPT -2
#define E_IO_READ -3
#define E_SOCKETCREATION -4
#define E_SOCKETBINDEN -5
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <time.h>
#include <errno.h>
void delay_ms(const unsigned int interval);

#endif