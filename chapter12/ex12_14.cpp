//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>
#include <string>

struct connection
{
    std::string ip;
    int port;
    connection(std::string i, int p) : ip(i), port(p) {}
};

struct destination
{
    std::string ip;
    int port;
    destination(std::string i, int p) : ip(i), port(p) {}
};

connection connect(destination* pDest) {
    std::shared_ptr<connection> pConn(new connection(pDest->ip, pDest->port));
    std::cout << "creating connection(" << pConn.use_count() << ")" << std::endl;
    return *pConn;
}

void disconnect(connection connect) {
    std::cout << "connection close(" << connect.ip << ":" << connect.port << ")" << std::endl;
}

void f(destination& d) {
    connection conn  = connect(&d);
    std::shared_ptr<connection> p(&conn, [] (connection* Pconn) {disconnect(*Pconn);});
    std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}

int main() {
    destination dest("220.181.111", 10086);
    f(dest);

    return 0;
}