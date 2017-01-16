# SmartEverything ST LPS25H  pressure Sensor
----

This is a library for the ST LPS25H component.

The LPS25H is an ultra compact absolute piezoresistive pressure sensor.
It includes a monolithic sensing element and an IC interface able to take the information 
from the sensing element and to provide a digital signal to the external world.

The sensing element consists of a suspended membrane realized inside a single mono-silicon substrate. 
It is capable to detect the absolute pressure and is manufactured with a dedicated process developed by ST.

The membrane is very small compared to the traditionally built silicon micromachined membranes. 
Membrane breakage is prevented by an intrinsic mechanical stopper..


[* ST LPS25H Home Page *](http://www.stmicroelectronics.com.cn/web/catalog/sense_power/FM89/SC1316/PF255230)

Host control and result reading is performed using an I2C interface, no extra pin are required.

It was principally designed to work with the SmartEverything board, but could
be easily adapt and use on every Arduino and Arduino Certified boards.

Written by Seve <seve@axelelettronica.it>.

## Repository Contents
-------------------
* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **library.properties** - General library properties for the Arduino package manager.

## Releases
---
#### v1.1.1 Second Release 18-Dec-2015
* Change example to be more Arduino boards compatible and not only for ASME boards family.

#### v1.1.0 Second Release 18-Dec-2015
* Fixed Issue:<br>
    Fix Pressure example: Add Wire.begin() to initiate the Wire library and join the I2C bus<br>.

#### v1.0.0 First Release

## Documentation
--------------

* **[Installing an Arduino Library Guide](http://www.arduino.cc/en/Guide/Libraries#toc3)** - How to install a SmartEverything library on the Arduino IDE using the Library Manager


## License Information
-------------------

Copyright (c) Amel Technology. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA


