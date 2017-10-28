/****************************************************************************
 *  Socket Library 
 *
 *  Author       : Park Dong Ro
 *  LastModify   : 2006.1
 *  Comment      : C++ Portable Types Library Port 
 *
 ****************************************************************************/

#ifndef __SZ_SOCK_H__
#define __SZ_SOCK_H__

#if defined(__WIN32__) && !defined(WIN32)
#  define WIN32
#endif

#ifdef __WIN32__
#   include <winsock2.h>
#else
#	include <errno.h>
#   include <netdb.h>       // for socklen_t
#   include <sys/types.h>
#   include <sys/socket.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//==========================================================================
// SYSTEM PORTING
//==========================================================================
#ifdef _MSC_VER
// we don't want "unreferenced inline function" warning
#  pragma warning (disable: 4514)
#endif

typedef unsigned int    uint;
typedef unsigned long   ulong;
typedef unsigned short  ushort;
typedef unsigned char   uchar;
typedef signed char     schar;
typedef char*           pchar;
typedef const char*     pconst;
typedef void*           ptr;
typedef int*            pint;

//
// portable 64-bit integers:
//
#if defined(_MSC_VER) || defined(__BORLANDC__)
   typedef __int64             large;
   typedef unsigned __int64    ularge;
#else
   typedef long long           large;
   typedef unsigned long long  ularge;
#endif


#if defined(_MSC_VER) || defined(__BORLANDC__)
#  define strcasecmp stricmp
#  define snprintf _snprintf
// atoll() is not portable, use AnsiStringtoi() instead
// #  define atoll _atoi64
#endif

//
// misc.
//
#ifndef NULL
#   define NULL 0
#endif

#define nil 0

inline int   imax(int x, int y)       { return (x > y) ? x : y; }
inline int   imin(int x, int y)       { return (x < y) ? x : y; }
inline large lmax(large x, large y)   { return (x > y) ? x : y; }
inline large lmin(large x, large y)   { return (x < y) ? x : y; }

void* memalloc(uint a);
void* memrealloc(void* p, uint a);
void memfree(void* p);
void memerror();
//==========================================================================
/*
#ifdef _MSC_VER
#pragma pack(push, 4)
#endif
*/
const int invhandle = -1;

// max backlog value for listen()
#ifndef SOMAXCONN
#  define SOMAXCONN -1
#endif

typedef char* sockval_t;

#ifndef __WIN32__
#  define closesocket close
#endif


#if defined(__DARWIN__) || defined(__WIN32__)
  typedef int psocklen;
#else
  typedef socklen_t psocklen;
#endif


//------------------------------------------------------
// BSD-compatible socket error codes for Win32
//------------------------------------------------------

#if defined(WSAENOTSOCK) && !defined(ENOTSOCK)

#define EWOULDBLOCK             WSAEWOULDBLOCK
#define EINPROGRESS             WSAEINPROGRESS
#define EALREADY                WSAEALREADY
#define ENOTSOCK                WSAENOTSOCK
#define EDESTADDRREQ            WSAEDESTADDRREQ
#define EMSGSIZE                WSAEMSGSIZE         // 10040
#define EPROTOTYPE              WSAEPROTOTYPE
#define ENOPROTOOPT             WSAENOPROTOOPT
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#define EOPNOTSUPP              WSAEOPNOTSUPP
#define EPFNOSUPPORT            WSAEPFNOSUPPORT
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#define EADDRINUSE              WSAEADDRINUSE
#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#define ENETDOWN                WSAENETDOWN
#define ENETUNREACH             WSAENETUNREACH
#define ENETRESET               WSAENETRESET
#define ECONNABORTED            WSAECONNABORTED
#define ECONNRESET              WSAECONNRESET
#define ENOBUFS                 WSAENOBUFS
#define EISCONN                 WSAEISCONN
#define ENOTCONN                WSAENOTCONN
#define ESHUTDOWN               WSAESHUTDOWN
#define ETOOMANYREFS            WSAETOOMANYREFS
#define ETIMEDOUT               WSAETIMEDOUT
#define ECONNREFUSED            WSAECONNREFUSED
#define ELOOP                   WSAELOOP
// #define ENAMETOOLONG            WSAENAMETOOLONG
#define EHOSTDOWN               WSAEHOSTDOWN
#define EHOSTUNREACH            WSAEHOSTUNREACH
// #define ENOTEMPTY               WSAENOTEMPTY
#define EPROCLIM                WSAEPROCLIM
#define EUSERS                  WSAEUSERS
#define EDQUOT                  WSAEDQUOT
#define ESTALE                  WSAESTALE
#define EREMOTE                 WSAEREMOTE

// NOTE: these are not errno constants in UNIX!
#define HOST_NOT_FOUND          WSAHOST_NOT_FOUND
#define TRY_AGAIN               WSATRY_AGAIN
#define NO_RECOVERY             WSANO_RECOVERY
#define NO_DATA                 WSANO_DATA

#endif


// shutdown() constants

#if defined(SD_RECEIVE) && !defined(SHUT_RD)
#  define SHUT_RD       SD_RECEIVE
#  define SHUT_WR       SD_SEND
#  define SHUT_RDWR     SD_BOTH
#endif

/**********************************************************************
 * critical error processing
 **********************************************************************/
#define CRIT_FIRST 0xC0000

typedef void (*_pcrithandler)(int code, const char* msg);

_pcrithandler getcrithandler();
_pcrithandler setcrithandler(_pcrithandler newh);

void fatal(int code, const char* msg);


/**********************************************************************
 * NetException
 **********************************************************************/
class NetException
{
public:
    int code;
    const char* msg;
    NetException(int icode, const char* imsg) { code=icode; msg=imsg; }
    ~NetException(){};
    int getCode()          { return code; }
    const char* getMessage()    { return msg; }
};


//--------------------------------------------------------------------//
// IP address class and DNS utilities 
//--------------------------------------------------------------------//
//
// IP address
//
struct ipaddress
{
    union
    {
        uchar   data[4];
        ulong   ldata;
    };
    ipaddress()                             {}
    ipaddress(ulong a)                      { ldata = a; }
    ipaddress(int a, int b, int c, int d);
    ipaddress& operator= (ulong a)          { ldata = a; return *this; }
    uchar& operator [] (int i)              { return data[i]; }
    operator ulong() const                  { return ldata; }
};

/**********************************************************************
 * ippeerinfo
 * IP peer info: host name, IP and the port name
 * used internally in TcpSocket and UdpSocket
 **********************************************************************/
class ippeerinfo
{
protected:
    ipaddress ip;           // target IP
    char host[128];         // target host name; either IP or hostname must be specified
    int       port;         // target port number
    void      notfound();   // throws a (estream*) exception

    friend bool psockname(int, ippeerinfo&);
public:
    ippeerinfo();
    ippeerinfo(ipaddress iip, int iport);
    ippeerinfo(const char* ihost, int iport);
    ippeerinfo(ipaddress iip, const char* ihost, int iport);

    ipaddress getAddress(); // resolves the host name if necessary (only once)
    void getAddress(char* strAddr);
    const char* getHost();  // performs reverse-lookup if necessary (only once)
    int       getPort();

    void      clear();
    void toString(char *str, bool showport);
};

/**********************************************************************
 * ipbindinfo
 * common internal interfaces for TcpServerSocket and UdpServerSocket
 **********************************************************************/
class ipbindinfo: public ippeerinfo
{
public:
    int handle;

    ipbindinfo(ipaddress iip, const char* ihost, int iport);
    virtual ~ipbindinfo();
};

extern ipaddress ipnone;
extern ipaddress ipany;
extern ipaddress ipbcast;


void addrToStr(char *str, ipaddress ip );
ipaddress  getHostAddrByName(const char* name);
const char* getHostNameByAddr(ipaddress ip);
const char* getHostNameByName(const char* name);


// internal utilities
int usockerrno();
const char* usockerrmsg(int code);
bool psockwait(int handle, int timeout);
bool psockname(int handle, ippeerinfo&);


//--------------------------------------------------------------------//
// TCP socket classes 
//--------------------------------------------------------------------//
// status codes: compatible with WinInet API
// additional status codes are defined in pinet.h for ipsocket
const int IO_CREATED    = 1;
const int IO_OPENING    = 5;
const int IO_OPENED     = 35;
const int IO_READING    = 37;
const int IO_WRITING    = 38;
const int IO_EOF        = 45;
const int IO_CLOSING    = 250;
const int IO_CLOSED     = 253;

// additional IO status codes
const int IO_RESOLVING  = 10;
const int IO_RESOLVED   = 11;
const int IO_CONNECTING = 20;
const int IO_CONNECTED  = 21;


/**********************************************************************
 * TcpSocket
 **********************************************************************/
class TcpSocket: public ippeerinfo
{
    friend class TcpServerSocket;

protected:
    int svsocket;   // server socket descriptor, used internally by TcpServerSocket
    void closehandle();

private:
    int nonBlocking;    
public:
    //------------------------------
    // 추가 코드.
    int     handle;
    bool    connected;
    bool    cancelled;
    int     stmerrno;       // UNIX-compatible error numbers, see comments in piobase.cxx
    int     status;         // stream status code, see IO_xxx constants above

    void    open();
    void    open(int port);
    void    open(const char *localAddr, int localPort);
    void    close();
    //------------------------------

    TcpSocket();
    TcpSocket(ipaddress remoteAddr, int remotePort);
    TcpSocket(const char* remoteAddr, int remotePort);
    virtual ~TcpSocket();

    bool      waitfor(int timeout);
    ipaddress getLocalAddress();
    int       getLocalPort();
    void      set_ip(ipaddress);
    void      set_host(const char*);
    void      set_port(int);

    unsigned long available();
    //#ifdef WIN32
    virtual int recv(char* buf, int len);
    virtual int recv(char* buf, int off, int len);
    virtual int send(const char* buf, int len);
    virtual int send(const char* buf, int off, int len);
	//#endif

    bool setNonBlocking(int mode);
    bool setTcpNoDelay(int mode);
    bool setSoTimeout(int miliseconds);
    bool setReceiveBufferSize(int size);
    bool setSendBufferSize(int size);
    bool setSoLinger(int value);
};

#define MAX_BINDADDR_SIZE 2
/**********************************************************************
 * ServerSocket
 **********************************************************************/
class ServerSocket
{
protected:
    int     socktype;
    bool    active;
    //std::vector<ipbindinfo *> addrlist;
    int addrlistSize;
    ipbindinfo* addrlist[MAX_BINDADDR_SIZE];

    void error(ippeerinfo& peer, int code, const char* defmsg);
    bool dopoll(int* i, int timeout);
    void setupfds(void* set, int i);

    virtual void close();
    virtual void dobind(ipbindinfo*) = 0;

public:
    ServerSocket(int isocktype);
    virtual ~ServerSocket();

    virtual void open();
    void bind(ipaddress ip, int port);
    void bindall(int port);

    //int get_addrcount() { return length(addrlist); }
    const ipbindinfo& get_addr(int i) { return *(ipbindinfo*)addrlist[i]; }
    void clear();
};


/**********************************************************************
 * TcpServerSocket
 **********************************************************************/
class TcpServerSocket: public ServerSocket
{
protected:
    virtual void dobind(ipbindinfo*);

public:
    TcpServerSocket();
    virtual ~TcpServerSocket();

    bool poll(int i = -1, int timeout = 0);
    bool serve(TcpSocket& s, int i = -1, int timeout = -1);
    //TcpSocket* accept( int addrIndex);
    bool accept( TcpSocket *s);
    bool accept( TcpSocket *s, int addrIndex);
};


//--------------------------------------------------------------------//
// UDP socket classes
//--------------------------------------------------------------------//

/**********************************************************************
 * UdpSocket
 **********************************************************************/
class UdpSocket: public ippeerinfo
{
private:
    int nonBlocking;

protected:
    //void error(int code, const char* msg);
public:
    int handle;

    UdpSocket();
    UdpSocket(ipaddress ip, int port);
    UdpSocket(const char* host, int port);
    virtual ~UdpSocket();

    bool isOpen();
	void open();
    void open(int port);
    void open(const char *localAddr, int localPort);
    void close();
    
    void setRemoteAddr(ipaddress iip);
    void setRemoteHost(const char*);
    void setRemotePort(int);
    ipaddress getLocalAddress();
    int getLocalPort();

    bool waitfor(int timeout);
    unsigned long available();

    int  recv(char* buf, int len );
    int  recv(char* buf, int len, ipaddress *remoteAddr, int *remotePort);
    int  recv(char* buf, int len, sockaddr_in* sa );
    
    int send(const char* buf, int len);
    int sendto(const char* buf, int len, const char* remoteAddr, int remotePort);
    int sendto(const char* buf, int len, ipaddress remoteAddr, int remotePort);
    int sendto(const char* buf, int len, sockaddr_in* sa);
    	
    bool setNonBlocking(int mode);
    bool setSoTimeout(int miliseconds);
    bool setReceiveBufferSize(int size);
    bool setSendBufferSize(int size);
};


/**********************************************************************
 * UdpServerSocket
 **********************************************************************/
class UdpServerSocket: public ServerSocket, public ippeerinfo
{
protected:
    int handle;

    virtual void close();
    virtual void dobind(ipbindinfo*);

public:
    UdpServerSocket();
    virtual ~UdpServerSocket();

    bool poll(int i = -1, int timeout = 0);
    int  receive(char* buf, int count);
    void send(const char* buf, int count);
    void sendto(const char* buf, int count, ipaddress ip, int port);
    bool setSoTimeout(int miliseconds);
    bool setReceiveBufferSize(int size);
    bool setSendBufferSize(int size);

};

/***********************************************************************/
/*
#ifdef _MSC_VER
#pragma pack(pop)
#endif
*/
#endif // __SZ_SOCK_H__

