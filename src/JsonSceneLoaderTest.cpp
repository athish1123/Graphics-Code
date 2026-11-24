#include "JsonSceneLoader/SceneLoader.h"
#include "JsonSceneLoader/SceneParser_JSON.h"

#include <filesystem>

int main(int argc, char* argv[]) {
    constexpr int width = 1000;
    constexpr int height = 1000;

    std::filesystem::path sceneFile = "scene.json";
    if (!std::filesystem::exists(sceneFile) && argc > 0) {
        const auto executableSceneFile =
            std::filesystem::path(argv[0]).parent_path() / "scene.json";
        if (std::filesystem::exists(executableSceneFile)) {
            sceneFile = executableSceneFile;
        }
    }

    if (!std::filesystem::exists(sceneFile)) {
        std::cerr << "Could not find scene.json in the current directory or next to the executable.\n";
        return 1;
    }

    Scene scene(nullptr, Framebuffer(width, height));

    auto loader = std::make_shared<SceneLoader>(scene, width, height);
    SceneParser_JSON parser(loader);

    parser.parseFileData(sceneFile.string());

    if (!scene.cam) {
        std::cerr << "The JSON file did not create a camera.\n";
        return 1;
    }

    scene.render("scene-output.png");
    std::cout << "Rendered scene to scene-output.png\n";
    return 0;
}