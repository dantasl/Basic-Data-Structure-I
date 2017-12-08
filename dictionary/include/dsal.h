#ifndef _DSAL_H_
#define _DSAL_H_

#include "dal.h"

namespace ac
{
	template< typename Key, typename Data, typename KeyComparator = std::less<Key> >
	class DSAL : public DAL<Key, Data, KeyComparator>
	{
		protected:
			int _search ( const Key & _x ) const
			{
				KeyComparator comp;
				auto dict_size = DAL<Key, Data, KeyComparator>::mi_Length;
				int left(0);
				int right( dict_size - 1 );
				int mid(0);
				
				while ( left <= right )
				{
					mid = (left + right) / 2;
					auto data = DAL<Key, Data, KeyComparator>::mpt_Data[mid].id;
					if ( not comp(data, _x) and not comp(_x, data)	)
						return mid;
					if ( comp(data, _x) ) left = mid + 1;
					else right = mid - 1;
				}

				return -1;	
			}

		public:			
			DSAL( int _MaxSz = DAL<Key, Data, KeyComparator>::SIZE )
				: DAL< Key, Data, KeyComparator > ( _MaxSz )
			{ /* empty */ }

			virtual ~DSAL() { /* empty */ }

			bool remove ( const Key & _x, Data & _s )
			{
				// Checks if dictionary is empty
				if ( DAL<Key, Data, KeyComparator>::empty() ) return false;
				
				auto &length = DAL<Key, Data, KeyComparator>::mi_Length;
				auto &data = DAL<Key, Data, KeyComparator>::mpt_Data;

				// Searches for key provided by the client
				auto find = _search( _x );

				// Checks if element was found
				if ( find == -1 ) return false;

				// Updates _s with the found element
				_s = data[find].info;

				// Checks if element is the dictionary's back
				if ( find == length ) { length -= 1;  return true; }				

				// Otherwise, we need to delete and fill the gap
				for ( auto i(length); i >= find; --i )
				{
					data[i].id = data[i - 1].id;
					data[i].info = data[i - 1].info;
				}

				length -= 1;
				return true;
			}

			bool insert ( const Key & _newKey, const Data & _newInfo )
			{
				/*auto capacity = DAL<Key, Data, KeyComparator>::mi_Capacity;
				auto &length = DAL<Key, Data, KeyComparator>::mi_Length;
				auto &data = DAL<Key, Data, KeyComparator>::mpt_Data;

				// Checks if the dictionary is empty and this is the first insertion
				if ( length == 0 )
				{
					data[0].id = _newKey;
					data[0].info = _newInfo;
					length += 1;
					return true;
				}

				// Checks if the dictionary can store new data and the client's input is unique
				if ( length == capacity or _search(_newKey) != -1) return false;
				
				// We need to check where the input will be stored. For this, we need to find its immediate predecessor.
				KeyComparator comp;
				Key pre = min();
				int pre_pos = 0; // Stores the position of the predecessor element

				// Finding _newKey's predecessor
				for(auto i(0); i != length; ++i)
				{
					if ( comp( data[i].id, _newKey ) and comp( pre, data[i].id ) )
					{
						pre = data[i].id;
						pre_pos = i;
						break;
					}						
				}

				std::cout << "Inserting " << _newKey << " with predecessor " << data[pre_pos].id << std::endl;
				for ( auto i(0); i != length; ++i ) std::cout << data[i].id << std::endl;

				// Check if position to insert _newKey is at the dictionary's back
				if ( pre_pos == length - 1 )
				{
					data[length].id = _newKey;
					data[length].info = _newInfo;
					length += 1;
					return true;
				}

				// Otherwise, we need to shift all data to the right and insert new element
				for ( auto i(length - 1); i >= pre_pos ; --i )
				{
					data[i].id = data[i - 1].id;
					data[i].info = data[i - 1].info;
				}

				data[pre_pos + 1].id = _newKey;
				data[pre_pos + 1].info = _newInfo;
				length += 1;
				return true;*/
				auto &length = DAL<Key, Data, KeyComparator>::mi_Length;
				auto &data = DAL<Key, Data, KeyComparator>::mpt_Data;
				auto capacity = DAL<Key, Data, KeyComparator>::mi_Capacity;

				auto t = _search(_newKey);
				//<! check if has space in list or if empty list
				if ( length == capacity or t != -1) return false;

				
				KeyComparator comp;
				Key aux;
				auto possible_pos = 0;
				auto pos = -1;

				//<! finds the correct position to insert
				while ( possible_pos < length )
				{
					aux = data[possible_pos].id;
					if ( comp( aux, _newKey) ) pos = possible_pos;

					possible_pos++;
				}

				//<! check if the insertion is in the end
				if ( pos == length-1 )
				{
					data[length].id = _newKey;
					data[length].info = _newInfo;
					length++;
					return true;
				}
				else if ( pos == -1)
				{
					//<! open space
					for ( auto i(length); i > pos+1; --i)
					{
						data[i].id = data[i-1].id;
						data[i].info = data[i-1].info;
					}
					data[0].id = _newKey;
					data[0].info = _newInfo;
					length++;
					return true;
				}else
				{
					//<! open space
					for ( auto i(length); i > pos+1; --i)
					{
						data[i].id = data[i-1].id;
						data[i].info = data[i-1].info;
					}

						data[pos+1].id = _newKey;
						data[pos+1].info = _newInfo;
						length++;
						return true;
				}
				
				return false;
			}

			Key min( void ) const
			{
				if ( DAL<Key, Data, KeyComparator>::mi_Length == 0 )
					throw std::out_of_range("Cannot access min element on an empty dictionary.");
				return DAL<Key, Data, KeyComparator>::mpt_Data[0].id;
			}

			Key max( void ) const
			{
				auto len = DAL<Key, Data, KeyComparator>::mi_Length;
				if ( len == 0 )
					throw std::out_of_range("Cannot access max element on an empty dictionary.");
				return DAL<Key, Data, KeyComparator>::mpt_Data[len].id;
			}

			bool successor ( const Key & _x, Key & _y ) const
			{
				if ( DAL<Key, Data, KeyComparator>::empty() ) return false;
				// Check if the provided key is in dictionary or is the last element of the dictionary.
				auto s = _search(_x);
				if ( s == -1 or s == DAL<Key, Data, KeyComparator>::mi_Length ) return false;
				_y = DAL<Key, Data, KeyComparator>::mpt_Data[s + 1].id;
				return true;
			}

			bool predecessor ( const Key & _x, Key & _y ) const
			{
				if ( DAL<Key, Data, KeyComparator>::empty() ) return false;
				// Check if the provided key is in dictionary or is the first element of the dictionary.
				auto s = _search(_x);
				if ( s == -1 or s == 0 ) return false;
				_y = DAL<Key, Data, KeyComparator>::mpt_Data[s - 1].id;
				return true;
			}
	};
}

#endif