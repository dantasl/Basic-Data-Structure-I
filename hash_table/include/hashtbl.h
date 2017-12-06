/**
 * @file    hashtbl.h
 * @brief   Defining and implementing functions for ADT Hash Table.
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @since   05/12/2017
 * @date    06/12/2017
 */

#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <forward_list>
#include <iostream>
#include <functional>
#include <cmath> // std::sqrt

namespace ac
{
	template< class KeyType, class DataType >
	class HashEntry
	{
		public:
			HashEntry ( KeyType k_, DataType d_ ) : m_key( k_ ), m_data( d_ )
			{ /* empty */ }
			KeyType m_key; //!< Stores the key for an entry.
			DataType m_data; //!< Stored the data for an entry.
	};

	template < typename KeyType,
			   typename DataType,
			   typename KeyHash = std::hash<KeyType>,
			   typename KeyEqual = std::equal_to<KeyType> >

	class HashTbl
	{
		private:
			
			/**
			 * @brief      Helper function to check if a size is prime or not.
			 *
			 * @param[in]  size  Size to be checked.
			 *
			 * @return     True if size is prime. False, otherwise.
			 */
			bool check_Prime ( unsigned int size ) 
			{
				int i;
				if(size == 0 || size == 1) return false;
			    for(i = 2; i <= std::sqrt(size); ++i)
			    {
			        if ( size%i == 0 ) return false;
			    }
			  	return true;
			}

			/**
			 * @brief      Helper function to find the next prime number of a
			 *             given size.
			 *
			 * @param[in]  size  Initial number to find next prime.
			 *
			 * @return     The closest prime number of the given size.
			 */
			unsigned int find_Next_Prime( unsigned int size )
			{
				while( not check_Prime(size) ) size++;
				return size;
			}

		public:
			
			using Entry = HashEntry< KeyType, DataType >; //!< Alias

			/**
			 * @brief      Default constructor. Initializes attributes and sets
			 *             the m_size with the prime number closest to the
			 *             clients input (if provided any).
			 *
			 * @param[in]  tbl_size_  The table size.
			 */
			HashTbl ( int tbl_size_ = DEFAULT_SIZE )
				: m_count(0)
			{
				auto t_size = find_Next_Prime(tbl_size_);
				m_size = t_size;
				m_data_table = new std::forward_list<Entry>[m_size];
			}
			
			/**
			 * @brief      Default destructor. Clears all elements of this table
			 *             and deletes m_data_table.
			 */
			virtual ~HashTbl() { clear(); delete [] m_data_table; }

			/**
			 * @brief      Inserts a new element in this hash_table.
			 *
			 * @param[in]  k_    The key of the element.
			 * @param[in]  d_    The data of the element.
			 *
			 * @return     True if function manages to insert a new element at
			 *             the table. False if the element was already stored on
			 *             the table.
			 */
			bool insert ( const KeyType & k_, const DataType & d_ )
			{
				// Checks if the load factor is equal to 1.0. If it is, calls for rehash.
				if ( m_count == m_size ) rehash();
				KeyHash hashFunc;   // Instantiate the "functor" for primary hash.
				KeyEqual equalFunc; // Instantiate the "functor" for the equal to test.
				Entry new_entry ( k_, d_ ); // Create a new entry based on arguments. 
				// Apply double hashing method, one functor and the other with modulo function.
				auto end( hashFunc( k_ ) % m_size );
				// Iterates over the list searching for occurrence. In case one is found, overwrites
				// its data and returns false. In case the list is empty, the break condition will be
				// met at the beginning and the loop will not run.
				for(auto i = m_data_table[end].begin(); i != m_data_table[end].end(); ++i)
				{
					if( equalFunc( i -> m_key, new_entry.m_key ) )
					{
						i -> m_data = d_;
						return false;
					}	
				}
				// If the instruction "survived" this far, simply push element at the front.
				m_data_table[end].push_front(new_entry);
				m_count++;
				return true;
			}

			/**
			 * @brief      Removes an element of the table with the same key
			 *             provided by client.
			 *
			 * @param[in]  k_    Key of the element to be removed.
			 *
			 * @return     True if the function was able to delete the element. False, otherwise.
			 */
			bool remove ( const KeyType & k_ )
			{
				KeyHash hashFunc; // Instantiate the "functor" for primary hash.
				KeyEqual equalFunc;  // Instantiate the "functor" for the equal to test.
				// Apply double hashing method, one functor and the other with modulo function.
				auto end( hashFunc( k_ ) % m_size );
				if( m_data_table[end].empty() ) return false;
				// Iterates list searching for first occurrence of key.
				auto before = m_data_table[end].before_begin();
				for(auto i = m_data_table[end].begin(); i != m_data_table[end].end(); ++i)
				{
					if( equalFunc( i -> m_key, k_ ) )
					{
						m_data_table[end].erase_after(before);
						m_count--;
						return true;
					}
					before++;	
				}
				return false;
			}

			/**
			 * @brief      Retrieves an element from this table.
			 *
			 * @param[in]  k_    Key of the element to be retrieved.
			 * @param      d_    Where the result will be stored.
			 *
			 * @return     True if function manages to find the element. False
			 *             otherwise.
			 */
			bool retrieve ( const KeyType & k_, DataType & d_ ) const
			{
				KeyHash hashFunc; // Instantiate the "functor" for primary hash.
				KeyEqual equalFunc;  // Instantiate the "functor" for the equal to test.
				// Apply double hashing method, one functor and the other with modulo function.
				auto end( hashFunc( k_ ) % m_size );
				if( m_data_table[end].empty() ) return false;
				// Iterates list searching for first occurrence of key.
				for(auto i = m_data_table[end].begin(); i != m_data_table[end].end(); ++i)
				{
					if( equalFunc( i -> m_key, k_ ) )
					{
						d_ = i -> m_data;
						return true;
					}	
				}
				return false;	
			}

			/**
			 * @brief      This function iterates over each forward_list of the
			 *             table and calls for their method clear().
			 */
			void clear ( void )
			{
				for( auto i(0); i < m_size; ++i ) m_data_table[i].clear();
				m_count = 0;
			}

			/**
			 * @brief      Checks if the table is empty or not.
			 *
			 * @return     True if it is, false otherwise.
			 */
			bool empty ( void ) const
			{
				return m_count == 0;
			}

			/**
			 * @brief      This function retrieves for the client how many
			 *             elements are stored within this table.
			 *
			 * @return     Number of elements stored in this table.
			 */
			unsigned long int count ( void ) const
			{
				return m_count;
			}

			/**
			 * @brief      This function will print all elements stored in this
			 *             table.
			 */
			void print ( void ) const
			{
				if ( empty() ) { std::cout << "Empty table. \n"; return; }
				for(auto i(0); i < m_size; ++i)
				{
					for(auto j = m_data_table[i].begin(); j != m_data_table[i].end(); ++j)
					{
						auto content = j -> m_data;
						std::cout << "|  " << i;
						std::cout << "  | " << content.mClientName;
						std::cout << " |  " << content.mBankCode;
						std::cout << "   |  " << content.mBranchCode;
						std::cout << "  |  " << content.mNumber;
						std::cout << "  | " << content.mBalance << " |\n";
					}	
				}
				std::cout << std::endl;
			}

		private:			
			
			/**
			 * @brief      This function will create a new table n_table with
			 *             size double of the m_data_table. Then, it will
			 *             iterate over each member of the m_data_table, will
			 *             apply a new hash function on each of its elements and
			 *             store them on n_table. After this, all the previous
			 *             stored elements of m_data_table will be deleted and
			 *             its new value will be a reference to n_table.
			 */
			void rehash( void ) //!< Change Hash table size if load factor λ > 1.0
			{
				KeyHash hashFunc; // Instantiate the "functor" for primary hash.
				// New size is the next prime closest to the double previous size.
				auto n_size = find_Next_Prime(m_size * 2);
				auto n_table = new std::forward_list<Entry> [n_size];
				for(auto i(0); i != m_size; ++i)
				{
					for(auto j = m_data_table[i].begin(); j != m_data_table[i].end(); ++j)
					{
						// Calculating new hash for the bigger table.
						auto n_end ( hashFunc( j -> m_key ) % n_size );
						n_table[n_end].push_front(*j);
					}
				}

				return;

				// Deleting reference for the old table and updating it for the new.
				delete [] m_data_table;
				m_data_table = n_table;
				m_size = n_size;
			}

		private:
			unsigned int m_count; //!< Number of elements currently stored in the table.
			unsigned int m_size; //!< Hash table size.			 
			std::forward_list < Entry > * m_data_table;
			static const short DEFAULT_SIZE = 11; //!< Default size for this hash table.
	};
}

#endif