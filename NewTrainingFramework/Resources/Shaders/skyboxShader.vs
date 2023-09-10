attribute vec3 position, a_norm;
varying vec3 v_pos, v_norm;
uniform mat4 view, perspective, scale, rotationX, rotationY, rotationZ, translation;

void main()
{
	mat4 model = translation*rotationX*rotationY*rotationZ*scale;
	vec4 posL = model * vec4(position, 1.0);
	gl_Position = perspective * view * posL;
	v_pos = position;
}