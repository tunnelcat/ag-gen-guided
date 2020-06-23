// asset.cpp is used to represent an asset on the network and contains functions
// to access and manipulate the properties (id, name, network, qualities) of an
// asset

#include <libpq-fe.h>
#include <string>
#include <vector>

#include "ag_gen.h"

using namespace std;

/**
 * @brief Constructor for Asset
 * @details Fetches the qualities of an asset with given parameters
 *
 * @param iid The id of the asset to fetch
 * @param netid The id of the network to fetch from
 * @param nname The name of the Asset
 * @param q The vector of qualities to associate with the Asset
 */
Asset::Asset(std::string nname, std::vector<Quality> q)
    : name(move(nname)), qualities(std::move(q)) {}

std::string Asset::get_name()
{

    return name;

}
