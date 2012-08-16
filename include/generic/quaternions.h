//this quatrnion class was written by Coldon
//http://www.gamedev.net/community/forums/topic.asp?topic_id=468679

const float VECTOR_TOLERANCE = 0.0000001f;
const float QUATERNION_TOLERANCE = 0.0000001f;

class point3f
{	
public:
		
	//members
	//------------------------------------------------------------------------------

	float x, y, z;
	
	//constructors
	//------------------------------------------------------------------------------

	point3f() : x(0),y(0),z(0) {}		
	point3f(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {}

	//methods
	//------------------------------------------------------------------------------

	//addition
	point3f operator +(point3f p)
	{
		return point3f(x + p.x, y + p.y, z + p.z);		 
	}

	//subtraction
	point3f operator -(point3f p)
	{
		return point3f(x -p.x, y - p.y, z - p.z);		 
	}

	//convert to array
	void toArray(float* a)
	{	
		a[0] = x;
		a[1] = y;
		a[2] = z;
	}
};

//vector class
class vector3f
{

public:

	//members
	//------------------------------------------------------------------------------

	float x, y, z;

	//constructors
	//------------------------------------------------------------------------------

	//default constructor
	vector3f() : x(0),y(0),z(0) {}	

	//create vector from point
	vector3f(point3f p) : x(p.x), y(p.y), z(p.z) {}
	
	vector3f operator =(point3f p)
	{
		return vector3f(p);
	}

	//create vector with co-ordinates
	vector3f(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {}

	//methods
	//------------------------------------------------------------------------------
	
	//cross product
	vector3f crossProduct(const vector3f &v)
	{
		vector3f cp;

		//cross product
		cp.x =	y * v.z - z * v.y;
		cp.y =	-( x * v.z - z * v.x );
		cp.z =	x * v.y - y * v.x;

		return cp;
	}

	//normalize
	void normalize()
	{
		float sumSquares = x*x + y*y + z*z;

		//dont normalise if vector is close enough
		if ( abs(sumSquares - 1.0) > VECTOR_TOLERANCE )
		{
			float L = sqrt(sumSquares);
			
			x /= L;
			y /= L;
			z /= L;
		}
	}

	//return normalize copy of current vector
	vector3f getNormalized()
	{
		//copy current quarternion and return conjugate
		vector3f v(*this);
		v.normalize();

		return v;
	}

	//dot product
	float dotProduct(const vector3f &v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	//shortcut for cross product
	vector3f operator *(vector3f &v)
	{
		return crossProduct(v);
	}

	//addition
	vector3f operator +(vector3f &v)
	{
		return vector3f(x + v.x, y + v.y, z + v.z);		 
	}

	//subtraction
	vector3f operator -(vector3f &v)
	{
		return vector3f(x - v.x, y - v.y, z - v.z);		 
	}
};

class quaternion
{
public:
	
	//members
	//------------------------------------------------------------------------------
	
	float x,y,z,w;

public:		
	
	//constructors
	//------------------------------------------------------------------------------

	//empty constructor
	quaternion() : x(0), y(0), z(0), w(0) {}
	
	//specific constructor
	quaternion(float xi, float yi, float zi, float wi) : x(xi), y(yi), z(zi), w(wi) {}

	//from vector
	quaternion(vector3f v) : x(v.x), y(v.y), z(v.z), w(0) {}

	//create from an angle and an arbitrary axis
	quaternion(float degrees, vector3f axis)
	{
		float theta = (degrees / 180.0f) * PI;			
		float sinTheta = sin( theta / 2.0f );
		float cosTheta = cos( theta / 2.0f );			
	
		//calculate quaternion values
		x = axis.x * sinTheta;
		y = axis.y * sinTheta;
		z = axis.z * sinTheta;
		w = cosTheta;
	}

	//methods
	//------------------------------------------------------------------------------

	//define quaternion multiplication operator
	quaternion operator *(const quaternion &b)
	{
		quaternion result;

		result.x = w * b.x + x * b.w + y * b.z - z * b.y;
		result.y = w * b.y - x * b.z + y * b.w + z * b.x;
		result.z = w * b.z + x * b.y - y * b.x + z * b.w;
		result.w = w * b.w - x * b.x - y * b.y - z * b.z;			

		//return new quaterion
		return(result);
	}

	//define vector multiplication operator
	vector3f operator *(const vector3f &vi)
	{
		//create quaternion from normalized vector
		vector3f vn(vi);
		vn.normalize();
		quaternion v(vn), result;
			
		//apply multiplications 
		result = v * getConjugate();
		result = *this * result;
	 
		return vector3f(result.x, result.y, result.z);
	}

	//normalise quaterion
	void normalize()
	{		  
		float sumSquares = x * x + y * y + z * z + w * w;
		
		if ( abs(sumSquares - 1.0) > QUATERNION_TOLERANCE )
		{			
			float L = sqrt(sumSquares);
		
			x /= L;
			y /= L;
			z /= L;
			w /= L;
		}
	}

	//return normalized copy of current quaternion
	quaternion getNormalized()
	{
		//copy current quarternion and return conjugate
		quaternion q(*this);
		q.normalize();

		return q;
	}

	//conjugate quaterion
	void conjugate()
	{
		x = -x;
		y = -y;
		z = -z;			
	}

	//return conjugate copy of current quaternion
	quaternion getConjugate()
	{
		//copy current quarternion and return conjugate
		quaternion q(*this);
		q.conjugate();

		return q;
	}

	//to vector
	vector3f toVector()
	{		
		return vector3f(x, y, z);		
	}

	//to matrix (homogenous 4x4 matrix)
	void toMatrix(float* matrix)
	{		
		// First row
		matrix[0]	= 1.0f - 2.0f * ( y * y + z * z );
		matrix[1]	= 2.0f * (x * y + z * w);
		matrix[2]	= 2.0f * (x * z - y * w);
		matrix[3]	= 0.0f;
		
		// Second row
		matrix[4]	= 2.0f * ( x * y - z * w );
		matrix[5]	= 1.0f - 2.0f * ( x * x + z * z );
		matrix[6]	= 2.0f * (z * y + x * w );
		matrix[7]	= 0.0f;

		// Third row
		matrix[8]	= 2.0f * ( x * z + y * w );
		matrix[9]	= 2.0f * ( y * z - x * w );
		matrix[10]	= 1.0f - 2.0f * ( x * x + y * y );
		matrix[11]	= 0.0f;

		// Fourth row
		matrix[12]	= 0;
		matrix[13]	= 0;
		matrix[14]	= 0;
		matrix[15]	= 1.0f;		
	}

};
