#include <math.h>

float noise(float x, float y);
float cosineInterpolate(float a, float b, float x);
float perlinNoise(float x, float y);
float perlinNoise3D(float x, float y, float z);


float noise(float x, float y)
{
	int n = int(x + y * 57);
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589)
		& 0x7fffffff) / 1073741824.0);
}

float noise3(float x, float y, float z)
{
	int n = int(x + y * 57 + z * 126);
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589)
		& 0x7fffffff) / 1073741824.0);
}

float cosineInterpolate(float a, float b, float x)
{
	float ft = x * 3.1415927;
	float f = (1 - cos(ft)) * 0.5;

	return  a*(1 - f) + b*f;
}

float perlinNoise(float x, float y)
{
	float X = floor(x), Y = floor(y);

	float v1 = noise(X, Y);
	float v2 = noise(X + 1, Y);
	float v3 = noise(X, Y + 1);
	float v4 = noise(X + 1, Y + 1);

	return cosineInterpolate(
		cosineInterpolate(v1, v2, x - X),
		cosineInterpolate(v3, v4, x - X),
		y - Y
		);
}

float perlinNoise3D(float x, float y, float z)
{
	float X = floor(x), Y = floor(y), Z = floor(z);

	float v0 = noise3(X, Y, Z);
	float v1 = noise3(X + 1, Y, Z);
	float v2 = noise3(X, Y + 1, Z);
	float v3 = noise3(X + 1, Y + 1, Z);
	float v4 = noise3(X, Y, Z + 1);
	float v5 = noise3(X + 1, Y, Z + 1);
	float v6 = noise3(X, Y + 1, Z + 1);
	float v7 = noise3(X + 1, Y + 1, Z + 1);

	float i0 = cosineInterpolate(v0, v1, x - X);
	float i1 = cosineInterpolate(v2, v3, x - X);
	float i2 = cosineInterpolate(v4, v5, x - X);
	float i3 = cosineInterpolate(v6, v7, x - X);

	float ii0 = cosineInterpolate(i0, i1, y - Y);
	float ii1 = cosineInterpolate(i2, i3, y - Y);

	return cosineInterpolate(ii0, ii1, z - Z);

}
