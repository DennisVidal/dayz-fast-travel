class DC_FastTravelMarker : BuildingSuper
{	
	protected int m_ParentLocationID;
	protected int m_LocationID;
	
	void DC_FastTravelMarker()
	{
		RegisterNetSyncVariableInt("m_ParentLocationID");
		RegisterNetSyncVariableInt("m_LocationID");
		
		m_ParentLocationID = -1;
		m_LocationID = -1;
	}
	
	override void SetActions()
	{
		AddAction(DC_ActionRequestFastTravel);
	}
	
	void SetIDs(int parentLocationID, int locationID)
	{
		m_ParentLocationID = parentLocationID;
		m_LocationID = locationID;
		SetSynchDirty();
	}
	
	void SetParentLocationID(int id)
	{
		m_ParentLocationID = id;
		SetSynchDirty();
	}
	
	int GetParentLocationID()
	{
		return m_ParentLocationID;
	}
	
	void SetLocationID(int id)
	{
		m_LocationID = id;
		SetSynchDirty();
	}
	
	int GetLocationID()
	{
		return m_LocationID;
	}
}