class DC_FastTravelBoard : BuildingSuper
{	
	protected vector m_LocalMapSWCorner; //Bottom left corner of the map on the board object in local space (x is the offset outwards from the dayz trail sign)
	protected float m_LocalMapXMultiplier; //multiplier for 1km in x direction (-z on the dayz trail sign)
	protected float m_LocalMapYMultiplier;//multiplier for 1km in y direction
	
	protected ref DC_FastTravelLocation m_Location;
	protected DC_FastTravelMarker m_BoardLocationMarker;
	protected ref array<DC_FastTravelMarker> m_LocationMarkers;

	void DC_FastTravelBoard()
	{
		m_Location = null;
		m_BoardLocationMarker = null;
		m_LocationMarkers =  new array<DC_FastTravelMarker>; 
		m_LocalMapSWCorner = "-0.037 -0.72751 0.94527";
		m_LocalMapXMultiplier = -0.10209375;
		m_LocalMapYMultiplier = 0.10073642857;
	}
	
	bool InitWithLocationID(int id)
	{
		if(GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			if(!m_Location)
			{
				if(id > -1)
				{
					m_Location = DC_FastTravel.GetInstance().GetConfig().GetLocationByID(id);
					if(m_Location)
					{
						SpawnBoardLocationMarker();
						SpawnVisitableLocationMarkers();
						return true;
					}
					else
					{
						if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Location with ID " + id + " could not be found");}
					}
				}
				else
				{
					if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Tried to initialize a board with ID " + id + ", but you can't initialize a board with an ID less than 0");}
				}
			}
			else
			{
				if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Tried to initialize a board with ID " + id + ", but the board was already initialized with ID " + m_Location.GetID());}
			}
		}
		return false;
	}
	
	protected void SpawnBoardLocationMarker()
	{
		if(GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			if(m_Location)
			{
				if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Trying to spawn the board location marker for board with location ID " + m_Location.GetID());}
				m_BoardLocationMarker = DC_FastTravelMarker.Cast(GetGame().CreateObject(GetMarkerTypeByID(m_Location.GetMarkerType()) + "CurrentLocation", GetPosition(), false, false, false));
				if(m_BoardLocationMarker)
				{
					m_BoardLocationMarker.SetIDs(m_Location.GetID(), m_Location.GetID());
					
					m_BoardLocationMarker.SetPosition(GetPositionOnBoardMap(m_Location.GetMarkerCoordinates()));
					if(m_BoardLocationMarker.IsKindOf("DC_FastTravelMarkerNeedle"))
					{
						m_BoardLocationMarker.SetOrientation(GetOrientation() + Vector(0, 20 - Math.RandomFloatInclusive(0,30), 15 - Math.RandomFloatInclusive(0,30)));
					}
					else
					{
						m_BoardLocationMarker.SetOrientation(GetOrientation());
					}
					
					if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Succesfully spawned the board location marker for board with location ID " + m_Location.GetID());}
				}
				else
				{
					if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Could not spawn board location marker for board with location ID " + m_Location.GetID());}				
				}
			}
		}
	}
	
	protected void SpawnVisitableLocationMarkers()
	{
		if(GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			if(m_Location)
			{
				if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Trying to spawn the visitable location markers for board with location ID " + m_Location.GetID());}
				vector markerLocation;
				DC_FastTravelLocation location;
				array <ref DC_FastTravelVisitableLocation> visitableLocations = m_Location.GetVisitableLocations();
				for(int i = 0; i < visitableLocations.Count(); i++)
				{
					location = DC_FastTravel.GetInstance().GetConfig().GetLocationByID(visitableLocations.Get(i).GetLocationID());
					if(location)
					{
						markerLocation = location.GetMarkerCoordinates();
						if(markerLocation != "-1 -1 -1")
						{
							m_LocationMarkers.InsertAt(DC_FastTravelMarker.Cast(GetGame().CreateObject(GetMarkerTypeByID(location.GetMarkerType()) + "VisitableLocation", GetPosition(), false, false, false)), i);
							if(m_LocationMarkers.Get(i))
							{
								m_LocationMarkers.Get(i).SetIDs(m_Location.GetID(), visitableLocations.Get(i).GetLocationID());
								
								m_LocationMarkers.Get(i).SetPosition(GetPositionOnBoardMap(markerLocation));
								if(m_LocationMarkers.Get(i).IsKindOf("DC_FastTravelMarkerNeedle"))
								{
									m_LocationMarkers.Get(i).SetOrientation(GetOrientation() + Vector(0, 20 - Math.RandomFloatInclusive(0,30), 15 - Math.RandomFloatInclusive(0,30)));
								}
								else
								{
									m_LocationMarkers.Get(i).SetOrientation(GetOrientation());
								}
																
								if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Succesfully spawned visitable location marker " + (i+1) +" for board with location ID " + m_Location.GetID());}	
							}
							else
							{
								if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Could not spawn visitable location marker " + (i+1) +" for board with location ID " + m_Location.GetID());}				
							}
						}
					}
				}
			}
		}
	}
	
	protected vector GetPositionOnBoardMap(vector worldCoordinates)
	{
		return CoordToParent(m_LocalMapSWCorner + Vector(0, (worldCoordinates[2] / 1000) * m_LocalMapYMultiplier, (worldCoordinates[0] / 1000) * m_LocalMapXMultiplier));
	}
	
	protected string GetMarkerTypeByID(int markerID)
	{
		string type = DC_FastTravel.GetInstance().GetConfig().GetLocationMarkerTypeByID(markerID);
		if(type != "")
		{
			return type;
		}
		
		return "DC_FastTravelMarkerNeedle";
	}
}