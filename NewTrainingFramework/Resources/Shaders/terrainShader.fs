precision mediump float;
varying vec4 v_blend;
varying vec3 v_pos;
varying vec2 v_uv2;
uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;
uniform vec3 u_camPos, f_color;
uniform float minR, maxR;
void main()
{
    vec4 c_0 = texture2D(u_texture_0, v_uv2);
	vec4 c_1 = texture2D(u_texture_1, v_uv2);
	vec4 c_2 = texture2D(u_texture_2, v_uv2);
	vec4 c_final = v_blend.r * c_0 + v_blend.g*c_1 + v_blend.b * c_2;
	float d = distance(v_pos, u_camPos);
	float alpha = clamp((d-minR)/(maxR-minR), 0.3, 0.7);
	vec3 c_fog = (alpha - 0.15) * f_color + (1.0 - alpha) * c_final.xyz;
    gl_FragColor = vec4(c_fog, 1.0);
}
