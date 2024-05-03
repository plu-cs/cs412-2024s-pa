#pragma once

#include "material.h"
#include "json.h"

/**
 * Library of materials indexed by name
 */
namespace MaterialLib {
    void load(const json & j = json::object());
    std::shared_ptr<Material> find( const std::string & name );
};