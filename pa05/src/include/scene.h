#pragma once

#include <memory>

#include "surface.h"
#include "camera.h"
#include "image.h"

class Scene {
public:
    Scene() = default;
    explicit Scene( const json & j ) { parse_scene(j); }
    Image render() const;
    int samples() { return num_samples; }

private:
    void parse_scene( const json & j );
    Color3f recursive_color( Ray & ray, int depth ) const;

    std::shared_ptr<Group> surfaces;
    std::shared_ptr<Camera> camera;
    int num_samples = 1;
    Color3f background = {0,0,0};
};