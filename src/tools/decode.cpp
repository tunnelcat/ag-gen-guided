
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include <getopt.h>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "ag_gen/asset.h"
#include "ag_gen/quality.h"
#include "ag_gen/topology.h"

#include "util/db_functions.h"
#include "util/keyvalue.h"

void print_usage() {
    std::cout << "Usage: fbitems [OPTIONS...]" << std::endl
              << "\t-h\tShows this help menu." << std::endl
              << "\t-i\tindex. If no index provided, all items will be found." << std::endl
              << "\t-c\tconfig section. If none is provided, default will be used." << std::endl;
}

std::string find_one_impl(std::vector<std::string> &str_vector, int index) {
    std::vector<std::pair<size_t, std::string>> fbitems;

    std::ostringstream output;

    std::vector<EncodedQuality> cmpq_base;
    auto cmpq = [](EncodedQuality &a, EncodedQuality &b) { return a.dec.asset_id < b.dec.asset_id; };
    std::priority_queue<EncodedQuality, std::vector<EncodedQuality>, decltype(cmpq)> pqq(cmpq, cmpq_base);

    std::vector<EncodedTopology> cmpt_base;
    auto cmpt = [](EncodedTopology &a, EncodedTopology &b) { return a.dec.from_asset < b.dec.from_asset; };
    std::priority_queue<EncodedTopology, std::vector<EncodedTopology>, decltype(cmpt)> pqt(cmpt, cmpt_base);

    try {
        fbitems = fetch_one_factbase_items(index);
    } catch (CustomDBException &ex) {
        std::cout << index << " not in DB" << std::endl;
        exit(1);
    }

    for(auto &item : fbitems) {
        std::string type = item.second;
        if (type == "quality") {
            EncodedQuality eq;
            eq.enc = item.first;
            pqq.emplace(eq);
        } else {
            EncodedTopology et;
            et.enc = item.first;
            pqt.emplace(et);
        }
    }

    Keyvalue kv = fetch_kv();
    std::vector<Asset> assets = fetch_all_assets(kv);
    output << index << ":";

    while(!pqq.empty()) {
        EncodedQuality qual = pqq.top();
        pqq.pop();

        output << "\tquality:";

        Asset asset = assets[qual.dec.asset_id];
        output << asset.get_name() << ",";

        std::string attr = str_vector[qual.dec.attr];
        std::string val = str_vector[qual.dec.val];

        output << attr << "=" << val;
        output << " : " << qual.enc << "\n";

    }

    while(!pqt.empty()) {
        EncodedTopology topo = pqt.top();
        pqt.pop();

        output << "\ttopology:";

        Asset from_asset = assets[topo.dec.from_asset];
        Asset to_asset = assets[topo.dec.to_asset];

        output << from_asset.get_name() << "->" << to_asset.get_name() << ",";

        std::string prop = str_vector[topo.dec.property];
        std::string val = str_vector[topo.dec.value];

        output << prop << "=" << val;
        output << " : " << topo.enc << "\n";
    }

    output << std::endl;

    return output.str();
}

void find_one(std::vector<std::string> &str_vector, int index) {
    std::ofstream output("file.txt");
    output << find_one_impl(str_vector, index);
}

void find_all(std::vector<std::string> &str_vector) {
    int max = get_max_factbase_id();

    std::ofstream output("file.txt");

    for(auto i=0; i<=max; ++i) {
        output << find_one_impl(str_vector, i);
    }

    output << std::endl;
    output.close();
}

int main(int argc, char *argv[]) {

    std::string opt_config;
    std::string opt_index;

    int opt;
    while ((opt = getopt(argc, argv, "hc:i:")) != -1) {
        switch (opt) {
        case 'c':
            opt_config = optarg;
            break;
        case 'i':
            opt_index = optarg;
            break;
        case 'h':
            print_usage();
            return 0;
        case '?':
            if (optopt == 'c')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            exit(EXIT_FAILURE);
        case ':':
            fprintf(stderr, "wtf\n");
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr, "Unknown option -%c.\n", optopt);
            print_usage();
            exit(EXIT_FAILURE);
        }
    }

    std::string config_section = (opt_config.empty()) ? "default" : opt_config;

    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("config.ini", pt);

    std::string host = pt.get<std::string>(config_section + ".host");
    std::string port = pt.get<std::string>(config_section + ".port");
    std::string dbName = pt.get<std::string>(config_section + ".db");
    std::string username = pt.get<std::string>(config_section + ".username");
    std::string password = pt.get<std::string>(config_section + ".password");

    std::cout << dbName << "\n";
    init_db("postgresql://" + username + "@" + host + ":" + port + "/" + dbName);

//    Keyvalue kv = fetch_facts();
//    std::vector<std::string> str_vector = kv.get_str_vector();

    std::vector<std::string> str_vector = fetch_keyvalues();

    if (opt_index.empty()) {
        find_all(str_vector);
    } else {
        try {
            auto index = boost::lexical_cast<int>(opt_index);
            find_one(str_vector, index);
        } catch (boost::bad_lexical_cast &e) {
            print_usage();
            return 2;
        }
    }

    // All done :)
    return 0;
}
