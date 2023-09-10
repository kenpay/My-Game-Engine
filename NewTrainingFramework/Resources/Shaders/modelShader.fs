precision mediump float;
varying vec3 v_pos, v_norm;
varying vec2 v_uv;
uniform sampler2D u_texture_0;
uniform vec3 u_camPos, f_color, u_ambientalCol, u_lightDiffCol, u_lightSpecColor, u_lightPos;
uniform float minR, maxR, u_specPower, u_ratio;
void main()
{
	vec4 culoare = texture2D(u_texture_0, v_uv);
    if (culoare.a < 0.1)
        discard;
		
	vec3 compAmb = culoare.xyz * u_ambientalCol;
	vec3 N = normalize(v_norm);
	vec3 L = normalize(v_pos - u_lightPos);
	vec3 Cdiff = culoare.xyz * u_lightDiffCol * max(dot(N, -L), 0.0);
	vec3 R = normalize(reflect(L, N));
	vec3 E = normalize(u_camPos - v_pos);
	vec3 Cspec = u_lightSpecColor * pow(max(dot(R,E), 0.0), u_specPower);
	vec3 c_lumina = u_ratio * compAmb + ( 1.0 - u_ratio) * (Cdiff + Cspec);
	float d = distance(v_pos, u_camPos);
	float alpha = clamp((d-minR)/(maxR-minR), 0.0, 1.0);
	vec3 c_fog = alpha * f_color + (1.0 - alpha) * c_lumina.xyz;
	if (culoare.a < 0.2)
		discard;
    gl_FragColor = vec4(c_fog, culoare.a);
}
