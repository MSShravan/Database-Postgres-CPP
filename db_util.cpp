#include "db_util.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void run_query(connection *C, const std::string &query) {
    work txn{*C};

    try {
        txn.exec(query.c_str());
        txn.commit();
    } catch (std::exception const &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        throw;
    }

}

void drop_tables(connection *C) {
    std::string drop_query = "DROP TABLE IF EXISTS ";
    run_query(C, drop_query + "player");
    run_query(C, drop_query + "team");
    run_query(C, drop_query + "state");
    run_query(C, drop_query + "color");
}

void create_tables(connection *C) {
    std::string color_query = "CREATE TABLE color ("
                              "color_id SERIAL NOT NULL, "
                              "name TEXT, "
                              "CONSTRAINT clridpk PRIMARY KEY (color_id))";
    std::string state_query = "CREATE TABLE state ("
                              "state_id SERIAL NOT NULL, "
                              "name TEXT, "
                              "CONSTRAINT stidpk PRIMARY KEY (state_id))";
    std::string team_query = "CREATE TABLE team ("
                             "team_id SERIAL NOT NULL, "
                             "name TEXT, "
                             "state_id INT, "
                             "color_id INT, "
                             "wins INT, "
                             "losses INT, "
                             "CONSTRAINT tmidpk PRIMARY KEY (team_id), "
                             "CONSTRAINT stidfk FOREIGN KEY (state_id) REFERENCES state(state_id) ON DELETE SET NULL ON UPDATE CASCADE, "
                             "CONSTRAINT clridfk FOREIGN KEY (color_id) REFERENCES color(color_id) ON DELETE SET NULL ON UPDATE CASCADE)";
    std::string player_query = "CREATE TABLE player ("
                               "player_id SERIAL NOT NULL, "
                               "team_id INT, "
                               "uniform_num INT, "
                               "first_name TEXT, "
                               "last_name TEXT, "
                               "mpg INT, "
                               "ppg INT, "
                               "rpg INT, "
                               "apg INT, "
                               "spg REAL, "
                               "bpg REAL, "
                               "CONSTRAINT plyridpk PRIMARY KEY (player_id), "
                               "CONSTRAINT tmidfk FOREIGN KEY (team_id) REFERENCES team(team_id) ON DELETE SET NULL ON UPDATE CASCADE)";

    run_query(C, color_query);
    run_query(C, state_query);
    run_query(C, team_query);
    run_query(C, player_query);
}

void parseRecord(const std::string &record, std::vector<std::string> &words) {
    std::string word;
    std::stringstream stringStream(record);

    bool skipFirst = true;
    while (stringStream >> word) {
        if (!skipFirst)
            words.push_back(word);
        skipFirst = false;
    }
}

void insert_record(connection *C, const std::string &tableName, const std::vector<std::string> &values) {
    if (tableName == "color") {
        add_color(C, values[0]);
    } else if (tableName == "state") {
        add_state(C, values[0]);
    } else if (tableName == "team") {
        add_team(C,
                 values[0],
                 std::stoi(values[1]),
                 std::stoi(values[2]),
                 std::stoi(values[3]),
                 std::stoi(values[4]));
    } else if (tableName == "player") {
        add_player(C,
                   std::stoi(values[0]),
                   std::stoi(values[1]),
                   values[2],
                   values[3],
                   std::stoi(values[4]),
                   std::stoi(values[5]),
                   std::stoi(values[6]),
                   std::stoi(values[7]),
                   std::stod(values[8]),
                   std::stod(values[9]));
    }
}

void insert_records(connection *C, const std::string &filename, const std::string &tableName) {
    std::ifstream fColor(filename, std::ifstream::in);
    if (fColor.is_open()) {
        std::string line;
        while (std::getline(fColor, line)) {
            std::vector<std::string> values;
            parseRecord(line, values);
            insert_record(C, tableName, values);
        }
        fColor.close();
    }
}

void insert_records(connection *C) {
    insert_records(C, "color.txt", "color");
    insert_records(C, "state.txt", "state");
    insert_records(C, "team.txt", "team");
    insert_records(C, "player.txt", "player");
}
