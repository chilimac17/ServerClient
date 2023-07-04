/**
 * @file Client.h
 * @author Michael Chillemi
 * @brief M12.B4: Programming Assignment 6: Single Server-Client Connection to Multiple 
 *        Simultaneous Clients Connection.
 * @version 0.1
 * @date 2023-04-20
 * 
 * 
 */

/**
 *
 * @include(s) 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * @brief Constants
 * 
 */
#define PORT 8080

/**
 * @brief Variables
 * 
 */
int clientSocket; 
int connection_number;
struct sockaddr_in serverAddr;
char buffer_reader[1024];