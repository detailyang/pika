#ifndef __PIKA_SERVER_H__
#define __PIKA_SERVER_H__

#include <stdio.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <fcntl.h>
#include <event.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/epoll.h>

#include "csapp.h"
#include "xdebug.h"
#include "pika_define.h"
#include "status.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

class PikaThread;
class PikaEpoll;
class PikaConn;

class PikaWorker
{
public:
    PikaWorker();
    ~PikaWorker();

    void Start();

private:
    friend class PikaConn;
    Status SetBlockType(BlockType type);

    /*
     * The udp server port and address
     */
    int sockfd_;
    int flags_;
    int port_;
    char host_[PIKA_NAME_LEN];

    /*
     * The listen socket address
     */
    struct sockaddr_in servaddr_;

    /*
     * The Epoll event handler
     */
    PikaEpoll *pikaEpoll_;

    /*
     * The leveldb handler
     */
    leveldb::DB *db_;

    leveldb::Options options_;

    /*
     * Here we used auto poll to find the next work thread,
     * last_thread_ is the last work thread
     */
    int last_thread_;
    /*
     * This is the work threads
     */
    PikaThread *pikaThread_[PIKA_THREAD_NUM];

    // No copying allowed
    PikaWorker(const PikaWorker&);
    void operator=(const PikaWorker&);

};

#endif
