#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg) {
    work txn{*C};
    try {
        txn.exec(
                "INSERT INTO player (team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg) "
                "VALUES (" +
                txn.quote(team_id) + ", " +
                txn.quote(jersey_num) + ", " +
                txn.quote(first_name) + ", " +
                txn.quote(last_name) + ", " +
                txn.quote(mpg) + ", " +
                txn.quote(ppg) + ", " +
                txn.quote(rpg) + ", " +
                txn.quote(apg) + ", " +
                txn.quote(spg) + ", " +
                txn.quote(bpg) +
                ")");
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses) {
    work txn{*C};
    try {
        txn.exec("INSERT INTO team (name, state_id, color_id, wins, losses) "
                 "VALUES (" +
                 txn.quote(name) + ", " +
                 txn.quote(state_id) + ", " +
                 txn.quote(color_id) + ", " +
                 txn.quote(wins) + ", " +
                 txn.quote(losses) +
                 ")");
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void add_state(connection *C, string name) {
    work txn{*C};
    try {
        txn.exec("INSERT INTO state (name) "
                 "VALUES (" + txn.quote(name) + ")");
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void add_color(connection *C, string name) {
    work txn{*C};
    try {
        txn.exec("INSERT INTO color (name) "
                 "VALUES (" + txn.quote(name) + ")");
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

/*
 * All use_ params are used as flags for corresponding attributes
 * a 1 for a use_ param means this attribute is enabled (i.e. a WHERE clause is needed)
 * a 0 for a use_ param means this attribute is disabled
 */
void query1(connection *C,
            int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
) {
    work txn{*C};
    try {
        bool isAnd = false;
        std::string query = "SELECT * FROM player ";
        std::string where = "WHERE ";
        if (use_mpg == 1) {
            where += "mpg>=" + txn.quote(min_mpg) + " AND mpg<=" + txn.quote(max_mpg);
            isAnd = true;
        }
        if (use_ppg == 1) {
            if (isAnd) {
                where += " AND ";
            }
            where += "ppg>=" + txn.quote(min_ppg) + " AND ppg<=" + txn.quote(max_ppg);
            isAnd = true;
        }
        if (use_rpg == 1) {
            if (isAnd) {
                where += " AND ";
            }
            where += "rpg>=" + txn.quote(min_rpg) + " AND rpg<=" + txn.quote(max_rpg);
            isAnd = true;
        }
        if (use_apg == 1) {
            if (isAnd) {
                where += " AND ";
            }
            where += "apg>=" + txn.quote(min_apg) + " AND apg<=" + txn.quote(max_apg);
            isAnd = true;
        }
        if (use_spg == 1) {
            if (isAnd) {
                where += " AND ";
            }
            where += "spg>=" + txn.quote(min_spg) + " AND spg<=" + txn.quote(max_spg);
            isAnd = true;
        }
        if (use_bpg == 1) {
            if (isAnd) {
                where += " AND ";
            }
            where += "bpg>=" + txn.quote(min_bpg) + " AND bpg<=" + txn.quote(max_bpg);
            isAnd = true;
        }
        if (isAnd) {
            query += where;
        }

        pqxx::result r{txn.exec(query)};
        cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
        for (auto values: r) {
            for (int i = 0; i < 9; i++) {
                cout << values[i].c_str();
                cout << " ";
            }
            stringstream sstream;
            sstream << setprecision(1) << fixed << values[9].as<double>() << " " << values[10].as<double>();
            cout << sstream.str() << endl;
        }
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void query2(connection *C, string team_color) {
    work txn{*C};
    try {
        pqxx::result r{txn.exec("SELECT team.name "
                                "FROM team, color "
                                "WHERE team.color_id=color.color_id "
                                "AND color.name=" + txn.quote(team_color))};
        cout << "NAME" << endl;
        for (auto values: r) {
            cout << values[0].c_str() << endl;
        }
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void query3(connection *C, string team_name) {
    work txn{*C};
    try {
        pqxx::result r{txn.exec(
                "SELECT player.first_name, player.last_name "
                "FROM player, team "
                "WHERE player.team_id=team.team_id "
                "AND team.name=" + txn.quote(team_name) +
                " ORDER BY player.ppg DESC")};
        cout << "FIRST_NAME LAST_NAME" << endl;
        for (auto values: r) {
            cout << values[0].c_str() << " " << values[1].c_str() << endl;
        }
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void query4(connection *C, string team_state, string team_color) {
    work txn{*C};
    try {
        pqxx::result r{txn.exec(
                "SELECT player.uniform_num, player.first_name, player.last_name "
                "FROM player, team, state, color "
                "WHERE player.team_id=team.team_id "
                "AND team.state_id=state.state_id "
                "AND team.color_id=color.color_id "
                "AND state.name=" + txn.quote(team_state) +
                " AND color.name=" + txn.quote(team_color))};
        cout << "UNIFORM_NUM FIRST_NAME LAST_NAME" << endl;
        for (auto values: r) {
            cout << values[0].c_str() << " " << values[1].c_str() << " " << values[2].c_str() << endl;
        }
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void query5(connection *C, int num_wins) {
    work txn{*C};
    try {
        pqxx::result r{txn.exec("SELECT player.first_name, player.last_name, team.name, team.wins "
                                "FROM player, team "
                                "WHERE player.team_id=team.team_id "
                                "AND team.wins>" + txn.quote(num_wins))};
        cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
        for (auto values: r) {
            cout << values[0].c_str() << " " << values[1].c_str() << " " << values[2].c_str() << " "
                 << values[3].c_str() << endl;
        }
        txn.commit();
    } catch (exception const &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}
