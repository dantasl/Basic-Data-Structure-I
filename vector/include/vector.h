#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <cassert>
#include <iterator>
#include <cstdlib>
#include <algorithm>
#include <initializer_list>

namespace sc
{
	template <typename T>
	class MyIterator
	{
		private:
			T *current;

		public:
			MyIterator(T * ptr_ = nullptr)
				: current(ptr_)
				{/* Empty */}

			const T & operator*() const
			{
				assert(current 	!= nullptr);
				return *current;
			}

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
			size_type m_end;			//Quantidade de elementos
			size_type m_capacity;		//Capacidade de armazenamento
			T * m_storage;				//Armazenamento

		public:

			/// [I] SEPECIAL MEMBERS
			vector()
				: m_end(0)
				, m_capacity(DEFAULT_SIZE)
				, m_storage(new T[m_capacity])
				{ /* Empty */ }
			
			~vector() { delete [] m_storage; }

			vector(const vector & other)
				: m_end(other.m_end)
				, m_capacity(other.m_capacity)
				, m_storage(new T[m_capacity])
			{
				for(auto i(0u); i != m_end; ++i)
					m_storage[i] = other.m_storage[i];
			}

			vector(size_type n)
				: m_end(0)
				, m_capacity(n)
				, m_storage (new T[m_capacity])
				{/*empty*/}

			
			template< typename InputItr >
			vector(InputItr first, InputItr last)
			{
				auto total_size = last - first;
				m_end = size_t(total_size);
				m_capacity = size_t(total_size);
				m_storage = new T[m_capacity];
 
				for(auto i(0u); i != total_size; ++i)
					m_storage[i] = i+first;
			}
			
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
			/// Returns a iterator to the first element of the vector
			iterator begin( void )
			{
				return iterator(&m_storage[0]);
			}
			/// Returns a iterator to the last element of the vector
			iterator end( void )
			{
				return iterator(&m_storage[m_end]);
			}
			/// Returns a constant iterator to the first element of the vector
			const_iterator cbegin( void ) const
			{
				return const_iterator(&m_storage[0]);
			}
			/// Returns a constant iterator to the last element of the vector
			const_iterator cend( void ) const
			{
				return const_iterator(&m_storage[m_end]);
			}

			/// [III] CAPACITY
			/// Return the logical size of the vector
			size_type size( void ) const
			{
				return m_end;
			}
			/// Return the total capacity of the vector
			size_type capacity( void ) const
			{
				return m_capacity;
			}
			/// Check if the vector is empty
			bool empty( void ) const
			{
				return m_end == 0;
			}

			/// [IV] MODIFIERS
			void clear ( void )
			{
				delete [] m_storage;
				m_end = 0;
				m_capacity = 0; 
				m_storage = nullptr;
			}
			/// Adds a element to the begin of the vector
			void push_front(const_reference ref)
			{
				if( m_end == m_capacity )
                   reserve(m_capacity * 2);

                for(auto i(m_end+1); i != 0; --i)
                    m_storage[i] = m_storage[i-1];

                m_end++;
                m_storage[0] = ref;
			}
			/// Adds a element to the end of the vector
			void push_back(const_reference ref)
			{
				if( m_end == m_capacity )
					reserve( 2 * m_capacity );
	
				m_storage[m_end++] = ref;
			}
			/// Withdraw the last element in the vector
			void pop_back( void )
			{			
				if( empty() )
					throw std::out_of_range("Unnable to pop an element of an empty vector. \n");
				m_storage[--m_end];

			}
			/// Withdraw the last element in the vector
			void pop_front( void )
			{
				for(auto i(0); i != m_end; ++i)
                    m_storage[i] = m_storage[i+1];
                m_end--;

			}
			/// Inserts a element, range of elements, or list to an especific point in the vector
			iterator insert( iterator at, const_reference ref )
			{				
				auto it = begin();
				int counter = 0;
				
				for(counter = 0; it != at; ++it, ++counter);
				
				if( m_end == m_capacity )
					reserve( 2 * m_capacity );
				
				for( auto i(m_end+1); i != counter; --i )
					m_storage[i] = m_storage[i-1];

				m_storage[counter] = ref;
				m_end++;
				return it;
			}
			
			template<typename InputItr>
			iterator insert(iterator at, InputItr _first, InputItr _last)
			{				
				auto total_distance = _last - _first;
				auto first = _first;
				auto begin = begin();
				int start = 0;

				for(; begin != at; ++begin, ++start);

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

				return begin;
			}

			iterator insert(iterator at, std::initializer_list<value_type> list)
			{				
				auto total_distance = list.size();
				auto begin = begin();
				int start = 0;

				for(; begin != at; ++begin, ++start);

				while(m_end + total_distance > m_capacity)
					reserve( 2 * m_capacity );
				
				for(auto i(m_end + total_distance); i != start; --i)
					m_storage[i] = m_storage[i - total_distance]; 
				
				for(auto &ref: list)
					m_storage[start++] = ref;
				
				m_end += total_distance;

				return begin;
			}
			/// Increases de capacity of the vector
			void reserve(size_type new_size)
			{
				
				if(new_size <= m_capacity) return; //!< It's not full
				/// Creates the new Storage area
				T * temp = new T[new_size];  
				/// Backup the data to the new storage area
				for(auto i(0u); i < m_capacity; ++i)
					temp[i] = m_storage[i];
				/// Delete the old storage area
				delete [] m_storage;
				/// Reassings the storage area
				m_storage = temp;
				/// Updates the vector's storage capacity
				m_capacity = new_size;

			}
			/// Makes the capacity of the vector equal to its logical lenght
			void shrink_to_fit( void )
			{
				T * temp = new T[m_end];  
				for(auto i(0); i < m_end; ++i)
					temp[i] = m_storage[i];
				delete [] m_storage;
				m_storage = temp;
				m_capacity = m_end;
			}
			/// Fill the vector with a especific element, range of elements or list
			void assign(const_reference ref)
			{
				if( empty() )
					throw std::out_of_range("Unable to assign values to an empty vector. \n");
				for(auto i(0u); i != m_end; ++i)
					m_storage[i] = ref;
			}
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
			/// Erases an element in a specific place in the vector
			iterator erase( iterator _first, iterator _last )
			{
				auto first = _first;
				auto begin = begin();
				int start = 0;
				int counter = 0;

				for(; first != _last; ++first, ++counter);

				for(; begin != first; ++start, ++begin);
				
				for(auto i(start); i != m_end - counter; ++i)
					m_storage[i] = m_storage[i+counter];

				m_end -= counter;
				return first;
			}

			iterator erase(iterator it)
			{
				auto begin = begin();
				int counter = 0;

				for(; it != begin; ++begin, ++counter);

				for(auto i(counter); i != m_end - 1; ++i)
					m_storage[i] = m_storage[i+1];

				m_end--;
				return iterator(begin);
			}

			/// [V] ELEMENT ACCESS
			/// Returns the last element in the vector
			const_reference back( void ) const
			{
				return m_storage[m_end-1];
			}
			/// Returns the first element in the vector
			const_reference front( void ) const
			{
				return m_storage[0];
			}
			/// Returns the constant content of the position pos (exemple: myvector[3])
			const_reference operator[]( size_type at ) const
			{
				return m_storage[at];
			}
			/// Returns the content of the position pos (exemple: myvector[3])
			reference operator[](size_type at)
			{
				return m_storage[at];
			}
			/// Returns the content of the position pos after check if the element exists
			const_reference at(size_type at)
			{
				if(at >= m_end)
					throw std::out_of_range("Unable to access element out of vector's range. \n");
				return m_storage[at];

			}
			/// Returns a pointer to the vector data
			pointer data( void )
			{
				return m_storage;
			}
			/// Returns a constant pointer to the vector data
			const_reference data( void ) const
			{
				return m_storage;
			}
			void print( void ) const
			{
				if( empty() )
				{
					std::cerr << "Unable to print elements of an empty vector." << std::endl;
					return;
				}
				std::cout << "|";
				std::copy(&m_storage[0], &m_storage[m_end], std::ostream_iterator<int>(std::cout, "|"));
				std::cout << std::endl;
			}

			/// [VI] OPERATORS
			/// Checks if two vectors have the same capacity logical size and contents
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
			/// Oposit logic of operator==
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
	};	
}

#endif