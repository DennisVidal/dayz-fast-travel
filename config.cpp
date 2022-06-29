class CfgPatches
{
	class DC_FastTravel
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"JM_CF_Scripts"
		};
	};
};

class CfgMods
{
	class DC_FastTravel
	{
		dir = "DC_FastTravel";
		name = "FastTravel";
		credits = "";
		author = "Deadcraft";
		authorID = "711";
		version = "0.1";
		type = "mod";
		dependencies[] =
		{
			"World",
			"Mission"
		}; 
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] =
				{
					"DC_FastTravel/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] =
				{
					"DC_FastTravel/Scripts/5_Mission"
				};
			};
		};
	};
};

class CfgModels
{
	class FastTravelMarkerNeedle
	{
		sections[] =
		{
			"everything"
		};
	};
	class FastTravelTicket
	{
		sections[] =
		{
			"everything"
		};
	};
};

class CfgVehicles
{
	class HouseNoDestruct;
	class DC_FastTravelBoard : HouseNoDestruct
	{
		scope = 1;
		model = "DZ\structures\signs\tourist\trailmap_noarrow.p3d";
	};

	class DC_FastTravelBoardLivonia : DC_FastTravelBoard
	{
		scope = 1;
		model = "DZ\structures_bliss\signs\tourist\trailmap_enoch.p3d";
	};

	class DC_FastTravelBoardValning : DC_FastTravelBoard
	{
		scope = 1;
	};
	
	class DC_FastTravelMarker : HouseNoDestruct
	{
	};
	
	class DC_FastTravelMarkerNeedle : DC_FastTravelMarker
	{
		model = "DC_FastTravel\Data\FastTravelMarkerNeedle.p3d";
		hiddenSelections[] = 
		{
			"everything"
		};
	};
	
	class DC_FastTravelMarkerNeedleCurrentLocation: DC_FastTravelMarkerNeedle
	{
		scope = 1;
		hiddenSelectionsTextures[] =
		{
			"DC_FastTravel\Data\FastTravelMarkerNeedleRed_co.paa"
		};
	};
	
	class DC_FastTravelMarkerNeedleVisitableLocation: DC_FastTravelMarkerNeedle
	{
		scope = 1;
		hiddenSelectionsTextures[] =
		{
			"DC_FastTravel\Data\FastTravelMarkerNeedleGreen_co.paa"
		};
	};
	
	class Inventory_Base;
	class DC_FastTravelTicket : Inventory_Base
	{
		scope = 2;
		displayName = "Fast Travel Ticket";
		descriptionShort = "A ticket used for fast traveling at fast travel boards";
		model = "DC_FastTravel\Data\FastTravelTicket.p3d";
		rotationFlags = 1;
		canBeSplit = 1;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 3;
		itemSize[] = {1,1};
		weight = 100;
		hiddenSelections[] = 
		{
			"everything"
		};
		hiddenSelectionsTextures[] =
		{
			"DC_FastTravel\Data\FastTravelTicket_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"DC_FastTravel\Data\FastTravelTicket.rvmat"
		};
	};
	
	class DC_FastTravelTicketGolden : DC_FastTravelTicket
	{
		scope = 2;
		displayName = "Golden Fast Travel Ticket";
		descriptionShort = "A golden ticket used for fast traveling at fast travel boards";
		varQuantityInit = 0;
		varQuantityMin = 0;
		varQuantityMax = 0;
		hiddenSelectionsTextures[] =
		{
			"DC_FastTravel\Data\FastTravelTicketGolden_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"DC_FastTravel\Data\FastTravelTicketGolden.rvmat"
		};
	};
};
