#ifndef _DAL_H_
#define _DAL_H_

namespace ac
{
	template< typename Key, typename Data, typename KeyComparator = std::less<Key> >
	class DAL
	{
		protected:
			
			struct NodeAL // Node structure representing pair key-information
			{
				Key id; // The key is a simple integer
				Data info; // The information is a chain of chars
			};

			static const int SIZE=50; // Defaul list size
			int mi_Length;			  // Current lenght of the list
			int mi_Capacity;		  // Maximum storage capacity
			NodeAL *mpt_Data;			  // Storage area: dinamic allocated array

			// Auxiliar search
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
				
				DAL ( int _MaxSz = SIZE )
					: mi_Length(0)
					, mi_Capacity(_MaxSz)
					, mpt_Data( new NodeAL[_MaxSz] )
					{ /* empty */ }
				
				virtual ~DAL () { delete [] mpt_Data; }

				int capacity( void ) const
				{
					return mi_Capacity;
				}

				bool empty( void ) const
				{
					return mi_Length == 0;
				}

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
				
				bool search ( const Key & _x, Data & _s ) const
				{
					if ( empty() ) return false;
					auto found_position = _search(_x);
					if ( found_position == -1 ) return false;
					_s = mpt_Data[found_position].info;
					return true;
				}
				
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
				
				Key max () const
				{
					if ( mi_Length == 0 ) throw std::out_of_range("Cannot find max key on an empty dictionary.");
					KeyComparator comp;
					auto curr_max = mpt_Data[0].id;
					for( auto i(0); i != mi_Length; ++i )
					{
						if ( not comp( mpt_Data[i].id, curr_max ) ) curr_max = mpt_Data[i].id;
					}
					return curr_max;
				}

				bool successor ( const Key & _x, Key & _y ) const
				{
					if ( mi_Length == 0 ) return false;
					// Check if the provided key is in dictionary
					if ( _search(_x) == -1 ) return false;
					
					KeyComparator comp;
					Key suc = max();

					// If _x is equal to the max key, his successor would be out of the dictionary
					if ( not comp(suc, _x) and not comp(_x, suc) ) return false;
					
					for( auto i(0); i != mi_Length; ++i )
					{	
						if ( comp( _x, mpt_Data[i].id ) and comp( mpt_Data[i].id, suc ) )
							suc = mpt_Data[i].id;
					}
					_y = suc;
					return true;
				}

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