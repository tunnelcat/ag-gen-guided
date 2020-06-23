//
// Created by Kyle Cook on 6/24/17.
//

#include <iostream>

#include "edge.h"
#include "util/db.h"

/**
 * @brief Constructor for Edge
 * @details Initializes information with given parameters and initializes id to
 * 0.
 *
 * @param iFrom The From Node
 * @param iTo The To Node
 * @param ex Exploit associated with the Edge
 * @param ag AssetGroup associated with the Edge
 */
Edge::Edge(int iFrom, int iTo, Exploit &ex, AssetGroup &ag)
    : from_node(iFrom), to_node(iTo), exploit(ex), assetGroup(ag), deleted(false) {}

/**
 * @return The Edge ID
 */
int Edge::get_id() { return id; }

void Edge::set_deleted() { deleted = true; }

bool Edge::is_deleted() { return deleted; }

int Edge::get_from_id()
{

    return from_node;

}

int Edge::get_to_id()
{

    return to_node;

}

int Edge::get_exploit_id()
{

    return exploit.get_id();

}

/**
 * @return The Edge information as a string for SQL
 */
std::string Edge::get_query() {
    return std::to_string(from_node) + "," + std::to_string(to_node) + "," +
           std::to_string(exploit.get_id()) + ")";
}

/**
 * @brief Sets the Edge id to the current id and increments edge_current_id.
 *
 * @return The new id
 */
int Edge::set_id() {
    id = edge_current_id++;
    return id;
}

int Edge::edge_current_id = 0;

/**
 * @return The Assets as a string for SQL
 */
std::string Edge::get_asset_query() {
    auto current_perm = assetGroup.get_perm();
    std::string sql;
    for (size_t i = 0; i < current_perm.size(); ++i) {

        if (i == 0)
            sql += "(" + std::to_string(id) + "," + std::to_string(i) + "," +
                   std::to_string(current_perm[i]) + ")";

        else
            sql += ",(" + std::to_string(id) + "," + std::to_string(i) + "," +
                   std::to_string(current_perm[i]) + ")";
    }
    return sql;
}
