#version 420 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D uniTexture1;
uniform sampler2D uniTexture2;

uniform vec4 variedColor;

void main()
{
	//FragColor = texture(ourTexture, TexCoord) * variedColor;
	//	FragColor = variedColor;
	FragColor = mix(texture( uniTexture1,TexCoord),texture( uniTexture2,TexCoord), 0.2);
}