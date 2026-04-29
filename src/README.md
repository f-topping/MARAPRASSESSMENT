README
SCIF20002:Programming and Data analysis for Scientists Assessment 2 Mini Project and Report

This project is part of an assessment. it includes three main parts and it
is suggested that you view part 2, then 3, before 1, as this was how it was developed. 

The first is the part 1 section, considering SEIReq.cpp. this code solves the SEIR differential equations, and outputs the results against time. 
To yield data, you must first compile the file, by typing "g++ SEIReq.cpp -o program" into the terminal,
next, run and pipeline the data into a csv file with "./program > part_one.csv"
Visualising the data will be covered in the third part.

The second part is the monte carlo sim. it concerns the Makefile, lattice.h, lattice.cpp, member.h, member.cpp, and main.cpp.
The purpose of this part was to develop an object oriented approach to modelling the infectious agents
in the SEIR model. To yield data, you must compile all the files together, 
by typing "make program", and then ./program to run it. Doing so will produce your data, a lovely csv file, but also a load of 
nasty object files, that we can remove with "make clean". Again, visualising
the data will be covered in the third part.

The third part was data visualisation with python. the files associated with
this are the two csv files made from the prior two parts (although only one
is needed), and plotSEIR.py. dependencies include the matplotlib and pandas libraries.
to run this part, you must ensure its configured to the csv you have. if you
wish to view the second parts csv, then you need not worry and can skip ahead.
otherwise, you want to type "nano plotSEIR.py" and replace the csv file where
indicated. Truly, you need not see the graphical representation, as the raw
csv files are just as readable, and much easier turned into graphs using Microsoft Excel.
To run the python, type "python3 plotSEIR.py" into the terminal and enter. If all is good, a popup should appear presenting your graph.

If you feel you must, you can "SEIReq.cpp", "main.cpp", or "lattice.cpp" and tweak some of the values inside if youre intrested in what may happen.
It is not recommended. You do so at your own risk.
