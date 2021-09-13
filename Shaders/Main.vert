#version 440
// For OpenGL version 4.4

in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

uniform mat4 model; // Exists in graphics memory. Need to acquire Id in main program to use it.
uniform mat4 view;

void main()
{
    colorOut = colorIn; // Passthrough to fragment shader

    // Transform local space (model) to world space (gl_Position):
    gl_Position = view * model * vec4(vertexIn, 1.0);
    // Operations are applied from right to left: model * vertex --> world space;
    //      Then view * world space --> camera space.
}
