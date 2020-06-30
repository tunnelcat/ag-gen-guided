
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <array>
#include <iterator>
#include <sys/time.h>

#include "db_functions.h"

#include "keyvalue.h"
#include "db.h"

#include "ag_gen/exploit.h"
#include "ag_gen/edge.h"
#include "ag_gen/quality.h"
#include "ag_gen/topology.h"
#include "ag_gen/asset.h"
#include "ag_gen/factbase.h"

static DB db;
void init_db(std::string connect_str) {
    db.connect(connect_str);
}

void import_models(std::string nm, std::string xp) {
    db.exec(nm);
    db.exec(xp);
}

int get_max_factbase_id() {
    std::vector<Row> res = db.exec("SELECT MAX(id) FROM factbase;");
    return stoi(res[0][0]);
}

std::vector<std::string> fetch_keyvalues() {
    std::vector<Row> rows = db.exec("SELECT property FROM keyvalue;");
    std::vector<std::string> kvs{};

    for(auto &row : rows) {
        kvs.push_back(row[0]);
    }

    return kvs;
}

Keyvalue fetch_kv() {
    auto kv_raw = fetch_keyvalues();
    Keyvalue kv{};
    kv.populate(kv_raw);
    return kv;
}

void delete_edges(std::vector<int> edge_ids) {
    std::ostringstream ss;

    ss << "(";

    std::copy(edge_ids.begin(), edge_ids.end() - 1, std::ostream_iterator<int>(ss, ", "));
    ss << edge_ids.back() << ")";

    std::string ids = ss.str();

    std::string sql = "DELETE FROM edge_asset_binding WHERE edge_id IN " + ids
                    + "; DELETE FROM edge WHERE id IN" + ids + ";";

    db.exec(sql);
}

GraphInfo fetch_graph_info() {
    std::vector<Row> factbase_rows = db.exec("SELECT id FROM factbase ORDER BY id;");
    std::vector<Row> edge_rows = db.exec("SELECT * FROM edge ORDER BY id;");

    std::vector<int> factbase_ids;
    factbase_ids.resize(factbase_rows.size());

    std::transform(factbase_rows.begin(), factbase_rows.end(), factbase_ids.begin(),
                   [](Row row){ return std::stoi(row[0]); });

    std::vector<std::array<int, 4>> edges;

    for (auto& row : edge_rows) {
        int id = std::stoi(row[0]);
        int from_node = std::stoi(row[1]);
        int to_node = std::stoi(row[2]);
        int exploit_id = std::stoi(row[3]);

        std::array<int, 4> arr = {id, from_node, to_node, exploit_id};
        edges.push_back(arr);
    }

    return std::make_pair(factbase_ids, edges);
}

std::vector<std::vector<std::pair<size_t, std::string>>> fetch_all_factbase_items() {
    std::vector<std::vector<std::pair<size_t, std::string>>> fi;
    std::vector<Row> firows = db.exec("SELECT * FROM factbase_item;");
    if (firows.empty())
        throw CustomDBException();

    int current_index = -1;
    for (auto firow : firows) {
        int index = stoi(firow[0]);
        if (index != current_index) {
            current_index = index;
            fi.emplace_back();
        }
        size_t st;
        sscanf(firow[1].c_str(), "%zu", &st);
        fi[index].push_back(make_pair(st, firow[2]));
    }

    return fi;
}

std::vector<std::pair<size_t, std::string>> fetch_one_factbase_items(int index) {
    std::vector<std::pair<size_t, std::string>> fi;
    std::vector<Row> firows = db.exec("SELECT f,type FROM factbase_item WHERE factbase_id=" + std::to_string(index) + ";");
    if (firows.empty())
        throw CustomDBException();

    for (auto firow : firows) {
        size_t st;
        sscanf(firow[0].c_str(), "%zu", &st);
        fi.push_back(std::make_pair(st, firow[1]));
    }

    return fi;
}

std::vector<std::string> fetch_unique_values() { //from the database to fetch all the values and properties and put them in a string vector
    std::string keyvaluesql = "SELECT property FROM quality\n"
                              "UNION DISTINCT\n"
                              "SELECT value FROM quality\n"
                              "UNION DISTINCT\n"
                              "SELECT property FROM exploit_postcondition\n"
                              "UNION DISTINCT\n"
                              "SELECT value FROM exploit_postcondition\n"
                              "UNION DISTINCT\n"
                              "SELECT property FROM topology\n"
                              "UNION DISTINCT\n"
                              "SELECT value FROM topology;";//all the values and properties will be distinct from each other

    std::vector<Row> rows = db.exec(keyvaluesql);
    std::vector<std::string> attrs; //this will be a set of values and properties

    for(auto &row : rows) {
        attrs.push_back(row[0]);
    }

    return attrs;
}

/**
 * @brief       Fetches all possible quality attributes.
 *
 * @return     Returns a vector of strings with all possible quality attributes.
 */
std::vector<std::string> fetch_quality_attributes() {
    std::vector<std::string> attrs;
    std::vector<Row> qrows = db.exec("SELECT DISTINCT property FROM quality;");
    std::vector<Row> erows =
        db.exec("SELECT DISTINCT property FROM exploit_postcondition;");

    for (auto &row : qrows) {
        std::string prop = row[0];
        attrs.push_back(prop);
    }

    for (auto &row : erows) {
        std::string prop = row[0];
        attrs.push_back(prop);
    }

    return attrs;
}

/**
 * @brief      Fetches all possible quality values.
 *
 * @return     Returns
 */
std::vector<std::string> fetch_quality_values() {
    std::vector<std::string> vals;
    std::vector<Row> qrows = db.exec("SELECT DISTINCT value FROM quality;");
    std::vector<Row> erows =
        db.exec("SELECT DISTINCT value FROM exploit_postcondition;");

    for (auto &row : qrows) {
        std::string val = row[0];
        vals.push_back(val);
    }

    for (auto &row : erows) {
        std::string val = row[0];
        vals.push_back(val);
    }

    return vals;
}

std::vector<std::string> fetch_topology_attributes() {
    std::vector<std::string> attrs;
    std::vector<Row> rows = db.exec("SELECT DISTINCT property FROM topology;");

    for (auto &row : rows) {
        std::string prop = row[0];
        attrs.push_back(prop);
    }

    return attrs;
}

/**
 * @brief      Fetches all possible topology values.
 *
 * @return     Returns a vector of strings with all possible topology values
 */
std::vector<std::string> fetch_topology_values() {
    std::vector<std::string> vals;
    std::vector<Row> rows = db.exec("SELECT DISTINCT value FROM topology;");

    for (auto &row : rows) {
        std::string val = row[0];
        vals.push_back(val);
    }

    return vals;
}

/**
 * @brief Fetches the preconditions of an Exploit from the database.
 */
std::unordered_map<
    int, std::tuple<std::vector<ParameterizedQuality>, std::vector<ParameterizedTopology>>>
fetch_exploit_preconds() {
    std::vector<Row> rows = db.exec("SELECT * FROM exploit_precondition;");

    std::unordered_map<
        int, std::tuple<std::vector<ParameterizedQuality>, std::vector<ParameterizedTopology>>>
        precond_map;

    int curr_id = -1;
    std::vector<ParameterizedQuality> preconds_q;
    std::vector<ParameterizedTopology> preconds_t;
    for (auto &row : rows) {
        int type = stoi(row[2]);
        int exploit_id = stoi(row[1]);

        if (exploit_id != curr_id) {
            if (curr_id != -1) {
                std::tuple<std::vector<ParameterizedQuality>,
                      std::vector<ParameterizedTopology>>
                    tup{preconds_q, preconds_t};
                precond_map[curr_id] = tup;

                preconds_q.clear();
                preconds_t.clear();
            }

            curr_id = exploit_id;
        }

        if (type == 0) {//type 0 is quality-typed precondition
            int param1 = stoi(row[3]);
            std::string property = row[5];
            std::string value = row[6];

            ParameterizedQuality qual{param1, property, value};
            preconds_q.push_back(qual);
        } else { //type 1 is topology-typed precondition
            int param1 = stoi(row[3]);
            int param2 = stoi(row[4]);
            std::string property = row[5];
            std::string value = row[6];
            std::string op = row[7];
            std::string dir_str = row[8];

            DIRECTION_T dir;
            if(dir_str == "->") {
                dir = FORWARD_T;
            } else if (dir_str == "<-") {
                dir = BACKWARD_T;
            } else if (dir_str == "<->") {
                dir = BIDIRECTION_T;
            } else {
                std::cerr << "Unknown direction '" << dir_str << "'" << std::endl;
                exit(1);
            }

            ParameterizedTopology topo{param1,   param2, dir,
                                       property, op,     value}; //parameterized into a struct
            preconds_t.push_back(topo);
        }
    }

    std::tuple<std::vector<ParameterizedQuality>, std::vector<ParameterizedTopology>> tup{
        preconds_q, preconds_t};
    precond_map[curr_id] = tup;//the last exploit's preconditions (quality and topology) also needs to put in the unordered map

    return precond_map; //the unordered map use the exploit id as the key, the value of each item is the parameterized quality and topology
}

/**
 * @brief Fetches the postconditions of an Exploit from the database.
 */
std::unordered_map<
    int, std::tuple<std::vector<PostconditionQ>, std::vector<PostconditionT>>>
fetch_exploit_postconds() {
    std::vector<Row> rows = db.exec("SELECT * FROM exploit_postcondition;");

    std::unordered_map<
        int, std::tuple<std::vector<PostconditionQ>, std::vector<PostconditionT>>>
        postcond_map;

    int curr_id = -1;
    std::vector<PostconditionQ> postconds_q; //PostconditionQ and PostconditionT are defined in exploit.h
    std::vector<PostconditionT> postconds_t;
    for (auto &row : rows) {
        int type = stoi(row[2]);//type 0 change on quality, 1 change on topology(seldom)
        int exploit_id = stoi(row[1]);

        std::string action_str = row[9];
        ACTION_T action;

        // std::cout << action_str << "\n";

        if(action_str == "add" || action_str == "insert") {
            action = ADD_T;
        } else if (action_str == "update") {
            action = UPDATE_T;
        } else if (action_str == "delete") {
            action = DELETE_T;
        } else {
            std::cout << "Bad Action '" << action_str << "'" << std::endl;
            exit(1);
        }

        if (exploit_id != curr_id) {
            if (curr_id != -1) {
                std::tuple<std::vector<PostconditionQ>,
                      std::vector<PostconditionT>>
                    tup{postconds_q, postconds_t};
                postcond_map[curr_id] = tup;

                postconds_q.clear();
                postconds_t.clear();
            }

            curr_id = exploit_id;
        }

        if (type == 0) {
            int param1 = stoi(row[3]);
            std::string property = row[5];
            std::string value = row[6];

            ParameterizedQuality qual{param1, property, value};
            postconds_q.push_back(std::make_tuple(action, qual));
        } else {
            int param1 = stoi(row[3]);
            int param2 = stoi(row[4]);
            std::string property = row[5];
            std::string value = row[6];
            std::string op = row[7];
            std::string dir_str = row[8];

            DIRECTION_T dir;
            if(dir_str == "->") {
                dir = FORWARD_T;
            } else if (dir_str == "<-") {
                dir = BACKWARD_T;
            } else if (dir_str == "<->") {
                dir = BIDIRECTION_T;
            } else {
                std::cerr << "Unknown direction '" << dir_str << "'" << std::endl;
                exit(1);
            }

            ParameterizedTopology topo{param1,   param2, dir,
                                       property, op,     value};
            postconds_t.push_back(std::make_tuple(action, topo));
        }
    }

    std::tuple<std::vector<PostconditionQ>, std::vector<PostconditionT>> tup{
        postconds_q, postconds_t};
    postcond_map[curr_id] = tup;

    return postcond_map;
}

std::vector<Exploit> fetch_all_exploits() {
    std::vector<Exploit> exploits;
    std::vector<Row> rows = db.exec("SELECT * FROM exploit;");

    auto pre = fetch_exploit_preconds();
    auto post = fetch_exploit_postconds();

    for (auto &row : rows) {
        int id = std::stoi(row[0]);
        std::string name = row[1];
        int num_params = std::stoi(row[2]);

        auto preconds = pre[id];
        auto postconds = post[id];
        //Use Exploit class's obj exploit to store each exploit's complete info, especially pre-and-post conditions
        Exploit exploit(id, name, num_params, preconds, postconds);
        exploits.push_back(exploit);//push into exploits vector
    }

    return exploits; //the vector will be returned to the calling function.
}

/**
 * @brief Gets all of the qualities for the Asset
 * @details Grabs all of the qualities in the database associated with
 *          the Asset's ID and gives them to the Asset
 */
std::unordered_map<int, std::vector<Quality>> fetch_asset_qualities(Keyvalue &facts) {
    std::vector<Row> rows = db.exec("SELECT * FROM quality;");

    std::unordered_map<int, std::vector<Quality>> qmap;

    int curr_id = -1;
    std::vector<Quality> qualities;
    for (auto &row : rows) {
        int asset_id = std::stoi(row[0]);
        std::string property = row[1];
        std::string op = row[2];
        std::string value = row[3];

        if (asset_id != curr_id) {
            if (curr_id != -1) { //a new asset's quality has been reached
                qmap[curr_id] = qualities; //all the old qualities are put in the old asset's element in the unordered map 
                qualities.clear(); //clear the qualities for the new asset
            }
            curr_id = asset_id; //unconditional update curr_id to asset_id whenever a new asset is reached
        }
        // Quality qual(asset_id, property, "=", value);
        // qualities.push_back(qual);

        qualities.emplace_back(asset_id, property, op, value, facts);//each asset's qualities will be put in a dedicated Quality vector
    }

    qmap[curr_id] = qualities;//the last asset's qualities must be put in the unordered map too

    return qmap;
}

/**
 * @brief Gets all of the Assets under the network
 * @details Grabs all of the Assets in the database under the network given in
 *          the argument and returns a vector of those Assets
 *
 * @param network Name of the network to grab from
 */
std::vector<Asset> fetch_all_assets(Keyvalue &facts) {
    std::vector<Row> rows = db.exec("SELECT * FROM asset;");  
    std::vector<Asset> new_assets; //use class Asset (in asset.h) to define a vector, each element will be an object

    auto qmap = fetch_asset_qualities(facts); //combine each asset with all its qualities

    for (auto &row : rows) {
        int id = std::stoi(row[0]);
        std::string name = row[1];
        auto q = qmap[id]; 
        new_assets.emplace_back(name, q);
    }

    return new_assets;
}

std::vector<Quality> fetch_all_qualities(Keyvalue &facts) {
    std::vector<Quality> qualities;
    std::vector<Row> rows = db.exec("SELECT * FROM quality;");

    for (auto &row : rows) {
        int asset_id = std::stoi(row[0]);  
        std::string property = row[1];
        std::string op = row[2];
        std::string value = row[3];

        Quality qual(asset_id, property, op, value, facts);  
        qualities.push_back(qual);
    }

    return qualities;
}

std::vector<Topology> fetch_all_topologies(Keyvalue &facts) {
    std::vector<Topology> topologies;

    std::vector<Row> rows = db.exec("SELECT * FROM topology;");
    for (auto &row : rows) {
        int from_asset = std::stoi(row[0]);
        int to_asset = std::stoi(row[1]);
        std::string dir_str = row[2];

        DIRECTION_T dir;         
        if(dir_str == "->") {
            dir = FORWARD_T;
        } else if (dir_str == "<-") {
            dir = BACKWARD_T;
        } else if (dir_str == "<->") {
            dir = BIDIRECTION_T;
        } else {
            std::cerr << "Unknown direction '" << dir_str << "'" << std::endl;
            exit(1);
        }

        std::string property = row[3];
        std::string op = row[4];
        std::string value = row[5];

        Topology t(from_asset, to_asset, dir, property, op, value, facts); //associate each record from topology table with the facts
        topologies.push_back(t);
    }

    return topologies;
}

Keyvalue fetch_facts() { //Keyvalue is a class name(defined in Keyvalue.h), this function will return an Keyvalue obj
    Keyvalue initfacts;

    initfacts.populate(fetch_unique_values());

    return initfacts;
}

void save_ag_to_db(AGGenInstance &instance, bool save_keyvalue){
    std::vector<FactbaseItems>& factbase_items = instance.factbase_items;
    std::vector<Factbase>& factbases = instance.factbases;
    std::vector<Edge>& edges = instance.edges;
    Keyvalue& factlist = instance.facts;
    struct timeval t1,t2;

    //this part takes 0.3s
    gettimeofday(&t1,NULL);
    db.exec("BEGIN;");
    if (!factbases.empty()){
        printf("The size of the factbases is %ld\n",factbases.size());
        std::string factbase_sql_query = "INSERT INTO factbase VALUES ";

        for (int i = 0; i < factbases.size(); ++i) {
            if (i == 0) {
                factbase_sql_query += "(" + std::to_string(factbases[i].get_id()) +
                                      ",'" +
                                      std::to_string(factbases[i].hash(factlist)) + "')";
            } else {
                factbase_sql_query += ",(" + std::to_string(factbases[i].get_id()) +
                                      ",'" +
                                      std::to_string(factbases[i].hash(factlist)) + "')";
            }
        }
        factbase_sql_query += ";";
        db.execAsync(factbase_sql_query);	
    }
    db.execAsync("COMMIT;");
    if (!factbase_items.empty()) {
	int fis=factbase_items.size();
	for(int k=0;k<4;k++){	
        std::string item_sql_query = "INSERT INTO factbase_item VALUES ";
        std::string quality_sql_query = "";
        std::string topology_sql_query = "";
	int sql_index=0;

	for (int j = 0; j<fis/4+((k==3)?(fis%4):0); j++){
               auto fbi = factbase_items[j+k*(fis/4)];
            int id = std::get<1>(fbi);
            auto items = std::get<0>(fbi);
            auto quals = std::get<0>(items);
            auto topo = std::get<1>(items);
            for (auto qi : quals) {
                if (sql_index == 0)
                    quality_sql_query += "(" + std::to_string(id) + "," +
                                         std::to_string(qi.get_encoding()) +
                                         ",'quality')";

                else
                    quality_sql_query += ",(" + std::to_string(id) + "," +
                                         std::to_string(qi.get_encoding()) +
                                         ",'quality')";
                sql_index++;
            }

            for (auto ti : topo) {
                if (sql_index == 0)
                    topology_sql_query += "(" + std::to_string(id) + "," +
                                          std::to_string(ti.get_encoding()) +
                                          ",'topology')";

                else
                    topology_sql_query += ",(" + std::to_string(id) + "," +
                                          std::to_string(ti.get_encoding()) +
                                          ",'topology')";
                sql_index++;
            }
        }
	
        item_sql_query += quality_sql_query + topology_sql_query + ";";
	db.exec("BEGIN;");
        db.execAsync(item_sql_query);
	db.execAsync("COMMIT;");
	}
    }
    gettimeofday(&t2,NULL);
    printf("The saving of factbase and items took %lf ms\n",(t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_usec-t1.tv_usec)/1000.0);


    gettimeofday(&t1,NULL);
    if (!edges.empty()) {
        std::vector<std::string> edge_queries;
        edge_queries.resize(edges.size());
        std::transform(edges.begin(), edges.end(), edge_queries.begin(), to_query);//to_query is a unary operation on all the elements in edges. It is defined in db_function.
     
        struct timeval t3,t4;
        //---first way to build the map
        std::unordered_map<std::string, int> eq;
	gettimeofday(&t3,NULL);
        auto ei = edge_queries.begin(); //returns an iterator, not the 1st element!
        int j;
        for (j = 0; ei != edge_queries.end(); j++, ei++){ 	
            eq.insert({*ei, j});
	}

        	std::vector<std::string> unique_eq;
	int unique_idx[eq.size()];
	int jj=0;
	for(auto ei: eq) {
	    unique_eq.push_back(ei.first);
	    unique_idx[jj]=ei.second;
	    jj++;
	}
	gettimeofday(&t4,NULL);
    	

	struct timeval t5,t6;
	gettimeofday(&t5,NULL);
	for(int k=0;k<2;k++)
	{
        std::string edge_sql_query = "INSERT INTO edge VALUES ";
        std::string edge_assets_sql_query = "INSERT INTO edge_asset_binding VALUES ";
        for(int i=0;i<(jj/2)+((k==1)?(jj%2):0);i++){
	    int idx=unique_idx[i+k*(jj/2)];
	    int eid = edges[idx].get_id();
            if(i==0){
	    	edge_sql_query += "(" + std::to_string(eid) + "," + unique_eq[i+k*(jj/2)];
                edge_assets_sql_query += edges[idx].get_asset_query();
	    }
	    else{
                edge_sql_query += ",(" + std::to_string(eid) + "," + unique_eq[i+k*(jj/2)];
                edge_assets_sql_query += "," + edges[idx].get_asset_query();		
	    }
	}	
        edge_sql_query += ";";
        edge_assets_sql_query += ";";
        db.exec("BEGIN;");
        db.execAsync(edge_sql_query);//33.7s
        db.execAsync(edge_assets_sql_query); //7.6s
	db.execAsync("COMMIT;");//this part only takes 0.5ms
        }
	gettimeofday(&t6,NULL);
	}
    gettimeofday(&t2,NULL);
    printf("The saving of edge and edge_asset_binding took %lf ms\n",(t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_usec-t1.tv_usec)/1000.0);//42.0s

    gettimeofday(&t1,NULL);
    db.exec("BEGIN;");
    int cnt1=0;
    if (save_keyvalue) {
        std::ostringstream out;
        out << "INSERT INTO keyvalue VALUES ";
        std::vector<std::string> keyvalue_vector = factlist.get_str_vector();
        size_t count = 0;
        for(auto &value : keyvalue_vector) {
            if(count == 0)
                out << "(" << std::to_string(count++) << ",'" << value << "')";
            else
                out << ",(" << std::to_string(count++) << ",'" << value << "')";
            cnt1=cnt1+1;
        }
        out << ";";
        db.execAsync(out.str());
    }
    db.execAsync("COMMIT;");
    gettimeofday(&t2,NULL);
    printf("The saving of keyvalue took %lf ms\n",(t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_usec-t1.tv_usec)/1000.0);
}
