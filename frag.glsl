#version 420
in vec2 exTexCoord;
out vec4 outColour;

uniform sampler2D texSample;

float pi = 3.14159265358f;
float e = 2.718281828;
float c = 1.0053611;
uniform float maxIterations;

vec2 powc(float x, vec2 s)
{
	// x^s = e^(log(x)s) = e^(log(x)Re(s) + log(x)Im(s)i) = x^Re(s) * (cos(log(x)Im(s)) + sin(log(x)Im(s))i)
	float theta = log(x) * s.y;
	return pow(x, s.x) * vec2(cos(theta), sin(theta));
}

vec2 multInv(vec2 s)
{
	return vec2(s.x, -s.y)/dot(s, s);
}

vec2 multC(vec2 a, vec2 b)
{
	return vec2(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}

vec2 sinc(vec2 z)
{
	// z = a + bi
	float sina = sin(z.x);
	float cosa = cos(z.x);
	return 0.5*(exp(z.y)*vec2(sina, cosa) - exp(-z.y)*vec2(-sina, cosa));
}

vec2 expc(vec2 z){return powc(e, z);}

float GetAngle(vec2 s)
{
	s /= length(s);
	float theta;
	if(s.y >= 0 && s.x >= 0)
		return asin(s.y);
	else if(s.x < 0)
		return pi - asin(s.y);
	else
		return (2 * pi) + asin(s.y);

	return 0;
}

vec2 f(vec2 t)
{
	vec2 r = vec2(t.x, t.y);

	// e^t = e^t.x * e^t.yi = e^t.x(cos(t.y) + isin(t.y))
	//r = exp(r.x)*vec2(cos(r.y), sin(r.y));

	/*//
	// Riemann Zeta function
	float i = 1;
	vec2 x = vec2(0,0);
	while (i < maxIterations)
	{
		x += multInv(powc(i, r));
		i += 1;
	}
	r = x;//*/

	//*//
	// Mandelbrot
	float j = 0.0f;
	vec2 mandel = r;
	vec2 julia_0 = vec2(0.285, 0.01);
	vec2 julia_1 = vec2(-0.8, 0.156);
	vec2 julia_2 = vec2(-0.4, 0.6);
	vec2 c = julia_2;	// Fractal type
	vec2 z = vec2(r.x, r.y);
	while (j < maxIterations)
	{
		z = vec2(z.x*z.x - z.y*z.y, 2*z.x*z.y) + c;
		if(dot(z, z) > 2.0)
		{
			return vec2(1 - j/maxIterations, 0);
		}
		j += 1;
	}
	r = vec2(0, 0);//*/

	// Poles
	//vec2 p0 = vec2(1,1), p1 = vec2(-1,5);
	//r = multC(multInv(t - p0), multInv(t - p1));
	//r = multC(r, multInv(t - vec2(-6,5)));

	// e^sin(z)
	//r = expc(sinc(t));

	// Complex sin
	//r = sinc(t);

	// drip-drip
	//r = vec2(sin(length(r-vec2(5, 0))), cos(length(r-vec2(-5, 0))));

	/*// Spiral
	float theta = GetAngle(t);
	float logLen = log(length(t));
	r = vec2(10*theta/(2*pi) + logLen, logLen - 10*theta/(2*pi));//*/

	//sqrt
	//r = vec2(log(abs(t.x + (t.y*t.y)/(4*t.x))), log(abs((t.y/2)*log(abs(t.x)) - t.y)));

	//spiral2
	//r = vec2(8*GetAngle(t)/(2*pi), log(length(t)));

	//r = vec2(t.x + t.y*t.y/(2*abs(t.x)*log(abs(t.x))), t.y - t.y*log(abs(log(abs(t.x)))));

	return r;
}

void main(void)
{
	vec2 texCoord = f(exTexCoord);
	outColour = texture(texSample, texCoord);

	// Domain colouring
	//outColour = texture(texSample, vec2(GetAngle(texCoord)/(2*pi), 0.1))*(sin(length(texCoord)) + 0.25);
}