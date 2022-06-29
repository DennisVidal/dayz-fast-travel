class DC_FastTravelLocationCoordinates
{
	protected vector m_Coordinates;
	protected float m_Radius;
	
	void DC_FastTravelLocationCoordinates(vector coordinates = "-1 -1 -1", float radius = 0.0)
	{
		SetCoordinates(coordinates);
		SetRadius(radius);
	}
	
	void SetCoordinates(vector coordinates)
	{
		m_Coordinates = coordinates;
	}
	
	vector GetRawCoordinates()
	{
		return m_Coordinates;
	}
	
	vector GetCoordinates()
	{
		vector coordinates = m_Coordinates;
		if(coordinates[1] == -1 && coordinates != "-1 -1 -1")
		{
			coordinates[1] = GetGame().SurfaceY(coordinates[0], coordinates[2]);
		}
		
		return coordinates;
	}
	
	void SetRadius(float radius)
	{
		m_Radius = radius;
		if(m_Radius < 0)
		{
			m_Radius = 0;
		}
	}
	
	float GetRadius()
	{
		if(m_Radius < 0)
		{
			m_Radius = 0;
		}
		
		return m_Radius;
	}
	
	vector GetRandomCoordinatesWithinRadius()
	{
		vector coordinates = GetRawCoordinates();
		if(m_Radius > 0)
		{
			float angle = Math.RandomFloat01() * Math.PI2;
			float x = Math.Cos(angle) * GetRadius();
			float z = Math.Sin(angle) * GetRadius();
			coordinates = coordinates + Vector(x, 0, z);
			if(coordinates[1] == -1)
			{
				coordinates[1] = GetGame().SurfaceY(coordinates[0], coordinates[2]);
			}
		}
				
		return coordinates;
	}
	
	vector TryToGetSafeRandomCoordinatesWithinRadius()
	{		
		vector coordinates, hitPosition, hitNormal;
		float hitFraction;
		Object hitObject;
		coordinates = GetRandomCoordinatesWithinRadius();
		DayZPhysics.SphereCastBullet(coordinates + "0 0.3 0", coordinates + "0 1.7 0", 0.2, (PhxInteractionLayers.BUILDING | PhxInteractionLayers.VEHICLE_NOTERRAIN), NULL, hitObject, hitPosition, hitNormal, hitFraction);
		if(hitPosition == vector.Zero) //might still spawn in big objects
		{
			return coordinates;
		}
		return "-1 -1 -1";
	}
}