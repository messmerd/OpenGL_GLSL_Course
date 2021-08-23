#version 440
// For OpenGL version 4.4

//uniform int time; // Exists in graphics memory. Need to acquire Id in main program to use it.
in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

void main()
{
    colorOut = colorIn; // Passthrough to fragment shader
    gl_Position = vec4(vertexIn, 1.0); // Add w component


}
