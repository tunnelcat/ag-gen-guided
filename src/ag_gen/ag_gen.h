#ifndef AG_GEN_HPP
#define AG_GEN_HPP

#include <deque>
#include <list>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <chrono>

#include "asset.h"
#include "assetgroup.h"
#include "edge.h"
#include "exploit.h"
#include "factbase.h"
#include "network_state.h"

#include "util/keyvalue.h"

#ifdef REDIS
#include "util/redis_manager.h"
#endif

using FactbaseItems =
    std::tuple<std::tuple<std::vector<Quality>, std::vector<Topology>>, int>;

typedef enum OPERATION_T {
    EQ_T,
    GEQ_T,
    LEQ_T,
    GT_T,
    LT_T
} OPERATION_T;

struct AGGenInstance {
    std::string opt_network;
    std::vector<Asset> assets;  //init
    std::vector<Factbase> factbases;
    std::vector<Quality> initial_qualities; //init
    std::vector<Topology> initial_topologies; //init
    std::vector<FactbaseItems> factbase_items;
    std::vector<Exploit> exploits; //init
    std::vector<Edge> edges;
    Keyvalue facts; //init

    std::chrono::duration<double> elapsed_seconds;
};

/** AGGen class
 * @brief Generate attack graph
 * @details Main generator class that stores state for the entire graph
 * generation process.
 */
class AGGen {
    AGGenInstance instance;
    std::deque<NetworkState> frontier;               //!< Unexplored states
    std::unordered_map<size_t, int> hash_map{};      //!< Map of hashes to Factbase ID

    bool use_redis;
#ifdef REDIS
    RedisManager *rman;
#endif

  public:
    explicit AGGen(AGGenInstance &_instance);

#ifdef REDIS
    AGGen(AGGenInstance &_instance, RedisManager &_rman);
#endif

    AGGenInstance &generate(bool batch_process, int batch_num, int numThrd, int initQSize);
};

#endif // AG_GEN_HPP
