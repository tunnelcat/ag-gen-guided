#!/usr/bin/env bash

function init() {
    echo -n "Loading Schema: "
    SCHEMA="sql/schema.sql"
    OUTPUT="$(psql $DB < $SCHEMA 2>&1)"
    if [[ $? -ne 0 ]]; then
        echo "Error" >&2
        echo $OUTPUT >&2
        exit 1
    fi
    echo "Done"

    if [[ -f "$FILE" ]]; then
        echo -n "Importing Data: "
        OUTPUT="$(psql $DB < $FILE 2>&1)"
        if [[ $? -ne 0 ]]; then
            echo "Error"
            echo $OUTPUT
            exit 1
        fi
        echo "Done"
    fi

    # Execute extra sql files
    echo -n "Adding support functions: "
    OUTPUT="$(psql $DB < "sql/factbase.sql" 2>&1)"
    if [[ $? -ne 0 ]]; then
        echo "Error"
        echo $OUTPUT
        exit 1
    fi
    echo "Done"

    echo "Database Initialization Complete."
}

function update() {
    if [[ -z "$FILE" ]]; then
        echo "-i is required for the update action."
        exit 1
    fi

    if [[ ! -f "$FILE" ]]; then
        echo "$FILE must exist."
        exit 1
    fi

    if [[ -z "$DB" ]]; then
        echo "-d is required for the update action."
        exit 1
    fi

    echo -n "Running SQL script $FILE: "
    OUTPUT="$(psql $DB < $FILE 2>&1)"
    if [[ $? -ne 0 ]]; then
        echo "Error" >&2
        echo $OUTPUT >&2
        exit 1
    fi
    echo "Complete"
}

function drop() {
    if [[ -z "$DB" ]]; then
        echo "-d is required for the drop action." >&2
        exit 1
    fi

    echo -n "Dropping $DB: "
    OUTPUT="$(dropdb $DB 2>&1)"
    if [[ $? -ne 0 ]]; then
        echo "Error"
        echo $OUTPUT
        exit 1
    fi
    echo "Dropped"
}

function test() {
    echo "Test!"
    echo "File: $FILE"
    echo "Database: $DB"
    echo "Action: $ACTION"
}

function usage() {
    echo "usage: db_manage [OPTIONS]" >&2
    echo "A script to help manage the attack graph generation database" >&2
    echo "" >&2
    echo "  -a, --action        Action to perform on the database" >&2
    echo "                          Defaults to \"init\"" >&2
    echo "  -d, --database      The database to manage" >&2
    echo "                          Defaults to \"ag_gen\"" >&2
    echo "  -f, --force         Forces a database to be overwritten" >&2
    echo "  -h, --help          Displays this help message" >&2
    echo "  -i, --import        SQL data to import to the database" >&2
    echo "  -s, --schema        Schema file to initialize database with" >&2
    echo "                          Defaults to \"sql/schema.sql\"" >&2
    echo "" >&2
}

if [[ -z "$1" ]]; then
    usage
    exit 1
fi

while true; do
    case "$1" in
        -i | --import)
            # Include SQL file
            FILE="$2"
            shift 2
            ;;
        -d | --database)
            # Use this database
            DB="$2"
            shift 2
            ;;
        -a | --action)
            ACTION=$2
            shift 2
            ;;
        -s | --schema)
            SCHEMA="$2"
            shift 2
            ;;
        -f | --force)
            FORCE=true
            shift
            ;;
        -h | --help)
            # Display help
            usage
            exit 0
            ;;
        --)
            # End of options
            shift
            break
            ;;
        -*)
            echo "Unknown option: $1" >&2
            exit 1
            ;;
        *)
            break
            ;;
    esac
done

if [[ -z "$ACTION" ]]; then
    ACTION="init"
fi
$ACTION # Call the action as a function














