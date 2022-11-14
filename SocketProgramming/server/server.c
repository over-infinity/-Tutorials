/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

/***************************************
 * Stages for server:
 *   1. Socket creation
 *   2. Setsockopt
 *   3. Bind
 *   4. Listen
 *   5. Accept
 *
 ***************************************/

/*
 *  @name void error(const char *msg)
 *
 *  @brief This function is called when a system call fails.
 *          It displays a message about the error on stderr and then aborts the program.
 *          The perror man page gives more information.
 */

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     //The server reads characters from the socket connection into this buffer.
     char buffer[256];

     /* A sockaddr_in is a structure containing an internet address. This structure is defined in netinet/in.h.
      * Here is the definition:
      *
      * struct sockaddr_in
      * {
      *   short   sin_family; // must be AF_INET
      *   u_short sin_port;
      *   struct  in_addr sin_addr;
      *   char    sin_zero[8]; // Not used, must be zero
      *  };
      *
      * An in_addr structure, defined in the same header file, contains only one field, a unsigned long called s_addr.
      *
      * The variable serv_addr will contain the address of the server, and cli_addr will contain
      * the address of the client which connects to the server.
      */
     struct sockaddr_in serv_addr, cli_addr;

     int n;
     int opt = 1;

     /*
      * The user needs to pass in the port number on which the server will accept connections as an argument.
      * This code displays an error message if the user fails to do this.
      */
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(EXIT_FAILURE);
     }

     /*********************************************************************************************************************
      * 1. Socket creation:
      *
      *     int sockfd = socket(domain, type, protocol)
      *
      * The socket() system call creates a new socket. It takes three arguments. The first is the address domain of the socket.
      *
      * Recall that there are two possible address domains, the unix domain for two processes which share a common file system,
      * and the Internet domain for any two hosts on the Internet.
      * The symbol constant AF_UNIX is used for the former, and AF_INET for
      * the latter (there are actually many other options which can be used here for specialized purposes).
      *
      * sockfd: socket descriptor, an integer (like a file-handle)
      * The socket system call returns an entry into the file descriptor table (i.e. a small integer).
      * This value is used for all subsequent references to this socket. If the socket call fails, it returns -1.
      *
      * domain: integer, specifies communication domain.
      * We use AF_ LOCAL as defined in the POSIX standard for communication between processes on the same host.
      * For communicating between processes on different hosts connected by IPV4, we use AF_INET and
      * AF_I NET 6 for processes connected by IPV6.
      * Recall that there are two possible address domains, the unix domain for two processes which share a common file system,
      * and the Internet domain for any two hosts on the Internet.
      * The symbol constant AF_UNIX is used for the former, and AF_INET for
      * the latter (there are actually many other options which can be used here for specialized purposes).
      *
      * type: communication type
      * The second argument is the type of socket. Recall that there are two choices here,
      *  a stream socket in which characters are read in a continuous stream as if from a file or pipe,
      *  and a datagram socket, in which messages are read in chunks.  The two symbolic constants
      *  are SOCK_STREAM and SOCK_DGRAM:
      * SOCK_STREAM: TCP(reliable, connection oriented)
      * SOCK_DGRAM: UDP(unreliable, connectionless)
      *
      * protocol: Protocol value for Internet Protocol(IP), which is 0.
      * The third argument is the protocol. If this argument is zero (and it always should be except for unusual circumstances),
      *  the operating system will choose the most appropriate protocol. It will choose TCP for stream sockets and UDP for datagram sockets.
      *
      ***********************************************************************************************************************/

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     /*
      * @name bzero((char *) &serv_addr, sizeof(serv_addr));
      *
      * @brief The function bzero() sets all values in a buffer to zero.
      *       It takes two arguments, the first is a pointer to the buffer and the second is the size of the buffer.
      *       Thus, this line initializes serv_addr to zeros.
      */
     bzero((char *) &serv_addr, sizeof(serv_addr));

     /*
      * The port number on which the server will listen for connections is passed in as an argument,
      * and this statement uses the atoi() function to convert this from a string of digits to an integer.
      */
     portno = atoi(argv[1]);

     /*
      * The variable serv_addr is a structure of type struct sockaddr_in. This structure has four fields.
      * The first field is short sin_family, which contains a code for the address family.
      * It should always be set to the symbolic constant AF_INET.
      * */
     serv_addr.sin_family = AF_INET;


     /*
      * The second field of serv_addr is unsigned short sin_port, which contain the port number.
      *  However, instead of simply copying the port number to this field, it is necessary to convert
      *  this to network byte order using the function htons() which converts a port number
      *  in host byte order to a port number in network byte order.
      *
      * */
      serv_addr.sin_port = htons(portno);

     /*
      * The third field of sockaddr_in is a structure of type struct in_addr which contains only a single
      * field unsigned long s_addr. This field contains the IP address of the host.
      * For server code, this will always be the IP address of the machine on which the server
      * is running, and there is a symbolic constant INADDR_ANY which gets this address.
      * */
     serv_addr.sin_addr.s_addr = INADDR_ANY;



     /*********************************************************************************************
      * 2. Setsockopt:
      *
      *  int setsockopt(int sockfd, int level, int optname,  const void *optval, socklen_t optlen);
      *
      * This helps in manipulating options for the socket referred by the file descriptor sockfd.
      * This is completely optional, but it helps in reuse of address and port.
      * Prevents error such as: “address already in use”.
      *
      *********************************************************************************************/

     if (setsockopt(sockfd, SOL_SOCKET,
                        SO_REUSEADDR | SO_REUSEPORT, &opt,
                        sizeof(opt))) {
              error("ERROR on setsockopt");
         }

     /*******************************************************************************************
      * 3. Bind
      *
      *     int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
      *
      * After the creation of the socket, the bind function binds the socket to the address
      * and port number specified in addr(custom data structure).
      * In the example code, we bind the server to the localhost, hence we use INADDR_ANY to specify the IP address.
      *
      * The bind() system call binds a socket to an address, in this case the address of the current host and
      * port number on which the server will run. It takes three arguments, the socket file descriptor,
      * the address to which is bound, and the size of the address to which it is bound.
      * The second argument is a pointer to a structure of type sockaddr, but what is passed in
      * is a structure of type sockaddr_in, and so this must be cast to the correct type.
      * This can fail for a number of reasons, the most obvious being that this socket is already in use on this machine.
      * The bind() manual has more information.
      *******************************************************************************************/

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");


     /*****************************************************************************************************
      * 4. Listen:
      *
      *     int listen(int sockfd, int backlog);
      *
      * It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection.
      * The backlog, defines the maximum length to which the queue of pending connections for sockfd may grow.
      * If a connection request arrives when the queue is full, the client may receive an error with
      * an indication of ECONNREFUSED.
      *
      * The listen system call allows the process to listen on the socket for connections.
      * The first argument is the socket file descriptor, and the second is the size of the backlog queue,
      * i.e., the number of connections that can be waiting while the process is handling a particular connection.
      * This should be set to 5, the maximum size permitted by most systems.
      * If the first argument is a valid socket, this call cannot fail, and so the code doesn't check for errors.
      * The listen() man page has more information.
      *******************************************************************************************************/

     listen(sockfd,5);

     /*********************************************************************************************************
      * 5. Accept:
      *
      *   int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
      *
      * It extracts the first connection request on the queue of pending connections for the listening
      * socket, sockfd, creates a new connected socket, and returns a new file descriptor
      * referring to that socket. At this point, the connection is established between client and server,
      *  and they are ready to transfer data.
      *
      *  The accept() system call causes the process to block until a client connects to the server.
      *  Thus, it wakes up the process when a connection from a client has been successfully established.
      *  It returns a new file descriptor, and all communication on this connection should be done
      *  using the new file descriptor. The second argument is a reference pointer to the address of
      *  the client on the other end of the connection, and the third argument is the size of this structure.
      *
      */

     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     /*
      * Note that we would only get to this point after a client has successfully connected to our server.
      * This code initializes the buffer using the bzero() function, and then reads from the socket.
      * Note that the read call uses the new file descriptor, the one returned by accept(),
      * not the original file descriptor returned by socket().
      * Note also that the read() will block until there is something for it to read in the socket,
      * i.e. after the client has executed a write().
      * */
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);

     /*
      * Once a connection has been established, both ends can both read and write to the connection.
      * Naturally, everything written by the client will be read by the server, and everything written by the server
      *  will be read by the client. This code simply writes a short message to the client.
      *  The last argument of write is the size of the message. The write() man page has more information.
      * */

     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     // closing the listening socket
     shutdown(sockfd, SHUT_RDWR);
     return 0; 
}
