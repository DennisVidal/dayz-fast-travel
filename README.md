# DayZ Fast Travel

![An image of a fast travel board with the travel prompt](https://github.com/DennisVidal/DayZ-Fast-Travel/blob/main/DayZ_Mod_Fast_Travel.png)


This mod adds a fast travel system to DayZ with the aim of improving the player experience and giving server owners additional options to customize the gameplay of their servers. It comes with fast travel boards, which use DayZ's hiking trail boards as a base. Server owners can place these boards freely around the map to allow players to travel quickly between predefined locations if they have the required items. Locations appear as pins on the board, each with an action prompt consisting of the name of the selected location and travel cost.

The mod is highly customizable and usage examples include a simple travel network between traders, a way to access hard to reach or even walled of areas with high value loot at the cost of rare items, and a more immersive replacement for UI-based spawn selection mods.

## Core Features
- Fast travel boards that players can use to quickly travel between predefined locations
- Adjustable travel cost per location and destination
- Two variants of fast travel tickets to use as a starting point

---
## Requirements
The only dependency of this mod is currently the [Community Framework](https://steamcommunity.com/workshop/filedetails/?id=1559212036 "Steam workshop page of Community Framework") as it is used to streamline the networking, and as such, it is required to run the mod.

---
## Setup
### Clients
1. Download the mod from the [workshop page](https://steamcommunity.com/sharedfiles/filedetails/?id=1843000706 "Steam workshop page of Fast Travel")
2. Add the mod, [CF](https://steamcommunity.com/workshop/filedetails/?id=1559212036 "Steam workshop page of CF") and any other mods you need to your `-mod` launch parameter (each mod is separated by a ";")
3. Start your game and join your server

Alternatively, it's probably easier to just use either DayZ's launcher or the [DayZSA launcher](https://dayzsalauncher.com/ "Website of the DayZSA launcher") to join a server.

### Server
1. Download the mod from the [workshop page](https://steamcommunity.com/sharedfiles/filedetails/?id=1843000706 "Steam workshop page of Fast Travel")
2. Add the mod, [CF](https://steamcommunity.com/workshop/filedetails/?id=1559212036 "Steam workshop page of CF") and any other mods you need to the `-mod` launch parameter of your server (each mod is separated by a ";")
3. Start your server to generate the config file in your server's profile folder
4. Adjust the values in the config to your liking and spawn fast travel boards wherever you want
5. Restart your server to load the new config


---
## Spawning the Fast Travel Boards
While there are different ways to spawn objects in DayZ, the fast travel boards of this mod require some additional setup to assign locations to them. To make this process easier, the mods comes with a function that does all of the setup for you, in the form of `DC_FastTravel.SpawnBoard(int id, vector position, vector orientation)`.
The first parameter `id` is the `m_ID` config variable of whatever location you want to assign and display on the board. The second and third parameters `position` and `orientation` are the world-space location and rotation of the board respectively and are passed in as strings.

The actual spawning is done by adding this function to your server mission's init file:
1. Open the `init.c` file in your server's mission folder
2. Spawn the board in the `main` function using the 'DC_FastTravel.SpawnBoard' function: 
```cs
void main()
{ 
  DC_FastTravel.SpawnBoard(1, "3692.1 403.512 5988.1", "163 0 0"); //Green Mountain with m_ID = 1 in the config
  DC_FastTravel.SpawnBoard(2, "8345.2 293.5 6002", "193 0 0"); // Kumyrna with m_ID = 2 in the config

   //Remaining code in main...
```

Depending on the map you are using, you'll have to adjust the board texture to display the correct map. To change which version spawns, you can add a fourth `mapID` parameter to the `SpawnBoard` function in the following form:
`DC_FastTravel.SpawnBoard(id, position, orientation, mapID);`
By default this mod supports Chernarus (0), Livonia (1), and Valning (2). While both Chernarus and Livonia are included in DayZ, Valning additionally requires the [Valning Tourist Map mod by Sylver](https://steamcommunity.com/sharedfiles/filedetails/?id=1843000706 "Link to the Valning Tourist Map mod") to display the right map on the board


---
## Configuration
The config gets created automatically once you start the server for the first time after installing the mod. After the config file has been generated, you can navigate to the server's profile folder to find it. It should be labeled `DC_FastTravelConfig`. If you haven't set a profile folder for your server yet, you might want to consider doing so with the -profiles launch parameter, as it makes it easier to find the config and any log files in general. The config itself is a normal JSON file and can therefore be edited rather easily. The following table explains its contents:

<table>
  <thead>
    <tr>
      <th>Variable</th>
      <th>Explanation</th>
      <th>Example</th>
      <th>Note</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><b>m_CreateLogs</b></td>
      <td>Decides whether logs should be created in the script*.log files</td>
      <td><pre lang="json">"m_CreateLogs": 1</pre></td>
      <td></td>
    </tr>
    <tr>
      <td><b>m_MessageDisplayTime</b></td>
      <td>The display time in seconds for messages</td>
      <td><pre lang="json">"m_MessageDisplayTime": 3.0</pre></td>
      <td>Currently unused</td>
    </tr> 
    <tr>
      <td><b>m_Locations</b></td>
          <td>An array that contains the information of all configured locations</td>
          <td><pre lang="json">"m_Locations": [
    {
        "m_ID": 1,
        "m_Name":"Green Mountain",
        "m_MarkerCoordinates": [
            ...
        ],
        "m_MarkerType": 0,
        "m_LocationCoordinates": [
            ...
        ],
        "m_VisitableLocations": [
            ...
        ]
    },
    {
        "m_ID": 2,
        "m_Name":"Kumyrna",
        "m_MarkerCoordinates": [
            ...
        ],
        "m_MarkerType": 0,
        "m_LocationCoordinates": [
            ...
        ],
        "m_VisitableLocations": [
            ...
        ]
    }
]</pre></td>
      <td>Each location block contains a
          <b><i>m_ID</i></b>,
          <b><i>m_Name</i></b>,
          <b><i>m_MarkerCoordinates</i></b>,
          <b><i>m_MarkerType</i></b>,
          <b><i>m_LocationCoordinates</i></b>,
          and 
          <b><i>m_VisitableLocations</i></b>
          <br>
          <br>
          Consecutive location blocks are separated by commas
      </td>
    </tr>
    <tr>
      <td><b>m_ID</b></td>
      <td>The ID of a location</td>
      <td><pre lang="json">"m_ID": 4</pre></td>
      <td>This is an arbitary integer used to identify a location independent of its name. It is used as the <b><i>id</b></i> parameter when spawing the board as well as the <b><i>m_LocationID</b></i> variable to set this location as visitable from another</td>
    </tr>
    <tr>
      <td><b>m_Name</b></td>
      <td>The displayed name of the location on the board</td>
      <td><pre lang="json">"m_Name": "Cherno"</pre></td>
      <td></td>
    </tr> 
     <tr>
      <td><b>m_MarkerCoordinates</b></td>
      <td>The location of the marker for this location on the board</td>
      <td><pre lang="json">"m_MarkerCoordinates": [
    3692.1,
    -1,
    5988.1
]</pre></td>
      <td>
        The marker is independent of any other location data and could, for example, be placed on the side of the map while the actual spawn points are located in the center of the map
        <br>
        <br>
        The y-value is unused and should remain set to -1. If all components are set to -1, the first position in <b><i>m_LocationCoordinates</i></b> will be used instead
        </td>
    </tr> 
     <tr>
      <td><b>m_MarkerType</b></td>
      <td>The type of marker to be used</td>
      <td><pre lang="json">"m_MarkerType": 0</pre></td>
      <td>
        This can usually be left set to 0, as it is only needed if you want to assign a custom pin to this location
        <br>
        <br>
        Should be one of the entries in <b><i>m_LocationMarkerTypes</i></b>
      </td>
    </tr> 
    <tr>
      <td><b>m_LocationCoordinates</b></td>
      <td>An array of possible spawn locations when a player is traveling to this location</td>
       <td><pre lang="json">"m_LocationCoordinates": [
    {
        "m_Coordinates": [
            3699.5,
            -1,
            5991
        ],
        "m_Radius": 4
    },
    {
        "m_Coordinates": [
            4374,
            -1,
            1273
        ],
        "m_Radius": 10
    }
]</pre></td>
      <td>
       Each spawn point consists of <b><i>m_Coordinates</i></b> and a <b><i>m_Radius</i></b>
       <br>
       <br>
       Consecutive spawn points are separated by a comma
       <br>
       <br>
       The actual spawn position when traveling to a location is chosen at random from all its spawn points and within the chosen spawn point from a random location in <b><i>m_Radius</i></b> around <b><i>m_Coordinates</i></b> that offers enough space for the player
       <br>
       <br>
       In tight areas such as buildings, it is preferable to define multiple smaller spawn points instead of a single big one, as that could lead to players spawing inside the walls of the object
      </td>
    </tr> 
     <tr>
      <td><b>m_Coordinates</b></td>
      <td>The center of a spawn point</td>
      <td><pre lang="json">"m_Coordinates": [
    3699.5,
    -1,
    5991
]</pre></td>
      <td>If the y-value is set to -1, the terrain height at that xz-position will be used instead</td>
    </tr>
     <tr>
      <td><b>m_Radius</b></td>
      <td>The radius around a spawn point that a location can be chosen from</td>
      <td><pre lang="json">"m_Radius": 4</pre></td>
      <td></td>
    </tr> 
     <tr>
      <td><b>m_VisitableLocations</b></td>
      <td>An array of locations that can be visited from a location</td>
      <td><pre lang="json">"m_VisitableLocations": [
    {
        "m_LocationID": 2,
        "m_RequiredTokenClassName": "DC_FastTravelTicket",
        "m_RequiredTokenQuantity": 1
    },
    {
        "m_LocationID": 5,
        "m_RequiredTokenClassName": "DC_FastTravelTicket",
        "m_RequiredTokenQuantity": 1
    }
]</pre></td>
      <td>
        Consecutive locations are separated by a comma
        <br>
        <br>
        Setting <b><i>m_RequiredTokenClassName</i></b> to "" and <b><i>m_RequiredTokenQuantity</i></b> to "0" will make fast traveling to this location free
      </td>
    </tr> 
    <tr>
      <td><b>m_LocationID</b></td>
      <td>The <b><i>m_ID</i></b> variable of the location you want to set as visitable</td>
      <td><pre lang="json">"m_LocationID": 2</pre></td>
      <td></td>
    </tr> 
    <tr>
      <td><b>m_RequiredTokenClassName</b></td>
      <td>The class name of the item that is required to fast travel to this location</td>
      <td><pre lang="json">"m_RequiredTokenClassName": "DC_FastTravelTicket"</pre></td>
      <td></td>
    </tr>
    <tr>
      <td><b>m_RequiredTokenQuantity</b></td>
      <td>The amount of <b><i>m_RequiredTokenClassName</i></b> required in your inventory to fast travel</td>
      <td><pre lang="json">"m_RequiredTokenQuantity": 2</pre></td>
      <td></td>
    </tr> 
    <tr>
      <td><b>m_LocationMarkerTypes</b></td>
      <td>A map of possible marker pins</td>
      <td><pre lang="json">"m_LocationMarkerTypes": {
    "0": "DC_FastTravelMarkerNeedle"
}</pre></td>
      <td>Usually doesn't need to be touched, as it is only used for defining custom markers</td>
    </tr> 
  </tbody>
</table>
        
---
## Troubleshooting
From my experience, the cause of most issues is a simple syntax error in the config file. Therefore, the first thing you should try is running the config through some JSON validator like [this](https://jsonformatter.curiousconcept.com/) one.

If there are no errors in your config, check that you didn't set a float value instead of an integer one for certain variables in the config, e.g., setting the location id to 1.0 instead of just 1.

In case none of the above is the case, feel free to add me on either Discord (deadcraft) or [Steam](https://steamcommunity.com/id/Deadcraft "Steam profile of Dennis Vidal"), and I'll try to assist you with the problem.

---
## Usage & Monetization
- Distributing, reuploading, and repacking of this mod or any of its contents is not allowed
- Derivatives and modifications of this mod require my prior permission
- Monetizing features of this mod is prohibited
- Should your server break [Bohemia Interactive's monetization guidelines](https://www.bohemia.net/monetization "Bohemia Interactive's monetization guidelines") in any way, you are also prohibited from using this mod on your server
