class DC_ActionRequestFastTravel : ActionInteractBase
{
	protected string m_ActionText;
	
	void DC_ActionOpenBankingMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEIDX_ERECT;
		m_HUDCursorIcon = CursorIcons.Cursor;
		
		m_ActionText = "";
	}
	
	override string GetText()
	{
		return m_ActionText;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		
		if(target.GetObject().IsKindOf("DC_FastTravelMarker"))
		{
			DC_FastTravelMarker locationMarker = DC_FastTravelMarker.Cast(target.GetObject()); 
			if(locationMarker)
			{
				if(locationMarker.GetParentLocationID() != locationMarker.GetLocationID())
				{
					DC_FastTravelLocation parentLocation = DC_FastTravel.GetInstance().GetConfig().GetLocationByID(locationMarker.GetParentLocationID());
					if(parentLocation)
					{	
						DC_FastTravelLocation location = DC_FastTravel.GetInstance().GetConfig().GetLocationByID(locationMarker.GetLocationID());
						if(location)
						{
							DC_FastTravelVisitableLocation visitableLocation = parentLocation.GetVisitableLocationByID(locationMarker.GetLocationID());
							if(visitableLocation)
							{
								SetActionText(location.GetName(), GetDisplayName(visitableLocation.GetRequiredTokenClassName()), visitableLocation.GetRequiredTokenQuantity());
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}
	
	override void OnExecuteClient(ActionData action_data)
	{
		DC_FastTravelMarker locationMarker = DC_FastTravelMarker.Cast(action_data.m_Target.GetObject()); 
		if(locationMarker)
		{
			DC_FastTravel.GetInstance().RequestFastTravel(locationMarker.GetParentLocationID(), locationMarker.GetLocationID());
		}
	}
	
	void SetActionText(string targetLocationName, string targetLocationTokenName, int targetLocationTokenCost)
	{
		m_ActionText = "";
		if(targetLocationName != "")
		{
			m_ActionText += "Fast travel to " + targetLocationName;
			if(targetLocationTokenCost > 0 && targetLocationTokenName != "")
			{
				m_ActionText += " for " + targetLocationTokenCost.ToString() + " " + targetLocationTokenName;
			}
		}
	}
	
	string GetDisplayName(string className)
	{
		if(GetGame().ConfigIsExisting(CFG_VEHICLESPATH + " " + className + " displayName"))
		{
			return GetGame().ConfigGetTextOut(CFG_VEHICLESPATH + " " + className + " displayName");
		}
		else if(GetGame().ConfigIsExisting(CFG_MAGAZINESPATH + " " + className + " displayName"))
		{
			return GetGame().ConfigGetTextOut(CFG_MAGAZINESPATH + " " + className + " displayName");
		}
		return className;
	}
}