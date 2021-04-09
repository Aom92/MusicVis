#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
void main()
{
	gl_Position = position;
};


#shader fragment
#version 330 core

out vec4 color;
uniform float iTime;



void main()
{
	//Cool shader
	vec2 iResolution;
	iResolution = vec2(640.0, 480.0);
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0, 2, 4));
	color = vec4(col, 1.0);

};
