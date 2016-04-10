#version 330 core

uniform vec4 u_color;
uniform vec3 u_lightColor;
uniform float u_ambientStrength;
uniform sampler2D u_texture;
uniform float u_shininess;
uniform vec3 u_specularIntensity;
uniform vec3 u_specularMaterial;

in vec3 normalDirection;
in vec2 uvMaterial;
in vec3 lightDirection;
in vec3 worldPosition;
in vec3 cameraPosition;

out vec4 fragment;

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;

  //Normalize on every fragment
  vec3 lightDirectionNormalized = normalize(lightDirection);
  vec3 normalDirectionNormalized = normalize(normalDirection);

  //Ambient Light
  vec3 ambient = u_lightColor * u_ambientStrength;

  //Diffuse Light
  vec3 diffuse = u_lightColor * max(dot(normalDirectionNormalized, lightDirectionNormalized), 0.0f);

  //Specular Light
  //vec3 viewDirection = normalize(cameraPosition - worldPosition);
  vec3 viewDirection = normalize(normalDirection - cameraPosition);
  vec3 reflectionDirection = reflect(-lightDirectionNormalized, normalDirectionNormalized);
  float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), u_shininess);
  vec3 specular = u_lightColor * spec * u_specularIntensity * u_specularMaterial;

  //Final
  fragment = materialColor * vec4((ambient + diffuse + specular), 1.0f);
};

////////////////////////////////////////////

#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D floorTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool blinn;

void main()
{           
    vec3 color = texture(floorTexture, fs_in.TexCoords).rgb;
    // Ambient
    vec3 ambient = 0.05 * color;
    // Diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    vec3 normal = normalize(fs_in.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // Specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    if(blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    }
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color
    FragColor = vec4(ambient + diffuse + specular, 1.0f);
}