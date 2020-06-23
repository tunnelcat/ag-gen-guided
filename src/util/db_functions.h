
#ifndef DB_FUNCTIONS_H
#define DB_FUNCTIONS_H

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

#include "keyvalue.h"
#include "db.h"

#include "ag_gen/ag_gen.h"
#include "ag_gen/exploit.h"
#include "ag_gen/edge.h"
#include "ag_gen/quality.h"
#include "ag_gen/topology.h"
#include "ag_gen/asset.h"
#include "ag_gen/factbase.h"

using GraphInfo = std::pair<std::vector<int>, std::vector<std::array<int, 4>>>;

struct CustomDBException : public std::exception
{

    const char * what () const throw ()
    {
        return "DB Exception";
    }

};

void init_db(std::string connect_str);

void import_models(std::string nm, std::string xp);

GraphInfo fetch_graph_info();

void delete_edges(std::vector<int> edge_ids);

int get_max_factbase_id();

std::vector<std::vector<std::pair<size_t, std::string>>> fetch_all_factbase_items();
std::vector<std::pair<size_t, std::string>> fetch_one_factbase_items(int index);

std::vector<std::string> fetch_keyvalues();
Keyvalue fetch_kv();
std::vector<std::string> fetch_unique_values();
std::vector<std::string> fetch_quality_attributes();
std::vector<std::string> fetch_quality_values();
std::vector<std::string> fetch_topology_attributes();
std::vector<std::string> fetch_topology_values();

std::unordered_map<
    int, std::tuple<std::vector<ParameterizedQuality>, std::vector<ParameterizedTopology>>>
               fetch_exploit_preconds();
std::unordered_map<
    int, std::tuple<std::vector<PostconditionQ>, std::vector<PostconditionT>>>
               fetch_exploit_postconds();

std::vector<Exploit> fetch_all_exploits();
std::unordered_map<int, std::vector<Quality>> fetch_asset_qualities(Keyvalue &facts);
std::vector<Asset> fetch_all_assets(Keyvalue &facts);
std::vector<Quality> fetch_all_qualities(Keyvalue &facts);
std::vector<Topology> fetch_all_topologies(Keyvalue &facts);
Keyvalue fetch_facts();

inline std::string to_query(Edge edge) { return edge.get_query(); }

// void save_ag_to_db(std::vector<FactbaseItems> &factbase_items,
//                    std::vector<Factbase> &factbases, std::vector<Edge> &edges,
//                    Keyvalue &factlist);

void save_ag_to_db(AGGenInstance &instance, bool save_keyvalue);

// void test_create();

#endif
