/**
 * @file    list.h
 * @brief   Defining and implementing functions for ADT Double Linked List.
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @since   26/11/2017
 * @date    26/11/2017
 */

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
					
					/**					
					 * @brief      Dereferencing operator.
					 *
					 * @return     Content of attribute current.
					 */
					const T & operator*() const
					{
						assert( current != nullptr );
						return current->data;
					}

					/**
					 * @brief      Pre-increment operator.
					 */
					const_iterator & operator++() // ++it;
					{
						assert( current != nullptr );
						current = current -> next;
						return *this;
					}

					/**
					 * @brief      Post-increment operator.
					 */
					const_iterator operator++( int ) // it++;
					{
						assert( current != nullptr );
						auto temp = current;
						current = current -> next;
						return temp;
					}

					/**
					 * @brief      Pre-decrement operator.
					 */
					const_iterator & operator--() // --it;
					{
						assert( current != nullptr );
						current = current -> prev;
						return *this;
					}

					/**
					 * @brief      Post-decrement operator.
					 */
					const_iterator operator--( int ) // it--;
					{
						assert( current != nullptr );
						auto temp = current;
						current = current -> prev;
						return temp;
					}

					/**
					 * @brief      Equality operator. Checks if the data stored on this
					 *             instance of const_iterator is equal to another
					 *             const_iterator.
					 *
					 * @param[in]  rhs   Another instance to be checked.
					 *
					 * @return     True if they are equals. False otherwise.
					 */
					bool operator==( const const_iterator & rhs ) const
					{
						return current == rhs.current;
					}

					/**
					 * @brief      Non-equality operator. Checks if the data stored on
					 *             this instance of const_iterator is different to
					 *             another const_iterator.
					 *
					 * @param[in]  rhs   Another instance to be checked.
					 *
					 * @return     True if they are different. False otherwise.
					 */					
					bool operator!=( const const_iterator & rhs ) const
					{
						return current != rhs.current;
					}
			};

			class iterator : public const_iterator
			{
				protected:
					/**
					 * @brief      Default constructor for iterator.
					 *
					 * @param      p     Node to initialize iterator.
					 */
					iterator( Node *p ) : const_iterator( p ) { /*empty */ }
					friend class list<T>;

				public:
					/**
					 * @brief     Default empty constructor.
					 */
					iterator() : const_iterator() { /* Empty */ }

					/**
					 * @brief      Dereferencing operator.
					 *
					 * @return     Constant reference to the content stored.
					 */
					const T & operator*() const
					{
						assert( const_iterator::current != nullptr );
						return const_iterator::current->data;
					}

					/**
					 * @brief      Dereferencing operator.
					 *
					 * @return     Reference to the content stored.
					 */
					T & operator*()
					{
						assert( const_iterator::current != nullptr );
						return const_iterator::current->data;
					}

					/**
					 * @brief      Pre-increment operator.
					 */
					iterator & operator++() // ++it;
					{
						assert( const_iterator::current != nullptr );
						const_iterator::current = const_iterator::current -> next;
						return *this;
					}

					/**
					 * @brief      Post-increment operator.
					 */
					iterator operator++( int ) // it++;
					{
						assert( const_iterator::current != nullptr );
						auto temp = const_iterator::current;
						const_iterator::current = const_iterator::current -> next;
						return temp;
					}

					/**
					 * @brief      Pre-decrement operator.
					 */
					iterator & operator--() // --it;
					{
						assert( const_iterator::current != nullptr );
						const_iterator::current = const_iterator::current -> prev;
						return *this;
					}

					/**
					 * @brief      Post-decrement operator.
					 */
					iterator operator--( int ) // it--;
					{
						assert( const_iterator::current != nullptr );
						auto temp = const_iterator::current;
						const_iterator::current = const_iterator::current -> prev;
						return temp;
					}
			};

			/// [I] SPECIAL MEMBERS
			
			/**
			 * @brief      Default constructor. Creates an empty list.
			 */
			list()
				: m_size( 0 )
				, m_head( new Node() )
				, m_tail( new Node() ) 
			{
				m_head -> next = m_tail;
				m_tail -> prev = m_head;
			}

			/**
			 * @brief      Constructs the list with count default-inserted
			 *             instances of T.
			 *
			 * @param[in]  count  Number of instances to be created.
			 */
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

			/**
			 * @brief      Constructs the list with the contents of the range
			 *             [first, last).
			 *
			 * @param[in]  first    Where the range starts.
			 * @param[in]  last     Where it ends.
			 *
			 * @tparam     InputIt  Iterator to the list.
			 */
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

			/**
			 * @brief      Copy constructor. Constructs the list with the deep
			 *             copy of the contents of other.
			 *
			 * @param[in]  other  List to be copied.
			 */
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

			/**
			 * @brief      Constructs the list with the contents of the
			 *             initializer list init
			 *
			 * @param[in]  ilist  Initiliazer list to be copied.
			 */
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

			/**
			 * @brief      Destructs the list. The destructors of the elements
			 *             are called and the used storage is deallocated.
			 */
			~list()
			{
				clear();
				delete m_head;
				delete m_tail;
			}

			/**
			 * @brief      Copy assignment operator. Replaces the contents with
			 *             a copy of the contents of other
			 *
			 * @param[in]  other  List to be copied
			 *   
			 */
			list & operator= ( const list & other )
			{
				clear();
				for(auto i = other.cbegin(); i != other.cend(); ++i)
					push_back(*i);
				return *this;
			}

			/**
			 * @brief      Replaces the contents with those identified by
			 *             initializer list ilist
			 *
			 * @param[in]  ilist  The initializer list to be copied.
			 *
			 */
			list & operator= (std::initializer_list<T> ilist)
			{
				clear();
				for(auto i = ilist.begin(); i != ilist.end(); ++i)
					push_back(*i);
				return *this;
			}	

			/// [II] ITERATORS
			
			/**
			 * @brief      This function retrieves the reference for the address
			 *             of the beginning of the list.
			 *
			 * @return     Iterator to begin.
			 */
			iterator begin(void)
			{
				return iterator(m_head -> next);
			}

			/**
			 * @brief      This function retrieves the constant reference for
			 *             the address of the beginning of the list.
			 *
			 * @return     const_iterator to begin.
			 */			
			const_iterator cbegin(void) const
			{
				return const_iterator(m_head -> next);
			}

			/**
			 * @brief      This function retrieves the reference for the address
			 *             of the ending of the list.
			 *
			 * @return     Iterator to end.
			 */			
			iterator end(void)
			{
				return iterator(m_tail);
			}

			/**
			 * @brief      This function retrieves the constant reference for
			 *             the address of the ending of the list.
			 *
			 * @return     const_iterator to end.
			 */			
			const_iterator cend(void) const
			{
				return const_iterator(m_tail);
			}

			/// [III] CAPACITY
			
			/**
			 * @brief      Gets the number of elements stored in this list.
			 *
			 * @return     Size of the list.
			 */
			int size() const
			{
				return m_size;
			}

			/**
			 * @brief      Checks if the list is empty.
			 *
			 * @return     True if size's equal to zero. False, otherwise.
			 */
			bool empty() const
			{
				return m_size == 0;
			}

			/// [IV] MODIFIERS
			
			/**
			 * @brief      This function iterates over each element of the list
			 *             and deletes it. Then, resets m_head, m_tail and
			 *             m_size to their first configuration.
			 */
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

			/**
			 * @brief      Retrieves the front element of the list i.e the
			 *             m_head's next element.
			 *
			 * @return     Front element of the list.
			 */
			T & front()
			{
				if( empty() )
					throw std::out_of_range("Unnable to access front element of an empty list. \n");
				return m_head -> next -> data;
			}

			/**
			 * @brief      Retrieves as constant the front element of the list
			 *             i.e. the m_head's next element.
			 *
			 * @return     Constant front element of the list.
			 */
			const T & front() const
			{
				if( empty() )
					throw std::out_of_range("Unnable to access front element of an empty list. \n");
				return m_head -> next -> data;
			}

			/**
			 * @brief      Retrieves the back element of the list i.e. the
			 *             m_tail's previous element.
			 *
			 * @return     Back element of the list.
			 */
			T & back()
			{
				if( empty() )
					throw std::out_of_range("Unnable to access back element of an empty list. \n");
				return m_tail -> prev -> data;
			}

			/**
			 * @brief      Retrieves as constant the back element of the list
			 *             i.e. the m_tail's previous element.
			 *
			 * @return     Constant back element of the list.
			 */
			const T & back() const
			{
				if( empty() )
					throw std::out_of_range("Unnable to access back element of an empty list. \n");
				return m_tail -> prev -> data;
			}

			/**
			 * @brief      Pushes a new element to the list's front. Creates a
			 *             new node with the same m_head's next. Updates the
			 *             actual front element to point as previous element the
			 *             new node and then updates the m_head to point as next
			 *             the new node.
			 *
			 * @param[in]  value  Content of the element to be pushed.
			 */
			void push_front( const T & value )
			{
				auto new_node = new Node(value, m_head, m_head->next);
				m_head -> next -> prev = new_node;
				m_head -> next = new_node;
				++m_size;
			}

			/**
			 * @brief      Pushes a new element to the list's back. Creates a new node wit
			 *
			 * @param[in]  value  The value
			 */
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

			/**
			 * @brief      Removes the first element and updates the list's
			 *             linkage.
			 */
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

			/**
			 * @brief      Removes the last element and updates the list's
			 *             linkage.
			 */
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

			/**
			 * @brief      All
			 *
			 * @param[in]  value  The value
			 */
			void assign( const T& value )
			{
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