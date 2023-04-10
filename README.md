# Database-Postgres-CPP

This project creates a PostgreSQL database and implements:
1. A C++ program to read text files containing the entries (rows) for each table, and build
the database by creating each table and adding entries.
2. A C++ library (set of functions) which will provide an interface for a program to interact
with the database (e.g. add rows to the tables and query for certain information).

The database relates to ACC basketball teams, and will allow queries to discover information
about things like player statistics, team attributes, etc. The database will have 4 tables, specified
as follows:
1. PLAYER (PLAYER_ID, TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG,
RPG, APG, SPG, BPG)
2. TEAM (TEAM_ID, NAME, STATE_ID, COLOR_ID, WINS, LOSSES)
3. STATE (STATE_ID, NAME)
4. COLOR (COLOR_ID, NAME)

*Note the following abbreviations: MPG = minutes per game, PPG = points per game, RPG =
rebounds per game, APG = assists per game, SPG = steals per game, BGP = blocks per game
