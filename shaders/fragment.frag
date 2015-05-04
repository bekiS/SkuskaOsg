//lightConst
const int LIGHT_COUNT = 1;
const int LIGHT_SIZE = 5;
const int COLOR = 0;
const int POSITION = 1;
const int ATTENUATION = 2;
const int SPOT_DIR = 3;
//SPOT_PARAMS [ cos_spot_cutoff, spot_exponent, ignored, is_spot ]
const int SPOT_PARAMS = 4;
const float MATERIAL_SHININES = 0.5;
const vec4 Global_ambient = vec4(0.09, 0.09, 0.09, 1.0);

uniform int lightsCount;
uniform vec4 lights[ LIGHT_COUNT*LIGHT_SIZE ];

uniform mat4 osg_ViewMatrixInverse;
uniform sampler2DRect posMap;
uniform sampler2DRect normalMap;
uniform sampler2DRect colorMap;


////light_preCalc

void phong_preCalc(
    in vec3 mat_position,
    in vec4 light_position,
    out float light_distance,
    out vec3 ec_light_location,
    out vec3 ec_light_half
) {
    // This is the core setup for a phong lighting pass
    // as a reusable fragment of code.
    // vertex_position -- un-transformed vertex position (world-space)
    // light_position -- un-transformed light location (direction)
    // light_distance -- output giving world-space distance-to-light
    // ec_light_location -- output giving location of light in eye coords
    // ec_light_half -- output giving the half-vector optimization
    if (light_position.w == 0.0) {
        // directional rather than positional light...
        ec_light_location = normalize(
            gl_NormalMatrix *
            light_position.xyz
        );
        light_distance = 0.0;
    } else {
        // positional light, we calculate distance in
        // model-view space here, so we take a partial
        // solution...
        vec3 ms_vec = (
            light_position.xyz -
            mat_position
        );
        vec3 light_direction = gl_NormalMatrix * ms_vec;
        ec_light_location = normalize( light_direction );
        light_distance = abs(length( ms_vec ));
    }
    // half-vector calculation
    ec_light_half = normalize(
        ec_light_location + vec3( 0,0,1 )
    );
}


vec3 phong_weightCalc(
    in vec3 light_pos, // light position/direction
    in vec3 half_light, // half-way vector between light and view
    in vec3 frag_normal, // geometry normal
    in float shininess, // shininess exponent
    in float distance, // distance for attenuation calculation...
    in vec4 attenuations, // attenuation parameters...
    in vec4 spot_params, // spot control parameters...
    in vec4 spot_direction // model-space direction
) {
    // returns vec3( ambientMult, diffuseMult, specularMult )
    float n_dot_pos = max( 0.0, dot(
        frag_normal, light_pos
    ));
    float n_dot_half = 0.0;
    float attenuation = 1.0;
    if (n_dot_pos > -.05) {
        float spot_effect = 1.0;
        if (spot_params.w != 0.0) {
            // is a spot...
            float spot_cos = dot(
                gl_NormalMatrix * normalize(spot_direction.xyz),
                normalize(-light_pos)
            );
            if (spot_cos <= spot_params.x) {
                // is a spot, and is outside the cone-of-light...
                return vec3( 0.0, 0.0, 0.0 );
            } else {
                if (spot_cos == 1.0) {
                    spot_effect = 1.0;
                } else {
                    spot_effect = pow(
                            (1.0-spot_params.x)/(1.0-spot_cos),
                            spot_params.y
                        );
                }
            }

	    
        }
        n_dot_half = pow( max(0.0,dot(half_light, frag_normal )), shininess);
        if (distance != 0.0) {
            float attenuation = 1.0/(
                attenuations.x +
                (attenuations.y * distance) +
                (attenuations.z * distance * distance)
            );
            n_dot_half *= spot_effect;
            n_dot_pos *= attenuation;
            n_dot_half *= attenuation;
        }
    }
    return vec3( attenuation, n_dot_pos, n_dot_half);
}

        



void main() {
    vec3 mat_position = texture2DRect(posMap,  gl_FragCoord.xy).xyz;
    vec3 mat_normal = texture2DRect(normalMap, gl_FragCoord.xy).xyz;
    vec4 mat_color = texture2DRect(colorMap,   gl_FragCoord.xy).xyzw;
    // Convert camera position from Camera (eye) space (it's always at 0, 0, 0
    // in there) to World space. Don't forget to use mat4 and vec4!
    vec4 cameraPos_worldspace = osg_ViewMatrixInverse * vec4(0, 0, 0, 1);
    // Direction from point to camera.
    vec3 viewDir_worldspace = normalize(vec3(cameraPos_worldspace) - mat_position);
    // Final fragment color.
    vec4 fragColor = Global_ambient * mat_color;
    
    vec3 EC_Light_half[LIGHT_COUNT];
    vec3 EC_Light_location[LIGHT_COUNT];
    float Light_distance[LIGHT_COUNT];
    for (int i = 0; i< lightsCount; i++ ) {
        int j = i * LIGHT_SIZE;
        phong_preCalc(
            mat_position,
            lights[j+POSITION],
            Light_distance[i],
            EC_Light_location[i],
            EC_Light_half[i]
        );
    }
    
    int i,j;
    for (i=0;i<lightsCount;i++) {
        j = i* LIGHT_SIZE;
        vec3 weights = phong_weightCalc(
            normalize(EC_Light_location[i]),
            normalize(EC_Light_half[i]),
            normalize(mat_normal),
            MATERIAL_SHININES,
            abs(Light_distance[i]),
            lights[j+ATTENUATION],
            lights[j+SPOT_PARAMS],
            lights[j+SPOT_DIR]
        );
        fragColor = ( fragColor
                  +( (lights[j+COLOR] * mat_color)
                  * (weights.x  +  weights.y  +  weights.z))
                  );
    }
//void main()
//{
//    vec3 p_worldspace = texture2DRect(posMap,    gl_FragCoord.xy).xyz;
//    vec3 n_worldspace = texture2DRect(normalMap, gl_FragCoord.xy).xyz;
//    vec3 c_worldspace = texture2DRect(colorMap,  gl_FragCoord.xy).xyz;
//    vec3 fragColor  = vec3(0.0, 0.0, 0.0);
//    // Direction from point to light (not vice versa!)
//    for (int i=0;i<lightsCount;i++) {
//    int j = i * LIGHT_SIZE;
//    vec3 lightDir_worldspace = normalize(lights[j + SPOT_DIR].xyz  - p_worldspace);
//    // Lambertian diffuse color.
//    float diff = max(0.2, dot(lightDir_worldspace, n_worldspace));
//    // Convert camera position from Camera (eye) space (it's always at 0, 0, 0
//    // in there) to World space. Don't forget to use mat4 and vec4!
//    vec4 cameraPos_worldspace = osg_ViewMatrixInverse * vec4(0, 0, 0, 1);
//    // Direction from point to camera.
//    vec3 viewDir_worldspace = normalize(vec3(cameraPos_worldspace) - p_worldspace);
//    // Blinn-Phong specular highlights.
//    vec3 h_worldspace = normalize(lightDir_worldspace + viewDir_worldspace);
//    float spec = pow(max(0.0, dot(h_worldspace, n_worldspace)), 40.0);
//    // Final fragment color.
//    vec3 color = diff * c_worldspace;// * s_worldspace;
//    // Only add specular if the fragment is NOT in the shadow.
//    fragColor += color + spec;
//    }

    gl_FragColor = fragColor;
}
