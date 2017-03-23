#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

vec2 checker(vec2 p) {
    vec2 p2 = abs(fract(p)-0.5);
    return vec2(mod(floor(p.x)+floor(p.y), 2.0),max(1.0-(-max(p2.x,p2.y)+0.5)*50.0,0.0));
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = (fragCoord.xy * 2.0 - resolution.xy) / resolution.y;
    fragColor = vec4(1.0);
    
    
    float len = 0.0;
    for ( float i = 5.0; i< 160.0; i++) {
    
        float size = i;
        
        vec2  pos = (2. * fragCoord.xy / resolution.xy - 1.)
                * vec2(resolution.x / resolution.y,1.);
        vec2  rot = vec2(atan(pos.x, pos.y) / 3.14*size+time/(size-4.0),
                         size / length(pos)*0.1+time+i*0.2);
        vec2 check = checker(rot);
        if (check.x == 1.0) {
    		fragColor = vec4(0.05*i);
            break;
        }
        len = max(check.y,len);
        
    }
    
}

void main( void ) {
	mainImage(gl_FragColor,gl_FragCoord.xy);
}