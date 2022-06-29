#define DC_FASTTRAVEL

class DC_FastTravel
{
	const protected static string m_ConfigPath = "$profile:DC_FastTravelConfig.json";
	
	protected static ref DC_FastTravel Instance;
	
	protected ref DC_FastTravelConfig m_Config;
	
	void DC_FastTravel()
	{
		m_Config = null;
		if(GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			GetRPCManager().AddRPC("DC_FastTravel", "FastTravelDataRequest", this, SingleplayerExecutionType.Server);
			GetRPCManager().AddRPC("DC_FastTravel", "FastTravelToLocationRequest", this, SingleplayerExecutionType.Server);
			LoadConfig();
		}
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
			GetRPCManager().AddRPC("DC_FastTravel", "FastTravelDataRequestResponse", this, SingleplayerExecutionType.Client);
			GetRPCManager().AddRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", this, SingleplayerExecutionType.Client);
			RequestConfigFromServer();
		}
		
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}
	
	static DC_FastTravel GetInstance()
	{
		if(!Instance)
		{
			Instance = new DC_FastTravel();
		}
		return Instance;
	}
	
	DC_FastTravelConfig GetConfig()
	{
		if(!m_Config)
		{
			if(GetGame().IsServer() || !GetGame().IsMultiplayer())
			{
				LoadConfig();
			}
			else
			{
				RequestConfigFromServer();
			}
			
		}
		return m_Config;
	}
	
	protected void LoadConfig()
	{
		m_Config = new DC_FastTravelConfig();
		
		if (FileExist(m_ConfigPath))
        {
            JsonFileLoader<DC_FastTravelConfig>.JsonLoadFile(m_ConfigPath, m_Config);
        }
        else
        {
            CreateDefaultConfig();
        }
	}
	
	protected void CreateDefaultConfig()
	{
		m_Config = new DC_FastTravelConfig();
		
		//Locations
		m_Config.GetLocationData().Insert(new DC_FastTravelLocation(1, "Green Mountain", "3692.1 -1 5988.1"));
			m_Config.GetLocationData().Get(0).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(3699.5, -1, 5991), 4));
			m_Config.GetLocationData().Get(0).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(3701.3, -1, 5977.5), 3));
			m_Config.GetLocationData().Get(0).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(3724, -1, 5970), 5));
			m_Config.GetLocationData().Get(0).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(3723.7, -1, 5958), 2));
			m_Config.GetLocationData().Get(0).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(3711.6, -1, 6002.4), 2));
			m_Config.GetLocationData().Get(0).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(3733.6, -1, 6013.6), 8));
			m_Config.GetLocationData().Get(0).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(3688.3, -1, 6006), 3));
			m_Config.GetLocationData().Get(0).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(3697, -1, 6015), 2));
			m_Config.GetLocationData().Get(0).GetVisitableLocations().Insert(new DC_FastTravelVisitableLocation(2, "DC_FastTravelTicket", 1));
		
		m_Config.GetLocationData().Insert(new DC_FastTravelLocation(2, "Kumyrna", "8345.2 -1 6002"));
			m_Config.GetLocationData().Get(1).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(8348, -1, 6002), 2));
			m_Config.GetLocationData().Get(1).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(8349, -1, 5998), 2));
			m_Config.GetLocationData().Get(1).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(8353, -1, 5989), 4));
			m_Config.GetLocationData().Get(1).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(8360, -1, 5985), 6));
			m_Config.GetLocationData().Get(1).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(8369, -1, 5988), 2));
			m_Config.GetLocationData().Get(1).GetLocationCoordinates().Insert(new DC_FastTravelLocationCoordinates(Vector(8329, -1, 5995), 7));
			m_Config.GetLocationData().Get(1).GetVisitableLocations().Insert(new DC_FastTravelVisitableLocation(1, "DC_FastTravelTicket", 1));
		
		//MarkerTypes
		m_Config.GetLocationMarkerTypes().Insert(0, "DC_FastTravelMarkerNeedle");
		
        JsonFileLoader<DC_FastTravelConfig>.JsonSaveFile(m_ConfigPath, m_Config);
	}
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//serverside
	void FastTravelDataRequest(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
        if(type == CallType.Server)
		{
			GetRPCManager().SendRPC("DC_FastTravel", "FastTravelDataRequestResponse", new Param1<DC_FastTravelConfig>(m_Config), true, sender);
		}
	}
	
	void FastTravelToLocationRequest(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		Param2<int, int> params;
        if(!ctx.Read(params)) return;
        if(type == CallType.Server)
		{
			PlayerBase player = GetPlayerByID(sender.GetId());
			if(player && !player.IsInVehicle())
			{
				DC_FastTravelLocation currentLocation = m_Config.GetLocationByID(params.param1);
				if(currentLocation)
				{
					DC_FastTravelLocation targetLocation = m_Config.GetLocationByID(params.param2);
					if(targetLocation)
					{
						DC_FastTravelVisitableLocation visitableTargetLocation = currentLocation.GetVisitableLocationByID(targetLocation.GetID());
						if(visitableTargetLocation)
						{
							if(PlayerHasEnoughTokens(player, visitableTargetLocation.GetRequiredTokenClassName(), visitableTargetLocation.GetRequiredTokenQuantity()))
							{
								vector targetCoordinates = targetLocation.GetSafeCoordinates(-1 , 20);
								if(targetCoordinates != "-1 -1 -1")
								{
									if(RemoveTokens(player, visitableTargetLocation.GetRequiredTokenClassName(), visitableTargetLocation.GetRequiredTokenQuantity()))
									{
										player.SetPosition(targetCoordinates);
										GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", new Param1<int>(0), true, sender);
									}
									else
									{
										if(m_Config.GetCreateLogs()) {Print("[DC_FastTravel]	Player with PlainID: " + sender.GetPlainId() + " and Name: " + sender.GetName() + ", from ID: " + params.param1 + ", to ID: " + params.param2 + ": Tokens could not be removed");}//tokens could not be removed
										GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", new Param1<int>(1), true, sender);
									}
								}
								else
								{
									if(m_Config.GetCreateLogs()) {Print("[DC_FastTravel]	Player with PlainID: " + sender.GetPlainId() + " and Name: " + sender.GetName() + ", from ID: " + params.param1 + ", to ID: " + params.param2 + ": No safe location found");}//No safe location found
									GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", new Param1<int>(2), true, sender);
								}
							}
							else
							{
								if(m_Config.GetCreateLogs()) {Print("[DC_FastTravel]	Player with PlainID: " + sender.GetPlainId() + " and Name: " + sender.GetName() + ", from ID: " + params.param1 + ", to ID: " + params.param2 + ": Not enough tokens on player");}//Not enough tokens on player
								GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", new Param1<int>(3), true, sender);
							}
						}
						else
						{
							if(m_Config.GetCreateLogs()) {Print("[DC_FastTravel]	Player with PlainID: " + sender.GetPlainId() + " and Name: " + sender.GetName() + ", from ID: " + params.param1 + ", to ID: " + params.param2 + ": Location can't be visited from current location");}//location can't be visited from current location
							GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", new Param1<int>(4), true, sender);
						}
					}
					else
					{
						if(m_Config.GetCreateLogs()) {Print("[DC_FastTravel]	Player with PlainID: " + sender.GetPlainId() + " and Name: " + sender.GetName() + ", from ID: " + params.param1 + ", to ID: " + params.param2 + ": Target location does not exist");}//target location does not exist
						GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", new Param1<int>(5), true, sender);
					}
				}
				else
				{
					if(m_Config.GetCreateLogs()) {Print("[DC_FastTravel]	Player with PlainID: " + sender.GetPlainId() + " and Name: " + sender.GetName() + ", from ID: " + params.param1 + ", to ID: " + params.param2 + ": Current location does not exist");}//current location does not exist
					GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", new Param1<int>(6), true, sender);
				}
			}
			else
			{
				if(m_Config.GetCreateLogs()) {Print("[DC_FastTravel]	Player with PlainID: " + sender.GetPlainId() + " and Name: " + sender.GetName() + ", from ID: " + params.param1 + ", to ID: " + params.param2 + ": Can't fast travel in vehicles (or player does not exist)");}//Can't fast travel in vehicles (or player does not exist)
				GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequestResponse", new Param1<int>(7), true, sender);
			}
		}
	}
	
	//clientside
	void RequestConfigFromServer()
	{
		GetRPCManager().SendRPC("DC_FastTravel", "FastTravelDataRequest", null, true);
	}
	
	void RequestFastTravel(int currentLocationID, int targetLocationID)
	{
		if(currentLocationID >= 0 && targetLocationID >= 0)
		{
			GetRPCManager().SendRPC("DC_FastTravel", "FastTravelToLocationRequest", new Param2<int, int>(currentLocationID, targetLocationID), true);
		}
	}
	
	void FastTravelDataRequestResponse(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		Param1<DC_FastTravelConfig> param;
        if(!ctx.Read(param)) return;
        if(type == CallType.Client)
		{
			m_Config = param.param1;
		}
	}
	
	void FastTravelToLocationRequestResponse(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		Param1<bool> param;
        if(!ctx.Read(param)) return;
        if(type == CallType.Client)
		{
			ShowMessage(param.param1);
		}
	}
	
	//-----------------------------------------------------------------------------------------------
	
	protected void ShowMessage(int messageCode)
	{
	}
	
	protected PlayerBase GetPlayerByID(string id)
	{
		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		for(int i = 0; i < players.Count(); i++)
		{
			if(players.Get(i).GetIdentity().GetId() == id)
			{
				return PlayerBase.Cast(players.Get(i));
			}
		}
		return null;
	}
	
	protected bool PlayerHasEnoughTokens(PlayerBase player, string tokenClassName, int tokenQuantity)
	{
		if(!player || tokenQuantity < 0)
		{
			return false;
		}
		
		if(tokenQuantity == 0)
		{
			return true;
		}
		
		if(tokenClassName == "")
		{
			return false;
		}
		
		int tokenCount = 0;
		array<EntityAI> inventory = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);
		ItemBase item;
		
		for(int i = 0; i < inventory.Count(); i++)
		{
			if(tokenClassName == inventory.Get(i).GetType())
			{
				Class.CastTo(item, inventory.Get(i));
				if(item)
				{					
					tokenCount += GetItemQuantity(item);
					if(tokenCount >= tokenQuantity)
					{
						return true;					
					}
				}
			}
		}
		return false;
	}
	
	protected bool RemoveTokens(PlayerBase player, string tokenClassName, int quantityToRemove)
	{
		if(!player || quantityToRemove < 0)
		{
			return false;
		}
		
		if(quantityToRemove == 0)
		{
			return true;
		}
		
		if(tokenClassName == "")
		{
			return false;
		}
		
		
		array<EntityAI> inventory = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);
		ItemBase item;
		int quantityLeft = quantityToRemove;
		int itemQuantity;
		for(int i = 0; i < inventory.Count(); i++)
		{
			if(tokenClassName == inventory.Get(i).GetType())
			{
				Class.CastTo(item, inventory.Get(i));
				if(item)
				{
					itemQuantity = GetItemQuantity(item);
										
					if(quantityLeft >= itemQuantity)
					{
						quantityLeft -= itemQuantity;
						GetGame().ObjectDelete(item);
					}
					else
					{
						SetItemQuantity(item, itemQuantity - quantityLeft);
						quantityLeft -= quantityLeft;
					}
					
					if(quantityLeft == 0)
					{
						return true;
					}
				}
			}
		}
		
		return false;
	}
	
	protected void SetItemQuantity(ItemBase item, int quantity)
	{
		if(!item || quantity < 0)
		{
			return;
		}
		
		if(item.IsMagazine())
		{
			Magazine magazineItem = Magazine.Cast(item);
			if(magazineItem)
			{
				magazineItem.ServerSetAmmoCount(quantity);
			}
		}
		else
		{
			item.SetQuantity(quantity);
		}
	}
	
	protected int GetItemQuantity(ItemBase item)
	{
		if(!item)
		{
			return 0;
		}
		
		if(item.IsMagazine())
		{
			Magazine magazineItem = Magazine.Cast(item);
			if(magazineItem)
			{
				return magazineItem.GetAmmoCount();
			}
		}
		else
		{
			if(item.GetQuantity() <= 0)
			{
				if(item.GetQuantityMax() <= 0)
				{
					return 1;
				}
			}
			return item.GetQuantity();
		}
		return 0;
	}
	
	static string GetBoardClassName(int mapID)
	{
		if(mapID == 1)
		{
			return "DC_FastTravelBoardLivonia";
		}
		else if(mapID == 2)
		{
			return "DC_FastTravelBoardValning";
		}
		return "DC_FastTravelBoard";
	}

	static Object SpawnBoard(int id, vector position, vector orientation, int mapID = 0) //mapID -> 0 = Chernarus, 1 = Livonia, 2 = Valning
	{
		if(GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			DC_FastTravelBoard board = DC_FastTravelBoard.Cast(GetGame().CreateObject(GetBoardClassName(mapID), position));
			if(board)
			{
				if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Successfully created board object at position " + position.ToString());}
				board.SetPosition(position);
	   			board.SetOrientation(orientation);
	    		board.SetOrientation(board.GetOrientation());
	    		board.Update();
	    		board.SetAffectPathgraph(true, false);
	    		if(board.CanAffectPathgraph())
				{
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, board);
				}
								
				if(board.InitWithLocationID(id))
				{
					if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Successfully initialized board object at position " + position.ToString() + " with ID " + id);}
				}
				else
				{
					if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Could not initialize board object at position " + position.ToString() + " with ID " + id);}
				}
				
				return board;
			}
			else
			{
				if(DC_FastTravel.GetInstance().GetConfig().GetCreateLogs()) {Print("[DC_FastTravel]	Could not create board object at position " + position.ToString());}
			}
		}
		
	    return null;
	}
}