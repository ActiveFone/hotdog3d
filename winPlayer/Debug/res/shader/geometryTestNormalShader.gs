#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.4; 

uniform float time;

void GenerateLine(int index)
{
	vec4 pos = gl_in[index].gl_Position +  vec4(gs_in[index].normal * ((sin(time) + 1.0) / 2.0), 0.0) * 2.0;
    gl_Position = pos;
	EmitVertex();
	gl_Position = pos + vec4(gs_in[index].normal, 0.0) * MAGNITUDE;
	EmitVertex();
	EndPrimitive();
}

void main() {    
    GenerateLine(0);
	GenerateLine(1);
	GenerateLine(2);
}