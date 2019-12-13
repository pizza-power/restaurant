#include <iostream>
#include <string>
#include <iomanip>

// quit order function
void quit_order() {
    std::cout << "Thank you! Have a nice Day!\n" << std::endl;
    std::cout << std::setfill ('x') << std::setw (80) << std::endl;
    std::cout << "\n" << std::endl;
}

//intro routine, commences order
bool intro_routine() {
    std::cout << "\n\nWelcome to Matt's Pizza Palace!\n\nPress 'Y' or order or 'X' to cancel: ";
    char order_verify;
    std::cin >> order_verify;
    order_verify = toupper(order_verify);

    if (order_verify == 'Y') {
        return true;
    } else if ( order_verify == 'X' || (order_verify == 'x')) {
        return false;
    } else {
        intro_routine();
    }
    return false;
}

