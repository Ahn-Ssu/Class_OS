#include <mach/mach.h>

struct messgae {
    mach_msg_header_t header;
    int data;
};

mach_port_t client;
mach_port_t server;

/* Client Code */
struct message message;

// construct the header
message.header.msgh_size = sizeof(message);
message.header.msgh_remote_port = server;
message.header.msgh_local_port = client;

// send the messgae

mach_msg(&message.header,   // message header
    MACH_SEND_MSG,          // sending a message
    sizeof(message),        // size of message sent
    0,                      // maximum size of received message - unnecessary
    MACH_PORT_NULL,         // name of receive port - unnecessary
    MACH_MSG_TIMEOUT_NONE,  // no time outs
    MACH_PORT_NULL);         // no notify port 


/* Server Code */
struct message message;

// receive the message
mach_msg(&message.header,
    MACH_RCV_MSG,
    0,
    sizeof(message),
    server,
    MACH_MSG_TIMEOUT_NONE,
    MACH_PORT_NULL);
    