attribute vec3 position, a_norm;
attribute vec2 a_uv;
varying vec3 v_color, v_pos, v_norm;
varying vec2 v_uv;
uniform mat4 view, perspective, scale, rotationX, rotationY, rotationZ, translation;

void main()
{
	mat4 model = translation*rotationX*rotationY*rotationZ*scale;
	vec4 posL = model * vec4(position, 1.0);
	gl_Position = perspective * view * posL;
	v_uv = a_uv;
	v_pos = posL.xyz;
	v_norm = (model * vec4(a_norm, 0.0)).xyz;
}