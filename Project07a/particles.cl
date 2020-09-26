typedef float4 point;
typedef float4 vector;
typedef float4 color; // r, g, b, a
typedef float4 sphere; //x, y, z, r

constant sphere Sphere1 = (sphere)( -135., -800., 0.,  600. );
constant sphere Sphere2 = (sphere)( -115., -640., 0., 480.);
constant sphere Sphere3 = (sphere)( -45., -4000., 0., 2000.);
constant sphere Sphere4 = (sphere)( 700., -800., 0.,  600. );
constant sphere Sphere5 = (sphere)( 680., -640., 0., 480.);


vector
Bounce( vector in, vector n )
{
	vector out = in - n*(vector)( 2.*dot(in.xyz, n.xyz) );
	out.w = 0.;
	return out;
}

vector
BounceSphere( point p, vector v, sphere s )
{
	vector n;
	n.xyz = fast_normalize( p.xyz - s.xyz );
	n.w = 0.;
	return Bounce( v, n );
}

bool
IsInsideSphere( point p, sphere s )
{
	float r = fast_length( p.xyz - s.xyz );
	return  ( r < s.w );
}

kernel
void
Particle( global point *dPobj, global vector *dVel, global color *dCobj )
{
	const float4 G       = (float4) ( 0., -9.8, 0., 0. );
	const float  DT      = 0.01;
	const sphere Sphere1 = (sphere)( -135., -800., 0.,  600. );
	const sphere Sphere2 = (sphere)( -115., -640., 0., 480.);
	const sphere Sphere3 = (sphere)( -100., -4000., 0.,  2000. );
	const sphere Sphere4 = (sphere)( 700., -800., 0.,  600. );
	const sphere Sphere5 = (sphere)( 680., -640., 0.,  480. );
	int gid = get_global_id( 0 );

	// extract the position and velocity for this particle:
	point  p = dPobj[gid];
	vector v = dVel[gid];

	// remember that you also need to extract this particle's color
	// and change it in some way that is obviously correct
	color c = dCobj[gid];

	// advance the particle:

	point  pp = p + v*DT + G*(point)( .5*DT*DT*DT );
	vector vp = v + G*DT;
	color cc =  c + v*DT * G*(point) (.5*DT*DT); 
	pp.w = 1.;
	vp.w = 0.;
	cc.w = (0, .0f, .4f);
	// test against the first sphere here:

	if( IsInsideSphere( pp, Sphere1 ) )
	{
		vp = BounceSphere( p, v, Sphere1 );
		pp = p + vp*DT + G*(point)( .5*DT*DT );
		cc = c + v*DT;
	}

	// test against the second sphere here:
	if( IsInsideSphere( pp, Sphere2 ) )
	{
		vp = BounceSphere( p, v, Sphere2 );
		pp = p + vp*DT + G*(point)( .5*DT*DT );
		cc =  c + v*DT;
	}


		if( IsInsideSphere( pp, Sphere3 ) )
	{
		vp = BounceSphere( p, v, Sphere3 );
		pp = p + vp*DT + G*(point)( .5*DT*DT );
		cc =  c + v*DT;
	}

		if( IsInsideSphere( pp, Sphere4 ) )
	{
		vp = BounceSphere( p, v, Sphere3 );
		pp = p + vp*DT + G*(point)( .5*DT*DT );
		cc =  c + v*DT;
	}

			if( IsInsideSphere( pp, Sphere5 ) )
	{
		vp = BounceSphere( p, v, Sphere3 );
		pp = p + vp*DT + G*(point)( .5*DT*DT );
		cc = c + v*DT;
	}


	dPobj[gid] = pp;
	dVel[gid]  = vp;
	dCobj[gid] = cc;
}
