# Abstract Data Type - Implementing a Dictionary

In the present repository I'm storing the codes created to implement a Dictionary.

<b>Lucas Gomes Dantas</b> (<dantaslucas@ufrn.edu.br>), student in the <b>Basic Data Structure I</b> class of <b>Prof. Dr. Selan
Rodrigues dos Santos</b> at <b>Federal University of Rio Grande do Norte</b>.

## Compiling and Running

* Clone this repository in any directory you want;
* Via prompt, go to the directory where you've cloned this repository;
* Type `make init` to create the project structure;
* Type `make` to compile the project.

There is already a driver testing some of the hash table's functions. If you want to run it, type: <code>./bin/dictionary_test</code>

## Including and using library

Were implemented two types of dictionary, under `dal.h` and `dsal.h`. The first one stands for Dictionary with Array List and the elements are stored in a unsorted array. The second one stands for Dictionary with Sorted Array List and the elements are stored in a sorted array. 

You may choose to use any of those two libraries. They both follow the same way to instantiate:

* `ac::DAL<Key, Data, KeyComparator> dict`

Where `ac` is the namespace (stands for associative container), `DAL` is the name of the class with unsorted array (can be replaced by `DSAL` if client wants to use the sorted version) ,`<Key>` is the element's key, `Data` is the value of the element, `KeyComparator` is the functor of comparison (default funtion is std::less) and `dict` is the dictionary's name.

## Possible errors and exceptions

Errors, for this implementation, were treated in a very simple way. The functions will return a `false` when they're not able to perform their actions and a `true` when possible.

Also, in some cases, there might be a `std::out_of_range`, throwed when the client tries to access min or max keys of empty dictionaries.

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
