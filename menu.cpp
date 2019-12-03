#include "menu.h"

Menu::Menu(mysqlx::Schema new_database)
    : database(new_database) {}

//void Menu::print_menu(const std::vector<std::tuple<int, std::string, double>>& m) {

void Menu::print_menu() {

    for (auto i : this->menu_items()) {
        std::cout << "Item Number " << " Item " << " Price " << std::endl;
        std::cout << std::get<0>(i) << ")\t" <<  std::get<1>(i) << "\t " << std::get<2>(i) << std::endl;

    }
    std::cout << std::endl;

}
std::vector<std::tuple<int, std::string, double>> Menu::menu_items() {

    std::vector<std::tuple<int, std::string, double>> items;
    mysqlx::Table menu = this->database.getTable("menu");
    mysqlx::RowResult res = menu.select("item_number", "item_name", "item_price").execute();
    mysqlx::Row row;

    while((row = res.fetchOne())) {
        items.emplace_back(std::make_tuple(row[0], row[1], row[2]));
    }

    return items;
}