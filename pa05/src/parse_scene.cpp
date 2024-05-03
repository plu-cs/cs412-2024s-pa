#include "scene.h"
#include "materiallib.h"
#include "sphere.h"
#include "quad.h"

void Scene::parse_scene( const json & j ) {
    num_samples = j.value("num_samples", num_samples);
    background = j.value("background", background);

    if(! j.contains("camera") ) {
        throw LutertParseException("Scene must include a camera");
    }

    // Parse camera
    camera = std::make_shared<Camera>(j["camera"] );

    // Materials
    if( j.contains("materials") ) MaterialLib::load(j["materials"]);

    // Surfaces
    surfaces = std::make_shared<Group>();

    if( j.contains("surfaces") ) {
        if( !j["surfaces"].is_array() ) throw LutertParseException("surfaces should be an array");

        for( const auto & jsurf : j["surfaces"] ) {
            if( !jsurf.contains("type") ) throw LutertParseException("Surface found without type");
            std::string type = jsurf["type"];
            std::shared_ptr<Surface> surf = nullptr;
            if( type == "sphere" ) {
                surf = std::make_shared<Sphere>(jsurf);
            } else if( type == "quad" ) {
                surf = std::make_shared<Quad>(jsurf);
            } else {
                throw LutertParseException(fmt::format("Surface type '{}' not recognized", type));
            }
            surfaces->add(surf);
        }
    }
}