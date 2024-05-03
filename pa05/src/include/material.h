#pragma once

#include "common.h"
#include "hitrecord.h"
#include "json.h"

class Ray;

/**
 * Struct used to return information about a scattering event.
*/
struct ScatterInfo {
    Vec3f attenuation;  ///< Ratio of light that is absorbed by the material
    Ray scattered;      ///< The scattered ray 

    ScatterInfo() = default;
};

/**
 * Base class for materials.
 */
class Material {
public:
    virtual ~Material() = default;

    /**
     * Compute the scattered direction at a given hitpoint.
     *
     * @param r the incoming ray
     * @param hit information about the intersection
     * @return true if the light is scattered
     */
    virtual std::optional<ScatterInfo> scatter( const Ray & r, const HitRecord & hit ) const {
        return {};
    }

    /**
     * @returns whether this material emits light
    */
    virtual bool is_emissive() const { return false; }

    /**
     * Returns the color emitted by this material, if it is emissive.
     * 
     * @param ray the Ray that intersected the surface
     * @param hit information about the intersection
    */
    virtual Color3f emitted(const Ray & ray, const HitRecord & hit ) const { return {0,0,0}; }
};

class Lambertian : public Material {
public:
    explicit Lambertian( const json & j = json::object() ) {
        albedo = j.value("albedo", albedo);
    }

    std::optional<ScatterInfo> scatter( const Ray & r, const HitRecord & hit ) const override;

    Vec3f albedo = Vec3f{1,1,1}; ///< Base reflective color (fraction of reflected light)
};

class Metal : public Material {
public:
    explicit Metal( const json &j = json::object() ) {
        albedo = j.value("albedo", albedo);
        roughness = j.value("roughness", roughness);
    }

    std::optional<ScatterInfo> scatter( const Ray & r, const HitRecord & hit ) const override;

    Vec3f albedo = Vec3f{1,1,1}; ///< Base reflective color (fraction of reflected light)
    float roughness = 0.0;       ///< Surface roughness
};

class Dielectric : public Material {
public:
    explicit Dielectric( const json &j = json::object() ) {
        ior = j.value("ior", ior);
    }

    std::optional<ScatterInfo> scatter( const Ray & r, const HitRecord & hit ) const override;

    float ior = 1.0f;   ///< Index of refraction
};

class Light : public Material {
public:
    explicit Light( const json & j = json::object() ) {
        power = j.value("power", power);
    }

    bool is_emissive() const { return true; }
    
    Color3f emitted(const Ray & ray, const HitRecord & hit) const {
        // Only emit from the outward facing side
        if( dot(ray.d, hit.sn) < 0 ) return power;
        return {0,0,0};
    }

    Color3f power = {1,1,1};
};