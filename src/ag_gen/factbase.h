#ifndef FACTBASE_HPP
#define FACTBASE_HPP

#include <cstdint>
#include <functional>
#include <vector>

#include "quality.h"
#include "topology.h"

class NetworkState;

/** Factbase class
 * @brief Contains known facts in a NetworkState.
 * @details Contains known facts that are completely true in the
 *          NetworkState such as Qualities and Topologies.
 */
class Factbase {
    static int current_id;

    int id;
    std::vector<Quality> qualities;
    std::vector<Topology> topologies;

    Factbase(std::vector<Quality> q, std::vector<Topology> t);

    friend class NetworkState;

  public:

    std::tuple<std::vector<Quality>, std::vector<Topology>> get_facts_tuple() const;

    bool find_quality(Quality &q) const;
    bool find_topology(Topology &t) const;

    std::vector<Quality>::iterator get_quality(Quality &q);
    std::vector<Topology>::iterator get_topology(Topology &t);

    void add_quality(Quality &q);
    void add_topology(Topology &t);

    void delete_quality(Quality &q);
    void delete_topology(Topology &t);

    void print() const;
    void set_id();
    int get_id() const;
    size_t hash(Keyvalue &factlist) const;
};

#endif
