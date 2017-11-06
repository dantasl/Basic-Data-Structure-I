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
			MyIterator(T * ptr_ = nullptr)
				: current(ptr_)
				{/* empty */}

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
			size_type m_end;
			size_type m_capacity;
			T * m_storage;

		public:

			/// [I] SEPECIAL MEMBERS
			vector()
				: m_end(0)
				, m_capacity(DEFAULT_SIZE)
				, m_storage(new T[m_capacity])
				{ /* empty */ }
			
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
				{ /* empty */ }

			
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
			iterator begin( void )
			{
				return iterator(&m_storage[0]);
			}

			iterator end( void )
			{
				return iterator(&m_storage[m_end]);
			}

			const_iterator cbegin( void ) const
			{
				return const_iterator(&m_storage[0]);
			}

			const_iterator cend( void ) const
			{
				return const_iterator(&m_storage[m_end]);
			}

			/// [III] CAPACITY
			size_type size( void ) const
			{
				return m_end;
			}
			
			size_type capacity( void ) const
			{
				return m_capacity;
			}
			
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
			
			void push_front(const_reference ref)
			{
				if( m_end == m_capacity )
                   reserve(m_capacity * 2);

                for(auto i(m_end+1); i != 0; --i)
                    m_storage[i] = m_storage[i-1];

                m_end++;
                m_storage[0] = ref;
			}
			
			void push_back(const_reference ref)
			{
				if( m_end == m_capacity )
					reserve( 2 * m_capacity );
	
				m_storage[m_end++] = ref;
			}
			
			void pop_back( void )
			{			
				if( empty() )
					throw std::out_of_range("Unnable to pop an element of an empty vector. \n");
				m_storage[--m_end];

			}
			
			void pop_front( void )
			{
				for(auto i(0u); i != m_end; ++i)
                    m_storage[i] = m_storage[i+1];
                m_end--;

			}
			
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
			
			void shrink_to_fit( void )
			{
				T * temp = new T[m_end];  
				for(auto i(0); i < m_end; ++i)
					temp[i] = m_storage[i];
				delete [] m_storage;
				m_storage = temp;
				m_capacity = m_end;
			}
			
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
			
			const_reference back( void ) const
			{
				return m_storage[m_end-1];
			}
			
			const_reference front( void ) const
			{
				return m_storage[0];
			}
			
			const_reference operator[]( size_type at ) const
			{
				return m_storage[at];
			}
			
			reference operator[](size_type at)
			{
				return m_storage[at];
			}
			
			const_reference at(size_type at)
			{
				if(at >= m_end)
					throw std::out_of_range("Unable to access element out of vector's range. \n");
				return m_storage[at];

			}
			
			pointer data( void )
			{
				return m_storage;
			}
			
			const_reference data( void ) const
			{
				return m_storage;
			}

			/// [VI] OPERATORS			
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