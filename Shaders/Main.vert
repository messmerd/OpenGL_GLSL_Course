#version 440
// For OpenGL version 4.4

in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

// Uniform variables exist in graphics memory. Need to acquire Id in main program to use it.
uniform mat4 model; // Model matrix (position, scale, and rotation of a 3D object - for model transformation)
uniform mat4 view; // View matrix (for viewing transformation into camera/eye space)
uniform mat4 proj; // Projection matrix (for projection transform into clip space)

void main()
{
    colorOut = colorIn; // Passthrough to fragment shader

    // Transform local space (model) to world space (gl_Position):
    gl_Position = proj * view * model * vec4(vertexIn, 1.0);
    // Operations are applied from right to left: model * vertex --> world space;
    //      Then view * world space --> camera space; Then proj * camera space --> clip space;
}
