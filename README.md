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
Build         Height    Avg depth   Time for 10,000 searches (ms)   Explanation
File order    177       18.32       2.10       This order will fall between sorted and balanced because it is in an unspecified order
Sorted order  6071      3035.50     172.05       This order produces a chain BST because every new value is greater than the previous
Balanced      12        10.65       1.23       Balanced order is the fastest because there are no chains in the BST, so the height is a minimum. Therefore, less comparisons need to be made, so it is the fastest. 



Example Session:
Validated after each of 6072 inserts: all valid
Loaded 6072 airports (1626 lines skipped). Duplicates: 0
Height: 177  Average depth: 18.32
Commands: find, insert, remove, validate, range, rebalance, list, height, quit
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
BOX - Borroloola Airport, Borroloola, Australia
BOY - Bobo Dioulasso Airport, Bobo-dioulasso, Burkina Faso
BPC - Bamenda Airport, Bamenda, Cameroon
BPE - Qinhuangdao Beidaihe Airport, Bagan, Burma
BPF - Batuna Aerodrome, Batuna, Solomon Islands
BPG - Barra do Garças Airport, Barra Do Garcas, Brazil
BPH - Bislig Airport, , Philippines
BPI - Miley Memorial Field, Big Piney, United States
BPL - Alashankou Bole (Bortala) airport, Bole, China
BPM - Begumpet Airport, Hyderabad, India
BPN - Sultan Aji Muhamad Sulaiman Airport, Balikpapan, Indonesia
BPS - Porto Seguro Airport, Porto Seguro, Brazil
BPT - Southeast Texas Regional Airport, Beaumont, United States
BPX - Qamdo Bangda Airport, Bangda, China
BPY - Besalampy Airport, Besalampy, Madagascar
BQA - Dr.Juan C. Angara Airport, Baler, Philippines
BQB - Busselton Regional Airport, Brusselton, Australia
BQE - Bubaque Airport, Bubaque, Guinea-Bissau
BQG - Bogorodskoye Airport, Bogorodskoe, Russia
BQH - London Biggin Hill Airport, Biggin Hill, United Kingdom
BQJ - Batagay Airport, Batagay, Russia
BQK - Brunswick Golden Isles Airport, Brunswick, United States
BQL - Boulia Airport, Boulia, Australia
BQN - Rafael Hernandez Airport, Aguadilla, Puerto Rico
BQS - Ignatyevo Airport, Blagoveschensk, Russia
BQT - Brest Airport, Brest, Belarus
BQU - J F Mitchell Airport, Bequia, Saint Vincent and the Grenadines
BRA - Barreiras Airport, Barreiras, Brazil
BRC - San Carlos De Bariloche Airport, San Carlos De Bariloche, Argentina
BRD - Brainerd Lakes Regional Airport, Brainerd, United States
BRE - Bremen Airport, Bremen, Germany
BRI - Bari Karol Wojtyła Airport, Bari, Italy
BRK - Bourke Airport, Bourke, Australia
BRL - Southeast Iowa Regional Airport, Burlington, United States
BRM - Barquisimeto International Airport, Barquisimeto, Venezuela
BRN - Bern Belp Airport, Bern, Switzerland
BRO - Brownsville South Padre Island International Airport, Brownsville, United States
BRQ - Brno-Tuřany Airport, Brno, Czech Republic
BRR - Barra Airport, Barra, United Kingdom
BRS - Bristol Airport, Bristol, United Kingdom
BRT - Bathurst Island Airport, Bathurst Island, Australia
BRU - Brussels Airport, Brussels, Belgium
BRV - Bremerhaven Airport, Bremerhaven, Germany
BRW - Wiley Post Will Rogers Memorial Airport, Barrow, United States
BRX - Maria Montez International Airport, Barahona, Dominican Republic
BSA - Bosaso Airport, Bosaso, Somalia
BSB - Presidente Juscelino Kubistschek International Airport, Brasilia, Brazil
BSC - José Celestino Mutis Airport, Bahia Solano, Colombia
BSD - Baoshan Yunduan Airport, Baoshan, China
BSF - Bradshaw Army Airfield, Bradshaw Field, United States
BSG - Bata Airport, Bata, Equatorial Guinea
BSJ - Bairnsdale Airport, Bairnsdale, Australia
BSK - Biskra Airport, Biskra, Algeria
BSL - EuroAirport Basel-Mulhouse-Freiburg Airport, Mulhouse, France
BSO - Basco Airport, Basco, Philippines
BSR - Basrah International Airport, Basrah, Iraq
BST - Bost Airport, Lashkar Gah, Afghanistan
BSU - Basankusu Airport, Basankusu, Congo (Kinshasa)
BSX - Pathein Airport, Pathein, Burma
BTC - Batticaloa Airport, Batticaloa, Sri Lanka
BTE - Sherbro International Airport, Bonthe, Sierra Leone
BTH - Hang Nadim International Airport, Batam, Indonesia
BTI - Barter Island LRRS Airport, Barter Island, United States
BTJ - Sultan Iskandar Muda International Airport, Banda Aceh, Indonesia
BTK - Bratsk Airport, Bratsk, Russia
BTL - W K Kellogg Airport, Battle Creek, United States
BTM - Bert Mooney Airport, Butte, United States
BTR - Baton Rouge Metropolitan Airport, Baton Rouge, United States
BTS - M. R. Štefánik Airport, Bratislava, Slovakia
BTT - Bettles Airport, Bettles, United States
BTU - Bintulu Airport, Bintulu, Malaysia
BTV - Burlington International Airport, Burlington, United States
BTW - Batu Licin Airport, Batu Licin, Indonesia
BTZ - Bursa Airport, Bursa, Turkey
BUA - Buka Airport, Buka Island, Papua New Guinea
BUC - Burketown Airport, Burketown, Australia
BUD - Budapest Liszt Ferenc International Airport, Budapest, Hungary
BUF - Buffalo Niagara International Airport, Buffalo, United States
BUG - Benguela Airport, Benguela, Angola
BUI - Bokondini Airport, Bokondini-Papua Island, Indonesia
BUJ - Bou Saada Airport, Bou Saada, Algeria
BUL - Bulolo Airport, Bulolo, Papua New Guinea
BUN - Gerardo Tobar López Airport, Buenaventura, Colombia
BUO - Burao Airport, Burao, Somalia
BUP - Bhatinda Air Force Station, Bhatinda, India
BUQ - Joshua Mqabuko Nkomo International Airport, Bulawayo, Zimbabwe
BUR - Bob Hope Airport, Burbank, United States
BUS - Batumi International Airport, Batumi, Georgia
BUT - Bathpalathang Airport, Jakar, Bhutan
BUU - Muara Bungo Airport, Muara Bungo, Indonesia
BUW - Betoambari Airport, Bau-Bau, Indonesia
BUX - Bunia Airport, Bunia, Congo (Kinshasa)
BUY - Bunbury Airport, Bunbury, Australia
BUZ - Bushehr Airport, Bushehr, Iran
BVA - Paris Beauvais Tillé Airport, Beauvais, France
BVB - Atlas Brasil Cantanhede Airport, Boa Vista, Brazil
BVC - Rabil Airport, Boa Vista, Cape Verde
BVE - Brive Souillac Airport, Brive, France
BVG - Berlevåg Airport, Berlevag, Norway
BVH - Brigadeiro Camarão Airport, Vilhena, Brazil
BVI - Birdsville Airport, Birdsville, Australia
BVS - Breves Airport, Breves, Brazil
BVY - Beverly Municipal Airport, Beverly, United States
BWA - Gautam Buddha Airport, Bhairawa, Nepal
BWB - Barrow Island Airport, Barrow Island, Australia
BWE - Braunschweig-Wolfsburg Airport, Braunschweig, Germany
BWF - Barrow Walney Island Airport, Barrow Island, United Kingdom
BWG - Bowling Green Warren County Regional Airport, Bowling Green, United States
BWH - Butterworth Airport, Butterworth, Malaysia
BWI - Baltimore/Washington International Thurgood Marshall Airport, Baltimore, United States
Found 113 airports, visited 127 nodes
> remove BOS
Removed BOS
> rebalance
Rebalanced 6071 airports
Height: 12  Average depth: 10.65
> 


