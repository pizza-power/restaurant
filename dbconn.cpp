#ifndef DBCONN_H
#define DBCONN_H

#include <iostream>

#include "mysqlx/xdevapi.h"

// class to deal with database connection

#endif




//#include <iostream>
//#include <vector>
//#include "mysqlx/xdevapi.h"
//#include "include/mysqlx/devapi/result.h"
//
//int main() {
//
//    mysqlx::Session mySession(mysqlx::SessionOption::HOST, "localhost",
//                              mysqlx::SessionOption::PORT, 33060,
//                              mysqlx::SessionOption::USER, "root",
//                              mysqlx::SessionOption::PWD, "");
//    mysqlx::Schema db = mySession.getSchema("restaurant");
//    mysqlx::Table customers = db.getTable("customers");
//
//    mysqlx::RowResult res = customers.select("customer_id", "first_name", "last_name", "street_address",
//            "city", "state", "username", "password", "join_date_time")
//            .where("customer_id < :customer_id")
//            .bind("customer_id", 20).execute();
//
////    mysqlx::Row record = res.fetchOne();
//
////    for (int i = 0; i <= 8; ++i) {
////        std::cout << record[i] << std::endl;
////    }
//
//    mysqlx::Row row;
//
//    while ((row = res.fetchOne())) {
//        std::cout << "Customer ID: " << row[0] << std::endl;
//        std::cout << "First Name: " << row[1] << std::endl;
//        std::cout << "Last Name: " << row[2] << std::endl;
//        std::cout << "Street Address: " << row[3] << std::endl;
//        std::cout << "City: " << row[4] << std::endl;
//        std::cout << "State: " << row[5] << std::endl;
//        std::cout << "Username: " << row[6] << std::endl;
//        std::cout << "Password: " << row[7] << std::endl;
//        std::cout << "Join Date/Time: " << row[8] << std::endl << std::endl;
//    }
//    return 0;
//};