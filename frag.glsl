#version 400
in vec4 exColour;
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
	float signy = sign(s.y);
	float signx = sign(s.x);
	float theta;
	if(signy > 0 && signx > 0)
		theta = asin(s.y);
	else if(signy > 0 && signx < 0)
		theta = pi - asin(s.y);
	else if(signy < 0 && signx < 0)
		theta = pi - asin(s.y);
	else if(signy < 0 && signx > 0)
		theta = 2 * pi + asin(s.y);

	return theta;
}

vec2 f(vec2 t)
{
	vec2 r = t;

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

	/*//
	// Mandelbrot
	float i = 0.0f;
	vec2 c = r;
	vec2 z = vec2(0,0);
	while (i < maxIterations)
	{
		z = vec2(z.x*z.x - z.y*z.y, 2*z.x*z.y) + c;
		float t = dot(z, z);
		if(t > 2.0f)
		{
			return vec2(1 - i/maxIterations, 0);
		}
	    i += 1;
	}
	r = vec2(0, 0);//*/

	// e^sin(z)
        //r = expc(sinc(t));

	// drip-drip
	//r = vec2(sin(length(t-vec2(5, 0))), cos(length(t-vec2(-5, 0))));

	//r = vec2(1/length(t), GetAngle(t));

        r = expc(vec2(10*GetAngle(t)/(2*pi) + log(length(t)), log(length(t)) - 10*GetAngle(t)/(2*pi)));

	return r;
}

void main(void)
{
	vec2 texCoord = f(exTexCoord);

	outColour = texture(texSample, texCoord);

	// Domain colouring
	//(log(length(texCoord)) - floor(log(length(texCoord)))) *
	//outColour = texture(texSample, vec2(GetAngle(texCoord)/(2*pi), length(texCoord)));
}
