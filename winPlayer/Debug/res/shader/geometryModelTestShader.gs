#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
} gs_in[];

out vec2 TexCoords; 

uniform float time;

vec4 explode2(int num, vec3 normal)
{	
	vec4 position = gl_in[num].gl_Position;

	float magnitude = 2.0;
	vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; 
	//return position + vec4(direction, 0.0);
	return position;
}

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

vec4 GetOffsetPos(vec4 offset, vec4 pos)
{
    return pos + offset;
}

vec4 explode33(vec3 normal, int i, vec4 pos)
{	
	vec4 position = pos;
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; 
    return position + vec4(direction, 0.0);
	//return vec4(pos.r, gl_in[i].gl_Position.gba);
	//return pos;
}

void main() {    
    vec3 normal = GetNormal();

	for (int i = 0; i < 3; i++)
	{
		gl_Position = explode33(normal, i, gl_in[i].gl_Position);
		//gl_Position = explode2(i, normal);
		TexCoords = gs_in[i].texCoords;
		EmitVertex();
	}
    EndPrimitive();
}