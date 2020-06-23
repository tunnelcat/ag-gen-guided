// factbase.cpp implements the Factbase class which contains the known facts
// that are completely true in a particular Network State

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

#include <boost/functional/hash.hpp>

#include "ag_gen.h"

using namespace std;

int Factbase::current_id = 0;

/**
 * @brief Constructor for Factbase
 *
 * @param q A vector of Qualities
 * @param t A vector of Topologies
 */
Factbase::Factbase(std::vector<Quality> q, std::vector<Topology> t)
    : qualities(q), topologies(t) {
    id = 0;
}

/**
 * @brief Increments the current ID.
 */
void Factbase::set_id() {
    id = current_id++;
}

/**
 * @return The current Factbase ID.
 */
int Factbase::get_id() const { return id; }

std::tuple<std::vector<Quality>, std::vector<Topology>> Factbase::get_facts_tuple() const {
    return std::make_tuple(qualities, topologies);
}

/**
 * @brief Searches for a Quality in the Factbase.
 * @details Returns true if the Quality is found and false otherwise.
 *
 * @param q Quality for which to search.
 */
bool Factbase::find_quality(Quality &q) const {
    return std::find(qualities.begin(), qualities.end(), q) != qualities.end();
}

std::vector<Quality>::iterator Factbase::get_quality(Quality &q) {
    return std::find(qualities.begin(), qualities.end(), q);
}

/**
 * @brief Searches for a Topology in the Factbase.
 * @details Returns true if the Topology is found and false otherwise.
 *
 * @param t Topology for which to search.
 */
bool Factbase::find_topology(Topology &t) const {
    return std::find(topologies.begin(), topologies.end(), t) != topologies.end();
}

std::vector<Topology>::iterator Factbase::get_topology(Topology &t) {
    return std::find(topologies.begin(), topologies.end(), t);
}

/**
 * @brief Adds a given Quality to the factbase's vector of Qualities.
 *
 * @param q Quality to add
 */
void Factbase::add_quality(Quality &q) {
    qualities.push_back(q);
}

void Factbase::delete_quality(Quality &q) {
    auto qual = get_quality(q);
    if(qual != qualities.end()) {
        qualities.erase(qual);
    }
}

/**
 * @brief Adds a given Topology to the factbase's vector of Topologies.
 *
 * @param t Topology to add
 */
void Factbase::add_topology(Topology &t) {
    topologies.push_back(t);
}

void Factbase::delete_topology(Topology &t) {
    auto topo = get_topology(t);
    if(topo != topologies.end()) {
        topologies.erase(topo);
    }
}

/**
 * @brief Shamelessly copied from Boost::hash_combine
 */
// void combine(size_t *seed) {
//     *seed ^= std::hash<size_t>{}(seed) + 0x9e3779b97f4a7c15 + (seed << 6) +
//             (seed >> 2);
// }

/**
 * @brief Hashes the Factbase
 *
 * @param factlist The current Keyvalue
 * @return The hash of the Factbase
 */
size_t Factbase::hash(Keyvalue &factlist) const {
    //  size_t hash = 0xf848b64e; // Random seed value
    // size_t seed = 0x0c32a12fe19d2119;
    size_t seed = 0;

    std::set<size_t> factset_q;
    std::transform(qualities.begin(), qualities.end(), std::inserter(factset_q, factset_q.end()),
        [&](const Quality &q) -> size_t { return q.encode(factlist).enc;});
    std::for_each(factset_q.begin(), factset_q.end(),
        [&](size_t t) { boost::hash_combine(seed, t); });

    std::set<size_t> factset_t;
    std::transform(topologies.begin(), topologies.end(), std::inserter(factset_t, factset_t.end()),
        [&](const Topology &t) -> size_t { return t.encode(factlist).enc;});
    std::for_each(factset_t.begin(), factset_t.end(),
        [&](size_t t) { boost::hash_combine(seed, t); });

    return seed;
}

/**
 * @brief Prints out the Factbase information.
 */
void Factbase::print() const {
    cout << "ID: " << id << endl;
//        cout << "HASH: " << hash() << endl;
    cout << "Qualities: " << qualities.size() << endl;
    cout << "Topologies: " << topologies.size() << endl << endl;
    for (auto &qual : qualities) {
        qual.print();
    }
    for (auto &topo : topologies) {
        topo.print();
    }
}
