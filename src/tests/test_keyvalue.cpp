//
// Created by archlord on 12/6/16.
//

#include "asset.hpp"
#include "keyvalue.hpp"
#include "network.hpp"
#include "util_db.hpp"

using namespace std;

int main(int argc, char **argv) {
    string opt_network = "home";
    string conn_info = "postgresql://kyle@localhost/ag_gen_test";

    // unordered_map<string,int> assets;
    // fill_asset_table(conn_info, opt_network, assets);

    dbconnect(conn_info.c_str());
    try {
        auto network = Network::find(opt_network);
    } catch (const exception &e) {
        cout << e.what() << endl;
    }

    vector<shared_ptr<Asset>> asset_list;
    asset_list = Asset::fetch_all(opt_network);

    Keyvalue<Asset> meow(asset_list);

    cout << "Key Value Store:" << endl;
    for (const auto &n : meow.hash_table) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }

    cout << "Vector: " << endl;
    int idx = 0;
    for (const auto &thing : meow.str_vector) {
        std::cout << "Index: " << idx << ") " << thing << endl;
        idx++;
    }

    cout << "Testing function: get_id" << endl;
    cout << "Router has id: " << meow.get_id("router") << endl;
    cout << "Laptop has id: " << meow.get_id("laptop") << endl;
    cout << "Attacker has id: " << meow.get_id("attacker") << endl;
    cout << "ID 0: " << meow.get_name(0) << endl;
    cout << "ID 1: " << meow.get_name(1) << endl;
    cout << "ID 2: " << meow.get_name(2) << endl;
}
