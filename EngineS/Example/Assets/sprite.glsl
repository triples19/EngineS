#ifdef VERTEX

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = texCoords;
    gl_Position = vec4(vertex, 0.0, 1.0);
}

#endif

#ifdef FRAGMENT

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;

void main()
{
    color = vec4(1.0, 1.0, 1.0, 1.0) * texture(image, TexCoords);
}

#endif