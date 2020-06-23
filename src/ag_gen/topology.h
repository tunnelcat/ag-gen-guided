#ifndef AG_GEN_TOPOLOGY_H
#define AG_GEN_TOPOLOGY_H

#include <string>
#include <vector>

#include "util/keyvalue.h"

typedef enum {
    FORWARD_T = 0,
    BACKWARD_T = 1,
    BIDIRECTION_T = 2,
} DIRECTION_T;

union EncodedTopology {
    struct {
        int from_asset : 16;
        int to_asset : 16;
        int dir : 2;
        int property : 10;
        int op : 4;
        int value : 16;

    } dec;
    size_t enc;
};

struct ParameterizedTopology {
    int from_param;
    int to_param;
    DIRECTION_T dir;
    std::string prop;
    std::string op;
    std::string val;

    int get_from_param() { return from_param; }
    int get_to_param() { return to_param; }
    DIRECTION_T get_dir() { return dir; }
    std::string get_property() { return prop; }
    std::string get_operation() { return op; }
    std::string get_value() { return val; }

    void print() {
        std::cout << "From Param: " << std::to_string(from_param) << std::endl;
        std::cout << "To Param: " << std::to_string(to_param) << std::endl;
        std::cout << "Direction: " << dir << std::endl << std::endl;
        std::cout << "Property: " << prop << std::endl << std::endl;
        std::cout << "Operation: " << op << std::endl << std::endl;
        std::cout << "Value: " << val << std::endl << std::endl;
    }
};

using PostconditionTopology = std::tuple<ParameterizedTopology, std::string>;

/** Topology class
 * @brief Holds information for the Topology
 */
class Topology {
    int from_asset_id;
    int to_asset_id;
    std::string property;
    std::string op;
    std::string value;
    DIRECTION_T dir;

    size_t encoded;

    const EncodedTopology encode(const Keyvalue &kv_facts) const;

    friend class Factbase;

  public:
    Topology(int f_asset, int t_asset, DIRECTION_T dir, std::string property,
             std::string op, std::string val, Keyvalue &facts);

    int get_from_asset_id() const;
    int get_to_asset_id() const;
    std::string get_property() const;
    std::string get_op() const;
    std::string get_value() const;
    DIRECTION_T get_dir() const;

    const size_t get_encoding() const;

    void print() const;

    bool operator==(const Topology &rhs) const;
    bool operator<(const Topology &rhs) const;

    void set_value(std::string &val);
};

#endif // AG_GEN_TOPOLOGY_H
