Recitation 2
============

Recitation Project

We have been given a file of chemical formulae, specifically hydrocarbons. Hydrocarbons consist of only hydrogen and carbon atoms.

Each line of the file contains the name of the chemical followed by its molecular formula which will be in the form:

C#H#

where # is the number of carbon (C) and hydrogen (H) atoms.
(No name in the file contains blanks.)

Because hyrdocarbons with the same molecular formula can appear in many structural forms and each of the forms has a different name, the same molecular formula might appear more than once in the file with different names. (e.g.: Butane and 2-methylpropane both have the molecular formula C4H10.)

Our goal is to keep one entry for each unique molecular formula along with all the names for that formula and then display all these entries in order by ascending number of carbon atoms. (We can do this without actually sorting the items by making multiple passes over the vector, first printing all forumlas with one carbon, then all with two carbons, etc.)

Each molecular formula will be kept in a struct with three fields:

the name(s) for formula

the number of carbon atoms

the number of hydrogen atoms

We will be storing all these structs in a vector.

An example

Suppose this is the file:

n-Butane C4H10

Propyne C3H3

1,3-Butadiyne C4H2

Hexane C6H14

Butane C4H10

iso-Butane C4H10

Pentane C5H12

Your program should store these five entries and then display something 
like:

C3H3 Propyne

C4H10 n-Butane Butane iso-Butane

C4H2 1,3-Butadiyne

C5H12 Pentane

C6H14 Hexane

Notice that the output is "sorted" only by the number of carbon atoms.
There is no attempt to sort by anything else.
Or, put another way: all other orderings show simply the order the items were taken from the file.

Notes
As you learned in CS1114, you should solve a problem by breaking it into parts and subparts and writing functions for each.