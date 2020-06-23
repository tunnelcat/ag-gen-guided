/** \file db.h
 * \author Kyle Cook <kylecook80@gmail.com>
 * \date June 2016
 * \copyright Copyright (C) The University of Tulsa - All Rights Reserved.
 * Unauthorized copying or distribution of this file is strictly prohibited.
 */

#ifndef UTIL_DB_HPP
#define UTIL_DB_HPP

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <libpq-fe.h>

class DB;
typedef std::vector<std::string> Row;

class DBException : public std::runtime_error {
  public:
    explicit DBException(std::string &error_message)
        : std::runtime_error(error_message) {}
    explicit DBException(std::string &&error_message)
        : std::runtime_error(error_message) {}
};

class Connection {
    bool connected = false;
    std::string ci;
    PGconn *conn_r;

    friend class DB;

  public:
    Connection() {}

    void connect(const std::string &conninfo) {
        // Create database connection
        ci = conninfo;
        conn_r = PQconnectdb(conninfo.c_str());
        //conn_r = PQconnectdb("dbname=ag_gen user=user password=hello123"); 
        if (PQstatus(conn_r) != CONNECTION_OK) {
            std::string errormsg(PQerrorMessage(conn_r));
            throw DBException("Database connection failed: " + conninfo + "\n" +
                              errormsg);
        }
        connected = true;

        /* https://www.postgresql.org/docs/10/static/libpq-example.html */
        /* Set always-secure search path, so malicious users can't take control. */
        // PGresult *res = PQexec(conn_r, "SELECT pg_catalog.set_config('search_path', '', false)");
        // if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        //     std::string errormsg(PQerrorMessage(conn_r));
        //     PQclear(res);
        //     throw DBException("Something went really wrong: " + errormsg);
        // }

        // PQclear(res);
    }

    ~Connection() {
        // Close connection before exiting
        if (conn_r) {
            PQfinish(conn_r);
        }
        connected = false;
    }

    bool is_connected() { return connected; }

    std::vector<Row> exec(const std::string &sql) {
        if (!is_connected()) {
            throw DBException("Not connected to Database.");
        }

        std::vector<Row> rows;
        PGresult *res = PQexec(conn_r, sql.c_str());
        if (PQresultStatus(res) == PGRES_COMMAND_OK) {
            // No return
        } else if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            // Return rows
            int numrows = PQntuples(res);
            int numfields = PQnfields(res);
            for (auto i = 0; i < numrows; i++) {
                Row new_row;
                for (auto j = 0; j < numfields; j++) {
                    new_row.push_back(PQgetvalue(res, i, j));
                }
                rows.push_back(new_row);
            }
        } else {
            // DB Error
            throw DBException(PQerrorMessage(conn_r));
        }

        PQclear(res);
        return rows;
    }

    void execAsync(const std::string &sql) {
        if (!is_connected()) {
            throw DBException("Not connected to Database.");
        }

        while(PQgetResult(conn_r) != NULL);

        int res = PQsendQuery(conn_r, sql.c_str());
    }
};

class DB {
    Connection conn;

  public:
    DB() {}

    void connect(const std::string &conninfo) { conn.connect(conninfo); }

    //Connection get_conn() {return conn;}

    std::vector<Row> exec(const std::string &sql) {  //note: Row is a string vector, so vector<Row> type is a vector of string vectors.
        try {
            auto results = conn.exec(sql);
            return results;
        } catch (DBException &e) {
            std::cerr << "Database Exception: " << e.what() << std::endl;
            abort();
        }
    }

    void execAsync(const std::string &sql) {
        try {
            conn.execAsync(sql);
        } catch (DBException &e) {
            std::cerr << "Database Exception: " << e.what() << std::endl;
            abort();
        }
    }

    PGconn *raw_conn() {
        return conn.conn_r;
    }
};

#endif // UTIL_DB_HPP
