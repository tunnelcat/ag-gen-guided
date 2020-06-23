%error-verbose
%name-prefix="nm"

%{
    #include <stdio.h>
    #include <stdlib.h>

    #include "util/mem.h"
    #include "util/str_array.h"
    #include "util/hash.h"
    #include "util/build_sql.h"

    #define YYDEBUG 0

    int nmlex();
    void yyerror(struct networkmodel* nm, char const *s);

    extern FILE* nmin;
    extern int nmlineno;

    extern int assetcount;
    extern int factcount;
%}

%union {
    struct str_array* arr;
    struct list* lst;
    struct networkmodel* model;
    struct statement* st;
    struct fact *fct;
    char* string;
}

%parse-param { struct networkmodel* nm }

%type <lst> factlist
%type <fct> f

%type <string> asset
%type <string> relop operator direction number value

%type <st> statement

%token <string> IDENTIFIER INT FLOAT
%token <string> EQ GT LT GEQ LEQ
%token <string> ONEDIR ONEDIRBACK BIDIR NOTONEDIR NOTBIDIR
%token NETWORK MODEL ASSETS COLON FACTS PERIOD SEMI QUALITY COMMA TOPOLOGY WHITESPACE;
%token TAGS

%%

root: NETWORK IDENTIFIER EQ assets facts tags PERIOD {}
;

assets: ASSETS COLON assetlist {}
;

assetlist: {}
| assetlist asset {
    list_add(nm->assets, $2);
  }
;

asset: IDENTIFIER SEMI { $$ = $1; }
;

tags: {}
| TAGS COLON {}
;

facts: FACTS COLON factlist { nm->facts = $3; }
;

factlist: { $$ = NULL; }
| factlist f {
    if($1 == NULL) {
        $$ = list_new();
        list_add($$, $2);
    } else {
        list_add($$, $2);
        $$ = $1;
    }
  }
;

f: QUALITY COLON IDENTIFIER COMMA statement SEMI {
    statement *st = getmem(sizeof(struct statement));
    st->obj = $5->obj;
    st->op = $5->op;
    st->val = $5->val;

    struct fact *fct = getmem(sizeof(struct fact));
    fct->type = QUALITY_T;
    fct->from = $3;
    fct->dir = NULL;
    fct->to = NULL;
    fct->st = st;

    $$ = fct;
  }
| TOPOLOGY COLON IDENTIFIER direction IDENTIFIER COMMA statement SEMI {
    struct statement* st = $7;
    st->obj = $7->obj;
    st->op = $7->op;
    st->val = $7->val;

    struct fact *fct = getmem(sizeof(struct fact));
    fct->type = TOPOLOGY_T;
    fct->from = $3;
    fct->dir = $4;
    fct->to = $5;
    fct->st = st;

    $$ = fct;
  }
;

statement:
  IDENTIFIER {
    struct statement* st = getmem(sizeof(struct statement));
    st->obj = $1;
    st->op = "";
    st->val = "";
    $$ = st;
  }
| IDENTIFIER operator value {
    struct statement* st = getmem(sizeof(struct statement));
    st->obj = $1;
    st->op = $2;
    st->val = $3;
    $$ = st;
  }
;

value:
  IDENTIFIER
| number
;

number:
  INT
| FLOAT
;

operator:
  relop
| EQ
;

relop:
  GT
| LT
| GEQ
| LEQ
;

direction:
  BIDIR
| ONEDIR
| ONEDIRBACK
| NOTBIDIR
| NOTONEDIR
;

%%

/*
int main(int argc, char** argv) {
    FILE* file;
    if(argv[1] == 0) {
        printf("Please pass a file to parse as an argument.\n");
        exit(1);
    } else {
        file = fopen(argv[1], "r");
    }

    if(!file) {
        fprintf(stderr, "Cannot open file.\n");
        return -1;
    }

    struct networkmodel nm;
    nm.asset_tab = new_hashtable(101);

    //yydebug = 1;
    yyin = file;
    do {
        yyparse(&nm);
    } while(!feof(yyin));

    print_str_array(nm.assets);

    str_array* qualities = new_str_array();
    str_array* topologies = new_str_array();

    for(int i=0; i<nm.facts->used; i++) {
        char* current = nm.facts->arr[i];
        char* copy = getstr(strlen(current));

        strncpy(copy, current, strlen(current));

        char* type = strsep(&copy, ":");
        printf("%s\n", type);
        if(strncmp(type, "q", 1) == 0) {
            add_str(qualities, copy);
        } else {
            add_str(topologies, copy);
        }
    }

    FILE* fp = fopen("test.sql", "w");
    if(fp == NULL) {
        printf("Error creating file.\n");
        exit(1);
    }

    char* assetheader = "INSERT INTO asset VALUES";
    fprintf(fp, "%s\n", assetheader);
    for(int i=0; i<nm.assets->used-1; i++) {
        char* nextstring = nm.assets->arr[i];
        fprintf(fp, "%s\n", nextstring);
    }
    char* stripped = nm.assets->arr[nm.assets->used-1];
    stripped[strlen(stripped)-1] = '\n';
    fprintf(fp, "%s\n", stripped);

    fprintf(fp, "%s\n", "ON CONFLICT DO NOTHING;");

    char* qualityheader = "\nINSERT INTO quality VALUES";
    fprintf(fp, "%s\n", qualityheader);
    for(int i=0; i<qualities->used-1; i++) {
        char* nextstring = qualities->arr[i];
        fprintf(fp, "%s\n", nextstring);
    }
    stripped = qualities->arr[qualities->used-1];
    stripped[strlen(stripped)-1] = '\n';
    fprintf(fp, "%s\n", stripped);

    fprintf(fp, "%s\n", "ON CONFLICT DO NOTHING;");

    char* topologyheader = "\nINSERT INTO topology VALUES";
    fprintf(fp, "%s\n", topologyheader);
    for(int i=0; i<topologies->used-1; i++) {
        char* nextstring = topologies->arr[i];
        fprintf(fp, "%s\n", nextstring);
    }
    stripped = topologies->arr[topologies->used-1];
    stripped[strlen(stripped)-1] = '\n';
    fprintf(fp, "%s\n", stripped);

    fprintf(fp, "%s\n", "ON CONFLICT DO NOTHING;");

    fclose(fp);

    free_hashtable(nm.asset_tab);
}
*/

void yyerror(struct networkmodel* nm, char const *s) {
    fprintf(stderr, "Line %d: %s\n", nmlineno, s);
    exit(-1);
}
