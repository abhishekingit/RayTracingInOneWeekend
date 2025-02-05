# Fun with RayTracing

### Generating a ppm image

<img alt="image.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convImage.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" height="512px">

Generating a basic Portable Pixmap file and used ImageMagick to convert to png

### Generating a linearly blended gradient by sending rays into the scene

<img alt="RTgradient.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convRtGradient.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" height="512px">

Sending rays into the scene and using lerp for blend creating a gradient (Tweaked some values myself in rayColor to create this indigo-green gradient)

### Ray and Sphere Intersection

<img alt="RTSphere.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convRtSphere.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" height="512px">

A rudimentary image of Ray and Sphere Intersection without shading and reflection (Color separation logic in rayColor is based on discriminant of the equation for Ray and Sphere for a common 't')

### Surface Normals and Shaded Sphere

<img alt="ShadedSphere.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convShadedSphere.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" height="512px">

Adding surface normals for the sphere and computing the hit points of the ray and calculating surface normals and color mapping it

### Adding abstraction for world objects 

<img alt="World.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convWorldImage.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" height="512px">

Creating abstractions for objects in the world and some more abstractions

### Adding Antialiasing and generating a high definition image

<img alt="antiAliased.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convAntiAliased.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" width="1024" height="576px">

Using Localized supersampling for anti aliasing. Also tried a higher resolution (1920 x 1080) for this image
Given that a PPM file is inefficient due to its large size caused by uncompressed pixel data, and that the book uses this format to generate the image because it is simple to create, there is some potential to parallelize the render loop to make this approach faster for high-resolution images.  

### Diffused Materials by generating random hemisphere vectors

<img alt="diffusedmaterial.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convDiffuseMaterial.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" height="512px">

Generating random hemisphere vectors

### Lambertian distribution

<img alt="scatteringComparison.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/scatteringComparison.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" height="512px">

Non uniform scattering of rays or Lambertian distribution (R) and uniform scattering (L)
The result on the right is a much accurate representation of diffuse reflection. It also has a tint of the background gradient consisting of blue and white.

### Gamma correction 

<img alt="gammaCorrected.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convGammaImage.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" height="512px">

Basic gamma transform

### Materials and rendering Reflections

<img alt="materials.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convMaterialSpheres.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" width="1024" height="576px">

Materials are classes in the raytracer program with each having a unique scatter method and an albedo value(this determines the attenuation or strength of the scattered ray color, dark materials will absorb most of the light while white materials will reflect most of the light)
In this image there are 2 material types diffuse and metal. The high definition image shows a very clean reflection of the blue sphere as of now. 

### Adding Fuzziness in Reflection

<img alt="fuzzSpheres.png" src="https://github.com/abhishekingit/RayTracingInOneWeekend/blob/main/outputImages/convFuzzRef.png?raw=true" data-hpc="true" class="Box-sc-g0xbh4-0 kzRgrI" width="1024" height="576px">

Fuzziness is a quality of specific materials which we see in real life. Like metals dont usually have a clean reflection like a glass/mirror but rather this blurred reflection. In this program we are just specifying the fuzziness of the material in main and based on that we are multiplying this fuzz factor with a random unit vector and adding to our normalised reflected ray.
