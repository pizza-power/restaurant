#ifndef DBCONN_H
#define DBCONN_H

#include "mysqlx/xdevapi.h"

extern class mysqlx::Session mySession(mysqlx::SessionOption::HOST, "localhost",
                              mysqlx::SessionOption::PORT, 33060,
                              mysqlx::SessionOption::USER, "root",
                              mysqlx::SessionOption::PWD, "");
extern class mysqlx::Schema db = mySession.getSchema("restaurant");

// class to deal with database connection
//
//class Dbconn {
//public:
//    std::string host;
//    int port;
//    std::string user;
//    std::string pwd;
//    std::string schema;
//
//public:
//    Dbconn(std::string, int, std::string, std::string, std::string, );
//};

#endif