#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cstring>
#include <iomanip>


#include "fns.h"

// quit order function
void quit_order() {
    std::cout << "Thank you! Have a nice Day!\n" << std::endl;
    std::cout << std::setfill ('x') << std::setw (80) << std::endl;
    std::cout << "\n" << std::endl;
}

//intro routine, commences order
char intro_routine() {
    std::cout << "\n\nWelcome to Matt's Pizza Palace!\n\nPress 'Y' or order or 'X' to cancel: ";
    char order_verify;
    std::cin >> order_verify;
    order_verify = toupper(order_verify);

    if (order_verify == 'Y') {
        std::cout << "\nWill this be for Carryout 'C' or Delivery 'D'? ";
        char order_type;
        std::cin >> order_type;
        order_type = toupper( order_type );

        return order_type;

    } else if ( order_verify == 'X' || (order_verify == 'x')) {
        return 'x';
    } else {
        intro_routine();

    }

    return 'O';
}

