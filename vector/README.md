# Abstract Data Type - Implementing a Vector

In the present repository I'm storing the codes created to implement a Vector.

<b>Lucas Gomes Dantas</b> (<dantaslucas@ufrn.edu.br>), student in the <b>Basic Data Structure I</b> class of <b>Prof. Dr. Selan
Rodrigues dos Santos</b> at <b>Federal University of Rio Grande do Norte</b>.

## Compiling and Running

* Clone this repository in any directory you want;
* Via prompt, go to the directory where you've cloned this repository;
* Type `make init` to create the project structure;
* Type `make` to compile the project.

There is already a driver testing some of the vector's functions. If you want to run this file, type: <code>./bin/vector</code>

## Including and using library

To use this library, you have to include the `vector.h` into your application. These vectors are instantiated as following:

* `sc::vector<T> v`

Where `sc` is the namespace (stands for sequential container), `<T>` is a type (e.g. string, int, float, double, etc.),  and 
`v` is the elements name.

## Possible errors and exceptions

While testing this library, the user may be confronted with the following errors:

* `std::out_of_range`

It appears when the program tries to access an element out of the vector's boundaries. e.g. Tried to `pop_back()` or
`pop_front` element of an empty vector. In any of these cases, a message informing the user about the occurred problem
will be displayed.

## License

    Copyright (C) 2017  Lucas Gomes Dantas
    Contact: <dantaslucas@ufrn.edu.br>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
