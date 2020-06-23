%error-verbose
%name-prefix="xp"

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "util/mem.h"
    #include "util/str_array.h"
    #include "util/hash.h"
    #include "util/build_sql.h"
    #include "util/list.h"

    int xplex();
    void xperror(struct list *xplist, char const *s);
    extern FILE* xpin;
    extern int xplineno;
%}

%union {
    struct str_array *arr;
    struct list *list;
    struct exploitpattern *xp;
    struct statement *st;
    struct postcondition *pc;
    struct fact *fct;
    char *string;
}

%parse-param { struct list *xplist }

%type <arr> parameters
%type <list> preconditions preconditionslist postconditions postconditionslist
%type <string> relop addop equality operator direction number value operation
%type <fct> fact precondition
%type <pc> postcondition
%type <st> statement
%type <xp> exploit

%token <string> IDENTIFIER INT FLOAT
%token <string> EQ NEQ GT LT GEQ LEQ PLUSEQ SUBEQ
%token <string> ONEDIR ONEDIRBACK BIDIR NOTONEDIR NOTBIDIR
%token <string> ADD INSERT UPDATE DELETE REMOVE
%token EXPLOIT PRECONDITIONS POSTCONDITIONS COLON FACTS PERIOD SEMI QUALITY COMMA TOPOLOGY WHITESPACE LPAREN RPAREN

%%

root: exploitlist {}
;

exploitlist: {}
| exploitlist exploit {
    list_add(xplist, $2);
}
;

exploit: EXPLOIT IDENTIFIER LPAREN parameters RPAREN EQ preconditions postconditions PERIOD {
    exploitpattern *xp = getmem(sizeof(exploitpattern));
    xp->name = $2;
    xp->params = $4;
    xp->preconditions = $7;
    xp->postconditions = $8;
    $$ = xp;
}
;

parameters: parameters COMMA IDENTIFIER {
    if($1 == NULL) {
        $$ = new_str_array();
        add_str($$, $3);
    } else {
        $$ = $1;
        add_str($$, $3);
    }
}
| IDENTIFIER {
    $$ = new_str_array();
    add_str($$, $1);
}
| { $$ = NULL; }
;

preconditions: PRECONDITIONS COLON preconditionslist { $$ = $3; }
;

preconditionslist: { $$ = NULL; }
| preconditionslist precondition {
    if($1 == NULL) {
        $$ = list_new();
        list_add($$, $2);
    } else {
        list_add($1, $2);
        $$ = $1;
    }
}
;

precondition: fact {
    $$ = $1;
}
;

postconditions: POSTCONDITIONS COLON postconditionslist {
    $$ = $3;
}
;

postconditionslist: { $$ = NULL; }
| postconditionslist postcondition {
    if($1 == NULL) {
        $$ = list_new();
        list_add($$, $2);
    } else {
        list_add($1, $2);
        $$ = $1;
    }
}
;

postcondition: operation fact {
    postcondition *pc = getmem(sizeof(postcondition));
    pc->op = $1;
    pc->f = $2;
    $$ = pc;
}
;

operation: ADD { $$ = $1; }
| INSERT { $$ = $1; }
| UPDATE { $$ = $1; }
| DELETE { $$ = $1; }
| REMOVE { $$ = $1; }
;

fact: QUALITY COLON IDENTIFIER COMMA statement SEMI {
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
    statement *st = getmem(sizeof(statement));
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
    statement* st = getmem(sizeof(statement));
    st->obj = $1;
    st->op = "";
    st->val = "";
    $$ = st;
  }
| IDENTIFIER operator value {
    statement* st = getmem(sizeof(statement));
    st->obj = $1;
    st->op = $2;
    st->val = $3;
    $$ = st;
  }
;

value: IDENTIFIER
| number
;

number: INT
| FLOAT
;

operator: relop
| addop
| equality
| ONEDIRBACK
;

equality: EQ
| NEQ
;

relop: GT
| LT
| GEQ
| LEQ
;

addop: PLUSEQ
| SUBEQ
;

direction: BIDIR
| NOTBIDIR
| NOTONEDIR
| ONEDIR
| ONEDIRBACK
;

%%

void print_xp_list(struct list *xplist) {
    for(int i=0; i<xplist->size; i++) {
        exploitpattern *xp = list_get_idx(xplist, i);
        printf("Exploit: %s\n", xp->name);

        printf("\tParams:\n");
        for(int j=0; j<xp->params->used; j++) {
            printf("\t\t%s\n", get_str_idx(xp->params, j));
        }

        printf("\tPreconditions:\n");
        for(int j=0; j<xp->preconditions->size; j++) {
            printf("\t\t%s\n", list_get_idx(xp->preconditions, j));
        }

        printf("\tPostconditions:\n");
        for(int j=0; j<xp->postconditions->size; j++) {
            struct postcondition *pc = list_get_idx(xp->postconditions, j);
            printf("\t\t%s %s %s %s\n", pc->op, pc->f->from, pc->f->dir, pc->f->to);
        }
    }
}

/*int main(int argc, char** argv) {
    FILE *file;
    if(argv[1] == 0) {
        //file = fopen("../examples/SystemV8.xp", "r");
        file = fopen("../examples/SystemV12_DIE_PIPE.xp", "r");
    } else {
        file = fopen(argv[1], "r");
    }

    if(!file) {
        fprintf(stderr, "Cannot open file.\n");
        return -1;
    }

    list *xplist = list_new();

    //yydebug = 1;
    yyin = file;
    do {
        yyparse(xplist);
    } while(!feof(yyin));

    FILE* fp = fopen("exploits.sql", "w");
    if(fp == NULL) {
        printf("Error creating file.\n");
        exit(1);
    }

    //print_xp_list(xplist);

    /////////////////////////
    // EXPLOITS
    /////////////////////////

    hashtable *exploit_ids = new_hashtable(101);

    // Preload buffer with SQL prelude
    size_t bufsize = INITIALBUFSIZE;
    char *buf = getcmem(bufsize);
    strcat(buf, "INSERT INTO exploit VALUES\n");

    // Iterate over each exploit in the list
    // Generate an "exploit_instance" which contains
    // the generated exploit id and the sql for
    // for the exploit.
    for(int i=0; i<xplist->size; i++) {
        struct exploitpattern *xp = list_get_idx(xplist, i);
        exploit_instance *ei = make_exploit(xp);
        add_hashtable(exploit_ids, xp->name, ei->id);
        // printf("%s - %d\n", xp->name, get_hashtable(exploit_ids, xp->name));
        while(bufsize < strlen(buf) + strlen(ei->sql))
            buf = realloc(buf, (bufsize*=2));
        strcat(buf, ei->sql);
    }

    // Replace the last comma with a semicolon
    char *last = strrchr(buf, ',');
    *last = ';';
    fprintf(fp, "%s\n", buf);

    /////////////////////////
    // PRECONDITIONS
    /////////////////////////

    // Preload buffer with SQL prelude
    bufsize = INITIALBUFSIZE;
    buf = getcmem(bufsize);
    strcat(buf, "INSERT INTO exploit_precondition VALUES\n");

    // Iterate over each exploit. We then iterate
    // over each f in the exploit and generate
    // the sql for it.
    for(int i=0; i<xplist->size; i++) {
        exploitpattern *xp = list_get_idx(xplist, i);
        for(int j=0; j<xp->preconditions->size; j++) {
            f *fct = list_get_idx(xp->preconditions, j);
            // printf("%s: %d\n", fct->from, get_hashtable(exploit_ids, fct->from));
            char *sqladd = make_precondition(exploit_ids, xp, fct);
            while(bufsize < strlen(buf) + strlen(sqladd)) {
                buf = realloc(buf, (bufsize*=2));
            }
            strcat(buf, sqladd);
        }
    }

    last = strrchr(buf, ',');
    *last = ';';
    fprintf(fp, "%s\n", buf);

    /////////////////////////
    // POSTCONDITIONS
    /////////////////////////

    // Preload buffer with SQL prelude
    bufsize = INITIALBUFSIZE;
    buf = getcmem(bufsize);
    strcat(buf, "INSERT INTO exploit_postcondition VALUES\n");

    // Iterate over each exploit. We then iterate
    // over each f in the exploit and generate
    // the sql for it.
    for(int i=0; i<xplist->size; i++) {
        exploitpattern *xp = list_get_idx(xplist, i);
        for(int j=0; j<xp->postconditions->size; j++) {
            postcondition *pc = list_get_idx(xp->postconditions, j);
            char *sqladd = make_postcondition(exploit_ids, xp, pc);
            while(bufsize < strlen(buf) + strlen(sqladd)) {
                buf = realloc(buf, (bufsize*=2));
            }
            strcat(buf, sqladd);
        }
    }

    last = strrchr(buf, ',');
    *last = ';';
    fprintf(fp, "%s\n", buf);
} */

void xperror(struct list *xplist, char const *s) {
    fprintf(stderr, "Line %d: %s\n", xplineno, s);
    exit(-1);
}
