#include <iostream>
#include "WordQuery.h"
#include "OrQuery.h"
#include "AndQuery.h"
#include "NotQuery.h"

int main() {
    std::string filename = R"(E:\code\CLionProjects\TextQuery\test.txt)";
    std::ifstream infile(filename);
    TextQuery source = TextQuery(infile);
    Query query1 = (Query("hello") | Query("world")) & Query("china");
    QueryResult result = query1.eval(source);
    print(std::cout, result);

    query1 = Query("china");
    result = query1.eval(source);
    print(std::cout, result);

    return 0;
}
