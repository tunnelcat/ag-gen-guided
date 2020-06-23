#ifdef REDIS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cpp_redis/cpp_redis>

#include "ag_gen/quality.h"
#include "ag_gen/topology.h"
#include "redis_manager.h"

RedisManager::RedisManager(std::string host, int port,
                           std::vector<std::pair<std::string, std::string>> &sm) {
    client.connect(host, port);

    for (auto item : sm) {
        auto r = client.script_load(item.second);
        commit();
        script_map[item.first] = r.get().as_string();
    }
}

void RedisManager::insert_factbase(std::string &hash, int id) {
    client.sadd("factbases", std::vector<std::string>{hash});
    client.hset("idmap:" + hash, "id", std::to_string(id));
}

int RedisManager::get_factbase_id(std::string &hash) {
    auto r = client.hget("idmap:" + hash, "id");
    commit();
    return std::stoi(r.get().as_string());
}

bool RedisManager::check_factbase_exists(std::string &hash) {
    auto r = client.sismember("factbases", hash);
    commit();
    return r.get().as_integer() == 1;
}

#endif
