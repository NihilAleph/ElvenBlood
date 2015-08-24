#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

void main() {
    
    float distance = length(fragmentUV);
    vec2 origin = vec2(1.0, 0.0);
    vec2 normalizedUV = normalize(fragmentUV);
    float cosine = dot(normalizedUV, origin);
    if (cosine > cos(0.2)) {
    	if (distance < 1.0) {
    		color = vec4(fragmentColor.rgb, fragmentColor.a * (pow(0.5,distance)) * (cosine / (1 - cos(0.2)) + 1 - 1 / (1 - cos(0.2))));
    	}
    }
}