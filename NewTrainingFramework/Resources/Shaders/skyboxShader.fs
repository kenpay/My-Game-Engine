precision mediump float;
varying vec3 v_pos;
uniform samplerCube u_texture_0;
void main()
{
	gl_FragColor = textureCube(u_texture_0,  v_pos);
}
