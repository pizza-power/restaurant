#include "fns.h"

// Order Constructor

Order::Order(char new_order_type, std::string new_orderNumber, Customer new_this_customer)
        :order_type(new_order_type), orderNumber(new_orderNumber), this_customer(new_this_customer){}

bool Order::add_items(Order& this_order, std::vector<std::tuple<int, std::string, int>> menu) {
    /** probably need to add an option to add to an already existing order
    // could pass the existing order in as a reference, and then edit it
    // for now we won't do that
    // this function should probabbly not be a bool, it just doesn't seem right to be true or false
    // maybe add code to main so this function becomes void
    **/

    std::cout << "Press the number of the item that you would like to add to your order, or press "
                 "'X' to cancel your order, press 'M' to see the menu, or press 'D' when done. "<< std::endl;
    char pressed_key;
    std::cout << "Your choice: ";
    std::cin >> pressed_key;

    if (pressed_key == 'X') {
        // need an order destructor
        quit_order();
        return false;
    } else if (pressed_key == 'M') {
        print_menu(menu);
        return true;
    } else if (pressed_key == 'D') {
        return false;
    } else {
        int item_number = pressed_key - '0';
        this_order.order_items.push_back(menu[item_number - 1]);

        return true;

    }
}

void Order::remove_item() {
    std::cout << "Please press the number of the item you want to remove: ";
    int pressed_key;
    std::cin >> pressed_key;

    // write routing to find this item in the order, count how many times it occurs and ask to remove how many
    // error check to non real item numbers etc


}

// print the order
void Order::print_order(Customer customer) {

    std::cout << "\nOrder Number: " << orderNumber << "\nC/O or Delivery: " << order_type
              << "\nCustomer Name: " << customer.first_name + " " + customer.last_name <<"\n\nCustomer Address: " <<
              customer.street_address + " " + customer.city + ", " + customer.state << std::endl;


    // update to use empty() instead of code below it, and a range based for loop
    if (order_items.empty()) {
        std::cout << "\nNO ITEMS IN ORDER" << std::endl;
    } else {
        std::cout << "\n\nITEM\tPRICE" << std::endl;
        for (auto i : order_items) {
            std::cout << std::get<1>(i) << "\t" << std::get<2>(i)<< std::endl;
        }

    }
    std::cout << "\n\n" << std::endl;
}



//print the menu
void print_menu(const std::vector<std::tuple<int, std::string, int>>& m) {
    for (auto i : m) {
        std::cout << std::get<0>(i) << " " <<  std::get<1>(i) << " " << std::get<2>(i) << std::endl;
    }
    std::cout << "\n\n" << std::endl;
}

// quit order function
void quit_order() {
    std::cout << "Thank you! Have a nice Day!\n\n\n\n" << std::endl;
}




// customer class and member functions

Customer::Customer(std::string new_first_name, std::string new_last_name, std::string new_street_address,
                   std::string new_city, std::string new_state)
                   : first_name(new_first_name), last_name(new_last_name), street_address(new_street_address),
                   city(new_city), state(new_state) {}


void Customer::print_customer(const Customer& this_customer) {

    std::cout << first_name + " " +  last_name + "\n" + street_address + " " + city + ", " + state << std::endl;

}


// interactive function to build a customer
Customer customer_creator() {

    /** the menu and the menu printing needs to be moved elsewhere
     * the menu can go it it's own file, and then another function
     * can be used to print the menu
     */


    char pressed_key;

    std::string first_name;
    std::string last_name;
    std::string street_address;
    std::string city;
    std::string state;

    // make the menu, move this to it's own file
    std::vector<std::tuple<int, std::string, int>> menu;
    menu.push_back(std::make_tuple(1, "pizza", 999));
    menu.push_back(std::make_tuple(2, "hotdog", 299));
    menu.push_back(std::make_tuple(3, "drink", 199));

    std::cout << "\nPlease enter your first and last name.\n" << std::endl;
    std::cout << "First Name: ";
    std::cin >> first_name;
    std::cout << "\nLast Name: ";
    std::cin >> last_name;
    std::cout << std::endl;

    std::cout << "\nPlease enter your street address: ";
    std::cin.ignore();
    getline(std::cin, street_address);

    std::cout << "\nPlease enter you city: ";

    getline(std::cin, city);

    std::cout << "\nPlease enter your state in two letter abbreviation form, please: ";
    std::cin >> state;
    std::cout << "\n" << std::endl;

    // create a customer object
    Customer thiscustomer(first_name, last_name, street_address, city, state);

    // See the menu
    std::cout << "Welcome " << first_name << "! ";
    std::cout << "Press 'M' for the menu, or 'X' to quit: ";

    std::cin >> pressed_key;

    if (pressed_key == 'M') {
        std::cout << "\n\nPrinting menu... \n" << std::endl; // move this to the function
        print_menu(menu);
    } else if (pressed_key == 'X') {
        quit_order();
        return thiscustomer;
    }
    return thiscustomer;

}