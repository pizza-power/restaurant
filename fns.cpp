#include <iostream>
#include <string>
#include <vector>
#include <tuple>


#include "fns.h"

// quit order function
void quit_order() {
    std::cout << "Thank you! Have a nice Day!\n\n\n\n" << std::endl;
}

//intro routine, commences order

char intro_routine() {
    std::cout << "\n\nWelcome to Matt's Pizza Palace!\n\nPress 'Y' or order or 'X' to cancel: ";
    char order_verify;
    std::cin >> order_verify;

    if (order_verify == 'Y') {
        std::cout << "\nWill this be for Carryout 'C' or Delivery 'D'? ";
        char order_type;
        std::cin >> order_type;

        return order_type;

    } else {
        quit_order();
        return 'X';
    }
}

