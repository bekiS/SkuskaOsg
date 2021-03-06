
uniform mat4 osg_ViewMatrixInverse;

varying vec3 pos_worldspace;
varying vec3 n_worldspace;
varying vec3 t_worldspace;
varying vec3 b_worldspace;
varying vec4 c_worldspace;

void main()
{
    // Model space * Model matrix = World space
    // World space * View matrix = Camera (eye) space
    // Camera (eye) space * Projection matrix = Screen space
    // We simply translate vertex from Model space to Screen space.
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    // Pass the texture coordinate further to the fragment shader.
    gl_TexCoord[0] = gl_MultiTexCoord0;
    // gl_ModelViewMatrix, gl_NormalMatrix, etc. are in Camera(eye) space
    // Camera (eye) space * inverse View matrix = World space
    mat4 modelMatrix = osg_ViewMatrixInverse * gl_ModelViewMatrix;
    mat3 modelMatrix3x3 = mat3(modelMatrix[0].xyz, modelMatrix[1].xyz, modelMatrix[2].xyz);

    // Convert everything to World space.
    // Position.
    vec4 pos_WS4 = modelMatrix * gl_Vertex;
    pos_worldspace = vec3(pos_WS4.xyz);
    // Normal.
    n_worldspace   = modelMatrix3x3 * gl_Normal;
    // Tangent.
    t_worldspace   = modelMatrix3x3 * gl_MultiTexCoord1.xyz;
    // Bitangent / binormal.
    b_worldspace   = cross(n_worldspace, t_worldspace);
    //color
   c_worldspace =  gl_Color;
}

