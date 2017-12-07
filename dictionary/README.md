# Abstract Data Type - Implementing a Hash Table

In the present repository I'm storing the codes created to implement a Hash Table.

<b>Lucas Gomes Dantas</b> (<dantaslucas@ufrn.edu.br>), student in the <b>Basic Data Structure I</b> class of <b>Prof. Dr. Selan
Rodrigues dos Santos</b> at <b>Federal University of Rio Grande do Norte</b>.

## Compiling and Running

* Clone this repository in any directory you want;
* Via prompt, go to the directory where you've cloned this repository;
* Type `make init` to create the project structure;
* Type `make` to compile the project.

There is already a driver testing some of the hash table's functions. If you want to run it, type: <code>./bin/hash_test</code>

## Including and using library

To use this library, you have to include the `hashtbl.h` into your application. To instantiate a hash table, do as following:

* `ac::HashTbl<KeyType, DataType, KeyHash, KeyEqual> hs`

Where `ac` is the namespace (stands for associative container), `<KeyType>` is the element's key, `DataType` is the value of the element, `KeyHash` is the functor to hash the key provided by the client (default function is std::hash),`KeyEqual` is the functor of comparison (default funtion is std::equal_to) and `hs` is the hash_table's name.

## Possible errors and exceptions

Errors, for this implementation, were treated in a very simple way. The functions will return a `false` when they're not able to perform their actions and a `true` when possible.

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
