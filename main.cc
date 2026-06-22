#include <crow.h>
#include <string>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/get_json")([]{
        crow::json::wvalue response;

        response["success"] = true;
        response["message"] = "Data great downlode";
        response["status_code"] = 200;
        response["rating"] = 4.8;

        response["tags"] = crow::json::wvalue::list({"c++", "crow", "backend"});

        response["author"]["name"] = "Ivan";
        response["author"]["role"] = "Developer";

        return response;
    });

    CROW_ROUTE(app, "/post_json").methods(crow::HTTPMethod::POST)([](const crow::request& req){
        crow::json::rvalue request_data = crow::json::load(req.body);

        if (!request_data) {
            return crow::response(400, "Error: Invalid JSON payload");
        }

        if (!request_data.has("username") || !request_data.has("age")) {
            return crow::response(400, "Error: Username or age fields are missing");
        }

        std::string name = request_data["username"].s();
        int age = request_data["age"].i();

        crow::json::wvalue response_data(request_data);
        response_data["status"] = "processed";
        response_data["next_year_age"] = age + 1;

        return crow::response(response_data);
    });

    app.port(18080)
        .multithreaded()
        .run();
}
