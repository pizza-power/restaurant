#include <iostream>
#include <vector>
#include <tuple>
#include <string>

#include "customer.h"
#include "fns.h"

// customer class and member functions

Customer::Customer(std::string new_phone_number, std::string new_first_name, std::string new_last_name, std::string new_street_address,
                   std::string new_city, std::string new_state, int new_zip_code, std::string new_username,
                   std::string new_password, mysqlx::Schema new_database)
        : phone_number(new_phone_number), first_name(new_first_name), last_name(new_last_name), street_address(new_street_address),
          city(new_city), state(new_state), zip_code(new_zip_code), username(new_username), password(new_password),
          database(new_database) {}

          // build the customer object
Customer customer_creator(mysqlx::Schema& database) {

    // this creates a customer entry in the mysql database and returns that customer's data

    std::cout << "\n Please enter a phone number: ";
    std::string phone_number;
    std::cin >> phone_number;
    std::cout << "\nlooking up phone number...\n" << std::endl;

    // if the customer already exists, we don't add it to the database
    if (customer_lookup(phone_number, database)) {

        mysqlx::Table customers = database.getTable("customers");
        mysqlx::Row row;
        mysqlx::RowResult customer_row = customers.select("customer_id", "phone_number", "first_name", "last_name",
                                                          "street_address", "city", "state", "zip_code").
                where("phone_number = :param").bind("param", phone_number).execute();

        row = customer_row.fetchOne();

        std::cout << "Customer ID: " << row[0] << std::endl;
        std::cout << "First Name: " << row[2] << std::endl;
        std::cout << "Last Name: " << row[3] << std::endl;
        std::cout << "Street Address: " << row[4] << std::endl;
        std::cout << "City: " << row[5] << std::endl;
        std::cout << "State: " << row[6] << std::endl;
        std::cout << "Zip: " << row[7] << std::endl;
        std::cout << "\n" << std::endl;

        // todo: figure out how to properly get zip from the db and then use it to make the customer object
        Customer customer
                (phone_number, mysqlx::string(row[2]), mysqlx::string(row[3]), mysqlx::string(row[4]),
                 mysqlx::string(row[5]), mysqlx::string(row[6]), 66666, "", "", database);

        return customer;


    } else {

        std::string first_name;
        std::string last_name;
        std::string street_address;
        std::string city;
        std::string state;
        int zip_code;
        std::string username = "";
        std::string password = "";

        std::cout << "\n" << std::endl;
        std::cout << "\nPlease enter your first and last name.\n" << std::endl;
        std::cout << "First Name: ";
        std::cin >> first_name;
        std::cout << "\nLast Name: ";
        std::cin >> last_name;
        std::cout << std::endl;

        std::cout << "Please enter your street address: ";
        std::cin.ignore();
        getline(std::cin, street_address);

        std::cout << "\nPlease enter your city: ";
        getline(std::cin, city);

        std::cout << "\nPlease enter your state in two letter abbreviation form: ";
        std::cin >> state;

        std::cout << "\nPlease enter your zip code: ";
        // need input sanitization for non ints
        std::cin >> zip_code;

        // add customer to the sql table
        mysqlx::Table customers = database.getTable("customers");

        // todo: figure out methods for obtaining customer_id and datetime
        mysqlx::TableInsert(customers)
                .values(0, 787 , phone_number, first_name, last_name, street_address, city, state, zip_code, username,
                        password, "2009-11-11 23:43:21").execute();

        // create a customer object
        Customer customer
                (phone_number, first_name, last_name, street_address, city, state,
                        zip_code, username, password, database);

        return customer;
    }
}

bool customer_lookup(std::string& phone_number, mysqlx::Schema& database) {
    // uses phone_number and database table customers to test if customer is already in the sytem
    mysqlx::Table customers = database.getTable("customers");
    mysqlx::RowResult customer_row = customers.select("customer_id", "phone_number", "first_name", "last_name",
                                                      "street_address", "city", "state", "zip_code").
            where("phone_number = :param").bind("param", phone_number).execute();

    if (customer_row.count() > 0) {
        mysqlx::Row row;
        row = customer_row.fetchOne();
        std::cout << "customer id = " << row[0] << " phone number " << row[1] << std::endl;
        return true;
    } else {
        std::cout << "Customer not found! " << std::endl;
        return false;
    }
}

// todo: implement
void Customer::print_customer() {
    // select what field to search or enter email or something? email may be best bet because it wouldn't change?
}
void Customer::change_customer_info() {}
void Customer::customer_order_history() {}

