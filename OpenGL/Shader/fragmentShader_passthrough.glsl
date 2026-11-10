#version 410 core

// out vec4 fragmentColor;
// in float hue;

// vec3 hsvToRgb(float h)
// {
//    vec3 p = abs(fract(h + vec3(1.0, 2.0 / 3.0, 1.0 / 3.0)) * 6.0 - 3.0);
//    return clamp(p - 1.0, 0.0, 1.0);
// }

// void main()
// {
//    fragmentColor = vec4(hsvToRgb(hue), 1.0);
// }

in vec3 color;
out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(color, 1.0);
}
