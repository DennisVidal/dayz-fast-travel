# DayZ Fast Travel

![An image of a fast travel board with the travel prompt](https://github.com/DennisVidal/DayZ-Fast-Travel/blob/main/DayZ_Mod_Fast_Travel.png)

<b>Note:</b> The code for this mod isn't the best and a rework is long overdue. Although I've worked on it a while ago, I haven't gotten around to finishing it yet. Once I got more information I'll update the workshop page.

## What does this mod do?
This mod adds a fast travel system to DayZ. It allows for the placement and configuration of boards around the map through which players can fast travel to certain preconfigured locations. The configured visitable locations appear as pins on the board's map. The cost for fast traveling can be configured individually for each board and visitable location. The mod can be found [here](https://steamcommunity.com/sharedfiles/filedetails/?id=1843000706 "Steam workshop page of Fast Travel").

This mod requires [CF](https://steamcommunity.com/workshop/filedetails/?id=1559212036 "Steam workshop page of CF") to be loaded as well. The fast travel board utilises the model of the hiking trail boards that are already located around the map, it does however count them as different items and thus does not affect the already existing boards.

---
## How do I set up this mod?
### Clients
1. Download the mod from the [workshop page](https://steamcommunity.com/sharedfiles/filedetails/?id=1843000706 "Steam workshop page of Fast Travel")
2. Add the mod, [CF](https://steamcommunity.com/workshop/filedetails/?id=1559212036 "Steam workshop page of CF") and any other mods you need to your `-mod` launch parameter
3. Start your game and join your server

Alternatively, it's probably easier to just use either DayZ's launcher or the [DayZSA launcher](https://dayzsalauncher.com/ "Website of the DayZSA launcher") to join a server.

### Server
1. Download the mod from the [workshop page](https://steamcommunity.com/sharedfiles/filedetails/?id=1843000706 "Steam workshop page of Fast Travel")
2. Add the mod, [CF](https://steamcommunity.com/workshop/filedetails/?id=1559212036 "Steam workshop page of CF") and any other mods you need to the `-mod` launch parameter of your server
3. Start your server to generate the config file in your server's profile folder
4. Adjust the values in the config to your liking and spawn fast travel boards wherever you want
5. Start your server again

---
## How do I spawn the fast travel boards?
Unlike with most mods spawning the board objects through one of the normal ways will not work with this mod. It will spawn a board but without the functionality as no location gets assigned for it. To keep spawing the boards relatively simple the mod provides a static function in the DC_FastTravel class called 'SpawnBoard', hence boards can be spawned by simply using `DC_FastTravel.SpawnBoard(int id, vector position, vector orientation)` with the correct parameters in the init file of your server's mission.
1. Open the `init.c` file in your server's mission folder
2. Spawn the board in the `main` function using the 'DC_FastTravel.SpawnBoard' function: 
```cs
void main()
{ 
  DC_FastTravel.SpawnBoard(1, "3692.1 403.512 5988.1", "163 0 0"); //Green Mountain
  DC_FastTravel.SpawnBoard(2, "8345.2 293.5 6002", "193 0 0"); // Kumyrna
   
   //...
```
The `SpawnObject` function takes three parameters: an `id`, a `position` and an `orientation`.

The `id` corresponds to the `m_ID` variable configured for a location in the config file.

The `position` parameter is just a vector denoting the world-space position of the fast travel board. Note that vectors in Enforce are represented by a string in which each component is separated by a space. The board model also doesn't have its origin at the bottom, so you might have to offset the position a small amount along the y-axis to get the intended placement position.

The last parameter `orientation` is the rotation of the board. It is another vector in which each component is the angle in degrees around the corresponding axis. 

The easiest approach to find both the position and orientation for a fast travel board is probably to use some admin tool to get those values from a fitting location.


---
## How do I configure this mod?
After the config file is generated, you can navigate to the profile folder of your server to find the config. If you haven't set a profile folder for your server yet, you might want to consider doing so with the `-profiles` launch parameter, as it makes it easier to find the config and any log files in general. 
In the profile folder you should find a file labeled `DC_FastTravelConfig`. The config itself is a normal Json file and can therefore be edited rather easily. The following table explains its contents:

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
      <td>Decides whether logs should be created in the script*.log files.</td>
      <td>"m_CreateLogs":&nbsp;1</td>
      <td></td>
    </tr>
    <tr>
      <td><b>m_MessageDisplayTime</b></td>
      <td>The display time in seconds for messages.</td>
      <td>"m_MessageDisplayTime":&nbsp;3.0</td>
      <td>Currently unused.</td>
    </tr> 
    <tr>
      <td><b>m_Locations</b></td>
      <td>An array that contains the information of all configured locations.</td>
      <td>
         "m_Locations":&nbsp;[<br>
         &emsp;{<br>
         &emsp;&emsp;"m_ID":&nbsp;1,<br>
         &emsp;&emsp;"m_Name":&nbsp;"Green&nbsp;Mountain",<br>
         &emsp;&emsp;"m_MarkerCoordinates":&nbsp;[<br>
         &emsp;&emsp;&emsp;...<br>
         &emsp;&emsp;],<br>
         &emsp;&emsp;"m_MarkerType":&nbsp;0,<br>
         &emsp;&emsp;"m_LocationCoordinates":&nbsp;[<br>
         &emsp;&emsp;&emsp;...<br>
         &emsp;&emsp;],<br>
         &emsp;&emsp;"m_VisitableLocations":&nbsp;[<br>
         &emsp;&emsp;&emsp;...<br>
         &emsp;&emsp;]<br>
         &emsp;},<br>
         &emsp;{<br>
         &emsp;&emsp;"m_ID":&nbsp;2,<br>
         &emsp;&emsp;"m_Name":&nbsp;"Kumyrna",<br>
         &emsp;&emsp;"m_MarkerCoordinates":&nbsp;[<br>
         &emsp;&emsp;&emsp;...<br>
         &emsp;&emsp;],<br>
         &emsp;&emsp;"m_MarkerType":&nbsp;0,<br>
         &emsp;&emsp;"m_LocationCoordinates":&nbsp;[<br>
         &emsp;&emsp;&emsp;...<br>
         &emsp;&emsp;],<br>
         &emsp;&emsp;"m_VisitableLocations":&nbsp;[<br>
         &emsp;&emsp;&emsp;...<br>
         &emsp;&emsp;]<br>
         &emsp;}<br>
         ]<br>
      </td>
      <td>Each location block contains a
          <b><i>m_ID</i></b>,
          <b><i>m_Name</i></b>,
          <b><i>m_MarkerCoordinates</i></b>,
          <b><i>m_MarkerType</i></b>,
          <b><i>m_LocationCoordinates</i></b>,
          and 
          <b><i>m_VisitableLocations</i></b>.
          <br>
          <br>
          Consecutive location blocks are separated by commas.
      </td>
    </tr>
    <tr>
      <td><b>m_ID</b></td>
      <td>The ID of a location</td>
      <td>"m_ID":&nbsp;4</td>
      <td>This is an arbitary integer used to identify a location independent of its name. It is used as the <b><i>id</b></i> parameter when spawing the board as well as the <b><i>m_LocationID</b></i> variable to set this location as visitable from another.</td>
    </tr>
    <tr>
      <td><b>m_Name</b></td>
      <td>The displayed name of the location on the board.</td>
      <td>"m_Name":&nbsp;"Cherno"</td>
      <td></td>
    </tr> 
     <tr>
      <td><b>m_MarkerCoordinates</b></td>
      <td>The location of the marker for this location on the board.</td>
      <td>
        "m_MarkerCoordinates":&nbsp;[<br>
        &emsp;3692.1,<br>
        &emsp;-1,<br>
        &emsp;5988.1<br>
        ]<br>
      </td>
      <td>
        The marker is independent of any other location data. It could for example be placed on the side of the map while the actual spawn points are located in the center of the map.
        <br>
        <br>
        The y-value is unused and should remain set to -1. If all components are set to -1 the firt position in <b><i>m_LocationCoordinates</i></b> will be used instead.
        </td>
    </tr> 
     <tr>
      <td><b>m_MarkerType</b></td>
      <td>The type of marker to be used.</td>
      <td>"m_MarkerType":&nbsp;0</td>
      <td>
        This can usually be left set to 0 as it is only needed if you want to assign a custom pin to this location.
        <br>
        <br>
        Should be one of the entries in <b><i>m_LocationMarkerTypes</i></b>.
      </td>
    </tr> 
    <tr>
      <td><b>m_LocationCoordinates</b></td>
      <td>An array of possible spawn locations when a player is traveling to this location.</td>
       <td>
        "m_LocationCoordinates":&nbsp;[<br>
         &emsp;{<br>
         &emsp;&emsp;"m_Coordinates":&nbsp;[<br>
         &emsp;&emsp;&emsp;3699.5,<br>
         &emsp;&emsp;&emsp;-1,<br>
         &emsp;&emsp;&emsp;5991<br>
         &emsp;&emsp;],<br>
         &emsp;&emsp;"m_Radius":&nbsp;4<br>
         &emsp;},<br>
         &emsp;{<br>
         &emsp;&emsp;"m_Coordinates":&nbsp;[<br>
         &emsp;&emsp;&emsp;4374,<br>
         &emsp;&emsp;&emsp;-1,<br>
         &emsp;&emsp;&emsp;1273<br>
         &emsp;&emsp;],<br>
         &emsp;&emsp;"m_Radius":&nbsp;10<br>
         &emsp;}<br>
         ]<br>
      </td>
      <td>
       Each spawn point consists of <b><i>m_Coordinates</i></b> and a <b><i>m_Radius</i></b>.
       <br>
       <br>
       Consecutive spawn points are separated by a comma.
       <br>
       <br>
       The actual spawn position when traveling to a location is chosen at random from all its spawn points and within the chosen spawn point from a random location in <b><i>m_Radius</i></b> around <b><i>m_Coordinates</i></b> that offers enough space for the player.
       <br>
       <br>
       In tight areas (such as buildings) it is preferable to define multiple smaller spawn points instead of a single big one as that could lead to player spawing inside the walls of the object.
      </td>
    </tr> 
     <tr>
      <td><b>m_Coordinates</b></td>
      <td>The center of a spawn point.</td>
      <td>
        "m_Coordinates":&nbsp;[<br>
        &emsp;3699.5,<br>
        &emsp;-1,<br>
        &emsp;5991<br>
        ]<br>
      </td>
      <td>If the y-value is set to -1, the terrain height at that xz-position will be used instead.</td>
    </tr>
     <tr>
      <td><b>m_Radius</b></td>
      <td>The radius around a spawn point that a location can be chosen from.</td>
      <td>"m_Radius":&nbsp;4</td>
      <td></td>
    </tr> 
     <tr>
      <td><b>m_VisitableLocations</b></td>
      <td>An array of locations that can be visited from a location.</td>
      <td>
      "m_VisitableLocations":&nbsp;[<br>
      &emsp;{<br>
      &emsp;&emsp;"m_LocationID":&nbsp;2,<br>
      &emsp;&emsp;"m_RequiredTokenClassName":&nbsp;"DC_FastTravelTicket",<br>
      &emsp;&emsp;"m_RequiredTokenQuantity":&nbsp;1<br>
      &emsp;},<br>
      &emsp;{<br>
      &emsp;&emsp;"m_LocationID":&nbsp;5,<br>
      &emsp;&emsp;"m_RequiredTokenClassName":&nbsp;"DC_FastTravelTicket",<br>
      &emsp;&emsp;"m_RequiredTokenQuantity":&nbsp;1<br>
      &emsp;}<br>
      ]<br>
      </td>
      <td>
        Consecutive locations are separated by a comma.
        <br>
        <br>
        Setting <b><i>m_RequiredTokenClassName</i></b> to "" and <b><i>m_RequiredTokenQuantity </i></b> to "0" will make fast traveling to this location free.
      </td>
    </tr> 
    <tr>
      <td><b>m_LocationID</b></td>
      <td>The <b><i>m_ID</i></b> variable of the location you want to set as visitable.</td>
      <td>"m_LocationID":&nbsp;2</td>
      <td></td>
    </tr> 
    <tr>
      <td><b>m_RequiredTokenClassName</b></td>
      <td>The class name of the item that is to be required to fast travel to this location.</td>
      <td>"m_RequiredTokenClassName":&nbsp;"DC_FastTravelTicket"</td>
      <td></td>
    </tr>
    <tr>
      <td><b>m_RequiredTokenQuantity</b></td>
      <td>The amount of <b><i>m_RequiredTokenClassName</i></b> required in your inventory to fast travel.</td>
      <td>"m_RequiredTokenQuantity":&nbsp;2</td>
      <td></td>
    </tr> 
    <tr>
      <td><b>m_LocationMarkerTypes</b></td>
      <td>A map of possible marker pins.</td>
      <td>
        "m_LocationMarkerTypes":&nbsp;{<br>
        &emsp;"0":&nbsp;"DC_FastTravelMarkerNeedle",<br>
        &emsp;"1":&nbsp;"FastTravelMarkerHouseShaped"<br>
        }<br>
      </td>
      <td>Usually doesn't need to be touched as it is onlu used for defining custom markers.</td>
    </tr> 
  </tbody>
</table>

## I'm having some sort of issue with this mod, what can I do?

Feel free to add me on either Discord(Deadcraft#8378) or [Steam](https://steamcommunity.com/id/Deadcraft "Steam profile of Dennis Vidal") and I'll try to assist you with the problem.

