/**
 * @file MultiClientServer.c
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
#include "MultiClientServer.h"

//---------------------------------------------------------------------------//
//----------------------------MAIN METHOD------------------------------------//
//---------------------------------------------------------------------------//
int main()
{
	// Creating Master Socket Which Will Act As The Server Socket.
	master_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Check If The Master Socket Had An Error In Creation.
	if(master_socket < 0)
    {
		printf("[-]Error In Connecting Master Socket.[-]\n");
		exit(1);
	}

	printf("[+]Server Socket Is Created.[+]\n");

	// Define Server Address.  
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	// Binding Server Socket to Specified IP and Port.
	bind_num = bind(master_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	// Checking if Server Socket had a Error binding.
    if(bind_num < 0)
    {
		printf("[-]Error in binding.[-]\n");
		exit(1);
	}

	printf("[+]Bind to port %d\n", PORT);

	// Server Socket will listen uo to 10 connections.
	if(listen(master_socket, 10) == 0)
    {
		printf("[+]Listening....[+]\n");
	}
    else
    {
		printf("[-]Error in binding.[-]\n");
	}

	// Infinite While Loop.
	while(1)
	{
		// Accepting Incoming Connections to Server Socket.
		new_client_socket = accept(master_socket, (struct sockaddr*)&clientAddr, &addr_size);
		
		// Check If An Issue Occurred While Accepting Connection.
        if(new_client_socket < 0)
        {
			exit(1);
		}

		printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		// Fork Into A Child Process.
		if((childpid = fork()) == 0)
        {
			// Run Close Function on Server Socket.
			close(master_socket);

			// Infinite While Loop.
			while(1)
            {
				// Receive Function. 
				recv(new_client_socket, buffer, 1024, 0);
				
				// Use strcmp To Compare Buffer With Disconnection Key Words.
				if(strcmp(buffer, ":exit") == 0 || strcmp(buffer, "shutdown") == 0)
                {
					printf("Disconnected from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
					break;
				}
                else
                {
					// Print Client Message To Console & Echo It Back To Client.
					printf("Client %s:%d: %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buffer);
					send(new_client_socket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
			}
		}

	}

	// Close Client Socket. 
	close(new_client_socket);
	return 0;
}