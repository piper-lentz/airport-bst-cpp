The problem this program solves:
Every flight booking, boarding pass and baggage tag identifies an airport by its three-letter IATA code (BOS for
Boston Logan, JFK for New York Kennedy, DAC for Dhaka). A travel company needs a fast lookup service that,
given a code, returns the airport's name, city, country and location, and that stays correct while airports are added
and removed from its database. Customer agents also need alphabetical listings and range queries such as "every
code from BOS to BWI".



How to run the program:

Navigate to folder:
- cd path/to/airport-bst-cpp

Compile:
- g++ -std=c++17 -O2 src/*.cpp -o airports

The fixed script (answers the task questions):
- ./airports > AirportOutput.txt

Session mode where you can type commands:
- ./airports session



Data credits:
I used data from OpenFlights.org to complete this project. 



Table 6:
| Build order | Height | Average depth | Time for 10,000 searches (ms) | Explanation |
|---|---|---|---|---|
| File order | 177 | 18.32 | 2.10 | This order will fall between sorted and balanced because it is in an unspecified order |
| Sorted order | 6071 | 3035.50 | 172.05 | This order produces a chain BST because every new value is greater than the previous |
| Balanced | 12 | 10.65 | 1.23 | Balanced order is the fastest because there are no chains in the BST, so the height is a minimum. Therefore, less comparisons need to be made, so it is the fastest. |



Example Session:

```text
> load data/airports.dat
Validated after each of 6072 inserts: all valid
Loaded 6072 airports (1626 lines skipped: no IATA code). Duplicates: 0
Height: 177  Average depth: 18.32
> find BOS
find BOS
Path: GKA AEY EGS BUJ BJA BSK BOY BNI BOH BOO BOU BOS
Comparisons: 12
Found: BOS - General Edward Lawrence Logan International Airport, Boston, United States

> find XYZ
find XYZ
Path: GKA MAG POM WWK YAM XFW XGN XLS XRY XVS YAI YAA XYA XYE
Comparisons: 14
XYZ not found

> range BOS BWI
range BOS BWI
BOS - General Edward Lawrence Logan International Airport, Boston, United States
BOU - Bourges Airport, Bourges, France
BOW - Bartow Municipal Airport, Bartow, United States
...
BWG - Bowling Green Warren County Regional Airport, Bowling Green, United States
BWH - Butterworth Airport, Butterworth, Malaysia
BWI - Baltimore/Washington International Thurgood Marshall Airport, Baltimore, United States
Found 113 airports, visited 127 nodes
> remove BOS
Removed BOS
> rebalance
Rebalanced 6071 airports
Height: 12  Average depth: 10.65
```

