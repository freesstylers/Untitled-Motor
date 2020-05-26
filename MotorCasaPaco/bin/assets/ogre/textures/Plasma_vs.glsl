varying vec2 Texcoord;
varying vec2 vUv;
varying vec2 nUv;
			
void main()
{
	gl_Position		= ftransform();
	Texcoord		= gl_MultiTexCoord0.xy;	
	vUv = vec2(0.1, 0.1) * Texcoord;
	nUv = Texcoord;
}
