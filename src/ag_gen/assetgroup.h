//
// Created by Kyle Cook on 4/9/17.
//

#ifndef AG_GEN_ASSET_GROUP_H
#define AG_GEN_ASSET_GROUP_H

#include <vector>

#include "quality.h"
#include "topology.h"

/** AssetGroup class
 * @brief Holds information about multiple Assets
 * @details Holds the hypothetical qualities and topologies of
 *          multiple Assets as well as a vector of the number IDs of the Assets.
 *          It also implements a print method for the qualities and topologies
 *          and for the Assets.
 */
class AssetGroup {
    std::vector<Quality> hypothetical_qualities;
    std::vector<Topology> hypothetical_topologies;

    std::vector<size_t> perm;

  public:
    /**
     * @brief Constructor for AssetGroup
     * @details Initializes values of AssetGroup
     *
     * @param hypo_quals The hypothetical qualities of Assets
     * @param hypo_topos The hyptothetcial topologies of Assets
     * @param pperm IDs of the Assets
     */
    AssetGroup(std::vector<Quality> hypo_quals,
               std::vector<Topology> hypo_topos, std::vector<size_t> pperm)
        : hypothetical_qualities(move(hypo_quals)),
          hypothetical_topologies(move(hypo_topos)), perm(move(pperm)) {}

    std::vector<size_t> get_perm() const { return perm; }

    std::vector<Quality> get_hypo_quals() const {
        return hypothetical_qualities;
    }

    std::vector<Topology> get_hypo_topos() const {
        return hypothetical_topologies;
    }

    void print_facts();
    void print_group();
};

#endif // AG_GEN_ASSET_GROUP_H
