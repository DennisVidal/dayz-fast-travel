class DC_FastTravelConfig
{
	protected bool m_CreateLogs;
	protected float m_MessageDisplayTime;
	protected ref array<ref DC_FastTravelLocation> m_Locations;
	protected ref map<int, string> m_LocationMarkerTypes;
	
	void DC_FastTravelConfig(bool createLogs = true, float messageDisplayTime = 5.0)
	{
		
		m_CreateLogs = createLogs;
		m_MessageDisplayTime = messageDisplayTime;
		m_Locations = new array<ref DC_FastTravelLocation>;
		m_LocationMarkerTypes = new map<int, string>;
	}
	
	bool GetCreateLogs()
	{
		return m_CreateLogs;
	}
	
	void SetCreateLogs(bool createLogs)
	{
		m_CreateLogs = createLogs;
	}
	
	float GetMessageDisplayTime()
	{
		return m_MessageDisplayTime;
	}
	
	void SetMessageDisplayTime(float messageDisplayTime)
	{
		m_MessageDisplayTime = messageDisplayTime;
	}
	
	array<ref DC_FastTravelLocation> GetLocationData()
	{
		return m_Locations;
	}
	
	DC_FastTravelLocation GetLocationByID(int id)
	{
		if(id >= 0)
		{
			for(int i = 0; i < m_Locations.Count(); i++)
			{
				if(m_Locations.Get(i).GetID() == id)
				{
					return m_Locations.Get(i);
				}
			}
		}
		return null;
	}
	
	map<int, string> GetLocationMarkerTypes()
	{
		return m_LocationMarkerTypes;
	}
	
	string GetLocationMarkerTypeByID(int id)
	{
		string type = "";
		if(m_LocationMarkerTypes.Find(id, type))
		{
			return type;
		}
		return "";
	}
}