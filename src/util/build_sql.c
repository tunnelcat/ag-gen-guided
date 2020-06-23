#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util/build_sql.h"
#include "util/mem.h"
#include "util/list.h"
#include "util/vector.h"
#include "util/hash.h"

#define BUFSPACE 64

const char *sqlAsset = "(%d, '%s'),";
const char *sqlQuality = "(%d, '%s', '%s', '%s'),";
const char *sqlTopology = "(%d, %d, '%s', '%s', '%s', '%s'),";
const char *sqlExploit = "\t(%d, '%s', %d),\n";
const char *sqlPrecondition = "\t(%d, %d, %d, %d, %d, '%s', '%s', '%s', '%s'),\n";
const char *sqlPostcondition = "\t(%d, %d, %d, %d, %d, '%s', '%s', '%s', '%s', '%s'),\n";

static size_t asset_curr_id = 0;
asset_instance *make_asset(char *asset) {
    size_t len = strlen(sqlAsset) + strlen(asset) + BUFSPACE;

    char *buf = malloc(len);
    sprintf(buf, sqlAsset, asset_curr_id, asset);

    asset_instance *ai = getmem(sizeof(struct asset_instance));
    ai->id = asset_curr_id++;
    ai->sql = buf;

    return ai;
}

char *make_quality(size_t assetid, statement *st) {
    size_t mystringlen = strlen(sqlQuality) +
        strlen(st->obj) + strlen(st->op) + strlen(st->val) + BUFSPACE;

    char *mystring = getstr(mystringlen);
    sprintf(mystring, sqlQuality, assetid, st->obj, st->op, st->val);

    return mystring;
}

char *make_topology(size_t fromasset, size_t toasset, char *dir, statement *st) {
    size_t mystringlen = strlen(sqlTopology) +
        strlen(st->obj) + strlen(st->op) + strlen(st->val) + BUFSPACE;

    char *mystring = getstr(mystringlen);
    sprintf(mystring, sqlTopology, fromasset, toasset, dir, st->obj, st->op, st->val);

    return mystring;
}

static size_t postcondition_curr_id = 0;
char *make_postcondition(hashtable *exploit_ids, exploitpattern *xp, postcondition *pc) {
    char *buf = malloc(1000);

    int exploit_id = get_hashtable(exploit_ids, xp->name);
    hashtable *params = str_array_to_hashtable(xp->params);
    char *action = pc->op;

    if(pc->f->type == QUALITY_T) {
        char *obj = pc->f->st->obj;
        char *op = pc->f->st->op;
        char *val = pc->f->st->val;

        sprintf(buf, sqlPostcondition, postcondition_curr_id++, exploit_id, QUALITY_T, get_hashtable(params, pc->f->from), NULL, obj, val, op, NULL, action);

    } else {
        char *obj = pc->f->st->obj;
        char *op = pc->f->st->op;
        char *val = pc->f->st->val;
        char *dir = pc->f->dir;
        int asset_from = get_hashtable(params, pc->f->from);
        int asset_to = get_hashtable(params, pc->f->to);

        sprintf(buf, sqlPostcondition, postcondition_curr_id++, exploit_id, TOPOLOGY_T, asset_from, asset_to, obj, val, op, dir, action);
    }

    return buf;
}

static size_t precondition_curr_id = 0;
char *make_precondition(hashtable *exploit_ids, exploitpattern *xp, fact *fct) {
    char *buf = malloc(1000);

    int exploit_id = get_hashtable(exploit_ids, xp->name);
    hashtable *params = str_array_to_hashtable(xp->params);

    if(fct->type == QUALITY_T) {
        char *obj = fct->st->obj;
        char *op = fct->st->op;
        char *val = fct->st->val;

        sprintf(buf, sqlPrecondition, precondition_curr_id++, exploit_id, QUALITY_T, get_hashtable(params, fct->from), NULL, obj, val, op, NULL);

    } else {
        char *obj = fct->st->obj;
        char *op = fct->st->op;
        char *val = fct->st->val;
        char *dir = fct->dir;

        sprintf(buf, sqlPrecondition, precondition_curr_id++, exploit_id, TOPOLOGY_T, get_hashtable(params, fct->from), get_hashtable(params, fct->to), obj, val, op, dir);
    }

    return buf;
}

static size_t exploit_curr_id = 0;
exploit_instance *make_exploit(exploitpattern *xp) {
    size_t len = strlen(sqlExploit) + strlen(xp->name) + BUFSPACE;
    char *buf = malloc(len);
    sprintf(buf, sqlExploit, exploit_curr_id, xp->name, xp->params->used);
    exploit_instance *ei = getmem(sizeof(struct exploit_instance));
    ei->id = exploit_curr_id++;
    ei->sql = buf;
    return ei;
}

void print_fact(fact *fct) {
    if(fct->type == QUALITY_T) {
        printf("quality:%s,%s%s%s\n", fct->from, fct->st->obj, fct->st->op, fct->st->val);
    }
    else {
        printf("topology:%s%s%s,%s%s%s\n", fct->from, fct->dir, fct->to, fct->st->obj, fct->st->op, fct->st->val);
    }
}
