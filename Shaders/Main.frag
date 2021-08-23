#version 440
// For OpenGL version 4.4

//uniform bool isLit; // Exists in graphics memory. Need to acquire Id in main program to use it.
in vec3 colorOut; // Must have same name as in Main.vert
out vec4 fragColor;

void main()
{
    fragColor = vec4(colorOut, 1.0); // Add w component
}
