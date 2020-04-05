
#include <json.hpp>

using json = nlohmann::json;

/*
JSON TIPS:
SIEMPRE METER LOS VALORES DEL JSON EN UNA VARIABLE!
*/

//abrir el json a pelo
std::ifstream i("assets/json.json");
json j;
i >> j;

//puedes hacer esto
std::string aux = j["hola"];
std::cout << aux << '\n';
//o esto
std::cout << j["componente"]["nombre"].get<std::string>() << '\n';

std::cout << j["muerto"] << '\n';

std::cout << j["componente"]["posicion"]["x"].get<double>() << '\n';
std::cout << j["componente"]["posicion"]["y"].get<double>() << '\n';
std::cout << j["componente"]["posicion"]["z"].get<double>() << '\n';

std::cout << j["componente"]["color"].get<std::string>() << '\n';
std::cout << j["componente"]["ignacio"].get<std::string>() << '\n';
