#include "camera.h"
#include "json.h"

Camera::Camera(const json &j) {
    xform      = j.value("transform", xform);
    resolution = j.value("resolution", resolution);
    focal_dist = j.value("focal_dist", focal_dist);
    float vfov = j.value("vfov", 80.0f);

    // ============= TASK 2 - Step 1 ================================================
    // TODO: Compute the size (width and height)
    //   of the image plane and store the dimensions in the instance variable
    //   named image_plane_size.  Use the vertical field of view angle vfov.
    //   The angle is given in degrees, so you will need to convert to radians
    //   before using with trig functions.  You can use the function deg2rad(..)
    //   defined in "common.h".  Note that the aspect ratio can be determined from
    //   the variable resolution, and the focal distance is stored in focal_dist.
    
}

Ray Camera::generate_ray(const Vec2f &sample) const {
    Vec3f ray_origin;
    Vec3f ray_direction;

    // ============= TASK 2 - Step 2 ================================================
    // TODO: Given the location on the image plane in pixel coordinates,
    //   `sample`, compute and return the camera ray that starts at the origin
    //   and passes through that position on the image plane.


    return {ray_origin, ray_direction};  // This returns a Ray object constructed with these values
    // ------  TASK 4 ------------
    // TODO: Return a ray that is transformed into world coordinates 
}