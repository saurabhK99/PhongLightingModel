 #version 430

in vec4 vCol;   
in vec2 texCoordinate;
in vec3 Normal; 
in vec3 fragPos;      
                         
out vec4 color;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

struct Material {
    float shininess;
    float specularIntensity;
};

uniform vec3 eyePos;
uniform sampler2D texUnit;
uniform DirectionalLight dirLight;
uniform Material material;
                        
void main() {   
    vec4 ambientColor = (vec4(dirLight.color, 1.0) * dirLight.ambientIntensity);

    float diffuseFactor = max(dot(normalize(Normal), normalize(dirLight.direction)),0.0f);
    vec4 diffuseColor = (vec4(dirLight.color, 1.0) * dirLight.diffuseIntensity * diffuseFactor);

    vec4 specularColor = vec4(0.0, 0.0, 0.0, 0.0);

    if(diffuseFactor > 0.0f) {
        vec3 relativeFragPos = normalize(eyePos - fragPos);
        vec3 reflectedVertex = normalize(reflect(dirLight.direction, normalize(Normal)));

        float specularFactor = dot(reflectedVertex, relativeFragPos);

        if(specularFactor > 0.0f) {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = (vec4(dirLight.color, 1.0) * material.specularIntensity * specularFactor);
        }

    }

    color = (texture(texUnit, texCoordinate) * (ambientColor + diffuseColor + specularColor));           
}