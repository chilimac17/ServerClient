/**
 * @file Client.c
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
#include"Client.h"

//---------------------------------------------------------------------------//
//----------------------------MAIN METHOD------------------------------------//
//---------------------------------------------------------------------------//
int main()
{
	// Creating Client Socket.
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	// Checking If An Error Occurred In Creating Socket.
	if(clientSocket < 0)
	{
		printf("[-]Error In Creating.[-]\n");
		exit(1);
	}
	
	printf("[+]Client Socket is created.[+]\n");

	// Specifying Address for Client Socket.
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	// Connecting Client To Socket.
	connection_number = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	// Checking For Error. 
	if(connection_number < 0)
	{
		printf("[-]Error in connection.[-]\n");
		exit(1);
	}

	printf("[+]Connected to Server.[+]\n");

	// Infinite While Loop.
	while(1)
	{	
		// Scans Users Input & Sends It To Server. 
		printf("Client: \t");
		scanf("%s", &buffer_reader[0]);
		send(clientSocket, buffer_reader, strlen(buffer_reader), 0);

		// Use strcmp To Compare Buffer With Disconnection Key Words.
		// Closes Socket & Displays Message To User Indicating That
		// They Had Disconnected From The Server.
		if(strcmp(buffer_reader, ":exit") == 0 || strcmp(buffer_reader, "shutdown") == 0)
		{
			close(clientSocket);
			printf("[-]Disconnected from server.[-]\n");
			exit(1);
		}

		// If The Data Received By The Server Is Less Than 0.
		// Print Out An Error Message.
		if(recv(clientSocket, buffer_reader, 1024, 0) < 0)
		{
			printf("[-]Error in receiving data.[-]\n");
		}
		else
		{
			// Else Print The Message From The Server.
			printf("Server: \t%s\n", buffer_reader);
		}
	}

	return 0;
}