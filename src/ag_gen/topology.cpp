#include <iostream>
#include <vector>

#include "ag_gen.h"

/**
 * @brief Constructor for Topology
 *
 * @param f_asset The ID of the from asset
 * @param t_asset The ID of the to asset
 * @param dir The direction
 * @param property The property of the Topology
 * @param op The operation
 * @param val The value of the Topology
 */
Topology::Topology(int f_asset, int t_asset, DIRECTION_T dir, std::string property,
                   std::string op, std::string val, Keyvalue &facts)
    : from_asset_id(f_asset), to_asset_id(t_asset), property(move(property)),
      op(move(op)), value(move(val)), dir(std::move(dir)), encoded(encode(facts).enc) {}

/**
 * @return The From Asset ID
 */
int Topology::get_from_asset_id() const { return from_asset_id; }

/**
 * @return The To Asset ID
 */
int Topology::get_to_asset_id() const { return to_asset_id; }

/**
 * @return The property of the Topology
 */
std::string Topology::get_property() const { return property; }

/**
 * @return The operation of the Topology
 */
std::string Topology::get_op() const { return op; }

const size_t Topology::get_encoding() const {
    return encoded;
}

/**
 * @return The value of the Topology
 */
std::string Topology::get_value() const { return value; }

void Topology::set_value(std::string &val) { value = val; }

/**
 * @return The direction of the Topology
 */
DIRECTION_T Topology::get_dir() const { return dir; }

/**
 * @brief Prints the Topology
 */
void Topology::print() const {
    std::cout << std::to_string(from_asset_id) + " " + std::to_string(dir) + " " +
                std::to_string(to_asset_id) + ": " + property + " " + op + " " +
                value
         << std::endl;
}

/**
 * @brief Encodes the Topology
 *
 * @param kv_facts The Keyvalue of the facts
 *
 * @return The EncodedTopology
 */
const EncodedTopology Topology::encode(const Keyvalue &kv_facts) const {
    EncodedTopology topo{};

    topo.dec.from_asset = from_asset_id;
    topo.dec.to_asset = to_asset_id;
    topo.dec.dir = dir;
    topo.dec.property = kv_facts[property];
    topo.dec.op = 0; // Assuming only one operation for now
    topo.dec.value = kv_facts[value];

    return topo;
}

bool Topology::operator==(const Topology &rhs) const {
    if(this->dir != BIDIRECTION_T) {
        return (this->from_asset_id == rhs.from_asset_id) || (this->to_asset_id == rhs.to_asset_id);
    } else {
        if(this->from_asset_id != rhs.from_asset_id && this->from_asset_id != rhs.to_asset_id) {
            return false;
        }

        if(this->to_asset_id != rhs.to_asset_id && this->to_asset_id != rhs.from_asset_id) {
            return false;
        }
    }

    if (this->property != rhs.property) {
        return false;
    }

    if (this->op != rhs.op) {
        return false;
    }

    return (this->value == rhs.value);
}

bool Topology::operator<(const Topology &rhs) const {
    return (this->from_asset_id < rhs.from_asset_id);
}
