Moonlanding AADL + FMI
======================

About
-----

This example is adapted from the Moonlanding example from Peter Fritzon, as detailed in the tutorial : https://openmodelica.org/images/docs/userdocs/modprod2012-tutorial1-Peter-Fritzson-ModelicaTutorial.pdf

We adapted this example so that

* the environment is modeled as a Modelica example, and later turned into a FMU
* the controller is implemented as a C function,
* the controller is integrated to the environment in an AADL model

The `fmu2aadl` generates the corresponding AADL for the environment
elements, and the C wrapper function.

`ocarina` is used to assemble all elements together.

Note
----

The generated FMU targets GNU/Linux 64 bits
