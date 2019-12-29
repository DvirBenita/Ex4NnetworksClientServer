#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
static double
run_strtod (const char * input);
void printsin(struct sockaddr_in *s, char *str1, char *str2) {
  printf("%s\n", str1);
  printf("%s: ", str2);
  printf("%s= %s, %s= %d", "ip", inet_ntoa(s->sin_addr), "port", s->sin_port);
  printf("\n");
}

 
int main(int argc, char *argv[])
{
  
  int socket_fd, cc, fsize;
  //address and port of server/client
  struct sockaddr_in  s_in, from;
  //sturct represting massge
  struct { char head; char body[100]; char tail;} msg;
  struct { char head; char body[100]; char tail;} msg1;
  //open new socket with ipv3 and udp protocol
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
 //reset the address and port of client
  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */
  //changes the type  ipv4/6 of server to ipv4 
  s_in.sin_family = (short)AF_INET;
  //init the server internet address and casting from regular address to network
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);
  //init the server port and casting from regular adrress ip to network address
  s_in.sin_port = htons((u_short)0x3333);
  printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  
  
  fflush(stdout);//clean standart input
  //bind connect address and port with socket
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
 //^^socket return,pointer to sockaddr , len of the sturct

  double r = 0.0;
  for(;;) {
    //the size of address and port of server
    fsize = sizeof(from);
    //recive massge from the client
    cc = recvfrom(socket_fd,&msg1,sizeof(msg1),0,(struct sockaddr *)&from,&fsize);
    r =run_strtod(msg1.body);
    printf("the number i got is %lf\n",r);
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
    printsin((struct sockaddr*) &from, "recv_udp: ", "Packet from:");


    //print when got the data from the client
    printf("Got data ::%c%s%c\n",msg.head, msg.body,msg.tail);
    
    fflush(stdout);
    double ra =rand()/(double)RAND_MAX;
   printf("the random number is : %lf\n", ra);
  if(ra>r){
    //////send time
    int socket_fd;
  //the server address and port
  struct sockaddr_in  dest;
  //information about the server
  struct hostent *hostptr;
  //messge sturct
  struct { char head; char body[100]; char tail; } msgbuf;//change body to char[100]
  //open socket with ipv4 ,udp protocol
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  //rest the bits
  bzero((char *) &dest, sizeof(dest));
  //return to hostptr the information about the server by name
  hostptr = gethostbyname("localhost");
  //server address is ipv4
  dest.sin_family = (short) AF_INET;
  //copy to dest the server address
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  //the server port
  dest.sin_port = htons((u_short)0x3332);
  //message hrad
  msgbuf.head = '<';
  //  msgbuf.body = htonl(getpid()); /* IMPORTANT! */
  //copy the message from input
  strncpy(msgbuf.body, msg.body,sizeof(msg.body)); /* IMPORTANT! */ //changed to argv[2]
  msgbuf.tail = '>';
  printf("Send the messge to server with the port %d",dest.sin_port);
  printf("\n");
  //send the message to server
  sendto(socket_fd,&msgbuf,sizeof(msgbuf),0
  ,(struct sockaddr *)&dest, sizeof(dest));
  //recive the name back
  int dsize =sizeof(dest);
  int cc1;
  cc1 = recvfrom(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,&dsize);
  printf("Got data ::%c%s%c\n",msgbuf.head, msgbuf.body,msgbuf.tail);
   //send back the name
   printf("Send the messge back to client with the port: %d",from.sin_port);
  printf("\n");
  sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,
                  sizeof(from));
  }else{
    printf("the messge dropped");
  }
  }
  return 0;
}

static double
run_strtod (const char * input)
{
    double output;
    char * end;



    output = strtod (input, & end);

    if (end == input) {
        printf (" is not a valid number.\n");
    }
    else {
       
        return output;
    }
}

