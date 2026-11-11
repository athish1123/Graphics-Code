#include "JsonSceneLoader/SceneLoader.h"
#include "JsonSceneLoader/SceneParser_JSON.h"

int main(int argc, char *argv[]) {
    constexpr int width = 500;
    constexpr int height = 500;

    Scene scene(nullptr, Framebuffer(width, height));

    auto loader = std::make_shared<SceneLoader>(scene, width, height);
    SceneParser_JSON parser(loader);

    // use the argv[1] for the scene
    parser.parseFileData( argv[1] );

    if (!scene.cam) {
        std::cerr << "The JSON file did not create a camera.\n";
        return 1;
    }

    scene.render("scene-output.png");
    std::cout << "Rendered scene to scene-output.png\n";
    return 0;
}
