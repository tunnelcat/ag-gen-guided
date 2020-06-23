//
// Created by Kyle Cook on 6/26/17.
//

#include <algorithm>
#include <unordered_set>

#include "network_state.h"

/**
 * @brief Normal Constructor for NetworkState
 * @details Creates a Factbase for a given Network
 *          and sets this as its parent.
 *
 * @param q A vector of Qualities
 * @param t A vector of Topologies
 */
NetworkState::NetworkState(std::vector<Quality> q, std::vector<Topology> t)
    : factbase(Factbase(std::move(q), std::move(t))) {}

/**
 * @brief Copy Constructor for NetworkState
 * @details Creates a new Factbase and sets Network
 *          based on an incoming NetworkState
 *
 * @param ns The NetworkState from which to copy
 */
NetworkState::NetworkState(const NetworkState &ns) = default;

/**
 * @brief Sets the ID of the Factbase
 */
void NetworkState::set_id() { factbase.set_id(); }

/**
 * @return The ID of the NetworkState
 */
int NetworkState::get_id() { return factbase.get_id(); }

/**
 * @return The Factbase for the NetworkState
 */
const Factbase &NetworkState::get_factbase() const { return factbase; }

/**
 * @brief Returns the hash of the Factbase
 *
 * @param factlist The current Keyvalue
 * @return The hash of the Factbase
 */
size_t NetworkState::get_hash(Keyvalue &factlist) const {
    return factbase.hash(factlist);
}

/**
 * @brief Adds all unique Quality elements of a vector to the Factbase
 *
 * @param q A vector of Qualities
 */
void NetworkState::add_qualities(std::vector<Quality> q) {
    // For each quality, check if it already exists in the factbase. If it does
    // not already exist, we add it.
    for (auto &qual : q) {
        add_quality(qual);
    }
}

/**
 * @brief Adds all unique Topology elements of a vector to the Factbase
 *
 * @param t A vector of Topologies
 */
void NetworkState::add_topologies(std::vector<Topology> t) {
    // For each topology, check if it already exists in the factbase. If it does
    // not already exist, we add it.
    for (auto &topo : t) {
        add_topology(topo);
    }
}

void NetworkState::add_quality(Quality &q) {
    if (!factbase.find_quality(q)) {
        factbase.add_quality(q);
    }
}

void NetworkState::add_topology(Topology &t) {
    if (!factbase.find_topology(t)) {
        factbase.add_topology(t);
    }
}

void NetworkState::update_quality(Quality &q) {
    auto asset_id = q.get_asset_id();
    auto attr = q.get_name();
    auto val = q.get_value();

    for(auto &qual : factbase.qualities) {
        if(qual.get_asset_id() == asset_id &&
            qual.get_name() == attr) {
            qual.set_value(val);
        }
    }
}

void NetworkState::update_topology(Topology &t) {
    auto from_asset = t.get_from_asset_id();
    auto to_asset = t.get_to_asset_id();
    auto attr = t.get_property();
    auto val = t.get_value();

    for(auto &topo : factbase.topologies) {
        if(topo.get_from_asset_id() == from_asset &&
            topo.get_to_asset_id() == to_asset &&
            topo.get_property() == attr) {
            topo.set_value(val);
        }
    }
}

void NetworkState::delete_quality(Quality &q) {
    auto qual = factbase.get_quality(q);
    if(qual != factbase.qualities.end()) {
        factbase.qualities.erase(qual);
    }
}

void NetworkState::delete_topology(Topology &t) {
    auto topo = factbase.get_topology(t);
    if(topo != factbase.topologies.end()) {
        factbase.topologies.erase(topo);
    }
}

// int NetworkState::compare(std::string &hash, RedisManager* rman) const {
//     if (!rman->check_collision(hash)) {
//         if (!rman->check_facts(hash, factbase.qualities, factbase.topologies))
//             return -1;
//         return 0;
//     }

//     if (rman->check_facts(hash, factbase.qualities, factbase.topologies))
//         return 0;

//     int amt = rman->get_collision_count(hash);

//     for (int i = 0; i <= amt; ++i) {
//         std::string new_string = hash + "_" + std::to_string(i);
//         if (!rman->check_facts(new_string, factbase.qualities, factbase.topologies))
//             continue;

//         return i;
//     }

//     return -1;
//     // if (!rman->check_collision(hash)) {
//     //     if (!rman->check_qualities(hash, factbase.qualities))
//     //         return -1;

//     //     if (!rman->check_topologies(hash, factbase.topologies))
//     //         return -1;

//     //     return 0;
//     // }

//     // if (rman->check_qualities(hash, factbase.qualities) && rman->check_topologies(hash, factbase.topologies))
//     //     return 0;

//     // int amt = rman->get_collision_count(hash);

//     // for (int i = 1; i <= amt; ++i) {
//     //     std::string new_string = hash + "_" + std::to_string(i);
//     //     if (!rman->check_qualities(new_string, factbase.qualities))
//     //         continue;

//     //     if (!rman->check_topologies(new_string, factbase.topologies))
//     //         continue;

//     //     return i;
//     // }

//     // return -1;
// }

// bool NetworkState::operator==(const Factbase &rhs) const {
//     auto right_tuple = rhs.get_facts_tuple();
//     auto rq = std::get<0>(right_tuple);
//     auto rt = std::get<1>(right_tuple);

//     auto left_tuple = factbase.get_facts_tuple();
//     auto lq = std::get<0>(left_tuple);
//     auto lt = std::get<1>(left_tuple);

//     // Right quality set
//     std::unordered_set<size_t> rqs;
//     std::for_each(rq.begin(), rq.end(), [&rqs](Quality q){rqs.insert(q.get_encoding());});

//     // Right topology set
//     std::unordered_set<size_t> rts;
//     std::for_each(rt.begin(), rt.end(), [&rts](Topology t){rts.insert(t.get_encoding());});

//     for (auto q : lq) {
//         if (rqs.find(q.get_encoding()) == rqs.end())
//             return false;
//     }

//     for (auto t : lt) {
//         if (rts.find(t.get_encoding()) == rts.end())
//             return false;
//     }

//     return true;
// }
