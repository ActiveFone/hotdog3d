#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;

vec4 GetPos(vec4 offset, vec4 pos)
{
    return pos + offset;
}

void main() {  
	fColor = gs_in[0].color;  
	vec4 pos = gl_in[0].gl_Position;
	gl_Position = GetPos(vec4(-0.2, -0.2, 0.0, 0.0), pos);    // 1:左下
    EmitVertex();   
    gl_Position = GetPos(vec4(0.2, -0.2, 0.0, 0.0), pos);    // 2:右下
    EmitVertex();
    gl_Position = GetPos(vec4(-0.2, 0.2, 0.0, 0.0), pos);    // 3:左上
    EmitVertex();
    gl_Position = GetPos(vec4(0.2, 0.2, 0.0, 0.0), pos);   // 4:右上
    EmitVertex();
    gl_Position = GetPos(vec4(0.0, 0.4, 0.0, 0.0), pos);  // 5:顶部
    EmitVertex();
    EndPrimitive();
}