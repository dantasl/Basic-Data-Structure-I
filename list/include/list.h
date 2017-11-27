#ifndef _LIST_H_
#define _LIST_H_

#include <cassert>
#include <initializer_list>

namespace ls
{
	template <typename T>
	class list 
	{
		private:
			struct Node
			{
				T data; //<! Data field
				Node *prev; //<! Pointer to the previous node in the list.
				Node *next; //<! Pointer to the next node in the list.
				//<! Basic constructor.
				Node( const T & d = T(), Node * p = nullptr, Node *n = nullptr )
					: data(d)
					, prev(p)
					, next(n)
					{ /* Empty */ }
			};

		public:
			class const_iterator
			{
				protected:
					Node *current;
					const_iterator( Node * p ) : current( p ) { /* empty */ }
					friend class list<T>;

				public:
					const T & operator*() const
					{
						assert( current != nullptr );
						return current->data;
					}
					
					const_iterator & operator++() // ++it;
					{
						assert( current != nullptr );
						current = current -> next;
						return *this;
					}

					const_iterator operator++( int ) // it++;
					{
						assert( current != nullptr );
						auto temp = current;
						current = current -> next;
						return temp;
					}
					
					const_iterator & operator--() // --it;
					{
						assert( current != nullptr );
						current = current -> prev;
						return *this;
					}

					const_iterator operator--( int ) // it--;
					{
						assert( current != nullptr );
						auto temp = current;
						current = current -> prev;
						return temp;
					}

					bool operator==( const const_iterator & rhs ) const
					{
						return current == rhs.current;
					}
					
					bool operator!=( const const_iterator & rhs ) const
					{
						return current != rhs.current;
					}
			};

			class iterator : public const_iterator
			{
				protected:
					iterator( Node *p ) : const_iterator( p ) { /*empty */ }
					friend class list<T>;

				public:
					iterator() : const_iterator() { /* Empty */ }
					
					const T & operator*() const
					{
						assert( const_iterator::current != nullptr );
						return const_iterator::current->data;
					}
					
					T & operator*()
					{
						assert( const_iterator::current != nullptr );
						return const_iterator::current->data;
					}

					iterator & operator++() // ++it;
					{
						assert( const_iterator::current != nullptr );
						const_iterator::current = const_iterator::current -> next;
						return *this;
					}

					iterator operator++( int ) // it++;
					{
						assert( const_iterator::current != nullptr );
						auto temp = const_iterator::current;
						const_iterator::current = const_iterator::current -> next;
						return temp;
					}

					iterator & operator--() // --it;
					{
						assert( const_iterator::current != nullptr );
						const_iterator::current = const_iterator::current -> prev;
						return *this;
					}
					
					iterator operator--( int ) // it--;
					{
						assert( const_iterator::current != nullptr );
						auto temp = const_iterator::current;
						const_iterator::current = const_iterator::current -> prev;
						return temp;
					}
			};

			/// [I] SPECIAL MEMBERS
			list()
				: m_size( 0 )
				, m_head( new Node() )
				, m_tail( new Node() ) 
			{
				m_head -> next = m_tail;
				m_tail -> prev = m_head;
			}

			explicit list( unsigned long count )
				: m_size( 0 )
				, m_head( new Node() )
				, m_tail( new Node() )
			{
				m_head -> next = m_tail;
				m_tail -> prev = m_head;

				for( auto i(0u); i < count; ++i )
					push_back( T() );
			}

			template < typename InputIt >
			list( InputIt first, InputIt last )
				: m_size( 0 )
				, m_head( new Node() )
				, m_tail( new Node() )
			{
				m_head -> next = m_tail;
				m_tail -> prev = m_head;

				for( auto i = first; i != last; ++i )
					push_back(*i);
			}			
			
			list( const list & other )
				: m_size( 0 )
				, m_head( new Node() )
				, m_tail( new Node() )
			{
				m_head -> next = m_tail;
				m_tail -> prev = m_head;

				for( auto i = other.cbegin() ; i != other.cend() ; ++i )
					push_back(*i);
			}

			list( std::initializer_list<T> ilist )
				: m_size( 0 )
				, m_head( new Node() )
				, m_tail(new Node() )
			{
				m_head -> next = m_tail;
				m_tail -> prev = m_head;

				for(auto i = ilist.begin(); i != ilist.end(); ++i)
					push_back(*i);	
			}

			~list()
			{
				clear();
				delete m_head;
				delete m_tail;
			}
			
			list & operator= ( const list & other )
			{
				clear();
				for(auto i = other.cbegin(); i != other.cend(); ++i)
					push_back(*i);
				return *this;
			}

			list & operator= (std::initializer_list<T> ilist)
			{
				clear();
				for(auto i = ilist.begin(); i != ilist.end(); ++i)
					push_back(*i);
				return *this;
			}	

			/// [II] ITERATORS
			iterator begin(void)
			{
				return iterator(m_head -> next);
			}
			
			const_iterator cbegin(void) const
			{
				return const_iterator(m_head -> next);
			}
			
			iterator end(void)
			{
				return iterator(m_tail);
			}
			
			const_iterator cend(void) const
			{
				return const_iterator(m_tail);
			}

			/// [III] CAPACITY
			int size() const
			{
				return m_size;
			}
			
			bool empty() const
			{
				return m_size == 0;
			}

			/// [IV] MODIFIERS
			void clear()
			{
				if( empty() )
					return;
				auto curr(m_head -> next);
				while( curr != m_tail )
				{
					curr = curr -> next;
					delete curr -> prev;
				}
				m_head -> next = m_tail;
				m_tail -> prev = m_head;
				m_size = 0;
			}
			
			T & front()
			{
				if( empty() )
					throw std::out_of_range("Unnable to access front element of an empty list. \n");
				return m_head -> next -> data;
			}

			const T & front() const
			{
				if( empty() )
					throw std::out_of_range("Unnable to access front element of an empty list. \n");
				return m_head -> next -> data;
			}

			T & back()
			{
				if( empty() )
					throw std::out_of_range("Unnable to access back element of an empty list. \n");
				return m_tail -> prev -> data;
			}

			const T & back() const
			{
				if( empty() )
					throw std::out_of_range("Unnable to access back element of an empty list. \n");
				return m_tail -> prev -> data;
			}

			void push_front( const T & value )
			{
				auto new_node = new Node(value, m_head, m_head->next);
				m_head -> next -> prev = new_node;
				m_head -> next = new_node;
				++m_size;
			}

			void push_back( const T & value )
			{
				if ( empty() ) push_front(value);
				else
				{
					auto last = m_tail -> prev;
					last -> next = new Node(value, last, m_tail);
					m_tail -> prev = last -> next;
					++m_size;
				}				
			}

			void pop_front()
			{
				if( empty() )
					throw std::out_of_range("Unnable to pop front element of an empty list. \n");
				auto n = m_head -> next;
				m_head -> next = n -> next;
				if ( m_size == 1 ) m_tail -> prev = m_head -> next;
				delete n;
				--m_size;
			}

			void pop_back()
			{
				if ( empty() )
					throw std::out_of_range("Unnable to pop back element of an empty list. \n");
				auto previous = m_tail -> prev -> prev;
				previous -> next = m_tail;
				delete m_tail->prev;
				m_tail -> prev = previous;
				if ( m_size == 1 ) m_head -> next = m_tail -> prev;
				--m_size;
			}

			void assign( const T& value )
			{
				if ( empty() )
					throw std::out_of_range("Unnable to make this assignment on an empty list. \n");
				auto curr = m_head -> next;
				while( curr -> next != nullptr )
				{
					curr -> data = value;
					curr = curr -> next;
				}
			}

			/// [IV-a] MODIFIERS WITH ITERATORS
			
			template < class InItr >
			void assign( InItr first, InItr last )
			{
				clear();
				for(auto i = first; i != last; ++i) push_back(*i);				      
			}

			void assign( std::initializer_list<T> ilist )
			{
				clear();
				for(auto i = ilist.begin(); i != ilist.end(); ++i)
					push_back(*i);
			}
			
			iterator insert( const_iterator itr, const T & value )
			{
				auto new_insert = new Node( value, (itr.current) -> prev, itr.current );
				( ( itr.current ) -> prev) -> next = new_insert;
				( itr.current ) -> prev = new_insert;
				return iterator(new_insert);
			}

			iterator insert( const_iterator pos, std::initializer_list<T> ilist )
			{
				for( auto i = ilist.begin(); i != ilist.end(); ++i )
					insert(pos, *i);
				return iterator(pos.current);
			}
			
			iterator erase( const_iterator itr )
			{
				if( itr != cend() )
				{
					auto before = ( itr.current ) -> prev;
					auto after = ( itr.current ) -> next;
					before -> next = after;
					after -> prev = before;
					m_size--;
					delete itr.current;
					return iterator(after);
				}	
				return iterator(itr.current);
			}

			iterator erase( const_iterator first, const_iterator last )
			{
				for( auto i = first; i != last; ++i ) erase(*i);
			}
			
			const_iterator find( const T & value ) const
			{
				auto curr = m_head;
				while( curr != m_tail and curr -> data != value )
					curr = curr -> next;
				return curr;		
			}

		private:
			int m_size;
			Node *m_head;
			Node *m_tail;	
	};
}

#endif