#version 330 core

out vec4 FragColor;
in vec2 ourTexCoords;

uniform sampler2D ourTexture;
void main()
{
    FragColor = texture(ourTexture, ourTexCoords);
    // FragColor = ourColor / 255.0f;
}

