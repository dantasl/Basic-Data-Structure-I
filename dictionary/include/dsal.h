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
					if ( comp(_x, data) ) right = mid - 1;
					else left = mid + 1;
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
				if ( find == length - 1 ) { length -= 1;  return true; }				

				// Otherwise, we need to delete and fill the gap
				for ( auto i(find); i < length - 1; ++i )
				{
					data[i].id = data[i + 1].id;
					data[i].info = data[i + 1].info;
				}

				length -= 1;
				return true;
			}

			bool insert ( const Key & _newKey, const Data & _newInfo )
			{
				auto capacity = DAL<Key, Data, KeyComparator>::mi_Capacity;
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
				auto store_at = -1; // Where the new key will be inserted

				// Finding _newKey's predecessor (it will be inserted right after it)
				for(auto i(0); i != length; ++i)
				{
					if ( comp( data[i].id, _newKey ) ) store_at = i;						
				}

				// Check if found position is at end of dictionary
				if ( store_at == length - 1 )
				{
					data[length].id = _newKey;
					data[length].info = _newInfo;
					length += 1;
					return true;
				}
				else if ( store_at == - 1 ) // Means that its a insertion at the beginning of the dictionary
				{
					// Shift data to right to open gap for insertion
					for ( auto i(length); i > store_at + 1; --i )
					{
						data[i].id = data[i-1].id;
						data[i].info = data[i-1].info;
					}
					data[0].id = _newKey;
					data[0].info = _newInfo;
					length += 1;
					return true;
				}
				else // Means its a regular insertion at the "middle" of the dictionary
				{
					for ( auto i(length); i > store_at + 1; --i)
					{
						data[i].id = data[i-1].id;
						data[i].info = data[i-1].info;
					}

					data[store_at+1].id = _newKey;
					data[store_at+1].info = _newInfo;
					length += 1;
					return true;
				}
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
				return DAL<Key, Data, KeyComparator>::mpt_Data[len - 1].id;
			}

			bool successor ( const Key & _x, Key & _y ) const
			{
				if ( DAL<Key, Data, KeyComparator>::empty() ) return false;
				// Check if the provided key is in dictionary or is the last element of the dictionary.
				auto s = _search(_x);
				if ( s == -1 or s == DAL<Key, Data, KeyComparator>::mi_Length - 1) return false;
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