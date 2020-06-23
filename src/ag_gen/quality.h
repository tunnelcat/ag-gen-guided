//
// Created by Kyle Cook on 4/9/17.
//

#ifndef AG_GEN_QUALITY_H
#define AG_GEN_QUALITY_H

#include <string>

#include "util/keyvalue.h"

union EncodedQuality {
    struct {
        int asset_id : 16;
        int attr : 12;
        int op : 4;
        int val : 16;
    } dec;
    size_t enc;
};

/**
 * @brief Holds information about a Quality and a parameter number.
 */
struct ParameterizedQuality {
    int param;
    std::string name;
    std::string value;

    int get_param_num() { return param; }

    void print() {
        std::cout << "Param: " + std::to_string(param) << std::endl;
        std::cout << "Attribute: " + name << std::endl;
        std::cout << "Value: " + value << std::endl << std::endl;
    }
};

using PostconditionQuality = std::tuple<ParameterizedQuality, std::string>;

/** Quality class
 * @brief Holds information for the Quality
 */
class Quality {
    int asset_id;
    std::string name;
    std::string op;
    std::string value;

    size_t encoded;

    EncodedQuality encode(const Keyvalue &kv_facts) const;

    friend class Factbase;

  public:
    Quality(int assetId, std::string qualName, std::string op,
            std::string qualValue, Keyvalue &facts);

    int get_asset_id() const;
    std::string get_name() const;
    std::string get_op() const;
    std::string get_value() const;

    const size_t get_encoding() const;

    void set_value(std::string &val);

    void print() const;

    bool operator==(const Quality &rhs) const;
    bool operator<(const Quality &rhs) const;
};

#endif // AG_GEN_QUALITY_H
