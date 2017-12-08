/**
 * @file    dal.h
 * @brief   Defining and implementing functions for DAL.
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @since   06/12/2017
 * @date    07/12/2017
 */

#ifndef _DAL_H_
#define _DAL_H_

namespace ac
{
	/**
	 * @brief      Class for Dictionary with Array List.
	 *
	 * @tparam     Key            Key of the element.
	 * @tparam     Data           Value associated to the key.
	 * @tparam     KeyComparator  Functor to compare keys.
	 */
	template< typename Key, typename Data, typename KeyComparator = std::less<Key> >
	class DAL
	{
		protected:
			
			/**
			 * @brief      Node structure representing pair key-information
			 */
			struct NodeAL 
			{
				Key id; // The key is a simple integer
				Data info; // The information is a chain of chars
			};

			static const int SIZE=50; // Defaul list size
			int mi_Length;			  // Current lenght of the list
			int mi_Capacity;		  // Maximum storage capacity
			NodeAL *mpt_Data;			  // Storage area: dinamic allocated array

			/**
			 * @brief      Auxiliar search. Receives a key and return its
			 *             position on the dictionary, if found. Otherwise,
			 *             returns -1.
			 *
			 * @param[in]  _x    Key of the element to be searched.
			 *
			 * @return     Where the found element is stored of -1, in case of
			 *             error.
			 */
			int _search ( const Key & _x ) const
			{
				KeyComparator comp;

				for(auto i(0); i < mi_Length; ++i)
				{
					if( not comp( mpt_Data[i].id, _x ) and not comp( _x, mpt_Data[i].id )  )
						return i;
				}
				return -1; 
			}

			public:
				
				/**
				 * @brief      Default constructor. Initializes dictionary,
				 *
				 * @param[in]  _MaxSz  Size of the dictionary. Provided none,
				 *                     default value is 50.
				 */
				DAL ( int _MaxSz = SIZE )
					: mi_Length(0)
					, mi_Capacity(_MaxSz)
					, mpt_Data( new NodeAL[_MaxSz] )
					{ /* empty */ }
				
				/**
				 * @brief      Destroys the object.
				 */
				virtual ~DAL () { delete [] mpt_Data; }

				/**
				 * @brief      Retrieves the dictionary's maximum size.
				 *
				 * @return     Total capacity of the dictionary.
				 */
				int capacity( void ) const
				{
					return mi_Capacity;
				}

				/**
				 * @brief      Checks if the dictionary is empty or not.
				 *
				 * @return     True if no elements are stored in the dictionary.
				 *             False otherwise.
				 */
				bool empty( void ) const
				{
					return mi_Length == 0;
				}

				/**
				 * @brief      Given a key by the client, searches for its
				 *             occurrence inside the dictionary and if found,
				 *             removes it. Then, it takes the last element and
				 *             inserts in the gap left by the removed element.
				 *
				 * @param[in]  _x    Key provided by the client to remove element.
				 * @param      _s    Where the value of the element to be deleted
				 *                   will be stored and used by the client.
				 *
				 * @return     True if able to remove element, false otherwise.
				 */
				bool remove ( const Key & _x, Data & _s )
				{
					if ( empty() ) return false;
					auto found_position = _search(_x);
					if ( found_position == -1 ) return false;
					
					// If the found element is at the end of the dictionary, don't need to fill gap
					if ( found_position == (mi_Length - 1) )						 
						_s = mpt_Data[found_position].info;
					else // Otherwise, we need to fill the gap with the last element of the dictionary
					{
						_s = mpt_Data[found_position].info;
						mpt_Data[found_position] = mpt_Data[mi_Length - 1];
					}			
					
					mi_Length--;
					return true;
				}

				/**
				 * @brief      Searches for the match on a key provided by the
				 *             client.
				 *
				 * @param[in]  _x    Key provided by the client to search element.
				 * @param      _s    Where the information about the found element
				 *                   will be stored and used by the client.
				 *
				 * @return     True if able to find element. False otherwise.
				 */
				bool search ( const Key & _x, Data & _s ) const
				{
					if ( empty() ) return false;
					auto found_position = _search(_x);
					if ( found_position == -1 ) return false;
					_s = mpt_Data[found_position].info;
					return true;
				}

				/**
				 * @brief      Inserts a new element inside the dictionary.
				 *
				 * @param[in]  _newKey   The key of the new element to be inserted.
				 * @param[in]  _newInfo  The data associated to the key.
				 *
				 * @return     True if able to insert, false otherwise.
				 */
				bool insert ( const Key & _newKey, const Data & _newInfo )
				{
					// Checks if the dictionary can store new data
					if ( mi_Length == mi_Capacity ) return false;

					// Iterates over the array checking if the client's input is unique
					for (auto i(0); i < mi_Length; ++i)
						if ( mpt_Data[i].id == _newKey ) return false;

					// Reaching here, the input is valid to be inserted
					mpt_Data[mi_Length].id = _newKey;
					mpt_Data[mi_Length].info = _newInfo;
					mi_Length++;

					return true;
				}

				/**
				 * @brief      This function iterates over each element on the
				 *             dictionary and searches for the minimum key.
				 *
				 * @return     The minimum key.
				 */				
				Key min () const
				{
					if ( mi_Length == 0 ) throw std::out_of_range("Cannot find min key on an empty dictionary.");
					KeyComparator comp;
					auto curr_min = mpt_Data[0].id;
					for( auto i(0); i != mi_Length; ++i )
					{
						if( comp( mpt_Data[i].id, curr_min ) ) curr_min = mpt_Data[i].id;
					}
					return curr_min;
				}

				/**
				 * @brief      This function iterates over each element on the
				 *             dictionary and searches for the maximum key.
				 *
				 * @return     The maximum key.
				 */
				Key max () const
				{
					// Check if dictionary is empty
					if ( mi_Length == 0 ) throw std::out_of_range("Cannot find max key on an empty dictionary.");
					KeyComparator comp;
					auto curr_max = mpt_Data[0].id;
					for( auto i(0); i != mi_Length; ++i )
					{
						if ( not comp( mpt_Data[i].id, curr_max ) ) curr_max = mpt_Data[i].id;
					}
					return curr_max;
				}

				/**
				 * @brief      Given a key, iterates over the whole dictionary
				 *             searching for the element which key is immediate
				 *             successor of the one provided. Since this dictionary
				 *             is not sorted, the search is linear.
				 *
				 * @param[in]  _x    Key provided by the user to find the successor.
				 * @param      _y    Where the successor's key will be stored and
				 *                   used by the client.
				 *
				 * @return     True if able to find successor. False otherwise.
				 */
				bool successor ( const Key & _x, Key & _y ) const
				{
					if ( mi_Length == 0 ) return false;
					// Check if the provided key is in dictionary
					if ( _search(_x) == -1 ) return false;
					
					KeyComparator comp;
					Key suc = max();

					// If _x is equal to the max key, his successor would be out of the dictionary
					if ( not comp(suc, _x) and not comp(_x, suc) ) return false;
					
					// Iterating over the dictionary searching the immediate successor
					for( auto i(0); i != mi_Length; ++i )
					{	
						if ( comp( _x, mpt_Data[i].id ) and comp( mpt_Data[i].id, suc ) )
							suc = mpt_Data[i].id;
					}
					_y = suc;
					return true;
				}

				/**
				 * @brief      Given a key, iterates over the whole dictionary
				 *             searching for the element which key is immediate
				 *             predecessor of the one provided. Since this
				 *             dictionary is not sorted, the search is linear.
				 *
				 * @param[in]  _x    Key provided by the user to find the
				 *                   predecessor.
				 * @param      _y    Where the predecessor's key will be stored and
				 *                   used by the client.
				 *
				 * @return     True if able to find predecessor. False otherwise.
				 */
				bool predecessor ( const Key _x, Key & _y ) const
				{
					if ( mi_Length == 0 ) return false;
					// Check if the provided key is in dictionary
					if ( _search(_x) == -1 ) return false;
					
					KeyComparator comp;
					Key pre = min();

					// If _x is equal to the min key, his predecessor would be out of the dictionary
					if ( not comp(pre, _x) and not comp(_x, pre) ) return false;
					
					for( auto i(0); i != mi_Length; ++i )
					{
						if ( comp( mpt_Data[i].id, _x ) and comp( pre, mpt_Data[i].id ) )
							pre = mpt_Data[i].id;
					}
					_y = pre;
					return true;	
				}

				/**
				 * @brief      Overloading stream operator to print the dictionary's
				 *             elements.
				 */
				inline friend
				std::ostream &operator<< ( std::ostream& _os, const DAL& _oList )
				{
					_os << "[ ";
					for( int i(0); i < _oList.mi_Length; ++i )
						_os << "{id: " << _oList.mpt_Data[i].id << ", info: "
							<< _oList.mpt_Data[i].info << "} ";
					_os << "]";
					return _os;		
				}
	};
}

#endif