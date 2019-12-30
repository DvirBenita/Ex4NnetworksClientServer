#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int
main()
{
 char *hostname = "google.com";
 char *service = "http";
 struct addrinfo hints, *res0, *res;
 int err;
 int sock;

 memset(&hints, 0, sizeof(hints));
 hints.ai_socktype = SOCK_STREAM;
 hints.ai_family = PF_UNSPEC;

 if ((err = getaddrinfo(hostname, service, &hints, &res0)) != 0) {
   printf("error %d\n", err);
   return 1;
 }

   sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
 


   if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
     close(sock);

   }
   char buffer[256]={0};
   char httprequest[256] = "GET google.com HTTP/1.0 \n Host:";
   // write(sock, httprequest, strlen(httprequest));
char sendline[256], recvline[256];
char* ptr;

size_t n;

/// Form request
snprintf(sendline, 256, 
     "GET %s HTTP/1.0\r\n"  // POST or GET, both tested and works. Both HTTP 1.0 HTTP 1.1 works, but sometimes 
     "Host: %s\r\n"     // but sometimes HTTP 1.0 works better in localhost type
     "Content-type: application/x-www-form-urlencoded\r\n"
     "Content-length: %d\r\n\r\n"
     "%s\r\n",  (unsigned int)strlen(poststr), poststr);

/// Write the request
if (write(sock, sendline, strlen(sendline))>= 0) 
{
    /// Read the response
    while ((n = read(sock, recvline, 256)) > 0) 
    {
        recvline[n] = '\0';

        if(fputs(recvline, stdout) == EOF)
        {
            printf("fputs() error\n");
        }

        /// Remove the trailing chars
        ptr = strstr(recvline, "\r\n\r\n");

       
    }          
}
   /////////////////// 
   

 if (res == NULL) {
   /* could not create a valid connection */
   printf("failed\n");

   return 1;
 }

 freeaddrinfo(res0);

 /* Write transmission code using sock here... */

 return 0;
}