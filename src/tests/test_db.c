/** \file db_test.c
 * \author Kyle Cook <kylecook80@gmail.com>
 * \date June 2016
 * \copyright Copyright (C) The University of Tulsa - All Rights Reserved.
 * Unauthorized copying or distribution of this file is strictly prohibited.
 */

#include <stdlib.h>

#include "asset.h"
#include "exploit.h"
#include "network.h"
#include "util_db.h"
#include "util_list.h"

// Database connection information
#define CONNINFO "postgresql://localhost:5432/ag_gen_test"

int main() {
    struct List *network_list = list_new();
    struct List *asset_list = list_new();
    struct List *exploit_list = list_new();

    dbconnect(CONNINFO);

    int num_assets = assets_fetch(asset_list, "home");
    int num_exploits = exploits_fetch(exploit_list);
    int num_networks = networks_fetch(network_list);

    list_iterate(network_list, network_free);
    list_iterate(asset_list, asset_free);
    list_iterate(exploit_list, exploit_free);

    list_free(network_list);
    list_free(asset_list);
    list_free(exploit_list);

    dbclose();
}
