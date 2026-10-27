#pragma once

#include "../Camera/perspective_camera.h"
#include "../Light/light.h"
#include "../Shape/scene.h"
#include "../Shape/sphere.h"
#include "../Shape/triangle.h"
#include "../Shader/lambertian_shader.h"
#include "../Shader/mirror_shader.h"

#include <iostream>
#include "ISceneLoader.h"

class SceneLoader : public ISceneLoader {
private:
  Scene &m_targetScene; // Reference to the external scene
  int m_imageWidth, m_imageHeight;
  
  std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
  

public:
  // The caller provides the scene to be filled
  SceneLoader(Scene &sceneToPopulate, int imageWidth, int imageHeight) : 
    m_targetScene(sceneToPopulate),
    m_imageWidth(imageWidth), 
    m_imageHeight(imageHeight) {}

    
  // SceneLoader(Scene &sceneToPopulate) : m_targetScene(sceneToPopulate), numShaders(0), numTextures(0) {}

  void reserveCameras(size_t count) override {
    // makes sure the vector has enough space
    if (count > 1)
    {
      throw std::runtime_error("This render supports only one camera for now");
    }
    // m_targetScene.cameras.reserve(count);
  }

  void reserveLights(size_t count) override {
    m_targetScene.lights.reserve(count);
  }

  void reserveShapes(size_t count) override {
    m_targetScene.shapes.reserve(count);
  }

  void reserveShaders(size_t count) override { numShaders = count; }
  void reserveTextures(size_t count) override { numTextures = count; }
  
  void setSceneParams(const SceneParams &sparams) override 
  {
    std::cout << "Setting scene params." << std::endl;
    const Color background
    (
      sparams.bgColor.x,
      sparams.bgColor.y,
      sparams.bgColor.z
    );

    m_targetScene.set_background_gradient(background,background); //FIX THIS
  }

  void addCamera(
    const std::string &name, 
    const std::string &type,
    const ISceneLoader::vec &pos, 
    const ISceneLoader::vec &viewDir,
    float focalLength, 
    float imagePlaneWidth) override 
    {
      // std::cout << "Creating camera: " << name << ", type:" << type << std::endl;
      // auto cam = std::make_shared<Camera>();
      // cam->type = type;
      // m_targetScene.cameras.push_back(cam);

      auto camera = std::make_shared<PerspectiveCamera>
      (
        Vec3(pos.x, pos.y, pos.z),
        Vec3(viewDir.x, viewDir.y, viewDir.z),
        focalLength,
        imagePlaneWidth,
        m_imageWidth,
        m_imageHeight
      );
      camera->type = type;
      m_targetScene.cam = camera;
    }


  void addPointLight(
    const ISceneLoader::vec &pos,
    const ISceneLoader::vec &intensity) override 
    {
      std::cout << "Creating point light." << std::endl;
      auto light = std::make_shared<Light>(
        Vec3(pos.x, pos.y, pos.z),
        Color(intensity.x, intensity.y, intensity.z)
      );
      
      light->type = "Point_Light";
      m_targetScene.add_light(light);
    }


    void addAreaLight(
      const ISceneLoader::vec &pos,
      const ISceneLoader::vec &color,
      const ISceneLoader::vec &normal, float width,
      float length) override 
      {
        // std::cout << "Creating area light." << std::endl;
        throw std::runtime_error("Textures are not implemented by this renderer.");
      }


  void addShader(const ISceneLoader::ShaderDesc &shaderDesc) override 
  {
    std::cout << "Creating shader: type=" << shaderDesc.type << std::endl;
    // I place my shaders on an unordered map often
    if(shaderDesc.type == "Lambertian" || shaderDesc.type == "Diffuse")
    {
      m_shaders[shaderDesc.name] = std::make_shared<LambertianShader>
      (
        Color(
          shaderDesc.diffuse.data.x,
          shaderDesc.diffuse.data.y,
          shaderDesc.diffuse.data.z
        )
      );
      return;
    }

    if(shaderDesc.type == "Mirror")
    {
      m_shaders[shaderDesc.name] = std::make_shared<MirrorShader>(Color::white());
      return;
    }

    throw std::runtime_error("Unsupported shader type: " + shaderDesc.type);
  }
  
  void addShape(const ISceneLoader::ShapeDesc &shapeDesc) override 
  {
    std::cout << "Creating shape: type=" << shapeDesc.type << std::endl;
    
    const auto shaderIt = m_shaders.find(shapeDesc.shaderNameReference);

    if (shaderIt == m_shaders.end())
    {
      throw std::runtime_error("Shape '" + shapeDesc.name + "' references unknown shader '" + shapeDesc.shaderNameReference + "'.");
    }

    if(shapeDesc.hasXForm)
    {
      throw std::runtime_error("Shape transforms are not implemented by this renderer.");
    }

    if (shapeDesc.type == "sphere")
    {
      m_targetScene.add_shape(std::make_shared<Sphere>
      (
        Vec3(shapeDesc.center.x, shapeDesc.center.y, shapeDesc.center.z), 
        shapeDesc.radius,
        shaderIt->second
      ));

      return;
    }
    
    if(shapeDesc.type == "triangle")
    {
      m_targetScene.add_shape(std::make_shared<Triangle>(
        Vec3(shapeDesc.v0.x, shapeDesc.v0.y, shapeDesc.v0.z),
        Vec3(shapeDesc.v1.x, shapeDesc.v1.y, shapeDesc.v1.z),
        Vec3(shapeDesc.v2.x, shapeDesc.v2.y, shapeDesc.v2.z),
        shaderIt->second
      ));
      return;
    }

    throw std::runtime_error("Unsupported shape type: " + shapeDesc.type);
  }

  void addTexture(
    const std::string &type, const std::string &name,
    const std::string &sourceFile) override 
    {
      // std::cout << "Creating texture: type=" << type << ", name=" << name << ", sourceFile=" << sourceFile << std::endl;
      throw std::runtime_error("Textures are not implemented by this renderer.");
    }

public:
  int numShaders;
  int numTextures;

};
