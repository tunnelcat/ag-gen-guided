// network_state.h implements the Network State class which represents a single
// state of a network and cotains a factbase of known truths for the Network
// State

#ifndef NETWORK_STATE_H
#define NETWORK_STATE_H

#include "asset.h"
#include "factbase.h"
#include "quality.h"
#include "topology.h"

#include "util/keyvalue.h"
#include "util/redis_manager.h"

class Network;

/** NetworkState class
 * @brief Manages the current state of the network
 * @details The current network state is dependent on the Qualities
 *          and Topologies in the Factbase. NetworkState allows
 *          for the addition of Qualities and Topologies to the Factbase.
 */
class NetworkState {
    Factbase factbase;
    friend class Factbase;

  public:
    NetworkState(std::vector<Quality> q, std::vector<Topology> t);
    NetworkState(const NetworkState &ns);

    const Factbase &get_factbase() const;
    size_t get_hash(Keyvalue &factlist) const;

    void set_id();
    int get_id();

    void add_qualities(std::vector<Quality> q);
    void add_topologies(std::vector<Topology> t);

    void add_quality(Quality &q);
    void add_topology(Topology &t);

    void update_quality(Quality &q);
    void update_topology(Topology &t);

    void delete_quality(Quality &q);
    void delete_topology(Topology &t);
};

#endif
