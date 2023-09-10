precision mediump float;
varying vec3 v_pos, v_norm;
varying vec2 v_uv;
uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;
uniform float u_Time, u_DispMax, minR, maxR, u_specPower, u_ratio;
uniform vec3 u_camPos, f_color, u_ambientalCol, u_lightDiffCol, u_lightSpecColor, u_lightPos;

void main()
{
	vec2 disp = texture2D(u_texture_2, vec2(v_uv.x, v_uv.y + u_Time)).rg;
	vec2 offset = (( disp * 2.0 ) - 1.0)*u_DispMax;
	vec2 v_uv_displaced = v_uv+offset;
	vec4 c_fire = texture2D(u_texture_1, v_uv_displaced);
	vec4 c_alpha = texture2D(u_texture_0, v_uv);
	c_fire.a *= c_alpha.r;
    if (c_fire.a < 0.1)
        discard;
	vec3 compAmb = c_fire.xyz * u_ambientalCol;
	vec3 N = normalize(v_norm);
	vec3 L = normalize(v_pos - u_lightPos);
	vec3 Cdiff = c_fire.xyz * u_lightDiffCol * max(dot(N, -L), 0.0);
	vec3 R = normalize(reflect(L, N));
	vec3 E = normalize(u_camPos - v_pos);
	vec3 Cspec = u_lightSpecColor * pow(max(dot(R,E), 0.0), u_specPower);
	vec3 c_lumina = u_ratio * compAmb + ( 1.0 - u_ratio) * (Cdiff + Cspec);
	float d = distance(v_pos, u_camPos);
	float alpha = clamp((d-minR)/(maxR-minR), 0.0, 1.0);
	vec3 c_fog = alpha * f_color + (1.0 - alpha) * c_lumina.xyz;
    gl_FragColor = vec4(c_fog, c_fire.a);
}
