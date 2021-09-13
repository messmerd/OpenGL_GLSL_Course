#version 440
// For OpenGL version 4.4

in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

uniform mat4 model; // Exists in graphics memory. Need to acquire Id in main program to use it.

void main()
{
    colorOut = colorIn; // Passthrough to fragment shader

    // Transform local space (model) to world space (gl_Position):
    gl_Position = model * vec4(vertexIn, 1.0);
}
