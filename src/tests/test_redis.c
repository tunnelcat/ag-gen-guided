/** \file redis_test.c
 * \author Kyle Cook <kylecook80@gmail.com>
 * \date June 2016
 * \copyright Copyright (C) The University of Tulsa - All Rights Reserved.
 * Unauthorized copying or distribution of this file is strictly prohibited.
 *
 * Redis_test determines if there is a usable redis server.
 *
 * When run this executable validates whether a connection can be established to
 * the redis server and if an asset that is put into the redis server can be
 * retrieved with all of its data intact.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>

#include "asset.h"
#include "exploit.h"
#include "redisasset.h"
#include "redisexploit.h"
#include "util_common.h"
#include "util_redis.h"

static int rasset_test() {
    struct Asset *asset;
    struct Asset *new_asset;

    asset = calloc(1, sizeof(struct Asset));
    if (asset == NULL) {
        DEBUG_PRINT("Memory allocation error.\n", 0);
        exit(1);
    }

    asset->id = 1234;
    asset->name = dynstr("Sheard Dumisani");
    ;
    asset->network_id = 19122232;

    rasset_set("asset1", asset);
    new_asset = rasset_get("asset1");

    asset_free(asset);
    asset_free(new_asset);

    return 0;
}

static int rexploit_test() {
    struct Exploit *exploit;
    struct Exploit *new_exploit;

    exploit = calloc(1, sizeof(struct Exploit));
    if (!exploit) {
        DEBUG_PRINT("Memory allocation error.\n", 0);
        return EXIT_FAILURE;
    }

    exploit->id = 143222;
    exploit->name = dynstr("exploit1");

    rexploit_set("exploit", exploit);
    new_exploit = rexploit_get("exploit");

    exploit_free(exploit);
    exploit_free(new_exploit);

    return 0;
}

int main() {
    int res;
    int state = 0;
    int error = 0;

    res = redis_connect("localhost", 6379);
    if (res != 0) {
        DEBUG_PRINT("Error connecting to redis.\n", 0);
        exit(1);
    }

    res = rasset_test();
    if (res) {
        state = 1;
        error = 1;
    }
    TEST_PRINT("rasset_test", state);
    state = 0;

    res = rexploit_test();
    if (res) {
        state = 1;
        error = 1;
    }
    TEST_PRINT("rexploit_test", state);
    state = 0;

    return error;
}
