#include "surface.h"

std::optional<HitRecord> Group::intersect(Ray &ray) const {
    bool hit_something = false;
    HitRecord hit;
    for( auto & surf : surfaces ) {
        std::optional<HitRecord> hit_info = surf->intersect(ray);
        if( hit_info ) {
            hit_something = true;
            hit = *hit_info;
            ray.maxt = hit_info->t;
        }
    }
    if( hit_something ) return {hit};
    return {};
}
