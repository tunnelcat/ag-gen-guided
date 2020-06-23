/** \file perm_test.c
 * \author Kyle Cook <kylecook80@gmail.com>
 * \date July 2016
 * \copyright Copyright (C) The University of Tulsa - All Rights Reserved.
 * Unauthorized copying or distribution of this file is strictly prohibited.
 */

#include "util_common.h"
#include "util_odometer.h"

int main() {
    char *asset1 = "Asset 1";
    char *asset2 = "Asset 2";
    char *asset3 = "Asset 3";

    char *set[3] = {asset1, asset2, asset3};

    struct Odometer *perms = odometer_new(3, 3);
    odometer_printset(perms, (char **)set);
    odometer_free(perms);
}
