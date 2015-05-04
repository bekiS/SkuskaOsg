
varying vec3 pos_worldspace;
varying vec3 n_worldspace;
varying vec3 t_worldspace;
varying vec3 b_worldspace;
varying vec4 c_worldspace;

void main()
{
    gl_FragData[0] = vec4(pos_worldspace, gl_FragCoord.z);
    // Convert Tangent space to World space with TBN matrix.
    gl_FragData[1] = vec4(t_worldspace + b_worldspace + n_worldspace, 1.0);
    gl_FragData[2] = vec4(c_worldspace.xyz, 0.0);
}

