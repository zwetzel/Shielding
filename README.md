# Shielding
Basic shielding designed to measure energy attenuation and particle path deviation

This file is a highly edited version of the Geant4 built-in example B4.

All of the source code files can be found in the B4d/src folder. Each source file has a list of the headers that it uses at the beginning of the file. The headers can be found in the "include" folder. The only header that I remember editing was PGA2.hh, so I'll upload that one. The rest should be standard Geant4 headers that you can find online. here is an example of a header for the cylinder class G4Tubs.hh https://www-zeuthen.desy.de/geant4/geant4.9.3.b01/G4Tubs_8hh-source.html

Once you have the source code and headers copied over, you'll want to create a new directory where you will build your executable. mine is called "ex". Go into "ex" and type "cmake ../B4d". This should compile the source code into "ex". Once it is done, type "make" while in "ex" to create the executable file. It should be name "exampleB4d".

To run the executable, type "./exampleB4d". This should build the geometry and open a visualizer window so you can see if the geometry looks correct. Once the executable is build you need to feed it an input file to have it actually do anything. Mine is called "stuff.in". You should copy this into your "ex" folder. Run the input by typing "/control/execute stuff.in" after you have build the executable.

The input file uses an energy spectrum given to us by the guys at the NSC to correctly model the neutrons coming out of the core. That spectrum goes up to 20 MeV and is in a file called "Watt_neutron_pdf.gdat". You should copy this into your "ex" folder.
