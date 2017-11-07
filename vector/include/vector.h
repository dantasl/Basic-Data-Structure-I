/**
 * @file    vector.h
 * @brief   Defining and implementing functions for ADT Vector.
 *			Unfortunally, with time given, I was not able to write a good documentation for this class,
 *			but pretty much the basic information you need is available in the .pdf file available on
 *			the project's base.
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @date    21/10/2017
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <cassert>
#include <iterator>
#include <cstdlib>
#include <algorithm>
#include <initializer_list>

class MyIterator;
class vector;

namespace sc
{
	template <typename T>
	class MyIterator
	{
		private:
			T *current;

		public:

			/**
			 * @brief      Default constructor for MyIterator. Initializes
			 *             attribute current.
			 *
			 * @param      ptr_  The initializer pointer. Provided none, default
			 *                   value is nullptr.
			 */
			MyIterator(T * ptr_ = nullptr)
				: current(ptr_)
				{/* empty */}


			/**
			 * @brief      Dereferencing operator.
			 *
			 * @return     Content of attribute current.
			 */
			const T & operator*() const
			{
				assert(current 	!= nullptr);
				return *current;
			}


			/**
			 * @brief      Pre-increment operator.
			 *
			 * @return     
			 */
			MyIterator & operator++()
			{
				current++;
				return *this;
			}

			MyIterator operator++( int )
			{
				MyIterator temp = *this;
				current++;
				return temp;
			}

			MyIterator & operator--()
			{
				current--;
				return *this;
			}

			MyIterator operator--( int )
			{
				MyIterator temp = *this;
				current--;
				return temp;
			}

			bool operator==(const MyIterator & rhs) const
			{
				return current == rhs.current;
			}

			bool operator!=(const MyIterator & rhs) const
			{
				return current != rhs.current;
			}
	};
	
	template <typename T>
	class vector{

		public:
			using size_type = size_t;
			using value_type = T;
			const static size_type DEFAULT_SIZE = 1;
			using iterator = MyIterator<T>;
			using const_iterator = MyIterator<const T>;
			using reference = T &;
			using const_reference = const T &;
			using pointer = T *;

		private:
			size_type m_end;
			size_type m_capacity;
			T * m_storage;

		public:
			/// [I] SEPECIAL MEMBERS
			
			/**
			 * @brief      Default constructor. Initializes attributes with
			 *             default values.
			 */
			vector()
				: m_end(0)
				, m_capacity(DEFAULT_SIZE)
				, m_storage(new T[m_capacity])
				{ /* empty */ }

			/**
			 * @brief      Default destructor. Destroys m_storage.
			 */
			~vector() { delete [] m_storage; }

			/**
			 * @brief      Copy constructor. Creates a vector with same
			 *             attributes of the one given by parameter.
			 *
			 * @param[in]  other  Vector to make the copy.
			 */
			vector(const vector & other)
				: m_end(other.m_end)
				, m_capacity(other.m_capacity)
				, m_storage(new T[m_capacity])
			{
				for(auto i(0u); i != m_end; ++i)
					m_storage[i] = other.m_storage[i];
			}

			/**
			 * @brief      Constructor with limit. Creates an empty vector with
			 *             capacity equal to the parameter.
			 *
			 * @param[in]  n     Capacity of the vector.
			 */
			vector(size_type n)
				: m_end(0)
				, m_capacity(n)
				, m_storage (new T[m_capacity])
				{ /* empty */ }
			
			/**
			 * @brief      Constructor with range. Creates a vector with
			 *             elements in the range given by the client.
			 *
			 * @param[in]  first     Beginning of the range.
			 * @param[in]  last      Ending of the range.
			 *
			 * @tparam     InputItr  An iterator.
			 */
			template< typename InputItr >
			vector(InputItr first, InputItr last)
			{
				int distance(0);
				auto f = first;

				while( f != last )
				{
					distance++;
					f++;
				}	

				m_end = size_type(distance);
				m_capacity = size_type(distance);
				m_storage = new T[m_capacity];

 				auto it = first;
				for(auto i(0u); i != distance; ++i, ++it)
					m_storage[i] = *it;
			}

			/**
			 * @brief      Assignment operator. Creates a vector with the same
			 *             attributes and elements of the one given by
			 *             parameter.
			 *
			 * @param[in]  v     Vector to make the assignment.
			 */
			vector & operator= (const vector &v)
			{
				m_end(v.m_end);
				m_capacity(v.m_capacity);
				m_storage(new T[m_capacity]);
				for(auto i(0u); i != m_end; ++i)
					m_storage[i] = v.m_storage[i];
				return *this;
			}

			/// [II] ITERATORS
	
			/**
			 * @brief      This function retrieves the reference for the address
			 *             of the beginning of the vector.
			 *
			 * @return     Iterator to begin.
			 */
			iterator begin( void )
			{
				return iterator(&m_storage[0]);
			}

			/**
			 * @brief      This function retrieves the reference for the address
			 *             of the ending of the vector.
			 *
			 * @return     Iterator to end.
			 */
			iterator end( void )
			{
				return iterator(&m_storage[m_end]);
			}

			/**
			 * @brief      This function retrieves the constant reference for
			 *             the address of the beginning of the vector.
			 *
			 * @return     Constant iterator to begin.
			 */
			const_iterator cbegin( void ) const
			{
				return const_iterator(&m_storage[0]);
			}

			/**
			 * @brief      This function retrieves the constant reference for
			 *             the address of the ending of the vector.
			 *
			 * @return     Constant iterator to end.
			 */
			const_iterator cend( void ) const
			{
				return const_iterator(&m_storage[m_end]);
			}

			/// [III] CAPACITY
			
			/**
			 * @brief      This function retrives the logical size of the
			 *             vector, i.e. how many elements are stored.
			 *
			 * @return     Number of elements stored.
			 */
			size_type size( void ) const
			{
				return m_end;
			}

			/**
			 * @brief      This function retrieves the fisical size of the
			 *             vector, i.e. how many elements can be stored.
			 *
			 * @return     Number of elements that can be stored.
			 */
			size_type capacity( void ) const
			{
				return m_capacity;
			}

			/**
			 * @brief      This function checks if the vector is empty or not.
			 *
			 * @return     True if the size is equal to 0. False, otherwise.
			 */
			bool empty( void ) const
			{
				return m_end == 0;
			}

			/// [IV] MODIFIERS			

			/**
			 * @brief      This function deletes all elements stored on vector
			 *             and updates capacity and number of stored elements to
			 *             0.
			 */
			void clear ( void )
			{
				delete [] m_storage;
				m_end = 0;
				m_capacity = 0; 
				m_storage = nullptr;
			}

			/**
			 * @brief      Pushes a new element at the beginning of the vector.
			 *             Checks if the vector can store a new element and
			 *             makes the required adjustments (if needed) on the
			 *             capacity. After this, moves all elements for the right
			 *             and stores the new value on the first position.
			 *
			 * @param[in]  ref   The reference for the new element.
			 */
			void push_front(const_reference ref)
			{
				if( m_end == m_capacity )
                   reserve(m_capacity * 2);

                for(auto i(m_end+1); i != 0; --i)
                    m_storage[i] = m_storage[i-1];

                m_end++;
                m_storage[0] = ref;
			}

			/**
			 * @brief      Pushes a new element at the end of the vector. Checks
			 *             if the vector can store a new element and makes the
			 *             required adjustments (if needed) on the capacity.
			 *
			 * @param[in]  ref   The reference for the new element.
			 */
			void push_back(const_reference ref)
			{
				if( m_end == m_capacity )
					reserve( 2 * m_capacity );
	
				m_storage[m_end++] = ref;
			}

			/**
			 * @brief      This function removes the last element from the
			 *             vector.
			 */
			void pop_back( void )
			{			
				if( empty() )
					throw std::out_of_range("Unnable to pop an element of an empty vector. \n");
				m_storage[--m_end];

			}

			/**
			 * @brief      This function removes the first element from the
			 *             vector and moves all remaining elements to the left.
			 */
			void pop_front( void )
			{
				for(auto i(0u); i != m_end; ++i)
                    m_storage[i] = m_storage[i+1];
                m_end--;

			}

			/**
			 * @brief      This function inserts a new element at a position
			 *             given by client. Checks if the vector can store a new
			 *             element and makes the required adjustments (if
			 *             needed) on the capacity. After this, moves all
			 *             elements for the right (to open space for the new
			 *             one) and stores the new element.
			 *
			 * @param[in]  at    Where the new element will be stored.
			 * @param[in]  ref   The reference for the new element.
			 *
			 * @return     Iterator to position of the new stored element.
			 */
			iterator insert( iterator at, const_reference ref )
			{				
				auto it = begin();
				unsigned int counter = 0;
				
				for(counter = 0; it != at; ++it, ++counter);
				
				if( m_end == m_capacity )
					reserve( 2 * m_capacity );
				
				for( auto i(m_end+1); i != counter; --i )
					m_storage[i] = m_storage[i-1];

				m_storage[counter] = ref;
				m_end++;
				return it;
			}

			/**
			 * @brief      This function inserts a range of elements on the
			 *             vector at a position given by the client. Checks if
			 *             the vector can store the range of elements and makes
			 *             the required adjustments (if needed) on the capacity.
			 *             After this, moves all elements for the right (to open
			 *             space for range) and stores the range.
			 *
			 * @param[in]  at        Where the new range will begin to be
			 *                       stored.
			 * @param[in]  _first    Where the range starts.
			 * @param[in]  _last     Where the range ends.
			 *
			 * @tparam     InputItr  Iterator with reference to begin and end of
			 *                       the range.
			 *
			 * @return     Iterator to position of the new stored range.
			 */
			template<typename InputItr>
			iterator insert(iterator at, InputItr _first, InputItr _last)
			{				
				auto total_distance = _last - _first;
				auto first = _first;
				auto _begin = begin();
				unsigned int start = 0;

				for(; _begin != at; ++_begin, ++start);

				while(m_end + total_distance > m_capacity)
					reserve(2*m_capacity);

				for(auto i(m_end + total_distance); i != start; --i)
					m_storage[i] = m_storage[i - total_distance]; 
			
				for(auto i(start); i != start+total_distance; ++i)
				{
					m_storage[i] = first;
					first++;
				}
				m_end += total_distance;

				return _begin;
			}

			/**
			 * @brief      This function inserts list of elements on the vector
			 *             at a position given by the client. Checks if the
			 *             vector can store the list and makes the required
			 *             adjustments (if needed) on the capacity. After this,
			 *             moves all elements for the right (to open space for
			 *             the list) and stores the list.
			 *
			 * @param[in]  at    Where the list will begin to be stored.
			 * @param[in]  list  The list of elements to be stored.
			 *
			 * @return     Iterator to position of the new stored elements.
			 */
			iterator insert(iterator at, std::initializer_list<value_type> list)
			{				
				auto total_distance = list.size();
				auto _begin = begin();
				unsigned int start = 0;

				for(; _begin != at; ++_begin, ++start);

				while(m_end + total_distance > m_capacity)
					reserve( 2 * m_capacity );
				
				for(auto i(m_end + total_distance); i != start; --i)
					m_storage[i] = m_storage[i - total_distance]; 
				
				for(auto &ref: list)
					m_storage[start++] = ref;
				
				m_end += total_distance;

				return _begin;
			}

			/**
			 * @brief      Creates a new space of memory with the size of
			 *             new_size, makes the copy of all elements stored on
			 *             the previous address and deletes its reference.
			 *
			 * @param[in]  new_size  The new memory size.
			 */
			void reserve(size_type new_size)
			{
				
				if(new_size <= m_capacity) return;
				T * temp = new T[new_size];  
				for(auto i(0u); i < m_capacity; ++i)
					temp[i] = m_storage[i];
				delete [] m_storage;
				m_storage = temp;
				m_capacity = new_size;
			}

			/**
			 * @brief      When called, this function will create another space
			 *             of memory where its size is exactly the number of
			 *             elements that are actualy stored on the vector. It
			 *             will make a copy of all elements of the old space and
			 *             delete its reference.
			 */
			void shrink_to_fit( void )
			{
				T * temp = new T[m_end];  
				for(auto i(0); i < m_end; ++i)
					temp[i] = m_storage[i];
				delete [] m_storage;
				m_storage = temp;
				m_capacity = m_end;
			}

			/**
			 * @brief      This function will replace all previous stored
			 *             elements of the vector with the new value given by
			 *             the client.
			 *
			 * @param[in]  ref   The reference for the value that will be
			 *                   assigned.
			 */
			void assign(const_reference ref)
			{
				if( empty() )
					throw std::out_of_range("Unable to assign values to an empty vector. \n");
				for(auto i(0u); i != m_end; ++i)
					m_storage[i] = ref;
			}

			/**
			 * @brief      { function_description }
			 *
			 * @param[in]  list  The list
			 */
			void assign(std::initializer_list<T> list)
			{
				if( empty() )
					throw std::out_of_range("Unable to assign values to an empty vector. \n");
								
				size_type i = 0;
				auto cont(0u);
				
				while(cont < m_end)
				{
					for(auto &ref: list)
					{
						m_storage[i++] = ref;
						cont++;
					}
				}
			}			
			
			template<typename InputItr>
			void assign(InputItr first, InputItr last)
			{				
				auto total_distance = last - first;
				m_end = size_t(total_distance);
				m_capacity = size_t(total_distance);
				m_storage = new T[m_capacity];

				for(auto i(0u); i != total_distance; i++)
					m_storage[i] = i + first;
			}
			
			iterator erase( iterator _first, iterator _last )
			{
				auto first = _first;
				auto _begin = begin();
				unsigned int start = 0;
				int counter = 0;

				//Discover how many elements there are in range.
				for(; first != _last; ++first, ++counter);

				for(; _begin != first; ++start, ++_begin);
				
				for(auto i(start); i != m_end - counter; ++i)
					m_storage[i] = m_storage[i+counter];

				m_end -= counter;
				return first;
			}

			iterator erase(iterator it)
			{
				auto _begin = begin();
				int counter = 0;

				for(; it != _begin; ++_begin, ++counter);

				for(auto i(counter); i != m_end - 1; ++i)
					m_storage[i] = m_storage[i+1];

				m_end--;
				return iterator(_begin);
			}

			/// [V] ELEMENT ACCESS
			
			/**
			 * @brief      This function returns the element that is on the last
			 *             position of the vector.
			 *
			 * @return     Last element of the vector.
			 */
			const_reference back( void ) const
			{
				return m_storage[m_end-1];
			}

			/**
			 * @brief      This function returns the element that is on the
			 *             first position of the vector.
			 *
			 * @return     First element of the vector.
			 */
			const_reference front( void ) const
			{
				return m_storage[0];
			}
			
			/**
			 * @brief      This operator makes it possible for client to access
			 *             an element by its index.
			 *
			 * @param[in]  at    Index of the element that the client wants to access.
			 *
			 * @return     Constant value that is stored on that index.
			 */
			const_reference operator[]( size_type at ) const
			{
				return m_storage[at];
			}

			/**
			 * @brief      This operator makes it possible for client to access
			 *             an element by its index.
			 *
			 * @param[in]  at    Index of the element that the client wants to access.
			 *
			 * @return     Value that is stored on that index.
			 */			
			reference operator[](size_type at)
			{
				return m_storage[at];
			}

			/**
			 * @brief      This function makes it possible for the client to
			 *             access and element at a specific index.
			 *
			 * @param[in]  at    Index of the element that the client wants to access.
			 *
			 * @return     Value that is stored on that index.
			 */
			const_reference at(size_type at)
			{
				if(at >= m_end)
					throw std::out_of_range("Unable to access element out of vector's range. \n");
				return m_storage[at];

			}

			/**
			 * @brief      When this function is called, it will provide access
			 *             to all the data stored on the vector.
			 *
			 * @return     Attribute m_storage that holds all the elements
			 *             stored on the vector.
			 */
			pointer data( void )
			{
				return m_storage;
			}

			/**
			 * @brief      { function_description }
			 *
			 * @return     { description_of_the_return_value }
			 */
			const_reference data( void ) const
			{
				return m_storage;
			}

			/// [VI] OPERATORS
			
			/**
			 * @brief      Equality operator. Checks if all elements from this
			 *             vector are equal to the elements of a second vector.
			 *
			 * @param[in]  v     The vector to be checked for equality.
			 *
			 * @return     True if all elements are equal. False otherwise.
			 */
			bool operator==(const vector & v) const
			{
				if( (this->m_capacity != v.m_capacity) or (this->m_end != v.m_end) )
					return false;

				for(auto i(0u); i != m_end; ++i)
				{
					if(m_storage[i] != v.m_storage[i])
						return false;
				}

				return true;
			}
			
			/**
			 * @brief      Non-equality operator. Checks if all elements from
			 *             this vector are different to the elements of a second
			 *             vector.
			 *
			 * @param[in]  v     The vector to be checked for difference.
			 *
			 * @return     True if all elements are different. False otherwise.
			 */
			bool operator!=(const vector & v) const
			{
				if( (this->m_capacity != v.m_capacity) or (this->m_end != v.m_end) )
					return true;
				
				for(auto i(0u); i != m_end; ++i)
				{
					if( m_storage[i] != v.m_storage[i] )
						return true;
				}
				return false;
			}

			/// [VII] FRIEND FUNCTIONS
			
			/**
			 * @brief      Insertion on streamer operator. It is overloaded to
			 *             print all elements of a given vector.
			 *
			 * @param      os_   The output streamer
			 * @param      v_    The vector that will have its elements printed.
			 *
			 */
			friend std::ostream & operator<< ( std::ostream & os_, vector<T> & v_ )
			{
				if( v_.empty() )
				{
					os_ << "Unable to print elements of an empty vector." << std::endl;
					return os_;
				}
				for(auto i = v_.begin(); i != v_.end(); ++i)
					os_ << *i << " ";
				os_ << std::endl;
				return os_;	
			}
			
			/**
			 * @brief      This function simply swaps all values between two
			 *             vectors.
			 *
			 * @param      first_   The vector that will have its elements
			 *                      swaped with the second vector.
			 * @param      second_  The vector that will have its elements
			 *                      swaped with the first vector.
			 */
			friend void swap( vector<T> & first_, vector<T> & second_ )
			{
				if( first_.empty() or second_.empty() )
				{
					std::cout << "Unable to make operations with an empty vector." << std::endl;
					return;
				}

				auto temp = first_;

				first_.m_storage = second_.m_storage;
				first_.m_end = second_.m_end;
				first_.m_capacity = second_.m_capacity;

				second_.m_storage = temp.m_storage;
				second_.m_end = temp.m_end;
				second_.m_capacity = temp.m_capacity;
			}
	};	
}

#endif