precision mediump float;
varying vec3 v_color;
uniform sampler2D u_texture;
varying vec2 v_uv;
void main()
{
	//gl_FragColor = vec4(v_color, 1.0); 
    //gl_FragColor = vec4(v_uv.x, v_uv.y, 0.0, 1.0);
    vec4 culoare = texture2D(u_texture, v_uv);
    //if (culoare.a < 0.1)
        //discard;
    gl_FragColor = culoare;
}
