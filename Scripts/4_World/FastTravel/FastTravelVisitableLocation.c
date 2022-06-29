class DC_FastTravelVisitableLocation
{
	protected int m_LocationID;
	protected string m_RequiredTokenClassName;
	protected int m_RequiredTokenQuantity;
	
	void DC_FastTravelVisitableLocation(int locationID = -1, string requiredTokenClassName = "", int requiredTokenQuantity = 0)
	{
		SetLocationID(locationID);
		SetRequiredTokenClassName(requiredTokenClassName);
		SetRequiredTokenQuantity(requiredTokenQuantity);
	}
	
	void SetLocationID(int locationID)
	{
		m_LocationID = locationID;
	}
	
	int GetLocationID()
	{
		return m_LocationID;
	}
	
	void SetRequiredTokenClassName(string requiredTokenClassName)
	{
		m_RequiredTokenClassName = requiredTokenClassName;
	}
	
	string GetRequiredTokenClassName()
	{
		return m_RequiredTokenClassName;
	}
	
	void SetRequiredTokenQuantity(int requiredTokenQuantity)
	{
		m_RequiredTokenQuantity = requiredTokenQuantity;
		if(m_RequiredTokenQuantity < 0)
		{
			m_RequiredTokenQuantity = 0;
		}
	}
	
	int GetRequiredTokenQuantity()
	{
		if(m_RequiredTokenQuantity < 0)
		{
			m_RequiredTokenQuantity = 0;
		}
		
		return m_RequiredTokenQuantity;
	}
}