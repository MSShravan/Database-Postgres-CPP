#include <pqxx/pqxx>
#include "query_funcs.h"

using namespace pqxx;

void drop_tables(connection *C);

void create_tables(connection *C);

void insert_records(connection *C);
