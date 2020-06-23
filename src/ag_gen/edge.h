//
// Created by Kyle Cook on 6/24/17.
//

#ifndef AG_GEN_EDGE_H
#define AG_GEN_EDGE_H

#include "assetgroup.h"
#include "exploit.h"

/** Edge class
 * @brief Edge of the graph.
 */
class Edge {
    static int edge_current_id;
    int id;
    int from_node;
    int to_node;
    Exploit exploit;
    AssetGroup assetGroup;
    bool deleted;

  public:
    Edge(int, int, Exploit &, AssetGroup &);

    std::string get_query();
    std::string get_asset_query();

    int get_id();
    int set_id();
    int get_from_id();
    int get_to_id();
    int get_exploit_id();
    void set_deleted();
    bool is_deleted();
};

#endif // AG_GEN_EDGE_H
