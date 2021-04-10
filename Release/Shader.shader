#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
uniform float iTime;
void main()
{	
	vec2 iResolution;
	iResolution = vec2(640.0, 480.0);
	vec2 uv = position.xy / iResolution.xy * 0.05;


	
	gl_Position = vec4(uv.x * cos(iTime + 0.5 ) - uv.y * sin(iTime+0.5), uv.x * sin(iTime+0.3) + uv.y * cos( iTime +0.3) ,   0.5 , 0.5 );
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
