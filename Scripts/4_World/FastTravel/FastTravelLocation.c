class DC_FastTravelLocation
{
	protected int m_ID;
	protected string m_Name;
	protected vector m_MarkerCoordinates;
	protected int m_MarkerType;
	protected ref array<ref DC_FastTravelLocationCoordinates> m_LocationCoordinates;
	protected ref array<ref DC_FastTravelVisitableLocation> m_VisitableLocations;
	
	void DC_FastTravelLocation(int id = -1, string name = "", vector markerCoordinates = "-1 -1 -1", int markerType = 0)
	{
		SetID(id);
		SetName(name);
		SetMarkerCoordinates(markerCoordinates);
		SetMarkerType(markerType);
		
		m_LocationCoordinates = new array<ref DC_FastTravelLocationCoordinates>;
		m_VisitableLocations = new array<ref DC_FastTravelVisitableLocation>;
	}
	
	void SetID(int id)
	{
		m_ID = id;
		if(m_ID < -1)
		{
			m_ID = -1;
		}
	}
		
	int GetID()
	{
		if(m_ID < -1)
		{
			m_ID = -1;
		}
		return m_ID;
	}
	
	void SetName(string name)
	{
		m_Name = name;
	}
	
	string GetName()
	{
		return m_Name;
	}
	
	void SetMarkerCoordinates(vector markerCoordinates)
	{
		m_MarkerCoordinates = markerCoordinates;
	}
	
	vector GetMarkerCoordinates()
	{
		if(m_MarkerCoordinates == "-1 -1 -1")
		{
			if(m_LocationCoordinates.IsValidIndex(0))
			{
				return m_LocationCoordinates.Get(0).GetCoordinates();
			}
		}
		return m_MarkerCoordinates;
	}
	
	void SetMarkerType(int markerType)
	{
		m_MarkerType = markerType;
	}
	
	int GetMarkerType()
	{
		return m_MarkerType;
	}
	
	array<ref DC_FastTravelLocationCoordinates> GetLocationCoordinates()
	{
		return m_LocationCoordinates;
	}
	
	array<ref DC_FastTravelVisitableLocation> GetVisitableLocations()
	{
		return m_VisitableLocations;
	}
	
	vector GetSafeCoordinates(int coordinatesIndex = -1, int maxTries = 10)
	{
		vector safeCoords = "-1 -1 -1";
		if(m_LocationCoordinates.Count() > 0)
		{
			if(coordinatesIndex < m_LocationCoordinates.Count() && m_LocationCoordinates.Count() > 0)
			{
				if(coordinatesIndex < 0)
				{
					for(int i = 0; i < maxTries; i++)
					{
						if(coordinatesIndex < 0)
						{
							safeCoords = m_LocationCoordinates.Get(Math.RandomInt(0, m_LocationCoordinates.Count())).TryToGetSafeRandomCoordinatesWithinRadius();
						}
						else
						{
							safeCoords = m_LocationCoordinates.Get(coordinatesIndex).TryToGetSafeRandomCoordinatesWithinRadius();
						}
						
						if(safeCoords != "-1 -1 -1")
						{
							return safeCoords;
						}
					}
				}
			}
		}
		return "-1 -1 -1";
	}
	
	DC_FastTravelVisitableLocation GetVisitableLocationByID(int id)
	{
		for(int i = 0; i < m_VisitableLocations.Count(); i++)
		{
			if(m_VisitableLocations.Get(i).GetLocationID() == id)
			{
				return m_VisitableLocations.Get(i);
			}
		}
		return null;
	}
}