#version 330 core
out vec4 FragColor;
in vec2 texCoords;
uniform sampler2D boxTexture;

void main()
{    
    FragColor = texture(boxTexture, texCoords);
}