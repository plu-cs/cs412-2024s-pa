#include "materiallib.h"

namespace MaterialLib {
    std::unordered_map<std::string, std::shared_ptr<Material>> materials;

    void load(const json & j) {
        if( ! j.is_array() ) throw LutertParseException("materials property must be an array");
        for( auto & jmat : j ) {
            if( !jmat.contains("type") ) throw LutertParseException("Material found without type");
            if( !jmat.contains("name") ) throw LutertParseException("Material found without name");
            std::string name = jmat["name"];

            // Check for duplicates
            if( materials.find(name) != materials.end() ) {
                throw LutertParseException(fmt::format("Duplicate material names in input: {}", name));
            }

            std::string type = jmat["type"];
            std::shared_ptr<Material> mat = nullptr;
            if( type == "lambertian" ) {
                mat = std::make_shared<Lambertian>(jmat);
            } else if( type == "metal") {
                mat = std::make_shared<Metal>(jmat);
            } else if( type == "dielectric" ) {
                mat = std::make_shared<Dielectric>(jmat);
            } else if( type == "light" ) {
                mat = std::make_shared<Light>(jmat);
            } else {
                throw LutertParseException(fmt::format("Unrecognized material type: {}", type));
            }

            materials[name] = mat;
        }
    }

    std::shared_ptr<Material> find( const std::string & name ) {
        auto value = materials.find(name);
        if( value == materials.end() )
            throw LutertException(fmt::format("No material named '{}'", name));
        return value->second;
    }
}