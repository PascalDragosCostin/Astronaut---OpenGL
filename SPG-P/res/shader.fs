#version 140

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 pos0;

uniform sampler2D sampler;
uniform vec3 lightDirection;


vec3 lighting(vec3 pos, vec3 normal, vec3 lightPos, vec3 viewPos, vec3 ambient, vec3 diffuse, vec3 specular, float specPower)
{
  vec3 L = normalize(lightPos - pos);
  vec3 V = normalize(viewPos - pos);
  vec3 N = normalize(normal);
  vec3 R = normalize(reflect(-L, N));
  float cosTheta = dot(R, V);


  float diffCoef = abs(dot(L, N));
  float specCoef = pow(clamp(cosTheta, 0.0, 1.0), specPower);

  vec3 ambientColor = ambient * diffuse;
  vec3 diffuseColor = diffCoef * diffuse;
  vec3 specularColor = specCoef * specular * diffuse;
  vec3 col = ( ambientColor + specularColor * 3 ); 

  return clamp(col, 0, 1);
}


void main()
{
    // minusul vietii pentru ca ma intereseaza lumina reflectata, nu directia luminii
    //gl_FragColor = vec4(0.2, 0.2, 0.2, 0.2) + texture2D(sampler, texCoord0) * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
    
    vec3 ambient = vec3(0.1f, 0.1f, 0.2f);
    
    vec3 diffuse = texture2D(sampler, texCoord0).xyz * 0.8;
    vec3 specular = vec3(0.3);
    float specPower = 32;

    vec3 viewPos = vec3(0.0f, 0.0f, -10.0f);
    vec3 color = lighting(pos0, normal0, lightDirection, viewPos, ambient, diffuse, specular, specPower) + diffuse * clamp(dot(-lightDirection, normal0), 0.0, 25.0)/25;
    

    //gl_FragColor = texture2D(sampler, texCoord0) * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
    //gl_FragColor = texture2D(sampler, texCoord0);
    //gl_FragColor = vec4(diffuse * dot(lightDirection, normal0), 1.0);

    //gl_FragColor =  vec4(specular * pow(dot(reflect(-lightDirection, normal0), viewPos), specPower), 0) ;

    gl_FragColor = vec4(color, 1.0);
}
