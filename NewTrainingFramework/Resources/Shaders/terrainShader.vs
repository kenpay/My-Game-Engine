attribute vec3 position, a_norm;
uniform vec3 u_height;
varying vec3 v_color, v_pos, v_norm;
varying vec4 v_blend;
attribute vec2 a_uv;
varying vec2 v_uv2;
uniform mat4 view, perspective, scale, rotationX, rotationY, rotationZ, translation;
uniform sampler2D u_texture_3;
uniform float u_dimCel;

void main()
{
	vec4 c_blend = texture2D(u_texture_3, a_uv);
	mat4 model = translation*rotationX*rotationY*rotationZ*scale;
	vec4 posL = vec4(position, 1.0);
	vec4 pos_nou = posL;
	gl_Position = perspective * view * model * pos_nou;
	v_uv2 = u_dimCel * a_uv;
	v_blend = c_blend;
	v_pos = (model * posL).xyz;
	v_norm = (model * vec4(a_norm, 0.0)).xyz;
}