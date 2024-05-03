#include "scene.h"
#include "progressbar.h"
#include "random.h"
#include "material.h"

Image Scene::render() const {
    // allocate an image of the proper size
    auto image = Image(camera->get_resolution().x, camera->get_resolution().y);

    {
        ProgressBar progress(image.width() * image.height());   // To provide render progress feedback

        // =========================== TASK 8 =====================================================
        // TODO: Render the image, similar to task 7, except that you will now compute a random
        //   location within each pixel for each ray.
        //
        // Pseudo-code:
        //
        // foreach image row (go over image height)
        //     foreach pixel in the row (go over image width)
        //         init accumulated color to zero
        //         repeat num_samples times:
        //             compute a random point within the pixel (you can just add a random number between 0 and 1
        //                                                      to the pixel coordinate. You can use next_float() for
        //                                                      this)
        //             compute camera ray
        //             accumulate color raytraced with the ray (by calling recursive_color)
        //         divide color by the number of pixel samples
        //         write the average color to the image
        //         update the progress bar (++progress)
        //
    }

    // return the ray-traced image
    return image;
}

Color3f Scene::recursive_color( Ray & ray, int depth ) const {
    constexpr int max_depth = 64;
  
    // =========================== TASK 8 =====================================================
    // TODO: Recursively raytrace the scene, similar to the code you wrote in task 7
    //       The only difference is that you should also take into account surfaces 
    //       that are self-emitting
    //       To test for intersection against all objects in the scene, use the `surfaces`
    //       variable, which is a Group of Surfaces, and will test the ray against all 
    //       surfaces in the scene.
    //
    // Pseudo-code:
    //
    // if surfaces->intersect(..) is successful:
    //      get emitted color (hint: you can use hit.material->emitted)
    // 		if depth < max_depth and hit.material->scatter(....) is successful:
    //			recursive_color = call this function recursively with the scattered ray and increased depth
    //          return emitted color + attenuation * recursive_color
    //		else
    //			return emitted color;
    // else:
    // 		return background color (variable `background`)
    //

    return {0,0,0};  // Replace this
}
