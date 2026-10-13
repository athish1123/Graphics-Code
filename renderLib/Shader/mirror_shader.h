#ifndef MIRROR_SHADER
#define MIRROR_SHADER
#include "shader.h"

class MirrorShader : public Shader
{
    public:
        MirrorShader(const Color& tint = Color(1, 1, 1)) : Shader(tint), tint(tint) {}

        Color render(const Vec3& point, const Vec3& normal, const std::vector<const Light*>& lights) const override;
        const Color& getTint() const { return tint; }
    
    private:
        Color tint;

};


#endif