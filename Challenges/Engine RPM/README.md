## Read Live Engine RPM
### Challenge
Using a BeagleBone Black and a Truck Cape, connect to an engine contoller that is broadcasting non-zero engine RPM. Gather this data using `candump`. Interpret the raw CAN frames and extract information for Engine RPM, or J1939 SPN 190. Plot 20 seconds of changing RPM with matplotlib. Print the properly labeled plot to PDF and show it to your instructor.  

### Objectives
  * Learn how to interface with Linux SocketCAN and can-utils
  * Be able to look up a signal definition in the J1939 Digital Annex (spreadsheet)
  * Use `grep` to search for specific strings from a `candump`
  * Have a reliable CAN datalogger for use in future projects
  * Plot data using `matplotlib` in Python.

### Suggested Materials
This exercise can be run with any Linux device with CAN hardware. An example of a commercial product with these features is the DG Technologies' Beacon device. An example of a hand built project is the BeagleBone Black with a TU TruckCape.

### Resources
  * J1939DA
  * Internet Access (you may want to share your PC's connection sharing)
