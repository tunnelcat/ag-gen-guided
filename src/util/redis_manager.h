#ifdef REDIS

#ifndef REDIS_MANAGER_H
#define REDIS_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cpp_redis/cpp_redis>

#include "ag_gen/quality.h"

class RedisManager {
    cpp_redis::client client;

    std::unordered_map<std::string, std::string> script_map;

    // std::string insert_collision_factbase(std::string &hash, int id);

  public:
    RedisManager() {}
    RedisManager(std::string host, int port, std::vector<std::pair<std::string, std::string>> &sm);

    // void insert_facts(std::string &hash, std::vector<Quality> &quals, std::vector<Topology> &topos);
    void insert_factbase(std::string &hash, int id);

    void handle_collision(std::string &hash, int id, std::vector<Quality> &quals, std::vector<Topology> &topos);

    // int get_factbase_id(std::string &hash, int ci);

    int get_factbase_id(std::string &hash);

    // int get_collision_count(std::string &hash);

    // bool check_facts(std::string &hash, const std::vector<Quality> &quals, const std::vector<Topology> &topos);
    bool check_factbase_exists(std::string &hash);

    // bool check_collision(std::string &hash);

    inline void commit() { client.sync_commit(); }

    inline void clear() { client.flushall(); commit(); }

};

#endif
#endif
